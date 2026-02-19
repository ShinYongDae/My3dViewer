// OpenGLDraw.cpp: implementation of the COpenGLDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGLDraw.h"
#include "GlobalDefine.h"
#include "GvisMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGLDraw::COpenGLDraw()
{
	m_fDrawResolution = 0.001;
	m_nDrawMinArcVertex = 2;

	m_vecVertices.reserve(100000);
}

COpenGLDraw::~COpenGLDraw()
{
	m_vecVertices.clear();
}

// draw resolution for arc
void COpenGLDraw::SetDrawResolution(GLfloat fResolution)
{
	m_fDrawResolution = fResolution;
}

void COpenGLDraw::SetDrawMinimumArcVertex(int nVertex)
{
	m_nDrawMinArcVertex = nVertex;
}

int COpenGLDraw::GetArcSegment(double fRadius, double fAngle)
{
	if(fAngle<0)
		fAngle=-fAngle;
	
	double fOptSeg = 100*sqrt(fRadius);
	fOptSeg *= (fAngle/360.0);
	
	double fResSeg = (2.0*PI*fRadius) / m_fDrawResolution;
	fResSeg *= (fAngle/360.0);
	
	fAngle /= 10.0;
	double fMinSeg = max((double)m_nDrawMinArcVertex, fAngle);
	double fSeg = max(fMinSeg, min(fOptSeg, fResSeg));
	int nSeg = ceil(fSeg);

	return nSeg;
}
void COpenGLDraw::EnableBlending(GLenum sFactor ,GLenum dFactor)
{
	glEnable( GL_BLEND );
	glBlendFunc(sFactor, dFactor); 
}
void COpenGLDraw::EnableBlending(GLenum dFactor)
{
//	glDisable(GL_DEPTH_TEST);
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, dFactor); 
}
void COpenGLDraw::DisableBlending()
{
//	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

//void COpenGLDraw::SetStencil(BOOL bStencil)
//{
//	if(bStencil==STENCIL_DARK)
//	{
//		glStencilFunc(GL_EQUAL,0,15);
//		glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);
//	}
//	else if(bStencil ==STENCIL_CLEAR)   //clear
//	{
//		glStencilFunc(GL_NEVER,1,1);
//		glStencilOp(GL_INCR,GL_INCR,GL_INCR);	
//	}
//}
//
//void COpenGLDraw::ClearStencil(BOOL bStencil)
//{
//	if(bStencil==STENCIL_DARK)
//	{
//		glClear(GL_STENCIL_BUFFER_BIT);
//	}
//}
void COpenGLDraw::DrawArcDonut(DPOINT fptCenter ,double dStartAngle, double dEndAngle, double dRadius, double dWidth)
{
	vector<DPOINT> vecArcVertex;
	double dArcAngle;
	int nDir;
	if(dStartAngle> dEndAngle)
	{
		dArcAngle = dStartAngle - dEndAngle;
		nDir = CW;
	}
	else
	{
		dArcAngle = dEndAngle - dStartAngle;
		nDir = CCW;
	}
	GetArcVertices(vecArcVertex,fptCenter,dRadius,dStartAngle,dArcAngle,nDir);


	vector<DPOINT> vecVertex;
	double dAngle,dLen;
	int nNumOfVertex,i;
	CdPoint fptStart,fptVert;
	nNumOfVertex = (int)vecArcVertex.size();
	double dAngleGap;

	dAngle = dStartAngle;
	dLen = dWidth/2.0;
	dAngleGap = (dEndAngle - dStartAngle)/(nNumOfVertex-1);
	for(i=0;i<nNumOfVertex;i++)
	{
		fptStart = vecArcVertex[i];
		fptVert.x = fptStart.x + cos(dAngle)*dLen;
		fptVert.y = fptStart.y + sin(dAngle)*dLen;
		vecVertex.push_back(fptVert);
		dAngle += dAngleGap;
	}
	dStartAngle += PI;
	if(dStartAngle > 2.0 *PI)
	{
		dStartAngle -= 2.0 *PI;
	}
	dEndAngle += PI;
	if(dEndAngle > 2.0 *PI)
	{
		dEndAngle -= 2.0 *PI;
	}
	dAngleGap = (dStartAngle - dEndAngle)/(nNumOfVertex-1);

	for(i=nNumOfVertex-1;i>-1;i--)
	{
		fptStart = vecArcVertex[i];
		fptVert.x = fptStart.x + cos(dAngle)*dLen;
		fptVert.y = fptStart.y + sin(dAngle)*dLen;
		vecVertex.push_back(fptVert);
		dAngle += dAngleGap;
	}
	DrawConcavePolygon(vecVertex);
	vecVertex.clear();
}
////////////////////////////  common drawing function  ////////////////////////////////////////////////////
void COpenGLDraw::GetArcVertices(vector<DPOINT> &vecPt,const DPOINT &ptCenter,GLfloat radius,GLfloat start_angle, GLfloat arc_angle,int dir)
{
	GLfloat theta, tangetial_factor, radial_factor;
	GLfloat x,y,tx,ty, cV, sV;
	DPOINT BufPt;

	int ii;
	int num_segments = GetArcSegment(radius,arc_angle*RAD2DEG);

	theta = arc_angle / GLfloat(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	tangetial_factor = tanf(theta);

	radial_factor = cosf(theta);

	cV = cosf(start_angle);
	sV = sinf(start_angle);

	if (cV < 0.0000001 && cV > -0.0000001)
		cV = 0;
	if (sV < 0.0000001 && sV > -0.0000001)
		sV = 0;

	x = radius * cV;	// cosf(start_angle);//we now start at the start angle
	y = radius * sV;	// sinf(start_angle);


	for(ii = 0; ii < num_segments; ii++)
	{ 
		BufPt.x = x + ptCenter.x;
		BufPt.y = y + ptCenter.y;
		vecPt.push_back(BufPt);

		if(dir == CW) //cw direction
		{
			tx = y; 
			ty = -x;
		}
		else // ccw direction
		{
			tx = -y; 
			ty = x;
		}

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor; 
		y *= radial_factor; 
	} 
}

void COpenGLDraw::GetArcVertices(vector<DPOINT> &vecPt,double fSx, double fSy, double fEx, double fEy, double fCx, double fCy, int nDir)
{
	GLfloat fRadius = GetDistance(CdPoint(fSx,fSy),CdPoint(fCx,fCy));
	//// 20190104 Modify
	double fStartAngle = GetLineAngle(fCx, fCy, fSx, fSy);
	double fEndAngle = GetLineAngle(fCx, fCy, fEx, fEy);
	double fArcAngle;
	/////////////////////////////////////////////////////////////////
	if (fStartAngle < 0)
		fStartAngle += 2.0*PI;
	if (fEndAngle < 0)
		fEndAngle += 2.0*PI;

	if(nDir == CCW)
	{
		if(fEndAngle>fStartAngle)
		{
			fArcAngle = fEndAngle-fStartAngle;
		}
		else
		{
			fArcAngle = 2*PI-fStartAngle+fEndAngle;
		}
	}
	else
	{
		if(fEndAngle>fStartAngle)
		{
			fArcAngle = 2*PI-fEndAngle+fStartAngle;
		}
		else
		{
			fArcAngle = fStartAngle-fEndAngle;
		}
	}
	GetArcVertices(vecPt,tagdPOINT(fCx,fCy),fRadius,fStartAngle,fArcAngle,nDir);		

}

void COpenGLDraw::GetEllipseVertices(vector<DPOINT> &vecPt,double fCx, double fCy, double fWidth, double fHeight)
{
	DPOINT pp[4], pc, fptCoord;
	int nSegment;

	if(fWidth>fHeight)
	{
		nSegment = GetArcSegment((fWidth/2.0) * (fHeight/fWidth) );
	}
	else
	{
		nSegment = GetArcSegment((fHeight/2.0) * (fWidth/fHeight) );
	}

	fWidth = fWidth / 2;
	fHeight = fHeight / 2;

	double differ =(2.0 * PI)/(double)nSegment;
	double rad=0.0f;

	int i;

	for(i = 0 ; i < nSegment ; i++)
	{
		fptCoord.x = fCx + cos(rad) * fWidth;
		fptCoord.y = fCy + sin(rad) * fHeight;
		vecPt.push_back(fptCoord);

		rad += differ;
	}
}


void COpenGLDraw::GetPolygonArcVertices(vector<DPOINT> &vecPt, const DPOINT &ptCenter, double radius, double start_angle, double arc_angle, int dir)
{
	double theta, tangetial_factor, radial_factor;
	double x, y, tx, ty, cV, sV;
	DPOINT BufPt;

	int ii;
	int num_segments = GetArcSegment(radius, arc_angle*RAD2DEG);

	theta = arc_angle / GLfloat(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	tangetial_factor = tanf(theta);

	radial_factor = cosf(theta);

	cV = cosf(start_angle);
	sV = sinf(start_angle);

	if (cV < 0.0000001 && cV > -0.0000001)
		cV = 0;
	if (sV < 0.0000001 && sV > -0.0000001)
		sV = 0;

	x = radius * cV;	// cosf(start_angle);//we now start at the start angle
	y = radius * sV;	// sinf(start_angle);

	if (dir == CW) //cw direction
	{
		tx = y;
		ty = -x;
	}
	else // ccw direction
	{
		tx = -y;
		ty = x;
	}

	x += tx * tangetial_factor;
	y += ty * tangetial_factor;

	x *= radial_factor;
	y *= radial_factor;

	for (ii = 1; ii < num_segments - 1; ii++)
	{
		BufPt.x = x + ptCenter.x;
		BufPt.y = y + ptCenter.y;
		vecPt.push_back(BufPt);

		if (dir == CW) //cw direction
		{
			tx = y;
			ty = -x;
		}
		else // ccw direction
		{
			tx = -y;
			ty = x;
		}

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		x *= radial_factor;
		y *= radial_factor;
	}
}

void COpenGLDraw::DrawLineRound(double fSx, double fSy, double fEx, double fEy, double fLineWidth,BOOL bFill)
{
	DPOINT bufPt;

	m_vecVertices.clear();

	bufPt.x = fSx;
	bufPt.y = fSy;
	double fLineAngle = GetLineAngle(fEx, fEy, fSx, fSy);				//// 20190104 Modify atan2(fSy - fEy, fSx - fEx);
	double fBufAngle;
	double fRadius = fLineWidth/2.0;
	fBufAngle = fLineAngle -PI/2.0;
	if(fBufAngle<0)
		fBufAngle += 2.0*PI;

	GetArcVertices(m_vecVertices,bufPt,fRadius,fBufAngle,PI,CCW);
	bufPt.x = fEx;
	bufPt.y = fEy;
	fBufAngle += PI;
	if(fBufAngle>2.0*PI)
		fBufAngle -= 2.0*PI;

	GetArcVertices(m_vecVertices,bufPt,fRadius,fBufAngle,PI,CCW);
	if(bFill)
	{
		DrawConvexPolygon(m_vecVertices);
	}
	else
	{
		DrawPolygonLine(m_vecVertices);
	}	
}

void COpenGLDraw::DrawLineSquare(double fSx, double fSy, double fEx, double fEy, double fLineWidth)
{
	DPOINT pp[4];
	double cV, sV, XX1, YY1, XX2, YY2, d, R, hh, ww;
	GLfloat LineWidth;

	LineWidth=fLineWidth;

	d = sqrt((fEx - fSx) * (fEx - fSx) + (fEy - fSy) * (fEy - fSy));
    hh = fEy - fSy;
    ww = fEx - fSx;
    R = fLineWidth / 2;

	if (d > 0.000001)
	{
		cV = ww / d;
		sV = hh / d;
	}
	else
	{
		fLineWidth = fLineWidth / 2;
		DrawRect(CdPoint3D((fSx - fLineWidth),(fSy - fLineWidth),0.0),CdPoint3D((fSx + fLineWidth),(fSy + fLineWidth),0.0));
		
		return;
	}
    
    XX1 = fSx - R * cV;
    YY1 = fSy - R * sV;
    XX2 = fEx + R * cV;
    YY2 = fEy + R * sV;
    
    cV = R * ww / d;
    sV = R * hh / d;
    
	DrawQuad((XX1 + sV),(YY1 - cV),(XX2 + sV),(YY2 - cV),(XX2 - sV),(YY2 + cV),(XX1 - sV),(YY1 + cV));	
}
double COpenGLDraw::GetDrawAngle(double dStartAngle, double dEndAngle, BOOL bDir)
{
	double dGet,dAngle;
	dAngle = (dStartAngle+dEndAngle)/2.0;
	if(bDir)
	{
		if(dAngle<1.5*PI)
		{
			dGet = dAngle+PI*0.5;
		}
		else
			dGet = dAngle-1.5*PI;
	}
	else
	{
		if(dAngle<0.5*PI)
		{
			dGet = dAngle+1.5*PI;
		}
		else
		{
			dGet = dAngle-0.5*PI;	
		}
	}
	return dGet;
}
void COpenGLDraw::DrawLineRect(const CdPoint &stStartVertex,const CdPoint &stEndVertex,double dLineWidth)
{
	dLineWidth /=2.0;
	double dStartAngle;
	double dGetAngle;
	double x,y;
	dStartAngle = atan2(stEndVertex.y-stStartVertex.y,stEndVertex.x-stStartVertex.x);
	if(dStartAngle<0)
		dStartAngle+=2*PI;
	glBegin(GL_POLYGON);
		dGetAngle = GetDrawAngle(dStartAngle,dStartAngle,TRUE);			
		x = stStartVertex.x+dLineWidth*cos(dGetAngle);
		y = stStartVertex.y+dLineWidth*sin(dGetAngle);
		glVertex2f(x,y);
		x = stEndVertex.x+dLineWidth*cos(dGetAngle);
		y = stEndVertex.y+dLineWidth*sin(dGetAngle);
		glVertex2f(x,y);
		dGetAngle = GetDrawAngle(dStartAngle,dStartAngle,FALSE);
		x = stEndVertex.x+dLineWidth*cos(dGetAngle);
		y = stEndVertex.y+dLineWidth*sin(dGetAngle);
		glVertex2f(x,y);
		x = stStartVertex.x+dLineWidth*cos(dGetAngle);
		y = stStartVertex.y+dLineWidth*sin(dGetAngle);
		glVertex2f(x,y);
	glEnd();
}
void COpenGLDraw::DrawLineRect(double fSx, double fSy, double fEx, double fEy, double fLineWidth, double fLineHeight, BOOL bFill  )
{   
	double ww, hh, a, b;
	DPOINT pp[6];

	ww = fLineWidth / 2;
	hh = fLineHeight / 2;

	if (fSx != fEx && fSy != fEy)
	{
		if (fEx > fSx)
		{
			if (fEy > fSy)
			{
				pp[0].x = (fSx - ww);
				pp[0].y = (fSy - hh);
				pp[1].x = (fSx - ww);
				pp[1].y = (fSy + hh);
				pp[2].x = (fEx - ww);
				pp[2].y = (fEy + hh);
				pp[3].x = (fEx + ww);
				pp[3].y = (fEy + hh);
				pp[4].x = (fEx + ww);
				pp[4].y = (fEy - hh);
				pp[5].x = (fSx + ww);
				pp[5].y = (fSy - hh);
			}
			else
			{
				pp[0].x = (fSx - ww);
				pp[0].y = (fSy - hh);
				pp[1].x = (fSx - ww);
				pp[1].y = (fSy + hh);
				pp[2].x = (fSx + ww);
				pp[2].y = (fSy + hh);
				pp[3].x = (fEx + ww);
				pp[3].y = (fEy + hh);
				pp[4].x = (fEx + ww);
				pp[4].y = (fEy - hh);
				pp[5].x = (fEx - ww);
				pp[5].y = (fEy - hh);
			}
		}
		else
		{
			if (fSy > fEy)
			{
				pp[0].x = (fEx - ww);
				pp[0].y = (fEy - hh);
				pp[1].x = (fEx - ww);
				pp[1].y = (fEy + hh);
				pp[2].x = (fSx - ww);
				pp[2].y = (fSy + hh);
				pp[3].x = (fSx + ww);
				pp[3].y = (fSy + hh);
				pp[4].x = (fSx + ww);
				pp[4].y = (fSy - hh);
				pp[5].x = (fEx + ww);
				pp[5].y = (fEy - hh);
			}
			else
			{
				pp[0].x = (fEx - ww);
				pp[0].y = (fEy - hh);
				pp[1].x = (fEx - ww);
				pp[1].y = (fEy + hh);
				pp[2].x = (fEx + ww);
				pp[2].y = (fEy + hh);
				pp[3].x = (fSx + ww);
				pp[3].y = (fSy + hh);
				pp[4].x = (fSx + ww);
				pp[4].y = (fSy - hh);
				pp[5].x = (fSx - ww);
				pp[5].y = (fSy - hh);
			}
		}
	
		DrawConvexPolygon(pp,6,bFill);
	}
	else
	{
		DPOINT pp[4];
		if (fSx == fEx && fSy == fEy)
		{
			pp[0].x = (fSx - ww);     //  '좌하
			pp[0].y = (fSy - hh);     //
			pp[1].x = (fSx + ww);     //  '우하
			pp[1].y = (fSy - hh);     //

			pp[2].x = (fEx + ww);     //  '우상
			pp[2].y = (fEy + hh);     //
			pp[3].x = (fEx - ww);     //  '좌상
			pp[3].y = (fEy + hh);     //
		}
		else if (fSx == fEx)
		{
			if (fSy > fEy )//  'b > a가 되게
			{
				a = fEy;
				b = fSy;
			}
			else
			{
				a = fSy;
				b = fEy;
			}
			pp[0].x = (fSx - ww);     //  '좌하
			pp[0].y = (a - hh);      //
			pp[1].x = (fSx + ww);     //  '우하
			pp[1].y = (a - hh);      //

			pp[2].x = (fEx + ww);     //  '우상
			pp[2].y = (b + hh);      //
			pp[3].x = (fEx - ww);    //   '좌상
			pp[3].y = (b + hh);     // 
		}
		else
		{
			if (fSx > fEx)
			{
				a = fEx;
				b = fSx;
			}
			else
			{
				a = fSx;
				b = fEx;
			}
			pp[0].x = (a - ww);      //  '좌하
			pp[0].y = (fSy - hh);     //
			pp[1].x = (b + ww);      //  '우하
			pp[1].y = (fSy - hh);    // 

			pp[2].x = (b + ww);      //  '우상
			pp[2].y = (fEy + hh);     //
			pp[3].x = (a - ww);     //   '좌상
			pp[3].y = (fEy + hh);    // 
		}
		DrawConvexPolygon(pp,4,bFill);		
	}
}
void COpenGLDraw::DrawEllipse(double fCx, double fCy, double fWidth, double fHeight, BOOL bFill)
{
 	DPOINT pp[4], pc;
	int nSegment;

	if(fWidth>fHeight)
	{
		nSegment = GetArcSegment((fWidth/2.0) * (fHeight/fWidth) );
	}
	else
	{
		nSegment = GetArcSegment((fHeight/2.0) * (fWidth/fHeight) );
	}
	
	fWidth = fWidth / 2;
    fHeight = fHeight / 2;
 	
	double differ =(2.0 * PI)/(double)nSegment;
	double rad=0.0f;

	int i;
	
	if(bFill)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);

	for(i=0;i<nSegment;i++)
	{
		glVertex2f(fCx + cos(rad) * fWidth, fCy + sin(rad) * fHeight);
		rad += differ;
	}
	glEnd();
}

void COpenGLDraw::DrawSpline(float *knots,int nNumKnot, float *ctrlPoints, int nDeg ,int nStride )
{
	GLUnurbsObj *curve;
	curve = gluNewNurbsRenderer();
	gluBeginCurve(curve);
	gluNurbsCurve(curve,nNumKnot,knots,nStride,&ctrlPoints[0],nDeg+1,GL_MAP1_VERTEX_3);
	gluEndCurve(curve);
	gluDeleteNurbsRenderer(curve);
}
void COpenGLDraw::DrawDonut(double fCx, double fCy, double fDmo, double fDmi,BOOL bFill)
{ 
	double w = (fDmo - fDmi) / 2;
	int segments=GetArcSegment(fDmo/2);
	double theta = 2 * PI / double(segments); 
	double tangetial_factor = tanf(theta); 
	double radial_factor = 1 - cosf(theta); 
	double x1 = fCx + (fDmo/2); 
	double y1 = fCy;
	double x2 = fCx + (fDmi/2); 
	double y2 = fCy; 
	double tx,ty,rx,ry;

	int i;
	if(bFill)
	{
	glEnable(GL_STENCIL_TEST);
	//SetStencil(FALSE);

		glBegin(GL_POLYGON);
		for(i=0; i<segments+1; i++)
		{
			glVertex2f(x2, y2);
			tx = -(y2 - fCy); 
			ty = x2 - fCx; 
			x2 += tx * tangetial_factor; 
			y2 += ty * tangetial_factor; 
			rx = fCx - x2; 
			ry = fCy - y2; 
			x2 += rx * radial_factor; 
			y2 += ry * radial_factor; 
		}
		glEnd();
	//SetStencil(TRUE);
		glBegin(GL_POLYGON);
		for(i=0; i<segments+1; i++)
		{
			glVertex2f(x1, y1);
			tx = -(y1 - fCy); 
			ty = x1 - fCx; 
			x1 += tx * tangetial_factor; 
			y1 += ty * tangetial_factor; 
			rx = fCx - x1; 
			ry = fCy - y1; 
			x1 += rx * radial_factor; 
			y1 += ry * radial_factor; 
		}
		glEnd();
	//ClearStencil(TRUE);
	glDisable(GL_STENCIL_TEST);
	}
	else
	{
	glBegin(GL_LINE_LOOP);
	for(i=0; i<segments+1; i++)
	{
		glVertex2f(x2, y2);
		tx = -(y2 - fCy); 
		ty = x2 - fCx; 
		x2 += tx * tangetial_factor; 
		y2 += ty * tangetial_factor; 
		rx = fCx - x2; 
		ry = fCy - y2; 
		x2 += rx * radial_factor; 
		y2 += ry * radial_factor; 
	}
	glEnd();
		glBegin(GL_LINE_LOOP);
		for(i=0; i<segments+1; i++)
		{
			glVertex2f(x1, y1);
			tx = -(y1 - fCy); 
			ty = x1 - fCx; 
			x1 += tx * tangetial_factor; 
			y1 += ty * tangetial_factor; 
			rx = fCx - x1; 
			ry = fCy - y1; 
			x1 += rx * radial_factor; 
			y1 += ry * radial_factor; 
		}
		glEnd();
	}
}
void COpenGLDraw::DrawPolyLine(const DPOINT *fPoint,int nNumberOfVertex,int nLineWidth)
{
	GLfloat lineWidth;
	int i,nNumOfVertex;
	nNumOfVertex = nNumberOfVertex;

	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_STRIP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(fPoint[i].x, fPoint[i].y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(fPoint[i].x, fPoint[i].y);
		}
		glEnd();
	}
}
//void COpenGLDraw::DrawPolyLine(const vector<ENTVERTEX> &vecPt,int nLineWidth)
//{
//	GLfloat lineWidth;
//	int i,nNumOfVertex;
//	nNumOfVertex = (int)vecPt.size();
//
//	if(nLineWidth != 0)
//	{
//		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
//		glLineWidth(nLineWidth);
//		glBegin(GL_LINE_STRIP);
//		for( i=0; i<nNumOfVertex; i++)
//		{
//			glVertex2f(vecPt.at(i).stVertex.x, vecPt.at(i).stVertex.y);
//		}
//		glEnd();
//		glLineWidth(lineWidth);
//	}
//	else
//	{
//		glBegin(GL_LINE_STRIP);
//		for( i=0; i<nNumOfVertex; i++)
//		{
//			glVertex2f(vecPt.at(i).stVertex.x, vecPt.at(i).stVertex.y);
//		}
//		glEnd();
//	}
//}
void COpenGLDraw::DrawPolyLine(const vector<CdPoint> &vecPt,int nLineWidth)
{
	GLfloat lineWidth;
	int i,nNumOfVertex;
	nNumOfVertex = (int)vecPt.size();

	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_STRIP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
	}
}
void COpenGLDraw::DrawPolyLine(const vector<DPOINT> &vecPt,int nLineWidth)
{
	GLfloat lineWidth;
	int i,nNumOfVertex;
	nNumOfVertex = (int)vecPt.size();

	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_STRIP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
	}
}
//void COpenGLDraw::DrawPolygonLine(const vector <ENTVERTEX> &vecPt,int nLineWidth )
//{
//	GLfloat lineWidth;
//	int i,nNumOfVertex;
//	nNumOfVertex = (int)vecPt.size();
//
//	if(nLineWidth != 0)
//	{
//		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
//		glLineWidth(nLineWidth);
//		glBegin(GL_LINE_LOOP);
//		for( i=0; i<nNumOfVertex; i++)
//		{
//			glVertex2f(vecPt.at(i).stVertex.x, vecPt.at(i).stVertex.y);
//		}
//		glEnd();
//		glLineWidth(lineWidth);
//	}
//	else
//	{
//		glBegin(GL_LINE_LOOP);
//		for( i=0; i<nNumOfVertex; i++)
//		{
//			glVertex2f(vecPt.at(i).stVertex.x, vecPt.at(i).stVertex.y);
//		}
//		glEnd();
//	}
//}
void COpenGLDraw::DrawPolygonLine(const vector <CdPoint> &vecPt,int nLineWidth )
{
	GLfloat lineWidth;
	int i,nNumOfVertex;
	nNumOfVertex = (int)vecPt.size();

	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
	}
}
void COpenGLDraw::DrawPolygonLine(const CdPoint *fptVert,int nCount,int nLineWidth)
{
	GLfloat lineWidth;
	int i;
	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nCount; i++)
		{
			glVertex2f(fptVert[i].x, fptVert[i].y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nCount; i++)
		{
			glVertex2f(fptVert[i].x, fptVert[i].y);
		}
		glEnd();
	}
}
void COpenGLDraw::DrawPolygonLine(const DPOINT *fptVert,int nCount,int nLineWidth)
{
	GLfloat lineWidth;
	int i;
	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nCount; i++)
		{
			glVertex2f(fptVert[i].x, fptVert[i].y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nCount; i++)
		{
			glVertex2f(fptVert[i].x, fptVert[i].y);
		}
		glEnd();
	}
}
void COpenGLDraw::DrawPolygonLine(const vector <DPOINT> &vecPt,int nLineWidth)
{
	GLfloat lineWidth;
	int i,nNumOfVertex;
	nNumOfVertex = (int)vecPt.size();

	if(nLineWidth != 0)
	{
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);
		glLineWidth(nLineWidth);
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
		glLineWidth(lineWidth);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(vecPt.at(i).x, vecPt.at(i).y);
		}
		glEnd();
	}
}
//void COpenGLDraw::DrawConcavePolygon(const vector <ENTVERTEX> &fPoint)
//{
//	glEnableClientState(GL_VERTEX_ARRAY);
//
//	glEnable(GL_STENCIL_TEST);
//
//	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
//	glStencilFunc(GL_NEVER,0,1);
//	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
//	glBegin(GL_TRIANGLE_FAN);
//	int i,nNumOfVertex;
//	nNumOfVertex = (int)fPoint.size();
//	for( i=0; i<nNumOfVertex; i++)
//	{
//		glVertex2f(fPoint.at(i).stVertex.x,fPoint.at(i).stVertex.y);
//	}
//	glEnd();
//	
//	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
//	glStencilFunc(GL_EQUAL,1,1);
//	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);
//
//	glBegin(GL_TRIANGLE_FAN);
//	for( i=0; i<nNumOfVertex; i++)
//	{
//		glVertex2f(fPoint.at(i).stVertex.x,fPoint.at(i).stVertex.y);
//	}
//	glEnd();
//
//	glDisable(GL_STENCIL_TEST);
//}
void COpenGLDraw::DrawConcavePolygon(const vector <CdPoint> &fPoint)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_STENCIL_TEST);

	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	glStencilFunc(GL_NEVER,0,1);
	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
	glBegin(GL_TRIANGLE_FAN);
	int i,nNumOfVertex;
	nNumOfVertex = (int)fPoint.size();
	for( i=0; i<nNumOfVertex; i++)
	{
		glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
	}
	glEnd();
	
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<nNumOfVertex; i++)
	{
		glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
	}
	glEnd();

	glDisable(GL_STENCIL_TEST);
}
void COpenGLDraw::DrawConcavePolygon(const vector <DPOINT> &fPoint,BOOL bFill)
{
	if(bFill)
	{
		glEnable(GL_STENCIL_TEST);

		glStencilFunc(GL_NEVER,0,1);
		glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
		glBegin(GL_TRIANGLE_FAN);
		int i,nNumOfVertex;
		nNumOfVertex = (int)fPoint.size();
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
		}
		glEnd();
	

		glStencilFunc(GL_EQUAL,1,1);
		glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

		glBegin(GL_TRIANGLE_FAN);
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
		}
		glEnd();

		glDisable(GL_STENCIL_TEST);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		int i,nNumOfVertex;
		nNumOfVertex = (int)fPoint.size();
		for( i=0; i<nNumOfVertex; i++)
		{
			glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
		}
		glEnd();
	}
}

