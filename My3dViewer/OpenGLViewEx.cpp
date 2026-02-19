#include "StdAfx.h"
#include "OpenGLViewEx.h"
#include "AutoVariableControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL COpenGLViewEx::DispAlloc(int nResourceID,CWnd* pParent,COLORREF cBackGroundColor,BOOL bSetMouse)
{

	CRect sizeR;
	pParent->GetDlgItem(nResourceID)->GetClientRect(sizeR);
	int m_nViewSizeX=sizeR.right;
	int m_nViewSizeY=sizeR.bottom;
	
	pParent->GetDlgItem(nResourceID)->GetWindowRect(&sizeR);
	pParent->ScreenToClient(sizeR);
	this->Create(NULL,NULL,WS_OVERLAPPED|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE ,sizeR,pParent,nResourceID,NULL);
	SetBackGroundColor(cBackGroundColor);
	SetCoordinate(nResourceID,pParent,CdSize(m_nViewSizeX,m_nViewSizeY),CdPoint(0,0));
/*
	if(bSetMouse)
		SetMouseCurser();
*/
	return TRUE;
}

BOOL COpenGLViewEx::DispFree()
{
	m_bViewActionPause=TRUE;
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);

	delete this;

	return TRUE;
}


/////////LGH FUNCTION

COpenGLViewEx::COpenGLViewEx()
{
	m_bAdjustCoordinate=FALSE;
	m_bDisableAutoRender=TRUE;
	m_fMaxZoom=64.0;
	m_EventRenderSync.ResetEvent();
}

COpenGLViewEx::~COpenGLViewEx()
{
	m_ptCurPos.x=0;
	m_ptCurPos.y=0;
}

void COpenGLViewEx::DrawResume()
{	
	m_bPickArrayMode=bOldPickStatus;
	m_EventRenderSync.ResetEvent();
	m_bViewActionPause=FALSE;
}

void COpenGLViewEx::GetAbsolutePosition(CdRect& frtExtent,float& fX,float& fY,float& fZ)
{
	float cx,cy,cz;
	GetCamPos(cx,cy,cz);

	fX = -cx - (fabs((frtExtent.right-frtExtent.left)*1.98)/2.0);
	fY = -cy + (fabs((frtExtent.bottom-frtExtent.top)*1.98)/2.0);
	fZ = cz;
}

void COpenGLViewEx::GetAbsoluteRegion(CdRect& frtExtent,float& fSizeX,float& fSizeY,float& fRatioX,float& fRatioY)
{
	fSizeX = fabs((frtExtent.right-frtExtent.left))*1.98;
	fSizeY = fabs((frtExtent.bottom-frtExtent.top))*1.98;
	fRatioX=fRatioX=(fSizeX/(m_sizeWindow.cx+10));
	fRatioY=fRatioY=(fSizeY/(m_sizeWindow.cy+10));
}

void COpenGLViewEx::SetCamPos(GLfloat x,GLfloat y)
{
	m_fptCamPos.x = -x;
	m_fptCamPos.y = -y;
//	m_fptCamPos.z=0;
}

