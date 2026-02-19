//////////////////////////////////////////////////////////////
//      GeoDataType.h Ver 1.0                              //
//              Corp   : GIGAVIS                            //
//															//
//////////////////////////////////////////////////////////////

#if !defined(_GEODATATYPE_H__INCLUDED_)
#define _GEODATATYPE_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//const double PI = atan(1.0)*4;
#ifndef PI
	#define PI 3.14159265358979323846
#endif

//opencv header file include
#include <opencv2/opencv.hpp>


//// Barcode Text Draw
#define BARCODE_CHAR_WIDTH_FACTOR 2.9139092715			
#define BARCODE_TEXT_HEIGHT_FACTOR 0.333335
#define BARCODE_TEXT_GAP_FACTOR 0.166665
#define BARCODE_TEXT_THICKNESS_FACTOR 0.04
#define BARCODE_MIN_BAR_WIDTH	0.2032

const double DEG2RAD = PI/180.0;
const double RAD2DEG = 180.0/PI;
const float SIN45 = sinf(PI*0.25);
const float COS45 = cosf(PI*0.25);


// modify by khc 2014,4,24
struct Matrix3by3{
	// Constructor.
	// Parameters: see member variables.
	Matrix3by3(double pv0 =1.0, double pv1=0.0, double pv2=0.0,double pv3=0.0, double pv4=1.0, double pv5=0.0,double pv6=0.0, double pv7=0.0, double pv8=1.0)
	{
		v0 = pv0;
		v1 = pv1;
		v2 = pv2;

		v3 = pv3;
		v4 = pv4;
		v5 = pv5;

		v6 = pv6;
		v7 = pv7;
		v8 = pv8;
	}
	double v0, v1, v2;
	double v3, v4, v5;
	double v6, v7, v8;
};
typedef CArray<Matrix3by3, Matrix3by3> CArMatrix3by3;

class GInterPolation;

// The iPOINT structure defines the x- and y-coordinates of a point.
typedef struct tagiPOINT {
	tagiPOINT(int px = 0, int py = 0)
	{
		x = px;
		y = py;
	}
	int x; // Specifies the x-coordinate of a point.
	int y; // Specifies the y-coordinate of a point.
} IPOINT;
typedef CArray<IPOINT, IPOINT> CArintPoint;

// The IRECT structure defines the Left-Bottom and Right-Top coordinates of a point.
typedef struct tagiRECT {
	// Constructor.
	// Parameters: see member variables.
	int left; // Specifies the X1-coordinate of a Left-Bottom point.
	int bottom; // Specifies the Y1-coordinate of a Left-Bottom point.
	int right; // Specifies the X1-coordinate of a Right-Top point.
	int top; // Specifies the Y1-coordinate of a Right-Top point.
}IRECT;

// The IMG_RECT structure defines the Start X-Y and End X-Y coordinates of a point.
typedef struct tagImageRECT {
	// Constructor.
	// Parameters: see member variables.
	int nStX; // Specifies the X-coordinate of a Left-top point.
	int nStY; // Specifies the Y-coordinate of a Left-top point.
	int nEdX; // Specifies the X-coordinate of a Right-Bottom point.
	int nEdY; // Specifies the Y-coordinate of a Right-Bottom point.
}IMG_RECT;

////////////////////////////////////////////////////////////////////////// use camera pmcl type
#undef MAX_GRAB_BUFFER_ARR_NUM
#define MAX_GRAB_BUFFER_ARR_NUM  5

//typedef struct
//{
//	MIL_ID  MilImageGrab;
//	CCriticalSection AreaGrabCriticalSection;
//} HookDataStruct;
//////////////////////////////////////////////////////////////////////////


// The DPOINT structure defines the x- and y-coordinates of a point.
typedef struct tagfPOINT {
	tagfPOINT(float px = 0.0, float py = 0.0)
	{
		x = px;
		y = py;
	}
   float x; // Specifies the x-coordinate of a point.
   float y; // Specifies the y-coordinate of a point.
} FPOINT;




