// OpenGLViewView.cpp : implementation file
//

/*
GL_POINTS    n개의 정점을 각각 그린다.  
GL_LINES    연결되어 있지 않은 선을 그린다. 각 세그먼트는 v0과 v1, v2와 v3,...등등이다. 만약 n이 홀수라면 세그먼트를 구성하지 못한 vn-1은 무시된다.  
GL_POLYGON    꼭지점으로 정점 v0, v1,..,vn-1를 가지는 다각형을 그린다. 정점은 적어도 3개이상이어야 하며 만약 그렇지 않다면 아무것도 그려지지 않는다. 또한 다각형을 이루고 있는 변들끼리 교차해서는 안되며 (하드웨어알고리즘의 제한성으로 인하여) 반드시 다각형은 컨벡스여야만 한다.  
GL_TRIANGLES    정점 v0, v1, v2를 이용하여 삼각형을 그리고 v3, v4, v5등을 이용하여 삼각형을 계속 그린다. 만약 남아있는 점이 3개가 안된다면 무시된다. 
GL_LINE_STRIP    v0에서 v1로, v1에서 v2로 와 같은 방식으로 선을 그린다. 마지막 vn-2에서 vn-1로 선을 그려 총 n-1개의 직선세그먼트를 그린다. 선을 그리는데 필요한 정점의 순서에 아무런 제약조건이 없으므로 서로 교차하는 직선도 그릴 수 있다. 
GL_LINE_LOOP    GL_LINE_STRIP과 동일하지만 마지막에 vn-1에서 v0을 잇는 선을 그려서 폐루프를 형성한다. 
GL_QUADS   정점 v0, v1, v2, v3를 이용하여 사각형을 그린다. 계속해서 v4, v5, v6, v7을 이용해서 그린다. 
GL_QUAD_STRIP    사각형을 그리는데 사각형을 이루고 있는 네 정점의 순서는 v0, v1, v3, v2 을 이용해서 그린 다음 v2, v3, v5, v4을 이용해서 사각형을 그리는 순서이다. 
GL_TRIANGLE_STRIP    삼각형을 그리는데 삼각형의 정점의 순서는 v0, v1, v2로 그리고, v2, v1, v3로 그리고, v2, v3, v4등으로 그리는 식이다. 이 순서는 삼각형이 제대로 위치를 가지도록 보장을 해주며 이를 이용하여 곡면/면의 일부를 나타내는데 사용된다. 
GL_TRIANGLE_FAN    GL_TRIANGLE_STRIP와 비슷하다 그러나 삼각형을 그릴때 정점 v0, v1, v2을 이용하여 그리고, v0,v2, v3를 이용해서 그리고, v0, v3, v4을 이용해서 그리는 방식을 취하는 점에서 다르다. 모든 삼각형은 공통적으로 정점 v0를 가지고 있다.
*/

#include "stdafx.h"
#include "OpenGLView.h"
#include <math.h>
#include <io.h>
#include <windowsx.h>
//#include "MainFrm.h"
//#include "GvisAORDoc.h"
//#include "DlgSetPieceArray.h"
#include "ColorTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 폰트 리스트의 기준 변수 
GLuint base;
//extern MIL_ID m_MilSystem;

//extern CGvisCamDoc* pGlobalDoc;
//extern CGvisCamView* pGlobalView;

/////////////////////////////////////////////////////////////////////////////
// COpenGLViewView

void COpenGLView::MakeCurrent()
{
	wglMakeCurrent(m_hDC,m_hRC);
}

COpenGLView::COpenGLView()
{
	m_bMessageSendMode = 0;
	m_dWheelZDelta = 0;
	m_bMbuttonClick = TRUE;
	m_bSendHandleID = TRUE;
	m_bCursor = FALSE;
	m_bShowCursor = FALSE;
	m_bLbuttonDown = FALSE;
	m_bRbuttonDown = FALSE;
	
	// perspective parameter
	m_crBackGround = WHITE; // set default back ground color
	m_nOpMode = OPEN_GL::NONE;
	m_nPrevOpMode= OPEN_GL::NONE;

	m_bDragingTranslate=FALSE;
	m_bDragingMeasure=FALSE;
	m_bDragingRectZoom=FALSE;
	m_bDragingPiece = FALSE;
	m_bDragingRotate=FALSE;
	m_bDragingImgSave = FALSE;
	m_bDragingImgDistSub = FALSE;
	m_bDragingImgDist = FALSE;
	m_bDragingFindNominalLine = FALSE;
	
	m_bDisplayMetricUnit = TRUE;
	m_nDisplayDecimalNum = 3;

	m_fptOffset.x=0.0f;
	m_fptOffset.y= 0.0f;

	m_fFOV = 1.0f;
	m_fNear = 0.1f;
	m_fFar = -5000000.0f;

	m_nCursorType =0;
	m_nCursorSize = 0;
	m_crCursorColor=0;

	m_fFitSpace=10.0f;
	m_nHistoryStep=-1;
	m_bReady = FALSE;

	m_strFontName.Empty();
	m_fFontSize = 10.0;
	m_crFontColor = RED;
	m_crFontBackColor = BLACK;
	m_fCanvasPixelResolution = 0.0f;
	m_bDrawFirst = TRUE;
	m_frtRectPick.left = 0;
	m_frtRectPick.right = 0;
	m_frtRectPick.bottom = 0;
	m_frtRectPick.top = 0;
	m_fptPickMove.x = 0;
	m_fptPickMove.y = 0;
	m_fRectImage.left = m_fRectImage.bottom = m_fRectImage.top = m_fRectImage.right = 0;
	m_pDataImage[0] = NULL;
	m_pDataImage[1] = NULL;
	m_pDataImageAlign[0] = NULL;
	m_pDataImageAlign[1] = NULL;
	m_pDataImageAlign[2] = NULL;
	m_pDataImageAlign[3] = NULL;
	//m_MilImageGray[0] = M_NULL;
	//m_MilImageGray[1] = M_NULL;
	m_szReferAngleImgSize[0].cx = 0;
	m_szReferAngleImgSize[0].cy = 0;
	m_szReferAngleImgSize[1].cx = 0;
	m_szReferAngleImgSize[1].cy = 0;
//	glutSetCursor(GLUT_CURSOR_WAIT );
}

COpenGLView::~COpenGLView()
{
	for (int i = 0; i < 2; i++)
	{
		//if (m_MilImageGray[i])
		//{
		//	MbufFree(m_MilImageGray[i]);
		//	m_MilImageGray[i] = NULL;
		//}
		if (m_pDataImage[i])
		{
			GlobalFreePtr(m_pDataImage[i]);
			m_pDataImage[i] = NULL;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_pDataImageAlign[i])
		{
			GlobalFreePtr(m_pDataImageAlign[i]);
			m_pDataImageAlign[i] = NULL;
		}
	}
	if(!m_strFontName.IsEmpty())
		m_GLDraw.DestroyFont();
	
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}

BEGIN_MESSAGE_MAP(COpenGLView, CWnd)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	ON_WM_ACTIVATEAPP()
	ON_WM_ASKCBFORMATNAME()
	ON_WM_SIZE()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_dWheelZDelta = (zDelta < 0) ? -1 : 1;

	GLRenderScene(WM_MOUSEWHEEL);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pParentWnd = GetParent();
	m_hDC = ::GetDC(m_hWnd);
	SetupPixelFormat(m_hDC);

	// 픽셀 포맷이 적절하게 셋팅되었다면 우리는 이제 Rendering Context를 얻어야 한다.
	// 만약 RC를 얻는데 실패했다면 에러메세지를 출력하고 프로그램은 종료한다. 마찬가지로 반환값은 False이다.
	// create rendering context and make it current
	m_hRC = wglCreateContext(m_hDC);

	// RC(rendering context)를 활성화 시켜야 한다.
	// 만약 실패한다면 에러메세지를 출력하고 프로그램은 종료 그리고 반환값은 False이다.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	InitGraphicTool();
	return 0;
}

void COpenGLView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}

void COpenGLView::InitGraphicTool()
{
	m_OpenGLFbo.CreateFbo();
	glPointSize(1.0);
	glLineWidth(1.0);
	glShadeModel(GL_SMOOTH); // default
//	glShadeModel(GL_FLAT);
}

int COpenGLView::SetupPixelFormat(HDC hdc)
{
	int nPixelFormat;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor   
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			24,
			0,0,0,0,0,0,
			0,0,
			0,0,0,0,0,
			32,
			1,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
	};

	nPixelFormat =ChoosePixelFormat(m_hDC,&pfd);
	VERIFY(SetPixelFormat(m_hDC,nPixelFormat,&pfd));
	m_hRC =wglCreateContext(m_hDC);	
	VERIFY(wglMakeCurrent(m_hDC,m_hRC));

	return 1;
}


void COpenGLView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if(!m_bReady) return;
	// TODO: Add your message handler code here
	GLRenderScene(WM_PAINT);
	// Do not call CWnd::OnPaint() for painting messages
}
#ifdef UNDER_VS2008
void COpenGLView::OnActivateApp(BOOL bActive, HTASK hTask) 
#else
void COpenGLView::OnActivateApp(BOOL bActive, DWORD hTask) 	
#endif
{
	CWnd::OnActivateApp(bActive, hTask);
	// TODO: Add your message handler code here	
}

///////////////////////////////////////////////////////////////////////////////
// Get the OpenGL version number
void COpenGLView::GetOpenGLVersion(GLint &nMajor, GLint &nMinor)
{      
	const TCHAR *szVersionString = (const TCHAR *)glGetString(GL_VERSION); 
	if(szVersionString == NULL) 
	{          
		nMajor = 0;          
		nMinor = 0;          
		return;          
	}            
	// Get major version number. This stops at the first non numeric character 
	nMajor = _ttoi(szVersionString);            
	// Get minor version number. Start past the first ".", _ttoi terminates on first non numeric char.
	nMinor = _ttoi(_tcsstr(szVersionString, _T("."))+1);
}  

void COpenGLView::OnAskCbFormatName(UINT nMaxCount, LPTSTR lpszString) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnAskCbFormatName(nMaxCount, lpszString);
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_bReady)
	{
		CRect rect;
		m_sizeWindow.cx=cx;
		m_sizeWindow.cy=cy;	
		
		if(FitToScreen(m_frtWorld,m_fFitSpace))
		{
			GLRenderScene(WM_SIZE);
		}
	}
}

CdRect COpenGLView::GetWorldRect()
{
	return m_frtWorld;
}

void COpenGLView::SetWorldRect(CdRect frtWorld)
{
	m_frtWorld = frtWorld;
}

