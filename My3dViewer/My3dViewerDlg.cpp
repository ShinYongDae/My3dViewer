
// My3dViewerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "My3dViewer.h"
#include "My3dViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace std;


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy3dViewerDlg 대화 상자



CMy3dViewerDlg::CMy3dViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MY3DVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_viewer.SetParentWnd(this);
	m_fMax = 0.1;
	m_fMin = -0.1;
}

CMy3dViewerDlg::~CMy3dViewerDlg()
{
	if (m_viewer.GetSafeHwnd())
	{
		m_viewer.CloseWindow();
	}
}

void CMy3dViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEW, m_Pic);
	DDX_Control(pDX, IDC_VIEW_COLOR_BAR, m_PicColorBar);
}

BEGIN_MESSAGE_MAP(CMy3dViewerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy3dViewerDlg::OnBnClickedButton1)
	ON_WM_SHOWWINDOW()
	ON_WM_MOVE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3dViewerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy3dViewerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy3dViewerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMy3dViewerDlg 메시지 처리기

BOOL CMy3dViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_PicColorBar.GetWindowRect(m_rectResult);

	//CString sPath = _T("C:\\AorSet\\colors.jpg");
	CString sPath = _T("C:\\AorSet\\colorscale_rainbow.jpg");
	CFileFind cFile;
	BOOL bExist = cFile.FindFile(sPath);
	if (!bExist)
		AfxMessageBox(_T("Not exist colorscale_rainbow.jpg"));

	char * chText = StringToChar(sPath);
	//cv::Mat matRainbow = cv::imread("C:\\AorSet\\colors.jpg", cv::IMREAD_UNCHANGED);
	//cv::Mat matRainbow = cv::imread(chText, cv::IMREAD_UNCHANGED);
	m_matRainbow = cv::imread(chText, cv::IMREAD_UNCHANGED);
	delete chText;

	if (!m_matRainbow.empty())
		cv::resize(m_matRainbow, m_ImageColorBar, cv::Size(m_rectResult.Width(), m_rectResult.Height()));
	//if (!matRainbow.empty())
	//	cv::resize(matRainbow, m_ImageColorBar, cv::Size(m_rectResult.Width(), m_rectResult.Height()));

	m_viewer.Create(IDD_DLG_3D, this);

	CString sData;
	sData.Format(_T("%.6f"), m_fMin);
	SetDlgItemText(IDC_EDIT_MIN, sData);
	sData.Format(_T("%.6f"), m_fMax);
	SetDlgItemText(IDC_EDIT_MAX, sData);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMy3dViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMy3dViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();
		Refresh();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMy3dViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


TCHAR* CMy3dViewerDlg::StringToTCHAR(CString str)
{
	TCHAR *tszStr = NULL;
	int nLen = str.GetLength() + 1;
	tszStr = new TCHAR[nLen];
	memset(tszStr, 0x00, nLen * sizeof(TCHAR));
	_tcscpy(tszStr, str);

	return tszStr;
}


BOOL CMy3dViewerDlg::FileBrowse(CString& sPath, CString sType)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	//static TCHAR BASED_CODE szFilter[] = _T("3D Files (*.datx)|*.datx|All Files (*.*)|*.*||");
	//static TCHAR BASED_CODE szFilter[] = _T("3D Files (*.xyz)|*.xyz|All Files (*.*)|*.*||");
	//static TCHAR BASED_CODE szFilter[] = _T("3D Files (*.datx)|*.datx|3D Files (*.xyz)|*.xyz|All Files (*.*)|*.*||");
	TCHAR* szFilter = StringToTCHAR(sType);

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	delete szFilter;

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12를 Win2k Style로 다이얼로그 박스가 Open됨.

	// Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}

void CMy3dViewerDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath;

	if (!FileBrowse(sPath, _T("3D Files (*.datx)|*.datx|3D Files (*.xyz)|*.xyz|All Files (*.*)|*.*||")))
		return;
	GetDlgItem(IDC_STATIC_PATH)->SetWindowText(sPath);

	CString sData = _T("");
	CFileFind	find;
	if (!find.FindFile(sPath))
	{
		AfxMessageBox(_T("Error : 파일을 찾지못했습니다."));
		return;
	}

	if(m_viewer.Grab(sPath))
		AfxMessageBox(_T("Complete loading 3D File."));
}


void CMy3dViewerDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow)
	{
	}
}

void CMy3dViewerDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Refresh();
}

void CMy3dViewerDlg::Refresh()
{
	RefreshDlg();
}

