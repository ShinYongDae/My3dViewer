// Dlg3DViewer.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "My3dViewer.h"
#include "Dlg3DViewer.h"
#include "afxdialogex.h"
#include "GlobalDefineAOR.h"

// CDlg3DViewer 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlg3DViewer, CDialog)

CDlg3DViewer::CDlg3DViewer(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_3D, pParent)
{
	m_nSelectDrawType = SHAPE::SHAPE_NONE;
	m_nPolygonDrawVertex = 0;
	for (int i = 0; i < 100; i++)
	{
		m_ptPolygon[i] = CPoint(0, 0);
	}
	for (int i = 0; i < 4; i++)
	{
		m_ptRect[i] = CPoint(0, 0);
	}
	for (int i = 0; i < 2; i++)
	{
		m_ptLine[i] = CPoint(0, 0);
	}

	m_nIndexOfRefer = 0;

	for (int i = 0; i < REFER_BUFFER; i++)
	{
		m_pReferenceData[i] = NULL;
	}
	m_fpos_start = 50.00;
	m_fScan_Range = 0.2;
	m_fScan_Ramp = 0.2;
	m_bFitSuccess = FALSE;
	m_fMax = 20;
	m_fMin = -20;

	// for OpenGL Rendering
	m_bOpMode = 0;
	_mouseButton = 0;
	_angleHor = 40;
	_angleVer = -36;
	_fovAngle = 45;
	_eyePos.x = 0;
	_eyePos.y = -4;
	_eyePos.z = 0;
	_centerPos.x = 0;
	_centerPos.y = 0;
	_centerPos.z = 0;
}

CDlg3DViewer::~CDlg3DViewer()
{
	RemoveAllZygoXYZ();

	//if (this->GetSafeHwnd())
	//{
	//	m_pView->MakeCurrent();
	//	if (m_pView->m_hWnd)
	//		m_pView->DestroyWindow();
	//}
	//if (m_pView->m_hWnd)
	//	delete m_pView;

	if(m_matrixZ.total() > 0)
		m_matrixZ.release(); // 자동으로 해제되나 명시적 호출 가능
	if(m_matrixA.total() > 0)
		m_matrixA.release(); // 자동으로 해제되나 명시적 호출 가능

	cv::setNumThreads(0); // 만약 루프가 너무 많아 누수가 의심되면, Thread 로컬 캐시 정리

	if (m_pView)
	{
		m_pView->DestroyWindow();
		delete m_pView;
		m_pView = nullptr;
	}


	for (int i = 0; i < REFER_BUFFER; i++)
	{
		if (m_pReferenceData[i])
		{
			delete m_pReferenceData[i];
			m_pReferenceData[i] = NULL;
		}
	}
}

void CDlg3DViewer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ZOOM, m_ChkRectZoom);
	DDX_Control(pDX, IDC_CHECK_ZOOMIN, m_ChkZoomIn);
	DDX_Control(pDX, IDC_CHECK_ZOOMOUT, m_ChkZoomOut);
	DDX_Control(pDX, IDC_CHECK_FIT, m_ChkFit);
	DDX_Control(pDX, IDC_CHK_ONLY_RESIN, m_ChkOnlyResin);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_Pic);
}


BEGIN_MESSAGE_MAP(CDlg3DViewer, CDialog)
	ON_MESSAGE(WM_UPDATE_3D_MODEL, OnUpdate3DModel)
	ON_MESSAGE(WM_USER_RENDER, OnGLRender)
END_MESSAGE_MAP()


// CDlg3DViewer 메시지 처리기입니다.


BOOL CDlg3DViewer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect rt;
	GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(rt);
	ScreenToClient(rt);

	m_pView = new COpenGLViewEx();
	m_pView->m_bMessageSendMode = 1;
	m_pView->Create(NULL, NULL, WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, rt, this, 0);
	m_pView->SetCoordinate(IDC_STATIC_VIEW, this, CdSize(686, 1000), CdPoint(-500, -250), CdPoint(0, 0));

	m_pView->MakeCurrent();
	m_pView->SetBackGroundColor(BLACK);

	CReferenceData *pRefer = m_pReferenceData[m_nIndexOfRefer];
	if(pRefer)
		wglShareLists(pRefer->m_pOpenGLView->m_hRC, pRefer->m_pOpenGLView->m_hRC);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlg3DViewer::DispFree()
{
	if (m_pView)
		m_pView->DispFree();
}