void COpenGLDraw::MyConcavePolygonPicking(vector <DPOINT> fPoint)
{
	int nNumOfVertex = (int)fPoint.size();
	int i=0;

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NEVER,0,1);
	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<nNumOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
	
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<nNumOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
	glDisable(GL_STENCIL_TEST);
	glPopMatrix();
}
void COpenGLDraw::DrawConvexPolygon(const vector <CdPoint> &fPoint)
{
	glBegin(GL_POLYGON);
	int i,nNumOfVertex;
	nNumOfVertex =(int)fPoint.size();
	for( i=0; i<nNumOfVertex; i++)
	{
		glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
	}
	glEnd();
}

void COpenGLDraw::DrawConvexPolygon(const vector <DPOINT> &fPoint)
{
	glBegin(GL_POLYGON);
	int i,nNumOfVertex;
	nNumOfVertex = (int)fPoint.size();
	for( i=0; i<nNumOfVertex; i++)
	{
		glVertex2f(fPoint.at(i).x,fPoint.at(i).y);
	}
	glEnd();
}

void COpenGLDraw::DrawConvexPolygon(const DPOINT *fPoint,int nNumberOfVertex,BOOL bFill)
{
	if(bFill)
	{
		glBegin(GL_POLYGON);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
}
void COpenGLDraw::DrawConvexPolygon(const CdPoint *fPoint,int nNumberOfVertex)
{
	glBegin(GL_POLYGON);
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
}
void COpenGLDraw::DrawConvexPolygon(const CdPoint3D *fPoint,int nNumberOfVertex)
{
	glBegin(GL_POLYGON);
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
}

void COpenGLDraw::DrawConcavePolygon(const DPOINT *fPoint,int nNumberOfVertex,GLenum nMode)
{
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_NEVER,0,1);
	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
	glBegin(nMode);
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
	
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

	glBegin(nMode);
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();

	glDisable(GL_STENCIL_TEST);
}
void COpenGLDraw::DrawConcavePolygon(const CdPoint *fPoint,int nNumberOfVertex,GLenum nMode)
{
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_NEVER,0,1);
	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
	glBegin(nMode);
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();

	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

	glBegin(nMode);
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();

	glDisable(GL_STENCIL_TEST);
}
void COpenGLDraw::DrawConcavePolygon(const CdPoint3D *fPoint,int nNumberOfVertex)
{
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_NEVER,0,1);
	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
	glBegin(GL_TRIANGLE_FAN);
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();
	
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex2f(fPoint[i].x, fPoint[i].y);
	}
	glEnd();

	glDisable(GL_STENCIL_TEST);
}


