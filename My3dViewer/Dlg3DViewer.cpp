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

}

CDlg3DViewer::~CDlg3DViewer()
{
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