void CDlg3DViewer::InitReference(int nIndex, CWnd *pView, CWnd *pViewPiece, CWnd *pViewMask)
{
	if (!m_pReferenceData[nIndex])
	{
		m_pReferenceData[nIndex] = new CReferenceData(pView, pViewPiece, pViewMask, this, nIndex);
	}
}

LRESULT CDlg3DViewer::OnUpdate3DModel(WPARAM wParam, LPARAM lParam)
{
	SSR3DData *S3DData = Get3DData();
	if (S3DData->m_bValid)
	{
		cv::Mat matZMap, matResize;
		cv::Size szResize;
		m_pView->MakeCurrent();

		m_Model.m_ZMap = m_matrixZ.clone();
		if (!m_Model.m_ZMap.empty())
		{
			m_Model.m_ColorImg = S3DData->m_matDepthMapColor.clone();
			m_Model.m_GrayImg = S3DData->m_AmpMatrix.clone();
			m_Model.m_ResinImg = S3DData->m_matOnlyResin.clone();

			m_Model.MakeModel();
			double yScale, xScale;
			yScale = 1000 / S3DData->m_matDepthMap.rows;
			xScale = 1000 / S3DData->m_matDepthMap.cols;
			m_Model.ApplyScaleAndOffset(0, 0, 0, xScale, yScale, 5000);
		}
	}

	m_pView->Refresh();
	return 0;
}

SSR3DData* CDlg3DViewer::Get3DData()
{
	return &m_st3D;
}

CString CDlg3DViewer::ExtractInfo(CString sPath)
{
	CString sLine, sData = _T("");
	CStdioFile stdfile;	// Text로 파일을 ofen. (Data format : char형)
	if (!stdfile.Open(sPath, CFile::modeRead | CFile::shareDenyNone, NULL))
	{
		AfxMessageBox(_T("Fail to load Info."));
		return sData;
	}

	RemoveAllZygoXYZ();

	BOOL bExist = TRUE;
	CString str = _T("");
	int nLine = 0, nCol = 0;
	TCHAR seps[] = _T(" ");
	TCHAR *token;
	TCHAR tszStr[MAX_PATH];
	CString sResH, sResV;
	BOOL bPhaseData = FALSE;
	int nColY, nRowX;
	float fMicronZ;
	int nStLinePhaseData = 0, nEdLinePhaseData = 0;
	int nPrevLineColY0 = 0, nLinesColY = 0, nLinesRowX = 0;

	while (bExist)
	{
		bExist = stdfile.ReadString(str);
		if (bExist)
		{
			nLine++;

			if (bPhaseData)
			{
				if (str == "#")
				{
					nEdLinePhaseData = nLine - 1;
					break;
				}

				StringToTCHAR(str, tszStr);
				token = _tcstok(tszStr, seps); //문자열을 기준에 따라 token에 임시 저장한다.
				while (token != NULL)
				{
					if (nCol == 0)
						nColY = _ttoi(token);
					else if(nCol == 1)
						nRowX = _ttoi(token);
					else if (nCol == 2)
						fMicronZ = _tstof(token);

					if (!nColY)
					{
						if (!nPrevLineColY0)
							nPrevLineColY0 = nLine;
						else if (!nLinesColY)
							nLinesColY = nLine - nPrevLineColY0;
					}

					nCol++;
					token = _tcstok(NULL, seps);
				}
				nCol = 0;

				stTagZygoXYZ _xyz;
				_xyz.nColY = nColY;
				_xyz.nRowX = nRowX;
				_xyz.fZmm = fMicronZ / 1000.0;
				m_stZygoInfo3D.m_arZygoXYZ.Add(_xyz);
			}
			else if (nLine == 8)
			{
				StringToTCHAR(str, tszStr);
				token = _tcstok(tszStr, seps); //문자열을 기준에 따라 token에 임시 저장한다.
				while (token != NULL)
				{
					nCol++;
					if (nCol == 3)
					{
						sResH.Format(_T("%s"), token);
					}
					else if(nCol == 7)
					{
						sResV.Format(_T("%s"), token);
					}
					token = _tcstok(NULL, seps);
				}
				nCol = 0;
			}
			else if (str == "#")
			{
				bPhaseData = TRUE;
				nStLinePhaseData = nLine + 1;
			}

			sLine.Format(_T("%s\r\n"), str);
			sData += sLine;
		}
	}
	stdfile.Close();

	if(!nEdLinePhaseData)
		nEdLinePhaseData = nLine - 1;
	int nTotLinesPhaseData = nEdLinePhaseData - nStLinePhaseData + 1;
	nLinesRowX = nTotLinesPhaseData / nLinesColY;

	int nPos, nExp;
	double dNum;
	CString sNum, sExp;
	TCHAR tszNum[MAX_PATH], tszExp[MAX_PATH];

	nPos = sResH.Find('e', 0);
	sNum = sResH.Left(nPos);
	sExp = sResH.Right(sResH.GetLength() - (nPos+1));
	StringToTCHAR(sNum, tszNum);
	StringToTCHAR(sExp, tszExp);
	m_stZygoInfo3D.dResHmm = _tstof(tszNum) * pow(10, _ttoi(tszExp)) * 1000.0;

	nPos = sResV.Find('e', 0);
	sNum = sResV.Left(nPos);
	sExp = sResV.Right(sResV.GetLength() - (nPos + 1));
	StringToTCHAR(sNum, tszNum);
	StringToTCHAR(sExp, tszExp);
	m_stZygoInfo3D.dResVmm = _tstof(tszNum) * pow(10, _ttoi(tszExp)) * 1000.0;

	m_stZygoInfo3D.nTotalPhaseData = m_stZygoInfo3D.m_arZygoXYZ.GetCount();
	m_stZygoInfo3D.nSizeColY = nLinesColY;
	m_stZygoInfo3D.nSizeRowX = nLinesRowX;

	uint xSize = nLinesColY;
	uint ySize = nLinesRowX;
	m_matrixZ = cv::Mat(ySize, xSize, CV_32FC1); // ( row, col, 32비트 부동소수점(float) 자료형 )
	m_matrixA = cv::Mat(ySize, xSize, CV_8UC1);

	int nidx = 0;
	//COPY RAW DATA
	for (uint i = 0; i < ySize; i++) 
	{
		for (uint j = 0; j < xSize; j++) 
		{
			stTagZygoXYZ stXYZ = m_stZygoInfo3D.m_arZygoXYZ.GetAt(nidx); // Non scaled data.
			m_matrixZ.at<float>(i, j) = stXYZ.fZmm;
			//m_matrixA.at<float>(i, j) = stXYZ.fZmm;
			nidx++;
		}
	}

	return sData;
}