void COpenGLDraw::DrawConcavePolygon3D(const CdPoint3D *fPoint,int nNumberOfVertex)
{
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_NEVER,0,1);
	glStencilOp(GL_INVERT,GL_INVERT,GL_INVERT);
	glBegin(GL_TRIANGLE_FAN);
	int i;
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex3f(fPoint[i].x, fPoint[i].y,fPoint[i].z);
	}
	glEnd();
	
	glStencilFunc(GL_EQUAL,1,1);
	glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);

	glBegin(GL_TRIANGLE_FAN);
	for( i=0; i<nNumberOfVertex; i++)
	{
		glVertex3f(fPoint[i].x, fPoint[i].y,fPoint[i].z);
	}
	glEnd();

	glDisable(GL_STENCIL_TEST);
}

void COpenGLDraw::SetColor(COLORREF crColor)
{
	GLfloat red = GetRValue(crColor) / 255.0f;
	GLfloat green = GetGValue(crColor) / 255.0f;
	GLfloat blue = GetBValue(crColor) / 255.0f;
	glColor3f(red,green,blue);
}

void COpenGLDraw::SetColor(COLORREF crColor, double fAlpha)
{
	GLfloat red = GetRValue(crColor) / 255.0f;
	GLfloat green = GetGValue(crColor) / 255.0f;
	GLfloat blue = GetBValue(crColor) / 255.0f;
	glColor4f(red,green,blue, fAlpha);
}

