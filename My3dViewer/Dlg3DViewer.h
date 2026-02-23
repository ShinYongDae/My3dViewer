#pragma once

#include "OpenGLViewEx.h"
#include "ReferenceData.h"

// CDlg3DViewer 대화 상자입니다.

class CDlg3DViewer : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DViewer)

	COpenGLViewEx* m_pView;
	CReferenceData *m_pReferenceData[REFER_BUFFER];
	int m_nIndexOfRefer;


public:
	CDlg3DViewer(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlg3DViewer();

public:
	void InitReference(int nIndex, CWnd *pView, CWnd *pViewPiece, CWnd *pViewMask);


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_3D };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