typedef CArray<FPOINT, FPOINT> CArFPoint;

typedef struct tagROUTE {
	tagROUTE(FPOINT pt1 = FPOINT(0, 0), unsigned char chLevel1 = 0)
	{
		pt = pt1;
		chLevel = chLevel1;
	}
	FPOINT pt;
	unsigned char chLevel;
} ROUTE;

// The DPOINT structure defines the x- and y-coordinates of a point.
typedef struct tagdPOINT {
	tagdPOINT(double px = 0.0, double py = 0.0)
	{
		x = px;
		y = py;
	}
   double x; // Specifies the x-coordinate of a point.
   double y; // Specifies the y-coordinate of a point.
} DPOINT;

typedef struct tagdPOINT3D {
   double x; // Specifies the x-coordinate of a point.
   double y; // Specifies the y-coordinate of a point.
   double z; // Specifies the z-coordinate of a point.
   
//    //130702 LGH ADD THIS PARAM
//    double r; // Color RED 0~1.0
//    double g; // Color GREEN 0~1.0
//   double b; // Color BLUE 0~1.0
   
} DPOINT3D;


typedef struct tagnPOINT3D {
	int x; // Specifies the x-coordinate of a point.
	int y; // Specifies the y-coordinate of a point.
	int z; // Specifies the z-coordinate of a point.

			  //    //130702 LGH ADD THIS PARAM
			  //    double r; // Color RED 0~1.0
			  //    double g; // Color GREEN 0~1.0
			  //   double b; // Color BLUE 0~1.0

} NPOINT3D;

// The DSIZE structure specifies the width and height of a rectangle. 
typedef struct tagdSIZE {
    double cx; // Specifies the x-extent when a function returns. 
    double cy; // Specifies the y-extent when a function returns. 
}DSIZE;

typedef struct tagfSIZE {
	float cx; // Specifies the x-extent when a function returns. 
	float cy; // Specifies the y-extent when a function returns. 
}FSIZE;

// The DSIZE structure specifies the width and height of a rectangle. 
typedef struct tagdSIZE3D {
    double cx; // Specifies the x-extent when a function returns. 
    double cy; // Specifies the y-extent when a function returns. 
    double cz; // Specifies the z-extent when a function returns. 
}DSIZE3D;

typedef struct tagcLINE {
	CPoint p1;	// Specifies the x,y-coordinate of a line.
	CPoint p2;	 // Specifies the x,y-coordinate of a line.
} CLINE;
// The DPOINT structure defines start and end of the x- and y-coordinates of a line.
typedef struct tagdLINE {
   DPOINT p1;	// Specifies the x,y-coordinate of a line.
   DPOINT p2;	 // Specifies the x,y-coordinate of a line.
} DLINE;

typedef struct tagfLINE {
	FPOINT p1;	// Specifies the x,y-coordinate of a line.
	FPOINT p2;	 // Specifies the x,y-coordinate of a line.
} FLINE;

//////////////////////////////////////////////////////////////////JCH

typedef struct tagdLINEROUTE {
	FPOINT p1;	// Specifies the x,y-coordinate of a line.
	FPOINT p2;	 // Specifies the x,y-coordinate of a line.
	unsigned char chLevel;
} LINE_ROUTE;
// The DPOINT structure defines start and end of the x- and y-coordinates of a line.
typedef struct tagdLINE3D {
   DPOINT3D p1; // Specifies the x,y-coordinate of a line.
   DPOINT3D p2;	 // Specifies the x,y-coordinate of a line.
} DLINE3D;

// The DRECT structure defines the coordinates of the upper-left and 
// lower-right corners of a rectangle.
typedef struct tagdRECT {
   double left; // Specifies the x-coordinate of the upper-left corner of a rectangle.
   double bottom; // Specifies the y-coordinate of the upper-left corner of a rectangle.
   double right; // Specifies the x-coordinate of the lower-right corner of a rectangle.
   double top; // Specifies the y-coordinate of the lower-right corner of a rectangle.
}DRECT,*LPCDRECT;

