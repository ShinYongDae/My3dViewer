
// My3dViewerDlg.h : 헤더 파일
//

#pragma once

#include "Dlg3DViewer.h"

// CMy3dViewerDlg 대화 상자
class CMy3dViewerDlg : public CDialog
{
	BOOL FileBrowse(CString& sPath);

// 생성입니다.
public:
	CMy3dViewerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY3DVIEWER_DIALOG };
#endif

public:
	CDlg3DViewer m_viewer;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
