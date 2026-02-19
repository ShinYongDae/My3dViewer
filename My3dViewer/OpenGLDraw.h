// OpenGLDraw.h: interface for the COpenGLDraw class.
//
//////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
////                          OpenGLDraw.h Ver 2.0                                 ////
////                             Developer: CAM PART                               ////
////                               Corp   : GIGAVIS                                ////
////																			   ////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLDRAW_H__876EE1DF_5B8E_4297_93C8_B8A7FE8D4B72__INCLUDED_)
#define AFX_OPENGLDRAW_H__876EE1DF_5B8E_4297_93C8_B8A7FE8D4B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGLFontCam.h"
#include "GeoDataType.h"
#include "ColorTable.h"
#include <vector>
using namespace std;

#define STENCIL_CLEAR 0
#define STENCIL_DARK 1
#define STENCIL_NORMAL 2

class COpenGLDraw : public GInterPolation, public COpenGLFontCam
{
private:
	int     m_nDrawMinArcVertex;
	GLfloat m_fDrawResolution;
	vector <DPOINT> m_vecVertices;

public:
	COpenGLDraw();
	virtual ~COpenGLDraw();

	void GetArcVertices(vector<DPOINT> &vecPt,const DPOINT &ptCenter,GLfloat radius,GLfloat start_angle, GLfloat arc_angle,int dir);
	void GetArcVertices(vector<DPOINT> &vecPt,double fSx, double fSy, double fEx, double fEy, double fCx, double fCy, int nDir);
	void GetEllipseVertices(vector<DPOINT> &vecPt,double fCx, double fCy, double fWidth, double fHeight);
	void GetPolygonArcVertices(vector<DPOINT> &vecPt, const DPOINT &ptCenter, double radius, double start_angle, double arc_angle, int dir);

	int  GetArcSegment(double fRadius,double fAngle=360.0);
	double GetDrawAngle(double dStartAngle,double dEndAngle ,BOOL bDir);
	void SetDrawResolution(GLfloat fResolution); // draw resolution for arc
	void SetDrawMinimumArcVertex(int nVertex);

	//void SetStencil(int nMode);
	//void ClearStencil(int nMode);

	void DrawArcDonut(DPOINT fptCenter ,double dStartAngle, double dEndAngle, double dRadius, double dWidth);
	void DrawSpline(float *knots,int nNumKnot, float *ctrlPoints, int nDeg ,int nStride = 3);
	void DrawDonut(double fCx, double fCy, double fDmo, double fDmi,BOOL bFill = TRUE);	
	//void DrawPolygonLine(const vector <ENTVERTEX> &vecPt,int nLineWidth = 0);
	void DrawPolygonLine(const DPOINT *fptVert,int nCount,int nLineWidth = 0);
	void DrawPolygonLine(const CdPoint *fptVert,int nCount,int nLineWidth = 0);
	void DrawPolygonLine(const vector <CdPoint> &vecPt,int nLineWidth = 0);
	void DrawPolygonLine(const vector <DPOINT> &vecPt,int nLineWidth = 0);
	//void DrawPolyLine(const vector<ENTVERTEX> &vecPt,int nLineWidth = 0);
	void DrawPolyLine(const vector<DPOINT> &vecPt,int nLineWidth = 0);
	void DrawPolyLine(const vector<CdPoint> &vecPt,int nLineWidth = 0);
	void DrawPolyLine(const DPOINT *fPoint,int nNumberOfVertex,int nLineWidth = 0);
	//void DrawConcavePolygon(const vector <ENTVERTEX> &fPoint);
	void DrawConcavePolygon(const vector <DPOINT> &fPoint,BOOL bFill = TRUE);
	void DrawConcavePolygon(const CdPoint *fPoint,int nNumberOfVertex,GLenum nMode = GL_TRIANGLE_FAN);
	void DrawConcavePolygon(const vector <CdPoint> &fPoint);
	void DrawConcavePolygon(const DPOINT *fPoint,int nNumberOfVertex,GLenum nMode = GL_TRIANGLE_FAN);
	void DrawConcavePolygon(const CdPoint3D *fPoint,int nNumberOfVertex);
	void DrawConcavePolygon3D(const CdPoint3D *fPoint,int nNumberOfVertex);

	void DrawConvexPolygon(const vector <CdPoint> &fPoint);
	void DrawConvexPolygon(const CdPoint *fPoint,int nNumberOfVertex);
	void DrawConvexPolygon(const vector <DPOINT> &fPoint);
	void DrawConvexPolygon(const DPOINT *fPoint,int nNumberOfVertex,BOOL bFill = TRUE);
	void DrawConvexPolygon(const CdPoint3D *fPoint,int nNumberOfVertex);