void COpenGLDraw::DrawCircle(CdPoint fpt, GLfloat r,int fill)
{
	DrawCircle(fpt.x,fpt.y,r,fill); 
}

void COpenGLDraw::DrawCircle(GLfloat cx, GLfloat cy, GLfloat r,int fill,int nVert) 
{ 
	int ii;
	int num_segments;
	if(nVert > 0 )
	{
		num_segments = nVert;
	}
	else
	{
		num_segments= GetArcSegment(r);
	}

 	GLfloat circle_length = (2.0 * PI * r);


	GLfloat theta = 2.0 * PI / GLfloat(num_segments); //theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	GLfloat tangetial_factor = tanf(theta);
	GLfloat radial_factor = cosf(theta);
	GLfloat x = r;
	GLfloat y = 0;
	GLfloat tx , ty;

	if(fill)
		glBegin(GL_POLYGON); // filled circle
	else
		glBegin(GL_LINE_LOOP);// hollow circle since the circle is a closed curve, this is a loop now

	for(ii = 0; ii < num_segments; ii++)
	{ 
		glVertex3f(x + cx, y + cy,0.0f);

		tx = -y; 
		ty = x; 


		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor; 
		y *= radial_factor; 
	} 
	glEnd(); 
}


void COpenGLDraw::DrawArcRound(GLfloat cx, GLfloat cy, GLfloat r, GLfloat start_angle, GLfloat arc_angle, GLfloat width,int dir,int fill) 
{
	GLfloat halfWidth = width/2.0;
	DPOINT bufPt;

	m_vecVertices.clear();
	if(dir == CW)
	{
		GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r-halfWidth,start_angle,arc_angle,CW);
		bufPt.x = cx+r*cos(start_angle-arc_angle);
		bufPt.y = cy+r*sin(start_angle-arc_angle);
		if(start_angle-arc_angle -PI < 0)
		{
			GetArcVertices(m_vecVertices,bufPt,halfWidth,start_angle-arc_angle+PI,PI,CCW);
		}
		else
		{
			GetArcVertices(m_vecVertices,bufPt,halfWidth,start_angle-arc_angle -PI,PI,CCW);
		}
		if(start_angle-arc_angle<0)
		{
			GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r+halfWidth,start_angle-arc_angle+2.0*PI,arc_angle,CCW);
		}
		else
		{
			GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r+halfWidth,start_angle-arc_angle,arc_angle,CCW);
		}
		
		
		bufPt.x = cx+r*cos(start_angle);
		bufPt.y = cy+r*sin(start_angle);
		GetArcVertices(m_vecVertices,bufPt,halfWidth,start_angle,PI,CCW);

	}
	else if(dir == CCW)
	{
		GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r-halfWidth,start_angle,arc_angle,CCW);
		bufPt.x = cx+r*cos(start_angle+arc_angle);
		bufPt.y = cy+r*sin(start_angle+arc_angle);
		if(start_angle+arc_angle +PI> 2.0*PI)
		{
			GetArcVertices(m_vecVertices,bufPt,halfWidth,start_angle+arc_angle-PI,PI,CW);
		}
		else
		{
			GetArcVertices(m_vecVertices,bufPt,halfWidth,start_angle+arc_angle+PI,PI,CW);
		}
		if(start_angle+arc_angle>2.0*PI)
		{
			GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r+halfWidth,start_angle+arc_angle-2.0*PI,arc_angle,CW);
		}
		else
		{
			GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r+halfWidth,start_angle+arc_angle,arc_angle,CW);
		}
		
		
		bufPt.x = cx+r*cos(start_angle);
		bufPt.y = cy+r*sin(start_angle);
		GetArcVertices(m_vecVertices,bufPt,halfWidth,start_angle,PI,CW);		
	}
	if(fill)
		DrawConcavePolygon(m_vecVertices);
	else
		DrawPolygonLine(m_vecVertices);
	return;
}
void COpenGLDraw::DrawArc(CdPoint fptCenter, GLfloat r, GLfloat start_angle, GLfloat end_angle, int dir)
{
	CdPoint stVertex;
	GLfloat theta, tangetial_factor, radial_factor;
	GLfloat x,y,tx,ty; 
	GLfloat radius;
	double arc_angle;
	int num_segments;
	if(dir == CCW )
	{
		if(end_angle < start_angle)//ccw
		{
			arc_angle=360-(start_angle-end_angle);
		}
		else
		{
			arc_angle=end_angle-start_angle;
		}
	}
	else
	{
		if(end_angle < start_angle)//cw
		{
			arc_angle=start_angle-end_angle;
		}
		else
		{
			arc_angle=360-(end_angle-start_angle);
		}
	}


	radius = r;

	num_segments = GetArcSegment(radius,arc_angle);
	theta = (arc_angle*DEG2RAD) / GLfloat(num_segments);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	tangetial_factor = tanf(theta);

	radial_factor = cosf(theta);

	x = radius * cos(start_angle*DEG2RAD);//we now start at the start angle
	y = radius * sin(start_angle*DEG2RAD); 
	glBegin(GL_LINE_STRIP);
	for(int ii = 0; ii < num_segments; ii++)
	{ 
		glVertex2f(x + fptCenter.x,y + fptCenter.y);


		if(dir == CW) //cw direction
		{
			tx = y; 
			ty = -x;
		}
		else // ccw direction
		{
			tx = -y; 
			ty = x;
		}

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor; 
		y *= radial_factor; 
	} 
	x = radius * cos(end_angle*DEG2RAD);//we now start at the start angle
	y = radius * sin(end_angle*DEG2RAD); 
	glVertex2f(x + fptCenter.x,y + fptCenter.y);
	glEnd();
}
void COpenGLDraw::DrawArc(GLfloat cx, GLfloat cy, GLfloat r, GLfloat start_angle, GLfloat arc_angle, GLfloat width,int dir,int fill) 
{ 
	GLfloat halfWidth = width/2.0;
	DPOINT bufPt;

	m_vecVertices.clear();
	if(dir == CW)
	{
		GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r-halfWidth,start_angle,arc_angle,CW);
		GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r+halfWidth,start_angle-arc_angle,arc_angle,CCW);
	}
	else if(dir == CCW)
	{
		GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r-halfWidth,start_angle,arc_angle,CCW);
		GetArcVertices(m_vecVertices,tagdPOINT(cx,cy),r+halfWidth,start_angle+arc_angle,arc_angle,CW);
	}
	if(fill)
		DrawConcavePolygon(m_vecVertices);
	else
		DrawPolygonLine(m_vecVertices);
}

