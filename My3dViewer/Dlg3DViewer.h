#pragma once

#include "OpenGLViewEx.h"
#include "ReferenceData.h"
#include "C3DModel.h"

// CDlg3DViewer 대화 상자입니다.

class CDlg3DViewer : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DViewer)

	COpenGLViewEx* m_pView;
	CReferenceData *m_pReferenceData[REFER_BUFFER];
	int m_nIndexOfRefer;
	SSR3DData m_st3D;
	cv::Mat m_matrixZ;

	float GetDepthAvg(cv::Mat &matrixZ);
	cv::Mat calcGrayHist(const cv::Mat& img);

public:
	CDlg3DViewer(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlg3DViewer();

public:
	C3DModel m_Model;
	float m_fpos_start; // [mm]
	float m_fpos_end; // [mm]
	float m_fpos_reset; // [mm]
	float m_fScan_Range;
	float m_fScan_Ramp;
	float m_fpos_tgu; // [mm]
	float m_fpos_tgd;// [mm]


	void InitReference(int nIndex, CWnd *pView, CWnd *pViewPiece, CWnd *pViewMask);
	void Grab(CString sPath);
	SSR3DData* Get3DData();
	void SetPosition(float fCurPos);

public:
	LRESULT OnUpdate3DModel(WPARAM wParam, LPARAM lParam);

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