void COpenGLViewEx::SetHistogramCount(int nCnt,CdPoint3D fHistoStartP,CdPoint3D fHistoEndP)
{
	if(nCnt>4)
	{
		nCnt =4;
	}
	m_HistoCnt=nCnt;

	if(nCnt==1)
	{
		for(int i=0; i<4; i++)
		{
			m_HistoRegion[i].fStart.x=fHistoStartP.x;
			m_HistoRegion[i].fStart.y=fHistoStartP.y;
			m_HistoRegion[i].fStart.z=fHistoStartP.z;
			m_HistoRegion[i].fEnd.x=fHistoEndP.x;
			m_HistoRegion[i].fEnd.y=fHistoEndP.y;
			m_HistoRegion[i].fEnd.z=fHistoEndP.z;
		}
	}
	else if(nCnt==2)
	{	int i;
		for( i=0; i<4; i+=2)
		{
			m_HistoRegion[i].fStart.x=fHistoStartP.x+150;
			m_HistoRegion[i].fStart.y=fHistoStartP.y;
			m_HistoRegion[i].fStart.z=fHistoStartP.z;
			m_HistoRegion[i].fEnd.x=(fHistoEndP.x/2);
			m_HistoRegion[i].fEnd.y=fHistoEndP.y;
			m_HistoRegion[i].fEnd.z=fHistoEndP.z;
		}
		for(i=1; i<4; i+=2)
		{
			m_HistoRegion[i].fStart.x=(fHistoEndP.x/2)+150;
			m_HistoRegion[i].fStart.y=fHistoStartP.y;
			m_HistoRegion[i].fStart.z=fHistoStartP.z;
			m_HistoRegion[i].fEnd.x=fHistoEndP.x;
			m_HistoRegion[i].fEnd.y=fHistoEndP.y;
			m_HistoRegion[i].fEnd.z=fHistoEndP.z;
		}

	}
	else if(nCnt==3)
	{
		int i;
		for( i=0; i<4; i+=2)
		{
			m_HistoRegion[i].fStart.x=fHistoStartP.x;
			m_HistoRegion[i].fStart.y=fHistoStartP.y;
			m_HistoRegion[i].fStart.z=fHistoStartP.z;
			m_HistoRegion[i].fEnd.x=fHistoEndP.x;
			m_HistoRegion[i].fEnd.y=(fHistoEndP.y/2)-50;
			m_HistoRegion[i].fEnd.z=fHistoEndP.z;
		}
		for(i=1; i<4; i+=2)
		{
			m_HistoRegion[i].fStart.x=fHistoStartP.x;
			m_HistoRegion[i].fStart.y=(fHistoEndP.y/2)+50;
			m_HistoRegion[i].fStart.z=fHistoStartP.z;
			m_HistoRegion[i].fEnd.x=fHistoEndP.x;
			m_HistoRegion[i].fEnd.y=fHistoEndP.y;
			m_HistoRegion[i].fEnd.z=fHistoEndP.z;
		}
	}
	else if(nCnt==4)
	{
		m_HistoRegion[0].fStart.x=fHistoStartP.x+150;
		m_HistoRegion[0].fStart.y=fHistoStartP.y;
		m_HistoRegion[0].fStart.z=fHistoStartP.z;
		m_HistoRegion[0].fEnd.x=(fHistoEndP.x/2);
		m_HistoRegion[0].fEnd.y=(fHistoEndP.y/2)-50;
		m_HistoRegion[0].fEnd.z=fHistoEndP.z;

		m_HistoRegion[1].fStart.x=(fHistoEndP.x/2)+150;
		m_HistoRegion[1].fStart.y=fHistoStartP.y;
		m_HistoRegion[1].fStart.z=fHistoStartP.z;
		m_HistoRegion[1].fEnd.x=fHistoEndP.x;
		m_HistoRegion[1].fEnd.y=(fHistoEndP.y/2)-50;
		m_HistoRegion[1].fEnd.z=fHistoEndP.z;

		m_HistoRegion[2].fStart.x=fHistoStartP.x+150;
		m_HistoRegion[2].fStart.y=(fHistoEndP.y/2)+50;
		m_HistoRegion[2].fStart.z=fHistoStartP.z;
		m_HistoRegion[2].fEnd.x=(fHistoEndP.x/2);
		m_HistoRegion[2].fEnd.y=fHistoEndP.y;
		m_HistoRegion[2].fEnd.z=fHistoEndP.z;

		m_HistoRegion[3].fStart.x=(fHistoEndP.x/2)+150;
		m_HistoRegion[3].fStart.y=(fHistoEndP.y/2)+50;
		m_HistoRegion[3].fStart.z=fHistoStartP.z;
		m_HistoRegion[3].fEnd.x=fHistoEndP.x;
		m_HistoRegion[3].fEnd.y=fHistoEndP.y;
		m_HistoRegion[3].fEnd.z=fHistoEndP.z;
	
	}
}

//160211 lgh add
BOOL COpenGLViewEx::SetCoordinate(CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset)
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

	m_fptOriginCamPos.x=m_fptCamPos.x;
	m_fptOriginCamPos.y=m_fptCamPos.y;
	m_fptOriginCamPos.z=m_fptCamPos.z;

	m_OriginWorldPos[0]=GetExtentStartPos();
	m_OriginWorldPos[1]=GetExtentEndPos();

	return m_bReady;
}


