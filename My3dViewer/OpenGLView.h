#if !defined(AFX_OPENGLVIEW_H__813CA629_88E1_4B26_B3AE_1E71DC5605BA__INCLUDED_)
#define AFX_OPENGLVIEW_H__813CA629_88E1_4B26_B3AE_1E71DC5605BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GvisMath.h"
#include "OpenGLFBO.h"
#include "OpenGLDraw.h"

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
////                          OpenGLView.h Ver 2.0                                 ////
////                             Developer: CAM PART                               ////
////                               Corp   : GIGAVIS                                ////
////																			   ////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

	
// OpenGLView.h : header file
//

#define FONTSCALE   0.0168
#define FONTUNITSCALE 0.00795
#define FONTLFGAP     0.66667
#define FONTLINEGAP	  0.294 
#define DOTLENGTH	0.001
#define LEFTUP      0
#define LEFTDOWN    1
#define RIGHTUP     2
#define RIGHTDOWN   3
#define CP949		949


/////////////////////////////////////////////////////////////////////////////
// COpenGLView window

namespace OPEN_GL
{
	enum COMMAND 
	{ 
		NONE = 0,
		RECT_ZOOM = 1,		// rect zoom
		TRANSLATE = 2,
		ROTATE = 3,
		ZOOMIN = 4,
		ZOOMOUT = 5,
		ZOOM2 = 6,
		SCREEN_FIT = 7,
		RECT_FIT = 8,
		MEASUREMENT = 9,
		PICKING_OBJ = 10,
		RECT_VIEW = 11,
		IMG_SAVE = 12,
		IMG_DIST = 13,
		IMG_DIST_SUB = 14,
		FIND_NOMINAL_LINE = 15,
		RECT_PICK = 16,
		SET_PIECE = 17,
		EDIT_PIECE = 18
	};

	enum COMMAND_TYPE 
	{ 
		INTERNAL=0,		// internal command mouse button or key board message
		EXTERNAL=1		// external(maybe parent window) command
	};
};


class COpenGLView : public CWnd , public GPickFunction
{
	char* StringToChar(CString str);

// Construction
public:
	COpenGLView();
	//////////////////////////////////////////////////////////////////////////
	BOOL m_bMbuttonClick;
	//////////////////////////////////////////////////////////////////////////
	BOOL m_bSendHandleID;
// Attributes
	CSize m_sizeWindow;
	DPOINT m_fptOffset;
	HGLRC m_hRC;
	BOOL m_bDrawFirst;
	void MakeCurrent();

public:
	BOOL m_bMessageSendMode;//
	double m_dWheelZDelta;
	//MIL_ID m_MilImageGray[2];
	unsigned char *m_pDataImage[2];
	unsigned char *m_pDataImageAlign[4];
	CSize m_szReferAngleImgSize[2];
	CdRect m_fRectImage;
	COpenGLFBO m_OpenGLFbo;
	BOOL	m_bLbuttonDown,m_bRbuttonDown;
	CString m_strFontName;
	double	m_fFontSize;
	COLORREF m_crFontColor,m_crFontBackColor;

	CdPoint3D m_fptCamPos;
	CdPoint3D m_fptCamAngle;
	HDC m_hDC;

	//+++++++++++++++++++++++
	// Management Redo Undo Action
	//CArRedoUndo  m_ArActionHistory;
	int m_nHistoryStep;

	CdRect m_frtWorld;
	CdRect m_frtExtent;
	DRECT m_frtRectPick;
	DPOINT m_fptPickMove;
	GLfloat m_fCanvasPixelResolution;  // [um/pixel]

	BOOL m_bCursor;
	int m_nCursorType;
	int m_nCursorSize;
	COLORREF m_crCursorColor;
	
	BOOL m_bShowCursor;

	int m_nHandleID;

	CPoint m_ptCurPos;		// current mouse position
	CdPoint3D m_fptCurPos;	// current world position
	CPoint m_ptRefPos;		// mouse click(down) position
	CdPoint3D m_fptRefPos;

	BOOL m_bDragingMeasure;
	BOOL m_bDragingTranslate;
	BOOL m_bDragingRectZoom;
	BOOL m_bDragingPiece;
	BOOL m_bDragingRotate;
	BOOL m_bDragingImgSave;
	BOOL m_bDragingImgDist;
	BOOL m_bDragingImgDistSub;
	BOOL m_bDragingFindNominalLine;

	BOOL m_bDisplayMetricUnit;
	int  m_nDisplayDecimalNum;


	double m_fFOV;
	double m_fNear;
	double m_fFar;

	BOOL m_bReady;
	OPEN_GL::COMMAND m_nOpMode;
	OPEN_GL::COMMAND m_nPrevOpMode;
	COpenGLDraw m_GLDraw;
	
	BOOL m_bSetFontData;
	/////
	CWnd	*m_pParentWnd;
	void	*m_fpGLRenderFunc; // rendering function pointer may be parent rendering function, by khc 
	COLORREF m_crBackGround;
	double	m_fFitSpace;

// Operations
	public:
	
	CdPoint3D ScreenToWorld(CPoint point);
	//BOOL FindCamPos(GLdouble fAspect,CdRect frtRect,GLfloat fSpace = 0.0f,GLfloat fOffset = 0.001,BOOL bHeight = FALSE);

	void InitGraphicTool();

	BOOL MakeFboScreen(CdRect rect,int nWindowWidth,int nWindowHeight,GLfloat fSpace);

