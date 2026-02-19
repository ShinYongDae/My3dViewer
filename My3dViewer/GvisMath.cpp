#include "stdafx.h"
#include "GvisMath.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <gl/freeglut_std.h>
#pragma comment (lib, "freeglut.lib")

///////////////////////////////////////////////
CfPoint::CfPoint()
{
/* random filled */
	x = 0.0;
	y = 0.0;
}

CfPoint::CfPoint(float initfX, float initfY)
{
	x=initfX;
	y=initfY;
}
/*
CfPoint::CfPoint(FPOINT initfPt)
{
	*(CfPoint*)this = initfPt;
}
*/
CfPoint::~CfPoint()
{

}
void CfPoint::Offset(float fXOffset,float fYOffset)
{
	x += fXOffset;
	y += fYOffset;	
}

void CfPoint::Offset(FPOINT fPoint)
{
	x += fPoint.x;
	y += fPoint.y;	
}


CfPoint CfPoint::Round( FPOINT fPoint, int nPos)
{
	CfPoint fTemp;
	fTemp.x = fPoint.x * pow( 10.0, nPos );
	fTemp.x = floor( fTemp.x + 0.5 );
	fTemp.x *= pow( 10.0, -nPos );

	fTemp.y = fPoint.y * pow( 10.0, nPos );
	fTemp.y = floor( fTemp.y + 0.5 );
	fTemp.y *= pow( 10.0, -nPos );

	return fTemp;
}

BOOL CfPoint::operator ==(FPOINT fPoint) const
{
	return (x == fPoint.x && y == fPoint.y);
}

BOOL CfPoint::operator !=(FPOINT fPoint) const
{
	return (x != fPoint.x || y != fPoint.y);
}

void CfPoint::operator +=(FPOINT fPoint)
{
	x += fPoint.x; y += fPoint.y;
}

void CfPoint::operator -=(FPOINT fPoint)
{
	x -= fPoint.x; y -= fPoint.y;
}

CfPoint CfPoint::operator +(FPOINT fPoint ) const
{
	return CfPoint(x + fPoint.x, y + fPoint.y);
}


CfPoint CfPoint::operator -(FPOINT fPoint ) const
{
	return CfPoint(x - fPoint.x, y - fPoint.y);
}

//	CdRect CdPoint::operator -(const RECT* lpRect ) const
CfPoint CfPoint::operator -() const
{
	return CfPoint(-x, -y);
}

////////////////////////////////////////////////////////////////////
CdPoint::CdPoint()
{
/* random filled */
}

CdPoint::CdPoint(double initfX, double initfY)
{
	x=initfX;
	y=initfY;
}
CdPoint::CdPoint(DPOINT initfPt)
{
	*(DPOINT*)this = initfPt;
}
CdPoint::CdPoint(DSIZE initfSize)
{
//	*(DSIZE*)this = initfSize;
	x = initfSize.cx;
	y = initfSize.cy;
}
CdPoint::CdPoint(DWORD dwPoint)
{
	x = (short)LOWORD(dwPoint);
	y = (short)HIWORD(dwPoint);
}
CdPoint::~CdPoint()
{

}
void CdPoint::Offset(double fXOffset,double fYOffset)
{
	x += fXOffset;
	y += fYOffset;	
}

void CdPoint::Offset(DPOINT fPoint)
{
	x += fPoint.x;
	y += fPoint.y;	
}
void CdPoint::Offset(DSIZE fSize)
{
	x += fSize.cx;
	y += fSize.cy;
}

CdPoint CdPoint::Round( CdPoint fPoint, int nPos)
{
	CdPoint fTemp;
	fTemp.x = fPoint.x * pow( 10.0, nPos );
	fTemp.x = floor( fTemp.x + 0.5 );
	fTemp.x *= pow( 10.0, -nPos );

	fTemp.y = fPoint.y * pow( 10.0, nPos );
	fTemp.y = floor( fTemp.y + 0.5 );
	fTemp.y *= pow( 10.0, -nPos );

	return fTemp;
}

BOOL CdPoint::operator ==(DPOINT fPoint) const
{
	return (x == fPoint.x && y == fPoint.y);
}

BOOL CdPoint::operator !=(DPOINT fPoint) const
{
	return (x != fPoint.x || y != fPoint.y);
}

void CdPoint::operator +=(DSIZE  fSize)
{
	x += fSize.cx; y += fSize.cy;
}
void CdPoint::operator +=(DPOINT fPoint)
{
	x += fPoint.x; y += fPoint.y;
}
void CdPoint::operator -=(DSIZE  fSize)
{
	x += fSize.cx; y += fSize.cy;
}
void CdPoint::operator -=(DPOINT fPoint)
{
	x -= fPoint.x; y -= fPoint.y;
}
CdPoint CdPoint::operator +(DSIZE fSize ) const
{
	return CdPoint(x + fSize.cx, y + fSize.cy);
}
CdPoint CdPoint::operator +(DPOINT fPoint ) const
{
	return CdPoint(x + fPoint.x, y + fPoint.y);
}
CdRect CdPoint::operator +( const DRECT* lpfRect ) const
{
	return CdRect(lpfRect->left+x,lpfRect->top+y,lpfRect->right+x,lpfRect->bottom+y);
}
CdSize CdPoint::operator -(DPOINT fPoint ) const
{
	return CdSize(x - fPoint.x, y - fPoint.y);
}
CdPoint CdPoint::operator -(DSIZE fSize ) const
{
	return CdPoint(x - fSize.cx, y - fSize.cy);
}
CdRect CdPoint::operator -( const DRECT* lpfRect ) const
{
	return CdRect(lpfRect->left-x,lpfRect->top-y,lpfRect->right-x,lpfRect->bottom-y);
}
/*
CdPoint CdPoint::operator -(DPOINT fPoint ) const
{
	return CdPoint(x - fPoint.x, y - fPoint.y);
}
*/
//	CdRect CdPoint::operator -(const RECT* lpRect ) const
CdPoint CdPoint::operator -() const
{
	return CdPoint(-x, -y);
}

/////////////////////////////////////////////////////////////////////////////////////////////

CdPoint3D::CdPoint3D()
{
/* random filled */
}
CdPoint3D::CdPoint3D(double initfX, double initfY, double initfZ)
{
	x=initfX;
	y=initfY;
	z=initfZ;
}
CdPoint3D::CdPoint3D(DPOINT3D initfPt)
{
	*(DPOINT3D*)this = initfPt;
}

CdPoint3D::~CdPoint3D()
{

}
void CdPoint3D::Offset(double fXOffset,double fYOffset,double fZOffset)
{
	x += fXOffset;
	y += fYOffset;
	z += fZOffset;
}

void CdPoint3D::Offset(DPOINT3D fPoint)
{
	x += fPoint.x;
	y += fPoint.y;	
	z += fPoint.z;	
}

CdPoint3D CdPoint3D::Round( CdPoint3D fPoint, int nPos)
{
	CdPoint3D fTemp;
	fTemp.x = fPoint.x * pow( 10.0, nPos );
	fTemp.x = floor( fTemp.x + 0.5 );
	fTemp.x *= pow( 10.0, -nPos );

	fTemp.y = fPoint.y * pow( 10.0, nPos );
	fTemp.y = floor( fTemp.y + 0.5 );
	fTemp.y *= pow( 10.0, -nPos );

	fTemp.z = fPoint.z * pow( 10.0, nPos );
	fTemp.z = floor( fTemp.z + 0.5 );
	fTemp.z *= pow( 10.0, -nPos );

	
	return fTemp;
}

BOOL CdPoint3D::operator ==(DPOINT3D fPoint) const
{
	return (x == fPoint.x && y == fPoint.y && z == fPoint.z);
}

BOOL CdPoint3D::operator !=(DPOINT3D fPoint)  const
{
	return (x != fPoint.x || y != fPoint.y || z != fPoint.z);
}

void CdPoint3D::operator +=(DPOINT3D fPoint)
{
	x += fPoint.x; y += fPoint.y; z += fPoint.z;
}

void CdPoint3D::operator -=(DPOINT3D fPoint)
{
	x -= fPoint.x; y -= fPoint.y; z -= fPoint.z;
}

CdPoint3D CdPoint3D::operator +(DPOINT3D fPoint ) const
{
	return CdPoint3D(x + fPoint.x, y + fPoint.y, z + fPoint.z);
}

CdPoint3D CdPoint3D::operator -(DPOINT3D fPoint ) const
{
	return CdPoint3D(x - fPoint.x, y - fPoint.y, z - fPoint.z);
}

//130703 LGH ADD
CdPoint3D::CdPoint3D(CdPoint3D& vt) 
{
	x = vt.x; 
	y = vt.y;
	z = vt.z;
}

CdPoint3D CdPoint3D::operator + (CdPoint3D& fPoint) 
{	
	CdPoint3D sum;
	sum.x = x + fPoint.x;
	sum.y = y + fPoint.y;
	sum.z = z + fPoint.z;
	return sum;
}


void CdPoint3D:: operator = (CdPoint3D& fPoint)
{
	x = fPoint.x;
	y = fPoint.y;
	z = fPoint.z;
}

CdPoint3D CdPoint3D::operator - (CdPoint3D& fPoint)
{
	CdPoint3D sum;
	sum.x = x - fPoint.x;
	sum.y = y - fPoint.y;
	sum.z = z - fPoint.z;
	return sum;
}
	
CdPoint3D CdPoint3D::operator / (float div)
{
	CdPoint3D fDivison;
	
	if(div==0.0)
	{
		fDivison.x=0.0;
		fDivison.y=0.0;
		fDivison.z=0.0;
	}
	else
	{

		fDivison.x = x /div;
		fDivison.y = y /div;
		fDivison.z = z /div;
	}

	return fDivison;
}

CdPoint3D CdPoint3D::operator *(CdPoint3D& fDivison)
{
	CdPoint3D fMultiPly;

	fMultiPly.x = y*fDivison.z-z*fDivison.y;
	fMultiPly.y = z*fDivison.x-x*fDivison.z;
	fMultiPly.z = x*fDivison.y-y*fDivison.x;

	return fMultiPly;
}

CdPoint3D CdPoint3D::operator * (double dDivison)
{
	CdPoint3D fMultiPly;

	if(dDivison == 0.0)
	{
		fMultiPly.x = 0.0;
		fMultiPly.y = 0.0;
		fMultiPly.z = 0.0;
	}
	else
	{
		fMultiPly.x = x *dDivison;
		fMultiPly.y = y *dDivison;
		fMultiPly.z = z *dDivison;
	}

	return fMultiPly;
}

void CdPoint3D::Normalize()
{
	double mag = Magnitude();

	if(mag!=0.)
	{
		x/=(float)mag;
		y/=(float)mag;
		z/=(float)mag;
	}

}

double CdPoint3D::Magnitude()
{
	return sqrt( SQR(x) + SQR(y) + SQR(z) );
}
//ADD END


/////////////////////////////////////////////////////////////////////////////////////////////
CfSize::CfSize()
{
}
CfSize::CfSize(float initfCX, float initfCY)
{
	cx = initfCX;
	cy = initfCY;
}
CfSize::CfSize(FSIZE initfSize)
{
	*(FSIZE*)this = initfSize;
}
CfSize::CfSize(FPOINT initfPt)
{
	//	*(FPOINT*)this = initfPt; 
	cx = initfPt.x;
	cy = initfPt.y;
}
CfSize::CfSize(DWORD dwSize)
{
	cx = (short)LOWORD(dwSize);
	cy = (short)HIWORD(dwSize);
}
CfSize::~CfSize()
{

}

// Checks for equality between two sizes.
// Returns nonzero if the sizes are equal, otherwize 0.
BOOL CfSize::operator ==(FSIZE fSize) const
{
	return (cx == fSize.cx && cy == fSize.cy);
}

// Checks for inequality between two sizes.
// Returns nonzero if the sizes are not equal, otherwise 0.
BOOL CfSize::operator !=(FSIZE fSize) const
{
	return (cx != fSize.cx || cy != fSize.cy);
}

// Adds a fSize to this CfSize.
void CfSize::operator += (FSIZE fSize)
{
	cx += fSize.cx; cy += fSize.cy;
}

// Subtracts a size from this CfSize.
void CfSize::operator -=(FSIZE fSize)
{
	cx -= fSize.cx; cy -= fSize.cy;
}

// This operation adds two CSize values.
CfSize CfSize::operator +(FSIZE fSize) const
{
	return CfSize(cx + fSize.cx, cy + fSize.cy);
}

// The cx and cy members of this CSize value are added
// to the x and y data members of the POINT value
CfPoint CfSize::operator +(FPOINT fPoint) const
{
	return CfPoint(cx + fPoint.x, cy + fPoint.y);
}

// This operation subtracts two CSize values.
CfSize CfSize::operator -(FSIZE fSize) const
{
	return CfSize(cx - fSize.cx, cy - fSize.cy);
}

// This operation offsets (moves) aFPOINT or CdPoint value by the additive inverse 
// of this CdSize value. The cx and cy of this CdSize value are subtracted from 
// the x and y data members of the FPOINT value. 
// It is analogous to the version of CdPoint::operator - that takes aFSIZE parameter.
CfPoint CfSize::operator -(FPOINT fPoint) const
{
	return CfPoint(cx - fPoint.x, cy - fPoint.y);
}

// This operation offsets (moves) aRECT or CRect value by the additive inverse of this CSize value.
// The cx and cy members of this CSize value are subtracted from the left, top, right, and bottom data members of the RECT value. 
// It is analogous to the version of CRect::operator - that takes aSIZE parameter.
//CdRect operator -(const DRECT* lpfRect ) const;
//{
//}

// This operation returns the additive inverse of this CSize value.
CfSize CfSize::operator -() const
{
	return CfSize(-cx, -cy);
}

/////////////////////////////////////////////////////////////////////////////////////////////
CdSize::CdSize()
{
}
CdSize::CdSize(double initfCX,double initfCY)
{
	cx = initfCX;
	cy = initfCY;
}
CdSize::CdSize(DSIZE initfSize)
{
	*(DSIZE*)this = initfSize;
}
CdSize::CdSize(DPOINT initfPt)
{
//	*(DPOINT*)this = initfPt; 
	cx = initfPt.x;
	cy = initfPt.y;
}
CdSize::CdSize(DWORD dwSize)
{
	cx = (short)LOWORD(dwSize);
	cy = (short)HIWORD(dwSize);
}
CdSize::~CdSize()
{

}

// Checks for equality between two sizes.
// Returns nonzero if the sizes are equal, otherwize 0.
BOOL CdSize::operator ==(DSIZE fSize) const
{
	return (cx == fSize.cx && cy == fSize.cy);
}

// Checks for inequality between two sizes.
// Returns nonzero if the sizes are not equal, otherwise 0.
BOOL CdSize::operator !=(DSIZE fSize ) const
{
	return (cx != fSize.cx || cy != fSize.cy);
}

// Adds a fSize to this CdSize.
void CdSize::operator += (DSIZE fSize)
{
	cx += fSize.cx; cy += fSize.cy;
}

// Subtracts a size from this CdSize.
void CdSize::operator -=(DSIZE fSize)
{
	cx -= fSize.cx; cy -= fSize.cy;
}

// This operation adds two CSize values.
CdSize CdSize::operator +(DSIZE fSize) const
{
	return CdSize(cx+fSize.cx, cy+fSize.cy);
}

// The cx and cy members of this CSize value are added
// to the x and y data members of the POINT value
CdPoint CdSize::operator +(DPOINT fPoint ) const
{
	return CdPoint(cx + fPoint.x, cy + fPoint.y);
}

// This operation subtracts two CSize values.
CdSize CdSize::operator -(DSIZE fSize) const
{
	return CdSize(cx-fSize.cx, cy-fSize.cy);
}

// This operation offsets (moves) aFPOINT or CdPoint value by the additive inverse 
// of this CdSize value. The cx and cy of this CdSize value are subtracted from 
// the x and y data members of the DPOINT value. 
// It is analogous to the version of CdPoint::operator - that takes aFSIZE parameter.
CdPoint CdSize::operator -(DPOINT fPoint) const
{
	return CdPoint(cx-fPoint.x, cy-fPoint.y);
}

// This operation offsets (moves) aRECT or CRect value by the additive inverse of this CSize value.
// The cx and cy members of this CSize value are subtracted from the left, top, right, and bottom data members of the RECT value. 
// It is analogous to the version of CRect::operator - that takes aSIZE parameter.
//CdRect operator -(const DRECT* lpfRect ) const;
//{
//}

// This operation returns the additive inverse of this CSize value.
CdSize CdSize::operator -() const
{
	return CdSize(-cx,-cy);
}
/////////////////////////////////////////////////////////////////////////////////////////////
// CdSize3D Class
/////////////////////////////////////////////////////////////////////////////////////////////
CdSize3D::CdSize3D()
{
}
CdSize3D::CdSize3D(double initfCX,double initfCY,double initfCZ)
{
	cx = initfCX;
	cy = initfCY;
	cz = initfCZ;
}
CdSize3D::CdSize3D(DSIZE3D initfSize)
{
	*(DSIZE3D*)this = initfSize;
}
CdSize3D::CdSize3D(DPOINT3D initfPt)
{
	cx = initfPt.x;
	cy = initfPt.y;
	cz = initfPt.z;
}

CdSize3D::~CdSize3D()
{

}

// Checks for equality between two sizes.
// Returns nonzero if the sizes are equal, otherwize 0.
BOOL CdSize3D::operator ==(DSIZE3D fSize) const
{
	return (cx == fSize.cx && cy == fSize.cy && cz == fSize.cz);
}

// Checks for inequality between two sizes.
// Returns nonzero if the sizes are not equal, otherwise 0.
BOOL CdSize3D::operator !=(DSIZE3D fSize ) const
{
	return (cx != fSize.cx || cy != fSize.cy || cz != fSize.cz);
}

// Adds a fSize to this CdSize.
void CdSize3D::operator += (DSIZE3D fSize)
{
	cx += fSize.cx; cy += fSize.cy; cz += fSize.cz;
}

// Subtracts a size from this CdSize.
void CdSize3D::operator -=(DSIZE3D fSize)
{
	cx -= fSize.cx; cy -= fSize.cy; cz -= fSize.cz;
}

// This operation adds two CSize values.
CdSize3D CdSize3D::operator +(DSIZE3D fSize) const
{
	return CdSize3D(cx+fSize.cx, cy+fSize.cy, cz+fSize.cz);
}

// The cx and cy members of this CSize value are added
// to the x and y data members of the POINT value
CdPoint3D CdSize3D::operator +(DPOINT3D fPoint ) const
{
	return CdPoint3D(cx + fPoint.x, cy + fPoint.y, cz + fPoint.z);
}

// This operation subtracts two CSize values.
CdSize3D CdSize3D::operator -(DSIZE3D fSize) const
{
	return CdSize3D(cx-fSize.cx, cy-fSize.cy, cz-fSize.cz);
}

// This operation offsets (moves) aFPOINT or CdPoint value by the additive inverse 
// of this CdSize value. The cx and cy of this CdSize value are subtracted from 
// the x and y data members of the DPOINT value. 
// It is analogous to the version of CdPoint::operator - that takes aFSIZE parameter.
CdPoint3D CdSize3D::operator -(DPOINT3D fPoint) const
{
	return CdPoint3D(cx-fPoint.x, cy-fPoint.y, cz-fPoint.z);
}

// This operation offsets (moves) aRECT or CRect value by the additive inverse of this CSize value.
// The cx and cy members of this CSize value are subtracted from the left, top, right, and bottom data members of the RECT value. 
// It is analogous to the version of CRect::operator - that takes aSIZE parameter.
//CdRect operator -(const DRECT* lpfRect ) const;
//{
//}

// This operation returns the additive inverse of this CSize value.
CdSize3D CdSize3D::operator -() const
{
	return CdSize3D(-cx,-cy,-cx);
}

///////////////////////////////////////////////////////
// CdLine Class
///////////////////////////////////////////////////////
CdLine::CdLine(){}
CdLine::CdLine(DPOINT fptStart,DPOINT fptEnd){
	p1=fptStart;
	p2=fptEnd;
}
CdLine::CdLine(double sx,double sy,double ex,double ey)
{
	p1 = CdPoint(sx,sy);
	p2 = CdPoint(ex,ey);
}
CdLine::~CdLine(){}

double CdLine::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y),(p2.x - p1.x)));
}

CdPoint CdLine::CenterPoint()
{
	return CdPoint((p2.x-p1.x)/2.0+p1.x,(p2.y-p1.y)/2.0+p1.y);
}

double CdLine::Length()
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}


///////////////////////////////////////////////////////
// CfLGrid Class
///////////////////////////////////////////////////////
CfLGrid::CfLGrid()
{
	m_fStartX = 0.0; m_fStartY = 0.0; m_fPitchX = 0.0;
	m_fPitchY = 0.0; m_nCols = 0; m_nRows = 0;
	m_fSpeed = 0.0; m_fRepRate = 0.0;
}
CfLGrid::CfLGrid(DPOINT fptStart, DPOINT fptEnd)
{
	p1 = fptStart;
	p2 = fptEnd;
}
CfLGrid::CfLGrid(double sx, double sy, double ex, double ey)
{
	p1 = CdPoint(sx, sy);
	p2 = CdPoint(ex, ey);
}
CfLGrid::~CfLGrid() {}

double CfLGrid::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y), (p2.x - p1.x)));
}

CdPoint CfLGrid::CenterPoint()
{
	return CdPoint((p2.x - p1.x) / 2.0 + p1.x, (p2.y - p1.y) / 2.0 + p1.y);
}

double CfLGrid::Length()
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void CfLGrid::Set(double fStartX, double fStartY, double fPitchX, double fPitchY, int nCols, int nRows, double fSpeed, double fRepRate)
{
	m_fStartX = fStartX; m_fStartY = fStartY; m_fPitchX = fPitchX;
	m_fPitchY = fPitchY; m_nCols = nCols; m_nRows = nRows;
	m_fSpeed = fSpeed; m_fRepRate = fRepRate;
}


///////////////////////////////////////////////////////
// CfArc Class
///////////////////////////////////////////////////////
CfArc::CfArc()
{
	m_fptCenter = CdPoint(0.0, 0.0);
	m_fRadius = 0.0; m_fStartAngle = 0.0; m_fArcAngle = 0.0;
	m_fSpotSize = 0.0; m_fSpeed = 0.0; m_fRepRate = 0.0; m_fSpotSize = 0.0;
	m_nDir = 1;
}
CfArc::CfArc(DPOINT fptStart, DPOINT fptEnd)
{
	p1 = fptStart;
	p2 = fptEnd;
}
CfArc::CfArc(double sx, double sy, double ex, double ey)
{
	p1 = CdPoint(sx, sy);
	p2 = CdPoint(ex, ey);
}
CfArc::~CfArc() {}

double CfArc::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y), (p2.x - p1.x)));
}

double CfArc::Length()
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void CfArc::Set(CdPoint fptCenter, double fRadius, double fStartAngle, double fArcAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir)
{
	m_fptCenter = fptCenter;
	m_fRadius = fRadius; m_fStartAngle = fStartAngle; m_fArcAngle = fArcAngle; m_fSpeed = fSpeed;
	m_fSpotSize = fRepRate; m_fRepRate = fRepRate; m_fSpotSize = fSpotSize;
	m_nDir = nDir;
}


///////////////////////////////////////////////////////
// CfCircle Class
///////////////////////////////////////////////////////
CfCircle::CfCircle()
{
	m_fptCenter = CdPoint(0.0, 0.0);
	m_fRadius = 0.0; m_fStartAngle = 0.0;
	m_fSpotSize = 0.0; m_fSpeed = 0.0; m_fRepRate = 0.0; m_fSpotSize = 0.0;
	m_nDir = 1;
}
CfCircle::CfCircle(DPOINT fptStart, DPOINT fptEnd)
{
	p1 = fptStart;
	p2 = fptEnd;
}
CfCircle::CfCircle(double sx, double sy, double ex, double ey)
{
	p1 = CdPoint(sx, sy);
	p2 = CdPoint(ex, ey);
}
CfCircle::~CfCircle() {}

double CfCircle::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y), (p2.x - p1.x)));
}

double CfCircle::Length()
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void CfCircle::Set(CdPoint fptCenter, double fRadius, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir)
{
	m_fptCenter = fptCenter;
	m_fRadius = fRadius; m_fStartAngle = fStartAngle; m_fSpeed = fSpeed;
	m_fSpotSize = fRepRate; m_fRepRate = fRepRate; m_fSpotSize = fSpotSize;
	m_nDir = nDir;
}


///////////////////////////////////////////////////////
// CfTrepan Class
///////////////////////////////////////////////////////
CfTrepan::CfTrepan()
{
	m_fptCenter = CdPoint(0.0, 0.0);
	m_fOuterDiameter = 0.0; m_fInnerDiameter = 0.0; m_fStartAngle = 0.0;
	m_fSpotSize = 0.0; m_fSpeed = 0.0; m_fRepRate = 0.0; m_fSpotSize = 0.0;
	m_nDir = 1;
}
CfTrepan::CfTrepan(DPOINT fptStart, DPOINT fptEnd)
{
	p1 = fptStart;
	p2 = fptEnd;
}
CfTrepan::CfTrepan(double sx, double sy, double ex, double ey)
{
	p1 = CdPoint(sx, sy);
	p2 = CdPoint(ex, ey);
}
CfTrepan::~CfTrepan() {}

double CfTrepan::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y), (p2.x - p1.x)));
}

double CfTrepan::Length()
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void CfTrepan::Set(CdPoint fptCenter, double fOuterDiameter, double fInnerDiameter, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir)
{
	m_fptCenter = fptCenter;
	m_fOuterDiameter = fOuterDiameter; m_fInnerDiameter = fInnerDiameter; m_fStartAngle = fStartAngle; m_fSpeed = fSpeed;
	m_fSpotSize = fRepRate; m_fRepRate = fRepRate; m_fSpotSize = fSpotSize;
	m_nDir = nDir;
}


///////////////////////////////////////////////////////
// CfSpiral Class
///////////////////////////////////////////////////////
CfSpiral::CfSpiral()
{
	m_fptCenter = CdPoint(0.0, 0.0);
	m_fRadialPitch = 0.0;
	m_fOuterDiameter = 0.0; m_fInnerDiameter = 0.0; m_fStartAngle = 0.0;
	m_fSpotSize = 0.0; m_fSpeed = 0.0; m_fRepRate = 0.0; m_fSpotSize = 0.0;
	m_nDir = 1;
	m_bLastCircle = FALSE;
}
CfSpiral::CfSpiral(DPOINT fptStart, DPOINT fptEnd)
{
	p1 = fptStart;
	p2 = fptEnd;
}
CfSpiral::CfSpiral(double sx, double sy, double ex, double ey)
{
	p1 = CdPoint(sx, sy);
	p2 = CdPoint(ex, ey);
}
CfSpiral::~CfSpiral() {}

double CfSpiral::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y), (p2.x - p1.x)));
}

double CfSpiral::Length()
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void CfSpiral::Set(CdPoint fptCenter, double fOuterDiameter, double fInnerDiameter, double fRadialPitch, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir, BOOL bLastCircle)
{
	m_fptCenter = fptCenter;
	m_fRadialPitch = fRadialPitch;
	m_fOuterDiameter = fOuterDiameter; m_fInnerDiameter = fInnerDiameter; m_fStartAngle = fStartAngle; m_fSpeed = fSpeed;
	m_fSpotSize = fRepRate; m_fRepRate = fRepRate; m_fSpotSize = fSpotSize;
	m_nDir = nDir;
	m_bLastCircle = bLastCircle;
}



///////////////////////////////////////////////////////
// CfSpiralCircle Class
///////////////////////////////////////////////////////
CfSpiralCircle::CfSpiralCircle()
{
	m_fptCenter = CdPoint(0.0, 0.0);
	m_fRadialPitch = 0.0;
	m_fOuterDiameter = 0.0; m_fStartAngle = 0.0;
	m_fSpotSize = 0.0; m_fSpeed = 0.0; m_fRepRate = 0.0; m_fSpotSize = 0.0;
}
CfSpiralCircle::CfSpiralCircle(DPOINT fptStart, DPOINT fptEnd)
{
	p1 = fptStart;
	p2 = fptEnd;
}
CfSpiralCircle::CfSpiralCircle(double sx, double sy, double ex, double ey)
{
	p1 = CdPoint(sx, sy);
	p2 = CdPoint(ex, ey);
}
CfSpiralCircle::~CfSpiralCircle() {}

double CfSpiralCircle::Angle()
{
	return RAD2DEG*(atan2((p2.y - p1.y), (p2.x - p1.x)));
}

double CfSpiralCircle::Length()
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

void CfSpiralCircle::Set(CdPoint fptCenter, double fOuterDiameter, double fRadialPitch, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate)
{
	m_fptCenter = fptCenter;
	m_fRadialPitch = fRadialPitch;
	m_fOuterDiameter = fOuterDiameter; m_fStartAngle = fStartAngle; m_fSpeed = fSpeed;
	m_fSpotSize = fRepRate; m_fRepRate = fRepRate; m_fSpotSize = fSpotSize;
}

///////////////////////////////////////////////////////
// CdLine3D Class
///////////////////////////////////////////////////////
CdLine3D::CdLine3D(){}
CdLine3D::CdLine3D(DPOINT3D fptStart,DPOINT3D fptEnd){
	p1=fptStart;
	p2=fptEnd;
}
CdLine3D::CdLine3D(double sx,double sy,double sz,double ex,double ey,double ez)
{
	p1 = CdPoint3D(sx,sy,sz);
	p2 = CdPoint3D(ex,ey,ez);
}
CdLine3D::~CdLine3D(){}

CdPoint3D CdLine3D::CenterPoint()
{
	return CdPoint3D((p2.x-p1.x)/2.0+p1.x,(p2.y-p1.y)/2.0+p1.y,(p2.z-p1.z)/2.0+p1.z);
}

double CdLine3D::Length()
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
}


//////////////////////////////////////////////////////////////////////
// CdRect Class
//////////////////////////////////////////////////////////////////////
CfRect::CfRect() {}
CfRect::CfRect(float l, float t, float r, float b)
{
	left = l;	top = t;	right = r;	bottom = b;
	m_fWidth = r - l;
	m_fHeight = t - b;
}
CfRect::~CfRect() {}

