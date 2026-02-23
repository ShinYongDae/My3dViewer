// Dlg3DViewer.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "My3dViewer.h"
#include "Dlg3DViewer.h"
#include "afxdialogex.h"


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