// The DRECT structure defines the Left-Bottom and Right-Top coordinates of a point.
typedef struct tagfRECT {
	// Constructor.
	// Parameters: see member variables.
	float left; // Specifies the X1-coordinate of a Left-Bottom point.
	float bottom; // Specifies the Y1-coordinate of a Left-Bottom point.
	float right; // Specifies the X1-coordinate of a Right-Top point.
	float top; // Specifies the Y1-coordinate of a Right-Top point.
}FRECT, *LPCFRECT;

// The FQUAD structure defines the coordinates of the upper-left and 
// lower-right corners of a quadrilateral.
typedef struct tagdQUAD {
   DPOINT lefttop; // Specifies the x,y-coordinate of the upper-left corner of a quadrilateral.
   DPOINT righttop; // Specifies the x,y-coordinate of the upper-right corner of a quadrilateral.
   DPOINT rightbottom; // Specifies the x,y-coordinate of the lower-right corner of a quadrilateral.
   DPOINT leftbottom; // Specifies the x,y-coordinate of the lower-left corner of a quadrilateral.
}DQUAD,*LPCDQUAD;

typedef struct tagdQUAD3D {
   DPOINT3D lefttop;	// Specifies the x,y-coordinate of the upper-left corner of a quadrilateral in 3d.
   DPOINT3D righttop;	// Specifies the x,y-coordinate of the upper-right corner of a quadrilateral in 3d.
   DPOINT3D rightbottom; // Specifies the x,y-coordinate of the lower-right corner of a quadrilateral in 3d.
   DPOINT3D leftbottom; // Specifies the x,y-coordinate of the lower-left corner of a quadrilateral in 3d.
}DQUAD3D,*LPCDQUAD3D;



typedef struct tagLINE_WIDTH_AND_ANGLE {
	int nAngle;
	float fLineWidth;
}LINE_WIDTH_AND_ANGLE;


typedef struct tagDEFECT_FAIL_INFO {
	int nType;
	int nArea;
	float fWidth;
}DEFECT_FAIL_INFO;

typedef struct tagOPEN_GL_PIECE_INFO {
	BOOL bOrigin;
	DRECT frtRect;
}OPEN_GL_PIECE_INFO;


typedef struct tagLINE_QUAD_MATCHING {
	cv::Point pt1;
	cv::Point pt2;
	DQUAD stQuad;
}LINE_QUAD_MATCHING;


class CfPoint;
class CdPoint;
class CdPoint3D;
class CdSize;
class CfSize;
class CdSize3D;
class CdLine;
class CdLine3D;
class CdRect;
class CfRect;
class CdQuad;
class CdQuad3D;

class CfPoint : public tagfPOINT  
{
public:
	CfPoint();
	CfPoint(float initfX, float initfY);
//	CfPoint(FPOINT initfPt);
	CfPoint(DWORD dwPoint);
	virtual ~CfPoint();

	void	Offset(float fXOffset,float fYOffset);
	void	Offset(FPOINT fPoint);
	CfPoint Round( FPOINT fPoint, int nPos = 3);

	BOOL    operator ==(FPOINT fPoint) const; // Nonzero if the points are equal; otherwise 0.
	BOOL    operator !=(FPOINT fPoint) const; // Nonzero if the points are not equal; otherwise 0.

	void	operator +=(FPOINT fPoint);
	void	operator -=(FPOINT fPoint);
	
	CfPoint operator +(FPOINT fPoint ) const;
	CfPoint operator -(FPOINT fPoint ) const;
	CfPoint operator -() const;
};

class CdPoint : public tagdPOINT  
{
public:
	CdPoint();
	CdPoint(double initfX, double initfY);
	CdPoint(DPOINT initfPt);
	CdPoint(DSIZE initfSize);
	CdPoint(DWORD dwPoint);
	virtual ~CdPoint();