//AOI Function..
BOOL COpenGLViewEx::SetCoordinate(int nDlgId, CWnd *Dlg,CdSize fSize, CdPoint fptStart, CdPoint fptOffset)
{
	m_bDrawFirst = TRUE;
	CAutoBool Auto(&m_bAdjustCoordinate);
	CRect rect;

	m_fptCamPos.x=0.0f;
	m_fptCamPos.y=0.0f;
	m_fptCamPos.z=0.0f;
	m_fptCamAngle.x=0.0f;
	m_fptCamAngle.y=0.0f;
	m_fptCamAngle.z=0.0f;

	Dlg->GetDlgItem(nDlgId)->GetClientRect(rect);
	m_sizeWindow.cx=rect.right;
	m_sizeWindow.cy=rect.bottom;
	Dlg->GetDlgItem(nDlgId)->GetWindowRect(rect);
	Dlg->ScreenToClient(rect);
	m_WindowSPointX=rect.left;
	m_WindowSPointY=rect.top;
	

	m_nHandleID=nDlgId;

	m_frtWorld.left=fptStart.x;
	m_frtWorld.bottom=fptStart.y;
	m_frtWorld.right=fSize.cx+m_frtWorld.left;
	m_frtWorld.top=fSize.cy+m_frtWorld.bottom;

	m_fptOffset.x = fptOffset.x;
	m_fptOffset.y = fptOffset.y;
	
	if((m_frtWorld.left== 0.0 && m_frtWorld.right== 0.0) ||  (m_frtWorld.top == 0.0 && m_frtWorld.bottom == 0.0))
	{
		m_frtWorld.bottom = 100.0;
		m_frtWorld.right = 100.0;
	}

	if(FitToScreen())
	{
		m_bReady = TRUE;
	}
	else
	{
		AfxMessageBox(_T("Error at fit to screen"));
		m_bReady = FALSE;
	}

	m_fptOriginCamPos.x=m_fptCamPos.x;
	m_fptOriginCamPos.y=m_fptCamPos.y;
	m_fptOriginCamPos.z=m_fptCamPos.z;

	m_OriginWorldPos[0]=GetExtentStartPos();
	m_OriginWorldPos[1]=GetExtentEndPos();

	return m_bReady;
}

BOOL COpenGLViewEx::SetCoordinate(UINT nID, CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset)
{
	m_bDrawFirst = TRUE;
	CRect rect;

	m_fptCamPos.x=0.0;
	m_fptCamPos.y=0.0;
	m_fptCamPos.z=0.0;
	m_fptCamAngle.x=0.0f;
	m_fptCamAngle.y=0.0f;
	m_fptCamAngle.z=0.0f;
	m_nHandleID=nID;

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

	m_fptOriginCamPos.x=m_fptCamPos.x;
	m_fptOriginCamPos.y=m_fptCamPos.y;
	m_fptOriginCamPos.z=m_fptCamPos.z;

	m_OriginWorldPos[0]=GetExtentStartPos();
	m_OriginWorldPos[1]=GetExtentEndPos();

	return m_bReady;
}
void COpenGLViewEx::SetCoordinate(UINT nID,int nWidth,int nHeight, CdPoint fptStart, CdPoint fptOffset)
{
	m_bDrawFirst = TRUE;
	CRect rect;
	CAutoBool Auto(&m_bAdjustCoordinate);
	m_fptCamPos.x=0.0f;
	m_fptCamPos.y=0.0f;
	m_fptCamPos.z=0.0f;
	m_fptCamAngle.x=0.0f;
	m_fptCamAngle.y=0.0f;
	m_fptCamAngle.z=0.0f;

	m_sizeWindow.cx=nWidth;
	m_sizeWindow.cy=nHeight;
	m_WindowSPointX=0;
	m_WindowSPointY=0;
	m_nHandleID=nID;

	m_frtWorld.left=fptStart.x;
	m_frtWorld.bottom=fptStart.y;
	m_frtWorld.right=nWidth+m_frtWorld.left;
	m_frtWorld.top=nHeight+m_frtWorld.bottom;

	m_fptOffset.x = fptOffset.x;
	m_fptOffset.y = fptOffset.y;


	if(FitToScreen())
	{
		m_bReady = TRUE;
	}
	else
	{
		AfxMessageBox(_T("Error at fit to screen"));
		m_bReady = FALSE;
	}

	m_fptOriginCamPos.x=m_fptCamPos.x;
	m_fptOriginCamPos.y=m_fptCamPos.y;
	m_fptOriginCamPos.z=m_fptCamPos.z;

	m_OriginWorldPos[0]=GetExtentStartPos();
	m_OriginWorldPos[1]=GetExtentEndPos();
}

void COpenGLViewEx::GetCamPos(float& x,float& y,float& z)
{
	x=m_fptCamPos.x;
	y=m_fptCamPos.y;
	z=m_fptCamPos.z;
}

