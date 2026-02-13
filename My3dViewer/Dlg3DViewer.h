#pragma once


// CDlg3DViewer 대화 상자입니다.

class CDlg3DViewer : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DViewer)

public:
	CDlg3DViewer(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlg3DViewer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_3D };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