	void	Offset(double fXOffset,double fYOffset);
	void	Offset(DPOINT fPoint);
	void	Offset(DSIZE fSize);
	CdPoint Round( CdPoint fPoint, int nPos = 3);

	BOOL    operator ==(DPOINT fPoint) const; // Nonzero if the points are equal; otherwise 0.
	BOOL    operator !=(DPOINT fPoint) const; // Nonzero if the points are not equal; otherwise 0.

	void	operator +=(DSIZE  fSize);
	void	operator +=(DPOINT fPoint);
	void	operator -=(DSIZE  fSize);
	void	operator -=(DPOINT fPoint);
	
	CdPoint operator +(DSIZE fSize ) const;
	CdPoint operator +(DPOINT fPoint ) const;
	CdRect operator +( const DRECT* lpfRect ) const;

	CdSize operator -(DPOINT fPoint ) const;
	CdPoint operator -(DSIZE fSize ) const;
//	CdPoint operator -(DPOINT fPoint ) const; 본 함수는 CdSize에 선언됨.
	CdRect operator -(const DRECT* lpfRect ) const;
	CdPoint operator -() const;
};

class CdPoint3D : public tagdPOINT3D  
{
public:
	CdPoint3D();
	CdPoint3D(double initfX, double initfY, double initfZ);
	CdPoint3D(DPOINT3D initfPt);
	virtual ~CdPoint3D();

	void	Offset(double fXOffset,double fYOffset,double fZOffset);
	void	Offset(DPOINT3D fPoint);
	CdPoint3D Round( CdPoint3D fPoint, int nPos = 3);

	BOOL    operator ==(DPOINT3D fPoint) const; // Nonzero if the points are equal; otherwise 0.
	BOOL    operator !=(DPOINT3D fPoint) const; // Nonzero if the points are not equal; otherwise 0.

	void	operator +=(DPOINT3D fPoint);
	void	operator -=(DPOINT3D fPoint);
	
	CdPoint3D operator +(DPOINT3D fPoint ) const;
	CdPoint3D operator -(DPOINT3D fPoint ) const;

	//130703 LGH ADD START
	CdPoint3D(CdPoint3D& vt);
	CdPoint3D operator + (CdPoint3D& fPoint);
	void operator = (CdPoint3D& fPoint);
	CdPoint3D operator - (CdPoint3D& fPoint);
	CdPoint3D operator / (float div);
	CdPoint3D operator * (CdPoint3D& fDivison);
	CdPoint3D operator * (double dDivison);
	void Normalize();
	double Magnitude();
	//ADD END

};

class CdSize : public tagdSIZE  
{
public:
	CdSize();
	CdSize(double initfCX,double initfCY);
	CdSize(DSIZE initfSize);
	CdSize(DPOINT initfPt);
	CdSize(DWORD dwfSize);
	virtual ~CdSize();

	BOOL operator ==(DSIZE fSize) const; // Checks for equality between two sizes. Returns nonzero if the sizes are equal, otherwize 0.
	BOOL operator !=(DSIZE fSize) const; // Checks for inequality between two sizes. Returns nonzero if the sizes are not equal, otherwise 0.
	void operator +=(DSIZE fSize); // Adds a size to this CdSize.
	void operator -=(DSIZE fSize); // Subtracts a size from this CdSize.
	CdSize operator +(DSIZE fSize) const; // This operation adds two CSize values.
	CdPoint operator +(DPOINT fPoint ) const; // The cx and cy members of this CSize value are added to the x and y data members of the POINT value
//	CdRect operator +(const DRECT* lpfRect ) const;

	CdSize operator -(DSIZE fSize) const;
	CdPoint operator -(DPOINT fPoint) const;
//	CdRect operator -(const DRECT* lpfRect ) const;
	CdSize operator -()const;
};