void COpenGLView::OnCancelMode() 
{
	CWnd::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void COpenGLView::ClearScreen()
{
	glClearColor(0.0f,0.0f,0.0f,2.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 현재의 버퍼를 비워줌
	glLoadIdentity();
	glFlush();
}


void COpenGLView::ClearHistory()
{
	//m_ArActionHistory.RemoveAll();
	m_nHistoryStep=-1;
}

int COpenGLView::AddHistory(OPEN_GL::COMMAND nMode)
{
	//CRedoUndo sttRedoUndo = CRedoUndo(nMode,m_fptCamPos.x,m_fptCamPos.y,m_fptCamPos.z,m_fptCamAngle.x,m_fptCamAngle.y,m_fptCamAngle.z);

	//m_nHistoryStep++;
	//int nNUmOfHistory = m_ArActionHistory.GetSize();
	//if(m_nHistoryStep >= nNUmOfHistory)
	//	m_ArActionHistory.Add(sttRedoUndo);
	//else
	//{
	//	m_ArActionHistory.InsertAt(m_nHistoryStep,sttRedoUndo);
	//	m_ArActionHistory.RemoveAt(m_nHistoryStep+1,nNUmOfHistory-m_nHistoryStep);
	//}
	//
	return m_nHistoryStep;
}

int COpenGLView::UndoHistory()
{
	//int nNumOfHistory = m_ArActionHistory.GetSize();

	//if(nNumOfHistory > 1 && m_nHistoryStep > 0)
	//{
	//	m_nHistoryStep--;
	//	CRedoUndo sttRedoUndo;
	//	sttRedoUndo = m_ArActionHistory.GetAt(m_nHistoryStep);

	//	m_fptCamPos.x = sttRedoUndo.fptCamPos.x;
	//	m_fptCamPos.y = sttRedoUndo.fptCamPos.y;
	//	m_fptCamPos.z = sttRedoUndo.fptCamPos.z;

	//	m_fptCamAngle.x = sttRedoUndo.fptCamAngle.x;
	//	m_fptCamAngle.y = sttRedoUndo.fptCamAngle.y;
	//	m_fptCamAngle.z = sttRedoUndo.fptCamAngle.z;
	//	GLRenderScene(WM_FIT_TO_SCREEN);
	//}
	//return m_nHistoryStep;
	return 0;
}

int COpenGLView::RedoHistory()
{
	//int nNumOfHistory = m_ArActionHistory.GetSize();

	//if(nNumOfHistory > 1 && m_nHistoryStep < nNumOfHistory-1)
	//{
	//	m_nHistoryStep++;
	//	CRedoUndo sttRedoUndo;
	//	sttRedoUndo = m_ArActionHistory.GetAt(m_nHistoryStep);
	//	
	//	m_fptCamPos.x = sttRedoUndo.fptCamPos.x;
	//	m_fptCamPos.y = sttRedoUndo.fptCamPos.y;
	//	m_fptCamPos.z = sttRedoUndo.fptCamPos.z;

	//	m_fptCamAngle.x = sttRedoUndo.fptCamAngle.x;
	//	m_fptCamAngle.y = sttRedoUndo.fptCamAngle.y;
	//	m_fptCamAngle.z = sttRedoUndo.fptCamAngle.z;

	//	GLRenderScene(WM_FIT_TO_SCREEN);
	//}
	//return m_nHistoryStep;
	return 0;
}

int	COpenGLView::GetHistoryStep()
{
	return m_nHistoryStep;
}	

void COpenGLView::GLRenderScene(UINT nAction, int nKey)
{
	wglMakeCurrent(m_hDC, m_hRC);

	GLfloat red = GetRValue(m_crBackGround) / 255.0f;
	GLfloat green = GetGValue(m_crBackGround) / 255.0f;
	GLfloat blue = GetBValue(m_crBackGround) / 255.0f;

	glClearColor(red, green, blue,1);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLdouble fAspect;
 	if(m_sizeWindow.cy==0)
 		m_sizeWindow.cy=1;
 	glViewport(0,0,m_sizeWindow.cx,m_sizeWindow.cy);
 	fAspect=(GLdouble)m_sizeWindow.cx/(GLdouble)m_sizeWindow.cy;
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
	gluPerspective(m_fFOV,fAspect,m_fNear,m_fFar);

 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
	
	glRotatef(m_fptCamAngle.z,0.0f,0.0f,1.0f);
	glTranslated(m_fptCamPos.x,m_fptCamPos.y,m_fptCamPos.z);
	SetCanvasPixelResolution();

	CdPoint3D fptExtent1,fptExtent2;
	fptExtent1=ScreenToWorld(CPoint(0,0));
	fptExtent2=ScreenToWorld(CPoint(m_sizeWindow.cx,m_sizeWindow.cy));

	m_frtExtent.left   =fptExtent1.x;
	m_frtExtent.top    =fptExtent1.y;
	m_frtExtent.right  =fptExtent2.x;
	m_frtExtent.bottom =fptExtent2.y;

	m_fptCurPos = ScreenToWorld(m_ptCurPos);
	glPushMatrix();
	if(m_fptCamAngle.x != 0.0f || m_fptCamAngle.y != 0.0f)
	{
		glTranslatef((m_frtWorld.left+m_frtWorld.right)/2,(m_frtWorld.bottom+m_frtWorld.top)/2,0);
		glRotatef(m_fptCamAngle.x,1.0f,0.0f,0.0f);
		glRotatef(m_fptCamAngle.y,0.0f,1.0f,0.0f);
		glTranslatef(-(m_frtWorld.left+m_frtWorld.right)/2,-(m_frtWorld.bottom+m_frtWorld.top)/2,0);
	}
	int nNanTemp = _isnan(m_fCanvasPixelResolution);
	if (nNanTemp ==  0)
	{
		if (m_bSendHandleID)
		{
			if (m_pParentWnd)
				m_pParentWnd->SendMessage(WM_USER_RENDER, m_nHandleID, nAction);
		}
		else
		{
			if (m_pParentWnd)
				m_pParentWnd->SendMessage(WM_USER_RENDER, nKey, nAction);
		}
	}
	else
	{
		nNanTemp = nNanTemp;
	}

	glPopMatrix();
	if(m_bDragingRectZoom)  //rect zoom
	{
		m_GLDraw.SetColor(RED);
		m_GLDraw.DrawRect(m_fptRefPos,m_fptCurPos,2,FALSE);
	}
	if (m_bDragingPiece)
	{
		m_GLDraw.SetColor(BROWN);
		m_GLDraw.DrawRect(m_fptRefPos, m_fptCurPos, 2, FALSE);
	}
	if(m_bDragingMeasure) //Measure 
	{
		int nPolygonMode[4];
		glGetIntegerv(GL_POLYGON_MODE,nPolygonMode);
		if(nPolygonMode[0] == GL_LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		DrawMeasureLine(m_fptRefPos,m_fptCurPos);
		if(nPolygonMode[0] == GL_LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		}
	}

	if(m_bDragingImgSave)
	{
		DrawImageSave(m_fptRefPos,m_fptCurPos);
	}
	if(m_bDragingImgDist)
	{
		DrawImageDist(m_fptRefPos,m_fptCurPos);	
	}
	/*
	if(pGlobalView->m_bObjectDistanceSub)
	{
		if(m_bDragingImgDistSub)
		{
			DrawImageDistSub(m_fptRefPos,m_fptCurPos);	
		}
	}
	if(pGlobalView->m_bFindNominalLine)
	{
		if(m_bDragingFindNominalLine)
		{
			DrawFindNominalLine(m_fptRefPos,m_fptCurPos);	
		}
	}
	*/
	if(m_nCursorType != 0 && m_bShowCursor)    //mousecurser
	{
		if(m_nCursorType==1)
		{
			m_GLDraw.SetColor(m_crCursorColor);
			double fLength,fValue;
			if(m_frtExtent.right-m_frtExtent.left>m_frtExtent.top-m_frtExtent.bottom)
			{
				fValue=m_frtExtent.right-m_frtExtent.left;
			}
			else
			{
				fValue=m_frtExtent.top-m_frtExtent.bottom;
			}
			if(m_nCursorSize == 0)
			{
				fLength = fValue*2.0;
			}
			else if(m_nCursorSize == 1)
			{
				fLength = fValue/2.0;
			}
			else if(m_nCursorSize == 2)
			{
				fLength = fValue/4.0;
			}
			else if(m_nCursorSize == 3)
			{
				fLength = fValue/8.0;
			}
			m_GLDraw.DrawCross(m_fptCurPos,fLength,0.1);
		}
		/*
		GLfloat  fFontSize;
		if(m_fCursorSize==-1)
		{
			fFontSize=GetCanvasPixelResolution();
		}
		else
		{
			fFontSize=m_fCursorSize;
		}
		m_GLDraw.SetColor(m_crCursorColor);

		if(m_nCursorType==0)
		{
			m_GLDraw.DrawCross(m_fptCurPos,fFontSize,1);
		}
		else if(m_nCursorType==1)
		{
			m_GLDraw.DrawCross(m_fptCurPos,fFontSize,1,2);
		}
		else if(m_nCursorType==2)
		{
			m_GLDraw.DrawCircle(m_fptCurPos.x,m_fptCurPos.y,fFontSize/2,0);
		}
		else if(m_nCursorType==3)
		{
			m_GLDraw.DrawCircle(m_fptCurPos.x,m_fptCurPos.y,fFontSize/2,0);
			m_GLDraw.DrawCross(m_fptCurPos,fFontSize*2,1);
		}
		else if(m_nCursorType==4)
		{
			double fLength;

			if(m_frtExtent.right-m_frtExtent.left>m_frtExtent.top-m_frtExtent.bottom)
			{
				fLength=m_frtExtent.right-m_frtExtent.left;
			}
			else
			{
				fLength=m_frtExtent.top-m_frtExtent.bottom;
			}
			
			m_GLDraw.DrawCross(m_fptCurPos,fLength*10,0.1);
		}
		else
		{
			m_GLDraw.DrawCircle(m_fptCurPos.x,m_fptCurPos.y,fFontSize/2,0);
			m_GLDraw.DrawCross(m_fptCurPos,fFontSize*2,1,2);
		}
		*/
	}
	glFlush();

	SwapBuffers(m_hDC);
}
//++++++++++++++++++++++++++++++++++
// adjust to start pposition is lower than end position 
void COpenGLView::AdjustCoordinate(CdPoint3D &fptStart, CdPoint3D &fptEnd)
{
 	if(fptStart.x>fptEnd.x)
 		swap(fptStart.x,fptEnd.x);
 
 	if(fptStart.y>fptEnd.y)
		swap(fptStart.y,fptEnd.y);
}

GLfloat COpenGLView::GetCanvasPixelResolution()
{
	return m_fCanvasPixelResolution;
}

void COpenGLView::SetCanvasPixelResolution()
{
	CdPoint3D fpt;
	CdPoint3D fptObj1,fptObj2;
	CdPoint3D fptWin1,fptWin2;
	GLdouble fObjDistanceX,fObjDistanceY;
	GLdouble fRes;
	
	fObjDistanceX = m_sizeWindow.cx;
	fObjDistanceY = m_sizeWindow.cy;
	
	fptObj1.x=0.0;
	fptObj1.y=0.0;
	fptObj1.z=0.0f;
	fptObj2.x=fObjDistanceX;
	fptObj2.y=fObjDistanceY;
	fptObj2.z=0.0f;

	wglMakeCurrent(m_hDC, m_hRC);

	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint	viewport[4];

	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
	glGetIntegerv(GL_VIEWPORT,viewport);

	glTranslated(m_fptCamPos.x,m_fptCamPos.y,m_fptCamPos.z);

	// transforms the specified object coordinates into window coordinates using modelMatrix, projMatrix, and viewport
	gluProject(fptObj1.x, fptObj1.y, fptObj1.z, modelMatrix, projMatrix, viewport, &fptWin1.x,&fptWin1.y,&fptWin1.z);
	gluProject(fptObj2.x, fptObj2.y, fptObj2.z, modelMatrix, projMatrix, viewport, &fptWin2.x,&fptWin2.y,&fptWin2.z);	
	
	glPopMatrix();

	fRes =  fObjDistanceX/(fptWin2.x-fptWin1.x);
	fRes += fObjDistanceY/(fptWin2.y-fptWin1.y);

	m_fCanvasPixelResolution = fRes/2.0;
}

//+++++++++++++++++++++++++++++++++++++++++++++
// Convert OpenGL world position to Windows pixel position
CPoint COpenGLView::WorldToScreen(CdPoint3D  fpt)
{
	CdPoint3D fptObj1,fptObj2;
	CdPoint3D fptWin1,fptWin2;
	GLdouble fObjDistanceX,fObjDistanceY;
	CPoint point;

// 	CdPoint3D P;
// 	double fRes;
// 	P.y=m_frtExtent.top-m_frtExtent.bottom;
// 	fRes=m_sizeWindow.cy/P.y;
// 	point.y=(fpt.y - m_frtExtent.bottom )*fRes;
// 
// 	P.x=m_frtExtent.right-m_frtExtent.left;
// 	fRes=m_sizeWindow.cx/P.x;
// 	point.x=(fpt.x-m_frtExtent.left)*fRes;

	fObjDistanceX = m_sizeWindow.cx;
	fObjDistanceY = m_sizeWindow.cy;
	
	fptObj1.x=0.0;
	fptObj1.y=0.0;
	fptObj1.z=0.0f;
	fptObj2.x=fObjDistanceX;
	fptObj2.y=fObjDistanceY;
	fptObj2.z=0.0f;

	wglMakeCurrent(m_hDC, m_hRC);

	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint	viewport[4];

	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
	glGetIntegerv(GL_VIEWPORT,viewport);

	glTranslated(m_fptCamPos.x,m_fptCamPos.y,m_fptCamPos.z);

	// transforms the specified object coordinates into window coordinates using modelMatrix, projMatrix, and viewport
	gluProject(fptObj1.x, fptObj1.y, fptObj1.z, modelMatrix, projMatrix, viewport, &fptWin1.x,&fptWin1.y,&fptWin1.z);
	gluProject(fptObj2.x, fptObj2.y, fptObj2.z, modelMatrix, projMatrix, viewport, &fptWin2.x,&fptWin2.y,&fptWin2.z);	
	
	glPopMatrix();

	GLdouble fWinDistanceX, fWinDistanceY;
	fWinDistanceX=fptWin2.x-fptWin1.x;
	fWinDistanceY=fptWin2.y-fptWin1.y;

	GLdouble ff = GetCanvasPixelResolution();

	point.x = fpt.x /(fObjDistanceX/fWinDistanceX) + fptWin1.x;
	// convert point.y to window coordinate from OpenGL coordinate
	point.y = (double)m_sizeWindow.cy - (fpt.y / (fObjDistanceY/fWinDistanceY) + fptWin1.y);
	return point;
}

//+++++++++++++++++++++++++++++++++++++++++++++
// Convert Windows pixel position to OpenGL world position
CdPoint3D COpenGLView::ScreenToWorld(CPoint point)
{	
	CdPoint3D fpt;
	CdPoint3D fptObj1,fptObj2;
	CdPoint3D fptWin1,fptWin2;
	GLdouble fObjDistanceX,fObjDistanceY;

	
	fObjDistanceX = m_sizeWindow.cx;
	fObjDistanceY = m_sizeWindow.cy;
	
	fptObj1.x=0.0;
	fptObj1.y=0.0;
	fptObj1.z=0.0f;
	fptObj2.x=fObjDistanceX;
	fptObj2.y=fObjDistanceY;
	fptObj2.z=0.0f;

	wglMakeCurrent(m_hDC, m_hRC);

	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint	viewport[4];

	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
	glGetIntegerv(GL_VIEWPORT,viewport);

	glTranslated(m_fptCamPos.x,m_fptCamPos.y,m_fptCamPos.z);

	// transforms the specified object coordinates into window coordinates using modelMatrix, projMatrix, and viewport
	gluProject(fptObj1.x, fptObj1.y, fptObj1.z, modelMatrix, projMatrix, viewport, &fptWin1.x,&fptWin1.y,&fptWin1.z);
	gluProject(fptObj2.x, fptObj2.y, fptObj2.z, modelMatrix, projMatrix, viewport, &fptWin2.x,&fptWin2.y,&fptWin2.z);	
	
	glPopMatrix();

	GLdouble fWinDistanceX, fWinDistanceY;
	fWinDistanceX=fptWin2.x-fptWin1.x;
	fWinDistanceY=fptWin2.y-fptWin1.y;

	// convert point.y to window coordinate from OpenGL coordinate
	point.y = m_sizeWindow.cy-point.y;		

	fpt.x=((double)point.x-fptWin1.x)*(fObjDistanceX/fWinDistanceX);
	fpt.y=((double)point.y-fptWin1.y)*(fObjDistanceY/fWinDistanceY);
	fpt.z=0.0f;
	return fpt;
}

// Fit to full screen,canvas
BOOL COpenGLView::FitToScreen()
{
	if(FitToScreen(m_frtWorld,m_fFitSpace))
	{
		GLRenderScene(WM_FIT_TO_SCREEN);
		ClearHistory();
		AddHistory(OPEN_GL::SCREEN_FIT);

		return TRUE;
	}
	
	return FALSE;
}

BOOL COpenGLView::FitToScreen(CdRect rect)
{
	if(FitToScreen(rect,m_fFitSpace))
	{
		GLRenderScene();
		AddHistory(OPEN_GL::RECT_FIT);
		return TRUE;
	}
	return FALSE;
}

// Fit to user defined rect size
BOOL COpenGLView::FitToScreen(CdRect rect,GLfloat fSpace)
{
	CdPoint3D fptBeforeCamPos = m_fptCamPos;
 	m_fptCamPos.x=-(rect.right+rect.left)/2;
 	m_fptCamPos.y=-(rect.top+rect.bottom)/2;
	m_fptCamPos.z = m_fFar;
 	
	if(rect.right<rect.left)
		swap(rect.right,rect.left);
 	if(rect.top<rect.bottom)
		swap(rect.top,rect.bottom);

	wglMakeCurrent(m_hDC, m_hRC);
	
	int loopcnt=0;
	BOOL bFirst=TRUE;
	BOOL bBigger=TRUE;
	GLdouble fAspect;

	glViewport(0,0,m_sizeWindow.cx,m_sizeWindow.cy);
	fAspect=(GLdouble)m_sizeWindow.cx/(GLdouble)m_sizeWindow.cy;

	GLfloat fWidth = rect.right-rect.left,fHeight = rect.top-rect.bottom;
	
	//if(fWidth/m_sizeWindow.cx < fHeight/m_sizeWindow.cy)
	//{	 
	//	FindCamPos(fAspect,rect,(fSpace/100.0)*m_sizeWindow.cy,0.001,TRUE);
	//}
	//else
	//{
	//	FindCamPos(fAspect,rect,(fSpace/100.0)*m_sizeWindow.cx,0.001,FALSE);
	//}
	if(m_fptCamPos.z > -5.0 * m_fNear)
	{
		m_fptCamPos = fptBeforeCamPos;
	}
	return TRUE;
}

// Set rendering function pointer of parent window
void COpenGLView::SetRenderFunc(void(*fp)())
{
	m_fpGLRenderFunc = fp;
} 

CdPoint3D COpenGLView::GetCurPos()
{
	return m_fptCurPos;
}

//+++++++++++++++++++++++++++++++++++++++++++
// Set current position and mouse pointer move to 
void COpenGLView::SetCurPos(CdPoint3D fpt)
{
	fpt.z=0.0f;
	CPoint point = WorldToScreen(fpt);
	ClientToScreen(&point);
	SetCursorPos(point.x,point.y);
	m_ptCurPos = point;
}

void COpenGLView::SetMouseCursor(int Type,int Size,COLORREF Color)
{
	if(Type == 1)
		ViewCursor(TRUE);
	else
		ViewCursor(FALSE);

	m_nCursorType = Type;
	m_nCursorSize = Size;
	m_crCursorColor= Color;
}

void COpenGLView::ViewCursor(BOOL bEnable)
{
	int nShow = 0;
	m_bCursor = bEnable;
}

void COpenGLView::SetCursorType(int Type)
{
	m_nCursorType = Type;
}

void COpenGLView::SetCursorSize(int Size)
{
	m_nCursorSize = Size;
}

void COpenGLView::SetCursorColor(COLORREF Color)
{
	m_crCursorColor= Color;
}


CdPoint3D COpenGLView::GetWorldStartPos()
{
	CdPoint3D fptStart;

	fptStart.x=m_frtWorld.left;
	fptStart.y=m_frtWorld.bottom;
	fptStart.z=0.0f;

	return fptStart;
}

CdPoint3D COpenGLView::GetWorldEndPos()
{
	CdPoint3D fptEnd;

	fptEnd.x=m_frtWorld.right;
	fptEnd.y=m_frtWorld.top;
	fptEnd.z=0.0f;

	return fptEnd;
}

CdRect COpenGLView::GetExtentRect()
{
	return m_frtExtent;
}

CdPoint3D COpenGLView::GetExtentStartPos()
{
	CdPoint3D fptStart;

	fptStart.x=m_frtExtent.left;
	fptStart.y=m_frtExtent.bottom;
	fptStart.z=0.0f;

	return fptStart;
}
CdPoint3D COpenGLView::GetExtentEndPos()
{
	CdPoint3D fptEnd;

	fptEnd.x=m_frtExtent.right;
	fptEnd.y=m_frtExtent.top;
	fptEnd.z=0.0f;

	return fptEnd;
}

void COpenGLView::SetCamAngle(double Angle)
{
	m_fptCamAngle.z = Angle;
}

CSize COpenGLView::GetCanvasSize()
{
	return m_sizeWindow;
}

void COpenGLView::Refresh()
{
	GLRenderScene(WM_FIT_TO_SCREEN);
}

CPoint COpenGLView::GetCurMousePos()
{
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);
	return point;
}

CPoint COpenGLView::GetMousePos()
{
	return m_ptCurPos;
}

void COpenGLView::SetOpMode(OPEN_GL::COMMAND nMode)
{
	m_nPrevOpMode = m_nOpMode;
	m_nOpMode = nMode;
}

OPEN_GL::COMMAND COpenGLView::GetOpMode()
{
	return m_nOpMode;
}

OPEN_GL::COMMAND COpenGLView::GetPrevOpMode()
{
	return m_nPrevOpMode;
}

void COpenGLView::ZoomIn(double fup)
{
	m_fptCamPos.z/=fup;
	
	if(m_fptCamPos.z > -5.0 * m_fNear)
		m_fptCamPos.z = -5.0 * m_fNear;

	GLRenderScene(WM_FIT_TO_SCREEN);
	AddHistory(OPEN_GL::ZOOMIN);
	
}

void COpenGLView::ZoomOut(double fdown)
{
	m_fptCamPos.z*=fdown;

	GLRenderScene(WM_FIT_TO_SCREEN);
	AddHistory(OPEN_GL::ZOOMOUT);
}

void COpenGLView::ZoomMouseWheel(BOOL bZoomIn,double fup ,CdPoint3D fptCurPos)
{
	CdPoint3D fptBeforeCamPos = m_fptCamPos;
	double fCurCamPos;
	double fRatio;
	CdPoint fptCenter = CdPoint((m_frtExtent.left+m_frtExtent.right)/2.0,(m_frtExtent.top+m_frtExtent.bottom)/2.0);
	CdRect frtRect;
	frtRect = m_frtExtent;
	CdPoint fptBuf;
	if(bZoomIn)
	{
		m_fptCamPos.z/=fup;
		if(m_fptCamPos.z > -5.0 * m_fNear)
			m_fptCamPos.z = -5.0 * m_fNear;
	}
	else
	{
		m_fptCamPos.z*=fup;
	}
	fCurCamPos = m_fptCamPos.z;
	fRatio = fCurCamPos/fptBeforeCamPos.z;
	fptBuf.x = fptCenter.x - m_fptCurPos.x;
	fptBuf.y = fptCenter.y - m_fptCurPos.y;
	fptCenter.x = m_fptCurPos.x+fptBuf.x*fRatio;
	fptCenter.y = m_fptCurPos.y+fptBuf.y*fRatio;
	m_fptCamPos.x  = -fptCenter.x;
	m_fptCamPos.y = -fptCenter.y;

	fptBuf.x = frtRect.left - m_fptCurPos.x;
	fptBuf.y = frtRect.bottom - m_fptCurPos.y;
	frtRect.left = m_fptCurPos.x+fptBuf.x*fRatio;
	frtRect.bottom = m_fptCurPos.y+fptBuf.y*fRatio;

	fptBuf.x = frtRect.right - m_fptCurPos.x;
	fptBuf.y = frtRect.top - m_fptCurPos.y;
	frtRect.right = m_fptCurPos.x+fptBuf.x*fRatio;
	frtRect.top = m_fptCurPos.y+fptBuf.y*fRatio;
	if(frtRect.right-frtRect.left>(m_frtWorld.right-m_frtWorld.left)*5.0 && frtRect.top-frtRect.bottom>(m_frtWorld.top-m_frtWorld.bottom)*5.0)
	{
		m_fptCamPos = fptBeforeCamPos;
		return;
	}
	FitToScreen(frtRect,0);
	GLRenderScene(WM_FIT_TO_SCREEN);
	if(bZoomIn)
	{
		AddHistory(OPEN_GL::ZOOMIN);
	}
	else
	{
		AddHistory(OPEN_GL::ZOOMOUT);
	}
}

CdPoint3D COpenGLView::GetRotateAngle()
{
	return m_fptCamAngle;
}

void COpenGLView::SetRotateAngle(CdPoint3D fAngle)
{
	m_fptCamAngle = fAngle;
	if(m_fptCamAngle.x>=360.0f )
	{
		m_fptCamAngle.x=0.0f;
	}
	else if(m_fptCamAngle.x<0.0f)
	{
		m_fptCamAngle.x=360.0f;
	}

	if(m_fptCamAngle.y>=360.0f )
	{
		m_fptCamAngle.y=0.0f;
	}
	else if(m_fptCamAngle.y<0.0f)
	{
		m_fptCamAngle.y=360.0f;
	}

	if(m_fptCamAngle.z>=360.0f )
	{
		m_fptCamAngle.z=0.0f;
	}
	else if(m_fptCamAngle.z<0.0f)
	{
		m_fptCamAngle.z=360.0f;
	}
	GLRenderScene();

	AddHistory(OPEN_GL::ROTATE);
}

void COpenGLView::Translate(CdPoint3D fpt)
{
	m_fptCamPos.x -= fpt.x;
	m_fptCamPos.y -= fpt.y;
	GLRenderScene();
	AddHistory(OPEN_GL::TRANSLATE);	
}

void COpenGLView::Left(double fTranslate)
{
	m_fptCamPos.x -= fTranslate;
	GLRenderScene();
	AddHistory(OPEN_GL::TRANSLATE);
}
void COpenGLView::Right(double fTranslate)
{
	m_fptCamPos.x += fTranslate;
	GLRenderScene();
	AddHistory(OPEN_GL::TRANSLATE);
}
void COpenGLView::Up(double fTranslate)
{
	m_fptCamPos.y += fTranslate;
	GLRenderScene();
	AddHistory(OPEN_GL::TRANSLATE);
}

void COpenGLView::Down(double fTranslate)
{
	m_fptCamPos.y -= fTranslate;
	GLRenderScene();
	AddHistory(OPEN_GL::TRANSLATE);
}

///////////////////////////////////
// interface function
///////////////////////////////////

BOOL COpenGLView::SetCoordinate(int nDlgId, CWnd *Dlg,CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset)
{
	m_bDrawFirst = TRUE;
	CRect rect;

	m_fptCamPos.x=0.0;
	m_fptCamPos.y=0.0;
	m_fptCamPos.z=0.0;
	m_fptCamAngle.x=0.0f;
	m_fptCamAngle.y=0.0f;
	m_fptCamAngle.z=0.0f;

	Dlg->GetDlgItem(nDlgId)->GetClientRect(rect);
	m_sizeWindow.cx=rect.right;
	m_sizeWindow.cy=rect.bottom;
	
	m_frtWorld.left=fptStart.x;
	m_frtWorld.bottom=fptStart.y;
	m_frtWorld.right=fWorldSize.cx+fptStart.x;
	m_frtWorld.top=fWorldSize.cy+fptStart.y;

	m_fptOffset.x = fptOffset.x;
	m_fptOffset.y = fptOffset.y;

	if(FitToScreen())
		m_bReady = TRUE;
	else
		m_bReady = FALSE;
	return m_bReady;
}
BOOL COpenGLView::SetCoordinate(CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset)
{
	m_bDrawFirst = TRUE;
	CRect rect;

	m_fptCamPos.x=0.0;
	m_fptCamPos.y=0.0;
	m_fptCamPos.z=0.0;
	m_fptCamAngle.x=0.0f;
	m_fptCamAngle.y=0.0f;
	m_fptCamAngle.z=0.0f;

	GetClientRect(rect);
	m_sizeWindow.cx=rect.right;
	m_sizeWindow.cy=rect.bottom;
	
	m_frtWorld.left=fptStart.x;
	m_frtWorld.bottom=fptStart.y;
	m_frtWorld.right=fWorldSize.cx+fptStart.x;
	m_frtWorld.top=fWorldSize.cy+fptStart.y;

	m_fptOffset.x = fptOffset.x;
	m_fptOffset.y = fptOffset.y;

	if(FitToScreen())
		m_bReady = TRUE;
	else
		m_bReady = FALSE;
	return m_bReady;
}

void COpenGLView::SetBackGroundColor(COLORREF color)
{
	m_crBackGround = color;
	m_OpenGLFbo.SetBackGroundColor(color);
}

COLORREF COpenGLView::GetBackGroundColor()
{
	return m_crBackGround;
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLbuttonDown = TRUE;
	
	m_ptRefPos = m_ptCurPos = point;
	m_fptCurPos = ScreenToWorld(point);
	
	m_pParentWnd->PostMessage(WM_USER_CUR_POS_MESSAGE,(WPARAM)&m_fCanvasPixelResolution,(LPARAM)&m_fptCurPos);

	// set current world position regardless of the operating mode
	m_fptRefPos=m_fptCurPos;
	
	switch(m_nOpMode)
	{
	case OPEN_GL::RECT_VIEW: // for minimap
		break;
	case OPEN_GL::RECT_ZOOM:
		break;
	case OPEN_GL::TRANSLATE:
		break;
	case OPEN_GL::ROTATE:
		break;
	case OPEN_GL::IMG_SAVE:
		if(m_bDragingImgSave)
		{
			m_bDragingImgSave=FALSE;
			//m_fptRefPos=m_fptCurPos;
		}
		break;
	case OPEN_GL::IMG_DIST:
		if(m_bDragingImgDist)
		{
			m_bDragingImgDist=FALSE;
			//m_fptRefPos=m_fptCurPos;
		}
		break;
	case OPEN_GL::IMG_DIST_SUB:
		/*
		if(pGlobalView->m_bObjectDistanceSub)
		{
			if(m_bDragingImgDistSub)
			{
				m_bDragingImgDistSub=FALSE;
				//m_fptRefPos=m_fptCurPos;
			}
		}
		*/
		break;
	case OPEN_GL::FIND_NOMINAL_LINE:
		/*
		if(pGlobalView->m_bFindNominalLine)
		{
			if(m_bDragingFindNominalLine)
			{	
				m_bDragingFindNominalLine = FALSE;
			}
		}
		*/
		break;
	default:
		break;

	}
	GLRenderScene(WM_LBUTTONDOWN,nFlags);

	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT COpenGLView::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	if(m_bLbuttonDown)
	{
		ClientToScreen(&m_ptCurPos);
		SetCursorPos(m_ptCurPos.x,m_ptCurPos.y);
	}
	CPoint buf;
	GetCursorPos(&buf);
	ScreenToClient(&buf);	
	CRect rect;	
	GetClientRect(&rect);
	BOOL bState = PtInRect(rect,buf);

	if(m_bCursor != 0)
	{
		if(!m_bRbuttonDown)
		{
			m_bShowCursor = FALSE;
			Refresh();	
		}
	}
	
	return 0;
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if(m_bCursor != 0)
	{
		if(!m_bShowCursor)
			m_bShowCursor = TRUE;
	}
/*
	int nShow = 0;
	if(m_bShowCursor)
		nShow = ShowCursor(TRUE);
	else
		nShow = ShowCursor(FALSE);
*/

	m_ptCurPos = point;
	m_fptCurPos = ScreenToWorld(point);
	m_pParentWnd->PostMessage(WM_USER_CUR_POS_MESSAGE,(WPARAM)&m_fCanvasPixelResolution,(LPARAM)&m_fptCurPos);
	
	CdPoint3D f3dTranslate;

	switch(m_nOpMode)
	{
	case OPEN_GL::MEASUREMENT:
		if(nFlags == MK_LBUTTON)
		{
			if(!m_bDragingMeasure)
			{
				m_bDragingMeasure=TRUE;
			}
			else
			{


			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::RECT_VIEW: // for minimap
		if(nFlags == MK_LBUTTON)
		{
			m_fptPickMove.x = m_fptCurPos.x - m_fptRefPos.x;
			m_fptPickMove.y = m_fptCurPos.y - m_fptRefPos.y;
		}
		GLRenderScene(WM_MOUSEMOVE);
		break;
	case OPEN_GL::RECT_ZOOM:
		if(nFlags == MK_LBUTTON)
		{
			if(!m_bDragingRectZoom)
			{
				m_bDragingRectZoom=TRUE;
				//m_fptRefPos=m_fptCurPos;
			}
			else
			{
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::SET_PIECE:
		if (nFlags == MK_LBUTTON)
		{
			if (!m_bDragingPiece)
			{
				m_bDragingPiece = TRUE;
				//m_fptRefPos=m_fptCurPos;
			}
			else
			{
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::EDIT_PIECE:
		if (nFlags == MK_LBUTTON)
		{
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::RECT_PICK:
		if(nFlags == MK_LBUTTON)
		{
			if(!m_bDragingRectZoom)
			{
				m_bDragingRectZoom=TRUE;
				//m_fptRefPos=m_fptCurPos;
			}
			else
			{
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::IMG_SAVE:
		if(nFlags == MK_LBUTTON)
		{
			if(!m_bDragingImgSave)
			{
				m_bDragingImgSave=TRUE;
				//m_fptRefPos=m_fptCurPos;
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::IMG_DIST:
		if(nFlags == MK_LBUTTON)
		{
			if(!m_bDragingImgDist)
			{
				m_bDragingImgDist=TRUE;
				//m_fptRefPos=m_fptCurPos;
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;
	case OPEN_GL::IMG_DIST_SUB:
		/*
		if(nFlags == MK_LBUTTON)
		{
			if(pGlobalView->m_bObjectDistanceSub)
			{
				if(!m_bDragingImgDistSub)
			{
					m_bDragingImgDistSub=TRUE;
				//m_fptRefPos=m_fptCurPos;
			}
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		*/
		break;
	case OPEN_GL::FIND_NOMINAL_LINE:
		/*
		if(nFlags == MK_LBUTTON)
		{
			if(pGlobalView->m_bFindNominalLine)
			{
				if(!m_bDragingFindNominalLine)
				{	
					m_bDragingFindNominalLine = TRUE;
				}
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		*/
		break;
	case OPEN_GL::TRANSLATE:
		if(nFlags == MK_LBUTTON || nFlags == MK_MBUTTON)
		{
			if(!m_bDragingTranslate)
			{
				m_bDragingTranslate=TRUE;
			}
			else
			{
				f3dTranslate = m_fptRefPos-m_fptCurPos;

				m_fptCamPos.x -= f3dTranslate.x;
				m_fptCamPos.y -= f3dTranslate.y;
			}
			GLRenderScene(WM_MOUSEMOVE);
		}
		break;

	default:
		break;
	}
	if(m_nCursorType != 0 && m_nOpMode != OPEN_GL::RECT_VIEW && nFlags != MK_LBUTTON && nFlags != MK_MBUTTON)
	{
		GLRenderScene(WM_MOUSEMOVE);
	}
	else
	{
		if (m_bMessageSendMode)
		{
			GLRenderScene(WM_MOUSEMOVE);
		}
	}
//#ifndef _DEBUG
	TRACKMOUSEEVENT        mouseEvent;
	mouseEvent.cbSize = sizeof(mouseEvent);
	mouseEvent.dwFlags = TME_LEAVE;
	mouseEvent.hwndTrack = m_hWnd;
	TrackMouseEvent(&mouseEvent);
//#endif

	CWnd::OnMouseMove(nFlags, point);
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLbuttonDown = FALSE;
	m_ptCurPos=point;
	m_fptCurPos = ScreenToWorld(point);	
	m_pParentWnd->PostMessage(WM_USER_CUR_POS_MESSAGE,(WPARAM)&m_fCanvasPixelResolution,(LPARAM)&m_fptCurPos);
	
	switch(m_nOpMode)
	{
	case OPEN_GL::MEASUREMENT:
		if(m_bDragingMeasure)
		{
			m_bDragingMeasure=FALSE;
		}
		break;
	case OPEN_GL::RECT_VIEW: // for minimap
		break;
	case OPEN_GL::RECT_ZOOM:
		if(m_bDragingRectZoom)
		{
			m_bDragingRectZoom=FALSE;

			if(abs(m_ptRefPos.x - point.x) > 5 && abs(m_ptRefPos.y - point.y) > 5)
			{
				AdjustCoordinate(m_fptRefPos,m_fptCurPos);
				CdRect fRectZoom;
				fRectZoom.left=m_fptRefPos.x;
				fRectZoom.bottom=m_fptRefPos.y;
				fRectZoom.right=m_fptCurPos.x;
				fRectZoom.top=m_fptCurPos.y;
				FitToScreen(fRectZoom,0);
				AddHistory(m_nOpMode);
			}
		}
		break;
	case OPEN_GL::SET_PIECE:
		if (m_bDragingPiece)
		{
			m_bDragingPiece = FALSE;
		}
		break;
	case OPEN_GL::RECT_PICK:
		if(m_bDragingRectZoom)
		{
			m_bDragingRectZoom=FALSE;
			m_fptPickMove.x = 0;
			m_fptPickMove.y = 0;
			/*
			if(abs(m_ptRefPos.x - point.x) > 5 && abs(m_ptRefPos.y - point.y) > 5)
			{
				AdjustCoordinate(m_fptRefPos,m_fptCurPos);
				CdRect fRectZoom;
				fRectZoom.left=m_fptRefPos.x;
				fRectZoom.bottom=m_fptRefPos.y;
				fRectZoom.right=m_fptCurPos.x;
				fRectZoom.top=m_fptCurPos.y;
				FitToScreen(fRectZoom,0);
				AddHistory(m_nOpMode);
			}
			*/
			AdjustCoordinate(m_fptRefPos,m_fptCurPos);
			m_frtRectPick.left=m_fptRefPos.x;
			m_frtRectPick.bottom=m_fptRefPos.y;
			m_frtRectPick.right=m_fptCurPos.x;
			m_frtRectPick.top=m_fptCurPos.y;
		}
		break;
	case OPEN_GL::IMG_SAVE:
		if(m_bDragingImgSave)
		{
			m_bDragingImgSave=FALSE;
		}
		break;
	case OPEN_GL::IMG_DIST:
		if(m_bDragingImgDist)
		{
			m_bDragingImgDist=FALSE;
		}
		break;
	case OPEN_GL::IMG_DIST_SUB:
		/*
		if(pGlobalView->m_bObjectDistanceSub)
		{
			if(m_bDragingImgDistSub)
			{
				m_bDragingImgDistSub=FALSE;
				//m_fptRefPos=m_fptCurPos;
			}
		}
		*/
		break;
	case OPEN_GL::FIND_NOMINAL_LINE:
		/*
		if(pGlobalView->m_bFindNominalLine)
		{
			if(m_bDragingFindNominalLine)
			{
				m_bDragingFindNominalLine=FALSE;
				//m_fptRefPos=m_fptCurPos;
			}
		}
		*/
		break;
	case OPEN_GL::TRANSLATE:
		if(m_bDragingTranslate)
		{
			m_bDragingTranslate=FALSE;	
			AddHistory(m_nOpMode);
		}
		break;
	case OPEN_GL::ROTATE:
		{
		}
		break;
    case OPEN_GL::ZOOM2:
		ZoomMouseWheel(TRUE,4.0,m_fptCurPos);
		AddHistory(m_nOpMode);
		break;	
	default:
		break;

	}

	GLRenderScene(WM_LBUTTONUP,nFlags);

	CWnd::OnLButtonUp(nFlags, point);
}

void COpenGLView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bRbuttonDown = TRUE;
	m_fptCurPos = ScreenToWorld(point);

	GLRenderScene(WM_RBUTTONDOWN);
	if(m_nOpMode != OPEN_GL::ZOOM2)
		m_pParentWnd->SendMessage(WM_RBUTTONDOWN);
	CWnd::OnRButtonDown(nFlags, point);
}

void COpenGLView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRbuttonDown = FALSE;
	switch(m_nOpMode)
	{
	case OPEN_GL::ZOOM2:
		{
			ZoomMouseWheel(FALSE,4.0,m_fptCurPos);
			GLRenderScene(WM_RBUTTONUP);	
			AddHistory(m_nOpMode);
		}
		break;
	default:
		{
			GLRenderScene(WM_RBUTTONUP);
		}
	}
	
	CWnd::OnRButtonUp(nFlags, point);
}

void COpenGLView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	if(m_bMbuttonClick)
	{
		m_nPrevOpMode=GetOpMode();
		SetOpMode(OPEN_GL::TRANSLATE);

		m_ptCurPos = point;
		m_fptCurPos = ScreenToWorld(point);

		// set current world position regardless of the operating mode
		m_fptRefPos=m_fptCurPos;

		GLRenderScene(WM_MBUTTONDOWN);
	}
	CWnd::OnMButtonDown(nFlags, point);
}

void COpenGLView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bMbuttonClick)
	{
		m_fptCurPos = ScreenToWorld(point);
		if(m_bDragingTranslate)
		{
			m_bDragingTranslate=FALSE;	
			AddHistory(m_nOpMode);
		}
		if(m_fptRefPos.x == m_fptCurPos.x && m_fptRefPos.y == m_fptCurPos.y)
		{
			m_fptCamPos.x = - m_fptCurPos.x;
			m_fptCamPos.y = - m_fptCurPos.y;
		}
		GLRenderScene(WM_MBUTTONUP);
		SetOpMode(m_nPrevOpMode);
		GLRenderScene();
		
	}
	CWnd::OnMButtonUp(nFlags, point);
}


void COpenGLView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GLRenderScene(WM_LBUTTONDBLCLK);
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

double COpenGLView::GetFitSpace()
{
	return m_fFitSpace;
}
void COpenGLView::SetFitSpace(double fFitVal)
{
	m_fFitSpace=fFitVal;
}

void COpenGLView::SetHandleID(int nHandleID)
{
	m_nHandleID = nHandleID; 
}

void COpenGLView::SetFontSize(double fSize)
{
	m_fFontSize = fSize;
}
double COpenGLView::GetFontSize()
{
	return m_fFontSize;
}

void COpenGLView::SetFontColor(COLORREF crColor)
{
	m_crFontColor = crColor;
}

void COpenGLView::SetFontBackColor(COLORREF crColor)
{
	m_crFontBackColor = crColor;
}

//void COpenGLView::SetFontName(CString strFontName)
//{
//	
//	
//	
//	if(m_strFontName.CompareNoCase(strFontName))
//	{
//		CString strFontFileFullName;
//		int nResult;
//		if(!m_strFontName.IsEmpty())
//			m_GLDraw.DestroyFont();
//
//		if(strFontName.Find('@')>=0)
//		{
//			strFontName = strFontName.Mid(1);
//		}
//		strFontFileFullName = CGvisAORDoc::m_pAORMasterDoc->m_strFontFileFolder +_T("\\") +strFontName;
//		nResult = _taccess(strFontFileFullName,0);
//		if(nResult != 0)
//		{
//			strFontFileFullName = CGvisAORDoc::m_pAORMasterDoc->m_strFontFileFolder + _T("\\Verdana.ttf");
//		}
//
//
//		nResult = _taccess(strFontFileFullName,0);
//		if(nResult == 0)
//		{
//			
//#ifdef _UNICODE
//			char *FN = StringToChar(strFontFileFullName);
//
//			if(!m_GLDraw.Initialize(FONT_TYPE::BITMAP,FN, 128))
//			{
//             	     AfxMessageBox(_T("Fail m_GLDraw.Initialize Font"));
//				return;
//			}
//			delete FN;
//			FN = NULL;
//#else
//			if(!m_GLDraw.Initialize(FONT_TYPE::BITMAP,strFontFileFullName, 128))
//			{
//             	     AfxMessageBox(_T("Fail m_GLDraw.Initialize Font"));
//				return;
//			}
//#endif
//			
//		}
//		else
//		{
//			CString strMsg;
//                strMsg.Format(_T("%s :%s "), _T("Cannot Find Font"),strFontFileFullName);
//			AfxMessageBox(strMsg);
//			return;
//		}
//		m_strFontName = strFontFileFullName;
//	}
//	
//}
unsigned char * COpenGLView::SaveImageAngleAlignNew(DRECT &fExtent, int nPixelWidth, int nPixelHeight, int nIndex)
{
	Refresh();
	double fCamPosX = m_fptCamPos.x, fCamPosY = m_fptCamPos.y, fCamPosZ = m_fptCamPos.z;
	//++++++++++++++++++++++++
	// adjust window size

	CdRect fRectZoom;
	fRectZoom.left = fExtent.left;
	fRectZoom.bottom = fExtent.bottom;
	fRectZoom.right = fExtent.right;
	fRectZoom.top = fExtent.top;

	GLfloat red = GetRValue(m_crBackGround) / 255.0f;
	GLfloat green = GetGValue(m_crBackGround) / 255.0f;
	GLfloat blue = GetBValue(m_crBackGround) / 255.0f;
	int nErrorCode;

	if (!m_OpenGLFbo.InitFboImage(nErrorCode, nPixelWidth, nPixelHeight))
	{
		CString str;
		str.Format(_T("set fbo fail error code: %d  Width: %d Height: %d!!"), nErrorCode, nPixelWidth, nPixelHeight);
		AfxMessageBox(str);
		return FALSE;
	}
	m_OpenGLFbo.BindFboImage();
	glClearColor(red, green, blue, 1);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, nPixelWidth, nPixelHeight);

	GLdouble fAspect;
	fAspect = (GLdouble)nPixelWidth / (GLdouble)nPixelHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFOV, fAspect, m_fNear, m_fFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslated((fRectZoom.left + fRectZoom.right) / 2.0, (fRectZoom.bottom + fRectZoom.top) / 2.0, 0);
	BOOL bSuccess = MakeFboScreen(fRectZoom, nPixelWidth, nPixelHeight, 0);
	m_fRectImage = fRectZoom;
	if (bSuccess)
	{
		if (m_pParentWnd)
			m_pParentWnd->SendMessage(WM_USER_RENDER_FRAME_BUFFER, m_nHandleID, 1);
	}

	glPopMatrix();
	glFlush();
	if (!bSuccess)
	{
		m_fptCamPos.x = fCamPosX;
		m_fptCamPos.y = fCamPosY;
		m_fptCamPos.z = fCamPosZ;
		m_OpenGLFbo.CleanFboImage();
		return FALSE;
	}
	nPixelWidth = nPixelWidth - nPixelWidth % 4;

	BYTE *pBufData;
	pBufData = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight * 3);
	glReadPixels(0, 0, nPixelWidth, nPixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pBufData);

	if (!m_pDataImageAlign[nIndex])
	{
		m_pDataImageAlign[nIndex] = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight);
	}
	for (int i = 0; i < nPixelHeight; i++)
	{
		for (int j = 0; j < nPixelWidth; j++)
		{
			if (pBufData[i*nPixelWidth * 3 + j * 3 + 0] > 0)
			{
				m_pDataImageAlign[nIndex][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 1] > 0)
			{
				m_pDataImageAlign[nIndex][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 2] > 0)
			{
				m_pDataImageAlign[nIndex][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else
			{
				m_pDataImageAlign[nIndex][(nPixelHeight - i - 1)*nPixelWidth + j] = 0;
			}
		}
	}
	GlobalFreePtr(pBufData);
	pBufData = NULL;
	m_OpenGLFbo.CleanFboImage();

	m_fptCamPos.x = fCamPosX;
	m_fptCamPos.y = fCamPosY;
	m_fptCamPos.z = fCamPosZ;


	Refresh();
	return m_pDataImageAlign[nIndex];
}
unsigned char * COpenGLView::SaveImageAngleMask(DRECT &fExtent, int nPixelWidth, int nPixelHeight)
{
	Refresh();
	double fCamPosX = m_fptCamPos.x, fCamPosY = m_fptCamPos.y, fCamPosZ = m_fptCamPos.z;
	//++++++++++++++++++++++++
	// adjust window size

	CdRect fRectZoom;
	fRectZoom.left = fExtent.left;
	fRectZoom.bottom = fExtent.bottom;
	fRectZoom.right = fExtent.right;
	fRectZoom.top = fExtent.top;

	GLfloat red = GetRValue(m_crBackGround) / 255.0f;
	GLfloat green = GetGValue(m_crBackGround) / 255.0f;
	GLfloat blue = GetBValue(m_crBackGround) / 255.0f;
	int nErrorCode;

	if (!m_OpenGLFbo.InitFboImage(nErrorCode, nPixelWidth, nPixelHeight))
	{
		CString str;
		str.Format(_T("set fbo fail error code: %d  Width: %d Height: %d!!"), nErrorCode, nPixelWidth, nPixelHeight);
		AfxMessageBox(str);
		return FALSE;
	}
	m_OpenGLFbo.BindFboImage();
	glClearColor(red, green, blue, 1);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, nPixelWidth, nPixelHeight);

	GLdouble fAspect;
	fAspect = (GLdouble)nPixelWidth / (GLdouble)nPixelHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFOV, fAspect, m_fNear, m_fFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslated((fRectZoom.left + fRectZoom.right) / 2.0, (fRectZoom.bottom + fRectZoom.top) / 2.0, 0);
	BOOL bSuccess = MakeFboScreen(fRectZoom, nPixelWidth, nPixelHeight, 0);
	m_fRectImage = fRectZoom;
	if (bSuccess)
	{
		if (m_pParentWnd)
			m_pParentWnd->SendMessage(WM_USER_RENDER_FRAME_BUFFER, m_nHandleID, 3);
	}

	glPopMatrix();
	glFlush();
	if (!bSuccess)
	{
		m_fptCamPos.x = fCamPosX;
		m_fptCamPos.y = fCamPosY;
		m_fptCamPos.z = fCamPosZ;
		m_OpenGLFbo.CleanFboImage();
		return FALSE;
	}
	nPixelWidth = nPixelWidth - nPixelWidth % 4;

	BYTE *pBufData;
	pBufData = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight * 3);
	glReadPixels(0, 0, nPixelWidth, nPixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pBufData);
	if (m_szReferAngleImgSize[0].cx != nPixelWidth || m_szReferAngleImgSize[0].cy != nPixelHeight)
	{
		//if (m_MilImageGray[0])
		//{
		//	MbufFree(m_MilImageGray[0]);
		//	m_MilImageGray[0] = NULL;
		//}
		if (m_pDataImage[0])
		{
			GlobalFreePtr(m_pDataImage[0]);
			m_pDataImage[0] = NULL;
		}
		m_szReferAngleImgSize[0].cx = nPixelWidth;
		m_szReferAngleImgSize[0].cy = nPixelHeight;
	}
	if (!m_pDataImage[0])
	{
		m_pDataImage[0] = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight);
	}
	for (int i = 0; i < nPixelHeight; i++)
	{
		for (int j = 0; j < nPixelWidth; j++)
		{
			if (pBufData[i*nPixelWidth * 3 + j * 3 + 0] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 1] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 2] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 0;
			}
		}
	}
	GlobalFreePtr(pBufData);
	pBufData = NULL;
	m_OpenGLFbo.CleanFboImage();

	m_fptCamPos.x = fCamPosX;
	m_fptCamPos.y = fCamPosY;
	m_fptCamPos.z = fCamPosZ;


	Refresh();
	return m_pDataImage[0];
}
unsigned char * COpenGLView::SaveImageAngleHole(DRECT &fExtent, int nPixelWidth, int nPixelHeight)
{
	Refresh();
	double fCamPosX = m_fptCamPos.x, fCamPosY = m_fptCamPos.y, fCamPosZ = m_fptCamPos.z;
	//++++++++++++++++++++++++
	// adjust window size

	CdRect fRectZoom;
	fRectZoom.left = fExtent.left;
	fRectZoom.bottom = fExtent.bottom;
	fRectZoom.right = fExtent.right;
	fRectZoom.top = fExtent.top;

	GLfloat red = GetRValue(m_crBackGround) / 255.0f;
	GLfloat green = GetGValue(m_crBackGround) / 255.0f;
	GLfloat blue = GetBValue(m_crBackGround) / 255.0f;
	int nErrorCode;

	if (!m_OpenGLFbo.InitFboImage(nErrorCode, nPixelWidth, nPixelHeight))
	{
		CString str;
		str.Format(_T("set fbo fail error code: %d  Width: %d Height: %d!!"), nErrorCode, nPixelWidth, nPixelHeight);
		AfxMessageBox(str);
		return FALSE;
	}
	m_OpenGLFbo.BindFboImage();
	glClearColor(red, green, blue, 1);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, nPixelWidth, nPixelHeight);

	GLdouble fAspect;
	fAspect = (GLdouble)nPixelWidth / (GLdouble)nPixelHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFOV, fAspect, m_fNear, m_fFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslated((fRectZoom.left + fRectZoom.right) / 2.0, (fRectZoom.bottom + fRectZoom.top) / 2.0, 0);
	BOOL bSuccess = MakeFboScreen(fRectZoom, nPixelWidth, nPixelHeight, 0);
	m_fRectImage = fRectZoom;
	if (bSuccess)
	{
		if (m_pParentWnd)
			m_pParentWnd->SendMessage(WM_USER_RENDER_FRAME_BUFFER, m_nHandleID, 2);
	}

	glPopMatrix();
	glFlush();
	if (!bSuccess)
	{
		m_fptCamPos.x = fCamPosX;
		m_fptCamPos.y = fCamPosY;
		m_fptCamPos.z = fCamPosZ;
		m_OpenGLFbo.CleanFboImage();
		return FALSE;
	}
	nPixelWidth = nPixelWidth - nPixelWidth % 4;

	BYTE *pBufData;
	pBufData = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight * 3);
	glReadPixels(0, 0, nPixelWidth, nPixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pBufData);
	if (m_szReferAngleImgSize[0].cx != nPixelWidth || m_szReferAngleImgSize[0].cy != nPixelHeight)
	{
		//if (m_MilImageGray[0])
		//{
		//	MbufFree(m_MilImageGray[0]);
		//	m_MilImageGray[0] = NULL;
		//}
		if (m_pDataImage[0])
		{
			GlobalFreePtr(m_pDataImage[0]);
			m_pDataImage[0] = NULL;
		}
		m_szReferAngleImgSize[0].cx = nPixelWidth;
		m_szReferAngleImgSize[0].cy = nPixelHeight;
	}
	if (!m_pDataImage[0])
	{
		m_pDataImage[0] = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight);
	}
	for (int i = 0; i < nPixelHeight; i++)
	{
		for (int j = 0; j < nPixelWidth; j++)
		{
			if (pBufData[i*nPixelWidth * 3 + j * 3 + 0] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 1] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 2] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 0;
			}
		}
	}
	GlobalFreePtr(pBufData);
	pBufData = NULL;
	m_OpenGLFbo.CleanFboImage();

	m_fptCamPos.x = fCamPosX;
	m_fptCamPos.y = fCamPosY;
	m_fptCamPos.z = fCamPosZ;


	Refresh();
	return m_pDataImage[0];
}
unsigned char * COpenGLView::SaveImageAngleAlign(DRECT &fExtent, int nPixelWidth, int nPixelHeight)
{
	Refresh();
	double fCamPosX = m_fptCamPos.x, fCamPosY = m_fptCamPos.y, fCamPosZ = m_fptCamPos.z;
	//++++++++++++++++++++++++
	// adjust window size

	CdRect fRectZoom;
	fRectZoom.left = fExtent.left;
	fRectZoom.bottom = fExtent.bottom;
	fRectZoom.right = fExtent.right;
	fRectZoom.top = fExtent.top;

	GLfloat red = GetRValue(m_crBackGround) / 255.0f;
	GLfloat green = GetGValue(m_crBackGround) / 255.0f;
	GLfloat blue = GetBValue(m_crBackGround) / 255.0f;
	int nErrorCode;

	if (!m_OpenGLFbo.InitFboImage(nErrorCode, nPixelWidth, nPixelHeight))
	{
		CString str;
		str.Format(_T("set fbo fail error code: %d  Width: %d Height: %d!!"), nErrorCode, nPixelWidth, nPixelHeight);
		AfxMessageBox(str);
		return FALSE;
	}
	m_OpenGLFbo.BindFboImage();
	glClearColor(red, green, blue, 1);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, nPixelWidth, nPixelHeight);

	GLdouble fAspect;
	fAspect = (GLdouble)nPixelWidth / (GLdouble)nPixelHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFOV, fAspect, m_fNear, m_fFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslated((fRectZoom.left + fRectZoom.right) / 2.0, (fRectZoom.bottom + fRectZoom.top) / 2.0, 0);
	BOOL bSuccess = MakeFboScreen(fRectZoom, nPixelWidth, nPixelHeight, 0);
	m_fRectImage = fRectZoom;
	if (bSuccess)
	{
		if (m_pParentWnd)
			m_pParentWnd->SendMessage(WM_USER_RENDER_FRAME_BUFFER, m_nHandleID, 0);
	}

	glPopMatrix();
	glFlush();
	if (!bSuccess)
	{
		m_fptCamPos.x = fCamPosX;
		m_fptCamPos.y = fCamPosY;
		m_fptCamPos.z = fCamPosZ;
		m_OpenGLFbo.CleanFboImage();
		return FALSE;
	}
	nPixelWidth = nPixelWidth - nPixelWidth % 4;

	BYTE *pBufData;
	pBufData = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight * 3);
	glReadPixels(0, 0, nPixelWidth, nPixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pBufData);
	if (m_szReferAngleImgSize[1].cx != nPixelWidth || m_szReferAngleImgSize[1].cy != nPixelHeight)
	{
		//if (m_MilImageGray[1])
		//{
		//	MbufFree(m_MilImageGray[1]);
		//	m_MilImageGray[1] = NULL;
		//}
		if (m_pDataImage[1])
		{
			GlobalFreePtr(m_pDataImage[1]);
			m_pDataImage[1] = NULL;
		}
		m_szReferAngleImgSize[1].cx = nPixelWidth;
		m_szReferAngleImgSize[1].cy = nPixelHeight;
	}
	if (!m_pDataImage[1])
	{
		m_pDataImage[1] = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight);
	}
	for (int i = 0; i < nPixelHeight; i++)
	{
		for (int j = 0; j < nPixelWidth; j++)
		{
			if (pBufData[i*nPixelWidth * 3 + j * 3 + 0] > 0)
			{
				m_pDataImage[1][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 1] > 0)
			{
				m_pDataImage[1][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 2] > 0)
			{
				m_pDataImage[1][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else
			{
				m_pDataImage[1][(nPixelHeight - i - 1)*nPixelWidth + j] = 0;
			}
		}
	}
	GlobalFreePtr(pBufData);
	pBufData = NULL;
	m_OpenGLFbo.CleanFboImage();

	m_fptCamPos.x = fCamPosX;
	m_fptCamPos.y = fCamPosY;
	m_fptCamPos.z = fCamPosZ;


	Refresh();
	return m_pDataImage[1];
}
unsigned char * COpenGLView::SaveImageAngle(DRECT &fExtent, int nPixelWidth, int nPixelHeight, BOOL bCuttingMask, int nCuttingWidth)
{
	Refresh();
	double fCamPosX = m_fptCamPos.x, fCamPosY = m_fptCamPos.y, fCamPosZ = m_fptCamPos.z;
	//++++++++++++++++++++++++
	// adjust window size

	CdRect fRectZoom;
	fRectZoom.left = fExtent.left;
	fRectZoom.bottom = fExtent.bottom;
	fRectZoom.right = fExtent.right;
	fRectZoom.top = fExtent.top;

	GLfloat red = GetRValue(m_crBackGround) / 255.0f;
	GLfloat green = GetGValue(m_crBackGround) / 255.0f;
	GLfloat blue = GetBValue(m_crBackGround) / 255.0f;
	int nErrorCode;

	if (!m_OpenGLFbo.InitFboImage(nErrorCode, nPixelWidth, nPixelHeight))
	{
		CString str;
		str.Format(_T("set fbo fail error code: %d  Width: %d Height: %d!!"), nErrorCode, nPixelWidth, nPixelHeight);
		AfxMessageBox(str);
		return FALSE;
	}
	m_OpenGLFbo.BindFboImage();
	glClearColor(red, green, blue, 1);
	glClearStencil(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, nPixelWidth, nPixelHeight);

	GLdouble fAspect;
	fAspect = (GLdouble)nPixelWidth / (GLdouble)nPixelHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(m_fFOV, fAspect, m_fNear, m_fFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslated((fRectZoom.left + fRectZoom.right) / 2.0, (fRectZoom.bottom + fRectZoom.top) / 2.0, 0);
	BOOL bSuccess = MakeFboScreen(fRectZoom, nPixelWidth, nPixelHeight, 0);
	m_fRectImage = fRectZoom;
	if (bSuccess)
	{
		if (m_pParentWnd)
			m_pParentWnd->SendMessage(WM_USER_RENDER_FRAME_BUFFER, m_nHandleID, 0);
	}

	glPopMatrix();
	glFlush();
	if (!bSuccess)
	{
		m_fptCamPos.x = fCamPosX;
		m_fptCamPos.y = fCamPosY;
		m_fptCamPos.z = fCamPosZ;
		m_OpenGLFbo.CleanFboImage();
		return FALSE;
	}
	nPixelWidth = nPixelWidth - nPixelWidth % 4;

	BYTE *pBufData;
	pBufData = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight * 3);
	glReadPixels(0, 0, nPixelWidth, nPixelHeight, GL_RGB, GL_UNSIGNED_BYTE, pBufData);
	if (m_szReferAngleImgSize[0].cx != nPixelWidth || m_szReferAngleImgSize[0].cy != nPixelHeight)
	{
		//if (m_MilImageGray[0])
		//{
		//	MbufFree(m_MilImageGray[0]);
		//	m_MilImageGray[0] = NULL;
		//}
		if (m_pDataImage[0])
		{
			GlobalFreePtr(m_pDataImage[0]);
			m_pDataImage[0] = NULL;
		}
		m_szReferAngleImgSize[0].cx = nPixelWidth;
		m_szReferAngleImgSize[0].cy = nPixelHeight;
	}
	if (!m_pDataImage[0])
	{
		m_pDataImage[0] = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, sizeof(BYTE)*nPixelWidth*nPixelHeight);
	}	
	for (int i = 0; i < nPixelHeight; i++)
	{
		for (int j = 0; j < nPixelWidth; j++)
		{
			if (pBufData[i*nPixelWidth * 3 + j * 3 + 0] > 0)
			{
				m_pDataImage[0][(nPixelHeight -i-1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 1] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else if (pBufData[i*nPixelWidth * 3 + j * 3 + 2] > 0)
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 255;
			}
			else
			{
				m_pDataImage[0][(nPixelHeight - i - 1)*nPixelWidth + j] = 0;
			}
		}
	}
	GlobalFreePtr(pBufData);
	pBufData = NULL;
	m_OpenGLFbo.CleanFboImage();

	m_fptCamPos.x = fCamPosX;
	m_fptCamPos.y = fCamPosY;
	m_fptCamPos.z = fCamPosZ;
	if (bCuttingMask)
	{
		AddCuttingMask(m_pDataImage[0], nPixelWidth, nPixelHeight, nCuttingWidth);
	}


	Refresh();
	return m_pDataImage[0];
}
void COpenGLView::SaveImage(unsigned char * pRefImage, CString strPath)
{
	//int nPixelWidth = MAX_JAI_WIDTH_SIZE;
	//int nPixelHeight = MAX_JAI_HEIGHT_SIZE;
	//if (m_MilImageGray[0] == M_NULL)
	//{
	//	MbufAlloc2d(m_MilSystem, nPixelWidth, nPixelHeight, M_DEF_IMAGE_TYPE, M_IMAGE, &m_MilImageGray[0]);
	//}
	//MbufPut2d(m_MilImageGray[0], 0, 0, nPixelWidth, nPixelHeight, pRefImage);
	//MbufSave(strPath, m_MilImageGray[0]);
}
void COpenGLView::SetCamPos(CdPoint3D fptCamPos)
{
	m_fptCamPos = fptCamPos;
}
CdPoint3D COpenGLView::GetCamPos()
{
	return m_fptCamPos;
}

//BOOL COpenGLView::FindCamPos(GLdouble fAspect,CdRect frtRect,GLfloat fSpace,GLfloat fOffset,BOOL bHeight)
//{
//	double MousePosL[3];
//	GLdouble model[16];	
//	GLdouble proj[16];
//	GLint viewport[4];
//	GLdouble fCamPos = m_fptCamPos.z;
//	GLdouble fStartPos,fEndPos,fBufPos;
//	BOOL bUp,bFirst = TRUE;
//	int nLoopCnt = 0;
//	GLdouble dRightTopX = frtRect.right,dRightTopY = frtRect.top;
//	BOOL bFind = TRUE;
//	while(nLoopCnt<1000)
//	{
//		nLoopCnt++;
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective(m_fFOV,fAspect,m_fNear,m_fFar);
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//		glTranslatef(m_fptCamPos.x,m_fptCamPos.y,fCamPos);
//		glGetDoublev(GL_MODELVIEW_MATRIX,model);
//		glGetDoublev(GL_PROJECTION_MATRIX,proj);
//		glGetIntegerv(GL_VIEWPORT,viewport);
//		gluProject(dRightTopX, dRightTopY, 0.0f, model, proj, viewport, &MousePosL[0],&MousePosL[1],&MousePosL[2]);
//		
//		if(bHeight)
//		{
//			if(MousePosL[1]+fSpace>viewport[3])
//			{
//				if(!bFirst)
//				{
//					if(bUp)
//					{
//							break;
//					}
//				}
//				bUp = FALSE;
//			}
//			else
//			{
//				if(!bFirst)
//				{
//					if(!bUp)
//					{
//						break;
//					}
//				}
//				bUp = TRUE;
//			}
//		}
//		else 
//		{
//			if(MousePosL[0]+fSpace>viewport[2])
//			{
//				if(!bFirst)
//				{
//					if(bUp)
//				{	 
//					break;
//				}
//				}
//				bUp = FALSE;
//			}
//			else
//			{
//				if(!bFirst)
//				{
//					if(!bUp)
//					{
//						break;
//					}
//				}
//				bUp = TRUE;
//			}
//		}
//		fStartPos = fCamPos;
//		if(bUp)
//		{
//			fCamPos /= 2.0;
//		}
//		else
//		{
//			fCamPos *= 2.0;
//		}
//		fEndPos = fCamPos;
//		bFirst=FALSE;
//	}
//	
//	if(fStartPos>fEndPos)
//	{
//		fBufPos = fStartPos;
//		fStartPos = fEndPos;
//		fEndPos = fBufPos;
//	}
//	
//	while(nLoopCnt<1000)
//	{
//		nLoopCnt++;
//		fCamPos = (fStartPos +fEndPos)/2.0;
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective(m_fFOV,fAspect,m_fNear,m_fFar);
//		glMatrixMode(GL_MODELVIEW);
//		glLoadIdentity();
//		glTranslatef(m_fptCamPos.x,m_fptCamPos.y,fCamPos);
//		glGetDoublev(GL_MODELVIEW_MATRIX,model);
//		glGetDoublev(GL_PROJECTION_MATRIX,proj);
//		glGetIntegerv(GL_VIEWPORT,viewport);
//		gluProject(dRightTopX, dRightTopY, 0.0, model, proj, viewport, &MousePosL[0],&MousePosL[1],&MousePosL[2]);
//
//
//		if(bHeight)
//		{
//			if(MousePosL[1]+fSpace>viewport[3])
//			{
//				if(MousePosL[1]+fSpace-viewport[3]<fOffset)
//					break;
//				bUp = FALSE;
//			}
//			else
//			{	 
//				if(viewport[3]-(MousePosL[1]+fSpace)<fOffset)
//					break;
//				bUp = TRUE;
//			}
//		}
//		else
//		{
//			if(MousePosL[0]+fSpace>viewport[2])
//			{
//				if(MousePosL[0]+fSpace+viewport[2]<fOffset)
//					break;
//				bUp = FALSE;
//			}
//			else
//			{
//				if(viewport[2]-(MousePosL[0]+fSpace)<fOffset)
//					break;
//				bUp = TRUE;
//			}
//		}
//		if(bUp)
//		{
//			fStartPos = fCamPos;
//		}
//		else 
//		{
//			fEndPos = fCamPos;
//		}
//		if(fEndPos-fStartPos <fOffset)
//		{	 
//			break;
//		}
//	}
//	
//	if(fCamPos > -1.01 * m_fNear)
//	{
//		fCamPos = -1.01 * m_fNear; 
//		bFind = FALSE;
//	}
//	m_fptCamPos.z = fCamPos;
//	return bFind;
//}

BOOL COpenGLView::MakeFboScreen(CdRect rect,int nWindowWidth,int nWindowHeight,GLfloat fSpace)
{
	BOOL bFind = TRUE;
	m_fptCamPos.x=-(rect.right+rect.left)/2;
	m_fptCamPos.y=-(rect.top+rect.bottom)/2;
	if(rect.right<rect.left)
		swap(rect.right,rect.left);
	if(rect.top<rect.bottom)
		swap(rect.top,rect.bottom);

	wglMakeCurrent(m_hDC, m_hRC);

	int loopcnt=0;
	BOOL bFirst=TRUE;
	BOOL bBigger=TRUE;
	GLdouble fAspect;
	if(nWindowHeight==0)
		nWindowHeight=1;
	glViewport(0,0,nWindowWidth,nWindowHeight);
	fAspect=(GLdouble)nWindowWidth/(GLdouble)nWindowHeight;
	GLdouble fWidth = rect.right-rect.left,fHeight = rect.top-rect.bottom;
	//if(fWidth/m_sizeWindow.cx<fHeight/m_sizeWindow.cy)
	//{	
	//	bFind = FindCamPos(fAspect,rect,fSpace,0.001,TRUE);
	//}
	//else
	//{
	//	bFind = FindCamPos(fAspect,rect,fSpace,0.001,FALSE);
	//}
	return bFind;
}

void COpenGLView::GetTextSize(CString strText, double &fWidth, double &fHeight)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();

	if(m_strFontName.IsEmpty())
	{
		return;
	}
	else
	{
#ifdef _UNICODE
		char * chText = StringToChar(strText);
#else

		unsigned char *chText = (unsigned char *)strText.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
}

void COpenGLView::DrawTextDist(CString strText, DPOINT fptTextStart, COLORREF crColor)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();

	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(strText,fptTextStart.x,fptTextStart.y,0.0f,fFontSize,2,crColor);
	}
	else
	{
#ifdef _UNICODE
		char * chText = StringToChar(strText);	
#else

		char *chText = strText.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
//		double fWidth,fHeight,fLowerPartHeight;
//		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
//		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);

//		m_GLDraw.DrawRect(tagdPOINT(fptTextStart.x,fptTextStart.y+fLowerPartHeight),tagdPOINT(fptTextStart.x+fWidth*0.95,fptTextStart.y+fHeight));

		glColor4f(GetRValue(crColor)/255.0,GetGValue(crColor)/255.0,GetBValue(crColor)/255.0,1.0);
//		m_GLDraw.DrawLine(fptRef.x,fptTextStart.y,fptCur.x,fptTextStart.y);

		glPushMatrix();
		glTranslatef(fptTextStart.x,fptTextStart.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);

		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
}
void COpenGLView::DrawText(CString strText, GLdouble x, GLdouble y, GLdouble z, GLdouble fFontSize, GLfloat fLintWidth,COLORREF color,int Fill)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	if(strText.GetLength()<1)
		return;
	double dScale = fFontSize;


	glPushMatrix();

	glTranslatef(x, y, z);

	if(Fill == TRUE)
	{	
		int Lengh = strText.GetLength();
		m_GLDraw.SetColor(WHITE);
		glBegin(GL_QUADS);
		glVertex3f(-20*fFontSize,-25*fFontSize,0);
		glVertex3f(-20*fFontSize,+150*fFontSize,0);
		glVertex3f(75*fFontSize*Lengh,+150*fFontSize,0);
		glVertex3f(75*fFontSize*Lengh,-25*fFontSize,0);
		glEnd();
	}

	//	OpenGL renders stroke fonts with lines, 
	//	the line width can be specified by using the function glLineWidth() which takes only one parameter represents the width of the line. 
	//	Also the stroke width can be specified by using the function
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);

	glLineWidth(fLintWidth);

	m_GLDraw.SetColor(color);

	glScalef(dScale, dScale, 1);