void CDlg3DViewer::RemoveAllZygoXYZ()
{
	int nTotal = m_stZygoInfo3D.m_arZygoXYZ.GetCount();
	if (nTotal > 0)
	{
		m_stZygoInfo3D.m_arZygoXYZ.RemoveAll();
	}
}

void CDlg3DViewer::Grab(CString sPath) // "C:\\AORSet\\Data3D\\%d-%d.exr"
{
	m_bFitSuccess = FALSE;
	CString sData = ExtractInfo(sPath);

	cv::Scalar scalarAvg;
	scalarAvg = cv::mean(m_matrixZ); // memory leak
	double  dLastAvg = scalarAvg[0];
	//double  dLastAvg = 1.0;

	double dLastMax = -9999999;
	double dLastMin = 9999999;
	minMaxLoc(m_matrixZ, &dLastMin, &dLastMax); // memory leak

	double dAvg = GetDepthAvg(m_matrixZ); // memory leak
	//double dAvg = 1.0;

	int nPixels = m_matrixZ.rows * m_matrixZ.cols;
	double dStdev = 0;
	double dVar = 0;

	for (int j = 0; j < m_matrixZ.rows; j++)
	{
		for (int i = 0; i < m_matrixZ.cols; i++)
		{
			float fColor = m_matrixZ.at<float>(j, i);// 한 픽셀식 검사 

			dVar += (dAvg - fColor)*(dAvg - fColor);
		}
	}
	dStdev = sqrt(dVar / nPixels);

	for (int j = 0; j < m_matrixZ.rows; j++)
	{
		for (int i = 0; i < m_matrixZ.cols; i++)
		{
			float fColor = m_matrixZ.at<float>(j, i);// 한 픽셀식 검사 

			if (fabs(fColor - dAvg) > dStdev * 3)
			{
				fColor = dAvg;
			}
			m_matrixZ.at<float>(j, i) = fColor;
		}
	}

	SSR3DData *S3DData = Get3DData();
	S3DData->m_nSizeX = m_matrixZ.cols;
	S3DData->m_nSizeY = m_matrixZ.rows;
	S3DData->m_matDepthMap = m_matrixZ.clone();
	S3DData->m_dAvg = dLastAvg;
	S3DData->m_dMax = dLastMax;
	S3DData->m_dMin = dLastMin;
	S3DData->m_dStdev = dStdev;
	S3DData->m_dScanStart = m_fpos_start;
	S3DData->m_dScanEnd = m_fpos_end;
	S3DData->m_dTgu = m_fpos_tgu;
	S3DData->m_dTgd = m_fpos_tgd;
	S3DData->m_dRamp = m_fScan_Ramp;
	S3DData->m_dRange = m_fScan_Range;
	S3DData->m_dXResolution = _3D_RESOLUTION;
	S3DData->m_dYResolution = _3D_RESOLUTION;
	S3DData->m_bValid = 1;

	//cv::setNumThreads(0);
	//vec.clear(); // 더 이상 필요 없으면,
	Prepare3D();
	Display3D();
	Auto3D();
}

