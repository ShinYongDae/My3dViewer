// Dlg3DViewer.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "My3dViewer.h"
#include "Dlg3DViewer.h"
#include "afxdialogex.h"
#include "GlobalDefineAOR.h"
#include "My3dViewerDlg.h"
#include "H5Cpp.h"
#include "XceedZipControl.h"
#include "tinyxml2.h"

using namespace H5;

// CDlg3DViewer 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlg3DViewer, CDialog)

CDlg3DViewer::CDlg3DViewer(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_3D, pParent)
{
	m_pParentWnd = pParent;

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
	m_fMax = 0.1;
	m_fMin = -0.1;

	// for OpenGL Rendering
	InitParamRendering();
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
	DDX_Control(pDX, IDC_STATIC_VIEW, m_Pic);
}


BEGIN_MESSAGE_MAP(CDlg3DViewer, CDialog)
	ON_MESSAGE(WM_BUTTON_ZOOM, OnBtnZoom)
	ON_MESSAGE(WM_UPDATE_3D_MODEL, OnUpdate3DModel)
	ON_MESSAGE(WM_USER_RENDER, OnGLRender)
	ON_BN_CLICKED(IDC_CHECK_ZOOM, &CDlg3DViewer::OnBnClickedCheckZoom)
	ON_BN_CLICKED(IDC_CHECK_ZOOMIN, &CDlg3DViewer::OnBnClickedCheckZoomin)
	ON_BN_CLICKED(IDC_CHECK_ZOOMOUT, &CDlg3DViewer::OnBnClickedCheckZoomout)
	ON_BN_CLICKED(IDC_CHECK_FIT, &CDlg3DViewer::OnBnClickedCheckFit)
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

void CDlg3DViewer::InitParamRendering()
{
	m_bOpMode = 0;
	_mouseButton = 0;
	_angleHor = 40.0;
	_angleVer = -36.0;
	_fovAngle = 45.0;
	_transX = 0.0;
	_transY = 0.0;
	_transZ = 0.0;
	_eyePos.x = 0.0;
	_eyePos.y = -4.0;
	_eyePos.z = 0.0;
	_centerPos.x = 0.0;
	_centerPos.y = 0.0;
	_centerPos.z = 0.0;
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

LRESULT CDlg3DViewer::OnBtnZoom(WPARAM wParam, LPARAM lParam)
{
	BOOL bOn = (BOOL)lParam;
	((CButton*)GetDlgItem(IDC_CHECK_ZOOM))->SetCheck(bOn);

	if (bOn)
	{
		m_pView->SetOpMode(OPEN_GL::RECT_ZOOM);
		m_bOpMode = 1;
	}
	else
	{
		m_bOpMode = 0;
		m_pView->SetOpMode(OPEN_GL::NONE);
	}

	return 0;
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
			yScale = 1000.0 / (double)S3DData->m_matDepthMap.rows;
			xScale = 1000.0 / (double)S3DData->m_matDepthMap.cols;
			m_Model.ApplyScaleAndOffset(0.0, 0.0, 0.0, xScale, yScale, 5000.0);
		}
	}

	m_pView->Refresh();
	return 0;
}

SSR3DData* CDlg3DViewer::Get3DData()
{
	return &m_st3D;
}

char* CDlg3DViewer::StringToChar(CString str)
{
	char*		szStr = NULL;
	wchar_t*	wszStr;
	int				nLenth;

	USES_CONVERSION;
	//1. CString to wchar_t* conversion
	wszStr = T2W(str.GetBuffer(str.GetLength()));

	//2. wchar_t* to char* conversion
	nLenth = WideCharToMultiByte(CP_ACP, 0, wszStr, -1, NULL, 0, NULL, NULL); //char* 형에 대한길이를 구함 
	szStr = new char[nLenth];  //메모리 할당 

							   //3. wchar_t* to char* conversion
	WideCharToMultiByte(CP_ACP, 0, wszStr, -1, szStr, nLenth, 0, 0);
	return szStr;
}