void COpenGLDraw::DrawText(CString strText, GLdouble x, GLdouble y, GLdouble z, GLdouble fFontSize, GLfloat fLintWidth,COLORREF color,int Fill)
{
	if(strText.GetLength()<1)
		return;

	glPushMatrix();

	glTranslatef(x, y, z);

	
	if(Fill == TRUE)
	{	
		int Lengh = strText.GetLength();
		SetColor(WHITE);
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

	SetColor(color);

	glScalef(1.0f*fFontSize, 1.0f*fFontSize, z);
	
	TCHAR* pText;
	pText = strText.GetBuffer(0); // GetBuffer(0): strText가 가지고 있는 문자열의 만큼 가지고 온다

#ifdef _WIN64
//	while(*pText)
//		glutStrokeCharacter(GLUT_STROKE_ROMAN, *pText++);
#else
	while(*pText)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *pText++);
#endif
	
	glPopMatrix();

	glLineWidth(lineWidth);
}

void COpenGLDraw::DrawLine(const CdPoint3D &fptStart,const CdPoint3D &fptEnd)
{
	DrawLine(fptStart.x,fptStart.y,fptStart.z,fptEnd.x,fptEnd.y,fptStart.z);
}

void COpenGLDraw::DrawLine(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2)
{
	glBegin(GL_LINES);
	glVertex2f ((x1),(y1));
	glVertex2f ((x2),(y2));
	glEnd(); 

}

void COpenGLDraw::DrawLine(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2)
{
	glBegin(GL_LINES);
	glVertex3f ((x1),(y1),(z1));
	glVertex3f ((x2),(y2),(z2));
	glEnd(); 

}

void COpenGLDraw::DrawQuad(const CdQuad &fQuad,int fill)
{
	DrawQuad(fQuad.leftbottom.x,fQuad.leftbottom.y,fQuad.rightbottom.x,fQuad.rightbottom.y,
		fQuad.righttop.x,fQuad.righttop.y,fQuad.lefttop.x,fQuad.lefttop.y,fill);
}

void COpenGLDraw::DrawQuad(const DQUAD &fQuad, int fill)
{
	DrawQuad(fQuad.leftbottom.x, fQuad.leftbottom.y, fQuad.rightbottom.x, fQuad.rightbottom.y,
		fQuad.righttop.x, fQuad.righttop.y, fQuad.lefttop.x, fQuad.lefttop.y, fill);
}