float CDlg3DViewer::GetDepthAvg(cv::Mat &matrixZ)
{
	double dMaxZ, dMinZ;
	minMaxLoc(matrixZ, &dMinZ, &dMaxZ);

	cv::Mat matrixZchar = cv::Mat(matrixZ.rows, matrixZ.cols, CV_8UC1);
	int nValue;
	for (uint i = 0; i < matrixZchar.rows; i++)
	{
		for (uint j = 0; j < matrixZchar.cols; j++)
		{
			nValue = ConvertInt((matrixZ.at<float>(i, j) - dMinZ) / (dMaxZ - dMinZ) * 255.0);
			if (nValue > 255)
			{
				nValue = 255;
			}
			if (nValue < 0)
			{
				nValue = 0;
			}
			matrixZchar.at<uchar>(i, j) = nValue;
		}
	}

	cv::Mat Imagehist = calcGrayHist(matrixZchar);

	double histMax = 0;
	cv::Point maxLoc;
	minMaxLoc(Imagehist, 0, &histMax, 0, &maxLoc);


	DPOINT fptHist[256];
	for (int i = 0; i < 256; i++)
	{
		fptHist[i].x = i;
		fptHist[i].y = Imagehist.at<float>(i) * 200.0 / histMax;
	}
	//matrixZchar.release();
	//Imagehist.release();

	vector<IMAGE_HISTOGRAM> vecHist;
	IMAGE_HISTOGRAM stImageHist;
	int nSize = 0;
	int nUpperGray = 0, nLowerGray = 0;
	double dUpperGray = 0, dLowerGray = 0;
	double dCount;
	for (int i = 0; i < 256; i++)
	{
		if (i - 1 > 0)
		{
			if (fptHist[i - 1].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i - 2 > 0)
		{
			if (fptHist[i - 2].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i - 3 > 0)
		{
			if (fptHist[i - 3].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i - 4 > 0)
		{
			if (fptHist[i - 4].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i - 5 > 0)
		{
			if (fptHist[i - 5].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i + 1 < 256)
		{
			if (fptHist[i + 1].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i + 2 < 256)
		{
			if (fptHist[i + 2].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i + 3 < 256)
		{
			if (fptHist[i + 3].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i + 4 < 256)
		{
			if (fptHist[i + 4].y >= fptHist[i].y)
			{
				continue;
			}
		}
		if (i + 5 < 256)
		{
			if (fptHist[i + 5].y >= fptHist[i].y)
			{
				continue;
			}
		}
		stImageHist.nGray = fptHist[i].x;
		stImageHist.fValue = fptHist[i].y;
		vecHist.push_back(stImageHist);
	}

	nSize = vecHist.size();
	if (nSize > 1)
	{
		vector<IMAGE_HISTOGRAM> vecLower, vecUpper;
		IMAGE_HISTOGRAM stUpper, stLower;

		stUpper = vecHist.at(nSize - 1);
		stLower = vecHist.at(0);

		vecLower.push_back(stLower);
		vecUpper.push_back(stUpper);

		vecHist.erase(vecHist.begin());
		vecHist.erase(vecHist.begin() + vecHist.size() - 1);

		for (int i = 0; i < vecHist.size(); i++)
		{
			stImageHist = vecHist.at(i);
			if (abs(stLower.nGray - stImageHist.nGray) > abs(stUpper.nGray - stImageHist.nGray))
			{
				vecUpper.push_back(stImageHist);
			}
			else
			{
				vecLower.push_back(stImageHist);
			}
		}
		dCount = 0;
		for (int i = 0; i < vecUpper.size(); i++)
		{
			dUpperGray += vecUpper.at(i).nGray * vecUpper.at(i).fValue;
			dCount += vecUpper.at(i).fValue;
		}
		nUpperGray = ConvertInt(dUpperGray / dCount);

		dCount = 0;
		for (int i = 0; i < vecLower.size(); i++)
		{
			dLowerGray += vecLower.at(i).nGray * vecLower.at(i).fValue;
			dCount += vecLower.at(i).fValue;
		}
		nLowerGray = ConvertInt(dLowerGray / dCount);

		//vecLower.clear();
		//vecUpper.clear();
	}

	//vecHist.clear();

	float fMidGray = (float)(nUpperGray + nLowerGray) / 2.0;

	return fMidGray / 255.0 * (dMaxZ - dMinZ) + dMinZ;
}

cv::Mat CDlg3DViewer::calcGrayHist(const cv::Mat& img)
{
	CV_Assert(img.type() == CV_8U);

	cv::Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, cv::noArray(), hist, dims, histSize, ranges, true);

	return hist;
}

void CDlg3DViewer::SetPosition(float fCurPos)
{
	/*
	//DOWN SCAN
	m_fpos_tgu = 0;
	m_fpos_tgd = fCurPos + m_fScan_Range/2.0f;// [mm]
	m_fpos_start = fCurPos + m_fScan_Range / 2.0f + m_fScan_Ramp; // [mm]
	m_fpos_end = fCurPos - m_fScan_Range / 2.0f - m_fScan_Ramp; // [mm]
	m_fpos_reset = m_fpos_start; // [mm]
	*/
	//UP SCAN

	m_fpos_tgd = 0;
	m_fpos_tgu = fCurPos;// [mm]
	m_fpos_start = fCurPos - m_fScan_Range / 2.0f - m_fScan_Ramp; // [mm]
	m_fpos_end = fCurPos + m_fScan_Range / 2.0f + m_fScan_Ramp; // [mm]
	m_fpos_reset = m_fpos_start; // [mm]
}

TCHAR* CDlg3DViewer::StringToTCHAR(CString str)
{
	TCHAR *tszStr = NULL;
	int nLen = str.GetLength() + 1;
	tszStr = new TCHAR[nLen];
	memset(tszStr, 0x00, nLen * sizeof(TCHAR));
	_tcscpy(tszStr, str);

	return tszStr;
}

void CDlg3DViewer::StringToTCHAR(CString str, TCHAR* tszStr)
{
	int nLen = str.GetLength() + 1;
	if (nLen > MAX_PATH)
	{
		nLen = MAX_PATH;
	}
	memset(tszStr, 0x00, nLen * sizeof(TCHAR));
	_tcsncpy(tszStr, str, nLen - 1);

	return;
}


LRESULT CDlg3DViewer::OnGLRender(WPARAM wParam, LPARAM lParam)
{
	SSR3DData *S3DData = Get3DData();
	if (S3DData->m_bValid == 0)
		return 0;

	if (m_bOpMode == 0)
	{

		if (lParam == WM_LBUTTONDOWN)
		{
			_mouseButton = 1;
			_mouseDownPoint = m_pView->m_ptCurPos;
		}
		else if (lParam == WM_LBUTTONUP)
		{
			_mouseDownPoint = CPoint(0, 0);
			_mouseButton = 0;
		}
		else if (lParam == WM_RBUTTONDOWN)
		{
			_mouseButton = 2;
			_mouseDownPoint = m_pView->m_ptCurPos;
		}
		else if (lParam == WM_RBUTTONUP)
		{
			_mouseDownPoint = CPoint(0, 0);
			_mouseButton = 0;
		}
		else if (lParam == WM_MOUSEHWHEEL)
		{
			if (m_pView->m_dWheelZDelta == 1)
			{
				m_pView->ZoomIn(1.1);
			}
			else
				m_pView->ZoomOut(1.1);

			return 0;

			//_eyePos.y += m_pView->m_dWheelZDelta;
		}
		else if (lParam == WM_MOUSEMOVE)
		{
			if (_mouseButton == 1) {
				//Increment the object rotation angles
				_angleHor -= (m_pView->m_ptCurPos.x - _mouseDownPoint.x) / 3.6;
				_angleVer -= (m_pView->m_ptCurPos.y - _mouseDownPoint.y) / 3.6;

				//double dy = 0.3*(point.x-_mouseDownPoint.x);
				//double dp = 0.3*(point.y-_mouseDownPoint.y);
				//CordTransform dt(0, 0, 0, 0, _DEG2RAD*-dp, _DEG2RAD*dy);
				//_tr *= dt;

			}
			else if (_mouseButton == 2) {
				_centerPos.x -= (m_pView->m_ptCurPos.x - _mouseDownPoint.x) / 100.;
				_centerPos.z += (m_pView->m_ptCurPos.y - _mouseDownPoint.y) / 100.;

				//double dy = 0.002*(point.x-_mouseDownPoint.x);
				//double dz = 0.002*(point.y-_mouseDownPoint.y);
				//CordTransform dt(0, dy, dz, 0, 0, 0);
				//_tr *= dt;
			}
			else if (_mouseButton == 3) {
				//double dy = 0.3*(point.x-_mouseDownPoint.x);
				//CordTransform dt(0, 0, 0, _DEG2RAD*dy, 0, 0);
				//_tr *= dt;
			}

			_mouseDownPoint = m_pView->m_ptCurPos;

		}
	}

	GLfloat ambientLight[] = { 0.3f, 0.4f, 0.5f, 1.0f };
	GLfloat diffuseLight[] = { 0.2f, 0.5f, 0.2f, 1.0f };
	GLfloat lightPos[] = { -1500.0f, -500.0f, 5000.0f, 1.0f };
	GLfloat specular[] = { 0.2f, 0.5f, 0.5f, 1.0f };
	GLfloat specref[] = { 1.0f, 0.1f, 1.0f, 1.0f };

	bool bLight = 0;
	//glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	if (bLight)
	{
		//glEnable(GL_DEPTH_TEST); // Enables Depth Testing
		glEnable(GL_FRONT_FACE); // 뒷면에 대해서는 계산하지 말라
		glFrontFace(GL_CCW);   // 시계방향이 앞면이다.
		glEnable(GL_LIGHTING); // 빛을 사용한다.

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glEnable(GL_LIGHT0); // 0번빛을 사용한다.

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 50);
		glMaterialfv(GL_BACK, GL_SPECULAR, specref);
		glMateriali(GL_BACK, GL_SHININESS, 50);
	}
	//	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	// Really Nice Perspective    Calculations
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glPushMatrix();
	// 보는 시각 설정
	gluLookAt(_eyePos.x, _eyePos.y, _eyePos.z, _centerPos.x, _centerPos.y, _centerPos.z, 0, 0, 1);
	// gluLookAt (_tr(0,3), _tr(1,3), _tr(2,3),   _tr(0,3) + _tr(0,0), _tr(1,3) + _tr(1,0), _tr(2,3) + _tr(2,0), _tr(0,2), _tr(1,2), _tr(2,2));

	// 좌표계 회전
	glRotated(_angleVer, 1, 0, 0);
	glRotated(_angleHor, 0, 0, 1);
	//glTranslatef(-500, -500, 0);
	glTranslatef(-600, -200, 100);

	m_draw.DrawAxisXYZ(0, 0, 0, 150, 5);

//#if USE_3D_HELICAM
	m_draw.DrawGrid(10, 10, 100, 100, 0, 0, 5, 5, CdPoint3D(0, 0, 0), G_GRID_TEXT, RGB_RED);
//#elif USE_3D_GFV
//	m_draw.DrawGrid(10, 7, 100, 100, 0, 0, 5, 5, CdPoint3D(0, 0, 0), G_GRID_TEXT, RGB_RED);
//#endif

	m_draw.SetColor(RGB_BLUE, 1);



	if (S3DData->m_bValid)
	{
		double yScale;
		double xScale;

		if (!S3DData->m_matDepthMap.empty())
		{
//#if USE_3D_HELICAM == USE
			yScale = 1000 / S3DData->m_matDepthMap.rows;
			xScale = 1000 / S3DData->m_matDepthMap.cols;
//#elif USE_3D_GFV == USE
//			yScale = 686.0 / S3DData->m_matDepthMap.rows;
//			xScale = 1000.0 / S3DData->m_matDepthMap.cols;
//#endif

		}


		int x = 0;
		int y = 0;


		if (m_Model.m_bMeshCreated)
		{

			m_Model.Draw(TEX_LUT);

			//m_draw.DrawAxisXYZ(0, 0, 0, 100, 2);
		}


		if (m_nSelectDrawType == SHAPE::LINE)
		{
			double dStartZ, dEndZ;
			dStartZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000;
			dEndZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000;
			glLineWidth(3);
			m_draw.SetColor(RGB_WHITE, 0.5);
			glBegin(GL_LINES); // filled quad

			if (m_bOnlyResin)
			{
				glVertex3f((m_ptLine[0].x + m_ptPrePoint.x) * xScale, (m_ptLine[0].y + m_ptPrePoint.y) * yScale, 0);
				glVertex3f((m_ptLine[1].x + m_ptPrePoint.x) * xScale, (m_ptLine[1].y + m_ptPrePoint.y) *  yScale, 0);
			}
			else
			{
				glVertex3f((m_ptLine[0].x + m_ptPrePoint.x) * xScale, (m_ptLine[0].y + m_ptPrePoint.y) * yScale, dStartZ);
				glVertex3f((m_ptLine[1].x + m_ptPrePoint.x) * xScale, (m_ptLine[1].y + m_ptPrePoint.y) * yScale, dEndZ);
			}


			glEnd();
		}
		else if (m_nSelectDrawType == SHAPE::RECTANGLE)
		{
			double dDepthZ;
			dDepthZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000;
			glLineWidth(3);
			m_draw.SetColor(RGB_WHITE, 0.5);
			glBegin(GL_LINE_STRIP); // filled quad

			if (m_bOnlyResin)
			{
				glVertex3f((m_ptRect[0].x + m_ptPrePoint.x)*xScale, (m_ptRect[0].y + m_ptPrePoint.y)*yScale, 0);
				glVertex3f((m_ptRect[2].x + m_ptPrePoint.x)*xScale, (m_ptRect[2].y + m_ptPrePoint.y)*yScale, 0);
				glVertex3f((m_ptRect[1].x + m_ptPrePoint.x)*xScale, (m_ptRect[1].y + m_ptPrePoint.y)*yScale, 0);
				glVertex3f((m_ptRect[3].x + m_ptPrePoint.x)*xScale, (m_ptRect[3].y + m_ptPrePoint.y)*yScale, 0);
				glVertex3f((m_ptRect[0].x + m_ptPrePoint.x)*xScale, (m_ptRect[0].y + m_ptPrePoint.y)*yScale, 0);
			}
			else
			{
				glVertex3f((m_ptRect[0].x + m_ptPrePoint.x)*xScale, (m_ptRect[0].y + m_ptPrePoint.y)*yScale, dDepthZ);
				glVertex3f((m_ptRect[2].x + m_ptPrePoint.x)*xScale, (m_ptRect[2].y + m_ptPrePoint.y)*yScale, dDepthZ);
				glVertex3f((m_ptRect[1].x + m_ptPrePoint.x)*xScale, (m_ptRect[1].y + m_ptPrePoint.y)*yScale, dDepthZ);
				glVertex3f((m_ptRect[3].x + m_ptPrePoint.x)*xScale, (m_ptRect[3].y + m_ptPrePoint.y)*yScale, dDepthZ);
				glVertex3f((m_ptRect[0].x + m_ptPrePoint.x)*xScale, (m_ptRect[0].y + m_ptPrePoint.y)*yScale, dDepthZ);
			}
			glEnd();
		}
		else if (m_nSelectDrawType == SHAPE::POLYGON)
		{
			double dDepthZ;
			dDepthZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000;
			glLineWidth(3);
			m_draw.SetColor(RGB_WHITE, 0.5);
			glBegin(GL_LINE_STRIP); // filled quad

			if (m_bOnlyResin)
			{
				for (int i = 0; i < m_nPolygonDrawVertex; i++)
				{
					glVertex3f((m_ptPolygon[i].x + m_ptPrePoint.x)*xScale, (m_ptPolygon[i].y + m_ptPrePoint.y)*yScale, 0);
				}
				glVertex3f((m_ptPolygon[0].x + m_ptPrePoint.x)*xScale, (m_ptPolygon[0].y + m_ptPrePoint.y)*yScale, 0);
			}
			else
			{
				for (int i = 0; i < m_nPolygonDrawVertex; i++)
				{
					glVertex3f((m_ptPolygon[i].x + m_ptPrePoint.x)*xScale, (m_ptPolygon[i].y + m_ptPrePoint.y)*yScale, dDepthZ);
				}
				glVertex3f((m_ptPolygon[0].x + m_ptPrePoint.x)*xScale, (m_ptPolygon[0].y + m_ptPrePoint.y)*yScale, dDepthZ);
			}
			glEnd();
		}
		//else if (CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.size() > 0)
		//{
		//	double dDepthZ;
		//	dDepthZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000;
		//	glLineWidth(3);
		//	m_draw.SetColor(RGB_WHITE, 0.5);
		//	glBegin(GL_LINE_STRIP); // filled quad
		//
		//	if (m_bOnlyResin)
		//	{
		//		for (int i = 0; i < CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.size(); i++)
		//		{
		//			glVertex3f(CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.at(i).x*xScale, CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.at(i).y*yScale, 0);
		//		}
		//	}
		//	else
		//	{
		//		for (int i = 0; i < CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.size(); i++)
		//		{
		//			glVertex3f(CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.at(i).x*xScale, CGvisAORView::m_pAORMasterView->m_cMatching.m_vecThinningPt.at(i).y*yScale, dDepthZ);
		//		}
		//	}
		//	glEnd();
		//}

	}

	glPopMatrix();
	glLineWidth(1);

	if (bLight)
	{
		glDisable(GL_DEPTH_TEST); // Enables Depth Testing
		glDisable(GL_CULL_FACE); // 뒷면에 대해서는 계산하지 말라
		glEnable(GL_LIGHTING); // 빛을 사용한다.

		glDisable(GL_LIGHT0); // 0번빛을 사용한다.

		glDisable(GL_COLOR_MATERIAL);
	}

	return 0;
}

void CDlg3DViewer::Prepare3D()
{
}

void CDlg3DViewer::Display3D()
{
	SSR3DData* S3DData = Get3DData();
	cv::Mat matModelIMG = S3DData->m_matDepthMap.clone();
	cv::Mat dst = m_cMatching.ApplyConvertImageAuto(matModelIMG);
	m_cMatching.GetRealMinMax(m_fMin, m_fMax);
	cv::Mat dst2;
	applyColorMap(dst, dst2, cv::COLORMAP_RAINBOW);
	if (!dst.empty())
	{
		//S3DData->m_AmpMatrix = S3DData->m_AmpMatrix.clone();// 강도 이미지???
		//S3DData->m_matDepthMap = S3DData->m_matDepthMap.clone();//보정 안된 높이맵
		//S3DData->m_matDepthMapColor = S3DData->m_matDepthMapColor.clone();
		S3DData->m_bValid = 1;

		//SendMessage(WM_UPDATE_3D_MODEL, 0, 0);

		m_DefectColor = dst2;

		S3DData->m_matDepthMapColor = m_DefectColor.clone();
		S3DData->m_AmpMatrix = S3DData->m_matDepthMap.clone();


		CRect rectResult;
		CDC* pDCResult;
		m_Pic.GetWindowRect(rectResult);
		cv::resize(dst2, m_Image, cv::Size(rectResult.Width(), rectResult.Height()));
		pDCResult = m_Pic.GetDC();
		if (!m_Image.empty())
		{
			DrawMat(pDCResult->m_hDC, m_Image);
		}
		::ReleaseDC(m_hWnd, pDCResult->m_hDC);

		SendMessage(WM_UPDATE_3D_MODEL, 0, 0);
	}

	//CString strData;
	//strData.Format(_T("%.3f"), m_fMin*1000.0);
	//SetDlgItemText(IDC_EDIT_MIN, strData);
	//strData.Format(_T("%.3f"), m_fMax*1000.0);
	//SetDlgItemText(IDC_EDIT_MAX, strData);

}

void CDlg3DViewer::DrawMat(HDC hDC, cv::Mat& img)
{
	CV_Assert(!img.empty() && hDC != NULL);
	int ws = (img.cols + 3) & ~3;
	DrawMat(hDC, img, 0, 0, ws, img.rows);
}

void CDlg3DViewer::DrawMat(HDC hDC, cv::Mat& img, int x, int y, int dw, int dh)
{
	CV_Assert(!img.empty() && hDC != NULL);

	int bpp = 8 * img.elemSize();
	CV_Assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;
	if (bpp < 32) padding = 4 - (img.cols % 4);
	if (padding == 4) padding = 0;

	if (padding > 0 || img.isContinuous() == false) {
		cv::copyMakeBorder(img, img, 0, 0, 0, padding, cv::BORDER_CONSTANT, 0);
	}

	uchar buffer[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	BITMAPINFO* binfo = (BITMAPINFO*)buffer;

	BITMAPINFOHEADER* bmih = &(binfo->bmiHeader);
	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = img.cols;
	bmih->biHeight = -abs(img.rows);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;

	if (img.channels() == 1) {
		RGBQUAD* palette = binfo->bmiColors;
		for (int i = 0; i < 256; i++) {
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (uchar)i;
			palette[i].rgbReserved = 0;
		}
	}

	if (img.cols == dw && img.rows == dh) {
		::SetDIBitsToDevice(hDC,	// hdc
			x,				// DestX
			y,				// DestY
			img.cols,		// nSrcWidth
			img.rows,		// nSrcHeight
			0,				// SrcX
			0,				// SrcY
			0,				// nStartScan
			img.rows,		// nNumScans
			img.data,		// lpBits
			binfo,			// lpBitsInfo
			DIB_RGB_COLORS);	// wUsage
	}
	else {
		SetStretchBltMode(hDC, COLORONCOLOR);
		::StretchDIBits(hDC,
			x, y, dw, dh,
			0, 0, img.cols, img.rows,
			img.data, binfo, DIB_RGB_COLORS, SRCCOPY);
	}
}


void CDlg3DViewer::Auto3D()
{

}