BOOL CDlg3DViewer::ExtractInfoXYZ(CString sPath)
{
	CString sLine, sData = _T("");
	CStdioFile stdfile;	// Text로 파일을 ofen. (Data format : char형)
	if (!stdfile.Open(sPath, CFile::modeRead | CFile::shareDenyNone, NULL))
	{
		AfxMessageBox(_T("Fail to load XYZ_File of Zygo."));
		return FALSE;
	}

	RemoveAllZygoXYZ();

	BOOL bExist = TRUE;
	CString str = _T("");
	int nLine = 0, nCol = 0;
	TCHAR seps[] = _T(" ");
	TCHAR *token;
	TCHAR tszStr[MAX_PATH];
	CString sResH, sResV, sTotCols, sTotRows;
	BOOL bPhaseData = FALSE;
	int nColY, nRowX;
	float fMicronZ;
	int nStLinePhaseData = 0, nEdLinePhaseData = 0;
	int nPrevLineColY0 = 0, nLinesColY = 0, nLinesRowX = 0;

	int nSizeCol = 0, nSizeRow = 0;
	int nPixels = 0;

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
				m_matrixZ.at<float>(nRowX, nColY) = _xyz.fZmm; //COPY RAW DATA

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
			else if (nLine == 9)
			{
				StringToTCHAR(str, tszStr);
				token = _tcstok(tszStr, seps); //문자열을 기준에 따라 token에 임시 저장한다.
				while (token != NULL)
				{
					nCol++;
					if (nCol == 1)
					{
						sTotCols.Format(_T("%s"), token);
					}
					else if(nCol == 2)
					{
						sTotRows.Format(_T("%s"), token);

						nSizeRow = _ttoi(sTotRows); nSizeCol = _ttoi(sTotCols);
						m_matrixZ = cv::Mat((uint)nSizeRow, (uint)nSizeCol, CV_32FC1); // ( row, col, 32비트 부동소수점(float) 자료형 )
						m_matrixA = cv::Mat((uint)nSizeRow, (uint)nSizeCol, CV_8UC1);
						nPixels = nSizeRow * nSizeCol;
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
	m_stZygoInfo3D.dWaveLength = _tstof(tszNum) * pow(10, _ttoi(tszExp)) * 1000.0; // [mm]

	nPos = sResV.Find('e', 0);
	sNum = sResV.Left(nPos);
	sExp = sResV.Right(sResV.GetLength() - (nPos + 1));
	StringToTCHAR(sNum, tszNum);
	StringToTCHAR(sExp, tszExp);
	m_stZygoInfo3D.dResolution = _tstof(tszNum) * pow(10, _ttoi(tszExp)) * 1000.0; // [mm]

	m_stZygoInfo3D.nTotalPhaseData = m_stZygoInfo3D.m_arZygoXYZ.GetCount();
	m_stZygoInfo3D.nSizeColY = nLinesColY;
	m_stZygoInfo3D.nSizeRowX = nLinesRowX;

	//uint xSize = nLinesColY;
	//uint ySize = nLinesRowX;
	//m_matrixZ = cv::Mat(ySize, xSize, CV_32FC1); // ( row, col, 32비트 부동소수점(float) 자료형 )
	//m_matrixA = cv::Mat(ySize, xSize, CV_8UC1);
	//
	//int nidx = 0;
	//COPY RAW DATA
	//for (uint i = 0; i < ySize; i++) 
	//{
	//	for (uint j = 0; j < xSize; j++) 
	//	{
	//		stTagZygoXYZ stXYZ = m_stZygoInfo3D.m_arZygoXYZ.GetAt(nidx); // Non scaled data.
	//		m_matrixZ.at<float>(i, j) = stXYZ.fZmm;
	//		//m_matrixA.at<float>(i, j) = stXYZ.fZmm;
	//		nidx++;
	//	}
	//}

	return TRUE;
}

BOOL CDlg3DViewer::ExtractInfoDatx(CString sPath)
{
	CString sLine, sData = _T("");
	CStdioFile stdfile;	// Text로 파일을 ofen. (Data format : char형)
	if (!stdfile.Open(sPath, CFile::modeRead | CFile::shareDenyNone, NULL))
	{
		AfxMessageBox(_T("Fail to load Info."));
		return FALSE;
	}

	RemoveAllZygoXYZ();

	int nSizeCol = 0, nSizeRow = 0;
	double  dLastAvg = 0.0;

	int nPixels = 0;
	double dStdev = 0;
	double dVar = 0;
	float* data_out = nullptr;

	char* filepath = StringToChar(sPath);
	try 
	{
		Exception::dontPrint(); // Disable automatic error printing
		H5File file(filepath, H5F_ACC_RDONLY);

		// Open the "data" group where topography is stored
		Group dataGroup = file.openGroup("/Data/Surface");

		// Find the specific metadata subgroup (usually labeled, often the first)
		hsize_t numObjs = dataGroup.getNumObjs();
		std::string SubgroupName0 = dataGroup.getObjnameByIdx(0);

		// Open the dataset containing the spatial data (often "intensity" or "phase")
		DataSet dataset = dataGroup.openDataSet(SubgroupName0);

		// Get dataspace to understand dimensions
		DataSpace dataspace = dataset.getSpace();
		hsize_t dims[2];
		dataspace.getSimpleExtentDims(dims, NULL);
		//std::cout << "Data Dimensions: " << dims[0] << " x " << dims[1] << std::endl;
		nSizeCol = dims[1]; nSizeRow = dims[0];
		m_matrixZ = cv::Mat(nSizeRow, nSizeCol, CV_32FC1); // ( row, col, 32비트 부동소수점(float) 자료형 )
		m_matrixA = cv::Mat(nSizeRow, nSizeCol, CV_8UC1);
		nPixels = nSizeRow * nSizeCol;

		// 데이터 읽기 (float 배열 등)
		data_out = new float[dims[0] * dims[1]];
		dataset.read(data_out, PredType::NATIVE_FLOAT);

		//// Allocate memory to read data (assuming float/double)
		//std::vector<float> data(dims[0] * dims[1]);
		//// Read data
		//dataset.read(data.data(), PredType::NATIVE_FLOAT);

		// 외부 데이터를 cv::Mat으로 감싸기 (복사 없음)
		cv::Mat mat(dims[0], dims[1], CV_32FC1, data_out);

		// NaN 및 Inf 필터링 방법 1: cv::patchNaNs (NaN만 해결)
		cv::Mat patched = mat.clone();
		cv::patchNaNs(patched, 0.0); // NaN을 0으로 변환
		//std::cout << "patchNaNs 후 (0으로 대체):\n" << patched << std::endl;

		// NaN 및 Inf 필터링 방법 1: cv::patchNaNs (NaN만 해결)
		cv::Mat mask;
		// 절대값이 너무 큰 값(무한대)을 마스킹
		cv::absdiff(patched, cv::Scalar(0), mask);
		cv::compare(mask, 1e10, mask, cv::CMP_GT); // 10^10 보다 크면 무한대로 간주
		// 필터링된 위치에 특정값(예: 0) 대입
		patched.setTo(0, mask);


		// cv::mean() 함수를 사용하여 평균 계산
		// cv::mean은 cv::Scalar(4개 채널까지)를 반환합니다.
		cv::Scalar meanScalar = cv::mean(patched);

		// 결과 출력 (채널이 1개이므로 meanScalar[0]에 평균값이 저장됨)
		double average = meanScalar[0] / (float)1000000.0; // [mm]

		// Open the "data" group where topography is stored
		Group attributeGroup = file.openGroup("/Attributes");

		// Find the specific metadata subgroup (usually labeled, often the first)
		hsize_t numObjs1 = attributeGroup.getNumObjs();
		std::string SubgroupName1 = attributeGroup.getObjnameByIdx(numObjs1 - 1);

		// 속성에서 파장과 해상도를 읽어옴.
		Group attributeSubGroup = attributeGroup.openGroup(SubgroupName1);
		H5::Attribute attr;
		std::string attrName;
		attrName = "Data Context.Data Attributes.Wavelength:Value";
		if (attributeSubGroup.attrExists(attrName))
		{
			attr = attributeSubGroup.openAttribute(attrName);

			// Assuming the attribute is a double
			double wavelength_in;
			attr.read(PredType::NATIVE_DOUBLE, &wavelength_in);
			//std::cout << "Wavelength: " << wavelength_in << " Meters" << std::endl;
			m_stZygoInfo3D.dWaveLength = wavelength_in * 1000.0; // [mm]
		}
		else 
		{
			delete filepath;
			if (nullptr != data_out)
			{
				delete[] data_out;
				data_out = nullptr;
			}
			dataset.close();
			dataGroup.close();
			file.close();

			AfxMessageBox(_T("Attribute : Data Context.Data Attributes.attr.wavelength_in not found."));
			//std::cout << "Attribute " << attrName << " not found." << std::endl;
			return FALSE;
		}

		attrName = "Surface Data Context.Lateral Resolution:Value";
		if (attributeSubGroup.attrExists(attrName))
		{
			attr = attributeSubGroup.openAttribute(attrName);

			// Assuming the attribute is a double
			double lateralResolution;
			attr.read(PredType::NATIVE_DOUBLE, &lateralResolution);
			//std::cout << "Lateral Resolution : " << lateralResolution << " Meters" << std::endl;
			m_stZygoInfo3D.dResolution = lateralResolution * 1000.0; // [mm]
		}
		else 
		{
			delete filepath;
			if (nullptr != data_out)
			{
				delete[] data_out;
				data_out = nullptr;
			}
			dataset.close();
			dataGroup.close();
			file.close();

			AfxMessageBox(_T("Attribute : Data Context.Data Attributes.attr.lateral_res not found."));
			//std::cout << "Attribute " << attrName << " not found." << std::endl;
			return FALSE;
		}


		for (int nRow = 0; nRow < dims[0]; nRow++)
		{
			for (int nCol = 0; nCol < dims[1]; nCol++)
			{
				stTagZygoXYZ _xyz;
				_xyz.nColY = nCol;
				_xyz.nRowX = nRow;
				double dZ = (float)data_out[nRow * dims[1] + nCol] / (float)1000000.0;
				if (dZ > 1000000000.0 || dZ < -1000000000.0)
				{
					if (!nRow)
					{
						if (!nCol)
							dZ = 0.0;
						else
							dZ = m_matrixZ.at<float>(nRow * dims[1] + (nCol - 1));
					}
					else
					{
						if (!nCol)
							dZ = m_matrixZ.at<float>((nRow - 1) * dims[1] + nCol);
						else
							dZ = m_matrixZ.at<float>(nRow * dims[1] + (nCol - 1));
					}
					if (dZ > 1000000000.0 || dZ < -1000000000.0)
						int nStop = 1;
				}
				dVar += (average - dZ)*(average - dZ);

				_xyz.fZmm = dZ;
				m_stZygoInfo3D.m_arZygoXYZ.Add(_xyz);
				m_matrixZ.at<float>(nRow, nCol) = (float)_xyz.fZmm; //COPY RAW DATA
				//if (dLastAvg > 1114.0)
				//	int nStop = 1;
				dLastAvg += _xyz.fZmm;
			}
		}
		dLastAvg /= (double)(dims[0] * dims[1]);
		dStdev = sqrt(dVar / nPixels);
		// Data is now in 'data' vector - process as needed
		//std::cout << "Successfully read data." << std::endl;
		delete filepath;
		if (nullptr != data_out)
		{
			delete[] data_out;
			data_out = nullptr;
		}
		dataset.close();
		dataGroup.close();
		file.close();
	}
	catch (FileIException &error)
	{
		delete filepath;
		if (nullptr != data_out)
		{
			delete[] data_out;
			data_out = nullptr;
		}
		AfxMessageBox(_T("File or Group Exception error of datx file!!!"));
		error.printErrorStack();
		return FALSE;
	}
	catch (DataSetIException &error)
	{
		delete filepath;
		if (nullptr != data_out)
		{
			delete[] data_out;
			data_out = nullptr;
		}
		AfxMessageBox(_T("DataSet Exception error of datx file!!!"));
		error.printErrorStack();
		return FALSE;
	}

	//delete filepath;

	//for (int j = 0; j < m_matrixZ.rows; j++)
	//{
	//	for (int i = 0; i < m_matrixZ.cols; i++)
	//	{
	//		float fColor = m_matrixZ.at<float>(j, i);// 한 픽셀식 검사
	//
	//		if (fabs(fColor - dLastAvg) > dStdev * 3)
	//		{
	//			fColor = dLastAvg;
	//		}
	//		m_matrixZ.at<float>(j, i) = fColor;
	//	}
	//}


	m_stZygoInfo3D.nTotalPhaseData = m_stZygoInfo3D.m_arZygoXYZ.GetCount();
	m_stZygoInfo3D.nSizeColY = nSizeCol;
	m_stZygoInfo3D.nSizeRowX = nSizeRow;

	double dLastMax = -9999999;
	double dLastMin = 9999999;
	minMaxLoc(m_matrixZ, &dLastMin, &dLastMax); // memory leak

	SSR3DData *S3DData = Get3DData();
	S3DData->m_dAvg = dLastAvg;
	S3DData->m_dMax = dLastMax;
	S3DData->m_dMin = dLastMin;
	S3DData->m_dStdev = dStdev;

	//sData.Format(_T("%f"), dLastAvg);
	return TRUE;;
}

void CDlg3DViewer::RemoveAllZygoXYZ()
{
	int nTotal = m_stZygoInfo3D.m_arZygoXYZ.GetCount();
	if (nTotal > 0)
	{
		m_stZygoInfo3D.m_arZygoXYZ.RemoveAll();
	}
}

BOOL CDlg3DViewer::IsFileDatx(CString sPath)
{
	int nPos, nLine = 0;
	CString sFileName, sFile, sType, sTemp;

	CFileFind cFile;
	BOOL bExist = cFile.FindFile(sPath);
	if (!bExist) return FALSE; // 파일이 존재하지 않음.

	nPos = sPath.ReverseFind('.');
	if (nPos > 0)
	{
		sFileName = sPath.Left(nPos);
		sTemp = sPath.Right(sPath.GetLength() - nPos - 1);
		sType = sTemp.MakeLower();
		if (sType == _T("datx"))
			return TRUE;
	}

	return FALSE;
}

BOOL CDlg3DViewer::IsFileXYZ(CString sPath)
{
	int nPos, nLine = 0;
	CString sFileName, sType, sTemp;

	CFileFind cFile;
	BOOL bExist = cFile.FindFile(sPath);
	if (!bExist) return FALSE; // 파일이 존재하지 않음.

	// 파일명을 얻음.
	nPos = sPath.ReverseFind('.');
	if (nPos > 0)
	{
		sFileName = sPath.Left(nPos);
		sTemp = sPath.Right(sPath.GetLength() - nPos - 1);
		sType = sTemp.MakeLower();
		if (sType == _T("xyz"))
			return TRUE;
	}

	return FALSE;
}

BOOL CDlg3DViewer::Grab(CString sPath) // "C:\\AORSet\\Data3D\\%d-%d.exr"
{
	DWORD dwStartTick = GetTickCount();
	BOOL bPrevFitSuccess = m_bFitSuccess;
	m_bFitSuccess = FALSE;

	//cv::setNumThreads(0);
	//vec.clear(); // 더 이상 필요 없으면,
	if (!Prepare3D(sPath))
	{
		m_bFitSuccess = bPrevFitSuccess;
		return FALSE;
	}
	Display3D();
	((CMy3dViewerDlg*)m_pParentWnd)->SetMinMax(m_fMin, m_fMax);
	Auto3D();

	CString str;
	DWORD nElapsed = GetTickCount() - dwStartTick;
	str.Format(_T("%d"), nElapsed);
	GetDlgItem(IDC_EDIT_LOADING_TIME)->SetWindowText(str);
	return TRUE;
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
				double radianX = _angleHor * PI / 180.0; // 도를 라디안으로 변환
				double radianY = (90.0 - _angleHor) * PI / 180.0; // 도를 라디안으로 변환
				double dDiffX = (m_pView->m_ptCurPos.x - _mouseDownPoint.x) * cos(radianX); // + (m_pView->m_ptCurPos.y - _mouseDownPoint.y) * sin(radianY);
				double dDiffY = (m_pView->m_ptCurPos.y - _mouseDownPoint.y) * cos(radianY) - (m_pView->m_ptCurPos.x - _mouseDownPoint.x) * sin(radianX);
				double dDiffZ = m_pView->m_ptCurPos.y - _mouseDownPoint.y;
				//if (dDiffX > 5.0 || dDiffX < -5.0)
				//{
					_transX += dDiffX;
				//}
				//else if (dDiffY > 5.0 || dDiffY < -5.0)
				//{
					_transY += dDiffY;
				//}
				//else if (dDiffZ > 5.0 || dDiffZ < -5.0)
				//{
					_transZ -= dDiffZ;
				//}
				//_centerPos.x -= (m_pView->m_ptCurPos.x - _mouseDownPoint.x) / 100.;
				//_centerPos.z += (m_pView->m_ptCurPos.y - _mouseDownPoint.y) / 100.;

				//_centerPos.y += (m_pView->m_ptCurPos.y - _mouseDownPoint.y) / 100.;

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
	//glTranslatef(-600, -200, 100);
	glTranslatef(-600 + _transX, -350 + _transY, 100 + _transZ);

	m_draw.DrawAxisXYZ(0, 0, 0, 150, 5);

//#if USE_3D_HELICAM
	m_draw.DrawGrid(10, 10, 100, 100, 0, 0, 5, 5, CdPoint3D(0, 0, 0), G_GRID_TEXT, RGB_YELLOW);
	//m_draw.DrawGrid(10, 10, 100, 100, 0, 0, 5, 5, CdPoint3D(0, 0, 0), G_GRID_TEXT, RGB_RED);
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
			yScale = 1000.0 / (double)S3DData->m_matDepthMap.rows;
			xScale = 1000.0 / (double)S3DData->m_matDepthMap.cols;
//#elif USE_3D_GFV == USE
//			yScale = 686.0 / (double)S3DData->m_matDepthMap.rows;
//			xScale = 1000.0 / (double)S3DData->m_matDepthMap.cols;
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
			dStartZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000.0;
			dEndZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000.0;
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
			dDepthZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000.0;
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
			dDepthZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000.0;
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
		//	dDepthZ = (S3DData->m_dMax - S3DData->m_dMin) * 5000.0;
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

BOOL CDlg3DViewer::Prepare3D(CString sPath)
{
	CString sData = _T("");
	cv::Scalar scalarAvg;
	double  dLastAvg = 0.0;
	int i, j;

	if (IsFileDatx(sPath))
	{
		if (!ExtractInfoDatx(sPath))
			return FALSE;
		dLastAvg = _tstof(sData);
	}
	else if (IsFileXYZ(sPath))
	{
		if (!ExtractInfoXYZ(sPath))
			return FALSE;
		scalarAvg = cv::mean(m_matrixZ); // memory leak
		dLastAvg = scalarAvg[0];
	}
	else
	{
		AfxMessageBox(_T("Doesn't supported file!!!"));
		return FALSE;
	}

	SSR3DData *S3DData = Get3DData();

	if (IsFileXYZ(sPath))
	{
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

		for (j = 0; j < m_matrixZ.rows; j++)
		{
			for (i = 0; i < m_matrixZ.cols; i++)
			{
				float fColor = m_matrixZ.at<float>(j, i);// 한 픽셀식 검사 

				if (fabs(fColor - dAvg) > dStdev * 3)
				{
					fColor = dAvg;
				}
				m_matrixZ.at<float>(j, i) = fColor;
			}
		}

		S3DData->m_dAvg = dLastAvg;
		S3DData->m_dMax = dLastMax;
		S3DData->m_dMin = dLastMin;
		S3DData->m_dStdev = dStdev;
	}

	S3DData->m_nSizeX = m_matrixZ.cols;
	S3DData->m_nSizeY = m_matrixZ.rows;
	S3DData->m_matDepthMap = m_matrixZ.clone();

	S3DData->m_matFlu = m_matrixA.clone();
	S3DData->m_matAllDefect = m_matrixA.clone();
	S3DData->m_matRefCD = m_matrixA.clone();
	S3DData->m_matRefImg = m_matrixA.clone();

	//S3DData->m_dAvg = dLastAvg;
	//S3DData->m_dMax = dLastMax;
	//S3DData->m_dMin = dLastMin;
	//S3DData->m_dStdev = dStdev;
	S3DData->m_dScanStart = m_fpos_start;
	S3DData->m_dScanEnd = m_fpos_end;
	S3DData->m_dTgu = m_fpos_tgu;
	S3DData->m_dTgd = m_fpos_tgd;
	S3DData->m_dRamp = m_fScan_Ramp;
	S3DData->m_dRange = m_fScan_Range;
	S3DData->m_dXResolution = m_stZygoInfo3D.dResolution;
	S3DData->m_dYResolution = m_stZygoInfo3D.dResolution;
	//S3DData->m_dXResolution = _3D_RESOLUTION;
	//S3DData->m_dYResolution = _3D_RESOLUTION;
	S3DData->m_bValid = 1;
	m_draw.SetResolution(m_stZygoInfo3D.dResolution * 1000.0, m_stZygoInfo3D.dResolution * 1000.0); // [um/pixel]

	return TRUE;
}

void CDlg3DViewer::Display3D()
{
	SSR3DData* S3DData = Get3DData();
	cv::Mat matModelIMG = S3DData->m_matDepthMap.clone();
	cv::Mat dst = m_cMatching.ApplyConvertImageAuto(matModelIMG);
	//m_cMatching.GetAverage(m_fMin, m_fMax);
	m_cMatching.GetMinMax(m_fMin, m_fMax);
	//m_cMatching.GetRealMinMax(m_fMin, m_fMax);
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

void CDlg3DViewer::Display3D(float fMin, float fMax)
{
	SSR3DData* S3DData = Get3DData();
	cv::Mat matModelIMG = S3DData->m_matDepthMap.clone();
	cv::Mat dst = m_cMatching.ApplyConvertImage(matModelIMG, fMin, fMax);
	cv::Mat dst2;
	applyColorMap(dst, dst2, cv::COLORMAP_RAINBOW);
	if (!dst.empty())
	{
		S3DData->m_bValid = 1;
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

void CDlg3DViewer::SetParentWnd(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

void CDlg3DViewer::GetMinMax(float& fMin, float& fMax)
{
	fMin = m_fMin;
	fMax = m_fMax;
}

void CDlg3DViewer::SetMinMax(float fMin, float fMax)
{
	m_fMin = fMin;
	m_fMax = fMax;
}

void CDlg3DViewer::AdjustRange(float fMin, float fMax)
{
	SetMinMax(fMin, fMax);
	Display3D(fMin, fMax);
}

void CDlg3DViewer::OnBnClickedCheckZoom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_ZOOM))->GetCheck();

	if (bCheck)
	{
		m_pView->SetOpMode(OPEN_GL::RECT_ZOOM);
		m_bOpMode = 1;
	}
	else
	{
		m_bOpMode = 0;
		m_pView->SetOpMode(OPEN_GL::NONE);
	}
}

void CDlg3DViewer::OnBnClickedCheckZoomin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_CHECK_ZOOM))->SetCheck(0);
	m_pView->ZoomIn(2);
	((CButton*)GetDlgItem(IDC_CHECK_ZOOMIN))->SetCheck(0);
}


void CDlg3DViewer::OnBnClickedCheckZoomout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_CHECK_ZOOM))->SetCheck(0);
	m_pView->ZoomOut(2);
	((CButton*)GetDlgItem(IDC_CHECK_ZOOMOUT))->SetCheck(0);
}