class CfSize : public tagfSIZE
{
public:
	CfSize();
	CfSize(float initfCX, float initfCY);
	CfSize(FSIZE initfSize);
	CfSize(FPOINT initfPt);
	CfSize(DWORD dwfSize);
	virtual ~CfSize();

	BOOL operator ==(FSIZE fSize) const; // Checks for equality between two sizes. Returns nonzero if the sizes are equal, otherwize 0.
	BOOL operator !=(FSIZE fSize) const; // Checks for inequality between two sizes. Returns nonzero if the sizes are not equal, otherwise 0.
	void operator +=(FSIZE fSize); // Adds a size to this CfSize.
	void operator -=(FSIZE fSize); // Subtracts a size from this CfSize.
	CfSize operator +(FSIZE fSize) const; // This operation adds two CSize values.
	CfPoint operator +(FPOINT fPoint) const; // The cx and cy members of this CSize value are added to the x and y data members of the POINT value
											 //	CdRect operator +(const DRECT* lpfRect ) const;

	CfSize operator -(FSIZE fSize) const;
	CfPoint operator -(FPOINT fPoint) const;
	//	CdRect operator -(const DRECT* lpfRect ) const;
	CfSize operator -()const;
};

class CdSize3D : public tagdSIZE3D  
{
public:
	CdSize3D();
	CdSize3D(double initfCX,double initfCY,double initfCZ);
	CdSize3D(DSIZE3D initfSize);
	CdSize3D(DPOINT3D initfPt);
	virtual ~CdSize3D();

	BOOL operator ==(DSIZE3D fSize) const; // Checks for equality between two sizes. Returns nonzero if the sizes are equal, otherwize 0.
	BOOL operator !=(DSIZE3D fSize) const; // Checks for inequality between two sizes. Returns nonzero if the sizes are not equal, otherwise 0.
	void operator +=(DSIZE3D fSize); // Adds a size to this CdSize.
	void operator -=(DSIZE3D fSize); // Subtracts a size from this CdSize.
	CdSize3D operator +(DSIZE3D fSize) const; // This operation adds two CSize values.
	CdPoint3D operator +(DPOINT3D fPoint ) const; // The cx and cy members of this CSize value are added to the x and y data members of the POINT value
//	CdRect operator +(const DRECT* lpfRect ) const;

	CdSize3D operator -(DSIZE3D fSize) const;
	CdPoint3D operator -(DPOINT3D fPoint) const;
//	CdRect operator -(const DRECT* lpfRect ) const;
	CdSize3D operator -()const;
};

class CdLine : public tagdLINE
{
public:
	CdLine();
	CdLine(DPOINT start,DPOINT end);
	CdLine(double sx,double sy,double ex,double ey);
	virtual ~CdLine();
	double Length();
	double Angle();
	CdPoint CenterPoint(void);

};

class CfLGrid : public tagdLINE
{
public:
	double m_fStartX, m_fStartY, m_fPitchX, m_fPitchY, m_fSpeed, m_fRepRate;
	int m_nCols, m_nRows;

public:
	CfLGrid();
	CfLGrid(DPOINT start, DPOINT end);
	CfLGrid(double sx, double sy, double ex, double ey);
	virtual ~CfLGrid();
	double Length();
	double Angle();
	CdPoint CenterPoint(void);
	void Set(double fStartX, double fStartY, double fPitchX, double fPitchY, int nCols, int nRows, double fSpeed, double fRepRate);
};


class CfArc : public tagdLINE
{
public:
	CdPoint m_fptCenter;
	double m_fRadius, m_fStartAngle, m_fArcAngle, m_fSpotSize, m_fSpeed, m_fRepRate;
	int m_nDir;

public:
	CfArc();
	CfArc(DPOINT start, DPOINT end);
	CfArc(double sx, double sy, double ex, double ey);
	virtual ~CfArc();
	double Length();
	double Angle();
	void Set(CdPoint fptCenter, double fRadius, double fStartAngle, double fArcAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir = 1);
};