#ifdef _UNICODE
	char * chText = StringToChar(strText);
#else
	char *chText = (char *)strText.GetBuffer(0);
#endif

	m_GLDraw.DrawBMPFont(chText);

	glPopMatrix();

	glLineWidth(lineWidth);
#ifdef _UNICODE
	delete chText;
	chText = NULL;
#endif
}
void COpenGLView::DrawText(CString strText, DPOINT fptTextStart, GLdouble fFontSize)
{
	GLfloat fCanvasResolution = GetCanvasPixelResolution();

#ifdef _UNICODE
	char * chText = StringToChar(strText);
#else

	char *chText = strText.GetBuffer(0);
#endif
	double dScale = fFontSize / 150.0;

	glPushMatrix();
	glTranslatef(fptTextStart.x, fptTextStart.y, 0);
	glScalef(dScale, dScale, 1);
	m_GLDraw.DrawBMPFont(chText);

	glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
	delete chText;
	chText = NULL;
#endif
}
void COpenGLView::DrawText(CString strText, DPOINT fptTextStart, GLdouble fFontSize, COLORREF crColor)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();

#ifdef _UNICODE
	char * chText = StringToChar(strText);	
#else

	char *chText = strText.GetBuffer(0);
#endif
	double dScale = fFontSize/150.0;
	//		double fWidth,fHeight,fLowerPartHeight;
	//		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
	//		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);

	//		m_GLDraw.DrawRect(tagdPOINT(fptTextStart.x,fptTextStart.y+fLowerPartHeight),tagdPOINT(fptTextStart.x+fWidth*0.95,fptTextStart.y+fHeight));

	glColor4f(GetRValue(crColor)/255.0,GetGValue(crColor)/255.0,GetBValue(crColor)/255.0,1.0);
	//		m_GLDraw.DrawLine(fptRef.x,fptTextStart.y,fptCur.x,fptTextStart.y);

	glPushMatrix();
	glTranslatef(fptTextStart.x,fptTextStart.y, 0);
	glScalef(dScale, dScale, 1);
	m_GLDraw.DrawBMPFont(chText);

	glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
	delete chText;
	chText = NULL;