void CDlg3DViewer::OnBnClickedCheckFit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_CHECK_ZOOM))->SetCheck(FALSE);
	m_pView->SetOpMode(OPEN_GL::NONE);
	InitParamRendering();
	m_pView->FitToScreen();
	((CButton*)GetDlgItem(IDC_CHECK_FIT))->SetCheck(0);
}


void CDlg3DViewer::SaveXMLCompress3D(CString strPath)
{
	SSR3DData* S3DData = Get3DData();
	S3DData->m_bLoadManual3D = TRUE;

	if (!S3DData->m_bLoadManual3D)
	{
		if (!S3DData->m_matDepthMap.empty() && !S3DData->m_matFlu.empty() && !S3DData->m_matAllDefect.empty() && !S3DData->m_matRefCD.empty() && !S3DData->m_matRefImg.empty())
		{

			CXceedZipControl XceedZipControl;
			CString strData;
			CTime currentTime = CTime::GetCurrentTime();
			char *pText;
			tinyxml2::XMLDocument doc;
			tinyxml2::XMLDeclaration *decl = doc.NewDeclaration();
			doc.LinkEndChild(decl);

			tinyxml2::XMLElement *root = doc.NewElement("root");
			doc.LinkEndChild(root);

			tinyxml2::XMLElement *xmlTime = doc.NewElement("Time");
			strData.Format(_T("%04d/%d/%d %02d:%02d:%02d"), currentTime.GetYear(), currentTime.GetMonth(),
				currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(),
				currentTime.GetSecond());
			pText = StringToChar(strData);
			xmlTime->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlTime);

			tinyxml2::XMLElement *xmlVision = doc.NewElement("Version");
			strData.Format(_T("5"));
			pText = StringToChar(strData);
			xmlVision->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlVision);

			tinyxml2::XMLElement *xmlManual = doc.NewElement("Manual");
			strData.Format(_T("%d"), S3DData->m_bLoadManual3D);
			pText = StringToChar(strData);
			xmlManual->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlManual);

			tinyxml2::XMLElement *xmlSizeX = doc.NewElement("SizeX");
			strData.Format(_T("%d"), S3DData->m_nSizeX);
			pText = StringToChar(strData);
			xmlSizeX->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlSizeX);

			tinyxml2::XMLElement *xmlSizeY = doc.NewElement("SizeY");
			strData.Format(_T("%d"), S3DData->m_nSizeY);
			pText = StringToChar(strData);
			xmlSizeY->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlSizeY);

			tinyxml2::XMLElement *xmlResolutionX = doc.NewElement("XResolution");
			strData.Format(_T("%f"), S3DData->m_dXResolution);
			pText = StringToChar(strData);
			xmlResolutionX->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlResolutionX);

			tinyxml2::XMLElement *xmlResolutionY = doc.NewElement("YResolution");
			strData.Format(_T("%f"), S3DData->m_dYResolution);
			pText = StringToChar(strData);
			xmlResolutionY->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlResolutionY);

			tinyxml2::XMLElement *xmlMax = doc.NewElement("Max");
			strData.Format(_T("%f"), S3DData->m_dMax);
			pText = StringToChar(strData);
			xmlMax->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMax);

			tinyxml2::XMLElement *xmlMin = doc.NewElement("Min");
			strData.Format(_T("%f"), S3DData->m_dMin);
			pText = StringToChar(strData);
			xmlMin->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMin);

			tinyxml2::XMLElement *xmlAvg = doc.NewElement("Avg");
			strData.Format(_T("%f"), S3DData->m_dAvg);
			pText = StringToChar(strData);
			xmlAvg->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlAvg);

			tinyxml2::XMLElement *xmlStdev = doc.NewElement("Stdev");
			strData.Format(_T("%f"), S3DData->m_dStdev);
			pText = StringToChar(strData);
			xmlStdev->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlStdev);

			tinyxml2::XMLElement *xmlScanStart = doc.NewElement("ScanStart");
			strData.Format(_T("%f"), S3DData->m_dScanStart);
			pText = StringToChar(strData);
			xmlScanStart->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlScanStart);

			tinyxml2::XMLElement *xmlScanEnd = doc.NewElement("ScanEnd");
			strData.Format(_T("%f"), S3DData->m_dScanEnd);
			pText = StringToChar(strData);
			xmlScanEnd->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlScanEnd);

			tinyxml2::XMLElement *xmlTgu = doc.NewElement("Tgu");
			strData.Format(_T("%f"), S3DData->m_dTgu);
			pText = StringToChar(strData);
			xmlTgu->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlTgu);

			tinyxml2::XMLElement *xmlTgd = doc.NewElement("Tgd");
			strData.Format(_T("%f"), S3DData->m_dTgd);
			pText = StringToChar(strData);
			xmlTgd->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlTgd);

			tinyxml2::XMLElement *xmlRange = doc.NewElement("Range");
			strData.Format(_T("%f"), S3DData->m_dRange);
			pText = StringToChar(strData);
			xmlRange->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlRange);

			tinyxml2::XMLElement *xmlRamp = doc.NewElement("Ramp");
			strData.Format(_T("%f"), S3DData->m_dRamp);
			pText = StringToChar(strData);
			xmlRamp->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlRamp);

			tinyxml2::XMLElement *xmlMatchingPTX = doc.NewElement("MatchingPTX");
			strData.Format(_T("%f"), S3DData->m_dMatchingPTX);
			pText = StringToChar(strData);
			xmlMatchingPTX->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMatchingPTX);

			tinyxml2::XMLElement *xmlMatchingPTY = doc.NewElement("MatchingPTY");
			strData.Format(_T("%f"), S3DData->m_dMatchingPTY);
			pText = StringToChar(strData);
			xmlMatchingPTY->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMatchingPTY);


			tinyxml2::XMLElement *xmlMatchingScale = doc.NewElement("MatchingScale");
			strData.Format(_T("%f"), S3DData->m_dMatchingScale);
			pText = StringToChar(strData);
			xmlMatchingScale->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMatchingScale);

			tinyxml2::XMLElement *xmlMatchingTheta = doc.NewElement("MatchingTheta");
			strData.Format(_T("%f"), S3DData->m_dMatchingTheta);
			pText = StringToChar(strData);
			xmlMatchingTheta->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMatchingTheta);

			tinyxml2::XMLElement *xmlMatchingErode = doc.NewElement("MatchingErode");
			strData.Format(_T("%f"), S3DData->m_dMatchingErode);
			pText = StringToChar(strData);
			xmlMatchingErode->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlMatchingErode);

			tinyxml2::XMLElement *xmlDepthMap = doc.NewElement("DepthMap");
			strData = XceedZipControl.ImgCompressToCString(S3DData->m_matDepthMap, FALSE);
			pText = StringToChar(strData);
			xmlDepthMap->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlDepthMap);

			tinyxml2::XMLElement *xmlFlu = doc.NewElement("Flu");
			strData = XceedZipControl.ImgCompressToCString(S3DData->m_matFlu, TRUE);
			pText = StringToChar(strData);
			xmlFlu->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlFlu);

			tinyxml2::XMLElement *xmlAllDefect = doc.NewElement("AllDefect");
			strData = XceedZipControl.ImgCompressToCString(S3DData->m_matAllDefect, TRUE);
			pText = StringToChar(strData);
			xmlAllDefect->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlAllDefect);

			tinyxml2::XMLElement *xmlRefCD = doc.NewElement("RefCD");
			strData = XceedZipControl.ImgCompressToCString(S3DData->m_matRefCD, TRUE);
			pText = StringToChar(strData);
			xmlRefCD->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlRefCD);

			tinyxml2::XMLElement *xmlRefImg = doc.NewElement("RefImg");
			strData = XceedZipControl.ImgCompressToCString(S3DData->m_matRefImg, TRUE);
			pText = StringToChar(strData);
			xmlRefImg->LinkEndChild(doc.NewText(pText));
			delete pText;
			pText = NULL;
			root->LinkEndChild(xmlRefImg);

			pText = StringToChar(strPath);
			doc.SaveFile(pText);
			delete pText;
			pText = NULL;
		}
	}
	else
	{
		CXceedZipControl XceedZipControl;
		CString strData;
		CTime currentTime = CTime::GetCurrentTime();
		char *pText;
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLDeclaration *decl = doc.NewDeclaration();
		doc.LinkEndChild(decl);

		tinyxml2::XMLElement *root = doc.NewElement("root");
		doc.LinkEndChild(root);

		tinyxml2::XMLElement *xmlTime = doc.NewElement("Time");
		strData.Format(_T("%04d/%d/%d %02d:%02d:%02d"), currentTime.GetYear(), currentTime.GetMonth(),
			currentTime.GetDay(), currentTime.GetHour(), currentTime.GetMinute(),
			currentTime.GetSecond());
		pText = StringToChar(strData);
		xmlTime->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlTime);

		tinyxml2::XMLElement *xmlVision = doc.NewElement("Version");
		strData.Format(_T("5"));
		pText = StringToChar(strData);
		xmlVision->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlVision);

		tinyxml2::XMLElement *xmlManual = doc.NewElement("Manual");
		strData.Format(_T("%d"), S3DData->m_bLoadManual3D);
		pText = StringToChar(strData);
		xmlManual->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlManual);

		tinyxml2::XMLElement *xmlSizeX = doc.NewElement("SizeX");
		strData.Format(_T("%d"), S3DData->m_nSizeX);
		pText = StringToChar(strData);
		xmlSizeX->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlSizeX);

		tinyxml2::XMLElement *xmlSizeY = doc.NewElement("SizeY");
		strData.Format(_T("%d"), S3DData->m_nSizeY);
		pText = StringToChar(strData);
		xmlSizeY->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlSizeY);

		tinyxml2::XMLElement *xmlResolutionX = doc.NewElement("XResolution");
		strData.Format(_T("%f"), S3DData->m_dXResolution);
		pText = StringToChar(strData);
		xmlResolutionX->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlResolutionX);

		tinyxml2::XMLElement *xmlResolutionY = doc.NewElement("YResolution");
		strData.Format(_T("%f"), S3DData->m_dYResolution);
		pText = StringToChar(strData);
		xmlResolutionY->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlResolutionY);

		tinyxml2::XMLElement *xmlMax = doc.NewElement("Max");
		strData.Format(_T("%f"), S3DData->m_dMax);
		pText = StringToChar(strData);
		xmlMax->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMax);

		tinyxml2::XMLElement *xmlMin = doc.NewElement("Min");
		strData.Format(_T("%f"), S3DData->m_dMin);
		pText = StringToChar(strData);
		xmlMin->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMin);

		tinyxml2::XMLElement *xmlAvg = doc.NewElement("Avg");
		strData.Format(_T("%f"), S3DData->m_dAvg);
		pText = StringToChar(strData);
		xmlAvg->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlAvg);

		tinyxml2::XMLElement *xmlStdev = doc.NewElement("Stdev");
		strData.Format(_T("%f"), S3DData->m_dStdev);
		pText = StringToChar(strData);
		xmlStdev->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlStdev);

		tinyxml2::XMLElement *xmlScanStart = doc.NewElement("ScanStart");
		strData.Format(_T("%f"), S3DData->m_dScanStart);
		pText = StringToChar(strData);
		xmlScanStart->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlScanStart);

		tinyxml2::XMLElement *xmlScanEnd = doc.NewElement("ScanEnd");
		strData.Format(_T("%f"), S3DData->m_dScanEnd);
		pText = StringToChar(strData);
		xmlScanEnd->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlScanEnd);

		tinyxml2::XMLElement *xmlTgu = doc.NewElement("Tgu");
		strData.Format(_T("%f"), S3DData->m_dTgu);
		pText = StringToChar(strData);
		xmlTgu->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlTgu);

		tinyxml2::XMLElement *xmlTgd = doc.NewElement("Tgd");
		strData.Format(_T("%f"), S3DData->m_dTgd);
		pText = StringToChar(strData);
		xmlTgd->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlTgd);

		tinyxml2::XMLElement *xmlRange = doc.NewElement("Range");
		strData.Format(_T("%f"), S3DData->m_dRange);
		pText = StringToChar(strData);
		xmlRange->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlRange);

		tinyxml2::XMLElement *xmlRamp = doc.NewElement("Ramp");
		strData.Format(_T("%f"), S3DData->m_dRamp);
		pText = StringToChar(strData);
		xmlRamp->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlRamp);

		tinyxml2::XMLElement *xmlMatchingPTX = doc.NewElement("MatchingPTX");
		strData.Format(_T("%f"), S3DData->m_dMatchingPTX);
		pText = StringToChar(strData);
		xmlMatchingPTX->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMatchingPTX);

		tinyxml2::XMLElement *xmlMatchingPTY = doc.NewElement("MatchingPTY");
		strData.Format(_T("%f"), S3DData->m_dMatchingPTY);
		pText = StringToChar(strData);
		xmlMatchingPTY->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMatchingPTY);


		tinyxml2::XMLElement *xmlMatchingScale = doc.NewElement("MatchingScale");
		strData.Format(_T("%f"), S3DData->m_dMatchingScale);
		pText = StringToChar(strData);
		xmlMatchingScale->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMatchingScale);

		tinyxml2::XMLElement *xmlMatchingTheta = doc.NewElement("MatchingTheta");
		strData.Format(_T("%f"), S3DData->m_dMatchingTheta);
		pText = StringToChar(strData);
		xmlMatchingTheta->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMatchingTheta);

		tinyxml2::XMLElement *xmlMatchingErode = doc.NewElement("MatchingErode");
		strData.Format(_T("%f"), S3DData->m_dMatchingErode);
		pText = StringToChar(strData);
		xmlMatchingErode->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlMatchingErode);

		tinyxml2::XMLElement *xmlDepthMap = doc.NewElement("DepthMap");
		strData = XceedZipControl.ImgCompressToCString(S3DData->m_matDepthMap, FALSE);
		pText = StringToChar(strData);
		xmlDepthMap->LinkEndChild(doc.NewText(pText));
		delete pText;
		pText = NULL;
		root->LinkEndChild(xmlDepthMap);

		pText = StringToChar(strPath);
		doc.SaveFile(pText);
		delete pText;
		pText = NULL;
	}
}