void COpenGLDraw::DrawQuad(const vector<DPOINT> &vecPt,int fill)
{
	int i;

	if(fill)
		glBegin(GL_QUADS); // filled quad
	else
		glBegin(GL_LINE_LOOP); // hollow quad
	for(i=0; i<vecPt.size();i++)
	{
		glVertex2f(vecPt[i].x,vecPt[i].y);
	}
	glEnd();
}
void COpenGLDraw::DrawQuad(GLfloat x1, GLfloat y1,GLfloat z1,GLfloat x2, GLfloat y2,GLfloat z2,GLfloat x3, GLfloat y3,GLfloat z3,GLfloat x4, GLfloat y4,GLfloat z4,int fill)
{
	if(fill)
		glBegin(GL_QUADS); // filled quad
	else
		glBegin(GL_LINE_LOOP); // hollow quad

	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x3,y3,z3);
	glVertex3f(x4,y4,z4);

	glEnd();
}

void COpenGLDraw::DrawQuad(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2,GLfloat x3, GLfloat y3,GLfloat x4, GLfloat y4,int fill)
{	
	if(fill)
		glBegin(GL_QUADS); // filled quad
	else
		glBegin(GL_LINE_LOOP); // hollow quad

	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();

}

////////////////////////////////////////////////////////////////////////////
void COpenGLDraw::DrawPoint(const CdPoint &fptStart,int nPointSize)
{
	GLfloat fPointSize;
	if(nPointSize == 0 )
	{
		glBegin(GL_POINTS); // hollow quad
		glVertex2f(fptStart.x,fptStart.y);
		glEnd();
	}
	else
	{
		glGetFloatv(GL_POINT_SIZE,&fPointSize);
		glPointSize(nPointSize);
		glBegin(GL_POINTS); // hollow quad
		glVertex2f(fptStart.x,fptStart.y);
		glEnd();
		glPointSize(fPointSize);
	}
}
void COpenGLDraw::DrawPoint(const CdPoint3D &fptStart,int nPointSize)
{
	GLfloat fPointSize;
	if(nPointSize == 0 )
	{
		glBegin(GL_POINTS); // hollow quad
		glVertex3f(fptStart.x,fptStart.y,fptStart.z);
		glEnd();
	}
	else
	{
		glGetFloatv(GL_POINT_SIZE,&fPointSize);
		glPointSize(nPointSize);
		glBegin(GL_POINTS); // hollow quad
		glVertex3f(fptStart.x,fptStart.y,fptStart.z);
		glEnd();
		glPointSize(fPointSize);
	}
}
void COpenGLDraw::DrawPoints(const vector<CdPoint> &vecPt,int nPointSize)
{
	GLfloat fPointSize;
	int i;
	if(nPointSize == 0 )
	{
		glBegin(GL_POINTS); // hollow quad
		for(i=0; i<vecPt.size(); i++)
		{
			glVertex2f(vecPt[i].x,vecPt[i].y);
		}
		glEnd();
	}
	else
	{
		glGetFloatv(GL_POINT_SIZE,&fPointSize);
		glPointSize(nPointSize);
		glBegin(GL_POINTS); // hollow quad
		for(i=0; i<vecPt.size(); i++)
		{
			glVertex2f(vecPt[i].x,vecPt[i].y);
		}
		glEnd();
		glPointSize(fPointSize);
	}
}
void COpenGLDraw::DrawPoints(const vector<DPOINT> &vecPt,int nPointSize)
{
	GLfloat fPointSize;
	int i;
	if(nPointSize == 0 )
	{
		glBegin(GL_POINTS); // hollow quad
		for(i=0; i<vecPt.size(); i++)
		{
			glVertex2f(vecPt[i].x,vecPt[i].y);
		}
		glEnd();
	}
	else
	{
		glGetFloatv(GL_POINT_SIZE,&fPointSize);
		glPointSize(nPointSize);
		glBegin(GL_POINTS); // hollow quad
		for(i=0; i<vecPt.size(); i++)
		{
			glVertex2f(vecPt[i].x,vecPt[i].y);
		}
		glEnd();
		glPointSize(fPointSize);
	}
}

void COpenGLDraw::DrawPoints(const CdPoint3D *fptStart,int nCnt,int nPointSize)
{
	GLfloat fPointSize;
	int i;
	if(nPointSize == 0 )
	{
		glBegin(GL_POINTS); // hollow quad
		for(i=0; i<nCnt; i++)
		{
			glVertex3f(fptStart[i].x,fptStart[i].y,fptStart[i].z);
		}
		glEnd();
	}
	else
	{
		glGetFloatv(GL_POINT_SIZE,&fPointSize);
		glPointSize(nPointSize);
		glBegin(GL_POINTS); // hollow quad
		for(i=0; i<nCnt; i++)
		{
			glVertex3f(fptStart[i].x,fptStart[i].y,fptStart[i].z);
		}
		glEnd();
		glPointSize(fPointSize);
	}
}
void COpenGLDraw::DrawLine(const CdPoint &fptStart,const CdPoint &fptEnd,int nWidth,int nDotted)
{
	if(nWidth == 1 && nDotted == 0)
	{
		glBegin(GL_LINES);
		glVertex2f(fptStart.x,fptStart.y);
		glVertex2f(fptEnd.x,fptEnd.y);
		glEnd();
	}
	else
	{
		GLfloat lineWidth;
		glGetFloatv(GL_LINE_WIDTH,&lineWidth);


		glLineWidth(nWidth);
		if(nDotted)
		{
			glEnable (GL_LINE_STIPPLE);
			glLineStipple (1, 0x0101); // dotted
		}
		glBegin(GL_LINES);
		glVertex2f(fptStart.x,fptStart.y);
		glVertex2f(fptEnd.x,fptEnd.y);
		glEnd();
		if(nDotted)
		{
			glDisable (GL_LINE_STIPPLE);
		}
		glLineWidth(lineWidth);
	}
}
void COpenGLDraw::DrawLine(const CdPoint3D &fptStart,const CdPoint3D &fptEnd,int nWidth,int nDotted)
{
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);


	glLineWidth(nWidth);
	if(nDotted)
	{
		glEnable (GL_LINE_STIPPLE);
		glLineStipple (1, 0x0101); // dotted
	}
	glBegin(GL_LINES);
	glVertex3f(fptStart.x,fptStart.y,fptStart.z);
	glVertex3f(fptEnd.x,fptEnd.y,fptEnd.z);
	glEnd();
	if(nDotted)
	{
		glDisable (GL_LINE_STIPPLE);
	}


	glLineWidth(lineWidth);
}
void COpenGLDraw::DrawLines(const CdPoint3D *fptStart,int nCnt,int nWidth,int nDotted)
{
	int i;
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);

	glLineWidth(nWidth);

	if(nDotted)
	{
		glEnable (GL_LINE_STIPPLE);
		glLineStipple (1, 0x0101); // dotted
	}
	glBegin(GL_LINE_STRIP);
	for(i=0; i<nCnt; i++)
	{
		glVertex3f(fptStart[i].x,fptStart[i].y,fptStart[i].z);
	}
	glEnd();

	if(nDotted)
	{
		glDisable (GL_LINE_STIPPLE);
	}
	glLineWidth(lineWidth);
}