	void MyConcavePolygonPicking(vector <DPOINT> fPoint);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SetColor(COLORREF color);
	void SetColor(COLORREF crColor, double fAlpha);
	void DrawText(CString strText, GLdouble x, GLdouble y, GLdouble z=0.0f, GLdouble fFontSize=1.0f, GLfloat fLintWidth= 1.0f,COLORREF color = BLACK,int Fill=FALSE);
	// point
	void DrawPoint(const CdPoint3D &fptStart,int nPointSize=0);
	void DrawPoint(const CdPoint &fptStart,int nPointSize=0);
	void DrawPoints(const CdPoint3D *fptStart,int nCnt,int nPointSize=0);
	void DrawPoints(const vector<DPOINT> &vecPt,int nPointSize=0);
	void DrawPoints(const vector<CdPoint> &vecPt,int nPointSize = 0);
	// line
	void DrawLine(const CdPoint3D &fptStart,const CdPoint3D &fptEnd);
	void DrawLine(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2);
	void DrawLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2);
	void DrawLine(const CdPoint3D* pVtArray,int nPtNum,int Flag,double width,GLfloat Origin_Shift_X,GLfloat Origin_Shift_Y,GLfloat Origin_Shift_Z);
	void DrawLine(const CdPoint3D &fptStart,const CdPoint3D &fptEnd,int nWidth=1,int nDotted=0);
	void DrawLine(const CdPoint &fptStart,const CdPoint &fptEnd,int nWidth=1,int nDotted=0);
	void DrawLines(const CdPoint3D *fptStart,int nCnt,int nWidth=1,int nDotted=0);
	void DrawLineRound(double fSx, double fSy, double fEx, double fEy, double fLineWidth, BOOL bFill = TRUE);
	void DrawLineSquare(double fSx, double fSy, double fEx, double fEy, double fLineWidth);
	void DrawLineRect(double fSx, double fSy, double fEx, double fEy, double fLineWidth, double fLineHeight, BOOL bFill = TRUE );
	void DrawLineRect(const CdPoint &stStartVertex,const CdPoint &stEndVertex,double dLineWidth);
	// rect	
	void DrawRect(const DPOINT &fptStart,const DPOINT &fptEnd,int width=0, int fill=TRUE);
	void DrawRect(const CdPoint3D &fptStart,const CdPoint3D &fptEnd,int width=0, int fill=TRUE);
	void DrawRect(const CdRect &rect,int width = 0, int fill=TRUE);
	void DrawRect(DRECT frtRect, int width, int fill);
	void DrawRect(DRECT frtRect,BOOL bFill = FALSE);
	// quad	
	void DrawQuad(const vector<DPOINT> &vecPt,int fill=TRUE);
	void DrawQuad(const CdQuad &fQuad,int fill=TRUE);
	void DrawQuad(const DQUAD &fQuad, int fill = TRUE);
	void DrawQuad(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2,GLfloat x3, GLfloat y3,GLfloat x4, GLfloat y4,int fill=TRUE);
	void DrawQuad(GLfloat x1, GLfloat y1,GLfloat z1,GLfloat x2, GLfloat y2,GLfloat z2,GLfloat x3, GLfloat y3,GLfloat z3,GLfloat x4, GLfloat y4,GLfloat z4,int fill=TRUE);
	void DrawQuad(const CdPoint3D &fptPoint1,const CdPoint3D &fptPoint2,const CdPoint3D &fptPoint3,const CdPoint3D &fptPoint4,int width=1, int fill=TRUE);
	
	void DrawEllipse(double fCx, double fCy, double fWidth, double fHeight, BOOL bFill = TRUE);
	void DrawCircle(CdPoint fpt, GLfloat r,int fill=TRUE);
	void DrawCircle(GLfloat cx, GLfloat cy, GLfloat r,int fill=TRUE,int nVert = 0);
	void DrawArcRound(GLfloat cx, GLfloat cy, GLfloat r, GLfloat start_angle, GLfloat arc_angle, GLfloat width,int dir,int fill=TRUE);
	void DrawArc(GLfloat cx, GLfloat cy, GLfloat r, GLfloat start_angle, GLfloat arc_angle, GLfloat width = 20.0,int dir = 0,int fill=TRUE);	
	void DrawArc(CdPoint fptCenter, GLfloat r, GLfloat start_angle, GLfloat end_angle, int dir);
////////////////////////////////////////////////////// lgh start
	void DrawAxisXYZ(GLfloat Position_X,GLfloat Position_Y,GLfloat Position_Z,double Length,double thick); // X,Y,Z 각도상태를 나타내는 객체

	void DrawCross(const CdPoint3D &fPosison,GLfloat fLength,GLfloat fLineWidth,int nShape=1);
	void DrawCross(const CdPoint &fPosison,GLfloat fLength,GLfloat fLineWidth,int nShape=1);
	void DrawGrid(int XdirNum,int YDirnum,double Xpitch,double Ypitch,double StartX,double StartY,int GridNumx,int GridNumy,CdPoint3D Orgin,int Option,COLORREF TextColor);
	void DrawGridEx(int XdirNum,int YDirnum,double Xpitch,double Ypitch,double StartX,double StartY,int GridNumx,int GridNumy,CdPoint3D Orgin,int Option,COLORREF TextColor);

//////////////////////////////////////////////////////////////////////////jun
	void EnableBlending(GLenum sFactor ,GLenum dFactor);
	void EnableBlending(GLenum dFactor = GL_ONE_MINUS_SRC_ALPHA);
	void DisableBlending();
};

#endif // !defined(AFX_OPENGLDRAW_H__876EE1DF_5B8E_4297_93C8_B8A7FE8D4B72__INCLUDED_)