BOOL CDlg3DViewer::LoadXMLCompress3D(CString strPath)
{
	SSR3DData* S3DData = Get3DData();
	S3DData->m_bLoadManual3D = TRUE;

	CXceedZipControl XceedZipControl;
	CString strElement, strAttrValue, strElementValue, strAttr, strTime;
	tinyxml2::XMLDocument XMLDoc;
	tinyxml2::XMLElement *pRootElement, *pSubElement;
	const tinyxml2::XMLAttribute *pAttr;
	char *pText;


	S3DData->m_bValid = 0;

	XMLDoc.LoadFile((CStringA)strPath);
	pRootElement = XMLDoc.RootElement();
	pSubElement = pRootElement->FirstChildElement()->ToElement();
	while (pSubElement)
	{
		pText = (char*)pSubElement->Value();
		strElement.Empty();
		if (pText)
		{
			strElement = CharToString(pText);
		}
		pAttr = pSubElement->FirstAttribute();
		while (pAttr)
		{
			pText = (char*)pAttr->Name();
			strAttr.Empty();
			if (pText)
			{
				strAttr = CharToString(pText);
			}
			pText = (char*)pAttr->Value();
			strAttrValue.Empty();
			if (pText)
			{
				strAttrValue = CharToString(pText);
			}
			pAttr = pAttr->Next();
		}
		pText = (char*)pSubElement->GetText();
		strElementValue.Empty();
		if (pText)
		{
			strElementValue = CharToString(pText);
		}
		if (strElement.CompareNoCase(_T("Time")) == 0)
		{
			//strTime = CharToString(pText);
		}
		if (strElement.CompareNoCase(_T("Version")) == 0)
		{
			S3DData->m_nVersion = _ttoi(CharToString(pText));
		}
		if (S3DData->m_nVersion > 3)
		{
			if (strElement.CompareNoCase(_T("Manual")) == 0)
			{
				S3DData->m_bLoadManual3D = _ttoi(CharToString(pText));
			}
		}
		if (strElement.CompareNoCase(_T("SizeX")) == 0)
		{
			S3DData->m_nSizeX = _ttoi(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("SizeY")) == 0)
		{
			S3DData->m_nSizeY = _ttoi(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("XResolution")) == 0)
		{
			S3DData->m_dXResolution = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("YResolution")) == 0)
		{
			S3DData->m_dYResolution = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Max")) == 0)
		{
			S3DData->m_dMax = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Min")) == 0)
		{
			S3DData->m_dMin = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Avg")) == 0)
		{
			S3DData->m_dAvg = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Stdev")) == 0)
		{
			S3DData->m_dStdev = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("ScanStart")) == 0)
		{
			S3DData->m_dScanStart = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("ScanEnd")) == 0)
		{
			S3DData->m_dScanEnd = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Tgu")) == 0)
		{
			S3DData->m_dTgu = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Tgd")) == 0)
		{
			S3DData->m_dTgd = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Range")) == 0)
		{
			S3DData->m_dRange = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("Ramp")) == 0)
		{
			S3DData->m_dRamp = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("MatchingPTX")) == 0)
		{
			S3DData->m_dMatchingPTX = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("MatchingPTY")) == 0)
		{
			S3DData->m_dMatchingPTY = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("MatchingScale")) == 0)
		{
			S3DData->m_dMatchingScale = _ttof(CharToString(pText));
		}
		if (strElement.CompareNoCase(_T("MatchingTheta")) == 0)
		{
			S3DData->m_dMatchingTheta = _ttof(CharToString(pText));
		}
		if (S3DData->m_nVersion > 1)
		{
			if (strElement.CompareNoCase(_T("MatchingErode")) == 0)
			{
				S3DData->m_dMatchingErode = _ttof(CharToString(pText));
			}
		}
		if (S3DData->m_nVersion > 2)
		{
			if (strElement.CompareNoCase(_T("DepthMap")) == 0)
			{
				//S3DData->m_matDepthMap = XceedZipControl.ImgUnCompressToMat(pText, MAX_3D_HEIGHT_SIZE, MAX_3D_WIDTH_SIZE, FALSE);
				S3DData->m_matDepthMap = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, FALSE);
				m_matrixZ = S3DData->m_matDepthMap.clone();
			}
			if (S3DData->m_nVersion > 3)
			{
				if (!S3DData->m_bLoadManual3D)
				{
					if (strElement.CompareNoCase(_T("Flu")) == 0)
					{
						S3DData->m_matFlu = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
						//S3DData->m_matFlu = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
					}
					if (strElement.CompareNoCase(_T("AllDefect")) == 0)
					{
						S3DData->m_matAllDefect = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
						//S3DData->m_matAllDefect = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
					}
					if (strElement.CompareNoCase(_T("RefCD")) == 0)
					{
						S3DData->m_matRefCD = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
						//S3DData->m_matRefCD = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
					}
					if (strElement.CompareNoCase(_T("RefImg")) == 0)
					{
						S3DData->m_matRefImg = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
						//S3DData->m_matRefImg = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
					}
				}
			}
			else
			{
				if (strElement.CompareNoCase(_T("Flu")) == 0)
				{
					S3DData->m_matFlu = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
					//S3DData->m_matFlu = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
				}
				if (strElement.CompareNoCase(_T("AllDefect")) == 0)
				{
					S3DData->m_matAllDefect = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
					//S3DData->m_matAllDefect = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
				}
				if (strElement.CompareNoCase(_T("RefCD")) == 0)
				{
					S3DData->m_matRefCD = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
					//S3DData->m_matRefCD = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
				}
				if (strElement.CompareNoCase(_T("RefImg")) == 0)
				{
					S3DData->m_matRefImg = XceedZipControl.ImgUnCompressToMat(pText, S3DData->m_nSizeY, S3DData->m_nSizeX, TRUE);
					//S3DData->m_matRefImg = XceedZipControl.ImgUnCompressToMat(pText, MAX_JAI_HEIGHT_SIZE, MAX_JAI_WIDTH_SIZE, TRUE);
				}
			}
		}
		pSubElement = pSubElement->NextSiblingElement();
	}
	if (S3DData->m_nVersion < 4)
	{
		S3DData->m_bLoadManual3D = FALSE;
	}
	if (S3DData->m_nVersion < 3)
	{
		std::string ss = (CT2A(strPath));
		cv::FileStorage XMLFileRead(ss, cv::FileStorage::READ);
		XMLFileRead["DepthMap"] >> S3DData->m_matDepthMap;
		XMLFileRead["Flu"] >> S3DData->m_matFlu;
		XMLFileRead["AllDefect"] >> S3DData->m_matAllDefect;
		XMLFileRead["RefCD"] >> S3DData->m_matRefCD;
		XMLFileRead["RefImg"] >> S3DData->m_matRefImg;
		XMLFileRead.release();
	}

	LoadAndSet(strPath);
	return TRUE;
}

