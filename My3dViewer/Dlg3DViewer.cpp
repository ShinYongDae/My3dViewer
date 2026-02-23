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
	m_nIndexOfRefer = 0;
	for (int i = 0; i < REFER_BUFFER; i++)
	{
		m_pReferenceData[i] = NULL;
	}
	m_fpos_start = 50.00;
	m_fScan_Range = 0.2;
	m_fScan_Ramp = 0.2;
}

CDlg3DViewer::~CDlg3DViewer()
{
	m_pView->MakeCurrent();

	if (this->GetSafeHwnd())
	{
		if (m_pView)
			m_pView->DestroyWindow();
	}

	if (m_pView)
		delete m_pView;

	m_pView = nullptr;

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
}


BEGIN_MESSAGE_MAP(CDlg3DViewer, CDialog)
	ON_MESSAGE(WM_UPDATE_3D_MODEL, OnUpdate3DModel)
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

void CDlg3DViewer::Grab(CString sPath) // "C:\\AORSet\\Data3D\\%d-%d.exr"
{
	std::string ss = (CT2A(sPath));//string 변환
	cv::imwrite(ss, m_matrixZ);

	cv::Scalar scalarAvg;
	scalarAvg = cv::mean(m_matrixZ);
	double  dLastAvg = scalarAvg[0];

	double dLastMax = -9999999;
	double dLastMin = 9999999;
	minMaxLoc(m_matrixZ, &dLastMin, &dLastMax);

	double dAvg = GetDepthAvg(m_matrixZ);
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
	}

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