void COpenGLDraw::DrawRect(DRECT frtRect, int width, int fill)
{
	if (width != 0 && fill == 0)
	{
		GLfloat lineWidth;

		glGetFloatv(GL_LINE_WIDTH, &lineWidth);

		glLineWidth(width);

		glBegin(GL_LINE_LOOP); // hollow quad
		glVertex3f(frtRect.left, frtRect.top, 0.0f);
		glVertex3f(frtRect.right, frtRect.top, 0.0f);
		glVertex3f(frtRect.right, frtRect.bottom, 0.0f);
		glVertex3f(frtRect.left, frtRect.bottom, 0.0f);
		glEnd();

		glLineWidth(lineWidth);
	}
	else
	{
		DrawRect(frtRect, fill);
	}
}
void COpenGLDraw::DrawRect(const CdRect &rect,int width, int fill)
{
	GLfloat lineWidth;
	if(fill)
	{
		glBegin(GL_QUADS); // filled quad

		glVertex3f(rect.left,rect.top,0.0f);
		glVertex3f(rect.right,rect.top,0.0f);
		glVertex3f(rect.right,rect.bottom,0.0f);
		glVertex3f(rect.left,rect.bottom,0.0f);

		glEnd();
	}
	else
	{
		if(width != 0)
		{
			glGetFloatv(GL_LINE_WIDTH,&lineWidth);

			glLineWidth(width);
			
			glBegin(GL_LINE_LOOP); // hollow quad
			glVertex3f(rect.left,rect.top,0.0f);
			glVertex3f(rect.right,rect.top,0.0f);
			glVertex3f(rect.right,rect.bottom,0.0f);
			glVertex3f(rect.left,rect.bottom,0.0f);
			glEnd();

			glLineWidth(lineWidth);
		}
		else
		{
			glBegin(GL_LINE_LOOP); // hollow quad
			glVertex3f(rect.left,rect.top,0.0f);
			glVertex3f(rect.right,rect.top,0.0f);
			glVertex3f(rect.right,rect.bottom,0.0f);
			glVertex3f(rect.left,rect.bottom,0.0f);
			glEnd();
		}
	}

}
void COpenGLDraw::DrawRect(DRECT frtRect,BOOL bFill)
{	
	if(bFill)
	{
		glBegin(GL_QUADS); // hollow quad
	}
	else
	{
		glBegin(GL_LINE_LOOP); // hollow quad
	}
	glVertex2f(frtRect.left,frtRect.bottom);
	glVertex2f(frtRect.left,frtRect.top);
	glVertex2f(frtRect.right,frtRect.top);
	glVertex2f(frtRect.right,frtRect.bottom);
	glEnd();		
}
void COpenGLDraw::DrawRect(const DPOINT &fptStart,const DPOINT &fptEnd,int width, int fill)
{
	GLfloat lineWidth;
	if(fill)
	{
		glBegin(GL_QUADS); // filled quad

		glVertex2f(fptStart.x,fptStart.y);
		glVertex2f(fptStart.x,fptEnd.y);
		glVertex2f(fptEnd.x,fptEnd.y);
		glVertex2f(fptEnd.x,fptStart.y);

		glEnd();
	}
	else
	{
		if(width != 0)
		{
			glGetFloatv(GL_LINE_WIDTH,&lineWidth);

			glLineWidth(width);
			
			glBegin(GL_LINE_LOOP); // hollow quad
			glVertex2f(fptStart.x,fptStart.y);
			glVertex2f(fptStart.x,fptEnd.y);
			glVertex2f(fptEnd.x,fptEnd.y);
			glVertex2f(fptEnd.x,fptStart.y);
			glEnd();

			glLineWidth(lineWidth);
		}
		else
		{
			glBegin(GL_LINE_LOOP); // hollow quad
			glVertex2f(fptStart.x,fptStart.y);
			glVertex2f(fptStart.x,fptEnd.y);
			glVertex2f(fptEnd.x,fptEnd.y);
			glVertex2f(fptEnd.x,fptStart.y);
			glEnd();
		}
	}
}

void COpenGLDraw::DrawRect(const CdPoint3D &fptStart,const CdPoint3D &fptEnd,int width, int fill)
{
	GLfloat lineWidth;
	if(fill)
	{
		glBegin(GL_QUADS); // filled quad

		glVertex3f(fptStart.x,fptStart.y,fptStart.z);
		glVertex3f(fptStart.x,fptEnd.y,fptStart.z);
		glVertex3f(fptEnd.x,fptEnd.y,fptStart.z);
		glVertex3f(fptEnd.x,fptStart.y,fptStart.z);

		glEnd();
	}
	else
	{
		if(width != 0)
		{
			glGetFloatv(GL_LINE_WIDTH,&lineWidth);

			glLineWidth(width);
			
			glBegin(GL_LINE_LOOP); // hollow quad
			glVertex3f(fptStart.x,fptStart.y,fptStart.z);
			glVertex3f(fptStart.x,fptEnd.y,fptStart.z);
			glVertex3f(fptEnd.x,fptEnd.y,fptStart.z);
			glVertex3f(fptEnd.x,fptStart.y,fptStart.z);
			glEnd();

			glLineWidth(lineWidth);
		}
		else
		{
			glBegin(GL_LINE_LOOP); // hollow quad
			glVertex3f(fptStart.x,fptStart.y,fptStart.z);
			glVertex3f(fptStart.x,fptEnd.y,fptStart.z);
			glVertex3f(fptEnd.x,fptEnd.y,fptStart.z);
			glVertex3f(fptEnd.x,fptStart.y,fptStart.z);
			glEnd();
		}
	}
}

void COpenGLDraw::DrawQuad(const CdPoint3D &fptPoint1,const CdPoint3D &fptPoint2,const CdPoint3D &fptPoint3,const CdPoint3D &fptPoint4,int width, int fill)
{
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);



	glLineWidth(width);
	if(fill)
		glBegin(GL_QUADS); // filled quad
	else
		glBegin(GL_LINE_LOOP); // hollow quad

	glVertex3f(fptPoint1.x,fptPoint1.y,fptPoint1.z);
	glVertex3f(fptPoint2.x,fptPoint2.y,fptPoint2.z);
	glVertex3f(fptPoint3.x,fptPoint3.y,fptPoint3.z);
	glVertex3f(fptPoint4.x,fptPoint4.y,fptPoint4.z);

	glEnd();


	glLineWidth(lineWidth);
}

void COpenGLDraw::DrawCross(const CdPoint3D &fPosison,GLfloat fLength,GLfloat fLineWidth,int nShape/* =1 */)
{
//	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);

	glLineWidth(fLineWidth);
	glPushMatrix();
	glTranslatef(fPosison.x,fPosison.y,fPosison.z); 
	
	if(nShape==2)
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES); // Xdir Line
	glVertex3f(-fLength/2.0,0,0);
	glVertex3f(fLength/2.0,0,0);
	glEnd();

	glBegin(GL_LINES); // Xdir Line
	glVertex3f(0,-fLength/2.0,0);
	glVertex3f(0,+fLength/2.0,0);
	glEnd();

	glPopMatrix();
	glLineWidth(lineWidth);
//	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);
}

void COpenGLDraw::DrawCross(const CdPoint &fPosison,GLfloat fLength,GLfloat fLineWidth,int nShape/* =1 */)
{
//	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);

	glLineWidth(fLineWidth);
	glPushMatrix();
	glTranslatef(fPosison.x,fPosison.y,0); 
	
	if(nShape==2)
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_LINES); // Xdir Line
	glVertex3f(-fLength/2.0,0,0);
	glVertex3f(fLength/2.0,0,0);
	glEnd();

	glBegin(GL_LINES); // Xdir Line
	glVertex3f(0,-fLength/2.0,0);
	glVertex3f(0,+fLength/2.0,0);
	glEnd();

	glPopMatrix();
	glLineWidth(lineWidth);
//	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);
}