BOOL CDlg3DViewer::Load3DFile(CString strPath)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SSR3DData *S3DData = Get3DData();
	CString str3DLog;
	char*szPath = (char*)StringToChar(strPath);
	BOOL bLoadSuccess = FALSE;
	CFile file;

	double dReadMotionX, dReadMotionY;
	int nManualMeas;
	if (file.Open(strPath, CFile::modeRead))
	{
		int nReadSize = 0;
		file.Read(&S3DData->m_nVersion, sizeof(int));
		nReadSize += sizeof(int);
		file.Read(&S3DData->m_nSizeX, sizeof(int));
		nReadSize += sizeof(int);

		file.Read(&S3DData->m_nSizeY, sizeof(int));
		nReadSize += sizeof(int);

		file.Read(&S3DData->m_dXResolution, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dYResolution, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dMax, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dMin, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dAvg, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dStdev, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dScanStart, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dScanEnd, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dTgu, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dTgd, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dRange, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dRamp, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dMatchingPTX, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dMatchingPTY, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dMatchingScale, sizeof(double));
		nReadSize += sizeof(double);

		file.Read(&S3DData->m_dMatchingTheta, sizeof(double));
		nReadSize += sizeof(double);

		if (S3DData->m_nVersion > 1)
		{
			file.Read(&S3DData->m_dMatchingErode, sizeof(double));
			nReadSize += sizeof(double);
		}


		int nGuardByte = 1024 - nReadSize;

		if (nGuardByte > 0)
		{
			int *pDummy = new int[nGuardByte];
			memset(pDummy, 0, sizeof(int) * nGuardByte);
			file.Read(pDummy, sizeof(int)*nGuardByte);
			delete[] pDummy;
		}
		int nRows = 0, nCols = 0;

		if (!S3DData->m_matDepthMap.empty())
		{
			S3DData->m_matDepthMap.release();
		}

		if (!S3DData->m_matFlu.empty())
		{
			S3DData->m_matFlu.release();
		}

		if (!S3DData->m_matAllDefect.empty())
		{
			S3DData->m_matAllDefect.release();
		}

		if (!S3DData->m_matRefCD.empty())
		{
			S3DData->m_matRefCD.release();
		}

		if (!S3DData->m_matRefImg.empty())
		{
			S3DData->m_matRefImg.release();
		}

		file.Read(&nCols, sizeof(int));
		file.Read(&nRows, sizeof(int));

		S3DData->m_matDepthMap = cv::Mat(nRows, nCols, CV_32FC1);
		S3DData->m_matDepthMap.setTo(0);

		int i = 0;
		for (i = 0; i < S3DData->m_matDepthMap.rows; i++)
		{
			float* ptr = S3DData->m_matDepthMap.ptr<float>(i);
			file.Read(ptr, sizeof(float)* S3DData->m_matDepthMap.cols);
		}

		file.Read(&nCols, sizeof(int));
		file.Read(&nRows, sizeof(int));

		S3DData->m_matFlu = cv::Mat(nRows, nCols, CV_8UC1);
		S3DData->m_matFlu.setTo(0);
		for (i = 0; i < S3DData->m_matFlu.rows; i++)
		{
			uchar * ptr = S3DData->m_matFlu.ptr<uchar>(i);
			file.Read(ptr, sizeof(uchar)*S3DData->m_matFlu.cols);
		}

		file.Read(&nCols, sizeof(int));
		file.Read(&nRows, sizeof(int));

		S3DData->m_matAllDefect = cv::Mat(nRows, nCols, CV_8UC1);

		S3DData->m_matAllDefect.setTo(0);
		for (i = 0; i < S3DData->m_matAllDefect.rows; i++)
		{
			uchar* ptr = S3DData->m_matAllDefect.ptr<uchar>(i);
			file.Read(ptr, sizeof(uchar)*S3DData->m_matAllDefect.cols);
		}

		file.Read(&nCols, sizeof(int));
		file.Read(&nRows, sizeof(int));

		S3DData->m_matRefCD = cv::Mat(nRows, nCols, CV_8UC1);

		S3DData->m_matRefCD.setTo(0);
		for (i = 0; i < S3DData->m_matRefCD.rows; i++)
		{
			uchar* ptr = S3DData->m_matRefCD.ptr<uchar>(i);
			file.Read(ptr, sizeof(uchar)*S3DData->m_matRefCD.cols);
		}


		file.Read(&nCols, sizeof(int));
		file.Read(&nRows, sizeof(int));

		S3DData->m_matRefImg = cv::Mat(nRows, nCols, CV_8UC1);
		S3DData->m_matRefImg.setTo(0);
		for (i = 0; i < S3DData->m_matRefImg.rows; i++)
		{
			uchar* ptr = S3DData->m_matRefImg.ptr<uchar>(i);
			file.Read(ptr, sizeof(uchar)* S3DData->m_matRefImg.cols);
		}

		file.Close();
		bLoadSuccess = TRUE;
		S3DData->m_bLoadManual3D = FALSE;
		str3DLog.Format(_T("Load Success : %s "), strPath);
		AfxMessageBox(str3DLog);
	}
	else
	{
		str3DLog.Format(_T("fail load file : %s "), strPath);
		AfxMessageBox(str3DLog);
		bLoadSuccess = FALSE;
	}

	delete szPath;

	return bLoadSuccess;
}