float CfRect::Width() {
	return m_fWidth = right - left;
}
float CfRect::Height() {
	return m_fHeight = top - bottom;
}
CfSize CfRect::Size() {
	CfSize fSize;
	fSize.cx = m_fWidth;
	fSize.cy = m_fHeight;
	return fSize;
}
CfPoint CfRect::TopLeft() {
	CfPoint fPt(left, top);
	return fPt;
}
CfPoint CfRect::BottomRight() {
	CfPoint fPt(right, bottom);
	return fPt;
}
CfPoint CfRect::CenterPoint() {
	CfPoint fPt;
	fPt.x = (right + left) / 2.;
	fPt.y = (bottom + top) / 2.;
	return fPt;
}
BOOL CfRect::IsRectEmpty() {
	if (m_fHeight <= 0. || m_fWidth <= 0.)
		return TRUE;
	return FALSE;
}
BOOL CfRect::IsRectNull() {
	if (left == 0. && top == 0. && right == 0. && bottom == 0.)
		return TRUE;
	return FALSE;
}
BOOL CfRect::PtInRect(CfPoint fPt) {
	if (fPt.x >= left && fPt.x < right && fPt.y < top && fPt.y >= bottom)
		return TRUE;
	return FALSE;
}
void CfRect::SetRect(float x1, float y1, float x2, float y2)
{
	left = x1;
	top = y1;
	right = x2;
	bottom = y2;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::SetRectEmpty() {
	left = right = top = bottom = 0.;
	m_fWidth = 0.;
	m_fHeight = 0.;
}
void CfRect::CopyRect(LPCFRECT lpSrcfRect) {
	left = lpSrcfRect->left;
	right = lpSrcfRect->right;
	top = lpSrcfRect->top;
	bottom = lpSrcfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
BOOL CfRect::EqualRect(LPCFRECT lpfRect) {
	if (lpfRect->left == left && lpfRect->top == top &&
		lpfRect->right == right && lpfRect->bottom == bottom)
		return TRUE;
	return FALSE;
}
void CfRect::InflateRect(float x, float y) {
	left = left - x;
	right = right + x;
	top = top - y;
	bottom = bottom + y;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::InflateRect(FSIZE fSize) {
	left = left - fSize.cx;
	right = right + fSize.cx;
	top = top - fSize.cy;
	bottom = bottom + fSize.cy;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::InflateRect(LPCFRECT lpfRect) {
	left = left - lpfRect->left;
	right = right + lpfRect->right;
	top = top - lpfRect->top;
	bottom = bottom + lpfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::InflateRect(float l, float t, float r, float b) {
	left = left - l;
	right = right + t;
	top = top - r;
	bottom = bottom + b;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(float x, float y) {
	left = left + x;
	right = right - x;
	top = top + y;
	bottom = bottom - y;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(FSIZE fSize) {
	left = left + fSize.cx;
	right = right - fSize.cx;
	top = top + fSize.cy;
	bottom = bottom - fSize.cy;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(LPCFRECT lpfRect) {
	left = left + lpfRect->left;
	right = right - lpfRect->right;
	top = top + lpfRect->top;
	bottom = bottom - lpfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::DeflateRect(float l, float t, float r, float b) {
	left = left + l;
	right = right - t;
	top = top + r;
	bottom = bottom - b;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CfRect::NormalizeRect() {
	if (left > right)
		swap(left, right);
	if (top > bottom)
		swap(top, bottom);
}
void CfRect::OffsetRect(float x, float y) {
	left += x;
	right += x;
	top += y;
	bottom += y;
}
void CfRect::OffsetRect(FPOINT fPoint) {
	left += fPoint.x;
	right += fPoint.x;
	top += fPoint.y;
	bottom += fPoint.y;
}
void CfRect::OffsetRect(FSIZE fSize) {
	left += fSize.cx;
	right += fSize.cx;
	top += fSize.cy;
	bottom += fSize.cy;
}
BOOL CfRect::SubtractRect(LPCFRECT lpfRectSrc1, LPCFRECT lpfRectSrc2)
{
	BOOL bChanged = FALSE;
	int nOverlap = 0;
	left = lpfRectSrc1->left;
	top = lpfRectSrc1->top;
	right = lpfRectSrc1->right;
	bottom = lpfRectSrc1->bottom;
	if ((lpfRectSrc2->left <= lpfRectSrc1->left) && (lpfRectSrc2->right >= lpfRectSrc1->right))
	{
		if ((lpfRectSrc2->top > lpfRectSrc1->top) && (lpfRectSrc2->top < lpfRectSrc1->bottom))
		{
			bottom = lpfRectSrc2->top;
			bChanged = TRUE;
		}
		if ((lpfRectSrc2->bottom < lpfRectSrc1->bottom) && (lpfRectSrc2->bottom > lpfRectSrc1->top))
		{
			top = lpfRectSrc2->bottom;
			bChanged = TRUE;
		}
		nOverlap++;
	}
	if ((lpfRectSrc2->top <= lpfRectSrc1->top) && (lpfRectSrc2->bottom >= lpfRectSrc1->bottom))
	{
		if ((lpfRectSrc2->left > lpfRectSrc1->left) && (lpfRectSrc2->left < lpfRectSrc1->right))
		{
			right = lpfRectSrc2->left;
			bChanged = TRUE;
		}
		if ((lpfRectSrc2->right < lpfRectSrc1->right) && (lpfRectSrc2->right > lpfRectSrc1->left))
		{
			left = lpfRectSrc2->right;
			bChanged = TRUE;
		}
		nOverlap++;
	}
	if (nOverlap == 2)
		left = right = top = bottom = 0.;
	return bChanged;
}

BOOL CfRect::IntersectRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2) {
	BOOL bChanged = FALSE;
	left = 0.;
	top = 0.;
	right = 0.;
	bottom = 0.;

	if ((lpfRect2->left > lpfRect1->left) && (lpfRect2->left < lpfRect1->right))
	{
		left = lpfRect2->left;
		bChanged = TRUE;
	}

	if ((lpfRect2->right > lpfRect1->left) && (lpfRect2->right < lpfRect1->right))
	{
		right = lpfRect2->right;
		bChanged = TRUE;
	}

	if ((lpfRect2->top > lpfRect1->top) && (lpfRect2->top < lpfRect1->bottom))
	{
		top = lpfRect2->top;
		bChanged = TRUE;
	}

	if ((lpfRect2->bottom > lpfRect1->top) && (lpfRect2->bottom < lpfRect1->bottom))
	{
		bottom = lpfRect2->bottom;
		bChanged = TRUE;
	}
	return bChanged;
}

BOOL CfRect::UnionRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2) {

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// CdRect Class
//////////////////////////////////////////////////////////////////////
CdRect::CdRect(){}
CdRect::CdRect(double l, double t, double r, double b)
{
	left = l;	top = t;	right = r;	bottom = b;
	m_fWidth = r - l;
	m_fHeight= t - b;
}
CdRect::~CdRect(){}

double CdRect::Width(){
	return m_fWidth = right-left;
}
double CdRect::Height(){
	return m_fHeight = top-bottom;
}
CdSize CdRect::Size(){
	CdSize fSize;
	fSize.cx = m_fWidth;
	fSize.cy = m_fHeight;
	return fSize;
}
CdPoint CdRect::TopLeft(){
	CdPoint fPt(left,top);
	return fPt;
}
CdPoint CdRect::BottomRight(){
	CdPoint fPt(right,bottom);
	return fPt;
}
CdPoint CdRect::CenterPoint(){
	CdPoint fPt;
	fPt.x = (right+left)/2.;
	fPt.y = (bottom+top)/2.;
	return fPt;
}
BOOL CdRect::IsRectEmpty(){
	if(m_fHeight <=0. || m_fWidth <= 0.)
		return TRUE;
	return FALSE;
}
BOOL CdRect::IsRectNull(){
	if(left == 0. && top == 0. && right == 0. && bottom == 0.)
		return TRUE;
	return FALSE;
}
BOOL CdRect::PtInRect(CdPoint fPt){
	if(fPt.x >= left && fPt.x < right && fPt.y < top && fPt.y >= bottom)
		return TRUE;
	return FALSE;
}
void CdRect::SetRect(double x1,double y1,double x2,double y2)
{
	left = x1;
	top = y1;
	right = x2;
	bottom = y2;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::SetRectEmpty(){
	left = right = top = bottom = 0.;
	m_fWidth = 0.;
	m_fHeight = 0.;
}
void CdRect::CopyRect(LPCDRECT lpSrcfRect){
	left = lpSrcfRect->left;
	right = lpSrcfRect->right;
	top = lpSrcfRect->top;
	bottom = lpSrcfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
BOOL CdRect::EqualRect(LPCDRECT lpfRect){
	if( lpfRect->left == left && lpfRect->top == top &&
		lpfRect->right == right && lpfRect->bottom == bottom)
		return TRUE;
	return FALSE;
}
void CdRect::InflateRect(double x,double y){
	left = left - x;
	right = right + x;
	top = top - y;
	bottom = bottom + y;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::InflateRect(DSIZE fSize){
	left = left - fSize.cx;
	right = right + fSize.cx;
	top = top - fSize.cy;
	bottom = bottom + fSize.cy;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::InflateRect(LPCDRECT lpfRect){
	left = left - lpfRect->left;
	right = right + lpfRect->right;
	top = top - lpfRect->top;
	bottom = bottom + lpfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::InflateRect(double l,double t,double r,double b ){
	left = left - l;
	right = right + t;
	top = top - r;
	bottom = bottom + b;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::DeflateRect(double x,double y){
	left = left + x;
	right = right - x;
	top = top + y;
	bottom = bottom - y;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::DeflateRect(DSIZE fSize){
	left = left + fSize.cx;
	right = right - fSize.cx;
	top = top + fSize.cy;
	bottom = bottom - fSize.cy;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::DeflateRect(LPCDRECT lpfRect){
	left = left + lpfRect->left;
	right = right - lpfRect->right;
	top = top + lpfRect->top;
	bottom = bottom - lpfRect->bottom;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::DeflateRect(double l,double t,double r,double b ){
	left = left + l;
	right = right - t;
	top = top + r;
	bottom = bottom - b;
	m_fWidth = right - left;
	m_fHeight = bottom - top;
}
void CdRect::NormalizeRect(){
	if(left > right)
		swap(left,right);
	if(top > bottom)
		swap(top,bottom);
}
void CdRect::OffsetRect(double x,double y){
	left += x;
	right += x;
	top += y;
	bottom += y;
}
void CdRect::OffsetRect(DPOINT fPoint){
	left += fPoint.x;
	right += fPoint.x;
	top += fPoint.y;
	bottom += fPoint.y;
}
void CdRect::OffsetRect(DSIZE fSize){
	left += fSize.cx;
	right += fSize.cx;
	top += fSize.cy;
	bottom += fSize.cy;
}
BOOL CdRect::SubtractRect(LPCDRECT lpfRectSrc1, LPCDRECT lpfRectSrc2 )
{
	BOOL bChanged = FALSE;
	int nOverlap = 0;
	left = lpfRectSrc1->left;
	top = lpfRectSrc1->top;
	right = lpfRectSrc1->right;
	bottom = lpfRectSrc1->bottom;
	if((lpfRectSrc2->left<=lpfRectSrc1->left) && (lpfRectSrc2->right>=lpfRectSrc1->right)) 
	{
		if((lpfRectSrc2->top > lpfRectSrc1->top) && (lpfRectSrc2->top < lpfRectSrc1->bottom))
		{
			bottom = lpfRectSrc2->top;
			bChanged = TRUE;
		}
		if((lpfRectSrc2->bottom < lpfRectSrc1->bottom) && (lpfRectSrc2->bottom > lpfRectSrc1->top))
		{
			top = lpfRectSrc2->bottom;
			bChanged = TRUE;
		}
		nOverlap++;
	}
	if((lpfRectSrc2->top<=lpfRectSrc1->top) && (lpfRectSrc2->bottom>=lpfRectSrc1->bottom)) 
	{
		if((lpfRectSrc2->left > lpfRectSrc1->left) && (lpfRectSrc2->left < lpfRectSrc1->right))
		{
			right = lpfRectSrc2->left;
			bChanged = TRUE;
		}
		if((lpfRectSrc2->right < lpfRectSrc1->right) && (lpfRectSrc2->right > lpfRectSrc1->left))
		{
			left = lpfRectSrc2->right;
			bChanged = TRUE;
		}
		nOverlap++;
	}
	if(nOverlap == 2)
		left = right = top = bottom = 0.;
	return bChanged;
}

BOOL CdRect::IntersectRect(LPCDRECT lpfRect1, LPCDRECT lpfRect2){
	BOOL bChanged = FALSE;
	left = 0.;
	top = 0.;
	right = 0.;
	bottom = 0.;

	if((lpfRect2->left > lpfRect1->left) && (lpfRect2->left < lpfRect1->right)) 
	{
		left = lpfRect2->left;
		bChanged = TRUE;
	}

	if((lpfRect2->right > lpfRect1->left) && (lpfRect2->right < lpfRect1->right)) 
	{
		right = lpfRect2->right;
		bChanged = TRUE;
	}
	
	if((lpfRect2->top > lpfRect1->top) && (lpfRect2->top < lpfRect1->bottom)) 
	{
		top = lpfRect2->top;
		bChanged = TRUE;
	}
	
	if((lpfRect2->bottom > lpfRect1->top) && (lpfRect2->bottom < lpfRect1->bottom)) 
	{
		bottom = lpfRect2->bottom;
		bChanged = TRUE;
	}
	return bChanged;
}

BOOL CdRect::UnionRect(LPCDRECT lpfRect1, LPCDRECT lpfRect2){

	return FALSE;
}

CdQuad::CdQuad(){}
CdQuad::~CdQuad(){}
CdQuad::CdQuad(DPOINT fptLT, DPOINT fptRT, DPOINT fptRB, DPOINT fptLB)
{
	lefttop = fptLT;
	righttop = fptRT;
	rightbottom = fptRB;
	leftbottom = fptLB;
}
CdQuad::CdQuad(DRECT rect)
{
	lefttop = CdPoint(rect.left,rect.top);
	righttop = CdPoint(rect.right,rect.top);
	rightbottom = CdPoint(rect.right,rect.bottom);
	leftbottom = CdPoint(rect.left,rect.bottom);
}
CdQuad::CdQuad(double ltx,double lty,double rtx,double rty,double rbx,double rby,double lbx,double lby)
{
	lefttop = CdPoint(ltx,lty);
	righttop = CdPoint(rtx,rty);
	rightbottom = CdPoint(rbx,rby);
	leftbottom = CdPoint(lbx,lby);
}
void CdQuad::OffsetQuad(double x,double y){
	lefttop.x += x; 
	lefttop.y += y; 
	righttop.x += x; 
	righttop.y += y; 
	rightbottom.x += x; 
	rightbottom.y += y; 
	leftbottom.x += x; 
	leftbottom.y += y; 
}
void CdQuad::OffsetQuad(DPOINT fPoint){
	lefttop.x += fPoint.x; 
	lefttop.y += fPoint.y; 
	righttop.x += fPoint.x; 
	righttop.y += fPoint.y; 
	rightbottom.x += fPoint.x; 
	rightbottom.y += fPoint.y; 
	leftbottom.x += fPoint.x; 
	leftbottom.y += fPoint.y; 
}
void CdQuad::OffsetQuad(DSIZE fSize){
	lefttop.x += fSize.cx; 
	lefttop.y += fSize.cy; 
	righttop.x += fSize.cx; 
	righttop.y += fSize.cy; 
	rightbottom.x += fSize.cx; 
	rightbottom.y += fSize.cy; 
	leftbottom.x += fSize.cx; 
	leftbottom.y += fSize.cy;
}
CdPoint CdQuad::TopLeft()
{
	CdPoint fPt(lefttop.x,lefttop.y);
	return fPt;
}
CdPoint CdQuad::TopRight()
{
	CdPoint fPt(righttop.x,righttop.y);
	return fPt;
}
CdPoint CdQuad::BottomRight()
{
	CdPoint fPt(rightbottom.x,rightbottom.y);
	return fPt;
}
CdPoint CdQuad::BottomLeft()
{
	CdPoint fPt(leftbottom.x,leftbottom.y);
	return fPt;
}

// 4각형의 중심점을 리턴한다.
CdPoint CdQuad::CenterPoint(){
	
	// 사각형으로 부터 4개의 선분을 추출한다.
	CdLine flnLeft(BottomLeft(),TopLeft());
	CdLine flnTop(TopLeft(),TopRight());
	CdLine flnRight(TopRight(),BottomRight());
	CdLine flnBottom(BottomRight(),BottomLeft());

	// 상하 및 좌우 2개의 대변의 중심점을 잇는 선분의 교점을 구한다.
	CdPoint fPt;
	GetIntersectPoint(flnLeft.CenterPoint(),
					flnRight.CenterPoint(),
					flnTop.CenterPoint(),
					flnBottom.CenterPoint(),fPt);
	return fPt;	
}

// 4각형의 대각선의 교점을 리턴한다.
BOOL CdQuad::DiagonalPoint(DPOINT &fPt)
{
	return GetIntersectPoint(TopLeft(),BottomRight(),TopRight(),BottomLeft(),fPt);
}

// 4각형의 무게 중심점을 리턴한다.
CdPoint CdQuad::CentralPoint()
{
	double p[8];
	double area = 0.0;
	double cx = 0.0;
	double cy = 0.0;
	double x1,y1,x2,y2;
	int i,j,k,l;

	p[0] = BottomLeft().x;
	p[1] = BottomLeft().y;
	p[2] = BottomRight().x;
	p[3] = BottomRight().y;
	p[4] = TopRight().x;
	p[5] = TopRight().y;
	p[6] = TopLeft().x;
	p[7] = TopLeft().y;

	for(i = 0; i < 4; i++)
	{
		j = (i+1)%4;
		k = i*2;
		l = j*2;

		x1 = p[k];
		y1 = p[k+1];
		x2 = p[l];
		y2 = p[l+1];

		area += ((x1 * y2) - (x2 * y1));
		cx += ((x1 + x2) * ((x1 * y2) - (x2 * y1)));
		cy += ((y1 + y2) * ((x1 * y2) - (x2 * y1)));

	}

	area /= 2.0;
	area = fabs(area);

//	fPt.x = cx / (area * 6.0);
//	fPt.y = cy / (area * 6.0);

	return CdPoint(cx / (area * 6.0),cy / (area * 6.0));

}

// Determines whether CRect is empty.
// A rectangle is empty if the width and/or height are 0 or negative.
BOOL CdQuad::IsQuadEmpty(){
//	if(m_fHeight <=0. || m_fWidth <= 0.)
//		return TRUE;
	return FALSE;
}
// Nonzero if CRect’s top, left, bottom, and right values are all equal to 0;
// otherwise 0.
BOOL CdQuad::IsQuadNull(){
	if(lefttop.x == 0.		&& lefttop.y == 0.		&& righttop.x == 0.		&& righttop.y == 0. && 
	   rightbottom.x == 0.	&& rightbottom.y == 0.	&& leftbottom.x == 0.	&& leftbottom.y == 0.)
		return TRUE;
	return FALSE;
}
BOOL CdQuad::PtInQuad(DPOINT fPt)
{
	// This will only handle convex quadrilaterals.
	double angle_12x = GetInteriorAngle( lefttop,righttop,fPt);
	double angle_123 = GetInteriorAngle( lefttop,righttop,rightbottom);
	if ( angle_12x > angle_123 )
		return FALSE;

	double angle_23x = GetInteriorAngle( righttop,rightbottom,fPt);
	double angle_234 = GetInteriorAngle( righttop,rightbottom,leftbottom);
	if ( angle_23x > angle_234 )
		return FALSE;

	double angle_34x = GetInteriorAngle( rightbottom,leftbottom,fPt);
	double angle_341 = GetInteriorAngle( rightbottom,leftbottom,lefttop);
	if ( angle_34x > angle_341 )
		return FALSE;

	double angle_41x = GetInteriorAngle(leftbottom,lefttop,fPt);
	double angle_412 = GetInteriorAngle(leftbottom,lefttop,righttop);
	if ( angle_41x > angle_412 )
		return FALSE;

	return TRUE;
}
void CdQuad::SetQuad(double x1,double y1,double x2,double y2,
					 double x3,double y3,double x4,double y4)
{
	lefttop = CdPoint(x1,y1);
	righttop = CdPoint(x2,y2);
	rightbottom = CdPoint(x3,y3);
	leftbottom = CdPoint(x4,y4);
}
void CdQuad::SetQuadEmpty()
{
	lefttop = CdPoint(0.,0.);
	righttop = CdPoint(0.,0.);
	rightbottom = CdPoint(0.,0.);
	leftbottom = CdPoint(0.,0.);
}
// Copies the lpSrcfQuad quadrilateral into CdQuad
void CdQuad::CopyQuad(LPCDQUAD lpSrcfQuad)
{
	*(DQUAD*)this = *lpSrcfQuad;
}
// Nonzero if the two quadrilateralS have the same top, left, bottom, and right values;
// otherwise 0.
BOOL CdQuad::EqualQuad(LPCDQUAD lpfQuad)
{
	if((CdPoint)lefttop == lpfQuad->lefttop && (CdPoint)lpfQuad->righttop == righttop &&
		(CdPoint)lpfQuad->rightbottom == rightbottom && (CdPoint)lpfQuad->leftbottom == leftbottom)
		return TRUE;
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
CdQuad3D::CdQuad3D(){}
CdQuad3D::~CdQuad3D(){}
CdQuad3D::CdQuad3D(DPOINT3D fptLT, DPOINT3D fptRT, DPOINT3D fptRB, DPOINT3D fptLB)
{
	lefttop = fptLT;
	righttop = fptRT;
	rightbottom = fptRB;
	leftbottom = fptLB;
}

CdQuad3D::CdQuad3D(CdPoint3D fptLT, CdPoint3D fptRT, CdPoint3D fptRB, CdPoint3D fptLB)
{
	lefttop = fptLT;
	righttop = fptRT;
	rightbottom = fptRB;
	leftbottom = fptLB;
}


CdQuad3D::CdQuad3D(double ltx,double lty,double ltz,double rtx,double rty,double rtz,double rbx,double rby,double rbz,double lbx,double lby,double lbz)
{
	lefttop = CdPoint3D(ltx,lty,ltz);
	righttop = CdPoint3D(rtx,rty,rtz);
	rightbottom = CdPoint3D(rbx,rby,rbz);
	leftbottom = CdPoint3D(lbx,lby,lbz);
}


void CdQuad3D::MakeQuadricArray(BOOL SetValue)
{
	if(SetValue == TRUE)
	{
		m_QuadArray[0]=(CdPoint3D)leftbottom; // 좌하 
		m_QuadArray[1]=(CdPoint3D)lefttop; // 좌상 
		m_QuadArray[2]=(CdPoint3D)righttop;
		m_QuadArray[3]=(CdPoint3D)rightbottom;
	}
	else
	{
		leftbottom=m_QuadArray[0]; // 좌하 
		lefttop=m_QuadArray[1]; // 좌상 
		righttop=m_QuadArray[2];
		rightbottom=m_QuadArray[3];

	}
}

void CdQuad3D::MakeQuadricTriangle()
{
//	CenterPoint();

	m_QuadTriangles[0].Pt1 = (CdPoint3D)lefttop;
	m_QuadTriangles[0].Pt2 = (CdPoint3D)leftbottom; 
	m_QuadTriangles[0].Pt3 = (CdPoint3D)m_CenterPoint3D;
				
				//CREATE FACE 2
	m_QuadTriangles[1].Pt1 = (CdPoint3D)leftbottom;
	m_QuadTriangles[1].Pt2 = (CdPoint3D)rightbottom;
	m_QuadTriangles[1].Pt3 = (CdPoint3D)m_CenterPoint3D; 
				
				//CREATE FACE 3
	m_QuadTriangles[2].Pt1 = (CdPoint3D)rightbottom;
	m_QuadTriangles[2].Pt2 = (CdPoint3D)righttop; 
	m_QuadTriangles[2].Pt3 = (CdPoint3D)m_CenterPoint3D;

				//CREATE FACE 4
	m_QuadTriangles[3].Pt1 = (CdPoint3D)righttop; 
	m_QuadTriangles[3].Pt2 = (CdPoint3D)lefttop; 
	m_QuadTriangles[3].Pt3 = (CdPoint3D)m_CenterPoint3D; 
}

void CdQuad3D::OffsetQuad(double x,double y,double z)
{
	lefttop.x += x; 
	lefttop.y += y; 
	lefttop.z += z; 
	righttop.x += x; 
	righttop.y += y; 
	righttop.z += z; 
	rightbottom.x += x; 
	rightbottom.y += y; 
	rightbottom.z += z; 
	leftbottom.x += x; 
	leftbottom.y += y; 
	leftbottom.z += z; 
}
void CdQuad3D::OffsetQuad(DPOINT3D fPoint){
	lefttop.x += fPoint.x; 
	lefttop.y += fPoint.y; 
	lefttop.z += fPoint.z; 

	righttop.x += fPoint.x; 
	righttop.y += fPoint.y; 
	righttop.z += fPoint.z; 
	
	rightbottom.x += fPoint.x; 
	rightbottom.y += fPoint.y; 
	rightbottom.z += fPoint.z; 
	
	leftbottom.x += fPoint.x; 
	leftbottom.y += fPoint.y; 
	leftbottom.z += fPoint.z; 
}

CdPoint3D CdQuad3D::TopLeft()
{
	CdPoint3D fPt(lefttop.x,lefttop.y,lefttop.z);
	return fPt;
}
CdPoint3D CdQuad3D::TopRight()
{
	CdPoint3D fPt(righttop.x,righttop.y,righttop.z);
	return fPt;
}
CdPoint3D CdQuad3D::BottomRight()
{
	CdPoint3D fPt(rightbottom.x,rightbottom.y,rightbottom.z);
	return fPt;
}
CdPoint3D CdQuad3D::BottomLeft()
{
	CdPoint3D fPt(leftbottom.x,leftbottom.y,leftbottom.z);
	return fPt;
}

// 4각형의 중심점을 리턴한다.
CdPoint3D CdQuad3D::CenterPoint()
{
	
	// 사각형으로 부터 4개의 선분을 추출한다.
	/////////////////////////
	CdLine3D flnLeft(BottomLeft(),TopLeft());
	CdLine3D flnTop(TopLeft(),TopRight());
	CdLine3D flnRight(TopRight(),BottomRight());
	CdLine3D flnBottom(BottomRight(),BottomLeft());

	// 상하 및 좌우 2개의 대변의 중심점을 잇는 선분의 교점을 구한다.
	CdPoint3D fPt;
	GetIntersectPoint(flnLeft.CenterPoint(),
					flnRight.CenterPoint(),
					flnTop.CenterPoint(),
					flnBottom.CenterPoint(),fPt);

	double dTempHeight;
	CdQuad3D TempQuad;

	TempQuad.leftbottom=leftbottom;
	TempQuad.lefttop=lefttop;
	TempQuad.rightbottom=rightbottom;
	TempQuad.righttop=righttop;

	SetInterPolationMode(G_BILINEAR);
	m_CenterPoint3D=fPt;
	CalculateInterPolation(TempQuad,fPt,dTempHeight);
	m_CenterPoint3D.z = dTempHeight;

	return m_CenterPoint3D;	
}

// 4각형의 대각선의 교점을 리턴한다.
BOOL CdQuad3D::DiagonalPoint(DPOINT3D &fPt){
	return GetIntersectPoint(TopLeft(),BottomRight(),TopRight(),BottomLeft(),fPt);
}
// Determines whether CRect is empty.
// A rectangle is empty if the width and/or height are 0 or negative.
BOOL CdQuad3D::IsQuadEmpty(){
//	if(m_fHeight <=0. || m_fWidth <= 0.)
//		return TRUE;
	return FALSE;
}

// Nonzero if CRect’s top, left, bottom, and right values are all equal to 0;
// otherwise 0.
BOOL CdQuad3D::IsQuadNull(){
	if(	lefttop.x == 0.		&& lefttop.y == 0.		&&	lefttop.z == 0.	&&
		righttop.x == 0.	&& righttop.y == 0.		&&  righttop.z == 0. && 
		rightbottom.x == 0.	&& rightbottom.y == 0.	&&	rightbottom.z == 0.	&&
		leftbottom.x == 0.	&& leftbottom.y == 0.	&&	leftbottom.z == 0.)
		return TRUE;
	return FALSE;
}
BOOL CdQuad3D::PtInQuad(DPOINT3D fPt)
{
	// This will only handle convex quadrilaterals.
	double angle_12x = GetInteriorAngle( lefttop,righttop,fPt);
	double angle_123 = GetInteriorAngle( lefttop,righttop,rightbottom);
	if ( angle_12x > angle_123 )
		return FALSE;

	double angle_23x = GetInteriorAngle( righttop,rightbottom,fPt);
	double angle_234 = GetInteriorAngle( righttop,rightbottom,leftbottom);
	if ( angle_23x > angle_234 )
		return FALSE;

	double angle_34x = GetInteriorAngle( rightbottom,leftbottom,fPt);
	double angle_341 = GetInteriorAngle( rightbottom,leftbottom,lefttop);
	if ( angle_34x > angle_341 )
		return FALSE;

	double angle_41x = GetInteriorAngle(leftbottom,lefttop,fPt);
	double angle_412 = GetInteriorAngle(leftbottom,lefttop,righttop);
	if ( angle_41x > angle_412 )
		return FALSE;

	return TRUE;
}
void CdQuad3D::SetQuad(double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3,double x4,double y4,double z4)
{
	lefttop = CdPoint3D(x1,y1,z1);
	righttop = CdPoint3D(x2,y2,z2);
	rightbottom = CdPoint3D(x3,y3,z3);
	leftbottom = CdPoint3D(x4,y4,z4);
}
void CdQuad3D::SetQuadEmpty()
{
	lefttop = CdPoint3D(0.,0.,0.);
	righttop = CdPoint3D(0.,0.,0.);
	rightbottom = CdPoint3D(0.,0.,0.);
	leftbottom = CdPoint3D(0.,0.,0.);
}
// Copies the lpSrcfQuad quadrilateral into CdQuad
void CdQuad3D::CopyQuad(LPCDQUAD3D lpSrcfQuad)
{
	*(DQUAD3D*)this = *lpSrcfQuad;
}
// Nonzero if the two quadrilateralS have the same top, left, bottom, and right values;
// otherwise 0.
BOOL CdQuad3D::EqualQuad(LPCDQUAD3D lpfQuad)
{
	if((CdPoint3D)lefttop == lpfQuad->lefttop && (CdPoint3D)lpfQuad->righttop == righttop &&
		(CdPoint3D)lpfQuad->rightbottom == rightbottom && (CdPoint3D)lpfQuad->leftbottom == leftbottom)
		return TRUE;
	return FALSE;
}

void GInterPolation::SetInterPolationMode(int mode)
{
	
	m_nInterPolationMode = mode;
	m_bCaculated=FALSE;

}
BOOL GInterPolation::CalculateInterPolation(CdPoint3D LeftBottom,CdPoint3D LeftTop,CdPoint3D RightTop,CdPoint3D RightBottom,CdPoint3D fpt,double& dResult)
{
	BOOL Ret = CalculateInterPolation(CdQuad3D(LeftTop,RightTop,RightBottom,LeftBottom),fpt,dResult);
	return Ret;
}

BOOL GInterPolation::GetBilinearIntersectPoint(CdPoint3D &fpt1,CdPoint3D &fpt2,CdPoint3D &fpt3,CdPoint3D &fpt4)
{
	if(!m_bCaculated) return FALSE;

	fpt1 = m_fptBLP1;
	fpt2 = m_fptBLP2;
	fpt3 = m_fptBLP3;
	fpt4 = m_fptBLP4;
	m_bCaculated=FALSE;
	return TRUE;
}

BOOL GInterPolation::GetBilinearIntersectPoint3D(CdQuad3D Qaud,CdPoint3D fCurPos,double& ResultHeight,CdPoint3D &fpt1,CdPoint3D &fpt2,CdPoint3D &fpt3,CdPoint3D &fpt4)
{	
	CdPoint3D Intersect_fpt_Left;
	CdPoint3D Intersect_fpt_Right;
	CdPoint3D Intersect_fpt_Top;
	CdPoint3D Intersect_fpt_Bottom;
	CdPoint3D CurrentPostion = fCurPos;
	double dHeightValue;

	CalculateInterPolation(Qaud,fCurPos,dHeightValue); // Interpolation에서 상속받은 함수.. Bilinear 보간함수. 
	ResultHeight=dHeightValue;
	GetBilinearIntersectPoint(Intersect_fpt_Bottom,Intersect_fpt_Top,Intersect_fpt_Left,Intersect_fpt_Right);
		
	CalculateInterPolation(Qaud,Intersect_fpt_Bottom,dHeightValue); // Interpolation에서 상속받은 함수.. Bilinear 보간함수. 
	Intersect_fpt_Bottom.z=dHeightValue;
	CalculateInterPolation(Qaud,Intersect_fpt_Top,dHeightValue); // Interpolation에서 상속받은 함수.. Bilinear 보간함수. 
	Intersect_fpt_Top.z=dHeightValue;
	CalculateInterPolation(Qaud,Intersect_fpt_Left,dHeightValue); // Interpolation에서 상속받은 함수.. Bilinear 보간함수. 
	Intersect_fpt_Left.z=dHeightValue;
	CalculateInterPolation(Qaud,Intersect_fpt_Right,dHeightValue); // Interpolation에서 상속받은 함수.. Bilinear 보간함수. 
	Intersect_fpt_Right.z=dHeightValue;

	//Calculatedhk GetBilinear는 한쌍이다.
	fpt1 = Intersect_fpt_Bottom;
	fpt2 = Intersect_fpt_Top;
	fpt3 = Intersect_fpt_Left;
	fpt4 = Intersect_fpt_Right;

	return TRUE;
}



BOOL GInterPolation::CalculateInterPolation(CdQuad3D fQuad,CdPoint3D fpt,double& dResult)
{
	double fH1=0,fH2=0,fH0=0;
	double a1x,a2x,a1y,a2y,c1x,c2y,q1y;
	double b1x,b2x,b1y,b2y,d1x,d2y,q1x;
	double a,b,c,R1,R2;

	if(fQuad.IsQuadNull())
	{
		return FALSE;
	}

	switch(m_nInterPolationMode)
	{
		case G_BILINEAR:

		a1x = fQuad.leftbottom.x;
		b1x = fQuad.rightbottom.x-fQuad.leftbottom.x;
		a2x = fQuad.lefttop.x;
		b2x = fQuad.righttop.x-fQuad.lefttop.x;

		a1y = fQuad.leftbottom.y;
		b1y = fQuad.rightbottom.y-fQuad.leftbottom.y;

		a2y = fQuad.lefttop.y;
		b2y = fQuad.righttop.y-fQuad.lefttop.y;
		
						
		c1x = a2x-a1x;
		d1x = b2x-b1x;
							
		c2y = a2y-a1y;
		d2y = b2y-b1y;
							
		q1y = fpt.y-a1y;
		q1x = fpt.x-a1x;					

		a=b1x * d2y - b1y * d1x;
		b=q1y*d1x-b1y*c1x+b1x*c2y-q1x*d2y;
		c=q1y*c1x - q1x*c2y;
	
		if(a != 0.0 )
			R1 = (-b+sqrt(b*b - 4*a*c))/(2*a);
		else
			R1 = -c/b;
						
		a1x = fQuad.leftbottom.x;
		b1x = fQuad.lefttop.x-fQuad.leftbottom.x;
		a2x = fQuad.rightbottom.x;
		b2x = fQuad.righttop.x-fQuad.rightbottom.x;

		a1y = fQuad.leftbottom.y;
		b1y = fQuad.lefttop.y-fQuad.leftbottom.y;
		a2y = fQuad.rightbottom.y;
		b2y = fQuad.righttop.y-fQuad.rightbottom.y;						
									
		c1x = a2x - a1x;
		d1x = b2x-b1x;
								
		c2y = a2y-a1y;
		d2y = b2y-b1y;
		q1y = fpt.y-a1y;
		q1x = fpt.x-a1x;

		a=b1x * d2y - b1y * d1x;
		b=q1y*d1x-b1y*c1x+b1x*c2y-q1x*d2y;
		c=q1y*c1x - q1x*c2y;

		if(a != 0.0 )
			R2 = (-b-sqrt(b*b - 4*a*c))/(2*a);
		else
			R2 = -c/b;

		m_fptBLP1.x = fQuad.leftbottom.x+(fQuad.rightbottom.x-fQuad.leftbottom.x)*R1;
		m_fptBLP1.y = fQuad.leftbottom.y+(fQuad.rightbottom.y-fQuad.leftbottom.y)*R1;							

		m_fptBLP2.x = fQuad.lefttop.x+(fQuad.righttop.x-fQuad.lefttop.x)*R1;
		m_fptBLP2.y = fQuad.lefttop.y+(fQuad.righttop.y-fQuad.lefttop.y)*R1;
		
		m_fptBLP3.y = fQuad.leftbottom.y+(fQuad.lefttop.y-fQuad.leftbottom.y)*R2;
		m_fptBLP3.x = fQuad.leftbottom.x+(fQuad.lefttop.x-fQuad.leftbottom.x)*R2;
		
		m_fptBLP4.y = fQuad.rightbottom.y+(fQuad.righttop.y-fQuad.rightbottom.y)*R2;
		m_fptBLP4.x = fQuad.rightbottom.x+(fQuad.righttop.x-fQuad.rightbottom.x)*R2;

		fH1 = (fQuad.rightbottom.z-fQuad.leftbottom.z)*R1 +fQuad.leftbottom.z;
		fH2 = (fQuad.righttop.z-fQuad.lefttop.z)*R1 +fQuad.lefttop.z;
		dResult = (fH2-fH1)*(R2) +fH1;

	m_bCaculated=TRUE;

	return TRUE;
		break;
	}
	return TRUE;
}

GPickFunction::GPickFunction()
{
	m_bPickLimitMode=0;
	m_PickingData=FALSE;
	m_nPickNum=-1;
	m_nPickingMax=0;
	m_PickingDrag=FALSE;
	m_nPickQaudID=-1;
}



BOOL GPickFunction::GetNearestQuad3D(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos,CdQuad3D& GetQaud)
{
	int nQuadIndex =GetNearestQuadIndex(CurrQaud3DArray,fWorldPos,G_DONTCARE);
	if(nQuadIndex!=-1)
	{
		GetQaud= CurrQaud3DArray.GetAt(nQuadIndex);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


int GPickFunction::GetNearestQuadIndex(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos,int Flag)
{
	int nQuadArrSize=CurrQaud3DArray.GetSize();

	if(nQuadArrSize ==0)
	{
		return -1;
	}
	
	register int i;
	double dLen=0.0; // 거리 
	double fMin,fMax;
	int nQuadIndex=-1;
	fMin = fMax = 1000000000000.0;

	CdPoint3D   TempFpt;
	CdQuad3D TempQuad;
	
	for(i=0; i<nQuadArrSize; i++)
	{
		TempQuad=CurrQaud3DArray.GetAt(i);
		
		TempFpt=TempQuad.CenterPoint();

		dLen = GetDistance(fWorldPos,TempFpt);	
		
		if(dLen < fMin)
		{
				fMin = dLen;
				nQuadIndex = i;
		}	

	}
		
	if(fMin < fMax)
	{
		return nQuadIndex;
	}
	else
	{
		return -1;
	}

}

int GPickFunction::GetNearestFptIndexInQuad3D(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos)
{
	if(CurrQaud3DArray.GetSize()==0)
	{
		return -1;
	}

	int nQuadPickIndex = GetNearestQuadIndex(CurrQaud3DArray,fWorldPos,G_DONTCARE);

	if(nQuadPickIndex==-1)
	{
		return -1;
	}

	CdQuad3D TempQaud=CurrQaud3DArray.GetAt(nQuadPickIndex);

	if(TempQaud.IsQuadNull()==TRUE)
	{
		return -1;
	}

	TempQaud.MakeQuadricArray(TRUE);

	int nPtIndex=GetNearestPtIndex(&TempQaud.m_QuadArray[0],4,fWorldPos);

	return nPtIndex;
}


BOOL GPickFunction::GetNearestFptInQuad3D(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos,CdPoint3D& ResultFpt)
{
	int nQuadPickIndex = GetNearestQuadIndex(CurrQaud3DArray,fWorldPos,G_DONTCARE);

	if(nQuadPickIndex==-1)
	{
		return FALSE;
	}

	CdQuad3D TempQaud=CurrQaud3DArray.GetAt(nQuadPickIndex);
	
	if(TempQaud.IsQuadNull()==TRUE)
	{
		return FALSE;
	}

	TempQaud.MakeQuadricArray(TRUE);

	int nPtIndex=GetNearestPtIndex(TempQaud.m_QuadArray,4,fWorldPos);

	if(nPtIndex==-1)
	{
		return FALSE;
	}
	else
	{
		ResultFpt = TempQaud.m_QuadArray[nPtIndex];
		return TRUE;
	}
}

int GPickFunction::GetNearestPtIndex(CdPoint3D* CurrfptArray,int PtNum,CdPoint3D fWorldPos)
{
	register int i=0;

	double dLen=0.0; // 거리 
	double fMin,fMax;
	int nCenterIndex=-1;
	fMin = fMax = 100.0;
	

		if(CurrfptArray==NULL)
		{
			return -1;
		}
		
		for(i=0; i<PtNum; i++)
		{
			dLen = GetDistance(fWorldPos,CurrfptArray[i]);	

			if(dLen < fMin)
			{
				fMin = dLen;
				nCenterIndex = i;
			}
		}

	if(fMin < fMax)
	{
		return nCenterIndex;
	}
	else
	{
		return -1;
	}
}


int GPickFunction::GetNearestPointIndexArr(CArfPt3D* Arr,CdPoint3D fpt)
{

	CdPoint3D fpt1;
	int index =-1;
	double fLen;
	double fMin,fMax;
	
	if(Arr==NULL)
		return -1;

	fMin = fMax = 1000000000000.0;

	int n;
	int nNumOfPoint = Arr->GetSize();

	for(n = 0; n < nNumOfPoint; n++)
	{
		fpt1 = Arr->GetAt(n);

		fLen =  GetDistance(fpt,fpt1);	
		if(fLen < fMin)
		{
			fMin = fLen;
			index = n;
		}
	}

	if(fMin < fMax)
		return index;
	else
		return -1;

}




void GPickFunction::EnablePickPtArray(CArfPt3D* CArrPt3d,int PtNum)
{
	m_bPickCarFptMode=TRUE;
	m_bPickArrayMode=TRUE;

	m_nPickNum=-1;
	m_PickArr3D = CArrPt3d;
	m_nPickingMax=PtNum;

}

void GPickFunction:: EnablePickPtArray(CdPoint3D *cfPoints,int nCnt)
{
	m_bPickArrayMode=TRUE;
	m_bPickCfPoint3DarrayMode=TRUE;
	m_nPickNum=-1;
	m_PickingData =cfPoints;
	m_nPickingMax=nCnt;
}

void GPickFunction:: EnablePickQuad3D(CArfQuad3D* CurrQaud3DArray)
{

	if(CurrQaud3DArray->GetSize()==0)
	{
		m_bPickQuadMode=FALSE;
		return;
	}

	m_bPickQuadMode=TRUE;

	m_nPickNum=-1;

	m_PickingData_Qaud = CurrQaud3DArray;
	m_nPickingMax=m_PickingData_Qaud->GetSize();

	//	GLRenderScene();
}



int GPickFunction::GetPickedArrIndex(int PickMode)
{
	if(PickMode==G_PICK_CFPOINT3D)
		return m_nPickNum;
	else
		return m_nPickQaudID;

}



void GPickFunction::DisablePickQuad3D()
{
	m_bPickQuadMode=FALSE;
}

void GPickFunction::DisablePickPtArray()
{
	m_bPickArrayMode=FALSE;
}

void GPickFunction::EnableVertexModify()
{
	m_bVertexMod=TRUE;
}

void GPickFunction::DisableVertexModify()
{
	m_bVertexMod=FALSE;
}	


void GPickFunction::EnablePickRange(CdPoint3D fpfMinimum,CdPoint3D fptMaximum)
{
	m_bPickLimitMode=TRUE;
	m_dPickRangeMinimum = fpfMinimum;
	m_dPickRangeMaximum = fptMaximum;
}

void GPickFunction::DisablePickRange()
{
	m_bPickLimitMode=FALSE;
}

BOOL GPickFunction::isPickRangeLimit()
{
	if(m_bPickLimitMode==TRUE)
		return m_bPickInRegion;
	else
		return FALSE;
}

BOOL GPickFunction::isDraging()
{
	return m_PickingDrag;
}

void GPickFunction::UpdateMousePostion(UINT nActCode,CdPoint3D fptMousePos)
{
	if(nActCode==WM_MOUSEMOVE)
	{	
		BOOL Ret=TRUE;

		if(m_bPickLimitMode==TRUE && isDraging()==FALSE && m_bVertexMod==FALSE)
		{
			if(fptMousePos.x >= m_dPickRangeMinimum.x && fptMousePos.x < m_dPickRangeMaximum.x)
			{
				if(fptMousePos.y >= m_dPickRangeMinimum.y && fptMousePos.y <= m_dPickRangeMaximum.y)
					Ret=TRUE;
				else
					Ret=FALSE;
			}
			else
				Ret=FALSE;
		}
		else
		{
			Ret=TRUE;
		}

		m_bPickInRegion=Ret;

		if(m_nPickingMax && !m_PickingDrag && m_bPickArrayMode==TRUE && Ret==TRUE)
		{
			if(m_bPickCfPoint3DarrayMode==TRUE)
			{

				m_nPickNum = GetNearestPtIndex(m_PickingData,m_nPickingMax,fptMousePos);
				if(m_nPickNum!=-1)
				{
					m_PickedPoint = m_PickingData[m_nPickNum];
				}

			}

			if(m_bPickCarFptMode==TRUE)
			{
				m_nPickNum= GetNearestPointIndexArr(m_PickArr3D,fptMousePos);

				if(m_nPickNum!=-1)
				{
					m_PickedPoint = m_PickArr3D->GetAt(m_nPickNum);
				}
			}

		}
		else if(m_nPickingMax && m_PickingDrag && m_nPickNum!=-1 && m_bPickArrayMode==TRUE&& m_bVertexMod==TRUE)
		{
			/* 실제로 데이터 변경하는 부분 */

			if(m_bPickCarFptMode==TRUE)
			{
				if(m_nPickNum!=-1)
				{
					m_PickedPoint.x=fptMousePos.x;
					m_PickedPoint.y=fptMousePos.y;
					m_PickArr3D->SetAt(m_nPickNum,m_PickedPoint);

				}
			}
			else
			{
				m_VetedModCriticalSection.Lock();
				m_PickingData[m_nPickNum].x=fptMousePos.x;
				m_PickingData[m_nPickNum].y=fptMousePos.y;
				m_VetedModCriticalSection.Unlock();
			}
		}

		//GetNearestFptIndexInQuad3D
		if(m_nPickingMax && !m_PickingDrag && m_bPickQuadMode==TRUE && Ret==TRUE)
		{
			m_nPickQaudID = GetNearestQuadIndex(*m_PickingData_Qaud,fptMousePos,G_DONTCARE);
			GetNearestFptInQuad3D(*m_PickingData_Qaud,fptMousePos,m_PickedPoint);
		}
	}
	else if(nActCode==WM_LBUTTONDOWN)
	{
		if(m_nPickingMax && !m_PickingDrag)
		{
			m_PickingDrag=TRUE;
		}
	}
	else if(nActCode==WM_LBUTTONUP)
	{
		if(m_nPickingMax)
		{
			m_PickingDrag=FALSE;
		}
	}
}

BOOL GPickFunction::GetPickedQAUD3D(CdQuad3D& Result)
{
	if(m_nPickQaudID!=-1 && m_bPickQuadMode==TRUE  && m_bPickArrayMode==TRUE)
	{				
		if(m_PickingData_Qaud==NULL || m_nPickQaudID > m_PickingData_Qaud->GetSize())
		{		
			return FALSE;
		}

		m_PickedQuad = m_PickingData_Qaud->GetAt(m_nPickQaudID);
		Result = m_PickedQuad;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL GPickFunction::GetPickedCfPoint3D(CdPoint3D& Result)
{
	if(m_bPickArrayMode==TRUE || m_bPickQuadMode==TRUE && m_bPickArrayMode==TRUE)
	{

		if(m_nPickNum!=-1 || m_nPickQaudID!=-1)
		{
			Result = m_PickedPoint;
			return TRUE;
		}
		else
		{
			return FALSE;
		}

	}
	else
	{
		return FALSE;
	}
}

CString DtoA(double fTmp)
{
	CString str;
	str.Format(_T("%3.2f"),fTmp);
	return str;
} 

CString DtoA(TCHAR* szFormat, double fTmp)
{
	CString str;
	str.Format(szFormat,fTmp);
	return str;
} 

CString DtoA(TCHAR* szFormat, int nTmp)
{
	CString str;
	str.Format(szFormat,nTmp);
	return str;
} 

CString DtoA(int nTmp)
{
	CString str;
	str.Format(_T("%02d"),nTmp);
	return str;
}

CString DtoA(UINT nTmp)
{
	CString str;
	str.Format(_T("%02d"),nTmp);
	return str;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
double mm2um(double fmm)
{
	return fmm*1000.0;
}
double um2mm(double fum)
{
	return fum/1000.0;
}

int Round(float fValue)
{
	if ((fValue < 0))
		return static_cast<int>(fValue - 0.5);

	return static_cast<int>(fValue + 0.5);
}

int Round(double dValue)
{
	if ((dValue < 0)) 
		return static_cast<int>(dValue - 0.5);
	
	return static_cast<int>(dValue + 0.5);
}

float ConvertInchToMetric(float fValue)
{
	return fValue * 25.4;
}
float ConvertMetricToInch(float fValue)
{
	return fValue / 25.4;
}
double ConvertInchToMetric(double fValue)
{
	return fValue * 25.4;
}
double ConvertMetricToInch(double fValue)
{
	return fValue / 25.4;
}
DPOINT ConvertPointInchToMetric(DPOINT &fpt)
{
	DPOINT fPoint;
	fPoint.x = fpt.x * 25.4;
	fPoint.y = fpt.y * 25.4;
	return fPoint;
}
DPOINT ConvertPointMetricToInch(DPOINT &fpt)
{
	DPOINT fPoint;
	fPoint.x = fpt.x / 25.4;
	fPoint.y = fpt.y / 25.4;
	return fPoint;
}
DRECT ConvertExtentInchToMetric(DRECT &fExtent)
{
	DRECT fRECT;
	fRECT.left = fExtent.left * 25.4;
	fRECT.bottom = fExtent.bottom * 25.4;
	fRECT.right = fExtent.right * 25.4;
	fRECT.top = fExtent.top * 25.4;
	return fRECT;
}
DRECT ConvertExtentMetricToInch(DRECT &fExtent)
{
	DRECT fRECT;
	fRECT.left = fExtent.left / 25.4;
	fRECT.bottom = fExtent.bottom / 25.4;
	fRECT.right = fExtent.right / 25.4;
	fRECT.top = fExtent.top / 25.4;
	return fRECT;
}
double GetDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((double)x2 - (double)x1, 2) + pow((double)y2 - (double)y1, 2));
}
double GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
double GetDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
double GetDistance(CPoint FirstPoint, CPoint SecondPoint)
{
	return sqrt(pow((double)SecondPoint.x - (double)FirstPoint.x, 2) + pow((double)SecondPoint.y - (double)FirstPoint.y, 2));
}
double GetDistance(DPOINT FirstPoint,DPOINT SecondPoint)
{
	return sqrt(pow(SecondPoint.x-FirstPoint.x,2)+pow(SecondPoint.y-FirstPoint.y,2));
}
double GetDistance(CdPoint3D FirstPoint,CdPoint3D SecondPoint)
{
	return sqrt(pow(SecondPoint.x-FirstPoint.x,2)+pow(SecondPoint.y-FirstPoint.y,2));
}
double GetDistance(CdPoint FirstPoint,CdPoint SecondPoint)
{
	return sqrt(pow(SecondPoint.x-FirstPoint.x,2)+pow(SecondPoint.y-FirstPoint.y,2));
}
double GetDistancePointToLine(CdPoint fpt1, CdPoint fpt2, double x, double y)
{
	double fDistance;

	if ((fpt1.x - fpt2.x) == 0 && (fpt1.y - fpt2.y) == 0)
	{
		if (fpt1.x == x && fpt1.y == y)
			fDistance = 0;
		else
			fDistance = sqrt(pow(fpt1.x - x, 2) + pow(fpt1.y - y, 2));
	}
	else if (fpt1.x - fpt2.x == 0)
	{
		fDistance = fabs(fpt1.x - x);
	}
	else if (fpt1.y - fpt2.y == 0)
	{
		fDistance = fabs(fpt1.y - y);
	}
	else
	{
		double fGradient = (fpt1.y - fpt2.y) / (fpt1.x - fpt2.x);
		double fConstant = fpt1.y - fGradient*fpt1.x;
		fDistance = fabs(-fGradient*x + y - fConstant) / sqrt(fGradient*fGradient + 1.0);
	}

	return fDistance;
}
double GetDistancePointToLine(DPOINT fpt1, DPOINT fpt2, double x, double y)
{
	double fDistance;

	if (fabs(fpt1.x - fpt2.x) < 0.00000001 && fabs(fpt1.y - fpt2.y) < 0.00000001)
	{
		if (fabs(fpt1.x - x) < 0.00000001 && fabs(fpt1.y - y) < 0.00000001)
			fDistance = 0.0;
		else
			fDistance = sqrt(pow(fpt1.x - x, 2) + pow(fpt1.y - y, 2));
	}
	else if (fabs(fpt1.x - fpt2.x) < 0.00000001)
	{
		fDistance = fabs(fpt1.x - x);
	}
	else if (fabs(fpt1.y - fpt2.y) < 0.00000001)
	{
		fDistance = fabs(fpt1.y - y);
	}
	else
	{
		double fGradient = (fpt1.y - fpt2.y) / (fpt1.x - fpt2.x);
		double fConstant = fpt1.y - fGradient*fpt1.x;
		fDistance = fabs(-fGradient*x + y - fConstant) / sqrt(fGradient*fGradient + 1.0);
	}

	return fDistance;
}
double GetDistancePointToLine(CPoint fpt1, CPoint fpt2, int x, int y)	// 임의의 Point에서 두점에 의한 Line과의 최소거리 
{
	double fDistance;

	if (abs(fpt1.x - fpt2.x) < 0 && abs(fpt1.y - fpt2.y) < 0)
	{
		if (abs(fpt1.x - x) < 0 && abs(fpt1.y - y) < 0)
			fDistance = 0.0;
		else
			fDistance = sqrt(pow((double)(fpt1.x - x), 2) + pow((double)(fpt1.y - y), 2));
	}
	else if (abs(fpt1.x - fpt2.x) < 0)
	{
		fDistance = abs(fpt1.x - x);
	}
	else if (abs(fpt1.y - fpt2.y) < 0)
	{
		fDistance = abs(fpt1.y - y);
	}
	else
	{
		double fGradient = (double)(fpt1.y - fpt2.y) / (double)(fpt1.x - fpt2.x);
		double fConstant = (double)(fpt1.y - fGradient*fpt1.x);
		fDistance = fabs(-fGradient*x + y - fConstant) / sqrt(fGradient*fGradient + 1.0);
	}

	return fDistance;
}
void GetOrthogonalPointOfLineAndPoint(DPOINT start, DPOINT end, double x, double y, DPOINT &fpt)
{
	if ((start.x - end.x) == 0 && (start.y - end.y) == 0)
	{
		fpt = start;
	}
	else if (start.x - end.x == 0)
	{
		fpt.x = start.x;
		fpt.y = y;
	}
	else if (start.y - end.y == 0)
	{
		fpt.x = x;
		fpt.y = start.y;
	}
	else
	{
		double fGradient1 = (start.y - end.y) / (start.x - end.x);
		double fConstant1 = start.y - fGradient1*start.x;
		double fGradient2 = -1 / fGradient1;
		double fConstant2 = y - fGradient2 * x;

		fpt.x = (fConstant2 - fConstant1) / (fGradient1 - fGradient2);
		fpt.y = fGradient1 * fpt.x + fConstant1;
	}
}
double D2R(double fDeg)
{
	double fVal = fDeg* DEG2RAD ;
	return fVal;
}

double R2D(double fRadian)
{
	double fVal = fRadian*RAD2DEG;
	return fVal;
}

void swap(double& p1,double& p2){
	double temp = p1;
	p1 = p2;
	p2 = temp;
}

void TranslatePoint(DPOINT &p, double dX, double dY)
{
	p.x += dX;
	p.y += dY;
}

void TranslateRect(DRECT &R, double dX, double dY)
{
	R.left += dX;
	R.bottom += dY;
	R.right += dX;
	R.top += dY;
}

void GetRotateParameter(double dAng, double *dCosineVal, double *dSineVal)
{
	int nAng = fmod(dAng+360.0,360.0); // normalize angle
    switch (nAng) // 'CCW
	{
	case 0:
        *dCosineVal = 1.0;
        *dSineVal = 0.0;
		break;
    case 90:
		*dCosineVal = 0.0;
        *dSineVal = 1.0;
		break;
    case 180:
        *dCosineVal = -1.0;
        *dSineVal = 0.0;
		break;
    case 270:
        *dCosineVal = 0.0;
        *dSineVal = -1.0;
		break;
	default:
        *dCosineVal = cos(dAng * DEG2RAD);
        *dSineVal = sin(dAng * DEG2RAD);
		break;
    }
}

void RotatePoint(DPOINT &fptRef,DPOINT &fptCenter,double fRotAngle)
{
	if(fRotAngle == 0.0)
		return;

	DPOINT fpt;		

	double cV, sV;
	switch((int)fRotAngle)
	{
	case 90:
	case -270:
		fpt.x = -fptRef.y + fptCenter.y + fptCenter.x;
		fpt.y = fptRef.x  - fptCenter.x + fptCenter.y;
		break;
	case 180:
	case -180:
		fpt.x = -fptRef.x + fptCenter.x + fptCenter.x;
		fpt.y = -fptRef.y + fptCenter.y + fptCenter.y;
		break;
	case 270:
	case -90:
		fpt.x = fptRef.y - fptCenter.y + fptCenter.x;
		fpt.y = -fptRef.x + fptCenter.x + fptCenter.y;
		break;
	default:
		cV = cos(fRotAngle * DEG2RAD);
		sV = sin(fRotAngle * DEG2RAD);
		fpt.x = ((fptRef.x - fptCenter.x) * cV) - ((fptRef.y - fptCenter.y) * sV) + fptCenter.x;
		fpt.y = ((fptRef.x - fptCenter.x) * sV) + ((fptRef.y - fptCenter.y) * cV) + fptCenter.y;
		break;
	}
	fptRef= fpt;
}

void RotateRect(DRECT &fRect, DPOINT &fCenter, double fAng)
{
    double X1, Y1, X2, Y2;
	DRECT rRect;
	double cV, sV;

	switch((int)fAng)
	{
	case 0:
		break;
	case 90:
	case -270:
		X1 = -fRect.bottom + fCenter.y + fCenter.x;
		Y1 = fRect.left - fCenter.x + fCenter.y;
		X2 = -fRect.top + fCenter.y + fCenter.x;
		Y2 = fRect.right - fCenter.x + fCenter.y;
   
		if (X1 < X2)
		{
			fRect.left = X1;
			fRect.right = X2;
		}
		else
		{
			fRect.left = X2;
			fRect.right = X1;
		}
    
		if (Y1 < Y2)
		{
			fRect.bottom = Y1;
			fRect.top = Y2;
		}
		else
		{
			fRect.bottom = Y2;
			fRect.top = Y1;
		}
		break;
	case 180:
	case -180:
		X1 = -fRect.left + fCenter.x + fCenter.x;
		Y1 = -fRect.bottom + fCenter.y + fCenter.y;
		X2 = -fRect.right + fCenter.x + fCenter.x;
		Y2 = -fRect.top + fCenter.y + fCenter.y;
    
		if (X1 < X2)
		{
			fRect.left = X1;
			fRect.right = X2;
		}
		else
		{
			fRect.left = X2;
			fRect.right = X1;
		}
    
		if (Y1 < Y2)
		{
			fRect.bottom = Y1;
			fRect.top = Y2;
		}
		else
		{
			fRect.bottom = Y2;
			fRect.top = Y1;
		}

		break;
	case 270:
	case -90:
		X1 = ((fRect.bottom - fCenter.y)) + fCenter.x;
		Y1 = -((fRect.left - fCenter.x)) + fCenter.y;
		X2 = ((fRect.top - fCenter.y)) + fCenter.x;
		Y2 = -((fRect.right - fCenter.x)) + fCenter.y;
    
		if (X1 < X2)
		{
			fRect.left = X1;
			fRect.right = X2;
		}
		else
		{
			fRect.left = X2;
			fRect.right = X1;
		}
    
		if (Y1 < Y2)
		{
			fRect.bottom = Y1;
			fRect.top = Y2;
		}
		else
		{
			fRect.bottom = Y2;
			fRect.top = Y1;
		}

		break;
	default:
		cV = cos(fAng * DEG2RAD);
		sV = sin(fAng * DEG2RAD);

		// rotate left-bottom and right top point
		X1 = ((fRect.left - fCenter.x) * cV) - ((fRect.bottom - fCenter.y) * sV) + fCenter.x;
		Y1 = ((fRect.left - fCenter.x) * sV) + ((fRect.bottom - fCenter.y) * cV) + fCenter.y;
		X2 = ((fRect.right - fCenter.x) * cV) - ((fRect.top - fCenter.y) * sV) + fCenter.x;
		Y2 = ((fRect.right - fCenter.x) * sV) + ((fRect.top - fCenter.y) * cV) + fCenter.y;

		if (X1 < X2)
		{
			rRect.left = X1;
			rRect.right = X2;
		}
		else
		{
			rRect.left = X2;
			rRect.right = X1;
		}
    
		if (Y1 < Y2)
		{
			rRect.bottom = Y1;
			rRect.top = Y2;
		}
		else
		{
			rRect.bottom = Y2;
			rRect.top = Y1;
		}
		// rotate left-top and right bottom point
		X1 = ((fRect.left - fCenter.x) * cV) - ((fRect.top - fCenter.y) * sV) + fCenter.x;
		Y1 = ((fRect.left - fCenter.x) * sV) + ((fRect.top - fCenter.y) * cV) + fCenter.y;
		X2 = ((fRect.right - fCenter.x) * cV) - ((fRect.bottom - fCenter.y) * sV) + fCenter.x;
		Y2 = ((fRect.right - fCenter.x) * sV) + ((fRect.bottom - fCenter.y) * cV) + fCenter.y;

		if (X1 < X2)
		{
			fRect.left = X1;
			fRect.right = X2;
		}
		else
		{
			fRect.left = X2;
			fRect.right = X1;
		}
    
		if (Y1 < Y2)
		{
			fRect.bottom = Y1;
			fRect.top = Y2;
		}
		else
		{
			fRect.bottom = Y2;
			fRect.top = Y1;
		}

		if(fRect.left > rRect.left)	fRect.left = rRect.left; 
		if(fRect.bottom > rRect.bottom)	fRect.bottom = rRect.bottom;   
		if(fRect.right < rRect.right)	fRect.right = rRect.right;   
		if(fRect.top < rRect.top)	fRect.top = rRect.top;
	}
}


BOOL GetScaleRect(DRECT *rect, double fScaleX, double fScaleY)
{
	rect->left *= fScaleX;
	rect->bottom *= fScaleY;
	rect->right *= fScaleX;
	rect->top *= fScaleY;

	return FALSE;
}

void MirrorVerticalRect(DRECT &fRect, double vAxis) 
{
    DRECT rRect;

	rRect = fRect;
    rRect.left = -(fRect.right - vAxis) + vAxis;
    rRect.right = -(fRect.left - vAxis) + vAxis;

	fRect = rRect;
}

void MirrorHorizontalRect(DRECT &fRect, double hAxis)
{
    DRECT rRect;

	rRect = fRect;
    rRect.bottom = -(fRect.top - hAxis) + hAxis;
    rRect.top = -(fRect.bottom - hAxis) + hAxis;
	fRect = rRect;
}

void MirrorHorizontalPoint(DPOINT &p, double hAxis)
{
	DPOINT r;

    r.x = p.x;
    if (hAxis < p.y) 
		r.y = hAxis - fabs(p.y - hAxis); 
	else 
		r.y = hAxis + fabs(p.y - hAxis);
	p = r;
}

void MirrorVerticalPoint(DPOINT &p, double vAxis)
{
	DPOINT r;
    if (vAxis < p.x)
		r.x = vAxis - fabs(p.x - vAxis); 
	else 
		r.x = vAxis + fabs(p.x - vAxis);
    r.y = p.y;

	p = r;
}

void AdjustExtentByPoint(DRECT &Extent, const DPOINT &pt)
{
	if (pt.x < Extent.left)
		Extent.left = pt.x;
	if (pt.y < Extent.bottom)
		Extent.bottom = pt.y;
	if (pt.x > Extent.right)
		Extent.right = pt.x;
	if (pt.y > Extent.top)
		Extent.top = pt.y;
}

void AdjustExtentByRect(DRECT &Extent, const DRECT &rect)
{
	if(Extent.left > rect.left)
		Extent.left = rect.left;
	if(Extent.right < rect.right)
		Extent.right = rect.right;
	if(Extent.bottom > rect.bottom)
		Extent.bottom = rect.bottom;
	if(Extent.top < rect.top)
		Extent.top = rect.top;
}

DRECT GetMaxExtentByRect(const DRECT &rect1, const DRECT &rect2, double dX, double dY)
{
	DRECT fExtent;
	if (rect1.left < rect2.left)
		fExtent.left = rect1.left - dX;
	else
		fExtent.left = rect2.left - dX;

	if (rect1.bottom < rect2.bottom)
		fExtent.bottom = rect1.bottom - dY;
	else
		fExtent.bottom = rect2.bottom - dY;

	if (rect1.right > rect2.right)
		fExtent.right = rect1.right + dX;
	else
		fExtent.right = rect2.right + dX;

	if (rect1.top > rect2.top)
		fExtent.top = rect1.top + dY;
	else
		fExtent.top = rect2.top + dY;

	return fExtent;
}

//// 20190721 Add
void SortInteger(vector <int> &vecInteger, BOOL bDecending)
{
	if (!bDecending)
		std::sort(vecInteger.begin(), vecInteger.end());
	else
		std::sort(vecInteger.begin(), vecInteger.end(), IntegerDecendingSortfunction);
}
BOOL IntegerDecendingSortfunction(int &a, int &b)
{
	if (a > b)
		return TRUE;

	return FALSE;
}
void SortFloat(vector <float> &vecFloat, BOOL bDecending)
{
	if (!bDecending)
		std::sort(vecFloat.begin(), vecFloat.end());
	else
		std::sort(vecFloat.begin(), vecFloat.end(), FloatDecendingSortfunction);
}
BOOL FloatDecendingSortfunction(float &a, float &b)
{
	if (a > b)
		return TRUE;

	return FALSE;
}
void SortDouble(vector <double> &vecDouble, BOOL bDecending)
{
	if (!bDecending)
		std::sort(vecDouble.begin(), vecDouble.end());
	else
		std::sort(vecDouble.begin(), vecDouble.end(), DoubleDecendingSortfunction);
}
BOOL DoubleDecendingSortfunction(double &a, double &b)
{
	if (a > b)
		return TRUE;

	return FALSE;
}

void SortPoint(int nSortType, vector <DPOINT> &vecPointList, double dGap)
{
	int j, k, nOrder, nNumOfPoint;
	double dComp;

	nNumOfPoint = (int)vecPointList.size();

	if (nNumOfPoint < 2)
		return;

	j = 0;
	nOrder = 0;
	switch (nSortType)
	{
	case 0:
	case 2:
	case 4:
	case 6:
		std::sort(vecPointList.begin(), vecPointList.end(), PointDecendingSortfunctionY);
		dComp = vecPointList.at(0).y;
		for (k = 0; k < nNumOfPoint; k++)
		{
			if (fabs(dComp - vecPointList.at(k).y) > dGap)
			{
				switch (nSortType)
				{
				case 0:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionX);
					break;
				case 2:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 4:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionX);
					break;
				case 6:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}
				j = k;
				dComp = vecPointList.at(k).y;
			}
			else if (k == nNumOfPoint - 1)
			{
				switch (nSortType)
				{
				case 0:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionX);
					break;
				case 2:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 4:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionX);
					break;
				case 6:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		std::sort(vecPointList.begin(), vecPointList.end(), PointAscendingSortfunctionX);
		dComp = vecPointList.at(0).x;
		for (k = 0; k < nNumOfPoint; k++)
		{
			if (fabs(dComp - vecPointList.at(k).x) > dGap)
			{
				switch (nSortType)
				{
				case 1:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionY);
					break;
				case 3:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 5:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionY);
					break;
				case 7:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}

				j = k;
				dComp = vecPointList.at(k).x;
			}
			else if (k == nNumOfPoint - 1)
			{
				switch (nSortType)
				{
				case 1:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionY);
					break;
				case 3:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 5:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionY);
					break;
				case 7:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	case 10:
	case 12:
	case 14:
	case 16:
		std::sort(vecPointList.begin(), vecPointList.end(), PointAscendingSortfunctionY);
		dComp = vecPointList.at(0).y;
		for (k = 0; k < nNumOfPoint; k++)
		{
			if (fabs(dComp - vecPointList.at(k).y) > dGap)
			{
				switch (nSortType)
				{
				case 10:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionX);
					break;
				case 12:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 14:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionX);
					break;
				case 16:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}

				j = k;
				dComp = vecPointList.at(k).y;
			}
			else if (k == nNumOfPoint - 1)
			{
				switch (nSortType)
				{
				case 10:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionX);
					break;
				case 12:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 14:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionX);
					break;
				case 16:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	case 11:
	case 13:
	case 15:
	case 17:
		std::sort(vecPointList.begin(), vecPointList.end(), PointDecendingSortfunctionX);
		dComp = vecPointList.at(0).x;
		for (k = 0; k < nNumOfPoint; k++)
		{
			if (fabs(dComp - vecPointList.at(k).x) > dGap)
			{
				switch (nSortType)
				{
				case 11:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionY);
					break;
				case 13:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 15:
					std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionY);
					break;
				case 17:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.begin() + k, PointDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}

				j = k;
				dComp = vecPointList.at(k).x;
			}
			else if (k == nNumOfPoint - 1)
			{
				switch (nSortType)
				{
				case 11:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionY);
					break;
				case 13:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 15:
					std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionY);
					break;
				case 17:
					if (nOrder == 0)
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecPointList.begin() + j, vecPointList.end(), PointDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	}
}
void PointDecendingSortX(vector <DPOINT> &vecPointList, int nStart, int nEnd)
{
	int nNumOfPoint = (int)vecPointList.size();
	if (nNumOfPoint < 1 || nEnd == nStart)
		return;

	if (nNumOfPoint > nStart)
	{
		if (nNumOfPoint > nEnd && nEnd > nStart)
			std::sort(vecPointList.begin() + nStart, vecPointList.begin() + nEnd, PointDecendingSortfunctionX);
		else
			std::sort(vecPointList.begin() + nStart, vecPointList.end(), PointDecendingSortfunctionX);
	}
}
void PointDecendingSortY(vector <DPOINT> &vecPointList, int nStart, int nEnd)
{
	int nNumOfPoint = (int)vecPointList.size();
	if (nNumOfPoint < 1 || nEnd == nStart)
		return;

	if (nNumOfPoint > nStart)
	{
		if(nNumOfPoint > nEnd && nEnd > nStart)
			std::sort(vecPointList.begin() + nStart, vecPointList.begin() + nEnd, PointDecendingSortfunctionY);
		else
			std::sort(vecPointList.begin() + nStart, vecPointList.end(), PointDecendingSortfunctionY);
	}
}
void PointAscendingSortX(vector <DPOINT> &vecPointList, int nStart, int nEnd)
{
	int nNumOfPoint = (int)vecPointList.size();
	if (nNumOfPoint < 1 || nEnd == nStart)
		return;

	if (nNumOfPoint > nStart)
	{
		if (nNumOfPoint > nEnd && nEnd > nStart)
			std::sort(vecPointList.begin() + nStart, vecPointList.begin() + nEnd, PointAscendingSortfunctionX);
		else
			std::sort(vecPointList.begin() + nStart, vecPointList.end(), PointAscendingSortfunctionX);
	}
}
void PointAscendingSortY(vector <DPOINT> &vecPointList, int nStart, int nEnd)
{
	int nNumOfPoint = (int)vecPointList.size();
	if (nNumOfPoint < 1 || nEnd == nStart)
		return;

	if (nNumOfPoint > nStart)
	{
		if (nNumOfPoint > nEnd && nEnd > nStart)
			std::sort(vecPointList.begin() + nStart, vecPointList.begin() + nEnd, PointAscendingSortfunctionY);
		else
			std::sort(vecPointList.begin() + nStart, vecPointList.end(), PointAscendingSortfunctionY);
	}
}
BOOL PointDecendingSortfunctionX(DPOINT &a, DPOINT &b)
{
	if (a.x > b.x)
		return TRUE;

	return FALSE;
}
BOOL PointDecendingSortfunctionY(DPOINT &a, DPOINT &b)
{
	if (a.y > b.y)
		return TRUE;
	
	return FALSE;
}
BOOL PointAscendingSortfunctionX(DPOINT &a, DPOINT &b)
{
	if (a.x < b.x)
		return TRUE;
	
	return FALSE;
}
BOOL PointAscendingSortfunctionY(DPOINT &a, DPOINT &b)
{
	if (a.y < b.y)
		return TRUE;
	
	return FALSE;
}

void SortRectX(vector <DRECT> &rectExtent, int nStart, int nEnd)
{
	int i, j, k;
	double fValue;

	if(nStart >= nEnd)
		return;

	i = nStart -1;
	j = nEnd+1;
	k = (nStart + nEnd)/2;
	fValue = rectExtent.at(k).left;
	do 
	{
		do 
		{
			i++;
		} while(rectExtent.at(i).left < fValue);
		
		do 
		{
			j--;
		} while(rectExtent.at(j).left > fValue);
		
		if(i < j)
			SwapRect(rectExtent, i, j);
	} while(i < j);

	SortRectX(rectExtent, nStart, i - 1);
	SortRectX(rectExtent, j + 1, nEnd);
}

void SortRectY(vector <DRECT> &rectExtent, int nStart, int nEnd)
{
	int i, j, k;
	double fValue;

	if(nStart >= nEnd)
		return;

	i = nStart -1;
	j = nEnd +1;
	k = (nStart + nEnd)/2;
	fValue = -rectExtent.at(k).bottom;
	do 
	{
		do 
		{
			i++;
		} while(-rectExtent.at(i).bottom < fValue);
		
		do 
		{
			j--;
		} while(-rectExtent.at(j).bottom > fValue);
		
		if(i < j)
			SwapRect(rectExtent, i, j);
	} while(i < j);

	SortRectY(rectExtent, nStart, i - 1);
	SortRectY(rectExtent, j + 1, nEnd);
}

void SwapRect(vector <DRECT> &rectExtent, int nIndex1, int nIndex2)
{
	DRECT fRect;

	fRect = rectExtent.at(nIndex1);
	rectExtent.at(nIndex1) = rectExtent.at(nIndex2);
	rectExtent.at(nIndex2) = fRect;
}
/*
//// 20181115 Add
void SortCircleObj(int nSortType, vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, double dGap)
{
	int j, k, nOrder, nNumOfData;
	double dComp;

	nNumOfData = (int)vecCircleObjList.size();

	if (nNumOfData < 2)
		return;

	if (dGap < 0)
	{
		std::sort(vecCircleObjList.begin(), vecCircleObjList.end(), CircleObjSizeAscendingSortfunction);
		dGap = vecCircleObjList.at(0).fRadius / 2.0;
	}

	j = 0;
	nOrder = 0;
	switch (nSortType)
	{
	case 0:
	case 2:
	case 4:
	case 6:
		std::sort(vecCircleObjList.begin(), vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
		dComp = vecCircleObjList.at(0).fptCenter.y;
		for (k = 0; k < nNumOfData; k++)
		{
			if (fabs(dComp - vecCircleObjList.at(k).fptCenter.y) > dGap)
			{
				switch (nSortType)
				{
				case 0:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionX);
					break;
				case 2:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 4:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionX);
					break;
				case 6:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}
				j = k;
				dComp = vecCircleObjList.at(k).fptCenter.y;
			}
			else if (k == nNumOfData - 1)
			{
				switch (nSortType)
				{
				case 0:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
					break;
				case 2:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 4:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
					break;
				case 6:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		std::sort(vecCircleObjList.begin(), vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
		dComp = vecCircleObjList.at(0).fptCenter.x;
		for (k = 0; k < nNumOfData; k++)
		{
			if (fabs(dComp - vecCircleObjList.at(k).fptCenter.x) > dGap)
			{
				switch (nSortType)
				{
				case 1:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionY);
					break;
				case 3:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 5:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionY);
					break;
				case 7:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}

				j = k;
				dComp = vecCircleObjList.at(k).fptCenter.x;
			}
			else if (k == nNumOfData - 1)
			{
				switch (nSortType)
				{
				case 1:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
					break;
				case 3:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 5:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
					break;
				case 7:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	case 10:
	case 12:
	case 14:
	case 16:
		std::sort(vecCircleObjList.begin(), vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
		dComp = vecCircleObjList.at(0).fptCenter.y;
		for (k = 0; k < nNumOfData; k++)
		{
			if (fabs(dComp - vecCircleObjList.at(k).fptCenter.y) > dGap)
			{
				switch (nSortType)
				{
				case 10:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionX);
					break;
				case 12:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 14:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionX);
					break;
				case 16:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}

				j = k;
				dComp = vecCircleObjList.at(k).fptCenter.y;
			}
			else if (k == nNumOfData - 1)
			{
				switch (nSortType)
				{
				case 10:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
					break;
				case 12:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
						nOrder = 0;
					}
					break;
				case 14:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
					break;
				case 16:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	case 11:
	case 13:
	case 15:
	case 17:
		std::sort(vecCircleObjList.begin(), vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
		dComp = vecCircleObjList.at(0).fptCenter.x;
		for (k = 0; k < nNumOfData; k++)
		{
			if (fabs(dComp - vecCircleObjList.at(k).fptCenter.x) > dGap)
			{
				switch (nSortType)
				{
				case 11:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionY);
					break;
				case 13:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 15:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionY);
					break;
				case 17:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.begin() + k, CircleObjDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}

				j = k;
				dComp = vecCircleObjList.at(k).fptCenter.x;
			}
			else if (k == nNumOfData - 1)
			{
				switch (nSortType)
				{
				case 11:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
					break;
				case 13:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
						nOrder = 0;
					}
					break;
				case 15:
					std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
					break;
				case 17:
					if (nOrder == 0)
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
						nOrder = 1;
					}
					else
					{
						std::sort(vecCircleObjList.begin() + j, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
						nOrder = 0;
					}
					break;
				}
			}
		}
		break;
	}
}
void CircleObjDecendingSortX(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd)
{
	int nNumOfData = (int)vecCircleObjList.size();
	if (nNumOfData < 1 || nEnd == nStart)
		return;

	if (nNumOfData > nStart)
	{
		if (nNumOfData > nEnd && nEnd > nStart)
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.begin() + nEnd, CircleObjDecendingSortfunctionX);
		else
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.end(), CircleObjDecendingSortfunctionX);
	}
}
void CircleObjDecendingSortY(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd)
{
	int nNumOfData = (int)vecCircleObjList.size();
	if (nNumOfData < 1 || nEnd == nStart)
		return;

	if (nNumOfData > nStart)
	{
		if (nNumOfData > nEnd && nEnd > nStart)
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.begin() + nEnd, CircleObjDecendingSortfunctionY);
		else
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.end(), CircleObjDecendingSortfunctionY);
	}
}
void CircleObjAscendingSortX(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd)
{
	int nNumOfData = (int)vecCircleObjList.size();
	if (nNumOfData < 1 || nEnd == nStart)
		return;

	if (nNumOfData > nStart)
	{
		if (nNumOfData > nEnd && nEnd > nStart)
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.begin() + nEnd, CircleObjAscendingSortfunctionX);
		else
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.end(), CircleObjAscendingSortfunctionX);
	}
}
void CircleObjAscendingSortY(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd)
{
	int nNumOfData = (int)vecCircleObjList.size();
	if (nNumOfData < 1 || nEnd == nStart)
		return;

	if (nNumOfData > nStart)
	{
		if (nNumOfData > nEnd && nEnd > nStart)
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.begin() + nEnd, CircleObjAscendingSortfunctionY);
		else
			std::sort(vecCircleObjList.begin() + nStart, vecCircleObjList.end(), CircleObjAscendingSortfunctionY);
	}
}
BOOL CircleObjDecendingSortfunctionX(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b)
{
	if (a.fptCenter.x > b.fptCenter.x)
		return TRUE;

	return FALSE;
}
BOOL CircleObjDecendingSortfunctionY(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b)
{
	if (a.fptCenter.y > b.fptCenter.y)
		return TRUE;

	return FALSE;
}
BOOL CircleObjAscendingSortfunctionX(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b)
{
	if (a.fptCenter.x < b.fptCenter.x)
		return TRUE;

	return FALSE;
}
BOOL CircleObjAscendingSortfunctionY(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b)
{
	if (a.fptCenter.y < b.fptCenter.y)
        return TRUE;

        return FALSE;
}

BOOL CircleObjSizeDecendingSortfunction(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b)
{
	if (a.fRadius > b.fRadius)
		return TRUE;

	return FALSE;
}
BOOL CircleObjSizeAscendingSortfunction(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b)
{
	if (a.fRadius < b.fRadius)
		return TRUE;

	return FALSE;
}
////
*/
//// 20200111 Add
BOOL CheckPolygonDirection(vector <DPOINT> vecPoint, int &nDir)
{
	int nVertices = (int)vecPoint.size();
	
	nDir = 1;
	if (nVertices < 3)
		return FALSE;

	double dSigned = 0.0;
	if (fabs(vecPoint.at(0).x - vecPoint.at(nVertices - 1).x) > 0.0000001 && fabs(vecPoint.at(0).y - vecPoint.at(nVertices - 1).y) > 0.0000001)
		vecPoint.push_back(vecPoint.at(0));

	for (int i = 0; i < nVertices - 1; i++)
	{
		dSigned += (vecPoint.at(i).x * vecPoint.at(i + 1).y - vecPoint.at(i + 1).x * vecPoint.at(i).y);
	}
	
	if (dSigned < 0)
		nDir = 1;
	else
		nDir = -1;

	return TRUE;
}

BOOL CheckPointInRect(const DRECT &fRect, const double x, const double y)
{
    if (fRect.left <= x && x <= fRect.right  && fRect.bottom <= y && y <= fRect.top )
        return TRUE;

		return FALSE;
}

BOOL CheckPointInRect(const DRECT &fRect, const DPOINT &pt)
{
	if (fRect.left <= pt.x && pt.x <= fRect.right  && fRect.bottom <= pt.y && pt.y <= fRect.top )
		return TRUE;

		return FALSE;
}
BOOL CheckRectInRect(DRECT *Inner, DRECT *Outer)
{
    if (Outer->left <= Inner->left && Outer->right >= Inner->right && Outer->bottom <= Inner->bottom && Outer->top >= Inner->top) 
		return TRUE;
	
	return FALSE;
}

BOOL CheckRectInRect(CdRect *Inner, CdRect *Outer)
{
    if (Outer->left <= Inner->left && Outer->right >= Inner->right && Outer->bottom <= Inner->bottom && Outer->top >= Inner->top) 
		return TRUE;
	
	return FALSE;
}

BOOL CheckUnionRect(DRECT *fRect1, DRECT *fRect2)
{   
	if(fRect1->top < fRect2->bottom || fRect1->bottom > fRect2->top || fRect1->right < fRect2->left || fRect1->left > fRect2->right)
		return FALSE;
	return TRUE;
}

BOOL CheckEqualRect(DRECT *fRect1, DRECT *fRect2)
{
	if (fRect1->left == fRect2->left && fRect1->right == fRect2->right && fRect1->bottom == fRect2->bottom && fRect1->top == fRect2->top)
		return TRUE;

	return FALSE;
}
BOOL CheckEqualRect(CdRect *fRect1, CdRect *fRect2)
{
	if (fRect1->left == fRect2->left && fRect1->right == fRect2->right && fRect1->bottom == fRect2->bottom && fRect1->top == fRect2->top)
		return TRUE;

	return FALSE;
}
BOOL CheckRectSize(DRECT *fRect1, DRECT *fRect2)
{
	if (fabs((fRect1->right - fRect1->left) - (fRect2->right - fRect2->left)) < 0.000001 && fabs((fRect1->top - fRect1->bottom) - (fRect2->top - fRect2->bottom)) < 0.000001)
		return TRUE;

	return FALSE;
}
BOOL CheckRectSize(CdRect *fRect1, CdRect *fRect2)
{
	if (fabs((fRect1->right - fRect1->left) - (fRect2->right - fRect2->left)) < 0.000001 && fabs((fRect1->top - fRect1->bottom) - (fRect2->top - fRect2->bottom)) < 0.000001)
		return TRUE;

	return FALSE;
}

BOOL CheckRectTypePolygon(const DPOINT *fptVert, int nSize)
{
	if (nSize != 5)
		return FALSE;

	if (fptVert[0].x != fptVert[4].x || fptVert[0].y != fptVert[4].y)
		return FALSE;

	if (fptVert[0].x == fptVert[1].x && fptVert[0].y != fptVert[1].y)
	{
		if (fptVert[1].y == fptVert[2].y && fptVert[3].y == fptVert[0].y && fptVert[2].x == fptVert[3].x)
		{
			return TRUE;
		}
	}
	else if (fptVert[0].y == fptVert[1].y && fptVert[0].x != fptVert[1].x)
	{
		if (fptVert[1].x == fptVert[2].x && fptVert[3].x == fptVert[0].x && fptVert[2].y == fptVert[3].y)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL IsPerpendicular(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint)
{
	double yDelta_a= middlePoint.y - startPoint.y;
	double xDelta_a= middlePoint.x - startPoint.x;
	double yDelta_b= endPoint.y - middlePoint.y;
	double xDelta_b= endPoint.x - middlePoint.x;

	// checking whether the line of the two pts are vertical
	if (fabs(xDelta_a) <= 0.0 && fabs(yDelta_b) <= 0.0)
	{
		TRACE(_T("The points are pependicular and parallel to x-y axis\n"));
		return TRUE;
	}
	if (fabs(yDelta_a) <= 0.0)
	{
		TRACE(_T(" A line of two point are perpendicular to x-axis 1\n"));
		return TRUE;
	}
	else if (fabs(yDelta_b) <= 0.0)
	{
		TRACE(_T(" A line of two point are perpendicular to x-axis 2\n"));
		return TRUE;
	}
	else if (fabs(xDelta_a) <= 0.0)
	{
		TRACE(_T(" A line of two point are perpendicular to y-axis 1\n"));
		return TRUE;
	}
	else if (fabs(xDelta_b) <= 0.0)
	{
		TRACE(_T(" A line of two point are perpendicular to y-axis 2\n"));
		return TRUE;
	}
	else
		return FALSE ;

	return TRUE;
}

//Equation of a Circle from 3 Points
DPOINT ArcCenter(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint)
{
	DPOINT fptCenter;
	double rd, Cx, Cy;

	if (startPoint.x == middlePoint.x || middlePoint.x == endPoint.x)
	{
		if (startPoint.x == middlePoint.x)
		{
			fptCenter.y = (startPoint.y + middlePoint.y) / 2.0;
			rd = (endPoint.y - middlePoint.y) / (endPoint.x - middlePoint.x);
			Cx = (middlePoint.x + endPoint.x) / 2.0;
			Cy = (middlePoint.y + endPoint.y) / 2.0;
		}
		else
		{
			fptCenter.y = (middlePoint.y + endPoint.y) / 2.0;
			rd = (middlePoint.y - startPoint.y) / (middlePoint.x - startPoint.x);
			Cx = (startPoint.x + middlePoint.x) / 2.0;
			Cy = (startPoint.y + middlePoint.y) / 2.0;
		}
		fptCenter.x = rd*Cy + Cx - (rd * fptCenter.y);

		return fptCenter;
	}

	if (startPoint.y == middlePoint.y || middlePoint.y == endPoint.y)
	{
		if (startPoint.y == middlePoint.y)
		{
			fptCenter.x = (startPoint.x + middlePoint.x) / 2.0;
			rd = (endPoint.y - middlePoint.y) / (endPoint.x - middlePoint.x);
			Cx = (middlePoint.x + endPoint.x) / 2.0;
			Cy = (middlePoint.y + endPoint.y) / 2.0;
		}
		else
		{
			fptCenter.x = (middlePoint.x + endPoint.x) / 2.0;
			rd = (middlePoint.y - startPoint.y) / (middlePoint.x - startPoint.x);
			Cx = (startPoint.x + middlePoint.x) / 2.0;
			Cy = (startPoint.y + middlePoint.y) / 2.0;
		}
		fptCenter.y = (Cx - fptCenter.x) / rd + Cy;

		return fptCenter;
	}

	double ma = (middlePoint.y - startPoint.y) / (middlePoint.x - startPoint.x);
	double mb = (endPoint.y - middlePoint.y) / (endPoint.x - middlePoint.x);

	fptCenter.x = (ma * mb * (startPoint.y - endPoint.y) + mb * (startPoint.x + middlePoint.x) -
		ma * (middlePoint.x + endPoint.x)) / (2 * (mb - ma));

	fptCenter.y = (-1 * (fptCenter.x - (startPoint.x + middlePoint.x) / 2) / ma) +
		((startPoint.y + middlePoint.y) / 2);

	return fptCenter;
}

double ArcRadius(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint)
{
	CdPoint fptCenter = ArcCenter(startPoint,middlePoint,endPoint);
	double fRadius = sqrt((startPoint.x-fptCenter.x)*(startPoint.x-fptCenter.x)+(startPoint.y-fptCenter.y)*(startPoint.y-fptCenter.y));
	return fRadius;
}

double ArcAngle(CdPoint startPoint,CdPoint endPoint,CdPoint centerPoint)
{
	// 두 선분의 각도 계산
	double dy_a= startPoint.y - centerPoint.y;
	double dx_a= startPoint.x - centerPoint.x;
    double angle_a = atan2(dy_a , dx_a) * 180.0 / PI;
	angle_a = fmod(angle_a+360.0,360);
	
	double dy_b= endPoint.y - centerPoint.y;
	double dx_b= endPoint.x - centerPoint.x;
	double angle_b = atan2(dy_b , dx_b) * 180.0 / PI;
	angle_b = fmod(angle_b+360.0,360);

	if(angle_b < angle_a)
		angle_b += 360.0;
	double fAngle = angle_b-angle_a;

	return fAngle;
}

//++++++++++++++++++++++++++++
// Arc길이가 주어졌을때 각도 계산
double ArcAngle(CdPoint startPoint,CdPoint centerPoint,double fArcLength)
{
	double fRadius = sqrt((startPoint.x-centerPoint.x)*(startPoint.x-centerPoint.x)+(startPoint.y-centerPoint.y)*(startPoint.y-centerPoint.y));
	double fCircleLength = 2*PI*fRadius;
	
	if(fCircleLength == 0)
		return 0;

	double fAngle = (fArcLength/fCircleLength)*360.0;

	return fmod(fAngle,360.0);
}

double ArcLength(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint)
{
	CdPoint centerPoint;
	if (!IsPerpendicular(startPoint, middlePoint, endPoint))
		centerPoint = ArcCenter(startPoint, middlePoint, endPoint);	
	else if (!IsPerpendicular(startPoint, endPoint, middlePoint))
		centerPoint = ArcCenter(startPoint, endPoint, middlePoint);	
	else if (!IsPerpendicular(middlePoint, startPoint, endPoint))
		centerPoint = ArcCenter(middlePoint, startPoint, endPoint);	
	else if (!IsPerpendicular(middlePoint, endPoint, startPoint))
		centerPoint = ArcCenter(middlePoint, endPoint, startPoint);	
	else if (!IsPerpendicular(endPoint, middlePoint, startPoint))
		centerPoint = ArcCenter(endPoint, middlePoint, startPoint);	
	else if (!IsPerpendicular(endPoint, startPoint, middlePoint))
		centerPoint = ArcCenter(endPoint, startPoint, middlePoint);	
	else { 
		TRACE(_T("\nThe three pts are perpendicular to axis\n"));
		return -1;
	}
	// 각도 계산
	double fAngle = ArcAngle(startPoint,endPoint,centerPoint);
	fAngle = fabs(fAngle);

	double fRadius = sqrt((startPoint.x-centerPoint.x)*(startPoint.x-centerPoint.x) + (startPoint.y-centerPoint.y)*(startPoint.y-centerPoint.y));
	double fArcLength = 2*PI* fRadius;
	fArcLength = fArcLength * fAngle / 360.0;
	return fArcLength;
}

BOOL CheckPointInMyOval(double fCx, double fCy, double fWidth, double fHeight,double x,double y)
{
    double  X1, Y1, X2, Y2, d, ww;
    
    if (fWidth > fHeight )
	{
        ww = fHeight;
        d = (fWidth - ww) / 2;
        X1 = fCx - d;
        Y1 = fCy;
        X2 = fCx + d;
        Y2 = fCy;
	}
    else
	{
        ww = fWidth;
        d = (fHeight - ww) / 2;
        X1 = fCx;
        Y1 = fCy - d;
        X2 = fCx;
        Y2 = fCy + d;
    }
    
	return CheckPointInMyLineRound(X1, Y1, X2, Y2, ww,x,y);
}


BOOL CheckPointInMyPolygonNSide(int n, double cX, double cY, double d, double ang,double x,double y)
{
	double cV, sV, sTheta, cTheta, XX, YY, R, X1, Y1, Theta;
	int i;
	vector <DPOINT> vecVertices;
	DPOINT fpt;
    if (n < 3) return FALSE;

    cV = cos(ang * DEG2RAD);
    sV = sin(ang * DEG2RAD);
    R = d / 2;
    
    Theta = 2 * PI / n;
    X1 = R;
    Y1 = 0;
    
    for (i=0 ; i<n ; i++)
	{
        sTheta = sin(i * Theta);
        cTheta = cos(i * Theta);
        XX = X1 * cTheta - Y1 * sTheta;
        YY = X1 * sTheta + Y1 * cTheta;          
            
        fpt.x =(XX * cV - YY * sV) + cX;
        fpt.y =(XX * sV + YY * cV) + cY;
		vecVertices.push_back(fpt);
    }

	if(CheckPointInPolygon(&vecVertices[0],(int)vecVertices.size(),x,y))
		return TRUE;
	else
		return FALSE;	
}

BOOL CheckPointInMyConcavePolygon(DPOINT *fPoint,int nNumberOfVertex,double x,double y)
{
	double *ptBuf = new double [2*nNumberOfVertex];
	BOOL bCheck = FALSE;
	for(int i = 0; i<nNumberOfVertex; i++)
	{
		ptBuf[i*2] = fPoint[i].x;
		ptBuf[i*2+1] = fPoint[i].y;
	}
	bCheck = CheckPointInPolygon(ptBuf,nNumberOfVertex,x,y);
	delete [] ptBuf;
	return bCheck;
}
BOOL CheckPointInMyConcavePolygon(CdPoint3D *fPoint,int nNumberOfVertex,double x,double y)
{
	double *ptBuf = new double [2*nNumberOfVertex];
	BOOL bCheck = FALSE;
	for(int i = 0; i<nNumberOfVertex; i++)
	{
		ptBuf[i*2] = fPoint[i].x;
		ptBuf[i*2+1] = fPoint[i].y;
	}
	bCheck = CheckPointInPolygon(ptBuf,nNumberOfVertex,x,y);
	delete [] ptBuf;
	return bCheck;
}
BOOL CheckPointInMyConcavePolygon(vector <DPOINT> &fPoint,double x,double y)
{
	return CheckPointInPolygon(&fPoint[0],(int)fPoint.size(),x,y);
}
BOOL CheckPointInMyThermalSquareRound(double fCx, double fCy, double fOutDia, double fInDia, double fAngle, int nNumOfSpoke, double fSpokeGap,double x,double y)
{
    double  Ro, Ri,nLength,cV,sV,X1,Y1,X2,Y2,fPointx;

	Ro = fOutDia / 2;
	Ri = fInDia / 2;
	fAngle = fAngle * DEG2RAD;
	nLength= Ro *sqrt(2.0);

	cV = cos(fAngle);
	sV = sin(fAngle);

	X1 = fCx + nLength * cV;
	Y1 = fCy + nLength * sV;

	cV = cos(fAngle + PI);
	sV = sin(fAngle + PI);

	X2 = fCx + nLength * cV;
	Y2 = fCy + nLength * sV;

	if(CheckPointInMyCircle(fCx,fCy,Ri,30,x,y))
		return FALSE;

	if(CheckPointInMyLine(X1,Y1,X2,Y2 ,fSpokeGap,x,y))
		return FALSE;
	
	fPointx = X1;
	X1= -(Y1 - fCy) + fCx;
	Y1=fPointx - fCx  + fCy;

	fPointx = X2;
	X2= -(Y2 - fCy) + fCx;
	Y2=fPointx - fCx  + fCy;
	if(CheckPointInMyLine(X1,Y1,X2,Y2 ,fSpokeGap,x,y))
		return FALSE;

	if(CheckPointInMyRect(fCx-Ro,fCy-Ro,fCx+Ro,fCy+Ro,x,y))
		return TRUE;
	else
		return FALSE;
	
}
BOOL CheckPointInMyThermalSquareOpen(double fCx, double fCy, double fOutDia, double fInDia, double fAngle, int nNumOfSpoke, double fSpokeGap,double x,double y)
{

	return CheckPointInMyThermalRoundOpen(fCx, fCy, fOutDia, fOutDia, fAngle, nNumOfSpoke, fSpokeGap, (fOutDia - fInDia) / 2,x,y);
	
}
BOOL CheckPointInMyThermalSquare(double fCx, double fCy, double fOutDia, double fInDia, double fAngle, int nNumOfSpoke, double fSpokeGap,double x,double y)
{
    double Ro, Ri, t, k, Ang1,Y1, XX, YY;
	int i, j, n;
	double fVertex[40];
	DPOINT pc;

	if (fAngle > 90 )
	{
		do 
		{
			fAngle = fAngle - 90;
		}
		while (fAngle > 90);
	}
	if (fAngle < 0 )
	{
		do
		{
			fAngle = fAngle + 90;
		}
		while (fAngle < 0);
	}

	Ro = fOutDia / 2;
	Ri = fInDia / 2;
	t = fSpokeGap / 2;
	Ang1 = fAngle * DEG2RAD;
	k = tan(Ang1); //   '기울기

	if (fAngle == 0 || fAngle == 90 )
	{
		fVertex[0] = fCx + Ri;
		fVertex[1] = fCy + t;
    
		fVertex[2] = fCx + Ro;
		fVertex[3] = fVertex[1];
    
		fVertex[4] = fVertex[2];
		fVertex[5] = fCy + Ro;
    
		fVertex[6] = fCx + t;
		fVertex[7] = fVertex[5];
    
		fVertex[8] = fVertex[6];
		fVertex[9] = fCy + Ri;
    
		fVertex[10] = fVertex[0];
		fVertex[11] = fVertex[9];

		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;

    
		for (i=0 ; i<6 ; i++)
		{
			if (fCx < fVertex[i*2])
			{
				fVertex[i*2] = fCx - fabs(fVertex[i*2] - fCx); 
			}
			else
			{
				fVertex[i*2] = fCx + fabs(fVertex[i*2] - fCx);
			}
		}
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;


		for (i=0 ; i<6 ; i++)
		{
			if (fCy < fVertex[i*2+1]) 
				fVertex[i*2+1] = fCy - fabs(fVertex[i*2+1] - fCy); 
			else 
				fVertex[i*2+1] = fCy + fabs(fVertex[i*2+1] - fCy);
		}
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;

		for (i=0 ; i<6 ; i++)
		{
			if (fCx < fVertex[i*2])
			{
				fVertex[i*2] = fCx - fabs(fVertex[i*2] - fCx); 
			}
			else
			{
				fVertex[i*2] = fCx + fabs( fVertex[i*2] - fCx);
			}
		}
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;

		return FALSE;
	}

	pc.x = fCx;
	pc.y = fCy + (t * sqrt(k * k + 1));
//                    ' pC를 지나고 기울기가 k인 직선의 방정식
//                    ' k(x - pc.x) = y - pc.y

	XX = fCx + Ri;
	YY = fCy + Ri;

	Y1 = k * (XX - pc.x) + pc.y;
	if (Y1 > YY )
	{
		fVertex[0] = (YY - pc.y) / k + pc.x;
		fVertex[1] = YY;
		n = 1;
	}
	else
	{
		fVertex[0] = XX;
		fVertex[1] = YY;
    
		fVertex[2] = XX;
		fVertex[3] = Y1;
		n = 2;
	}

	XX = fCx + Ro;
	YY = fCy + Ro;

	Y1 = k * (XX - pc.x) + pc.y;
	if (Y1 > YY )
	{
		fVertex[n*2] = (YY - pc.y) / k + pc.x;
		fVertex[n*2+1] = YY;
		n++;
	}		
	else
	{
		fVertex[n*2] = XX;
		fVertex[n*2+1] = Y1;
		n++;
		fVertex[n*2] = XX;
		fVertex[n*2+1] = YY;
		n++;
	}


	pc.x = fCx + (t * sqrt(k * k + 1));
	pc.y = fCy;

	Ang1 = (fAngle + 90) * DEG2RAD;
	k = tan(Ang1);

//                    ' pC를 지나고 기울기가 k인 직선의 방정식
//                    ' k(x - pc.x) = y - pc.y

	XX = fCx - Ro;
	YY = fCy + Ro;

	Y1 = k * (XX - pc.x) + pc.y;
	if (Y1 > YY )
	{
		fVertex[n*2] = (YY - pc.y) / k + pc.x;
		fVertex[n*2+1] = YY;
		n++;
	}
	else
	{
		fVertex[n*2] = XX;
		fVertex[n*2+1] = YY;
		n++;
    
		fVertex[n*2] = XX;
		fVertex[n*2+1] = Y1;
		n++;
	}

	XX = fCx - Ri;
	YY = fCy + Ri;

	Y1 = k * (XX - pc.x) + pc.y;
	if (Y1 > YY )
	{
		fVertex[n*2] = (YY - pc.y) / k + pc.x;
		fVertex[n*2+1] = YY;
		n++;
	}
	else
	{
		fVertex[n*2] = XX;
		fVertex[n*2+1] = Y1;
		n++;
    
		fVertex[n*2] = XX;
		fVertex[n*2+1] = YY;
		n++;
	}  
	fVertex[n*2] = fVertex[0];
	fVertex[n*2+1] = fVertex[1];
	n++;
	
	if(CheckPointInPolygon(fVertex,n,x,y))
		return TRUE;


	double fx,fy;
	for (i=1 ; i<nNumOfSpoke ; i++)
	{
		for (j=0 ; j<n ; j++)
		{
			fx=(fVertex[j*2] - fCx) * 0.0 - ((fVertex[j*2+1] - fCy) * 1.0) + fCx;
			fy=(fVertex[j*2] - fCx) * 1.0 + ((fVertex[j*2+1] - fCy) * 0.0) + fCy;

			fVertex[j*2]=fx;
			fVertex[j*2+1]=fy;	
		}
		if(CheckPointInPolygon(fVertex,n,x,y))
			return TRUE;
	}
	return FALSE;
	
}
BOOL CheckPointInMyThermalRoundSquare(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke,  double fSpokeGap,double x,double y)
{
   double  Ro, Ri,nLength,cV,sV,X1,Y1,X2,Y2,fPointx;


	Ro = fOutDia / 2;
	Ri = fInDia / 2;
	fAngle = fAngle * DEG2RAD;
	nLength= Ro *sqrt(2.0);

	cV = cos(fAngle);
	sV = sin(fAngle);

	X1 = fCx + nLength * cV;
	Y1 = fCy + nLength * sV;

	cV = cos(fAngle + PI);
	sV = sin(fAngle + PI);

	X2 = fCx + nLength * cV;
	Y2 = fCy + nLength * sV;

	if(CheckPointInMyCircle(fCx,fCy,Ri,40,x,y))
		return FALSE;
	if(CheckPointInMyLine(X1,Y1,X2,Y2 ,fSpokeGap,x,y))
		return FALSE;

	fPointx = X1;
	X1= -(Y1 - fCy) + fCx;
	Y1=fPointx - fCx  + fCy;

	fPointx = X2;
	X2= -(Y2 - fCy) + fCx;
	Y2=fPointx - fCx  + fCy;


	if(CheckPointInMyLine(X1,Y1,X2,Y2 ,fSpokeGap,x,y))
		return FALSE;

	if(CheckPointInMyCircle(fCx,fCy,Ro,40,x,y))
		return TRUE;
	else
		return FALSE;	
}
BOOL CheckPointInMyThermalRoundOpen(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke, double fSpokeGap, double fAirGap,double x,double y)
{
	double Ro, Ri, t, k, a, b, c, tRoot, XX, yy, X1, Y1, X2, Y2, Ang1;
	int i,n;
	double fVertex[12];
	Ro = fOutDia / 2;    //'Width
	Ri = fInDia / 2;    //'Height
	t = fSpokeGap / 2;
                 
	if (fAngle == 0 || fAngle == 90 || fAngle == 180 || fAngle == 270 )
	{
		fVertex[0] = fCx + (Ro - fAirGap);
		fVertex[1] = fCy + t;
		fVertex[2] = fCx + Ro;
		fVertex[3] = fCy + t;
		fVertex[4] = fVertex[2];
		fVertex[5] = fCy + Ri;
		fVertex[6] = fCx + t;
		fVertex[7] = fVertex[5];
		fVertex[8] = fVertex[6];
		fVertex[9] = fCy + (Ri - fAirGap);
		fVertex[10] = fVertex[0];
		fVertex[11] = fVertex[9];
    
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;
    
		for(i=0 ; i<6 ; i++)
		{
			if (fCx < fVertex[i*2])
			{
				fVertex[i*2] = fCx - fabs(fVertex[i*2] - fCx); 
			}
			else
			{
				fVertex[i*2] = fCx + fabs(fVertex[i*2] - fCx);
			}
		}
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;
			
		for(i=0 ; i<6 ; i++)
		{
			if (fCy < fVertex[i*2+1]) 
				fVertex[i*2+1] = fCy - fabs(fVertex[i*2+1] - fCy); 
			else 
				fVertex[i*2+1] = fCy + fabs(fVertex[i*2+1] - fCy);
		}
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;

		for(i=0 ; i<6 ; i++)
		{
			if (fCx < fVertex[i*2])
			{
				fVertex[i*2] = fCx - fabs(fVertex[i*2] - fCx); 
			}
			else
			{
				fVertex[i*2] = fCx + fabs(fVertex[i*2] - fCx);
			}
		}
		if(CheckPointInPolygon(fVertex,6,x,y))
			return TRUE;

		return FALSE;
	}
	else if (fAngle == 45 )
	{
		k = 1;
		a = k;
		b = -1;
		tRoot = t * sqrt(2.0);
		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		c = yy - XX;
    
		X1 = (tRoot - b * yy - c) / a;
		X2 = (-tRoot - b * yy - c) / a;
		if (X1 > X2)
			X1 = X2;

		fVertex[0] = X1;
		fVertex[1] = yy;
    
		fVertex[2] = fVertex[0];
		fVertex[3] = fCy + Ri;
    
		fVertex[4] = fVertex[2];
		fVertex[5] = fVertex[3];
		if (fCx < fVertex[4])
		{
			fVertex[4] = fCx - fabs(fVertex[4] - fCx); 
		}
		else
		{
			fVertex[4] = fCx + fabs(fVertex[4] - fCx);
		}
		fVertex[6] = fVertex[0];
		fVertex[7] = fVertex[1];
		if (fCx < fVertex[6])
		{
			fVertex[6] = fCx - fabs(fVertex[6] - fCx); 
		}
		else
		{
			fVertex[6] = fCx + fabs(fVertex[6] - fCx);
		}
    
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;
    
		for(i=0 ; i<4 ; i++)
		{
			if (fCy < fVertex[i*2+1]) 
				fVertex[i*2+1] = fCy - fabs(fVertex[i*2+1] - fCy); 
			else 
				fVertex[i*2+1] = fCy + fabs(fVertex[i*2+1] - fCy);
		}
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;
    
		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		c = yy - XX;
		Y1 = (tRoot - a * XX - c) / b;
		Y2 = (-tRoot - a * XX - c) / b;
		if (Y1 > Y2)
			Y1 = Y2;

		fVertex[0] = XX;
		fVertex[1] = Y1;
    
		fVertex[2] = fCx + Ro;
		fVertex[3] = fVertex[1];
    
		fVertex[4] = fVertex[2];
		fVertex[5] = fVertex[3];
		if (fCy < fVertex[5]) 
			fVertex[5] = fCy - fabs(fVertex[5] - fCy); 
		else 
			fVertex[5] = fCy + fabs(fVertex[5] - fCy);
		fVertex[3] = fVertex[0];
		if (fCy < fVertex[7]) 
			fVertex[7] = fCy - fabs(fVertex[7] - fCy); 
		else 
			fVertex[7] = fCy + fabs(fVertex[7] - fCy);
    
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;


		for(i=0 ; i<4 ; i++)
		{
			if (fCx < fVertex[i*2])
			{
				fVertex[i*2] = fCx - fabs(fVertex[i*2] - fCx); 
			}
			else
			{
				fVertex[i*2] = fCx + fabs(fVertex[i*2] - fCx);
			}
		}
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;

    
		return FALSE;
	}
	else
	{       

		Ang1 = fAngle * DEG2RAD;
		k = tan(Ang1);
		a = k;
		b = -1;
		c = (fCy + Ri - fAirGap / 2) - (k * (fCx + Ro - fAirGap / 2));
		tRoot = t * sqrt(k * k + 1);
		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		X1 = (tRoot - b * yy - c) / a;
		X2 = (-tRoot - b * yy - c) / a;
		if (X1 > X2)
			X1 = X2;

		n = 0;
		if ((X1 > fCx + Ro - fAirGap) || (X1 < fCx) )
			return FALSE;    //' Error
		else
		{
			fVertex[0] = X1;
			fVertex[1] = yy;
		}

		fVertex[2] = fVertex[0];
		fVertex[3] = fCy + Ri;

		fVertex[4] = fVertex[2];
		fVertex[5] = fVertex[3];
		if (fCx < fVertex[4])
		{
			fVertex[4] = fCx - fabs(fVertex[4] - fCx); 
		}
		else
		{
			fVertex[4] = fCx + fabs(fVertex[4] - fCx);
		}

		fVertex[6] = fVertex[0];
		fVertex[7] = fVertex[1];
		if (fCx < fVertex[6])
		{
			fVertex[6] = fCx - fabs(fVertex[6] - fCx); 
		}
		else
		{
			fVertex[6] = fCx + fabs(fVertex[6] - fCx);
		}
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;

		for(i=0 ; i<4 ; i++)
		{
			if (fCy < fVertex[i*2+1]) 
				fVertex[i*2+1] = fCy - fabs(fVertex[i*2+1] - fCy); 
			else 
				fVertex[i*2+1] = fCy + fabs(fVertex[i*2+1] - fCy);
		}
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;

		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		Y1 = (tRoot - a * XX - c) / b;
		Y2 = (-tRoot - a * XX - c) / b;
    
		if (Y1 > Y2)
			Y1 = Y2;
		n = 0;
		if ((Y1 > fCy + Ri - fAirGap) || Y1 < fCy )
			return FALSE;  //  'Erroe
		else
		{
			fVertex[0] = XX;
			fVertex[1] = Y1;
		}
    
		fVertex[2] = fCx + Ro;
		fVertex[3] = fVertex[1];
    
		fVertex[4] = fVertex[2];
		fVertex[5] = fVertex[3];
		if (fCy < fVertex[5]) 
			fVertex[5] = fCy - fabs(fVertex[5] - fCy); 
		else 
			fVertex[5] = fCy + fabs(fVertex[5] - fCy);

		fVertex[6] = fVertex[0];
		fVertex[7] = fVertex[1];
		if (fCy < fVertex[7]) 
			fVertex[7] = fCy - fabs(fVertex[7] - fCy); 
		else 
			fVertex[7] = fCy + fabs(fVertex[7] - fCy);

		
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;
    
		for(i=0 ; i<=4 ; i++)
		{
			if (fCx < fVertex[i*2])
			{
				fVertex[i*2] = fCx - fabs(fVertex[i*2] - fCx); 
			}
			else
			{
				fVertex[i*2] = fCx + fabs(fVertex[i*2] - fCx);
			}
		}
    
		if(CheckPointInPolygon(fVertex,4,x,y))
			return TRUE;
    
		return FALSE;
	}
	
}
BOOL CheckPointInMyThermalRound(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke, double fSpokeGap, double fAirGap,double x,double y)
{
	double Ro, Ri, t, k, a, b, c, tRoot, XX, yy, X1, Y1, X2, Y2, Ang1;
	DPOINT p;
	double m;
	int i,n;
	double fVertexBuf[40];

	Ro = fOutDia / 2;    //'Width
	Ri = fInDia / 2;    //'Height
	t = fSpokeGap / 2;
                 
	if (fAngle == 0 || fAngle == 90 || fAngle == 180 || fAngle == 270 )
	{
		fVertexBuf[0] = fCx + (Ro - fAirGap);
		fVertexBuf[1] = fCy + t;
		fVertexBuf[2] = fCx + Ro;
		fVertexBuf[3] = fCy + t;
		fVertexBuf[4] = fVertexBuf[2];
		fVertexBuf[5] = fCy + Ri;
		fVertexBuf[6] = fCx + t;
		fVertexBuf[7] = fVertexBuf[5];
		fVertexBuf[8] = fVertexBuf[6];
		fVertexBuf[9] = fCy + (Ri - fAirGap);
		fVertexBuf[10] = fVertexBuf[0];
		fVertexBuf[11] = fVertexBuf[9];
		if(CheckPointInPolygon(fVertexBuf,6,x,y))
			return TRUE;
   
		for (i=0; i<6 ; i++)
		{
			if (fCx < fVertexBuf[2*i])
			{
				fVertexBuf[2*i] = fCx - fabs(fVertexBuf[2*i] - fCx); 
			}
			else
			{
				fVertexBuf[2*i] = fCx + fabs(fVertexBuf[2*i] - fCx);
			}
		}
		if(CheckPointInPolygon(fVertexBuf,6,x,y))
			return TRUE;
   
		for (i=0; i<6 ; i++)
		{
			if (fCy < fVertexBuf[i*2+1]) 
				fVertexBuf[i*2+1] = fCy - fabs(fVertexBuf[i*2+1] - fCy); 
			else 
				fVertexBuf[i*2+1] = fCy + fabs(fVertexBuf[i*2+1] - fCy);
		}
		if(CheckPointInPolygon(fVertexBuf,6,x,y))
			return TRUE;

		for (i=0; i<6 ; i++)
		{
		   if (fCx < fVertexBuf[2*i])
			{
				fVertexBuf[2*i] = fCx - fabs(fVertexBuf[2*i] - fCx); 
			}
			else
			{
				fVertexBuf[2*i] = fCx + fabs(fVertexBuf[2*i] - fCx);
			}       
		}
		if(CheckPointInPolygon(fVertexBuf,6,x,y))
			return TRUE;

		return FALSE;
	}
	else if (fAngle == 45 )
	{
		k = 1;
		a = k;
		b = -1;
		tRoot = t * sqrt(2.0);
		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		c = yy - XX;
    
		X1 = (tRoot - b * yy - c) / a;
		X2 = (-tRoot - b * yy - c) / a;
		if (X1 > X2 )
			X1 = X2;

		fVertexBuf[0] = X1;
		fVertexBuf[1] = yy;
    
		yy = fCy + Ri;
		XX = fCx + Ro;
		c = yy - XX;
		X1 = (tRoot - b * yy - c) / a;
		X2 = (-tRoot - b * yy - c) / a;
		if (X1 > X2)
			X1 = X2;

		fVertexBuf[4] = fVertexBuf[2] = X1;
		fVertexBuf[5] = fVertexBuf[3] = yy;    

		if (fCx < fVertexBuf[4])
		{
			fVertexBuf[4] = fCx - fabs(fVertexBuf[4] - fCx); 
		}
		else
		{
			fVertexBuf[4] = fCx + fabs(fVertexBuf[4] - fCx);
		}

		fVertexBuf[6] = fVertexBuf[0];
		fVertexBuf[7] = fVertexBuf[1];

		if (fCx < fVertexBuf[6])
		{
			fVertexBuf[6] = fCx - fabs(fVertexBuf[6] - fCx); 
		}
		else
		{
			fVertexBuf[6] = fCx + fabs(fVertexBuf[6] - fCx);
		}
		if(CheckPointInPolygon(fVertexBuf,4,x,y))
			return TRUE;

  
		for (i=0; i<4 ; i++)
		{
			if (fCy < fVertexBuf[i*2+1]) 
				fVertexBuf[i*2+1] = fCy - fabs(fVertexBuf[i*2+1] - fCy); 
			else 
				fVertexBuf[i*2+1] = fCy + fabs(fVertexBuf[i*2+1] - fCy);
		}
		if(CheckPointInPolygon(fVertexBuf,4,x,y))
			return TRUE;

				
		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		c = yy - XX;
		Y1 = (tRoot - a * XX - c) / b;
		Y2 = (-tRoot - a * XX - c) / b;
		if (Y1 > Y2)
			Y1 = Y2;

		fVertexBuf[0] = XX;
		fVertexBuf[1] = Y1;
    
		yy = fCy + Ri;
		XX = fCx + Ro;
		c = yy - XX;
		Y1 = (tRoot - a * XX - c) / b;
		Y2 = (-tRoot - a * XX - c) / b;
		if (Y1 > Y2)
			Y1 = Y2;

		fVertexBuf[4] = fVertexBuf[2] = XX;
		fVertexBuf[5] = fVertexBuf[3] = Y1;
    
		if (fCy < fVertexBuf[5]) 
			fVertexBuf[5] = fCy - fabs(fVertexBuf[5] - fCy); 
		else 
			fVertexBuf[5] = fCy + fabs(fVertexBuf[5] - fCy);
		
		fVertexBuf[6] = fVertexBuf[0];
		fVertexBuf[7] = fVertexBuf[1];
		if (fCy < fVertexBuf[7]) 
			fVertexBuf[7] = fCy - fabs(fVertexBuf[7] - fCy); 
		else 
			fVertexBuf[7]  = fCy + fabs(fVertexBuf[7] - fCy);
    
		if(CheckPointInPolygon(fVertexBuf,4,x,y))
			return TRUE;

		for (i=0; i<4 ; i++)
		{
			if (fCx < fVertexBuf[i*2])
			{
				fVertexBuf[i*2] = fCx - fabs(fVertexBuf[i*2] - fCx); 
			}
			else
			{
				fVertexBuf[i*2] = fCx + fabs(fVertexBuf[i*2] - fCx);
			}
		}
 		if(CheckPointInPolygon(fVertexBuf,4,x,y))
			return TRUE;
		
    
		return FALSE;
	}
	else
	{    
		Ang1 = fAngle * DEG2RAD;
		k = tan(Ang1);
		a = k;
		b = -1;
		c = (fCy + Ri - fAirGap / 2) - (k * (fCx + Ro - fAirGap / 2));
		tRoot = t * sqrt(k * k + 1);
		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		X1 = (tRoot - b * yy - c) / a;
		X2 = (-tRoot - b * yy - c) / a;
		if (X1 > X2)
			X1 = X2;

		n = 0;
		if (X1 > fCx + Ro - fAirGap)
			return FALSE;    //' Error
		else
		{
			fVertexBuf[n*2] = X1;
			fVertexBuf[n*2+1] = yy;
        
			if (X1 < fCx)
			{
				fVertexBuf[n*2] = fCx;
				fVertexBuf[n*2+1] = yy + k * fabs(X1 - fCx);               
			}
			n++;
		}

		yy = fCy + Ri;
		XX = fCx + Ro;
		X1 = (tRoot - b * yy - c) / a;
		X2 = (-tRoot - b * yy - c) / a;
		if (X1 > X2)
			X1 = X2;

		if (X1 > fCx + Ro)
			return FALSE;    //'Error
		else
		{
			fVertexBuf[n*2] = X1;
			fVertexBuf[n*2+1] = yy;
        
			n++;
		}

		m = n - 1;
		for (i=m ; i>=0 ; i--)
		{
			fVertexBuf[n*2] = fVertexBuf[i*2];
			fVertexBuf[n*2+1] = fVertexBuf[i*2+1];
			if (fCx < fVertexBuf[i*2])
			{
				fVertexBuf[i*2] = fCx - fabs(fVertexBuf[i*2] - fCx); 
			}
			else
			{
				fVertexBuf[i*2] = fCx + fabs(fVertexBuf[i*2] - fCx);
			}
			n++;
		}
		fVertexBuf[n*2] = fVertexBuf[0];
		fVertexBuf[n*2+1] = fVertexBuf[1];
		n++;
 		if(CheckPointInPolygon(fVertexBuf,n,x,y))
			return TRUE;

    

		for (i=0 ; i < n ; i++)
		{
			if (fCy < fVertexBuf[i*2+1]) 
				fVertexBuf[i*2+1] = fCy - fabs(fVertexBuf[i*2+1] - fCy); 
			else 
				fVertexBuf[i*2+1] = fCy + fabs(fVertexBuf[i*2+1] - fCy);
		}
 		if(CheckPointInPolygon(fVertexBuf,n,x,y))
			return TRUE;

		yy = fCy + Ri - fAirGap;
		XX = fCx + Ro - fAirGap;
		Y1 = (tRoot - a * XX - c) / b;
		Y2 = (-tRoot - a * XX - c) / b;
    
		if (Y1 > Y2)
			Y1 = Y2;

		n = 0;
		if (Y1 > fCy + Ri - fAirGap)
			return FALSE;    //'Erroe
		else
		{
			fVertexBuf[n*2] = XX;
			fVertexBuf[n*2+1] = Y1;
        
			if (Y1 < fCy)
			{
				fVertexBuf[n*2] = XX + fabs(Y1 - fCy) / k;
				fVertexBuf[n*2+1] = fCy;
			}
			n++;
		}
    
		yy = fCy + Ri;
		XX = fCx + Ro;
		Y1 = (tRoot - a * XX - c) / b;
		Y2 = (-tRoot - a * XX - c) / b;
		if (Y1 > Y2)
			Y1 = Y2;
		if (Y1 > yy )
			return FALSE;  //   'Error
		else
		{
			fVertexBuf[n*2] = XX;
			fVertexBuf[n*2+1] = Y1;
			n++;
		}
    
		m = n - 1;
		for (i=m ; i>=0 ; i--)
		{
			fVertexBuf[n*2] = fVertexBuf[i*2];
			fVertexBuf[n*2+1] = fVertexBuf[i*2+1];
			if (fCy < fVertexBuf[i*2+1]) 
				fVertexBuf[i*2+1] = fCy - fabs(fVertexBuf[i*2+1] - fCy); 
			else 
				fVertexBuf[i*2+1] = fCy + fabs(fVertexBuf[i*2+1] - fCy);
			n++;
		}
		fVertexBuf[n*2] = fVertexBuf[0];
		fVertexBuf[n*2+1] = fVertexBuf[1];
		n++;
    
   
    
  		if(CheckPointInPolygon(fVertexBuf,n,x,y))
			return TRUE;   
		for (i = 0 ; i < n ; i++)
		{
			if (fCx < fVertexBuf[i*2])
			{
				fVertexBuf[i*2] = fCx - fabs(fVertexBuf[i*2] - fCx); 
			}
			else
			{
				fVertexBuf[i*2] = fCx + fabs(fVertexBuf[i*2] - fCx);
			}
		}
  		if(CheckPointInPolygon(fVertexBuf,n,x,y))
			return TRUE;  
		else
			return FALSE;
	}
	
}

BOOL CheckNumericCharacter(CString strCharactor, BOOL bUnsignedInt)
{
	int i, nS = 0, nLength = 0;
	TCHAR szTemp[MAX_DATA_LENGTH];

	nS = 0;
	nLength = strCharactor.GetLength();

	_stprintf(szTemp, _T("%s"), strCharactor);
	if (strCharactor.Left(1) == _T("-") || strCharactor.Left(1) == _T("+"))
	{
		if (bUnsignedInt)
			return FALSE;

		nS = 1;
	}
	for (i = nS; i < nLength; i++)
	{
		if (szTemp[i] == NULL)
			break;

		if (szTemp[i] == _T('.'))
		{
			return FALSE;
		}

		if (!_istdigit(szTemp[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

//BOOL CheckArcRound(GLfloat cx, GLfloat cy, GLfloat r, GLfloat start_angle, GLfloat arc_angle, GLfloat width,int dir,double x,double y) 
//{//kjc
//	GLfloat halfWidth = width/2.0;
//	DPOINT bufPt;
//	if(dir == CW)
//	{
//		if(CheckPointInArc(cx,cy,r-halfWidth,start_angle-arc_angle,start_angle,x,y))
//			return FALSE;
//		bufPt.x = cx+r*cos(start_angle-arc_angle);
//		bufPt.y = cy+r*sin(start_angle-arc_angle);
//		if(CheckPointInArc(bufPt.x,bufPt.y,halfWidth,start_angle-arc_angle+PI,start_angle-arc_angle+2*PI,x,y))
//			return TRUE;
//		if(CheckPointInArc(cx,cy,r+halfWidth,start_angle-arc_angle,start_angle,x,y))
//			return TRUE;
//		bufPt.x = cx+r*cos(start_angle);
//		bufPt.y = cy+r*sin(start_angle);
//		if(CheckPointInArc(bufPt.x,bufPt.y,halfWidth,start_angle,start_angle+PI,x,y))
//			return TRUE;
//	}
//	else if(dir == CCW)
//	{
//		if(CheckPointInArc(cx,cy,r-halfWidth,start_angle,start_angle+PI,x,y))
//			return FALSE;
//		bufPt.x = cx+r*cos(start_angle+arc_angle);
//		bufPt.y = cy+r*sin(start_angle+arc_angle);
//		if(CheckPointInArc(bufPt.x,bufPt.y,halfWidth,start_angle+arc_angle,start_angle+arc_angle+PI,x,y))
//			return TRUE;
//		if(CheckPointInArc(cx,cy,r+halfWidth,start_angle,start_angle+arc_angle,x,y))
//			return TRUE;
//		bufPt.x = cx+r*cos(start_angle);
//		bufPt.y = cy+r*sin(start_angle);
//		if(CheckPointInArc(bufPt.x,bufPt.y,halfWidth,start_angle-PI,start_angle,x,y))
//			return TRUE;
//	}
//	return FALSE;
//}
BOOL CheckPointInMyThermal(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke,  double fSpokeGap,double x,double y)
{
   double X1, Y1, X2, Y2, R, Ro, cV, sV, XX, Xa, Ya, Xb, Yb, d, cTheta, sTheta;
	DPOINT pc;
    int i;
	

	cV = cos(fAngle * DEG2RAD);
	sV = sin(fAngle * DEG2RAD);

	R = (fOutDia - fInDia) / 4;
	Ro = fInDia / 2 + R;
	d = (fSpokeGap / 2 + R);

	cTheta = sqrt(Ro * Ro - d * d) / Ro;
	sTheta = d / Ro;

	Xa = Ro * (cTheta * cV - sTheta * sV);
	Ya = Ro * (sTheta * cV + cTheta * sV);
	Xb = Ro * (cTheta * cV + sTheta * sV);
	Yb = Ro * (cTheta * sV - sTheta * cV);

	for (i=1 ; i<=nNumOfSpoke ; i++)
	{
		cV = cos(2 * i * PI / nNumOfSpoke);
		sV = sin(2 * i * PI / nNumOfSpoke);

		X1 = Xa * cV - Ya * sV;
		Y1 = Xa * sV + Ya * cV;
		X2 = Xb * cV - Yb * sV;
		Y2 = Xb * sV + Yb * cV;

		cV = cos(2 * PI / nNumOfSpoke);
		sV = sin(2 * PI / nNumOfSpoke);
		XX = X2 * cV - Y2 * sV;
		Y2 = X2 * sV + Y2 * cV;
		X2 = XX;
		
		if (X1 * Y2 - X2 * Y1 > 0 ) 
			if(CheckPointInMyArc(fCx + X2, fCy + Y2, fCx + X1, fCy + Y1, fCx, fCy, (fOutDia - fInDia) / 2, CW,x,y))
				return TRUE;
		else 
			if(CheckPointInMyArc(fCx + X2, fCy + Y2, fCx + X1, fCy + Y1, fCx, fCy, (fOutDia - fInDia) / 2, CCW,x,y))
				return TRUE;
	}
	return FALSE;
}
BOOL CheckPointInMyOctagon(double fCx, double fCy, double fwidth, double fheight, double fRadius,double x,double y)
{
	double  X1, Y1, X2, Y2, X3, Y3, X4, Y4;
	double fbufpt[16];
	fwidth = fwidth / 2;
	fheight = fheight / 2;

	X1 = fCx - fwidth;
	X2 = fCx - (fwidth - fRadius);
	X3 = fCx + (fwidth - fRadius);
	X4 = fCx + fwidth;

	Y1 = fCy - fheight;
	Y2 = fCy - (fheight - fRadius);
	Y3 = fCy + (fheight - fRadius);
	Y4 = fCy + fheight;


	fbufpt[0] = X3;
	fbufpt[1] = Y4;
	fbufpt[2] = X4;
	fbufpt[3] = Y3;
	fbufpt[4] = X4;
	fbufpt[5] = Y2;
	fbufpt[6] = X3;
	fbufpt[7] = Y1;
	fbufpt[8] = X2;
	fbufpt[9] = Y1;
	fbufpt[10] = X1;
	fbufpt[11] = Y2;
	fbufpt[12] = X1;
	fbufpt[13] = Y3;
	fbufpt[14] = X2;
	fbufpt[15] = Y4;
	return CheckPointInPolygon(fbufpt,8,x,y);
	
}
BOOL CheckPointInMyMoire(double fCx, double fCy, double fRingWidth, double fRingGap, int nNumRing, double fLineWidth, double fLineLength, double fLineAngle,double x,double y)
{
	DPOINT fVertex[4], pc;
	double fOutDia,fInDia;
	double R, cV, sV;
	int i;
	    
	R = (fRingGap + fRingWidth/2) * 2; 

	for (i=1 ; i <= nNumRing ; i++)
	{
		fInDia =  R * i - fRingWidth;
		fOutDia =  R * i + fRingWidth;
		if(CheckPointInMyDonut(fCx, fCy, fOutDia, fInDia,x,y))
			return TRUE;
	}

	R = fLineLength / 2;
	fVertex[0].x = fCx - R;
	fVertex[0].y = fCy;
	fVertex[1].x = fCx + R;
	fVertex[1].y = fCy;
	fVertex[2].x = fCx;
	fVertex[2].y = fCy - R;
	fVertex[3].x = fCx;
	fVertex[3].y = fCy + R;

	cV = cos(fLineAngle * DEG2RAD);
	sV = sin(fLineAngle * DEG2RAD);

	double fxVal,fYval;

	for (i=0 ; i<=3 ; i++)
	{
		fxVal=((fVertex[i].x - fCx) * cV) - ((fVertex[i].y - fCy) * sV) + fCx ;
		fYval=((fVertex[i].x - fCx) * sV) + ((fVertex[i].y - fCy) * cV) + fCy ;

		fVertex[i].x=fxVal;
		fVertex[i].y=fYval;
	}

	pc.x = fCx;
	pc.y = fCy;
	if(CheckPointInMyLineRound(fVertex[0].x, fVertex[0].y, fVertex[1].x, fVertex[1].y, fLineWidth,x,y))
		return TRUE;
	else if(CheckPointInMyLineRound(fVertex[2].x, fVertex[2].y, fVertex[3].x, fVertex[3].y, fLineWidth,x,y))
		return TRUE;
	else
		return FALSE;
	
}
BOOL CheckPointInMyOvalHalf(double fCx, double fCy, double fWidth, double fHeight,double x,double y)
{
 	fWidth = fWidth / 2;
	fHeight = fHeight / 2;
	if(CheckPointInArc(fCx + (fWidth - fHeight),fCy + fHeight, fCx + (fWidth - fHeight), fCy - fHeight, fCx + (fWidth - fHeight),fCy, CW,x,y))
	{
		return TRUE;
	}
	else if(CheckPointInQuad(fCx + (fWidth - fHeight), fCy - fHeight, fCx + (fWidth - fHeight),fCy + fHeight,fCx-fWidth, fCy+fHeight,fCx-fWidth, fCy-fHeight,x,y))
	{
		return TRUE;
	}
	else
		return FALSE;	
}
BOOL CheckPointInMyButterflySquare(double fCx, double fCy, double fWidth,double x,double y)
{
	double X1, Y1, X2, Y2, X3, Y3, X4, Y4;
	fWidth = fWidth / 2;

	X1=fCx-fWidth;
	Y1=fCy+fWidth;
	X2=fCx;
	Y2=fCy;

	X3=fCx;
	Y3=fCy;
	X4=fCx+fWidth;
	Y4=fCy-fWidth;


	if(CheckPointInMyRect(X1,Y1,X2,Y2,x,y))
		return TRUE;
	else
	{
		if(CheckPointInMyRect(X3,Y3,X4,Y4,x,y))
			return TRUE;
		else
			return FALSE;
	}
	
}
BOOL CheckPointInMyButterfly(double fCx, double fCy, double fWidth,double x,double y)
{
	int nSize=0;
	fWidth = fWidth / 2;

	if(CheckPointInArc(fCx - fWidth,fCy,fCx,fCy + fWidth,fCx,fCy,CW,x,y))
		return TRUE;
	else
	{
		if(CheckPointInArc(fCx,fCy - fWidth,fCx + fWidth, fCy,fCx,fCy,CCW,x,y))
			return TRUE;
		else
			return FALSE;
	}
}
BOOL CheckPointInMyHexagonVer(double fCx, double fCy, double fHexagonWidth, double fHexagonHeight, double fCornerSize,double x,double y)
{
    double X1, X2, X3, Y1, Y2, Y3, Y4;
  
	fHexagonWidth = fHexagonWidth / 2;
	fHexagonHeight = fHexagonHeight / 2;

	X1 = fCx - fHexagonWidth;
	X2 = fCx;
	X3 = fCx + fHexagonWidth;

	Y1 = fCy - fHexagonHeight;
	Y2 = fCy - (fHexagonHeight - fCornerSize);
	Y3 = fCy + (fHexagonHeight - fCornerSize);
	Y4 = fCy + fHexagonHeight;

	double bufpt[12];
	bufpt[0] = X2;
	bufpt[1] = Y4;
	bufpt[2] = X3;
	bufpt[3] = Y3;
	bufpt[4] = X3;
	bufpt[5] = Y2;
	bufpt[6] = X2;
	bufpt[7] = Y1;
	bufpt[8] = X1;
	bufpt[9] = Y2;
	bufpt[10] = X1;
	bufpt[11] = Y3;
	return CheckPointInPolygon(bufpt,6,x,y);
}
BOOL CheckPointInMyHexagonHor(double fCx, double fCy, double fHexagonWidth, double fHexagonHeight, double fCornerSize,double x,double y)
{
	double fWidth,fHeight;
    double X1, X2, X3, X4, Y1, Y2, Y3;

	fWidth = fHexagonWidth / 2.0;
	fHeight = fHexagonHeight / 2.0;

	X1 = fCx - fWidth;
	X2 = fCx - (fWidth - fCornerSize);
	X3 = fCx + (fWidth - fCornerSize);
	X4 = fCx + fWidth;

	Y1 = fCy - fHeight;
	Y2 = fCy;
	Y3 = fCy + fHeight;
	double bufpt[12];
	bufpt[0] = X3;
	bufpt[1] = Y3;
	bufpt[2] = X4;
	bufpt[3] = Y2;
	bufpt[4] = X3;
	bufpt[5] = Y1;
	bufpt[6] = X2;
	bufpt[7] = Y1;
	bufpt[8] = X1;
	bufpt[9] = Y2;
	bufpt[10] = X2;
	bufpt[11] = Y3;
	return CheckPointInPolygon(bufpt,6,x,y);
}
BOOL CheckPointInMyTriangle(double fCx, double fCy, double fTriangleBase, double fTriangleHeight,double x,double y)
{
	double fWidth,fHeight;

	fWidth = fTriangleBase / 2.0;
	fHeight = fTriangleHeight / 2.0;

	return CheckPointInTriangle(fCx - fWidth,fCy - fHeight,fCx + fWidth,fCy - fHeight,fCx,fCy + fHeight,x,y);	
}
BOOL CheckPointInMyDiamond(double fCx, double fCy, double fRectWidth, double ffRectHeight,double x,double y)
{
	double fWidth,fHeight;
	
	fWidth = fRectWidth / 2.0;
	fHeight = ffRectHeight / 2.0;

	return CheckPointInQuad(fCx,fCy + fHeight,fCx + fWidth,fCy,fCx,fCy - fHeight,fCx - fWidth,fCy,x,y);
	
}
BOOL CheckPointInMyDonutSquare(double fCx, double fCy, double fDmo, double fDmi,double x,double y)
{
	double foD, fiD;
	CdPoint gLpoint[8];

	foD = fDmo / 2;
    fiD = fDmi / 2;

	gLpoint[0].x=(fCx - foD);
	gLpoint[0].y=(fCy + foD);
	gLpoint[1].x=(fCx + foD);
	gLpoint[1].y=(fCy + foD);
	gLpoint[2].x=(fCx + foD);
	gLpoint[2].y=(fCy - foD);
	gLpoint[3].x=(fCx - foD);
	gLpoint[3].y=(fCy - foD);

	gLpoint[4].x=(fCx - fiD);
	gLpoint[4].y=(fCy + fiD);
	gLpoint[5].x=(fCx + fiD);
	gLpoint[5].y=(fCy + fiD);
	gLpoint[6].x=(fCx + fiD);
	gLpoint[6].y=(fCy - fiD);
	gLpoint[7].x=(fCx - fiD);
	gLpoint[7].y=(fCy - fiD);
	
	if(CheckPointInQuad(gLpoint[0].x,gLpoint[0].y,gLpoint[1].x,gLpoint[1].y,gLpoint[5].x,gLpoint[5].y,gLpoint[4].x,gLpoint[4].y,x,y))
		return TRUE;
	else if(CheckPointInQuad(gLpoint[7].x,gLpoint[7].y,gLpoint[6].x,gLpoint[6].y,gLpoint[2].x,gLpoint[2].y,gLpoint[3].x,gLpoint[3].y,x,y))
		return TRUE;
	else if(CheckPointInQuad(gLpoint[1].x,gLpoint[1].y,gLpoint[2].x,gLpoint[2].y,gLpoint[6].x,gLpoint[6].y,gLpoint[5].x,gLpoint[5].y,x,y))
		return TRUE;
	else if(CheckPointInQuad(gLpoint[0].x,gLpoint[0].y,gLpoint[4].x,gLpoint[4].y,gLpoint[7].x,gLpoint[7].y,gLpoint[3].x,gLpoint[3].y,x,y))
		return TRUE;
	else 
		return FALSE;	
}
BOOL CheckPointInMyEllipse(double fCx, double fCy, double fWidth, double fHeight,double x,double y)
{
	fWidth = fWidth / 2;
    fHeight = fHeight / 2;
 	
	if(((x-fCx)/fWidth)*((x-fCx)/fWidth) + ((y-fCy)/fHeight)*((y-fCy)/fHeight) <=1 )
		return TRUE;
	else
		return FALSE;	
}
BOOL CheckPointInMyCircle(double fOX, double fOY, double R, UINT nSeg,double x,double y)
{
	return CheckPointInCircle(fOX,fOY,R,x,y);
}
BOOL CheckPointInMyDonut(double fCx, double fCy, double fDmo, double fDmi,double x,double y)
{ 
	double distance = GetDistance(CdPoint(fCx,fCy),CdPoint(x,y));
	if(distance<=fDmo/2.0 && distance>=fDmi/2)
		return TRUE;
	else 
		return FALSE;	
}

BOOL CheckPointInMyArc(double fSx, double fSy, double fEx, double fEy, double fCX, double fCY, double fWidth, int nDir,double x,double y)
{
	CdPoint fptStart=CdPoint(fSx,fSy);
	CdPoint fptEnd=CdPoint(fEx,fEy);
	CdPoint fptCenter=CdPoint(fCX,fCY);
	CdPoint fbuf;
	double fAnglebuf;
	double fLineAngle1, fLineAngle2,fLineAngle3;

	double fdifferx = fptStart.x-fptCenter.x;
	double fdiffery = fptStart.y-fptCenter.y;

	double fCenterRadius = (fptStart.x-fptCenter.x)*(fptStart.x-fptCenter.x) +(fptStart.y-fptCenter.y)*(fptStart.y-fptCenter.y);
	fCenterRadius = sqrt(fCenterRadius);
	double fSmallArcRadius = fWidth/2.0;
	double fMinimumRadius = fCenterRadius-fSmallArcRadius;
	double fMaximumRadius = fCenterRadius+fSmallArcRadius;
	
	if(fSx == fEx && fSy == fEy && (fSx != fCX || fSy != fCY))
	{
		double fRadius = sqrt((fSx-fCX)*(fSx-fCX) + (fSy-fCY)*(fSy-fCY)) * 2;
		return CheckPointInMyDonut(fCX, fCY, fRadius + fWidth, fRadius - fWidth,x,y);
	}

	if(fdifferx==0)
	{
		if(fdiffery>0)
			fLineAngle1 = PI/2;	
		else
			fLineAngle1 = -PI/2;
	}
	else
		fLineAngle1 = atan2(fdiffery,fdifferx);

	fdifferx = fptEnd.x-fptCenter.x;
	fdiffery = fptEnd.y-fptCenter.y;
	if(fdifferx==0)
	{
		if(fdiffery>0)
			fLineAngle2 = PI/2;	
		else
			fLineAngle2 = -PI/2;
	}
	else
		fLineAngle2 = atan2(fdiffery,fdifferx);

	fdifferx = x-fptCenter.x;
	fdiffery = y-fptCenter.y;
	if(fdifferx==0)
	{
		if(fdiffery>0)
			fLineAngle3 = PI/2;	
		else
			fLineAngle3 = -PI/2;
	}
	else
		fLineAngle3 = atan2(fdiffery,fdifferx);
	

	if(nDir==CW)
	{
		fbuf = fptStart;
		fptStart = fptEnd;
		fptEnd = fbuf;

		fAnglebuf = fLineAngle1;
		fLineAngle1 = fLineAngle2;
		fLineAngle2 = fAnglebuf;
	}
	double distance = GetDistance(CdPoint(x,y),CdPoint(fCX, fCY));
	if(fLineAngle1>fLineAngle2)
	{
		if(fLineAngle3>=fLineAngle1 || fLineAngle3<= fLineAngle2)
		{
			if( distance >= fMinimumRadius && fMaximumRadius >= distance)
			{
				return TRUE;
			}
			else
				return FALSE;
		}
	}
	else
	{
		if(fLineAngle3>=fLineAngle1 && fLineAngle3<= fLineAngle2)
		{
			if( distance >= fMinimumRadius && fMaximumRadius >= distance)
			{
				return TRUE;
			}
			else
				return FALSE;
		}
	}
	
	if(fLineAngle2<PI && fLineAngle1<PI)
	{
		if(CheckPointInArc(fptEnd.x,fptEnd.y,fSmallArcRadius,fLineAngle2,fLineAngle2+PI,x,y))
			return TRUE;
		else
		{
			if(CheckPointInArc(fptStart.x,fptStart.y,fSmallArcRadius,fLineAngle1+PI,fLineAngle1,x,y))
				return TRUE;
			else
				return FALSE;
		}	
	}
	else if(fLineAngle2<PI && fLineAngle1>=PI)
	{
		if(CheckPointInArc(fptEnd.x,fptEnd.y,fSmallArcRadius,fLineAngle2,fLineAngle2+PI,x,y))
			return TRUE;
		else
		{
			if(CheckPointInArc(fptStart.x,fptStart.y,fSmallArcRadius,fLineAngle1-PI,fLineAngle1,x,y))
				return TRUE;
			else
				return FALSE;
		}
	}
	else
	{
		if(CheckPointInArc(fptEnd.x,fptEnd.y,fSmallArcRadius,fLineAngle2,fLineAngle2-PI,x,y))
			return TRUE;
		else
		{
			if(CheckPointInArc(fptStart.x,fptStart.y,fSmallArcRadius,fLineAngle1-PI,fLineAngle1,x,y))
				return TRUE;
			else
				return FALSE;
		}
	}
}
BOOL CheckPointInMyRectChamfferd(double fCx, double fCy, double fWidth, double fHeight, double fRadius, int nCorners,double x,double y)
{
	CString cc;
	int n=0;
	double fCoord[20];

    fWidth = fWidth / 2;
    fHeight = fHeight / 2;
    
	
	cc.Format(_T("%d"), nCorners);

	if(cc.Find(_T("1"), 0)>-1)
	{
		fCoord[0] = fCx + fWidth;
		fCoord[1] = fCy + (fHeight - fRadius);
		fCoord[2] = fCx + (fWidth - fRadius);
		fCoord[3] = fCy + fHeight;
		n = 2;
	}
	else
	{
		fCoord[0] = fCx + fWidth;
		fCoord[1] = fCy + fHeight;
		n = 1;
	}

	if(cc.Find(_T("2"), 0)>-1)
	{
		fCoord[2*n] = fCx - (fWidth - fRadius);
		fCoord[2*n+1] = fCy + fHeight;
		n++;
		fCoord[2*n] = fCx - fWidth;
		fCoord[2*n+1] = fCy + (fHeight - fRadius);
		n++;
	}
	else
	{
		fCoord[2*n] = fCx - fWidth;
		fCoord[2*n+1] = fCy + fHeight;
		n++;
	}

	if(cc.Find(_T("3"), 0)>-1)
	{
		fCoord[2*n] = fCx - fWidth;
		fCoord[2*n+1] = fCy - (fHeight - fRadius);
		n++;
		fCoord[2*n] = fCx - (fWidth - fRadius);
		fCoord[2*n+1] = fCy - fHeight;
		n++;
	}
	else
	{
		fCoord[2*n] = fCx - fWidth;
		fCoord[2*n+1] = fCy - fHeight;
		n++;
	}

	if(cc.Find(_T("4"), 0)>-1)
	{
		fCoord[2*n] = fCx + (fWidth - fRadius);
		fCoord[2*n+1] = fCy - fHeight;
		n++;
		fCoord[2*n] = fCx + fWidth;
		fCoord[2*n+1] = fCy - (fHeight - fRadius);
		n++;
	}
	else
	{
		fCoord[2*n] = fCx + fWidth;
		fCoord[2*n+1] = fCy - fHeight;
		n++;
	}

	fCoord[2*n] = fCoord[0];
	fCoord[2*n+1] = fCoord[1];
	n++;
	return CheckPointInPolygon(fCoord,n,x,y);
}

BOOL CheckPointInMyRectRound(double fCx, double fCy, double fWidth, double fHeight, double fRadius, int nCorners,double x,double y)
{
	double X1, Y1, X2, Y2, cX, cY;
	CString cc;
	DPOINT fPt;
	vector <DPOINT> vecCoord;
	vecCoord.clear();
	BOOL bFind = FALSE;
    fWidth = fWidth / 2;
    fHeight = fHeight / 2;

  
	cc.Format(_T("%d"), nCorners);

	if(cc.Find(_T("1"), 0)>-1)
	{
		X1 = fCx + fWidth;
		Y1 = fCy + (fHeight - fRadius);
		X2 = fCx + (fWidth - fRadius);
		Y2 = fCy + fHeight;
		cX = fCx + (fWidth - fRadius);
		cY = fCy + (fHeight - fRadius);

		
		if(CheckPointInArc(X1, Y1, X2, Y2, cX, cY,CCW,x,y))
			return TRUE;
	}
	else
	{		
		if(x<= fCx + fWidth && x>= fCx + fWidth- fRadius && y<= fCy + fHeight && y>= fCy + fHeight- fRadius)
			return TRUE;
	}

	if(cc.Find(_T("2"), 0)>-1)
	{
		X1 = fCx - (fWidth - fRadius);
		Y1 = fCy + fHeight;
		X2 = fCx - fWidth;
		Y2 = fCy + (fHeight - fRadius);
		cX = fCx - (fWidth - fRadius);
		cY = fCy + (fHeight - fRadius);

		if(CheckPointInArc(X1, Y1, X2, Y2, cX, cY,CCW,x,y))
			return TRUE;
	}
	else
	{
		if(x>= fCx - fWidth && x<= fCx - fWidth + fRadius && y<= fCy + fHeight && y>= fCy + fHeight- fRadius)
			return TRUE;
	}

	if(cc.Find(_T("3"), 0)>-1)
	{
		X1 = fCx - fWidth;
		Y1 = fCy - (fHeight - fRadius);
		X2 = fCx - (fWidth - fRadius);
		Y2 = fCy - fHeight;
		cX = fCx - (fWidth - fRadius);
		cY = fCy - (fHeight - fRadius);

		if(CheckPointInArc(X1, Y1, X2, Y2, cX, cY,CCW,x,y))
			return TRUE;
	}
	else
	{
		if(x>= fCx - fWidth && x<= fCx - fWidth + fRadius && y>= fCy - fHeight && y<= fCy - fHeight+ fRadius)
			return TRUE;
	}

	if(cc.Find(_T("4"), 0)>-1)
	{
		X1 = fCx + (fWidth - fRadius);
		Y1 = fCy - fHeight;
		X2 = fCx + fWidth;
		Y2 = fCy - (fHeight - fRadius);
		cX = fCx + (fWidth - fRadius);
		cY = fCy - (fHeight - fRadius);

		if(CheckPointInArc(X1, Y1, X2, Y2, cX, cY,CCW,x,y))
			return TRUE;
	}
	else
	{
		if(x<= fCx + fWidth && x>= fCx + fWidth- fRadius  && y>= fCy - fHeight && y<= fCy - fHeight+ fRadius)
			return TRUE;
	}
	fPt.x = fCx +fWidth -fRadius;
	fPt.y = fCy +fHeight;
	vecCoord.push_back(fPt);
	fPt.x = fCx -fWidth +fRadius;
	fPt.y = fCy +fHeight;
	vecCoord.push_back(fPt);
	fPt.x = fCx -fWidth +fRadius;
	fPt.y = fCy +fHeight-fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx -fWidth;
	fPt.y = fCy +fHeight-fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx -fWidth;
	fPt.y = fCy -fHeight+fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx -fWidth+fRadius;
	fPt.y = fCy -fHeight+fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx -fWidth+fRadius;
	fPt.y = fCy -fHeight;
	vecCoord.push_back(fPt);
	fPt.x = fCx +fWidth-fRadius;
	fPt.y = fCy -fHeight;
	vecCoord.push_back(fPt);
	fPt.x = fCx +fWidth-fRadius;
	fPt.y = fCy -fHeight+fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx +fWidth;
	fPt.y = fCy -fHeight+fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx +fWidth;
	fPt.y = fCy +fHeight-fRadius;
	vecCoord.push_back(fPt);
	fPt.x = fCx +fWidth- fRadius;
	fPt.y = fCy +fHeight-fRadius;
	vecCoord.push_back(fPt);
	return CheckPointInPolygon(&vecCoord[0],(int)vecCoord.size(),x,y);
}
BOOL CheckPointInMyRectCenter(double fSx, double fSy, double fLineWidth, double fLineHeight, double fAngle,double x,double y)
{
	double cV, sV, X1, Y1, X2, Y2;

	GLfloat LineWidth;

	LineWidth=fLineWidth;

    fLineWidth = fLineWidth / 2;
    fLineHeight = fLineHeight / 2;
	
    if (fAngle != 0)
	{
        cV = cos(fAngle * DEG2RAD);
        sV = sin(fAngle * DEG2RAD);
        X1 = (fSx - fLineWidth * cV);
        Y1 = (fSy - fLineWidth * sV);
        X2 = (fSx + fLineWidth * cV);
        Y2 = (fSy + fLineWidth * sV);
        cV = fLineHeight * cV;
        sV = fLineHeight * sV;
	}
	if(fAngle != 0)
	{
		return CheckPointInQuad((X1 - sV),(Y1 + cV),(X1 + sV),(Y1 - cV),(X2 + sV),(Y2 - cV),(X2 - sV),(Y2 + cV),x,y);
	}
	else
	{
		return CheckPointInQuad((fSx - fLineWidth),(fSy - fLineHeight),(fSx - fLineWidth),(fSy + fLineHeight),(fSx + fLineWidth),(fSy + fLineHeight),(fSx + fLineWidth),(fSy - fLineHeight),x,y);
	}	
}
BOOL CheckPointInMyRect(double fSx, double fSy, double fEx, double fEy,double x,double y)
{
	return CheckPointInQuad(fSx,fSy,fSx,fEy,fEx,fEy,fEx,fSy,x,y);
}
BOOL CheckPointInMyRect(double fSx, double fSy, double fLineWidth, double fLineHeight, double fAngle,double x,double y)
{
    DPOINT cp;
	DPOINT pp[4];
	double XX, YY, cV, sV;

    if (fAngle)
	{
        cV = cos(fAngle * DEG2RAD);
        sV = sin(fAngle * DEG2RAD);
        
        cp.x = fSx + fLineWidth / 2;
        cp.y = fSy + fLineHeight / 2;
    
        XX = -fLineWidth / 2;
        YY = -fLineHeight / 2;
        pp[0].x = (XX * cV) - (YY * sV) + cp.x;
        pp[0].y = (XX * sV) + (YY * cV) + cp.y;
//        '우하
        XX = fLineWidth / 2;
        YY = -fLineHeight / 2;
        pp[1].x = (XX * cV) - (YY * sV) + cp.x;
        pp[1].y = (XX * sV) + (YY * cV) + cp.y;
//        '우상
        XX = fLineWidth / 2;
        YY = fLineHeight / 2;
        pp[2].x = (XX * cV) - (YY * sV) + cp.x;
        pp[2].y = (XX * sV) + (YY * cV) + cp.y;
//        '좌상
        XX = -fLineWidth / 2;
        YY = fLineHeight / 2;
        pp[3].x = (XX * cV) - (YY * sV) + cp.x;
        pp[3].y = (XX * sV) + (YY * cV) + cp.y;
        
	}
    else
	{
        pp[0].x = fSx;           
        pp[0].y = fSy;           
        pp[1].x = fSx + fLineWidth;       
        pp[1].y = fSy;           
        
        pp[2].x = fSx + fLineWidth;       
        pp[2].y = fSy + fLineHeight;       
        pp[3].x = fSx;           
        pp[3].y = fSy + fLineHeight;       
    }

	return CheckPointInQuad(pp[0].x,pp[0].y,pp[1].x,pp[1].y,pp[2].x,pp[2].y,pp[3].x,pp[3].y,x,y);
}
BOOL CheckPointInMyLineRect(double fSx, double fSy, double fEx, double fEy, double fLineWidth, double fLineHeight,double x,double y)
{
	double ww, hh, a, b, a1, b1, a2, b2;
	vector<DPOINT> vecpt;
	DPOINT pp;
	vecpt.clear();
	ww = fLineWidth / 2;
	hh = fLineHeight / 2;

	if (fSx != fEx && fSy != fEy)
	{   
		if (fEx > fSx)
		{
			if (fEy > fSy)
			{
				pp.x = (fSx - ww);
				pp.y = (fSy - hh);
				vecpt.push_back(pp);
				pp.x = (fSx - ww);
				pp.y = (fSy + hh);
				vecpt.push_back(pp);
				pp.x = (fEx - ww);
				pp.y = (fEy + hh);
				vecpt.push_back(pp);
				pp.x = (fEx + ww);
				pp.y = (fEy + hh);
				vecpt.push_back(pp);
				pp.x = (fEx + ww);
				pp.y = (fEy - hh);
				vecpt.push_back(pp);
				pp.x = (fSx + ww);
				pp.y = (fSy - hh);
				vecpt.push_back(pp);
			}
			else
			{
				pp.x = (fSx - ww);
				pp.y = (fSy - hh);
				vecpt.push_back(pp);
				pp.x = (fSx - ww);
				pp.y = (fSy + hh);
				vecpt.push_back(pp);
				pp.x = (fSx + ww);
				pp.y = (fSy + hh);
				vecpt.push_back(pp);
				pp.x = (fEx + ww);
				pp.y = (fEy + hh);
				vecpt.push_back(pp);
				pp.x = (fEx + ww);
				pp.y = (fEy - hh);
				vecpt.push_back(pp);
				pp.x = (fEx - ww);
				pp.y = (fEy - hh);
				vecpt.push_back(pp);
			}
		}
		else
		{
			a1 = fEx;
			a2 = fSx;
			b1 = fEy;
			b2 = fSy;
			if (b2 > b1)
			{
				pp.x = (a1 - ww);
				pp.y = (b1 - hh);
				vecpt.push_back(pp);
				pp.x = (a1 - ww);
				pp.y = (b1 + hh);
				vecpt.push_back(pp);
				pp.x = (a2 - ww);
				pp.y = (b2 + hh);
				vecpt.push_back(pp);
				pp.x = (a2 + ww);
				pp.y = (b2 + hh);
				vecpt.push_back(pp);
				pp.x = (a2 + ww);
				pp.y = (b2 - hh);
				vecpt.push_back(pp);
				pp.x = (a1 + ww);
				pp.y = (b1 - hh);
				vecpt.push_back(pp);
			}
			else
			{
				pp.x = (a1 - ww);
				pp.y = (b1 - hh);
				vecpt.push_back(pp);
				pp.x = (a1 - ww);
				pp.y = (b1 + hh);
				vecpt.push_back(pp);
				pp.x = (a1 + ww);
				pp.y = (b1 + hh);
				vecpt.push_back(pp);
				pp.x = (a2 + ww);
				pp.y = (b2 + hh);
				vecpt.push_back(pp);
				pp.x = (a2 + ww);
				pp.y = (b2 - hh);
				vecpt.push_back(pp);
				pp.x = (a2 - ww);
				pp.y = (b2 - hh);
				vecpt.push_back(pp);
			}
		}
		
		return CheckPointInPolygon(&vecpt[0],(int)vecpt.size(),x,y);
	}

	if (fSx == fEx && fSy == fEy)
	{
		pp.x = (fSx - ww);     //  '좌하
		pp.y = (fSy - hh);     //
		vecpt.push_back(pp);
		pp.x = (fSx + ww);     //  '우하
		pp.y = (fSy - hh);
		vecpt.push_back(pp);

		pp.x = (fEx + ww);     //  '우상
		pp.y = (fEy + hh);     //
		vecpt.push_back(pp);
		pp.x = (fEx - ww);     //  '좌상
		pp.y = (fEy + hh);     //
		vecpt.push_back(pp);
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
		pp.x = (fSx - ww);     //  '좌하
		pp.y = (a - hh);      //
		vecpt.push_back(pp);
		pp.x = (fSx + ww);     //  '우하
		pp.y = (a - hh);      //
		vecpt.push_back(pp);
		pp.x = (fEx + ww);     //  '우상
		pp.y = (b + hh);      //
		vecpt.push_back(pp);
		pp.x = (fEx - ww);    //   '좌상
		pp.y = (b + hh);     // 
		vecpt.push_back(pp);
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
		pp.x = (a - ww);      //  '좌하
		pp.y = (fSy - hh);     //
		vecpt.push_back(pp);
		pp.x = (b + ww);      //  '우하
		pp.y = (fSy - hh);    // 
		vecpt.push_back(pp);

		pp.x = (b + ww);      //  '우상
		pp.y = (fEy + hh);     //
		vecpt.push_back(pp);
		pp.x = (a - ww);     //   '좌상
		pp.y = (fEy + hh);    // 
		vecpt.push_back(pp);
	}
	return CheckPointInQuad(vecpt[0].x,vecpt[0].y,vecpt[1].x,vecpt[1].y,vecpt[2].x,vecpt[2].y,vecpt[3].x,vecpt[3].y,x,y);
	
}
BOOL CheckPointInMyLineSquare(double fSx, double fSy, double fEx, double fEy, double fLineWidth,double x,double y)
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
		XX1 = fSx - R * cV;
		YY1 = fSy - R * sV;
		XX2 = fEx + R * cV;
		YY2 = fEy + R * sV;
    
		cV = R * ww / d;
		sV = R * hh / d;
    
		pp[0].x =XX1 + sV;     
		pp[0].y = YY1 - cV;    
		pp[1].x =XX2 + sV;    
		pp[1].y =YY2 - cV;  
		pp[2].x =XX2 - sV;    
		pp[2].y =YY2 + cV;    
		pp[3].x = pp[0].x - pp[1].x + pp[2].x;
		pp[3].y = pp[0].y - pp[1].y + pp[2].y;
		pp[3].x =XX1 - sV;  
		pp[3].y =YY1 + cV;  
		return CheckPointInQuad(pp[0].x,pp[0].y,pp[1].x,pp[1].y,pp[2].x,pp[2].y,pp[3].x,pp[3].y,x,y);
	}
	else
	{
		fLineWidth = fLineWidth / 2;
		pp[0].x = fSx - fLineWidth;     
		pp[0].y = fSy - fLineWidth;    
		pp[1].x = fSx - fLineWidth;    
		pp[1].y = fSy + fLineWidth;  
		pp[2].x = fSx + fLineWidth;    
		pp[2].y = fSy + fLineWidth;    
		pp[3].x = fSx + fLineWidth;
		pp[3].y = fSy - fLineWidth;

		return CheckPointInQuad(pp[0].x,pp[0].y,pp[1].x,pp[1].y,pp[2].x,pp[2].y,pp[3].x,pp[3].y,x,y);
	}
}

BOOL CheckPointInMyLineRound(double fSx, double fSy, double fEx, double fEy, double fLineWidth,double x,double y)
{
	double fRadius = fLineWidth/2.0;
 	GLfloat fArcLenth = PI * fRadius;
	CdPoint fbuf;
	CdPoint fStart,fEnd;
	double fLineAngle;
	DPOINT fp1,fp2,fp3,fp4;
	fStart=CdPoint(fEx,fEy);
	fEnd=CdPoint(fSx,fSy);
	if(fStart.x>fEnd.x)
	{
		fbuf = fStart;
		fStart = fEnd;
		fEnd = fbuf;
	}
		
	double fdifferx = fEnd.x-fStart.x;
	double fdiffery = fEnd.y-fStart.y;
	if(fdifferx==0)
	{
		fLineAngle = PI/2;
		if(fStart.y>fEnd.y)
		{
			fbuf = fStart;
			fStart = fEnd;
			fEnd = fbuf;
		}		
	}
	else
	{
		fLineAngle = atan2(fdiffery,fdifferx);
		if(fLineAngle<0)
		{
			fLineAngle += 2.0*PI;
		}
	}
	fp1.x = fEnd.x+ fRadius*cos(fLineAngle-PI/2.0);
	fp1.y = fEnd.y+ fRadius*sin(fLineAngle-PI/2.0);
	fp2.x = fEnd.x+ fRadius*cos(fLineAngle+PI/2.0);
	fp2.y = fEnd.y+ fRadius*sin(fLineAngle+PI/2.0);
	fp3.x = fStart.x+ fRadius*cos(fLineAngle+PI/2.0);
	fp3.y = fStart.y+ fRadius*sin(fLineAngle+PI/2.0);
	fp4.x = fStart.x+ fRadius*cos(fLineAngle-PI/2.0);
	fp4.y = fStart.y+ fRadius*sin(fLineAngle-PI/2.0);
	
	if(CheckPointInQuad(fp1.x,fp1.y,fp2.x,fp2.y,fp3.x,fp3.y,fp4.x,fp4.y,x,y))
		return TRUE;
	else
	{
		if(CheckPointInArc(fEnd.x,fEnd.y,fRadius,fLineAngle-PI/2.0,fLineAngle+PI/2.0,x,y))
			return TRUE;
		else
		{
			if(CheckPointInArc(fStart.x,fStart.y,fRadius,fLineAngle+PI/2.0,fLineAngle-PI/2.0,x,y))
				return TRUE;
			else
				return FALSE;
		}
	}
}

BOOL CheckPointInMyLine(double fSx, double fSy, double fEx, double fEy, double fLineWidth,double x,double y)
{
    double fLength, fHeight, fWidth, fTx, fTy;
	DPOINT fp1,fp2,fp3,fp4;
    fLength = sqrt((fEx - fSx) * (fEx - fSx) + (fEy - fSy) * (fEy - fSy));    
	if (fLength < 0.000001)
	{
		fp1.x =fSx - fLineWidth / 2.0;
		fp1.y =fSy - fLineWidth / 2.0;
		fp2.x =fSx - fLineWidth / 2.0;
		fp2.y =fSy + fLineWidth / 2.0;
		fp3.x =fSx + fLineWidth / 2.0;
		fp3.y =fSy + fLineWidth / 2.0;
		fp4.x =fSx + fLineWidth / 2.0;
		fp4.y =fSy - fLineWidth / 2.0;
	}    
	else
	{
		fHeight = fEy - fSy;
		fWidth = fEx - fSx;

		fTy = fLineWidth / 2.0 * fWidth / fLength;
		fTx = fLineWidth / 2.0 * fHeight / fLength;
        
		fp1.x =fSx + fTx;
		fp1.y =fSy - fTy;
		fp2.x =fEx + fTx;
		fp2.y =fEy - fTy;
		fp3.x =fEx - fTx;
		fp3.y =fEy + fTy;
		fp4.x =fSx - fTx;
		fp4.y =fSy + fTy;
	}
	return CheckPointInQuad(fp1.x,fp1.y,fp2.x,fp2.y,fp3.x,fp3.y,fp4.x,fp4.y,x,y);
}
BOOL CheckPointInArc(double fSx, double fSy, double fEx, double fEy, double fCx, double fCy, int nDir,double x,double y)
{
	double fRadDiffer;
	double fLineAngle1, fLineAngle2;
	double fdifferx,fdiffery;
	double fbuf , fAnglebuf;
	double fRadius;

	fdifferx = fSx-fCx;
	fdiffery = fSy-fCy;
	fRadius = sqrt(fdifferx*fdifferx+fdiffery*fdiffery);
	if(fdifferx==0)
	{
		if(fdiffery>0)
			fLineAngle1 = PI/2;	
		else
			fLineAngle1 = -PI/2;
	}
	else
		fLineAngle1 = atan2(fdiffery,fdifferx);
	if(fLineAngle1<0)
		fLineAngle1 += 2*PI;

	fdifferx = fEx-fCx;
	fdiffery = fEy-fCy;
	if(fdifferx==0)
	{
		if(fdiffery>0)
			fLineAngle2 = PI/2;	
		else
			fLineAngle2 = -PI/2;
	}
	else
		fLineAngle2 = atan2(fdiffery,fdifferx);

	if(fLineAngle2<0)
		fLineAngle2 += 2*PI;
	if(nDir==CW)
	{
		fbuf = fSx;
		fSx = fEx;
		fEx = fbuf;
		fbuf = fSy;
		fSy = fEy;
		fEy = fbuf;
		fAnglebuf = fLineAngle1;
		fLineAngle1 = fLineAngle2;
		fLineAngle2 = fAnglebuf;
	}
	if(fLineAngle1>fLineAngle2)
		fRadDiffer = (2*PI-fLineAngle1)+fLineAngle2;
	else
		fRadDiffer = fLineAngle2-fLineAngle1;

	return CheckPointInArc(fCx,fCy,fRadius,fLineAngle1,fLineAngle1+fRadDiffer,x,y);
}
BOOL CheckPointInArc(double cx,double cy,double radius,double startAngle,double arcAngle,int nDir,double x,double y)
{
	double angleRad;
	angleRad = atan2(y-cy,x-cx);
	if(angleRad<0)
		angleRad+=2.0*PI;
	if(nDir == CCW)
	{
		if(startAngle+arcAngle<=2*PI)
		{

			if(startAngle<= angleRad && startAngle+arcAngle>= angleRad)
			{
				if(CheckPointInCircle(cx,cy,radius,x,y))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			if(startAngle <= angleRad || startAngle+arcAngle-2*PI >= angleRad)
			{
				if(CheckPointInCircle(cx,cy,radius,x,y))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				return FALSE;
			}
		}
	}
	else
	{
		if(startAngle-arcAngle >= 0)
		{

			if(startAngle-arcAngle<= angleRad && startAngle>= angleRad)
			{
				if(CheckPointInCircle(cx,cy,radius,x,y))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			if(startAngle-arcAngle+2*PI <= angleRad || startAngle >= angleRad)
			{
				if(CheckPointInCircle(cx,cy,radius,x,y))
					return TRUE;
				else
					return FALSE;
			}
			else
			{
				return FALSE;
			}
		}
	}
}
BOOL CheckPointInArc(double cx,double cy,double radius,double startAngle,double endAngle,double x,double y)
{
	if(startAngle<0)
		startAngle += 2.0*PI;
	if(startAngle>2.0*PI)
		startAngle -= 2.0*PI;
	if(endAngle<0)
		endAngle += 2.0*PI;
	if(endAngle>2.0*PI)
		endAngle -= 2.0*PI;
	double angleRad;
	angleRad = atan2(y-cy,x-cx);
	if(angleRad<0)
		angleRad+=2.0*PI;	
	if(startAngle<=endAngle)
	{
		if(startAngle<= angleRad && endAngle>= angleRad)
		{
			if(CheckPointInCircle(cx,cy,radius,x,y))
				return TRUE;
			else
				return FALSE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if(startAngle <= angleRad || endAngle >= angleRad)
		{
			if(CheckPointInCircle(cx,cy,radius,x,y))
				return TRUE;
			else
				return FALSE;
		}
		else
		{
			return FALSE;
		}
	}
}
BOOL CheckPointInCircle(double cx, double cy, double radius, double x, double y)
{
	if(radius>=GetDistance(CdPoint(cx,cy),CdPoint(x,y)))
		return TRUE;
		return FALSE;
}
BOOL CheckPointInCircle(const DPOINT &cp, const double radius, double x, double y)
{
	if (sqrt(pow(cp.x - x, 2) + pow(cp.y - y, 2)) <= radius)
		return TRUE;

	return FALSE;
}
BOOL CheckPointInCircle(const DPOINT &cp, const double radius, const DPOINT &pt)
{
	if (sqrt(pow(cp.x - pt.x, 2) + pow(cp.y - pt.y, 2)) <= radius)
		return TRUE;

	return FALSE;
}
BOOL CheckPointInEllipse(double cx, double cy, double fWidth, double fHeight,double x,double y)
{
	fWidth = fWidth / 2;
	fHeight = fHeight / 2;

	if(((x-cx)/fWidth)*((x-cx)/fWidth) + ((y-cy)/fHeight)*((y-cy)/fHeight) <=1 )
		return TRUE;
	else
		return FALSE;	
}
BOOL CheckPointInTriangle(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y)
{
	double angle_123;
	double angle_12x;
	double angle_234;
	double angle_23x;
	double angle_341;
	double angle_34x;
	BOOL inside;

	// This will only handle convex quadrilaterals.
	inside = FALSE;

	angle_12x = GetInteriorAngle( x1, y1, x2, y2, x, y );
	angle_123 = GetInteriorAngle( x1, y1, x2, y2, x3, y3);

	if ( angle_12x > angle_123 )
		return FALSE;

	angle_23x = GetInteriorAngle( x2, y2, x3, y3, x, y );
	angle_234 = GetInteriorAngle( x2, y2, x3, y3, x1, y1 );

	if ( angle_23x > angle_234 )
		return FALSE;

	angle_34x = GetInteriorAngle( x3, y3, x1, y1, x, y );
	angle_341 = GetInteriorAngle( x3, y3, x1, y1, x2, y2 );

	if ( angle_34x > angle_341 )
		return FALSE;
	return TRUE;
}

BOOL CheckLineInRect(DRECT *fRect, DPOINT fptStart, DPOINT fptEnd, DPOINT fptStart1, DPOINT fptEnd1)
{
	return FALSE;
}

BOOL CheckPointInQuad(DQUAD fptQuad, double x, double y)
{
	return CheckPointInQuad(fptQuad.leftbottom.x, fptQuad.leftbottom.y, fptQuad.rightbottom.x, fptQuad.rightbottom.y, fptQuad.righttop.x, fptQuad.righttop.y,
		fptQuad.lefttop.x, fptQuad.lefttop.y, x, y);
}
//******************************************************************************
// CheckPointInQuadrilateral finds if a point is inside a convex quadrilateral in 2D.
// Modified:
// 06 February 1999
// Author:
// John Burkardt
// Parameters:
// Input, real X1, Y1, X2, Y2, X3, Y3, X4, Y4, the X and Y coordinates of the quadrilateral.
// Input, real X, Y, the point to be checked.
// Output, TRUE if ( X,Y) is inside the quadrilateral or on its boundary, and FALSE otherwise.
BOOL CheckPointInQuad(
		double x1,double y1,double x2,double y2,double x3,double y3,
		double x4,double y4,double x,double y)
{
	double angle_123;
	double angle_12x;
	double angle_234;
	double angle_23x;
	double angle_341;
	double angle_34x;
	double angle_412;
	double angle_41x;
	BOOL inside;

	// This will only handle convex quadrilaterals.
	inside = FALSE;

	angle_12x = GetInteriorAngle( x1, y1, x2, y2, x, y );
	angle_123 = GetInteriorAngle( x1, y1, x2, y2, x3, y3);

	if ( angle_12x > angle_123 )
		return FALSE;

	angle_23x = GetInteriorAngle( x2, y2, x3, y3, x, y );
	angle_234 = GetInteriorAngle( x2, y2, x3, y3, x4, y4 );

	if ( angle_23x > angle_234 )
		return FALSE;

	angle_34x = GetInteriorAngle( x3, y3, x4, y4, x, y );
	angle_341 = GetInteriorAngle( x3, y3, x4, y4, x1, y1 );

	if ( angle_34x > angle_341 )
		return FALSE;

	angle_41x = GetInteriorAngle( x4, y4, x1, y1, x, y );
	angle_412 = GetInteriorAngle( x4, y4, x1, y1, x2, y2 );

	if ( angle_41x > angle_412 )
		return FALSE;

	return TRUE;
}
BOOL CheckPointInQuad(const DPOINT *fptVert,double x,double y)
{
	double angle_123;
	double angle_12x;
	double angle_234;
	double angle_23x;
	double angle_341;
	double angle_34x;
	double angle_412;
	double angle_41x;
	BOOL inside;

	// This will only handle convex quadrilaterals.
	inside = FALSE;

	angle_12x = GetInteriorAngle( fptVert[0].x, fptVert[0].y, fptVert[1].x, fptVert[1].y, x, y );
	angle_123 = GetInteriorAngle( fptVert[0].x, fptVert[0].y, fptVert[1].x, fptVert[1].y, fptVert[2].x, fptVert[2].y);

	if ( angle_12x > angle_123 )
		return FALSE;

	angle_23x = GetInteriorAngle( fptVert[1].x, fptVert[1].y, fptVert[2].x, fptVert[2].y, x, y );
	angle_234 = GetInteriorAngle( fptVert[1].x, fptVert[1].y, fptVert[2].x, fptVert[2].y, fptVert[3].x, fptVert[3].y );

	if ( angle_23x > angle_234 )
		return FALSE;

	angle_34x = GetInteriorAngle( fptVert[2].x, fptVert[2].y, fptVert[3].x, fptVert[3].y, x, y );
	angle_341 = GetInteriorAngle( fptVert[2].x, fptVert[2].y, fptVert[3].x, fptVert[3].y, fptVert[0].x, fptVert[0].y );

	if ( angle_34x > angle_341 )
		return FALSE;

	angle_41x = GetInteriorAngle( fptVert[3].x, fptVert[3].y, fptVert[0].x, fptVert[0].y, x, y );
	angle_412 = GetInteriorAngle( fptVert[3].x, fptVert[3].y, fptVert[0].x, fptVert[0].y, fptVert[1].x, fptVert[1].y );

	if ( angle_41x > angle_412 )
		return FALSE;

	return TRUE;
}
BOOL CheckPointInQuad(vector<DPOINT> &vecPt,double x,double y)
{
	double angle_123;
	double angle_12x;
	double angle_234;
	double angle_23x;
	double angle_341;
	double angle_34x;
	double angle_412;
	double angle_41x;
	BOOL inside;

	// This will only handle convex quadrilaterals.
	inside = FALSE;

	angle_12x = GetInteriorAngle( vecPt[0].x, vecPt[0].y, vecPt[1].x, vecPt[1].y, x, y );
	angle_123 = GetInteriorAngle( vecPt[0].x, vecPt[0].y, vecPt[1].x, vecPt[1].y, vecPt[2].x, vecPt[2].y);

	if ( angle_12x > angle_123 )
		return FALSE;

	angle_23x = GetInteriorAngle( vecPt[1].x, vecPt[1].y, vecPt[2].x, vecPt[2].y, x, y );
	angle_234 = GetInteriorAngle( vecPt[1].x, vecPt[1].y, vecPt[2].x, vecPt[2].y, vecPt[3].x, vecPt[3].y );

	if ( angle_23x > angle_234 )
		return FALSE;

	angle_34x = GetInteriorAngle( vecPt[2].x, vecPt[2].y, vecPt[3].x, vecPt[3].y, x, y );
	angle_341 = GetInteriorAngle( vecPt[2].x, vecPt[2].y, vecPt[3].x, vecPt[3].y, vecPt[0].x, vecPt[0].y );

	if ( angle_34x > angle_341 )
		return FALSE;

	angle_41x = GetInteriorAngle( vecPt[3].x, vecPt[3].y, vecPt[0].x, vecPt[0].y, x, y );
	angle_412 = GetInteriorAngle( vecPt[3].x, vecPt[3].y, vecPt[0].x, vecPt[0].y, vecPt[1].x, vecPt[1].y );

	if ( angle_41x > angle_412 )
		return FALSE;

	return TRUE;
}
BOOL CheckPointInPolygon(double p[], int polySides, double x, double y)
{
	int     i, j=0;
	BOOL inpoly = FALSE;

	// The following code is by Randolph Franklin
	for (i = 0, j = polySides-1; i < polySides; j = i++)
	{
		if ((((p[i*2+1]<=y) && (y<p[j*2+1])) || ((p[j*2+1]<=y) && (y<p[i*2+1]))) &&
			(x < (p[j*2] - p[i*2]) * (y - p[i*2+1]) / (p[j*2+1] - p[i*2+1]) + p[i*2]))
		  inpoly = !inpoly;
	}
    return inpoly;
}

BOOL CheckPointInPolygon(const DPOINT *fptVert,int nCount,double x,double y)
{
	int  i, j;
	BOOL inpoly = FALSE;

	// The following code is by Randolph Franklin

	for (i = 0, j = nCount-1; i < nCount; j = i++)
	{
		if ((((fptVert[i].y<=y) && (y<fptVert[j].y)) || ((fptVert[j].y<=y) && (y<fptVert[i].y))) &&
			(x < (fptVert[j].x - fptVert[i].x) * (y - fptVert[i].y) / (fptVert[j].y - fptVert[i].y) + fptVert[i].x))
		  inpoly = !inpoly;
	}
    return inpoly;
}
BOOL CheckPointInPolygonFont(vector<FPOINT> &vecTest,double x,double y)
{
	int  i, j=0;
	BOOL inpoly = FALSE;

	// The following code is by Randolph Franklin
	for (i = 0, j = (int)vecTest.size()-1; i < (int)vecTest.size(); j = i++)
	{
		if ((((vecTest[i].y<=y) && (y<vecTest[j].y)) || ((vecTest[j].y<=y) && (y<vecTest[i].y))) &&
			(x < (vecTest[j].x - vecTest[i].x) * (y - vecTest[i].y) / (vecTest[j].y - vecTest[i].y) + vecTest[i].x))
		  inpoly = !inpoly;
	}
    return inpoly;
}

BOOL CheckPointOnLine(DPOINT fptStart, DPOINT fptEnd, double x, double y)
{
	if (x < min(fptStart.x, fptEnd.x) || x > max(fptStart.x, fptEnd.x) || y < min(fptStart.y, fptEnd.y) || y > max(fptStart.y, fptEnd.y))
		return FALSE;

	if (fptStart.x == fptEnd.x && fptStart.y == fptEnd.y)
	{
		if (fabs(fptStart.x - x) < 0.00000001 && fabs(fptStart.y - y) < 0.00000001)
			return TRUE;
		else
			return FALSE;
	}
	else if (fptStart.x == fptEnd.x)
	{
		if (fabs(fptStart.x - x) < 0.00000001)
			return TRUE;
		else
			return FALSE;
	}
	else if (fptStart.y == fptEnd.y)
	{
		if (fabs(fptStart.y - y) < 0.00000001)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		double fGradient = (fptEnd.y - fptStart.y) / (fptEnd.x - fptStart.x);
		double fConstant = fptStart.y - fGradient*fptStart.x;
		double yy = fGradient*x + fConstant;

		if (fabs(yy - y) < 0.00000001)
			return TRUE;
		else
			return FALSE;
	}

	return FALSE;
}

int GetOverlapPointOnLine(DLINE fLine1, DLINE fLine2, DPOINT &fpt1, DPOINT &fpt2)
{
	double x1 = fLine1.p1.x, x2 = fLine1.p2.x, x3 = fLine2.p1.x, x4 = fLine2.p2.x;
	double y1 = fLine1.p1.y, y2 = fLine1.p2.y, y3 = fLine2.p1.y, y4 = fLine2.p2.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		if (GetDistancePointToLine(fLine1.p1, fLine1.p2, fLine2.p1.x, fLine2.p1.y) > 0.00000001)
			return -1;
		else
		{
			x1 = min(fLine1.p1.x, fLine1.p2.x);
			x2 = max(fLine1.p1.x, fLine1.p2.x);
			x3 = min(fLine2.p1.x, fLine2.p2.x);
			x4 = max(fLine2.p1.x, fLine2.p2.x);

			y1 = min(fLine1.p1.y, fLine1.p2.y);
			y2 = max(fLine1.p1.y, fLine1.p2.y);
			y3 = min(fLine2.p1.y, fLine2.p2.y);
			y4 = max(fLine2.p1.y, fLine2.p2.y);

			if (x1 == x2)
			{
				if (y1 == y3 && y2 == y4)
				{
					fpt1 = fLine1.p1;
					fpt2 = fLine1.p2;
					return 2;
				}
				if (y1 == y4)
				{
					if (fLine1.p1.y >  fLine1.p2.y)
						fpt1 = fLine1.p2;
					else
						fpt1 = fLine1.p1;
					return 1;
				}
				if (y2 == y3)
				{
					if (fLine2.p1.y > fLine2.p2.y)
						fpt1 = fLine2.p2;
					else
						fpt1 = fLine2.p1;
					return 1;
				}
				if (y2 > y4)
				{
					if (y1 > y4)
					{
						return -1;
					}
					else
					{
						if (fLine2.p1.y > fLine2.p2.y)
							fpt1 = fLine2.p1;
						else
							fpt1 = fLine2.p2;

						if (y1 > y3)
						{
							if (fLine1.p1.y >  fLine1.p2.y)
								fpt2 = fLine1.p2;
							else
								fpt2 = fLine1.p1;
						}
						else
						{
							if (fLine2.p1.y > fLine2.p2.y)
								fpt2 = fLine2.p2;
							else
								fpt2 = fLine2.p1;
						}
						return 2;
					}
				}
				else
				{
					if (y2 < y3)
					{
						return -1;
					}
					else
					{
						if (fLine1.p1.y >  fLine1.p2.y)
							fpt1 = fLine1.p1;
						else
							fpt1 = fLine1.p2;

						if (y1 > y3)
						{
							if (fLine1.p1.y >  fLine1.p2.y)
								fpt1 = fLine1.p2;
							else
								fpt1 = fLine1.p1;
						}
						else
						{
							if (fLine2.p1.y > fLine2.p2.y)
								fpt1 = fLine2.p2;
							else
								fpt1 = fLine2.p1;
						}

						return 2;
					}
				}
			}
			else
			{
				if (x1 == x3 && x2 == x4)
				{
					fpt1 = fLine1.p1;
					fpt2 = fLine1.p2;
					return 2;
				}
				if (x1 == x4)
				{
					if (fLine2.p1.x > fLine2.p2.x)
						fpt1 = fLine2.p1;
					else
						fpt1 = fLine2.p2;

					return 1;
				}
				if (x2 == x3)
				{
					if (fLine1.p1.x >  fLine1.p2.x)
						fpt1 = fLine1.p1;
					else
						fpt1 = fLine1.p2;

					return 1;
				}
				if (x2 > x4)
				{
					if (x1 > x4)
					{
						return -1;
					}
					else
					{
						if (fLine2.p1.x > fLine2.p2.x)
							fpt1 = fLine2.p1;
						else
							fpt1 = fLine2.p2;

						if (x1 > x3)
						{
							if (fLine1.p1.x >  fLine1.p2.x)
								fpt1 = fLine1.p2;
							else
								fpt1 = fLine1.p1;
						}
						else
						{
							if (fLine2.p1.x > fLine2.p2.x)
								fpt1 = fLine2.p2;
							else
								fpt1 = fLine2.p1;
						}
						return 2;
					}
				}
				else
				{
					if (x2 < x3)
					{
						return -1;
					}
					else
					{
						if (fLine1.p1.x >  fLine1.p2.x)
							fpt1 = fLine1.p1;
						else
							fpt1 = fLine1.p2;

						if (x1 > x3)
						{
							if (fLine1.p1.x >  fLine1.p2.x)
								fpt1 = fLine1.p2;
							else
								fpt1 = fLine1.p1;
						}
						else
						{
							if (fLine2.p1.x > fLine2.p2.x)
								fpt1 = fLine2.p2;
							else
								fpt1 = fLine2.p1;
						}
						return 2;
					}
				}
			}
		}
	}

	return -1;
}

int GetOverlapPointOnLine(CdPoint fptStart, CdPoint fptEnd, CdPoint fptStart1, CdPoint fptEnd1, CdPoint &fpt1, CdPoint &fpt2)
{
	double x1 = fptStart.x, x2 = fptEnd.x, x3 = fptStart1.x, x4 = fptEnd1.x;
	double y1 = fptStart.y, y2 = fptEnd.y, y3 = fptStart1.y, y4 = fptEnd1.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		if (GetDistancePointToLine(fptStart, fptEnd, fptStart1.x, fptStart1.y) > 0.00000001)
			return -1;
		else
		{
			x1 = min(fptStart.x, fptEnd.x);
			x2 = max(fptStart.x, fptEnd.x);
			x3 = min(fptStart1.x, fptEnd1.x);
			x4 = max(fptStart1.x, fptEnd1.x);

			y1 = min(fptStart.y, fptEnd.y);
			y2 = max(fptStart.y, fptEnd.y);
			y3 = min(fptStart1.y, fptEnd1.y);
			y4 = max(fptStart1.y, fptEnd1.y);

			if (x1 == x2)
			{
				if (y1 == y3 && y2 == y4)
				{
					fpt1 = fptStart;
					fpt2 = fptEnd;
					return 2;
				}
				if (y1 == y4)
				{
					if (fptStart.y > fptEnd.y)
						fpt1 = fptEnd;
					else
						fpt1 = fptStart;
					return 1;
				}
				if (y2 == y3)
				{
					if (fptStart1.y > fptEnd1.y)
						fpt1 = fptEnd1;
					else
						fpt1 = fptStart1;
					return 1;
				}
				if (y2 > y4)
				{
					if (y1 > y4)
					{
						return -1;
					}
					else
					{
						if (fptStart1.y > fptEnd1.y)
							fpt1 = fptStart1;
						else
							fpt1 = fptEnd1;

						if (y1 > y3)
						{
							if (fptStart.y > fptEnd.y)
								fpt2 = fptEnd;
							else
								fpt2 = fptStart;
						}
						else
						{
							if (fptStart1.y > fptEnd1.y)
								fpt2 = fptEnd1;
							else
								fpt2 = fptStart1;
						}
						return 2;
					}
				}
				else
				{
					if (y2 < y3)
					{
						return -1;
					}
					else
					{
						if (fptStart.y > fptEnd.y)
							fpt1 = fptStart;
						else
							fpt1 = fptEnd;

						if (y1 > y3)
						{
							if (fptStart.y > fptEnd.y)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.y > fptEnd1.y)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}

						return 2;
					}
				}
			}
			else
			{
				if (x1 == x3 && x2 == x4)
				{
					fpt1 = fptStart;
					fpt2 = fptEnd;
					return 2;
				}
				if (x1 == x4)
				{
					if (fptStart1.x > fptEnd1.x)
						fpt1 = fptStart1;
					else
						fpt1 = fptEnd1;

					return 1;
				}
				if (x2 == x3)
				{
					if (fptStart.x > fptEnd.x)
						fpt1 = fptStart;
					else
						fpt1 = fptEnd;

					return 1;
				}
				if (x2 > x4)
				{
					if (x1 > x4)
					{
						return -1;
					}
					else
					{
						if (fptStart1.x > fptEnd1.x)
							fpt1 = fptStart1;
						else
							fpt1 = fptEnd1;

						if (x1 > x3)
						{
							if (fptStart.x > fptEnd.x)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.x > fptEnd1.x)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}
						return 2;
					}
				}
				else
				{
					if (x2 < x3)
					{
						return -1;
					}
					else
					{
						if (fptStart.x > fptEnd.x)
							fpt1 = fptStart;
						else
							fpt1 = fptEnd;

						if (x1 > x3)
						{
							if (fptStart.x > fptEnd.x)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.x > fptEnd1.x)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}
						return 2;
					}
				}
			}
		}
	}

	return -1;
}

int GetOverlapPointOnLine(DPOINT fptStart, DPOINT fptEnd, DPOINT fptStart1, DPOINT fptEnd1, DPOINT &fpt1, DPOINT &fpt2)
{
	double x1 = fptStart.x, x2 = fptEnd.x, x3 = fptStart1.x, x4 = fptEnd1.x;
	double y1 = fptStart.y, y2 = fptEnd.y, y3 = fptStart1.y, y4 = fptEnd1.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		if (GetDistancePointToLine(fptStart, fptEnd, fptStart1.x, fptStart1.y) > 0.00000001)
			return -1;
		else
		{
			x1 = min(fptStart.x, fptEnd.x);
			x2 = max(fptStart.x, fptEnd.x);
			x3 = min(fptStart1.x, fptEnd1.x);
			x4 = max(fptStart1.x, fptEnd1.x);

			y1 = min(fptStart.y, fptEnd.y);
			y2 = max(fptStart.y, fptEnd.y);
			y3 = min(fptStart1.y, fptEnd1.y);
			y4 = max(fptStart1.y, fptEnd1.y);

			if (x1 == x2)
			{
				if (y1 == y3 && y2 == y4)
				{
					fpt1 = fptStart;
					fpt2 = fptEnd;
					return 2;
				}
				if (y1 == y4)
				{
					if (fptStart.y > fptEnd.y)
						fpt1 = fptEnd;
					else
						fpt1 = fptStart;
					return 1;
				}
				if (y2 == y3)
				{
					if (fptStart1.y > fptEnd1.y)
						fpt1 = fptEnd1;
					else
						fpt1 = fptStart1;
					return 1;
				}
				if(y2 > y4)
				{
					if (y1 > y4)
					{
						return -1;
					}
					else
					{
						if (fptStart1.y > fptEnd1.y)
							fpt1 = fptStart1;
						else
							fpt1 = fptEnd1;

						if (y1 > y3)
						{
							if (fptStart.y > fptEnd.y)
								fpt2 = fptEnd;
							else
								fpt2 = fptStart;
						}
						else
						{
							if (fptStart1.y > fptEnd1.y)
								fpt2 = fptEnd1;
							else
								fpt2 = fptStart1;
						}
						return 2;
					}
				}
				else
				{
					if (y2 < y3)
					{
						return -1;
					}
					else
					{
						if (fptStart.y > fptEnd.y)
							fpt1 = fptStart;
						else
							fpt1 = fptEnd;

						if (y1 > y3)
						{
							if (fptStart.y > fptEnd.y)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.y > fptEnd1.y)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}

						return 2;
					}
				}
			}
			else
			{
				if (x1 == x3 && x2 == x4)
				{
					fpt1 = fptStart;
					fpt2 = fptEnd;
					return 2;
				}
				if (x1 == x4)
				{
					if (fptStart1.x > fptEnd1.x)
						fpt1 = fptStart1;
					else
						fpt1 = fptEnd1;

					return 1;
				}
				if (x2 == x3)
				{
					if (fptStart.x > fptEnd.x)
						fpt1 = fptStart;
					else
						fpt1 = fptEnd;

					return 1;
				}
				if (x2 > x4)
				{
					if (x1 > x4)
					{
						return -1;
					}
					else
					{
						if (fptStart1.x > fptEnd1.x)
							fpt1 = fptStart1;
						else
							fpt1 = fptEnd1;

						if (x1 > x3)
						{
							if (fptStart.x > fptEnd.x)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.x > fptEnd1.x)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}
						return 2;
					}
				}
				else
				{
					if (x2 < x3)
					{
						return -1;
					}
					else
					{
						if (fptStart.x > fptEnd.x)
							fpt1 = fptStart;
						else
							fpt1 = fptEnd;

						if (x1 > x3)
						{
							if (fptStart.x > fptEnd.x)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.x > fptEnd1.x)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}
						return 2;
					}
				}
			}
		}
	}

	return -1;
}

int GetOverlapPointOnLine(CPoint fptStart, CPoint fptEnd, CPoint fptStart1, CPoint fptEnd1, CPoint &fpt1, CPoint &fpt2)
{
	int x1 = fptStart.x, x2 = fptEnd.x, x3 = fptStart1.x, x4 = fptEnd1.x;
	int y1 = fptStart.y, y2 = fptEnd.y, y3 = fptStart1.y, y4 = fptEnd1.y;
	int d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		if (GetDistancePointToLine(fptStart, fptEnd, fptStart1.x, fptStart1.y) > 0)
			return -1;
		else
		{
			x1 = min(fptStart.x, fptEnd.x);
			x2 = max(fptStart.x, fptEnd.x);
			x3 = min(fptStart1.x, fptEnd1.x);
			x4 = max(fptStart1.x, fptEnd1.x);

			y1 = min(fptStart.y, fptEnd.y);
			y2 = max(fptStart.y, fptEnd.y);
			y3 = min(fptStart1.y, fptEnd1.y);
			y4 = max(fptStart1.y, fptEnd1.y);

			if (x1 == x2)
			{
				if (y1 == y3 && y2 == y4)
				{
					fpt1 = fptStart;
					fpt2 = fptEnd;
					return 2;
				}
				if (y1 == y4)
				{
					if (fptStart.y > fptEnd.y)
						fpt1 = fptEnd;
					else
						fpt1 = fptStart;
					return 1;
				}
				if (y2 == y3)
				{
					if (fptStart1.y > fptEnd1.y)
						fpt1 = fptEnd1;
					else
						fpt1 = fptStart1;
					return 1;
				}
				if (y2 > y4)
				{
					if (y1 > y4)
					{
						return -1;
					}
					else
					{
						if (fptStart1.y > fptEnd1.y)
							fpt1 = fptStart1;
						else
							fpt1 = fptEnd1;

						if (y1 > y3)
						{
							if (fptStart.y > fptEnd.y)
								fpt2 = fptEnd;
							else
								fpt2 = fptStart;
						}
						else
						{
							if (fptStart1.y > fptEnd1.y)
								fpt2 = fptEnd1;
							else
								fpt2 = fptStart1;
						}
						return 2;
					}
				}
				else
				{
					if (y2 < y3)
					{
						return -1;
					}
					else
					{
						if (fptStart.y > fptEnd.y)
							fpt1 = fptStart;
						else
							fpt1 = fptEnd;

						if (y1 > y3)
						{
							if (fptStart.y > fptEnd.y)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.y > fptEnd1.y)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}

						return 2;
					}
				}
			}
			else
			{
				if (x1 == x3 && x2 == x4)
				{
					fpt1 = fptStart;
					fpt2 = fptEnd;
					return 2;
				}
				if (x1 == x4)
				{
					if (fptStart1.x > fptEnd1.x)
						fpt1 = fptStart1;
					else
						fpt1 = fptEnd1;

					return 1;
				}
				if (x2 == x3)
				{
					if (fptStart.x > fptEnd.x)
						fpt1 = fptStart;
					else
						fpt1 = fptEnd;

					return 1;
				}
				if (x2 > x4)
				{
					if (x1 > x4)
					{
						return -1;
					}
					else
					{
						if (fptStart1.x > fptEnd1.x)
							fpt1 = fptStart1;
						else
							fpt1 = fptEnd1;

						if (x1 > x3)
						{
							if (fptStart.x > fptEnd.x)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.x > fptEnd1.x)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}
						return 2;
					}
				}
				else
				{
					if (x2 < x3)
					{
						return -1;
					}
					else
					{
						if (fptStart.x > fptEnd.x)
							fpt1 = fptStart;
						else
							fpt1 = fptEnd;

						if (x1 > x3)
						{
							if (fptStart.x > fptEnd.x)
								fpt1 = fptEnd;
							else
								fpt1 = fptStart;
						}
						else
						{
							if (fptStart1.x > fptEnd1.x)
								fpt1 = fptEnd1;
							else
								fpt1 = fptStart1;
						}
						return 2;
					}
				}
			}
		}
	}

	return -1;
}

BOOL IsConvex(vector<DPOINT> &vecPt)
{
	if (vecPt.size()<4)
		return TRUE;
	BOOL sign= FALSE;
	int n=(int)vecPt.size();

	if(vecPt[0].x == vecPt[n-1].x && vecPt[0].y == vecPt[n-1].y)
	{
		n--;
	}

	double dx1,dy1,dx2,dy2,zcrossproduct;
	for(int i=0;i<n;i++)
	{
		dx1 = vecPt[(i+2)%n].x-vecPt[(i+1)%n].x;
		dy1 = vecPt[(i+2)%n].y-vecPt[(i+1)%n].y;
		dx2 = vecPt[i].x-vecPt[(i+1)%n].x;
		dy2 = vecPt[i].y-vecPt[(i+1)%n].y;
		zcrossproduct = dx1*dy2 - dy1*dx2;
		if (i == 0)
			sign = zcrossproduct > 0;
		else
		{
			if (sign != (zcrossproduct>0))
				return FALSE;
		}
	}
	return TRUE;
}

BOOL IsConvex(const DPOINT *fptVert,int nCount)
{
	if (nCount < 4)
		return TRUE;
	if(fptVert[0].x == fptVert[nCount-1].x && fptVert[0].y == fptVert[nCount-1].y)
	{
		nCount--;
	}
	BOOL sign= FALSE;
	double dx1,dy1,dx2,dy2,zcrossproduct;
	for(int i=0;i<nCount;i++)
	{
		dx1 = fptVert[(i+2)%nCount].x-fptVert[(i+1)%nCount].x;
		dy1 = fptVert[(i+2)%nCount].y-fptVert[(i+1)%nCount].y;
		dx2 = fptVert[i].x-fptVert[(i+1)%nCount].x;
		dy2 = fptVert[i].y-fptVert[(i+1)%nCount].y;
		zcrossproduct = dx1*dy2 - dy1*dx2;
		if (i==0)
			sign=zcrossproduct>0;
		else
		{
			if (sign!=(zcrossproduct>0))
				return FALSE;
		}
	}
	return TRUE;
}

void GetPolygonClipping(vector<DPOINT> &vecPolygonVertex,vector<DPOINT> &vecLine,vector<DPOINT> &vecPoint)
{
	if(vecPolygonVertex[0].x != vecPolygonVertex[vecPolygonVertex.size()-1].x || vecPolygonVertex[0].y != vecPolygonVertex[vecPolygonVertex.size()-1].y )
		vecPolygonVertex.push_back(vecPolygonVertex[0]);
	unsigned int VertNo;
	unsigned int nNumSignChanges = 0;		// Tracks number of determinant sign changes
	unsigned int nPolygonSize = (int)vecPolygonVertex.size();
	if(nPolygonSize<3)
		return;
	int *ppnDetSignTable;
	ppnDetSignTable = new int[nPolygonSize];
	BOOL *ppbSignChangeTable;
	ppbSignChangeTable = new BOOL[nPolygonSize];

	for (VertNo = 0; VertNo < nPolygonSize; VertNo++)
	{	
		// Calculate the determinant (3x3 square matrix)
		double dS_i =  vecPolygonVertex[VertNo].x * (vecLine[0].y - vecLine[1].y)- vecLine[0].x * (vecPolygonVertex[VertNo].y - vecLine[1].y)+ 
			vecLine[1].x * (vecPolygonVertex[VertNo].y - vecLine[0].y);
	
		// Check the determinant result
		switch (VertNo) 
		{
			case 0:
				if (dS_i == 0)		// we have hit a vertex
					ppnDetSignTable[VertNo] = 0;

				else if (dS_i > 0)
					ppnDetSignTable[VertNo] = 1;		// +'ve

				else if (dS_i < 0)
					ppnDetSignTable[VertNo] = -1;		// -'ve

				ppbSignChangeTable[0] = FALSE;		// First element will NEVER be a sign change
				break;
			default:
				if (dS_i == 0)
					ppnDetSignTable[VertNo] = 0;
			
				else if (dS_i > 0)
					ppnDetSignTable[VertNo] = 1;

				else if (dS_i < 0)
					ppnDetSignTable[VertNo] = -1;
		
				// Check for sign change
				if (ppnDetSignTable[VertNo - 1] != ppnDetSignTable[VertNo])
				{
					ppbSignChangeTable[VertNo] = TRUE;
					nNumSignChanges++;
				}
				else
					ppbSignChangeTable[VertNo] = FALSE;
		}
	}
	//nNumSignChanges
	double dDeltaX;
	double dDeltaY;

	double dPolyLineSlope;		// Slope of polygon line segment
	double dBPoly;

	double dDeltaYLine;
	double dDeltaXLine;

	double dSlopeLine;			// Slope of intersecting line
	double dBLine;

	// Points and regions needed for checking if
	// the point is actually valid...

	CdRect lLineRect;

	double *pdIntersectionX;
	double *pdIntersectionY;
	vector<CdPoint> vecRect;
	CdPoint stpoint;
	unsigned int i;
	for( i=0; i<4; i++)
		vecRect.push_back(stpoint);

	pdIntersectionX = new double[nPolygonSize];
	pdIntersectionY = new double[nPolygonSize];

	unsigned int nIntrNum = 0;		// Tracks number of intersections	
	for (VertNo = 0; VertNo <nPolygonSize; VertNo++)
	{


		if (ppbSignChangeTable[VertNo] == TRUE)	// If true, create equation of the line
		{
			nIntrNum++;

			// Equation of polygon segment
			dDeltaX = vecPolygonVertex[VertNo].x - vecPolygonVertex[VertNo - 1].x;	// Ok here as 1st element ALWAYS false
			dDeltaY = vecPolygonVertex[VertNo].y - vecPolygonVertex[VertNo - 1].y;



			// Formulate equation of intersection line
			dDeltaYLine = vecLine[1].y - vecLine[0].y;
			dDeltaXLine = vecLine[1].x - vecLine[0].x;

			// Create the region from the points

			lLineRect.SetRect(vecLine[0].x,vecLine[0].y,vecLine[1].x,vecLine[1].y);
			lLineRect.InflateRect(1,1);
			lLineRect.NormalizeRect();

			vecRect[0].x = lLineRect.left;
			vecRect[0].y = lLineRect.top;

			vecRect[1].x = lLineRect.right;
			vecRect[1].y = lLineRect.top;

			vecRect[2].x = lLineRect.right;
			vecRect[2].y = lLineRect.bottom;

			vecRect[3].x = lLineRect.left;
			vecRect[3].y = lLineRect.bottom;


			
			if (dDeltaX == 0)	// Polygon line segment is vertical - trap it
			{
				dSlopeLine = dDeltaYLine / dDeltaXLine;
				dBLine = vecLine[1].y - dSlopeLine * vecLine[1].x;

				pdIntersectionX[nIntrNum] = vecPolygonVertex[VertNo].x;
				pdIntersectionY[nIntrNum] = dSlopeLine * pdIntersectionX[nIntrNum] + dBLine;
				

		
				if(!CheckPointInPolygon(&vecRect[0],(int)vecRect.size(),pdIntersectionX[nIntrNum],pdIntersectionY[nIntrNum]))
				{
					pdIntersectionY[nIntrNum] = -1;
					pdIntersectionX[nIntrNum] = -1;
				}

			}
			else if (dDeltaXLine == 0)	// Intersection line is vertical
			{
				dPolyLineSlope = dDeltaY / dDeltaX;
				dBPoly = vecPolygonVertex[VertNo].y - dPolyLineSlope * vecPolygonVertex[VertNo].x;

				pdIntersectionX[nIntrNum] = vecLine[1].x;
				pdIntersectionY[nIntrNum] = dPolyLineSlope * pdIntersectionX[nIntrNum] + dBPoly;
				


				if(!CheckPointInPolygon(&vecRect[0],(int)vecRect.size(),pdIntersectionX[nIntrNum],pdIntersectionY[nIntrNum]))
				{
					pdIntersectionY[nIntrNum] = -1;
					pdIntersectionX[nIntrNum] = -1;
				}
			}
			else if (dDeltaY == 0)	// Polygon segment is horizontal
			{
				dSlopeLine = dDeltaYLine / dDeltaXLine;
				dBLine = vecLine[1].y - dSlopeLine * vecLine[1].x;

				pdIntersectionY[nIntrNum] = vecPolygonVertex[VertNo].y;
				pdIntersectionX[nIntrNum] = (pdIntersectionY[nIntrNum] - dBLine) / dSlopeLine;
				
				if(!CheckPointInPolygon(&vecRect[0],(int)vecRect.size(),pdIntersectionX[nIntrNum],pdIntersectionY[nIntrNum]))
				{
					pdIntersectionY[nIntrNum] = -1;
					pdIntersectionX[nIntrNum] = -1;
				}
				
			}
			else if (dDeltaYLine == 0)	// Line segment horizontal
			{
				dPolyLineSlope = dDeltaY / dDeltaX;
				dSlopeLine = 0;

				dBPoly = vecPolygonVertex[VertNo].y - dPolyLineSlope * vecPolygonVertex[VertNo].x;
				dBLine = vecLine[1].y - dSlopeLine * vecLine[1].x;
			
				pdIntersectionY[nIntrNum] = dBLine;
				pdIntersectionX[nIntrNum] = (pdIntersectionY[nIntrNum] - dBPoly) / dPolyLineSlope;

				if(!CheckPointInPolygon(&vecRect[0],(int)vecRect.size(),pdIntersectionX[nIntrNum],pdIntersectionY[nIntrNum]))
				{
					pdIntersectionY[nIntrNum] = -1;
					pdIntersectionX[nIntrNum] = -1;
				}
			}
			else	// default case
			{
				// Calculate the slope and y-intercepts of polygon segment
				dPolyLineSlope = dDeltaY / dDeltaX;
				dBPoly = vecPolygonVertex[VertNo].y - dPolyLineSlope * vecPolygonVertex[VertNo].x;

				// slope and intercept of the line
				dSlopeLine = dDeltaYLine / dDeltaXLine;
				dBLine = vecLine[1].y - dSlopeLine * vecLine[1].x;

				// Solve the linear equations for the intersection points
				pdIntersectionX[nIntrNum] = (dBPoly - dBLine) / (dSlopeLine - dPolyLineSlope);
				pdIntersectionY[nIntrNum] = dSlopeLine * pdIntersectionX[nIntrNum] + dBLine;

				if(!CheckPointInPolygon(&vecRect[0],(int)vecRect.size(),pdIntersectionX[nIntrNum],pdIntersectionY[nIntrNum]))
				{
					pdIntersectionY[nIntrNum] = -1;
					pdIntersectionX[nIntrNum] = -1;
				}
				
			}

		}	
	}
	
	
	for(i=1;i<=nIntrNum;i++)
	{
		if((pdIntersectionX[i] != -1) &&(pdIntersectionY[i] != -1))
		{
//			beforePt = stpoint;
			stpoint.x = pdIntersectionX[i];
			stpoint.y = pdIntersectionY[i];
//			if(i>1)
//			{
//				if(beforePt.x ==stpoint.x &&beforePt.y ==stpoint.y)
//					continue;
//			}
			vecPoint.push_back(stpoint);
		}
	}

	delete[] ppnDetSignTable;
	delete[] ppbSignChangeTable;
	delete[] pdIntersectionX;
	delete[] pdIntersectionY;
	return ;
}
//////////////////////////////////////
// 3점이 주어졌을때 나머지 한점을 계산하여 리턴한다.
// 이때 구해지는 나머지 한점은 파라메타 입력순서에 영향을 받는다.
// 파라메타의 입력방향으로 한점이 생긴다.
void GetCornerPoint(double x1,double y1,double x2,double y2,double x3,double y3,double *x0,double *y0) 
{
	double cx,cy;
	
	cx = x1-x2+x3;	
	cy = y1-y2+y3;	

	*x0 = cx;
	*y0 = cy;
}

// 두선분의 벡터 방향을 나타낸다.
// 시계방향일 경우 (1)을 반시계 방향일경우 (-1)을  리턴한다.
// 두선분이 동일한 방향이라면 0를 리턴한다.
int GetVectorDir(double ax, double ay, double bx, double by, double cx, double cy)
{
	double temp;
	temp = bx*cy - ay*bx - ax*cy - by*cx + ax*by + ay*cx;
	if(temp >0.0)
		return CW;
	else if(temp <0.0) 
		return CCW;
	else 
		return PARALLEL;
}

int GetVectorDir(DPOINT start,DPOINT middle,DPOINT end)
{
	double temp;
	temp = middle.x*end.y - start.y*middle.x - start.x*end.y - middle.y*end.x 
		   + start.x*middle.y + start.y*end.x;
	if(temp >0.0)
		return CW;
	else if(temp <0.0) 
		return CCW;
	else 
		return PARALLEL;
}

int GetVectorDir(DPOINT3D start,DPOINT3D middle,DPOINT3D end)
{
	double temp;
	temp = middle.x*end.y - start.y*middle.x - start.x*end.y - middle.y*end.x 
		   + start.x*middle.y + start.y*end.x;
	if(temp >0.0)
		return CW;
	else if(temp <0.0) 
		return CCW;
	else 
		return PARALLEL;
}
int GetVectorDir(CdPoint start,CdPoint middle,CdPoint end)
{
	double temp;
	temp = middle.x*end.y - start.y*middle.x - start.x*end.y - middle.y*end.x 
		   + start.x*middle.y + start.y*end.x;
	if(temp >0.0)
		return CW;
	else if(temp <0.0) 
		return CCW;
	else 
		return PARALLEL;
}

/////////////////////////////////////
// GetInteriorAngle returns the interior angle in radians between two rays in 2D.
// Modified:
// 19 April 1999
// Author:
// John Burkardt
// Parameters:
// Input, double X1, Y1, X2, Y2, X3, Y3, define the rays
// (X1-X2,Y1-Y2) and (X3-X2,Y3-Y2) which in turn define the angle.
// Output, the angle swept out by the rays, measured in radians.
// This value satisfies 0 <= ANGLEI_RAD_2D 
// ray is of zero length, then ANGLEI_RAD_2D is returned as 0.
double GetAngle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double fAngleRad;
	double x;
	double y;

	x = (x1 - x2) * (x3 - x2) + (y1 - y2) * (y3 - y2);
	y = (x1 - x2) * (y3 - y2) - (y1 - y2) * (x3 - x2);

	if (x == 0.0 && y == 0.0)
		fAngleRad = 0.0;
	else
	{
		fAngleRad = atan2(y, x);
		if (fAngleRad < 0.0)
			fAngleRad = fAngleRad + 2.0 * PI;
	}

	return fAngleRad / PI*180.; //  Degree단위로 
}

// 두선분으로 이루어진 각을 리턴한다.
double GetAngle(DPOINT start, DPOINT middle, DPOINT end)
{
	double fAngle; // Radian 단위임
	double fX;
	double fY;

	fX = (start.x - middle.x)*(end.x - middle.x) + (start.y - middle.y)*(end.y - middle.y);
	fY = (start.x - middle.x)*(end.y - middle.y) - (start.y - middle.y)*(end.x - middle.x);

	if (fX == 0. && fY == 0.)
		fAngle = 0.0;
	else
	{
		fAngle = atan2(fY, fX);
		if (fAngle < 0.)
			fAngle = fAngle + 2. * PI;
	}

	fAngle = fAngle / PI*180.; //  Degree단위로 
	return fAngle;
}


// 두선분으로 이루어진 각을 리턴한다.
double GetAngle(DPOINT3D start, DPOINT3D middle, DPOINT3D end)
{
	double fAngle; // Radian 단위임
	double fX;
	double fY;

	fX = (start.x - middle.x)*(end.x - middle.x) + (start.y - middle.y)*(end.y - middle.y);
	fY = (start.x - middle.x)*(end.y - middle.y) - (start.y - middle.y)*(end.x - middle.x);

	if (fX == 0. && fY == 0.)
		fAngle = 0.0;
	else
	{
		fAngle = atan2(fY, fX);
		if (fAngle < 0.)
			fAngle = fAngle + 2. * PI;
	}

	fAngle = fAngle / PI*180.; //  Degree단위로 
	return fAngle;
}
double GetAngle(CdPoint start, CdPoint middle, CdPoint end)
{
	double fAngle; // Radian 단위임
	double fX;
	double fY;

	fX = (start.x - middle.x)*(end.x - middle.x) + (start.y - middle.y)*(end.y - middle.y);
	fY = (start.x - middle.x)*(end.y - middle.y) - (start.y - middle.y)*(end.x - middle.x);

	if (fX == 0. && fY == 0.)
		fAngle = 0.0;
	else
	{
		fAngle = atan2(fY, fX);
		if (fAngle < 0.)
			fAngle = fAngle + 2. * PI;
	}

	fAngle = fAngle / PI*180.; //  Degree단위로 
	return fAngle;
}
// 두선분으로 이루어진 내각을 절대값으로 리턴한다.
double GetInteriorAngle(double x1,double y1,double x2,double y2,double x3,double y3)
{
	double fAngleRad;
	double x;
	double y;

	x = ( x1 - x2 ) * ( x3 - x2 ) + ( y1 - y2 ) * ( y3 - y2 );
	y = ( x1 - x2 ) * ( y3 - y2 ) - ( y1 - y2 ) * ( x3 - x2 );

	if ( x == 0.0 && y == 0.0)
		fAngleRad = 0.0;
	else
	{
		fAngleRad = atan2(y,x);
		if (fAngleRad <0.0)
			fAngleRad = fAngleRad + 2.0 * PI;
	}
	
	if(GetVectorDir(x1,y1,x2,y2,x3,y3) == 1)
		fAngleRad = 2.0 * PI - fAngleRad;
		
	return fAngleRad/PI*180.; //  Degree단위로 
}

// 두선분으로 이루어진 내각을 절대값으로 리턴한다.
double GetInteriorAngle(DPOINT start,DPOINT middle,DPOINT end)
{
	double fAngle; // Radian 단위임
	double fX;
	double fY;

	fX=(start.x-middle.x)*(end.x-middle.x)+(start.y-middle.y)*(end.y-middle.y);
	fY=(start.x-middle.x)*(end.y-middle.y)-(start.y-middle.y)*(end.x-middle.x);

	if ( fX == 0. && fY == 0.)
		fAngle = 0.0;
	else
	{
		fAngle = atan2(fY,fX);
		if (fAngle <0.)
			fAngle = fAngle + 2. * PI;
	}
	
	if(GetVectorDir(start,middle,end) == CW)
		fAngle = 2. * PI - fAngle;
		
	fAngle = fAngle/PI*180.; //  Degree단위로 
	return fAngle;
}


// 두선분으로 이루어진 내각을 절대값으로 리턴한다.
double GetInteriorAngle(DPOINT3D start,DPOINT3D middle,DPOINT3D end)
{
	double fAngle; // Radian 단위임
	double fX;
	double fY;

	fX=(start.x-middle.x)*(end.x-middle.x)+(start.y-middle.y)*(end.y-middle.y);
	fY=(start.x-middle.x)*(end.y-middle.y)-(start.y-middle.y)*(end.x-middle.x);

	if ( fX == 0. && fY == 0.)
		fAngle = 0.0;
	else
	{
		fAngle = atan2(fY,fX);
		if (fAngle <0.)
			fAngle = fAngle + 2. * PI;
	}
	
	if(GetVectorDir(start,middle,end) == CW)
		fAngle = 2. * PI - fAngle;
		
	fAngle = fAngle/PI*180.; //  Degree단위로 
	return fAngle;
}
double GetInteriorAngle(CdPoint start,CdPoint middle,CdPoint end)
{
	double fAngle; // Radian 단위임
	double fX;
	double fY;

	fX=(start.x-middle.x)*(end.x-middle.x)+(start.y-middle.y)*(end.y-middle.y);
	fY=(start.x-middle.x)*(end.y-middle.y)-(start.y-middle.y)*(end.x-middle.x);

	if ( fX == 0. && fY == 0.)
		fAngle = 0.0;
	else
	{
		fAngle = atan2(fY,fX);
		if (fAngle <0.)
			fAngle = fAngle + 2. * PI;
	}

	if(GetVectorDir(start,middle,end) == CW)
		fAngle = 2. * PI - fAngle;

	fAngle = fAngle/PI*180.; //  Degree단위로 
	return fAngle;
}
// 시작과 끝점으로 형성된 선분의 Angle을 리턴
double GetLineAngle(double x1, double y1, double x2, double y2)
{
	double dAngle = 0.0;
	double dX = x2 - x1;
	double dY = y2 - y1;

	if (dX == 0.0)
	{
		if (dY > 0)
			dAngle = PI / 2.0;
		else
			dAngle = -PI / 2.0;
	}
	else if (dY == 0.0)
	{
		if (dX > 0)
			dAngle = 0.0;
		else
			dAngle = PI;
	}
	else
	{
		dAngle = atan2(dY, dX);
	}

	return dAngle;			//// Radian 단위로 출력
}
double GetLineAngle(DPOINT start, DPOINT end)
{
	double dAngle = 0.0;
	double dX = end.x - start.x;
	double dY = end.y - start.y;

	if (dX == 0.0)
	{
		if (dY > 0)
			dAngle = PI / 2.0;
		else
			dAngle = -PI / 2.0;
	}
	else if (dY == 0.0)
	{
		if (dX > 0)
			dAngle = 0.0;
		else
			dAngle = PI;
	}
	else
	{
		dAngle = atan2(dY, dX);
	}

	return dAngle;			//// Radian 단위로 출력
}
double GetLineAngle(DPOINT3D start, DPOINT3D end)
{
	double dAngle = 0.0;
	double dX = end.x - start.x;
	double dY = end.y - start.y;

	if (dX == 0.0)
	{
		if (dY > 0)
			dAngle = PI / 2.0;
		else
			dAngle = -PI / 2.0;
	}
	else if (dY == 0.0)
	{
		if (dX > 0)
			dAngle = 0.0;
		else
			dAngle = PI;
	}
	else
	{
		dAngle = atan2(dY, dX);
	}

	return dAngle;			//// Radian 단위로 출력
}
double GetLineAngle(CdPoint start, CdPoint end)
{
	double dAngle = 0.0;
	double dX = end.x - start.x;
	double dY = end.y - start.y;

	if (dX == 0.0)
	{
		if (dY > 0)
			dAngle = PI / 2.0;
		else
			dAngle = -PI / 2.0;
	}
	else if (dY == 0.0)
	{
		if (dX > 0)
			dAngle = 0.0;
		else
			dAngle = PI;
	}
	else
	{
		dAngle = atan2(dY, dX);
	}

	return dAngle;			//// Radian 단위로 출력
}
// 두 선분이 교차하는지를 조사.
// 교차하면 1을 그렇지 않으면 -1을 리턴한다.
// 만약 한선분의 끝점이 다른 선분상에 존재하면 0을 리턴한다.
/* 20190211 Modify ===================================>
int CheckIntersect(DLINE fLine1,DLINE fLine2)
{
	//C로 배우는 알고리즘,이재규,도처출판 세화,
	int r123,r124,r341,r342;

	if(fLine1.p1.x > fLine1.p2.x)
	{
		swap(fLine1.p1.x,fLine1.p2.x);
		swap(fLine1.p1.y,fLine1.p2.y);
	}

	if(fLine2.p1.x > fLine2.p2.x)
	{
		swap(fLine2.p1.x,fLine2.p2.x);
		swap(fLine2.p1.y,fLine2.p2.y);
	}

	r123 = GetVectorDir(fLine1.p1,fLine1.p2,fLine2.p1);
	r124 = GetVectorDir(fLine1.p1,fLine1.p2,fLine2.p2);
	r341 = GetVectorDir(fLine2.p1,fLine2.p2,fLine1.p1);
	r342 = GetVectorDir(fLine2.p1,fLine2.p2,fLine1.p2);

	if(r123 * r124 < 0 && r341 * r342 < 0) return 1; // 교차하는 경우

	if(r123 == 0 && r124 == 0) // 두 선분이 같은 방향일 경우
	{
		if(!(fLine2.p1.x > fLine1.p2.x || fLine1.p1.x > fLine2.p2.x))
			return 0;
		else
			return -1;
	}

	if(r123 == 0)
	{
		if(fLine1.p1.x <= fLine2.p1.x && fLine2.p1.x < fLine1.p2.x)
			return 0;
		else return -1;
	}

	if(r124 == 0)
	{
		if(fLine1.p1.x <= fLine2.p2.x && fLine2.p2.x < fLine1.p2.x)
			return 0;
		else return -1;
	}

	if(r341 == 0)
	{
		if(fLine2.p1.x <= fLine1.p1.x && fLine1.p1.x < fLine2.p2.x)
			return 0;
		else return -1;
	}
	
	if(r342 == 0)
	{
		if(fLine2.p1.x <= fLine1.p2.x && fLine1.p2.x < fLine2.p2.x)
			return 0;
		else return -1;
	}
	return -1;
}
int CheckIntersect(CdPoint fptStart,CdPoint fptEnd, CdPoint fptStart1,CdPoint fptEnd1)
{
	//C로 배우는 알고리즘,이재규,도처출판 세화,
	int r123,r124,r341,r342;

	if(fptStart.x > fptStart1.x)
	{
		swap(fptStart.x,fptStart1.x);
		swap(fptStart.y,fptStart1.y);
	}

	if(fptEnd.x > fptEnd1.x)
	{
		swap(fptEnd.x,fptEnd1.x);
		swap(fptEnd.y,fptEnd1.y);
	}

	r123 = GetVectorDir(fptStart,fptStart1,fptEnd);
	r124 = GetVectorDir(fptStart,fptStart1,fptEnd1);
	r341 = GetVectorDir(fptEnd,fptEnd1,fptStart);
	r342 = GetVectorDir(fptEnd,fptEnd1,fptStart1);

	if(r123 * r124 < 0 && r341 * r342 < 0) return 1; // 교차하는 경우

	if(r123 == 0 && r124 == 0) // 두 선분이 같은 방향일 경우
	{
		if(!(fptEnd.x > fptStart1.x ||fptStart.x > fptEnd1.x))
			return 0;
		else
			return -1;
	}

	if(r123 == 0)
	{
		if(fptStart.x <= fptEnd.x && fptEnd.x < fptStart1.x)
			return 0;
		else return -1;
	}

	if(r124 == 0)
	{
		if(fptStart.x <= fptEnd1.x && fptEnd1.x < fptStart1.x)
			return 0;
		else return -1;
	}

	if(r341 == 0)
	{
		if(fptEnd.x <= fptStart.x && fptStart.x < fptEnd1.x)
			return 0;
		else return -1;
	}
	
	if(r342 == 0)
	{
		if(fptEnd.x <= fptStart1.x && fptStart1.x < fptEnd1.x)
			return 0;
		else return -1;
	}
	return -1;
}
int CheckIntersect(DPOINT fptStart, DPOINT fptEnd, DPOINT fptStart1, DPOINT fptEnd1)
{
	//C로 배우는 알고리즘,이재규,도처출판 세화,
	int r123, r124, r341, r342;

	if (fptStart.x > fptStart1.x)
	{
		swap(fptStart.x, fptStart1.x);
		swap(fptStart.y, fptStart1.y);
	}

	if (fptEnd.x > fptEnd1.x)
	{
		swap(fptEnd.x, fptEnd1.x);
		swap(fptEnd.y, fptEnd1.y);
	}

	r123 = GetVectorDir(fptStart, fptStart1, fptEnd);
	r124 = GetVectorDir(fptStart, fptStart1, fptEnd1);
	r341 = GetVectorDir(fptEnd, fptEnd1, fptStart);
	r342 = GetVectorDir(fptEnd, fptEnd1, fptStart1);

	if (r123 * r124 < 0 && r341 * r342 < 0) return 1; // 교차하는 경우

	if (r123 == 0 && r124 == 0) // 두 선분이 같은 방향일 경우
	{
		if (!(fptEnd.x > fptStart1.x || fptStart.x > fptEnd1.x))
			return 0;
		else
			return -1;
	}

	if (r123 == 0)
	{
		if (fptStart.x <= fptEnd.x && fptEnd.x < fptStart1.x)
			return 0;
		else return -1;
	}

	if (r124 == 0)
	{
		if (fptStart.x <= fptEnd1.x && fptEnd1.x < fptStart1.x)
			return 0;
		else return -1;
	}

	if (r341 == 0)
	{
		if (fptEnd.x <= fptStart.x && fptStart.x < fptEnd1.x)
			return 0;
		else return -1;
	}

	if (r342 == 0)
	{
		if (fptEnd.x <= fptStart1.x && fptStart1.x < fptEnd1.x)
			return 0;
		else return -1;
	}
	return -1;
}
*/
// 두 선분이 교차하는지를 조사.
// 교차하면 1을 그렇지 않으면 -1을 리턴한다.
// 만약 한선분의 끝점이 다른 선분상에 존재하면 0을 리턴한다.
// 선분이 중첩되면 2를 리턴한다
int CheckIntersect(DLINE fLine1, DLINE fLine2)
{
	double x1 = fLine1.p1.x, x2 = fLine1.p2.x, x3 = fLine2.p1.x, x4 = fLine2.p2.x;
	double y1 = fLine1.p1.y, y2 = fLine1.p2.y, y3 = fLine2.p1.y, y4 = fLine2.p2.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		DPOINT fpt1, fpt2;
		return GetOverlapPointOnLine(fLine1, fLine2, fpt1, fpt2);
	}
	// Get the x and y 
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines 
	// 20200906 Modify
	//if (x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4))
	if ((x - min(x1, x2)) < -0.00000001 || (x - max(x1, x2)) > 0.00000001 || (x - min(x3, x4)) < -0.00000001 || (x - max(x3, x4)) > 0.00000001)
		return -1;

	//if (y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4))
	if ((y - min(y1, y2)) < -0.00000001 || (y - max(y1, y2)) > 0.00000001 || (y - min(y3, y4)) < -0.00000001 || (y - max(y3, y4)) > 0.00000001)
		return -1;

	if (x1 == x && y1 == y || x2 == x && y2 == y || x3 == x && y3 == y || x4 == x && y4 == y)
		return 0;

	return 1;
}
int CheckIntersect(CdPoint fptStart, CdPoint fptEnd, CdPoint fptStart1, CdPoint fptEnd1)
{
	double x1 = fptStart.x, x2 = fptEnd.x, x3 = fptStart1.x, x4 = fptEnd1.x;
	double y1 = fptStart.y, y2 = fptEnd.y, y3 = fptStart1.y, y4 = fptEnd1.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		CdPoint fpt1, fpt2;
		return GetOverlapPointOnLine(fptStart, fptEnd, fptStart1, fptEnd1, fpt1, fpt2);
	}
	// Get the x and y 
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines 
	//20200906 Modify
	//if (x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4))
	if ((x - min(x1, x2)) < -0.00000001 || (x - max(x1, x2)) > 0.00000001 || (x - min(x3, x4)) < -0.00000001 || (x - max(x3, x4)) > 0.00000001)
		return -1;

	//if (y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4))
	if ((y - min(y1, y2)) < -0.00000001 || (y - max(y1, y2)) > 0.00000001 || (y - min(y3, y4)) < -0.00000001 || (y - max(y3, y4)) > 0.00000001)
		return -1;

	if (x1 == x && y1 == y || x2 == x && y2 == y || x3 == x && y3 == y || x4 == x && y4 == y)
		return 0;

	return 1;
}
int CheckIntersect(DPOINT fptStart, DPOINT fptEnd, DPOINT fptStart1, DPOINT fptEnd1)
{
	double x1 = fptStart.x, x2 = fptEnd.x, x3 = fptStart1.x, x4 = fptEnd1.x;
	double y1 = fptStart.y, y2 = fptEnd.y, y3 = fptStart1.y, y4 = fptEnd1.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		DPOINT fpt1, fpt2;
		return GetOverlapPointOnLine(fptStart, fptEnd, fptStart1, fptEnd1, fpt1, fpt2);
	}

	// Get the x and y 
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines 
	// 20200906 Modify
	//if (x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4))
	if ((x - min(x1, x2)) < -0.00000001 || (x - max(x1, x2)) > 0.00000001 || (x - min(x3, x4)) < -0.00000001 || (x - max(x3, x4)) > 0.00000001)
		return -1;

	//if (y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4))
	if ((y - min(y1, y2)) < -0.00000001 || (y - max(y1, y2)) > 0.00000001 || (y - min(y3, y4)) < -0.00000001 || (y - max(y3, y4)) > 0.00000001)
		return -1;

	if (x1 == x && y1 == y || x2 == x && y2 == y || x3 == x && y3 == y || x4 == x && y4 == y)
		return 0;

	return 1;
}
BOOL GetIntersectPoint(CPoint fPt1, CPoint fPt2, CPoint fPt3, CPoint fPt4, CPoint &fPt)
{
	double t;
	double s;
	int under = (fPt4.y - fPt3.y)*(fPt2.x - fPt1.x) - (fPt4.x - fPt3.x)*(fPt2.y - fPt1.y);
	if (under == 0)
	{
		CPoint fpt1, fpt2;
		if (GetOverlapPointOnLine(fPt1, fPt2, fPt3, fPt4, fpt1, fpt2) == 1)
		{
			fPt = fpt1;
			return TRUE;
		}
		else
			return FALSE; // 두 선분은 평행하다.
	}

	double _t = (fPt4.x - fPt3.x)*(fPt1.y - fPt3.y) - (fPt4.y - fPt3.y)*(fPt1.x - fPt3.x);
	double _s = (fPt2.x - fPt1.x)*(fPt1.y - fPt3.y) - (fPt2.y - fPt1.y)*(fPt1.x - fPt3.x);

	t = _t / under;
	s = _s / under;

	if (t<0.0 || t>1.0 || s<0.0 || s>1.0)
		return FALSE; // 두 선분은 교차하지 않는다.

	if (_t == 0 && _s == 0)
	{
		if (fPt1.x == fPt3.x && fPt1.y == fPt3.y)
		{
			fPt = fPt1;
			return TRUE;
		}
		if (fPt1.x == fPt4.x && fPt1.y == fPt4.y)
		{
			fPt = fPt1;
			return TRUE;
		}
		if (fPt2.x == fPt3.x && fPt2.y == fPt3.y)
		{
			fPt = fPt2;
			return TRUE;
		}
		if (fPt2.x == fPt4.x && fPt2.y == fPt4.y)
		{
			fPt = fPt2;
			return TRUE;
		}

		return FALSE; // 두 선분은 동일한 선이다
	}
	fPt.x = fPt1.x + t * (double)(fPt2.x - fPt1.x);
	fPt.y = fPt1.y + t * (double)(fPt2.y - fPt1.y);

	return TRUE;
}
//// <======= 20190211 Modify =============================================
BOOL GetIntersectPoint(DPOINT fPt1,DPOINT fPt2,DPOINT fPt3,DPOINT fPt4,DPOINT &fPt)
{
	double t;
    double s; 
    double under = (fPt4.y-fPt3.y)*(fPt2.x-fPt1.x)-(fPt4.x-fPt3.x)*(fPt2.y-fPt1.y);
	if (under == 0)
	{
		DPOINT fpt1, fpt2;
		if (GetOverlapPointOnLine(fPt1, fPt2, fPt3, fPt4, fpt1, fpt2) == 1)
		{
			fPt = fpt1;
			return TRUE;
		}
		else
		return FALSE; // 두 선분은 평행하다.
	}

    double _t = (fPt4.x-fPt3.x)*(fPt1.y-fPt3.y) - (fPt4.y-fPt3.y)*(fPt1.x-fPt3.x);
    double _s = (fPt2.x-fPt1.x)*(fPt1.y-fPt3.y) - (fPt2.y-fPt1.y)*(fPt1.x-fPt3.x); 

    t = _t/under;
    s = _s/under; 

    if(t<0.0 || t>1.0 || s<0.0 || s>1.0)
		return FALSE; // 두 선분은 교차하지 않는다.

	if (_t == 0 && _s == 0)
	{
		if (fPt1.x == fPt3.x && fPt1.y == fPt3.y)
		{
			fPt = fPt1;
			return TRUE;
		}
		if (fPt1.x == fPt4.x && fPt1.y == fPt4.y)
		{
			fPt = fPt1;
			return TRUE;
		}
		if (fPt2.x == fPt3.x && fPt2.y == fPt3.y)
		{
			fPt = fPt2;
			return TRUE;
		}
		if (fPt2.x == fPt4.x && fPt2.y == fPt4.y)
		{
			fPt = fPt2;
			return TRUE;
		}
		
		return FALSE; // 두 선분은 동일한 선이다
	}
	fPt.x = fPt1.x + t * (double)(fPt2.x-fPt1.x);
    fPt.y = fPt1.y + t * (double)(fPt2.y-fPt1.y);

	return TRUE;
}

BOOL GetIntersectPoint(DPOINT3D fPt1,DPOINT3D fPt2,DPOINT3D fPt3,DPOINT3D fPt4,DPOINT3D &fPt)
{
	double t;
    double s; 
    double under = (fPt4.y-fPt3.y)*(fPt2.x-fPt1.x)-(fPt4.x-fPt3.x)*(fPt2.y-fPt1.y);
    if(under==0)
		return FALSE; // 두 선분은 평행하다.

    double _t = (fPt4.x-fPt3.x)*(fPt1.y-fPt3.y) - (fPt4.y-fPt3.y)*(fPt1.x-fPt3.x);
    double _s = (fPt2.x-fPt1.x)*(fPt1.y-fPt3.y) - (fPt2.y-fPt1.y)*(fPt1.x-fPt3.x); 

    t = _t/under;
    s = _s/under; 

    if(t<0.0 || t>1.0 || s<0.0 || s>1.0)
		return FALSE; // 두 선분은 교차하지 않는다.
    if(_t==0 && _s==0)
		return FALSE; // 두 선분은 동일한 선이다

	fPt.x = fPt1.x + t * (double)(fPt2.x-fPt1.x);
    fPt.y = fPt1.y + t * (double)(fPt2.y-fPt1.y);

	return TRUE;
}

BOOL GetIntersectPoint(CLINE fLine1, CLINE fLine2, CPoint &fPt)
{
	return GetIntersectPoint(fLine1.p1, fLine1.p2, fLine2.p1, fLine2.p2, fPt);
}
BOOL GetIntersectPoint(DLINE fLine1,DLINE fLine2,DPOINT &fPt)
{
	return GetIntersectPoint(fLine1.p1,fLine1.p2,fLine2.p1,fLine2.p2,fPt);
}

BOOL GetIntersectPoint(DLINE3D fLine1,DLINE3D fLine2,DPOINT3D &fPt)
{
	return GetIntersectPoint(fLine1.p1,fLine1.p2,fLine2.p1,fLine2.p2,fPt);
}
BOOL CheckPolygonLineIntersection(vector <CdPoint> &vecPolygonVertex, CdPoint LineStart, CdPoint LineEnd)
{
	int i;
	int nSize = (int)vecPolygonVertex.size();
	CdPoint stPoint;
	if (nSize < 3)
		return FALSE;
	for (i = 0; i < nSize - 1; i++)
	{
		if (CheckLineToLineIntersectionPoint(vecPolygonVertex[i], vecPolygonVertex[i + 1], LineStart, LineEnd, stPoint))
		{
			return TRUE;
		}
	}
	if (CheckLineToLineIntersectionPoint(vecPolygonVertex[nSize - 1], vecPolygonVertex[0], LineStart, LineEnd, stPoint))
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CheckPolygonLineIntersection(vector<DPOINT> &vecPolygonVertex, DPOINT LineStart, DPOINT LineEnd)
{
	int i;
	int size = (int)vecPolygonVertex.size();
	DPOINT stPoint;
	if (size < 3)
		return FALSE;

	for (i = 0; i < size - 1; i++)
	{
		if (CheckLineToLineIntersectionPoint(vecPolygonVertex[i], vecPolygonVertex[i + 1], LineStart, LineEnd, stPoint))
		{
			return TRUE;
		}
	}
	if (CheckLineToLineIntersectionPoint(vecPolygonVertex[size - 1], vecPolygonVertex[0], LineStart, LineEnd, stPoint))
	{
		return TRUE;
	}

	return FALSE;
}
void GetPolygonLineIntersection(vector <CdPoint> &vecPolygonVertex, CdPoint LineStart, CdPoint LineEnd, vector<CdPoint> &vecPoint)
{
	int i;
	int nSize = (int)vecPolygonVertex.size();
	CdPoint stPoint;
	if (nSize < 3)
		return;
	for (i = 0; i < nSize - 1; i++)
	{
		if (CheckLineToLineIntersectionPoint(vecPolygonVertex[i], vecPolygonVertex[i + 1], LineStart, LineEnd, stPoint))
		{
			vecPoint.push_back(stPoint);
		}
	}
	if (CheckLineToLineIntersectionPoint(vecPolygonVertex[nSize - 1], vecPolygonVertex[0], LineStart, LineEnd, stPoint))
	{
		vecPoint.push_back(stPoint);
	}
}
void GetPolygonLineIntersection(vector<DPOINT> &vecPolygonVertex, DPOINT LineStart, DPOINT LineEnd, vector<DPOINT> &vecPoint)
{
	int i;
	int size = (int)vecPolygonVertex.size();
	DPOINT stPoint;
	if(size<3)
		return;
	for(i=0;i<size-1;i++)
	{
		if(CheckLineToLineIntersectionPoint(vecPolygonVertex[i],vecPolygonVertex[i+1],LineStart,LineEnd,stPoint))
		{
			vecPoint.push_back(stPoint);
		}
	}
	if (vecPolygonVertex[size - 1].x != vecPolygonVertex[0].x || vecPolygonVertex[size - 1].y != vecPolygonVertex[0].y)
	{
		if (CheckLineToLineIntersectionPoint(vecPolygonVertex[size - 1], vecPolygonVertex[0], LineStart, LineEnd, stPoint))
	{
		vecPoint.push_back(stPoint);
	}
	}
}
void GetPolygonLineIntersection(const DPOINT *fptVertex, int nSize, DPOINT LineStart, DPOINT LineEnd, vector<DPOINT> &vecPoint)
{
	int i;
	DPOINT stPoint;
	if (nSize < 3)
	return;
	for (i = 0; i < nSize - 1; i++)
	{
		if (CheckLineToLineIntersectionPoint(fptVertex[i], fptVertex[i + 1], LineStart, LineEnd, stPoint))
		{
			vecPoint.push_back(stPoint);
		}
	}
	if (fptVertex[nSize - 1].x != fptVertex[0].x || fptVertex[nSize - 1].y != fptVertex[0].y)
	{
		if (CheckLineToLineIntersectionPoint(fptVertex[nSize - 1], fptVertex[0], LineStart, LineEnd, stPoint))
		{
			vecPoint.push_back(stPoint);
		}
	}
}

BOOL CheckLineToLineIntersectionPoint(CdPoint fptStart,CdPoint fptEnd, CdPoint LineStart,CdPoint LineEnd,CdPoint &GetPoint)
{
	double x1 = fptStart.x, x2 = fptEnd.x, x3 = LineStart.x, x4 = LineEnd.x;
	double y1 = fptStart.y, y2 = fptEnd.y, y3 = LineStart.y, y4 = LineEnd.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4); 

	// If d is zero, there is no intersection 
	if (d == 0)
	{
		CdPoint fpt1, fpt2;
		if (GetOverlapPointOnLine(fptStart, fptEnd, LineStart, LineEnd, fpt1, fpt2) == 1)
		{
			GetPoint = fpt1;
			return TRUE;
		}
		else
			return FALSE;
	}

	// Get the x and y 
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d; 
	double y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d; 
 
	// Check if the x and y coordinates are within both lines
	// 20200906 Modify
	//if ( x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4) ) 
	if ((x - min(x1, x2)) < -0.00000001 || (x - max(x1, x2)) > 0.00000001 || (x - min(x3, x4)) < -0.00000001 || (x - max(x3, x4)) > 0.00000001)
		return FALSE; 
 
	//if ( y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4) ) 
	if ((y - min(y1, y2)) < -0.00000001 || (y - max(y1, y2)) > 0.00000001 || (y - min(y3, y4)) < -0.00000001 || (y - max(y3, y4)) > 0.00000001)
		return FALSE; 
    
	// Return the point of intersection 
	GetPoint.x = x;
	GetPoint.y = y; 
	return TRUE; 
}
BOOL CheckLineToLineIntersectionPoint(DPOINT fptStart,DPOINT fptEnd, DPOINT LineStart,DPOINT LineEnd,DPOINT &GetPoint)
{
	double x1 = fptStart.x, x2 = fptEnd.x, x3 = LineStart.x, x4 = LineEnd.x; 
	double y1 = fptStart.y, y2 = fptEnd.y, y3 = LineStart.y, y4 = LineEnd.y;
	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4); 
    
	// If d is zero, there is no intersection 
	if (d == 0)
	{
		DPOINT fpt1, fpt2;
		if (GetOverlapPointOnLine(fptStart, fptEnd, LineStart, LineEnd, fpt1, fpt2) == 1)
		{
			GetPoint = fpt1;
			return TRUE;
		}
		else
			return FALSE;
	}

	// Get the x and y 
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4); 
	double x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d; 
	double y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d; 
 
	// Check if the x and y coordinates are within both lines 
	// 20200906 Modify
	//if (x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4) ) 
	if ((x - min(x1, x2)) < -0.00000001 || (x - max(x1, x2)) > 0.00000001 || (x - min(x3, x4)) < -0.00000001 || (x - max(x3, x4)) > 0.00000001)
		return FALSE; 
    
	//if ( y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4) ) 
	if ((y - min(y1, y2)) < -0.00000001 || (y - max(y1, y2)) > 0.00000001 || (y - min(y3, y4)) < -0.00000001 || (y - max(y3, y4)) > 0.00000001)
		return FALSE; 
    
	// Return the point of intersection 
	GetPoint.x = x;
	GetPoint.y = y; 
	return TRUE; 
}
BOOL CheckLineToLineIntersectionPointPlus(CdPoint fptStart, CdPoint fptEnd, CdPoint LineStart, CdPoint LineEnd, CdPoint &GetPoint)
{
	double  distAB, theCos, theSin, newX, ABpos;
	double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	Ax = fptStart.x;
	Ay = fptStart.y;
	Bx = fptEnd.x;
	By = fptEnd.y;
	Cx = LineStart.x;
	Cy = LineStart.y;
	Dx = LineEnd.x;
	Dy = LineEnd.y;
	//  Fail if either line segment is zero-length.
	if (Ax == Bx && Ay == By || Cx == Dx && Cy == Dy) return FALSE;

	//  Fail if the segments share an end-point.
	if (Ax == Cx && Ay == Cy || Bx == Cx && By == Cy
		|| Ax == Dx && Ay == Dy || Bx == Dx && By == Dy) {
		return FALSE;
	}


	//  (1) Translate the system so that point A is on the origin.
	Bx -= Ax; By -= Ay;
	Cx -= Ax; Cy -= Ay;
	Dx -= Ax; Dy -= Ay;

	//  Discover the length of segment A-B.
	distAB = sqrt(Bx*Bx + By*By);

	//  (2) Rotate the system so that point B is on the positive X axis.
	theCos = Bx / distAB;
	theSin = By / distAB;
	newX = Cx*theCos + Cy*theSin;
	Cy = Cy*theCos - Cx*theSin; Cx = newX;
	newX = Dx*theCos + Dy*theSin;
	Dy = Dy*theCos - Dx*theSin; Dx = newX;

	//  Fail if segment C-D doesn't cross line A-B.
	if (Cy < 0. && Dy < 0. || Cy >= 0. && Dy >= 0.) return FALSE;

	//  (3) Discover the position of the intersection point along line A-B.
	ABpos = Dx + (Cx - Dx)*Dy / (Dy - Cy);

	//  Fail if segment C-D crosses line A-B outside of segment A-B.
	if (ABpos<0. || ABpos>distAB) return FALSE;

	//  (4) Apply the discovered position to line A-B in the original coordinate system.
	GetPoint.x = Ax + ABpos*theCos;
	GetPoint.y = Ay + ABpos*theSin;

	//  Success.
	return TRUE;
}
BOOL CheckLineToLineIntersectionPointPlus(DPOINT fptStart,DPOINT fptEnd, DPOINT LineStart,DPOINT LineEnd,DPOINT &GetPoint)
{
	double  distAB, theCos, theSin, newX, ABpos ;
	double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy;
	Ax = fptStart.x;
	Ay = fptStart.y;
	Bx = fptEnd.x;
	By = fptEnd.y;
	Cx = LineStart.x;
	Cy = LineStart.y;
	Dx = LineEnd.x;
	Dy = LineEnd.y;
	//  Fail if either line segment is zero-length.
	if (Ax==Bx && Ay==By || Cx==Dx && Cy==Dy) return FALSE;

	//  Fail if the segments share an end-point.
	if (Ax==Cx && Ay==Cy || Bx==Cx && By==Cy
	||  Ax==Dx && Ay==Dy || Bx==Dx && By==Dy) {
	return FALSE; }


	//  (1) Translate the system so that point A is on the origin.
	Bx-=Ax; By-=Ay;
	Cx-=Ax; Cy-=Ay;
	Dx-=Ax; Dy-=Ay;

	//  Discover the length of segment A-B.
	distAB=sqrt(Bx*Bx+By*By);

	//  (2) Rotate the system so that point B is on the positive X axis.
	theCos=Bx/distAB;
	theSin=By/distAB;
	newX=Cx*theCos+Cy*theSin;
	Cy  =Cy*theCos-Cx*theSin; Cx=newX;
	newX=Dx*theCos+Dy*theSin;
	Dy  =Dy*theCos-Dx*theSin; Dx=newX;

	//  Fail if segment C-D doesn't cross line A-B.
	if (Cy<0. && Dy<0. || Cy>=0. && Dy>=0.) return FALSE;

	//  (3) Discover the position of the intersection point along line A-B.
	ABpos=Dx+(Cx-Dx)*Dy/(Dy-Cy);

	//  Fail if segment C-D crosses line A-B outside of segment A-B.
	if (ABpos<0. || ABpos>distAB) return FALSE;

	//  (4) Apply the discovered position to line A-B in the original coordinate system.
	GetPoint.x=Ax+ABpos*theCos;
	GetPoint.y=Ay+ABpos*theSin;

	//  Success.
	return TRUE; 
}

int ConvertInt(double dValue)
{
	if (dValue > 0)
		return int(dValue + 0.5);
	return int(dValue - 0.5);
}
int ConvertInt(float fValue)
{
	if (fValue > 0)
		return int(fValue + 0.5);
	return int(fValue - 0.5);
}
double SafeAcos(double x)
{
	if (x < -1.0) x = -1.0;
	else if (x > 1.0) x = 1.0;
	return acos(x);
}
double SafeAsin(double x)
{
	if (x < -1.0) x = -1.0;
	else if (x > 1.0) x = 1.0;
	return asin(x);
}

int OrganizePolygonVertices(vector <DPOINT> &vecVertices, double dGap)
{
	int i, nNumOfVertices;
	double dAngle;
	vector <DPOINT>::iterator it;

	nNumOfVertices = (int)vecVertices.size();
	if (vecVertices.at(0).x == vecVertices.at(nNumOfVertices - 1).x && vecVertices.at(0).y == vecVertices.at(nNumOfVertices - 1).y)
	{
		it = vecVertices.begin();
		vecVertices.erase(it + nNumOfVertices - 1);
	}

	if ((int)vecVertices.size() < 4)
		return (int)vecVertices.size();

	for (i = 1; i < (int)vecVertices.size() - 1; i++)
	{
		dAngle = GetInteriorAngle(vecVertices.at(i - 1), vecVertices.at(i), vecVertices.at(i + 1));
		if (dAngle < 0.0)
			dAngle *= -1.0;
		if (dAngle < dGap || fabs(dAngle - 180.0) < dGap)
		{
			it = vecVertices.begin();
			vecVertices.erase(it + i);
			i--;
		}
	}

	nNumOfVertices = (int)vecVertices.size();
	if (nNumOfVertices < 4)
		return nNumOfVertices;

	i = nNumOfVertices - 1;
	dAngle = GetInteriorAngle(vecVertices.at(i - 1), vecVertices.at(i), vecVertices.at(0));
	if (dAngle < 0.0)
		dAngle *= -1.0;
	if (dAngle < dGap || fabs(dAngle - 180.0) < dGap)
	{
		it = vecVertices.begin();
		vecVertices.erase(it + i);
	}

	nNumOfVertices = (int)vecVertices.size();
	dAngle = GetInteriorAngle(vecVertices.at(nNumOfVertices - 1), vecVertices.at(0), vecVertices.at(1));
	if (dAngle < 0.0)
		dAngle *= -1.0;
	if (dAngle < dGap || fabs(dAngle - 180.0) < dGap)
	{
		it = vecVertices.begin();
		vecVertices.erase(it);
	}

	nNumOfVertices = (int)vecVertices.size();
	if (vecVertices.at(0).x != vecVertices.at(nNumOfVertices - 1).x || vecVertices.at(0).y != vecVertices.at(nNumOfVertices - 1).y)
	{
		vecVertices.push_back(vecVertices.at(0));
		nNumOfVertices = (int)vecVertices.size();
	}

	return nNumOfVertices;
}