class CfCircle : public tagdLINE
{
public:
	CdPoint m_fptCenter;
	double m_fRadius, m_fStartAngle, m_fSpotSize, m_fSpeed, m_fRepRate;
	int m_nDir;

public:
	CfCircle();
	CfCircle(DPOINT start, DPOINT end);
	CfCircle(double sx, double sy, double ex, double ey);
	virtual ~CfCircle();
	double Length();
	double Angle();
	void Set(CdPoint fptCenter, double fRadius, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir = 1);
};

class CfTrepan : public tagdLINE
{
public:
	CdPoint m_fptCenter;
	double m_fOuterDiameter, m_fInnerDiameter, m_fStartAngle, m_fSpotSize, m_fSpeed, m_fRepRate;
	int m_nDir;

public:
	CfTrepan();
	CfTrepan(DPOINT start, DPOINT end);
	CfTrepan(double sx, double sy, double ex, double ey);
	virtual ~CfTrepan();
	double Length();
	double Angle();
	void Set(CdPoint fptCenter, double fOuterDiameter, double fInnerDiameter, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir = 1);
};

class CfSpiral : public tagdLINE
{
public:
	CdPoint m_fptCenter;
	double m_fOuterDiameter, m_fInnerDiameter, m_fStartAngle, m_fRadialPitch, m_fSpotSize, m_fSpeed, m_fRepRate;
	int m_nDir;
	BOOL m_bLastCircle;

public:
	CfSpiral();
	CfSpiral(DPOINT start, DPOINT end);
	CfSpiral(double sx, double sy, double ex, double ey);
	virtual ~CfSpiral();
	double Length();
	double Angle();
	void Set(CdPoint fptCenter, double fOuterDiameter, double fInnerDiameter, double fRadialPitch, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate, int nDir = 1, BOOL bLastCircle = FALSE);
};

class CfSpiralCircle : public tagdLINE
{
public:
	CdPoint m_fptCenter;
	double m_fOuterDiameter, m_fStartAngle, m_fRadialPitch, m_fSpotSize, m_fSpeed, m_fRepRate;

public:
	CfSpiralCircle();
	CfSpiralCircle(DPOINT start, DPOINT end);
	CfSpiralCircle(double sx, double sy, double ex, double ey);
	virtual ~CfSpiralCircle();
	double Length();
	double Angle();
	void Set(CdPoint fptCenter, double fOuterDiameter, double fRadialPitch, double fStartAngle, double fSpotSize, double fSpeed, double fRepRate);
};

class CdLine3D : public tagdLINE3D
{
public:
	CdLine3D();
	CdLine3D(DPOINT3D start,DPOINT3D end);
	CdLine3D(double sx,double sy,double sz,double ex,double ey,double ez);
	virtual ~CdLine3D();
	double Length();
	CdPoint3D CenterPoint(void);
};


class CdRect : public tagdRECT   
{
public:
	CdRect();
	CdRect(double left, double top, double right, double bottom);
	virtual ~CdRect();
	double Width();
	double Height();
	CdSize Size();
	CdPoint TopLeft();
	CdPoint BottomRight();
	CdPoint CenterPoint();
	BOOL IsRectEmpty(); // Determines whether CRect is empty. A rectangle is empty if the width and/or height are 0 or negative. Differs from IsRectNull, which determines whether all coordinates of the rectangle are zero.
	BOOL IsRectNull(); // Determines whether the top, left, bottom, and right values of CRect are all equal to 0.
	BOOL PtInRect(CdPoint fPt); // A point is within CRect if it lies on or within all four sides.
	void SetRect(double x1,double y1,double x2,double y2);
	void SetRectEmpty(); // Makes CdRect a null rectangle by setting all coordinates to zero
	void CopyRect(LPCDRECT lpSrcfRect); // Copies the lpSrcfRect rectangle into CdRect
	BOOL EqualRect(LPCDRECT lpfRect); // Nonzero if the two rectangles have the same top, left, bottom, and right values; otherwise 0.
	void InflateRect(double x,double y);
	void InflateRect(DSIZE fSize);
	void InflateRect(LPCDRECT lpfRect);
	void InflateRect(double l,double t,double r,double b);
	void DeflateRect(double x,double y);
	void DeflateRect(DSIZE fSize);
	void DeflateRect(LPCDRECT lpfRect);
	void DeflateRect(double l,double t,double r,double b);
	void NormalizeRect(); // Normalizes CdRect so that both the height and width are positive
	void OffsetRect(double x,double y);
	void OffsetRect(DPOINT fPoint);
	void OffsetRect(DSIZE fSize);
	BOOL SubtractRect(LPCDRECT lpfRectSrc1, LPCDRECT lpfRectSrc2 );
	BOOL IntersectRect(LPCDRECT lpfRect1, LPCDRECT lpfRect2);
	BOOL UnionRect(LPCDRECT lpfRect1, LPCDRECT lpfRect2);