void COpenGLViewEx::SetMaxZoom(float fZoom)
{
	m_fMaxZoom=max((float)0.25,fZoom);
}

GLfloat COpenGLViewEx::GetZoomRatio()
{
	GLfloat fRatio;

	if(m_fptCamPos.z!=0.0)
		fRatio = m_fptOriginCamPos.z/m_fptCamPos.z;
	else
		fRatio = 1.0;
	
	return fRatio;
}

DWORD COpenGLViewEx::WaitForRenderEnd(DWORD TimeOut)
{
	return WaitForSingleObject(m_EventRenderSync.m_hObject,TimeOut);
}
	
void COpenGLViewEx::DrawEnd()
{
	m_EventRenderSync.ResetEvent();
	m_EventRenderSync.SetEvent();
}

void COpenGLViewEx::SetCoordinateWorld()
{
	glTranslatef(-m_fptCamPos.x,-m_fptCamPos.y,0);
}

void COpenGLViewEx::RestoreCoordinateWorld()
{
	glTranslatef(m_fptCamPos.x,m_fptCamPos.y,0);
}

void COpenGLViewEx::DrawPause(DWORD TimeOut)
{	
	CString strdata;

	bOldPickStatus = m_bPickArrayMode;
	m_bViewActionPause=TRUE;
	if(m_bPickArrayMode==TRUE)
	m_bPickArrayMode=FALSE;

	DWORD Status = WaitForRenderEnd(TimeOut);
	
	switch(Status)
	{
		case WAIT_OBJECT_0:
		m_EventRenderSync.ResetEvent();
		break;
		
		default:
		Status = WaitForRenderEnd(TimeOut);
		if(Status == WAIT_OBJECT_0)
		m_EventRenderSync.ResetEvent();
		else
		{
			strdata.Format(_T("Render ID:%d , Rendering... Time Out"),m_nHandleID);
			m_EventRenderSync.ResetEvent();
			::AfxMessageBox(strdata);
		}
		break;
	}
}


void COpenGLViewEx::RectFitScreen(CdPoint3D fStartPoint, CdPoint3D fEndPoint)
{
	CdRect rectWorld;
	rectWorld.left=fStartPoint.x;
	rectWorld.bottom=fStartPoint.y;
	rectWorld.right=fEndPoint.x;
	rectWorld.top=fEndPoint.y;

	BOOL bFitScreen=FitToScreen(rectWorld,m_fFitSpace);

	if(bFitScreen==TRUE)
	{
		this->Invalidate();
		AddHistory(OPEN_GL::RECT_FIT);
	}

}

void COpenGLViewEx::RectFitScreen(CdPoint3D fCenterPoint, DOUBLE fSize)
{
	CdRect rectWorld;
	DOUBLE fHalfSize=fSize/2;

	rectWorld.left=fCenterPoint.x-fHalfSize;
	rectWorld.bottom=fCenterPoint.y-fHalfSize;
	rectWorld.right=fCenterPoint.x+fHalfSize;
	rectWorld.top=fCenterPoint.y+fHalfSize;

	BOOL bFitScreen=FitToScreen(rectWorld,m_fFitSpace);

	if(bFitScreen==TRUE)
	{
		this->Invalidate();
		AddHistory(OPEN_GL::RECT_FIT);
	}
}

void COpenGLViewEx::RectFitScreen(CdPoint fCenterPoint, DOUBLE fSize)
{
	CdRect rectWorld;
	DOUBLE fHalfSize=fSize/2.0;

	rectWorld.left=fCenterPoint.x-fHalfSize;
	rectWorld.bottom=fCenterPoint.y-fHalfSize;
	rectWorld.right=fCenterPoint.x+fHalfSize;
	rectWorld.top=fCenterPoint.y+fHalfSize;

	BOOL bFitScreen=FitToScreen(rectWorld,m_fFitSpace);


	if(bFitScreen==TRUE)
	{
		this->Invalidate();
		//GLRenderScene();
		AddHistory(OPEN_GL::RECT_FIT);
	}
}


void COpenGLViewEx::MakeCurrent()
{
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
}

void COpenGLViewEx::SetZoomRatio(float fZoom)
{
	m_fptCamPos.z = m_fptOriginCamPos.z / fZoom;
}

void COpenGLViewEx::SetCamPos(CdPoint3D fptCamPos)
{
	m_fptCamPos = fptCamPos;
}
CdPoint3D COpenGLViewEx::GetCamPos()
{
	return m_fptCamPos;
}