	int  SetupPixelFormat(HDC hdc);	
	void GLRenderScene(UINT nAction = 0, int nKey = 0);
	void ClearHistory();
	int AddHistory(OPEN_GL::COMMAND nMode);
	void DrawImageDistSub(CdPoint3D fptRef,CdPoint3D fptCur);
	void DrawImageDist(CdPoint3D fptRef,CdPoint3D fptCur);
	void DrawFindNominalLine(CdPoint3D fptRef,CdPoint3D fptCur);
	void DrawImageSave(CdPoint3D fptRef,CdPoint3D fptCur);
	void DrawMeasureLine(CdPoint3D fptRef,CdPoint3D fptCur);
public:
	CPoint WorldToScreen(CdPoint3D  point);
	void GetTextSize(CString strText, double &fWidth, double &fHeight);
	void DrawTextDist(CString strText, DPOINT fptTextStart, COLORREF crColor);
	void DrawText(CString strText, DPOINT fptTextStart, GLdouble fFontSize);
	void DrawText(CString strText, DPOINT fptTextStart, GLdouble fFontSize, COLORREF crColor);
	void DrawText(CString strText, GLdouble x, GLdouble y, GLdouble z=0.0f, GLdouble fFontSize=1.0f, GLfloat fLintWidth= 1.0f,COLORREF color = BLACK,int Fill=FALSE);
	void DrawObjectDist(DPOINT fptRef,DPOINT fptCur);
	void SetWorldRect(CdRect frtWorld);
	
	CdRect GetWorldRect();
	CdPoint3D GetCamPos();
	void SetCamPos(CdPoint3D fptCamPos);
	
	BOOL FitToScreen(CdRect rect,GLfloat fSpace);
	BOOL FitToScreen(CdRect rect);
	BOOL FitToScreen();

	void ZoomMouseWheel(BOOL bZoomIn,double fup ,CdPoint3D fptCurPos);
	void AdjustCoordinate(CdPoint3D &fptStart, CdPoint3D &fptEnd);

	void GetOpenGLVersion(GLint &nMajor, GLint &nMinor);

	void SetMouseCursor(int Type=0, int Size = 0,COLORREF Color=YELLOW);
	void ViewCursor(BOOL bEnable=FALSE);
	void SetCursorType(int Type=0);
	void SetCursorSize(int Size = 0);
	void SetCursorColor(COLORREF Color=WHITE);
	
	CdPoint3D GetCurPos();
	void SetCurPos(CdPoint3D fpt);
	
	CdPoint3D GetWorldStartPos();
	CdPoint3D GetWorldEndPos();
	CdPoint3D GetExtentStartPos();
	CdPoint3D GetExtentEndPos();

	int		UndoHistory();
	int		RedoHistory();
	int		GetHistoryStep();

	CPoint	GetMousePos();
	CPoint	GetCurMousePos();

	void	SetOpMode(OPEN_GL::COMMAND nMode);
	OPEN_GL::COMMAND GetOpMode();
	OPEN_GL::COMMAND GetPrevOpMode();
	
	void SetCanvasPixelResolution();
	GLfloat GetCanvasPixelResolution();

	void SetDisplayGeneral(BOOL bUnit, int nDecimal);

	void Refresh(); // khc
	void ZoomIn(double fUp=2.0);
	void ZoomOut(double fDown=2.0);
	void Left(double fTranslate=10.0);
	void Right(double fTranslate=10.0);
	void Up(double fTranslate=10.0);
	void Down(double fTranslate=10.0);
	void Translate(CdPoint3D fpt);
	
	CdPoint3D GetRotateAngle();
	void SetRotateAngle(CdPoint3D fAngle);

	BOOL SetCoordinate(CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset=CdPoint(0,0));
	BOOL SetCoordinate(int nDlgId, CWnd *Dlg,CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset=CdPoint(0,0));
	void SetHandleID(int nHandleID);

	CSize GetCanvasSize();	
	CdRect GetExtentRect();
	
	void SetBackGroundColor(COLORREF color);
	COLORREF GetBackGroundColor();

	void SetRenderFunc(void(*fp)()); // Set rendering function pointer of parent window
	void ClearScreen();

	double GetFitSpace();
	void SetFitSpace(double fFitVal);

	//void SetFontName(CString strFontName);
	void SetFontColor(COLORREF crColor);
	void SetFontBackColor(COLORREF crColor);
	void SetFontSize(double fSize);
	double GetFontSize();

	void SetCamAngle(double Angle);
	unsigned char * SaveImageAngle(DRECT &fExtent, int nPixelWidth, int nPixelHeight, BOOL bCuttingMask, int nCuttingWidth);
	unsigned char * SaveImageAngleAlign(DRECT &fExtent, int nPixelWidth, int nPixelHeight);

	unsigned char * SaveImageAngleAlignNew(DRECT &fExtent, int nPixelWidth, int nPixelHeight, int nIndex);
	unsigned char * SaveImageAngleMask(DRECT &fExtent, int nPixelWidth, int nPixelHeight);
	unsigned char * SaveImageAngleHole(DRECT &fExtent, int nPixelWidth, int nPixelHeight);
	void AddCuttingMask(unsigned char *pDataImage, int nPixelWidth, int nPixelHeight,int nCuttingWidth);

	void SaveImage(unsigned char * pRefImage, CString strPath);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
	

	// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnPaint();
#ifdef UNDER_VS2008
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
#else
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
#endif
	afx_msg void OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg  BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLVIEW_H__813CA629_88E1_4B26_B3AE_1E71DC5605BA__INCLUDED_)