	double m_fWidth, m_fHeight;
};

class CfRect : public tagfRECT
{
public:
	CfRect();
	CfRect(float left, float top, float right, float bottom);
	virtual ~CfRect();
	float Width();
	float Height();
	CfSize Size();
	CfPoint TopLeft();
	CfPoint BottomRight();
	CfPoint CenterPoint();
	BOOL IsRectEmpty(); // Determines whether CRect is empty. A rectangle is empty if the width and/or height are 0 or negative. Differs from IsRectNull, which determines whether all coordinates of the rectangle are zero.
	BOOL IsRectNull(); // Determines whether the top, left, bottom, and right values of CRect are all equal to 0.
	BOOL PtInRect(CfPoint fPt); // A point is within CRect if it lies on or within all four sides.
	void SetRect(float x1, float y1, float x2, float y2);
	void SetRectEmpty(); // Makes CdRect a null rectangle by setting all coordinates to zero
	void CopyRect(LPCFRECT lpSrcfRect); // Copies the lpSrcfRect rectangle into CdRect
	BOOL EqualRect(LPCFRECT lpfRect); // Nonzero if the two rectangles have the same top, left, bottom, and right values; otherwise 0.
	void InflateRect(float x, float y);
	void InflateRect(FSIZE fSize);
	void InflateRect(LPCFRECT lpfRect);
	void InflateRect(float l, float t, float r, float b);
	void DeflateRect(float x, float y);
	void DeflateRect(FSIZE fSize);
	void DeflateRect(LPCFRECT lpfRect);
	void DeflateRect(float l, float t, float r, float b);
	void NormalizeRect(); // Normalizes CdRect so that both the height and width are positive
	void OffsetRect(float x, float y);
	void OffsetRect(FPOINT fPoint);
	void OffsetRect(FSIZE fSize);
	BOOL SubtractRect(LPCFRECT lpfRectSrc1, LPCFRECT lpfRectSrc2);
	BOOL IntersectRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2);
	BOOL UnionRect(LPCFRECT lpfRect1, LPCFRECT lpfRect2);

	float m_fWidth, m_fHeight;
};

class CdQuad : public tagdQUAD 
{
public:
	CdQuad();
	CdQuad(DPOINT fptLT, DPOINT fptRT, DPOINT fptRB, DPOINT fptLB);
	CdQuad(DRECT rect);
	CdQuad(double ltx,double lty,double rtx,double rty,double rbx,double rby,double lbx,double lby);
	virtual ~CdQuad();
	void OffsetQuad(double x,double y);
	void OffsetQuad(DPOINT fPoint);
	void OffsetQuad(DSIZE fSize);
	CdPoint TopLeft();
	CdPoint TopRight();
	CdPoint BottomRight();
	CdPoint BottomLeft();
	CdPoint CenterPoint();
	BOOL DiagonalPoint(DPOINT &fPoint);
	CdPoint CentralPoint();
	BOOL IsQuadEmpty();
	BOOL IsQuadNull();
	BOOL PtInQuad(DPOINT fPt);
	void SetQuad(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4);
	void SetQuadEmpty();
	void CopyQuad(LPCDQUAD lpSrcfQuad); // Copies the lpSrcfQuad quadrilateral into CdQuad
	BOOL EqualQuad(LPCDQUAD lpfQuad); // Nonzero if the two quadrilateralS have the same top, left, bottom, and right values; otherwise 0.
};

