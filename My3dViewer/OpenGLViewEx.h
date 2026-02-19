#pragma once

#ifndef _OPENGLVIEW_
#define _OPENGLVIEW_

#include "GeoDataType.h"
#include "OpenGLView.h"

struct RectRegion
{
	CdPoint3D fStart;
	CdPoint3D fEnd;
};

class COpenGLViewEx : public COpenGLView
{
	public:
	CdPoint3D m_OriginWorldPos[2];
	CdPoint3D m_PrevWorldPos[2];
	BOOL m_bAdjustCoordinate;
	COpenGLViewEx();
	virtual ~COpenGLViewEx();
	
	public:
	BOOL DispAlloc(int nResourceID,CWnd* pParent,COLORREF cBackGroundColor=RGB(0,0,0),BOOL bSetMouse=TRUE);
	BOOL DispFree();
	float m_fMaxZoom;
	RectRegion m_HistoRegion[4];
	BOOL m_bDisableAutoRender;
	CdPoint3D m_fptOriginCamPos;
	BOOL m_bViewActionPause;
	CEvent m_EventRenderSync;
	int m_HistoCnt;
	int m_WindowSPointX;
	int m_WindowSPointY;

	public:
	int m_nFontHeight;
	//140821 lgh do not delete please
	// AOI & GENA Function
	void SetZoomRatio(float fZoom);
	void GetAbsolutePosition(CdRect& frtExtent,float& fX,float& fY,float& fZ);
	void GetAbsoluteRegion(CdRect& frtExtent,float& fSizeX,float& fSizeY,float& fRatioX,float& fRatioY);

	BOOL SetCoordinate(UINT nID, CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset);
	void SetCoordinate(UINT nID,int nWidth,int nHeight, CdPoint fptStart, CdPoint fptOffset);

	virtual BOOL SetCoordinate(int nDlgId, CWnd *Dlg,CdSize fSize, CdPoint fptStart=CdPoint(0,0), CdPoint fptOffset=CdPoint(0,0));
	virtual BOOL SetCoordinate(CdSize fWorldSize, CdPoint fptStart, CdPoint fptOffset=CdPoint(0,0));


	void SetHistogramCount(int nCnt,CdPoint3D fHistoStartP,CdPoint3D fHistoEndP);
	void SetCoordinateWorld();
	void RestoreCoordinateWorld();
	GLfloat GetZoomRatio();
	void DrawPause(DWORD TimeOut);
	void DrawResume();
	DWORD WaitForRenderEnd(DWORD TimeOut);
	void DrawEnd();

	void SetMaxZoom(float fZoom);
	void RectFitScreen(CdPoint3D fStartPoint, CdPoint3D fEndPoint);
	void RectFitScreen(CdPoint3D fCenterPoint, DOUBLE fSize);
	void RectFitScreen(CdPoint fCenterPoint, DOUBLE fSize);
	// END
	void MakeCurrent();
	//RenderScene

	virtual CdPoint3D GetCamPos();
	virtual void SetCamPos(CdPoint3D fptCamPos);

	void SetCamPos(GLfloat x,GLfloat y);//140820 lgh re add
	void GetCamPos(float& x,float& y,float& z);
};

#endif