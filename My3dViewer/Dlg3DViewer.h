#pragma once

#include "OpenGLViewEx.h"
#include "OpenGLDraw.h"
#include "ReferenceData.h"
#include "C3DModel.h"
#include "Matching.h"
#include "afxwin.h"

// CDlg3DViewer 대화 상자입니다.
struct stTagZygoXYZ
{
	int nColY, nRowX;
	float fZmm;
};
typedef CArray<stTagZygoXYZ, stTagZygoXYZ> CArZygoXYZ;

struct stTagZygoInfo3D
{
	double dWaveLength, dResolution;
	int nTotalPhaseData, nSizeColY, nSizeRowX;
	CArZygoXYZ m_arZygoXYZ;
};

class CDlg3DViewer : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DViewer)

	CWnd* m_pParentWnd;
	COpenGLViewEx* m_pView;
	COpenGLDraw m_draw;
	CReferenceData *m_pReferenceData[REFER_BUFFER];
	int m_nIndexOfRefer;
	SSR3DData m_st3D;
	cv::Mat m_matrixA, m_matrixZ;
	stTagZygoInfo3D m_stZygoInfo3D;
	BOOL m_bFitSuccess;
	//sPlane m_RefPlane;
	cv::Mat m_DefectColor;
	cv::Mat m_Image;

	int m_nPolygonDrawVertex;
	CPoint m_ptPolygon[100];
	CPoint m_ptRect[4];
	CPoint m_ptLine[2];
	CPoint m_ptPrePoint;
	int m_nSelectDrawType;
	BOOL m_bUseCurve;
	float m_fMax, m_fMin;

	BOOL m_bOnlyResin;
	CButton m_ChkRectZoom;
	CButton m_ChkZoomIn;
	CButton m_ChkZoomOut;
	CButton m_ChkFit;

	float GetDepthAvg(cv::Mat &matrixZ);
	cv::Mat calcGrayHist(const cv::Mat& img);
	BOOL ExtractInfoDatx(CString sPath);
	BOOL ExtractInfoXYZ(CString sPath);
	TCHAR* StringToTCHAR(CString str);
	void StringToTCHAR(CString str, TCHAR* tszStr);
	void RemoveAllZygoXYZ();
	char* StringToChar(CString str);
	BOOL IsFileDatx(CString sPath);
	BOOL IsFileXYZ(CString sPath);

	BOOL Prepare3D(CString sPath);
	void Display3D();
	void Display3D(float fMin, float fMax);
	void InitParamRendering();
	void Auto3D();

private:
	// for OpenGL Rendering
	BOOL m_bOpMode; // IDC_CHECK_ZOOM
	int _mouseButton;
	CPoint _mouseDownPoint;
	CdPoint3D _eyePos;
	CdPoint3D _centerPos;
	double _angleHor;
	double _angleVer;
	double _fovAngle;
	double _transX;
	double _transY;
	double _transZ;

	void DrawMat(HDC hDC, cv::Mat& img);
	void DrawMat(HDC hDC, cv::Mat& img, int x, int y, int dw, int dh);

public:
	CDlg3DViewer(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlg3DViewer();

public:
	Matching m_cMatching;
	C3DModel m_Model;
	float m_fpos_start; // [mm]
	float m_fpos_end; // [mm]
	float m_fpos_reset; // [mm]
	float m_fScan_Range;
	float m_fScan_Ramp;
	float m_fpos_tgu; // [mm]
	float m_fpos_tgd;// [mm]


	void InitReference(int nIndex, CWnd *pView, CWnd *pViewPiece, CWnd *pViewMask);
	BOOL Grab(CString sPath);
	SSR3DData* Get3DData();
	void SetPosition(float fCurPos);
	void DispFree();

	void SetParentWnd(CWnd* pParentWnd);
	void GetMinMax(float& fMin, float& fMax);
	void SetMinMax(float fMin, float fMax);
	void AdjustRange(float fMin, float fMax);
public:
	LRESULT OnUpdate3DModel(WPARAM wParam, LPARAM lParam);
	LRESULT OnGLRender(WPARAM wParam, LPARAM lParam);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_3D };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_Pic;
	afx_msg void OnBnClickedCheckZoom();
	afx_msg void OnBnClickedCheckZoomin();
	afx_msg void OnBnClickedCheckZoomout();
	afx_msg void OnBnClickedCheckFit();
};