void COpenGLDraw::DrawGridEx(int XdirNum,int YDirnum,double Xpitch,double Ypitch,double StartX,double StartY,int GridNumx,int GridNumy,CdPoint3D Orgin,int Option,COLORREF TextColor)
{

	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);
	
	if(Xpitch<=0.0 || Ypitch<=0.0 || XdirNum<=0 || YDirnum<=0)
		return;

	int nGridStepX; // 한방향의 정점을 몇번 건너뛸건지.. 결정하는 정수 
	int nGridStepY; // 동일 

	nGridStepX = GridNumx;
	nGridStepY = GridNumy;

	if(GridNumy < 9 && GridNumy%2==1)
	{ 
		nGridStepY-=((GridNumy) % (GridNumy-1));
	}

	if(GridNumx>13 && GridNumx%2==1)
	{
		nGridStepX-=((GridNumx) % (GridNumx-1));
	}

	int skipy=(YDirnum)/nGridStepY;
	int skipx=XdirNum/nGridStepX;
	int tempcount=0;
	register int j;
	TCHAR text[128]={0,};
	
	glPushMatrix();
	glTranslatef(Orgin.x,Orgin.y,Orgin.z);

	for(j=0; j<XdirNum; j++) //X 축 GRID 
	{
		glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex3d(Xpitch*j,0,Orgin.z);
		glVertex3d(Xpitch*j,Ypitch*(YDirnum-1),Orgin.z);
		glEnd();

		if(j==0 || j== XdirNum-1)
		{
				
			if(Option == G_GRID_TEXT || Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
			{
				_stprintf(text,_T("%3.1f"),Xpitch*j+StartX);

				DrawText(text,Xpitch*j-_tcslen(text),-17,Orgin.z,0.05,1.0,TextColor);
			}

			tempcount++;
		}
		else
		{
			if(tempcount>=skipx)
			{
				tempcount=0;

				if(Option == G_GRID_TEXT || Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
				{

					_stprintf(text,_T("%3.1f"),Xpitch*j+StartX);

					DrawText(text,Xpitch*j-15,-17,Orgin.z,0.05,1.0,TextColor);
				}					

			}
			tempcount++;
		}
	}
	tempcount=0;	
	
	for(j=0; j<YDirnum; j++) //Y 축 GRID 
	{
		glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex3d(0,Ypitch*j,Orgin.z);
		glVertex3d(Xpitch*(XdirNum-1),Ypitch*j,Orgin.z);
		glEnd();	
		
		if(j==0 || j== YDirnum-1)
		{

			if(Option == G_GRID_TEXT)
			{
				_stprintf(text,_T("%3.1f"),Ypitch*j+StartY);

				if(j==0)
				DrawText(text,-50,Ypitch*j+5,Orgin.z,0.05,1.0,TextColor);
				else
				DrawText(text,-50,Ypitch*j-5,Orgin.z,0.05,1.0,TextColor);
			}
			else if(Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
			{
				_stprintf(text,_T("%3.1f"),(Ypitch*(YDirnum-1)-Ypitch*j)+StartY);

				if(j==0)
				DrawText(text,-50,Ypitch*j+5,Orgin.z,0.05,1.0,TextColor);
				else
				DrawText(text,-50,Ypitch*j-5,Orgin.z,0.05,1.0,TextColor);
			}

			tempcount++;
		}
		else
		{
			if(tempcount>=skipy)
			{
				tempcount=0;

				if(Option == G_GRID_TEXT)
				{
#ifdef UNDER_VS2008
					_stprintf(text,_T("%3.1f"),Ypitch*j+StartY);
#else
					_stprintf_s(text,_T("%3.1f"),Ypitch*j+StartY);
#endif
					DrawText(text,-50,Ypitch*j-5,Orgin.z,0.05,1.0,TextColor);
				}
				else if(Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
				{
#ifdef UNDER_VS2008
					_stprintf(text,_T("%3.1f"),(Ypitch*(YDirnum-1)-Ypitch*j)+StartY);
#else
					_stprintf_s(text,_T("%3.1f"),(Ypitch*(YDirnum-1)-Ypitch*j)+StartY);
#endif
					if(j==0)
					DrawText(text,-50,Ypitch*j+5,Orgin.z,0.05,1.0,TextColor);
					else
					DrawText(text,-50,Ypitch*j-5,Orgin.z,0.05,1.0,TextColor);
				}

			}
			tempcount++;
		}
	}
	glPopMatrix();
}


void COpenGLDraw::DrawGrid(int XdirNum,int YDirnum,double Xpitch,double Ypitch,double StartX,double StartY,int GridNumx,int GridNumy,CdPoint3D Orgin,int Option,COLORREF TextColor)
{

	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);
	
	if(Xpitch<=0.0 || Ypitch<=0.0 || XdirNum<=0 || YDirnum<=0)
		return;

	int nGridStepX; // 한방향의 정점을 몇번 건너뛸건지.. 결정하는 정수 
	int nGridStepY; // 동일 

	nGridStepX = GridNumx;
	nGridStepY = GridNumy;

	if(GridNumy < 9 && GridNumy%2==1)
	{ 
		nGridStepY-=((GridNumy) % (GridNumy-1));
	}

	if(GridNumx>13 && GridNumx%2==1)
	{
		nGridStepX-=((GridNumx) % (GridNumx-1));
	}

	int skipy=(YDirnum)/nGridStepY;
	int skipx=XdirNum/nGridStepX;
	int tempcount=0;
	register int j;
	TCHAR text[128]={0,};
	
	glPushMatrix();
	glTranslatef(Orgin.x+StartX,Orgin.y+StartY,Orgin.z);

	for(j=0; j<XdirNum; j++) //X 축 GRID 
	{
		glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex3d(Xpitch*j,0,Orgin.z);
		glVertex3d(Xpitch*j,Ypitch*(YDirnum-1),Orgin.z);
		glEnd();

		if(j==0 || j== XdirNum-1)
		{
				
			if(Option == G_GRID_TEXT || Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
			{
				_stprintf(text,_T("%3.1f"),Xpitch*j+StartX);

				DrawText(text,Xpitch*j-15,-17,Orgin.z,0.1,1.0,TextColor);
			}

			tempcount++;
		}
		else
		{
			if(tempcount>=skipx)
			{
				tempcount=0;

				if(Option == G_GRID_TEXT || Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
				{

					_stprintf(text,_T("%3.1f"),Xpitch*j+StartX);

					DrawText(text,Xpitch*j-15,-17,Orgin.z,0.1,1.0,TextColor);
				}					

			}
			tempcount++;
		}
	}
	tempcount=0;	
	
	for(j=0; j<YDirnum; j++) //Y 축 GRID 
	{
		glBegin(GL_LINES);
		glColor3f(1.0,1.0,1.0);
		glVertex3d(0,Ypitch*j,Orgin.z);
		glVertex3d(Xpitch*(XdirNum-1),Ypitch*j,Orgin.z);
		glEnd();	
		
		if(j==0 || j== YDirnum-1)
		{

			if(Option == G_GRID_TEXT)
			{
				_stprintf(text,_T("%3.1f"),Ypitch*j+StartY);

				if(j==0)
				DrawText(text,-50,Ypitch*j+5,Orgin.z,0.1,1.0,TextColor);
				else
				DrawText(text,-50,Ypitch*j-5,Orgin.z,0.1,1.0,TextColor);
			}
			else if(Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
			{
				_stprintf(text,_T("%3.1f"),(Ypitch*(YDirnum-1)-Ypitch*j)+StartY);

				if(j==0)
				DrawText(text,-50,Ypitch*j+5,Orgin.z,0.1,1.0,TextColor);
				else
				DrawText(text,-50,Ypitch*j-5,Orgin.z,0.1,1.0,TextColor);
			}

			tempcount++;
		}
		else
		{
			if(tempcount>=skipy)
			{
				tempcount=0;

				if(Option == G_GRID_TEXT)
				{
					_stprintf(text,_T("%3.1f"),Ypitch*j+StartY);
					DrawText(text,-50,Ypitch*j-5,Orgin.z,0.1,1.0,TextColor);
				}
				else if(Option == G_GRID_TEXT+G_GRID_TEXT_INVERT)
				{
					_stprintf(text,_T("%3.1f"),(Ypitch*(YDirnum-1)-Ypitch*j)+StartY);
					if(j==0)
					DrawText(text,-50,Ypitch*j+5,Orgin.z,0.1,1.0,TextColor);
					else
					DrawText(text,-50,Ypitch*j-5,Orgin.z,0.1,1.0,TextColor);
				}

			}
			tempcount++;
		}
	}
	glPopMatrix();

}

void COpenGLDraw::DrawAxisXYZ(GLfloat Position_X,GLfloat Position_Y,GLfloat Position_Z,double Length,double thick) // X,Y,Z 각도상태를 나타내는 객체
{
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);


	glPushMatrix();
	glTranslatef(Position_X,Position_Y,Position_Z);
	
	glLineWidth(thick);
	glBegin(GL_LINES);

	glColor3ub(255.0f,0,0); // r x
	glVertex3f(0,0,0);
	glVertex3f(Length,0,0);

	glColor3ub(0,255.0f,0);// g y
	glVertex3f(0,0,0);
	glVertex3f(0,Length,0);

	glColor3ub(0,0,255.0f);// b z
	glVertex3f(0,0,0);
	glVertex3f(0,0,Length);
	glEnd();
	
	
	
	DrawText(_T("X+"),Length+1,0,Position_Z,0.1,0.1,RGB(255,0,0));
	DrawText(_T("Y+"),0,Length+1,Position_Z,0.1,0.1,RGB(0,255,0));
	DrawText(_T("Z+"),0,0,Length+1+Position_Z,0.1,0.1,RGB(0,0,255));
	glPopMatrix();
	glLineWidth(lineWidth);
}

void COpenGLDraw::DrawLine(const CdPoint3D* pVtArray,int nPtNum,int Flag,double width,GLfloat Origin_Shift_X,GLfloat Origin_Shift_Y,GLfloat Origin_Shift_Z)
{	
	int i=0;


	if(pVtArray==NULL)
	{
		return;
	}
	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH,&lineWidth);
	glLineWidth(width);
	if(Flag!=GL_LINE_STRIP)
	glBegin(GL_LINES);
	else
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,1.0,1.0);

	if(Flag!=GL_LINE_STRIP)
	{
	glVertex3f(pVtArray[0].x,pVtArray[0].y,pVtArray[0].z);
	glVertex3f(pVtArray[nPtNum-1].x,pVtArray[nPtNum-1].y,pVtArray[nPtNum-1].z);
	}
	else
	{
		for(i=0; i<nPtNum; i++)
		{
			glVertex3f(pVtArray[i].x,pVtArray[i].y,pVtArray[i].z);

		}
	}


	glEnd();
	glLineWidth(lineWidth);
}