void CMy3dViewerDlg::RefreshDlg()
{
	if (m_viewer.GetSafeHwnd())
	{
		CRect rtForm, rtViewer, rtDlg;
		this->GetWindowRect(&rtForm);
		int nHeithtSystemBar = GetSystemMetrics(SM_CYCAPTION);
		int nWidthFrameEdgeX = GetSystemMetrics(SM_CXPADDEDBORDER) * 2;
		int nWidthFrameEdgeY = GetSystemMetrics(SM_CYEDGE) * 3 + GetSystemMetrics(SM_CYBORDER) * 2;
		int OffsetY = nHeithtSystemBar + nWidthFrameEdgeY;
		int OffsetX = nWidthFrameEdgeX;
		GetDlgItem(IDC_VIEW)->GetWindowRect(&rtViewer);
		ScreenToClient(&rtViewer);

		//m_viewer.GetClientRect(rtDlg);
		m_viewer.GetWindowRect(rtDlg);
		int nWidthDlg = rtDlg.Width();
		int nHeightDlg = rtDlg.Height();
		rtDlg.left = rtForm.left + rtViewer.left + OffsetX;
		rtDlg.top = rtForm.top + rtViewer.top + OffsetY;
		m_viewer.SetWindowPos(NULL, rtDlg.left, rtDlg.top, nWidthDlg, nHeightDlg, SWP_NOZORDER | SWP_NOACTIVATE);
		m_viewer.ShowWindow(SW_SHOW);

		//if(!m_matRainbow.empty())
		//	cv::resize(m_matRainbow, m_ImageColorBar, cv::Size(m_rectResult.Width(), m_rectResult.Height()));


		if (m_PicColorBar.GetSafeHwnd())
		{
			CDC* pDCResult = m_PicColorBar.GetDC();
			if (!m_ImageColorBar.empty())
			{
				DrawMat(pDCResult->m_hDC, m_ImageColorBar);
			}
			ReleaseDC(pDCResult);
		}
	}
}

void CMy3dViewerDlg::DrawMat(HDC hDC, cv::Mat& img)
{
	CV_Assert(!img.empty() && hDC != NULL);
	int ws = (img.cols + 3) & ~3;
	DrawMat(hDC, img, 0, 0, ws, img.rows);
}

void CMy3dViewerDlg::DrawMat(HDC hDC, cv::Mat& img, int x, int y, int dw, int dh)
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


void CMy3dViewerDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_viewer.DispFree();
}

char* CMy3dViewerDlg::StringToChar(CString str)
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


void CMy3dViewerDlg::GetMinMax(float& fMin, float& fMax)
{
	CString sData;
	GetDlgItemText(IDC_EDIT_MIN, sData);
	m_fMin = _tstof(sData);
	GetDlgItemText(IDC_EDIT_MAX, sData);
	m_fMax = _tstof(sData);

	fMin = m_fMin;
	fMax = m_fMax;
}

void CMy3dViewerDlg::SetMinMax(float fMin, float fMax)
{
	m_fMin = fMin;
	m_fMax = fMax;

	CString sData;
	sData.Format(_T("%.6f"), m_fMin);
	SetDlgItemText(IDC_EDIT_MIN, sData);
	sData.Format(_T("%.6f"), m_fMax);
	SetDlgItemText(IDC_EDIT_MAX, sData);
}

void CMy3dViewerDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//cv::Mat matRainbow = cv::imread("C:\\AorSet\\colors.jpg");// , cv::IMREAD_UNCHANGED);
	//if (!matRainbow.empty())
	//	cv::resize(matRainbow, m_ImageColorBar, cv::Size(m_rectResult.Width(), m_rectResult.Height()));
	float fMin, fMax;
	GetMinMax(fMin, fMax);
	m_viewer.AdjustRange(fMin, fMax);
}


void CMy3dViewerDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath;
	GetDlgItemText(IDC_STATIC_PATH, sPath);
	if (sPath.IsEmpty())
	{
		AfxMessageBox(_T("IDC_STATIC_PATH 존재하지 않음."));
		return;
	}

	CFileFind cFile;
	BOOL bExist = cFile.FindFile(sPath);
	if (!bExist)
	{
		AfxMessageBox(_T("파일이 존재하지 않음."));
		return; // 파일이 존재하지 않음.
	}

	CString sFileName;

	int nPos = sPath.ReverseFind('.');
	if (nPos > 0)
	{
		sFileName = sPath.Left(nPos);
		nPos = sFileName.ReverseFind('\\');
		if (nPos > 0)
		{
			sFileName = sFileName.Right(sFileName.GetLength() - nPos - 1);
		}
		else
		{
			AfxMessageBox(_T("경로상에서 파일명 Parsing 오류."));
			return;
		}
	}
	else
	{
		AfxMessageBox(_T("경로상에서 확장명 Parsing 오류."));
		return;
	}

	sPath.Format(_T("C:\\AorSet\\xml\\%s.xml"), sFileName);
	m_viewer.SaveXMLCompress3D(sPath);
	CString sMsg;
	sMsg.Format(_T("%s 저장완료."),sPath);
	AfxMessageBox(sMsg);
}


void CMy3dViewerDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sPath;

	if (!FileBrowse(sPath, _T("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||")))
		return;
	GetDlgItem(IDC_STATIC_PATH)->SetWindowText(sPath);

	CString sData = _T("");
	CFileFind	find;
	if (!find.FindFile(sPath))
	{
		AfxMessageBox(_T("Error : 파일을 찾지못했습니다."));
		return;
	}

	//if (m_viewer.Load3DFile(sPath))
	//{
	//	m_viewer.LoadAndSet();
	//	AfxMessageBox(_T("Complete loading XML File."));
	//}
	if(m_viewer.LoadXMLCompress3D(sPath))
		AfxMessageBox(_T("Complete loading XML File."));
}