#endif
}

void COpenGLView::DrawObjectDist(DPOINT fptRef,DPOINT fptCur)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	CString txt, strUnit;
	CString strBuf;
	DPOINT fptOffset;
	DPOINT fptTextStart;
	double fMeasureLength;
	if(fptRef.x>fptCur.x)
	{
		fMeasureLength = fptRef.x-fptCur.x;
	}
	else
	{
		fMeasureLength = fptCur.x-fptRef.x;
	}
	fptTextStart.x = (fptRef.x+fptCur.x)/2.0f;
	fptTextStart.y = fptRef.y;

	if(!m_bDisplayMetricUnit)
	{
		fMeasureLength = fMeasureLength / 25.4;
		strUnit = _T("Inch");
	}
	else
	{
		if(fMeasureLength<1)
		{
			fMeasureLength *= 1000;
			strUnit = _T("um");
		}
		else
			strUnit = _T("mm");
	}
	
	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("%.f%s"),fMeasureLength, strUnit);
		break;
	case 1:
		txt.Format(_T("%.1f%s"),fMeasureLength, strUnit);
		break;
	case 2:
		txt.Format(_T("%.2f%s"),fMeasureLength, strUnit);
		break;
	case 3:
		txt.Format(_T("%.3f%s"),fMeasureLength, strUnit);
		break;
	case 4:
		txt.Format(_T("%.4f%s"),fMeasureLength, strUnit);
		break;
	case 5:
		txt.Format(_T("%.5f%s"),fMeasureLength, strUnit);
		break;
	case 6:
		txt.Format(_T("%.6f%s"),fMeasureLength, strUnit);
		break;
	}

	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,fptTextStart.x,fptTextStart.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		  char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);

		m_GLDraw.DrawRect(tagdPOINT(fptTextStart.x,fptTextStart.y+fLowerPartHeight),tagdPOINT(fptTextStart.x+fWidth*0.95,fptTextStart.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawLine(fptRef.x,fptTextStart.y,fptCur.x,fptTextStart.y);

		glPushMatrix();
		glTranslatef(fptTextStart.x,fptTextStart.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
			
		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}

	if(fptRef.y>fptCur.y)
	{
		fMeasureLength = fptRef.y-fptCur.y;
	}
	else
	{
		fMeasureLength = fptCur.y-fptRef.y;
	}
	fptTextStart.x = fptCur.x;
	fptTextStart.y = (fptRef.y+fptCur.y)/2.0f;

	if(!m_bDisplayMetricUnit)
	{
		fMeasureLength = fMeasureLength / 25.4;
		strUnit = _T("Inch");
	}
	else
	{
		if(fMeasureLength<1)
		{
			fMeasureLength *= 1000;
			strUnit = _T("um");
		}
		else
			strUnit = _T("mm");
	}

	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("%.f%s"),fMeasureLength, strUnit);
		break;
	case 1:
		txt.Format(_T("%.1f%s"),fMeasureLength, strUnit);
		break;
	case 2:
		txt.Format(_T("%.2f%s"),fMeasureLength, strUnit);
		break;
	case 3:
		txt.Format(_T("%.3f%s"),fMeasureLength, strUnit);
		break;
	case 4:
		txt.Format(_T("%.4f%s"),fMeasureLength, strUnit);
		break;
	case 5:
		txt.Format(_T("%.5f%s"),fMeasureLength, strUnit);
		break;
	case 6:
		txt.Format(_T("%.6f%s"),fMeasureLength, strUnit);
		break;
	}
	

	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,fptTextStart.x,fptTextStart.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		 char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);

		m_GLDraw.DrawRect(tagdPOINT(fptTextStart.x,fptTextStart.y+fLowerPartHeight),tagdPOINT(fptTextStart.x+fWidth*0.95,fptTextStart.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawLine(fptTextStart.x,fptRef.y,fptTextStart.x,fptCur.y);

		glPushMatrix();
		glTranslatef(fptTextStart.x,fptTextStart.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
			
		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
}
void COpenGLView::DrawMeasureLine(CdPoint3D fptRef,CdPoint3D fptCur)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	CString txt, strUnit;
	CString strBuf;
	DPOINT fptOffset;
	CdPoint fptCenter = CdPoint((m_frtExtent.left+m_frtExtent.right)/2.0,(m_frtExtent.top+m_frtExtent.bottom)/2.0);
	double fMeasureLength = GetDistance(fptRef,fptCur);
	double dAngle = atan2(fptCur.y-fptRef.y,fptCur.x-fptRef.x);
	if(dAngle<0)
		dAngle += 2*PI;
	unsigned char ch;
	ch = 128;

	if(!m_bDisplayMetricUnit)
	{
		fMeasureLength = fMeasureLength / 25.4;
		strUnit = _T("Inch");
	}
	else
	{
		if(fMeasureLength<1)
		{
			fMeasureLength *= 1000;
			strUnit = _T("um");
		}
		else
			strUnit = _T("mm");
	}

	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("%-.f%s,%-.fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	case 1:
		txt.Format(_T("%-.1f%s,%-.1fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	case 2:
		txt.Format(_T("%-.2f%s,%-.2fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	case 3:
		txt.Format(_T("%-.3f%s,%-.3fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	case 4:
		txt.Format(_T("%-.4f%s,%-.4fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	case 5:
		txt.Format(_T("%-.5f%s,%-.5fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	case 6:
		txt.Format(_T("%-.6f%s,%-.6fdeg"),fMeasureLength,strUnit, dAngle*RAD2DEG);
		break;
	}

	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,m_fptCurPos.x,m_fptCurPos.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif

		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);

		if(fptCenter.x>fptCur.x && fptCenter.y>fptCur.y)
		{
			fptOffset.x = fCanvasResolution*5;
			fptOffset.y = 0.0f;
		}
		else if(fptCenter.x<fptCur.x && fptCenter.y>fptCur.y)
		{
			fptOffset.x = -fWidth*0.95-fCanvasResolution*5;
			fptOffset.y = 0.0f;
		}
		else if(fptCenter.x>fptCur.x && fptCenter.y<fptCur.y)
		{
			fptOffset.x = fCanvasResolution*5;
			fptOffset.y = -fHeight;
		}
		else 
		{
			fptOffset.x = -fWidth*0.95-fCanvasResolution*5;
			fptOffset.y = -fHeight;
		}
		m_GLDraw.DrawRect(tagdPOINT(fptCur.x+fptOffset.x,fptCur.y+fptOffset.y+fLowerPartHeight),tagdPOINT(fptCur.x+fWidth*0.95+fptOffset.x,fptCur.y+fptOffset.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawLine(fptRef,fptCur,1,FALSE);
		m_GLDraw.DrawPoint(fptRef,5);
		m_GLDraw.DrawPoint(fptCur);

		glPushMatrix();
		glTranslatef(fptCur.x+fptOffset.x,fptCur.y+fptOffset.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
			
		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
	
}
void COpenGLView::DrawImageDistSub(CdPoint3D fptRef,CdPoint3D fptCur)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	CString txt, strWidthUnit, strHeightUnit;
	CString strBuf;
	double fWidth,fHeight;
	CdPoint3D fptLeft,fptRight;
	if(fptRef.x>fptCur.x)
	{
		fWidth = fptRef.x-fptCur.x;
	}
	else
	{
		fWidth = fptCur.x-fptRef.x;
	}
	if(fptRef.y>fptCur.y)
	{
		fHeight = fptRef.y-fptCur.y;
	}
	else
	{
		fHeight = fptCur.y-fptRef.y;
	}
	fptLeft.x = fptRef.x - fWidth;
	fptLeft.y = fptRef.y - fHeight;
	fptLeft.z = 0.0;
	fptRight.x = fptRef.x + fWidth;
	fptRight.y = fptRef.y + fHeight;
	fptRight.z = 0.0;
	fWidth *= 2.0f;
	fHeight *= 2.0f;

	if(!m_bDisplayMetricUnit)
	{
		fWidth = fWidth / 25.4;
		fHeight = fHeight / 25.4;
		strWidthUnit = _T("Inch");
		strHeightUnit = _T("Inch");
	}
	else
	{
		if(fWidth<1)
		{
			fWidth *= 1000.0;
			strWidthUnit = _T("um");
		}
		else
			strWidthUnit = _T("mm");

		if(fHeight<1)
		{
			fHeight *= 1000.0;
			strHeightUnit = _T("um");
		}
		else
			strHeightUnit = _T("mm");
	}

	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("W: %-.f%s ,H: %-.f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 1:
		txt.Format(_T("W: %-.1f%s ,H: %-.1f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 2:
		txt.Format(_T("W: %-.2f%s ,H: %-.2f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 3:
		txt.Format(_T("W: %-.3f%s ,H: %-.3f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 4:
		txt.Format(_T("W: %-.4f%s ,H: %-.4f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 5:
		txt.Format(_T("W: %-.5f%s ,H: %-.5f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 6:
		txt.Format(_T("W: %-.6f%s ,H: %-.6f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	}


	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,m_fptCurPos.x,m_fptCurPos.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		  char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);
		m_GLDraw.DrawRect(tagdPOINT(fptCur.x,fptCur.y+fLowerPartHeight),tagdPOINT(fptCur.x+fWidth*0.95,fptCur.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawRect(fptLeft,fptRight,0,FALSE);
		m_GLDraw.DrawPoint(fptRef,5);
		glPushMatrix();
		glTranslatef(fptCur.x,fptCur.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
			
		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
}
void COpenGLView::DrawImageDist(CdPoint3D fptRef,CdPoint3D fptCur)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	CString txt, strWidthUnit, strHeightUnit;
	CString strBuf;
	double fWidth,fHeight;
	CdPoint3D fptLeft,fptRight;
	AdjustCoordinate(fptRef,fptCur);
	if(fptRef.x>fptCur.x)
	{
		fWidth = fptRef.x-fptCur.x;
	}
	else
	{
		fWidth = fptCur.x-fptRef.x;
	}
	if(fptRef.y>fptCur.y)
	{
		fHeight = fptRef.y-fptCur.y;
	}
	else
	{
		fHeight = fptCur.y-fptRef.y;
	}
	fptLeft.x = fptRef.x ;
	fptLeft.y = fptRef.y ;
	fptLeft.z = 0.0;
	fptRight.x = fptCur.x ;
	fptRight.y = fptCur.y ;
	fptRight.z = 0.0;

	if(!m_bDisplayMetricUnit)
	{
		fWidth = fWidth / 25.4;
		fHeight = fHeight / 25.4;
		strWidthUnit = _T("Inch");
		strHeightUnit = _T("Inch");
	}
	else
	{
		if(fWidth<1)
		{
			fWidth *= 1000.0;
			strWidthUnit = _T("um");
		}
		else
			strWidthUnit = _T("mm");

		if(fHeight<1)
		{
			fHeight *= 1000.0;
			strHeightUnit = _T("um");
		}
		else
			strHeightUnit = _T("mm");
	}

	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("W: %-.f%s ,H: %-.f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 1:
		txt.Format(_T("W: %-.1f%s ,H: %-.1f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 2:
		txt.Format(_T("W: %-.2f%s ,H: %-.2f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 3:
		txt.Format(_T("W: %-.3f%s ,H: %-.3f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 4:
		txt.Format(_T("W: %-.4f%s ,H: %-.4f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 5:
		txt.Format(_T("W: %-.5f%s ,H: %-.5f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 6:
		txt.Format(_T("W: %-.6f%s ,H: %-.6f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	}

	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,m_fptCurPos.x,m_fptCurPos.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		  char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);
		m_GLDraw.DrawRect(tagdPOINT(fptCur.x,fptCur.y+fLowerPartHeight),tagdPOINT(fptCur.x+fWidth*0.95,fptCur.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawRect(fptLeft,fptRight,0,FALSE);
		m_GLDraw.DrawPoint(fptRef,5);
		glPushMatrix();
		glTranslatef(fptCur.x,fptCur.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
			
		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
}
void COpenGLView::DrawFindNominalLine(CdPoint3D fptRef,CdPoint3D fptCur)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	CString txt, strWidthUnit, strHeightUnit;
	CString strBuf;
	double fWidth,fHeight;
	CdPoint3D fptLeft,fptRight;
	AdjustCoordinate(fptRef,fptCur);
	if(fptRef.x>fptCur.x)
	{
		fWidth = fptRef.x-fptCur.x;
	}
	else
	{
		fWidth = fptCur.x-fptRef.x;
	}
	if(fptRef.y>fptCur.y)
	{
		fHeight = fptRef.y-fptCur.y;
	}
	else
	{
		fHeight = fptCur.y-fptRef.y;
	}
	fptLeft.x = fptRef.x ;
	fptLeft.y = fptRef.y ;
	fptLeft.z = 0.0;
	fptRight.x = fptCur.x ;
	fptRight.y = fptCur.y ;
	fptRight.z = 0.0;

	if(!m_bDisplayMetricUnit)
	{
		fWidth = fWidth / 25.4;
		fHeight = fHeight / 25.4;
		strWidthUnit = _T("Inch");
		strHeightUnit = _T("Inch");
	}
	else
	{
		if(fWidth<1)
		{
			fWidth *= 1000.0;
			strWidthUnit = _T("um");
		}
		else
			strWidthUnit = _T("mm");

		if(fHeight<1)
		{
			fHeight *= 1000.0;
			strHeightUnit = _T("um");
		}
		else
			strHeightUnit = _T("mm");
	}

	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("W: %-.f%s ,H: %-.f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 1:
		txt.Format(_T("W: %-.1f%s ,H: %-.1f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 2:
		txt.Format(_T("W: %-.2f%s ,H: %-.2f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 3:
		txt.Format(_T("W: %-.3f%s ,H: %-.3f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 4:
		txt.Format(_T("W: %-.4f%s ,H: %-.4f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 5:
		txt.Format(_T("W: %-.5f%s ,H: %-.5f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 6:
		txt.Format(_T("W: %-.6f%s ,H: %-.6f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	}

	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,m_fptCurPos.x,m_fptCurPos.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		  char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif

		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);
		m_GLDraw.DrawRect(tagdPOINT(fptCur.x,fptCur.y+fLowerPartHeight),tagdPOINT(fptCur.x+fWidth*0.95,fptCur.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawRect(fptLeft,fptRight,0,FALSE);

		glPushMatrix();
		glTranslatef(fptCur.x,fptCur.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
		glPopMatrix();//vecText[i].bLine
	}
}
void COpenGLView::DrawImageSave(CdPoint3D fptRef,CdPoint3D fptCur)
{
	GLfloat fCanvasResolution= GetCanvasPixelResolution();
	CString txt, strWidthUnit, strHeightUnit;
	CString strBuf;
	double fWidth,fHeight;
	if(fptRef.x>fptCur.x)
	{
		fWidth = fptRef.x-fptCur.x;
	}
	else
	{
		fWidth = fptCur.x-fptRef.x;
	}
	if(fptRef.y>fptCur.y)
	{
		fHeight = fptRef.y-fptCur.y;
	}
	else
	{
		fHeight = fptCur.y-fptRef.y;
	}

	if(!m_bDisplayMetricUnit)
	{
		fWidth = fWidth / 25.4;
		fHeight = fHeight / 25.4;
		strWidthUnit = _T("Inch");
		strHeightUnit = _T("Inch");
	}
	else
	{
		if(fWidth<1)
		{
			fWidth *= 1000.0;
			strWidthUnit = _T("um");
		}
		else
			strWidthUnit = _T("mm");

		if(fHeight<1)
		{
			fHeight *= 1000.0;
			strHeightUnit = _T("um");
		}
		else
			strHeightUnit = _T("mm");
	}

	switch(m_nDisplayDecimalNum)
	{
	case 0:
		txt.Format(_T("W: %-.f%s ,H: %-.f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 1:
		txt.Format(_T("W: %-.1f%s ,H: %-.1f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 2:
		txt.Format(_T("W: %-.2f%s ,H: %-.2f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 3:
		txt.Format(_T("W: %-.3f%s ,H: %-.3f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 4:
		txt.Format(_T("W: %-.4f%s ,H: %-.4f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 5:
		txt.Format(_T("W: %-.5f%s ,H: %-.5f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	case 6:
		txt.Format(_T("W: %-.6f%s ,H: %-.6f%s"),fWidth, strWidthUnit, fHeight, strHeightUnit);
		break;
	}


	if(m_strFontName.IsEmpty())
	{
		double fFontSize = fCanvasResolution* 40 / 199.0;
		m_GLDraw.DrawText(txt,m_fptCurPos.x,m_fptCurPos.y,0.0f,fFontSize,2,RED);
	}
	else
	{
#ifdef _UNICODE
		  char * chText = StringToChar(txt);	
#else

		char *chText = txt.GetBuffer(0);
#endif
		double dScale = fCanvasResolution*m_fFontSize / 144.0;
		double fWidth,fHeight,fLowerPartHeight;
		glColor4f(GetRValue(m_crFontBackColor)/255.0,GetGValue(m_crFontBackColor)/255.0,GetBValue(m_crFontBackColor)/255.0,1.0);
		m_GLDraw.GetFontSize((unsigned char *)chText,fWidth,fHeight,fLowerPartHeight,FONTSCALE*dScale);
		m_GLDraw.DrawRect(tagdPOINT(fptCur.x,fptCur.y+fLowerPartHeight),tagdPOINT(fptCur.x+fWidth*0.95,fptCur.y+fHeight));

		glColor4f(GetRValue(m_crFontColor)/255.0,GetGValue(m_crFontColor)/255.0,GetBValue(m_crFontColor)/255.0,1.0);
		m_GLDraw.DrawRect(fptRef,fptCur,0,FALSE);
		m_GLDraw.DrawPoint(fptRef,5);
		glPushMatrix();
		glTranslatef(fptCur.x,fptCur.y, 0);
		glScalef(dScale, dScale, 1);
		m_GLDraw.DrawBMPFont(chText);
			
		glPopMatrix();//vecText[i].bLine
#ifdef _UNICODE
		delete chText;
		chText = NULL;
#endif
	}
}

void COpenGLView::SetDisplayGeneral(BOOL bUnit, int nDecimal)
{
	m_bDisplayMetricUnit = bUnit;
	m_nDisplayDecimalNum = nDecimal;
}

void COpenGLView::AddCuttingMask(unsigned char *pDataImage, int nPixelWidth, int nPixelHeight, int nCuttingWidth)
{
	if (pDataImage)
	{
		int startx = nPixelWidth / 2 - 1;
		int starty = nPixelHeight / 2 - 1;
		int num;
		int maxdistance = 512;
		int maximum = maxdistance;
		int distance[8];
		int sizex = nPixelWidth, sizey = nPixelHeight;
		int nThres = 128;

		int x = startx;
		int y = starty;
		if (pDataImage[x + y*sizex] < nThres)
		{
			return;
		}
		for (int i = 0; i < 8; i++)
		{
			distance[i] = maxdistance;
		}
		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[0] = num;
				break;
			}
			x = startx;
			y = starty - num;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[0] = num;
				break;
			}
		}
		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[1] = num;
				break;
			}
			x = startx;
			y = starty + num;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[1] = num;
				break;
			}
		}
		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////
		//2시 방향
		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[2] = (int)(((float)(num)) * 1.414);
				break;
			}
			x = startx + num;
			y = starty - num;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[2] = (int)(((float)(num)) * 1.414);
				break;
			}
		}

		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[3] = (int)(((float)(num)) * 1.414);
				break;
			}
			x = startx - num;
			y = starty + num;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[3] = (int)(((float)(num)) * 1.414);
				break;
			}
		}

		////////////////////////////////////////////////////////////////
		//3시 방향
		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[4] = num;
				break;
			}
			x = startx + num;
			y = starty;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[4] = num;
				break;
			}
		}

		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[5] = num;
				break;
			}
			x = startx - num;
			y = starty;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[5] = num;
				break;
			}
		}

		////////////////////////////////////////////////////////////////
		//5시 방향
		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[6] = (int)(((float)(num)) * 1.414);
				break;
			}
			x = startx + num;
			y = starty + num;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[6] = (int)(((float)(num)) * 1.414);
				break;
			}
		}
		for (num = 1; num < maximum; num++)
		{
			if (num >= maxdistance)//현재까지 크기보다 크거나 같으면 패스
			{
				distance[7] = (int)(((float)(num)) * 1.414);
				break;
			}
			x = startx - num;
			y = starty - num;
			if (pDataImage[x + y*sizex] < nThres)
			{
				distance[7] = (int)(((float)(num)) * 1.414);
				break;
			}
		}
		int nDir = 0;
		int nMinDistance = distance[0]+ distance[1];
		int nDistance;
		for (int i = 1; i < 4; i++)
		{
			nDistance = distance[i * 2 + 1]+distance[i * 2];
			if (nMinDistance > nDistance)
			{
				nDir = i;
				nMinDistance = nDistance;
			}
		}
		int nWidth = nCuttingWidth / 2;
		int nMargin = nMinDistance / 10;
		int nStartY;
		switch (nDir)
		{
		case 0://12,6
			for (x = startx - nWidth; x < startx + nWidth; x++)
			{
				for (y = starty - distance[0] - nMargin; y < starty + distance[1] + nMargin; y++)
				{
					pDataImage[x + y*sizex] = 0;
				}
			}
			break;
		case 1://2,7
			nStartY = starty + (-distance[0] + distance[1]) / 2;
			for (x = startx - nWidth; x < startx + nWidth; x++)
			{
				for (y = nStartY - nWidth - nMargin; y < nStartY + nWidth + nMargin; y++)
				{
					pDataImage[x + y*sizex] = 0;
				}
			}
			break;
		case 2://3,9
			for (x = startx - distance[5] - nMargin; x < startx + distance[4] + nMargin; x++)
			{
				for (y = starty - nWidth; y < starty + nWidth; y++)
				{
					pDataImage[x + y*sizex] = 0;
				}
			}
			break;
		case 3://5,10
			nStartY = starty + (-distance[0] + distance[1]) / 2;
			for (x = startx - nWidth; x < startx + nWidth; x++)
			{
				for (y = nStartY - nWidth - nMargin; y < nStartY + nWidth + nMargin; y++)
				{
					pDataImage[x + y*sizex] = 0;
				}
			}
			break;
		}
		
	}
}

char* COpenGLView::StringToChar(CString str)
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