void CDlg3DViewer::LoadAndSet()
{
	SSR3DData* S3DData = Get3DData();
	S3DData->m_bValid = 1;

	SendMessage(WM_UPDATE_3D_MODEL, 0, 0);

	//m_DefectColor = S3DData->m_matDepthMapColor;

	m_fMax = S3DData->m_dMax;
	m_fMin = S3DData->m_dMin;

#ifdef SIMULATE
	CString strPath;
	cv::Mat mat3D = S3DData->m_matDepthMap.clone();
	strPath = CGvisAORDoc::m_pAORMasterDoc->m_strData3DFilePath + _T("m_matrixZ.exr");
	std::string ss = (CT2A(strPath));
	cv::imwrite(ss, mat3D);
#endif

	CString strData;
	strData.Format(_T("%.3f"), m_fMin*1000.0);
	SetDlgItemText(IDC_EDIT_MIN, strData);
	strData.Format(_T("%.3f"), m_fMax*1000.0);
	SetDlgItemText(IDC_EDIT_MAX, strData);

	//PostMessage(WM_COMMAND, IDC_BTN_SCAN);
	m_bUseCurve = TRUE;
	m_nSelectDrawType = SHAPE::SHAPE_NONE;
	Display3D();
}

void CDlg3DViewer::LoadAndSet(CString sPath)
{
	SSR3DData* S3DData = Get3DData();

	CFileFind finder;
	CString strFind;
	//m_vec3DFile.clear();
	//if (bXML)
	//{
	//	strFind = m_strLoadFolderPath + _T("\\*.XML");
	//}
	//else
	//{
	//	strFind = m_strLoadFolderPath + _T("\\*.3D");
	//}
	//BOOL bfind = finder.FindFile(strFind);

	//while (bfind)
	//{
	//	bfind = finder.FindNextFile();
	//	if (!finder.IsDots())
	//	{
	//		m_vec3DFile.push_back(finder.GetFileName());
	//	}
	//}

	//m_b3DLoad = TRUE;
	S3DData->m_bValid = 1;
	SendMessage(WM_UPDATE_3D_MODEL, 0, 0);

	//m_DefectColor = S3DData->m_matDepthMapColor;


#ifdef SIMULATE
	CString strPath;
	cv::Mat mat3D = S3DData->m_matDepthMap.clone();
	strPath = CGvisAORDoc::m_pAORMasterDoc->m_strData3DFilePath + _T("m_matrixZ.exr");
	std::string ss = (CT2A(strPath));
	cv::imwrite(ss, mat3D);
#endif

	//m_nPrePointX = 0;
	//m_nPrePointY = 0;
	//m_nCenterPointX = S3DData->m_matDepthMapColor.cols / 2;
	//m_nCenterPointY = S3DData->m_matDepthMapColor.rows / 2;
	//m_fDepthZoomScale = 1;
	//m_viewer.m_fDepthZoomScale = m_fDepthZoomScale;
	//m_viewer.m_ptPrePoint.x = m_nPrePointX;
	//m_viewer.m_ptPrePoint.y = m_nPrePointY;


	m_fMax = S3DData->m_dMax;
	m_fMin = S3DData->m_dMin;

	CString strData;
	strData.Format(_T("%.3f"), m_fMin*1000.0);
	SetDlgItemText(IDC_EDIT_MIN, strData);
	strData.Format(_T("%.3f"), m_fMax*1000.0);// +CGvisAORDoc::m_pAORMasterDoc->m_f3DMaxOffset);
	SetDlgItemText(IDC_EDIT_MAX, strData);

	//PostMessage(WM_COMMAND, IDC_BTN_SCAN);
	m_bUseCurve = TRUE;
	m_nSelectDrawType = SHAPE::SHAPE_NONE;
	Display3D();
}

CString CDlg3DViewer::CharToString(char *szStr)
{
	CString strRet;

	int nLen = strlen(szStr) + sizeof(char);
	wchar_t *tszTemp = NULL;
	tszTemp = new WCHAR[nLen];

	MultiByteToWideChar(CP_ACP, 0, szStr, -1, tszTemp, nLen * sizeof(WCHAR));

	strRet.Format(_T("%s"), (CString)tszTemp);
	if (tszTemp)
	{
		delete[] tszTemp;
		tszTemp = NULL;
	}
	return strRet;
}

void CDlg3DViewer::Auto3D()
{

}