struct MeshTriangle
{
	CdPoint3D Pt1;
	CdPoint3D Pt2;
	CdPoint3D Pt3;
	CdPoint3D fNrm;
};

class GInterPolation  //현재는 Bilinear 차후 tri kri등..넣을것임
{
public:
	int m_nInterPolationMode; 
	CdPoint3D m_fptBLP1;							
	CdPoint3D m_fptBLP2;
	CdPoint3D m_fptBLP3;
	CdPoint3D m_fptBLP4;
	BOOL m_bCaculated;
	void SetInterPolationMode(int mode);
	BOOL CalculateInterPolation(CdPoint3D LeftBottom,CdPoint3D LeftTop,CdPoint3D RightTop,CdPoint3D RightBottom,CdPoint3D fpt,double& dResult);
	BOOL CalculateInterPolation(CdQuad3D fQuad,CdPoint3D fpt,double& dResult);
	BOOL GetBilinearIntersectPoint(CdPoint3D &fpt1,CdPoint3D &fpt2,CdPoint3D &fpt3,CdPoint3D &fpt4);
	BOOL GetBilinearIntersectPoint3D(CdQuad3D Qaud,CdPoint3D fCurPos,double& ResultHeight,CdPoint3D &fpt1,CdPoint3D &fpt2,CdPoint3D &fpt3,CdPoint3D &fpt4);
};

class CdQuad3D : public tagdQUAD3D , public GInterPolation
{
public:
	CdQuad3D();
	CdQuad3D(DPOINT3D fptLT, DPOINT3D fptRT, DPOINT3D fptRB, DPOINT3D fptLB);
	CdQuad3D(double ltx,double lty,double ltz,double rtx,double rty,double rtz,double rbx,double rby,double rbz,double lbx,double lby,double lbz);
	CdQuad3D(CdPoint3D fptLT, CdPoint3D fptRT, CdPoint3D fptRB, CdPoint3D fptLB); //130708 lgh add
	
	// 하나의 쿼드에는 4개의 삼각형을 일단 만든다...
	MeshTriangle m_QuadTriangles[4];
	void MakeQuadricTriangle(); 
	CdPoint3D m_CenterPoint3D;
	// 하나의 쿼드에는 좌상좌하우하우상을 하나의 포인터 배열로 관리하겠다.
	CdPoint3D m_QuadArray[4]; 
	void MakeQuadricArray(BOOL SetValue);

	virtual ~CdQuad3D();
	void OffsetQuad(double x,double y,double z);
	void OffsetQuad(DPOINT3D fPoint);
	CdPoint3D TopLeft();
	CdPoint3D TopRight();
	CdPoint3D BottomRight();
	CdPoint3D BottomLeft();
	CdPoint3D CenterPoint();
	BOOL DiagonalPoint(DPOINT3D &fPoint);
	BOOL IsQuadEmpty();
	BOOL IsQuadNull();
	BOOL PtInQuad(DPOINT3D fPt);
	void SetQuad(double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3,double x4,double y4,double z4);
	void SetQuadEmpty();
	void CopyQuad(LPCDQUAD3D lpSrcfQuad); // Copies the lpSrcfQuad quadrilateral into CdQuad
	BOOL EqualQuad(LPCDQUAD3D lpfQuad); // Nonzero if the two quadrilateralS have the same top, left, bottom, and right values; otherwise 0.
};

#endif // !defined(_GEODATATYPE_H__INCLUDED_)
