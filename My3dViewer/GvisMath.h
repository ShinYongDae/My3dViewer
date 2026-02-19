// GvisMath.h: interface for the CGvisMath class.
// 본클래스는 CPoint,CSize,CRect를 float, double형으로 확장한 클래스임.
//////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
////                                 GvisMath.h Ver 1.5                              ////
////												                               ////
////                               Corp   : GIGAVIS                                ////
////																			   ////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GVISMATH_H__B8E4F205_0089_4CD3_A7D4_EB5CEF56B11D__INCLUDED_)
#define AFX_GVISMATH_H__B8E4F205_0089_4CD3_A7D4_EB5CEF56B11D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GlobalDefineAOR.h"
#include "GlobalDefine.h"
#include "GeoDataType.h"
#include <vector>
using namespace std;


typedef CArray<CDefData, CDefData> CArDef;
typedef CArray<CPoint, CPoint> CArPt;						
typedef CArray<CdPoint, CdPoint> CArfPt;
typedef CArray<CdRect, CdRect> CArfRect;
typedef CArray<CdQuad, CdQuad> CArfQuad;
typedef CArray<CdPoint3D, CdPoint3D> CArfPt3D;
typedef CArray<CdQuad3D, CdQuad3D> CArfQuad3D;

class GPickFunction
{
	public:
	GPickFunction();
	int GetNearestPtIndex(CdPoint3D* CurrfptArray,int PtNum,CdPoint3D fWorldPos);
	int	 GetNearestQuadIndex(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos,int Flag);
	BOOL GetNearestQuad3D(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos,CdQuad3D& GetQaud);
	BOOL GetNearestFptInQuad3D(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos,CdPoint3D &ResultFpt);
	int GetNearestFptIndexInQuad3D(CArfQuad3D& CurrQaud3DArray,CdPoint3D fWorldPos);
	int GetNearestPointIndexArr(CArfPt3D* Arr,CdPoint3D fpt);

	void EnablePickPtArray(CdPoint3D *cfPoints=NULL,int nCnt=NULL);
	void EnablePickPtArray(CArfPt3D* CArrPt3d,int PtNum);
	void EnablePickQuad3D(CArfQuad3D* CurrQaud3DArray);

	void DisablePickQuad3D();
	void DisablePickPtArray();

	void EnableVertexModify();
	void DisableVertexModify();

	int GetPickedArrIndex(int PickMode);
	BOOL GetPickedCfPoint3D(CdPoint3D& Result);
	BOOL GetPickedQAUD3D(CdQuad3D& Result);
	BOOL isDraging();

public:
	CdPoint3D *m_PickingData;
	CArfQuad3D *m_PickingData_Qaud;
	CArfPt3D *m_PickArr3D;
	int m_nPickQaudID;
	int m_nPickingMax;
	int m_nPickNum;
	CdPoint3D m_PickedPoint;

	BOOL m_bPickCarFptMode;
	BOOL m_bPickQuadMode; //픽킹 여부 
	BOOL m_bPickArrayMode;
	BOOL m_bVertexMod; // 버텍스 변경 여부 
	BOOL m_bPickCfPoint3DarrayMode;
	CCriticalSection m_VetedModCriticalSection;


	BOOL m_PickingDrag;

	CdPoint3D m_PickPoint;
	CdQuad3D m_PickedQuad;

	BOOL m_bPickLimitMode; //lgh add
	BOOL m_bPickInRegion;
	CdPoint3D m_dPickRangeMinimum;
	CdPoint3D m_dPickRangeMaximum;
	BOOL bOldPickStatus;

	void EnablePickRange(CdPoint3D fpfMinimum,CdPoint3D fptMaximum);
	void DisablePickRange();
	BOOL isPickRangeLimit();

	void UpdateMousePostion(UINT nActCode,CdPoint3D fptMousePos);
};

//+++++++++++++++++++++++++++++++++
// global math function

double D2R(double fDeg);
double R2D(double fRadian);
double mm2um(double fmm);
double um2mm(double fum);

////////// 20160712 sch ======================>
float ConvertInchToMetric(float fValue);
float ConvertMetricToInch(float fValue);
double ConvertInchToMetric(double fValue);
double ConvertMetricToInch(double fValue);
DPOINT ConvertPointInchToMetric(DPOINT &fpt);
DPOINT ConvertPointMetricToInch(DPOINT &fpt);
DRECT ConvertExtentInchToMetric(DRECT &fExtent);
DRECT ConvertExtentMetricToInch(DRECT &fExtent);
///// <=======================================

void TranslatePoint(DPOINT &p, double dX, double dY);
void TranslateRect(DRECT &R, double dX, double dY);
void GetRotateParameter(double dAng, double *dCosineVal, double *dSineVal);
void RotatePoint(DPOINT &fptRef,DPOINT &fptCenter,double fRotAngle);
void RotateRect(DRECT &fRect, DPOINT &fCenter, double fAng);
BOOL GetScaleRect(DRECT *rect, double fScaleX, double fScaleY);

void MirrorVerticalRect(DRECT &fRect, double vAxis);
void MirrorHorizontalRect(DRECT &fRect, double hAxis);
void MirrorHorizontalPoint(DPOINT &p, double hAxis);
void MirrorVerticalPoint(DPOINT &p, double vAxis);

void AdjustExtentByPoint(DRECT &Extent, const DPOINT &pt);
void AdjustExtentByRect(DRECT &Extent, const DRECT &rect);
DRECT GetMaxExtentByRect(const DRECT &rect1, const DRECT &rect2, double dX = 0.0, double dY = 0.0);

void SortInteger(vector <int> &vecInteger, BOOL bDecending = FALSE);
static BOOL IntegerDecendingSortfunction(int &a, int &b);

void SortFloat(vector <float> &vecFloat, BOOL bDecending = FALSE);
static BOOL FloatDecendingSortfunction(float &a, float &b);

void SortDouble(vector <double> &vecDouble, BOOL bDecending = FALSE);
static BOOL DoubleDecendingSortfunction(double &a, double &b);

void SortPoint(int nSortType, vector <DPOINT> &vecPointList, double dGap = 0.0);
void PointDecendingSortX(vector <DPOINT> &vecPointList, int nStart, int nEnd);
void PointDecendingSortY(vector <DPOINT> &vecPointList, int nStart, int nEnd);
void PointAscendingSortX(vector <DPOINT> &vecPointList, int nStart, int nEnd);
void PointAscendingSortY(vector <DPOINT> &vecPointList, int nStart, int nEnd);
static BOOL PointDecendingSortfunctionX(DPOINT &a, DPOINT &b);
static BOOL PointDecendingSortfunctionY(DPOINT &a, DPOINT &b);
static BOOL PointAscendingSortfunctionX(DPOINT &a, DPOINT &b);
static BOOL PointAscendingSortfunctionY(DPOINT &a, DPOINT &b);

void SortRectX(vector <DRECT> &rectExtent, int nStart, int nEnd);
void SortRectY(vector <DRECT> &rectExtent, int nStart, int nEnd);
void SwapRect(vector <DRECT> &rectExtent, int nIndex1, int nIndex2);
/*
void SortCircleObj(int nSortType, vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, double dGap = -1.0);
void CircleObjDecendingSortX(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd);
void CircleObjDecendingSortY(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd);
void CircleObjAscendingSortX(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd);
void CircleObjAscendingSortY(vector <CIRCLE_OBJECT_INFO> &vecCircleObjList, int nStart, int nEnd);
static BOOL CircleObjDecendingSortfunctionX(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b);
static BOOL CircleObjDecendingSortfunctionY(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b);
static BOOL CircleObjAscendingSortfunctionX(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b);
static BOOL CircleObjAscendingSortfunctionY(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b);

static BOOL CircleObjSizeDecendingSortfunction(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b);
static BOOL CircleObjSizeAscendingSortfunction(CIRCLE_OBJECT_INFO &a, CIRCLE_OBJECT_INFO &b);
*/
BOOL CheckPolygonDirection(vector <DPOINT> vecPoint, int &nDir);					//// 20200111 Add

BOOL CheckPointInRect(const DRECT &fRect, const double x, const double y);
BOOL CheckPointInRect(const DRECT &fRect, const DPOINT &pt);
//BOOL CheckPointInRect(const CdRect &fRect, const DPOINT &pt);

BOOL CheckRectInRect(DRECT *Inner, DRECT *Outer);
BOOL CheckRectInRect(CdRect *Inner, CdRect *Outer);
BOOL CheckUnionRect(DRECT *fRect1, DRECT *fRect2);

BOOL CheckEqualRect(DRECT *fRect1, DRECT *fRect2);
BOOL CheckEqualRect(CdRect *fRect1, CdRect *fRect2);
BOOL CheckRectSize(DRECT *fRect1, DRECT *fRect2);
BOOL CheckRectSize(CdRect *fRect1, CdRect *fRect2);
BOOL CheckRectTypePolygon(const DPOINT *fptVert, int nSize);

BOOL IsPerpendicular(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint);
DPOINT ArcCenter(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint);
double ArcRadius(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint);
double ArcAngle(CdPoint startPoint,CdPoint endPoint,CdPoint centerPoint);
double ArcAngle(CdPoint startPoint,CdPoint centerPoint,double fArcLength);
double ArcLength(CdPoint startPoint,CdPoint middlePoint,CdPoint endPoint);

BOOL CheckNumericCharacter(CString strCharactor, BOOL bUnsignedInt = TRUE);					//// 20200318 move 
//BOOL CheckArcRound(GLfloat cx, GLfloat cy, GLfloat r, GLfloat start_angle, GLfloat arc_angle, GLfloat width,int dir,double x,double y);
BOOL CheckPointInMyOval(double fCx, double fCy, double fWidth, double fHeight,double x,double y);
BOOL CheckPointInMyPolygonNSide(int n, double cX, double cY, double d, double ang,double x,double y); 
BOOL CheckPointInMyConcavePolygon(DPOINT *fPoint,int nNumberOfVertex,double x,double y);
BOOL CheckPointInMyConcavePolygon(CdPoint3D *fPoint,int nNumberOfVertex,double x,double y);
BOOL CheckPointInMyConcavePolygon(vector <DPOINT> &fPoint,double x,double y);
BOOL CheckPointInMyThermalSquareRound(double fCx, double fCy, double fOutDia, double fInDia, double fAngle, int nNumOfSpoke, double fSpokeGap,double x,double y);
BOOL CheckPointInMyThermalSquareOpen(double fCx, double fCy, double fOutDia, double fInDia, double fAngle, int nNumOfSpoke, double fSpokeGap,double x,double y);
BOOL CheckPointInMyThermalSquare(double fCx, double fCy, double fOutDia, double fInDia, double fAngle, int nNumOfSpoke, double fSpokeGap,double x,double y);
BOOL CheckPointInMyThermalRoundSquare(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke,  double fSpokeGap,double x,double y);
BOOL CheckPointInMyThermalRoundOpen(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke, double fSpokeGap, double fAirGap,double x,double y);
BOOL CheckPointInMyThermalRound(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke, double fSpokeGap, double fAirGap,double x,double y);
BOOL CheckPointInMyThermal(double fCx, double fCy, double fOutDia, double fInDia,double fAngle, int nNumOfSpoke,  double fSpokeGap,double x,double y);
BOOL CheckPointInMyOctagon(double fCx, double fCy, double fwidth, double fheight, double fRadius,double x,double y);
BOOL CheckPointInMyMoire(double fCx, double fCy, double fRingWidth, double fRingGap, int nNumRing, double fLineWidth, double fLineLength, double fLineAngle,double x,double y);
BOOL CheckPointInMyOvalHalf(double fCx, double fCy, double fWidth, double fHeight,double x,double y);
BOOL CheckPointInMyButterflySquare(double fCx, double fCy, double fWidth,double x,double y);
BOOL CheckPointInMyButterfly(double fCx, double fCy, double fWidth,double x,double y);
BOOL CheckPointInMyHexagonVer(double fCx, double fCy, double fHexagonWidth, double fHexagonHeight, double fCornerSize,double x,double y);
BOOL CheckPointInMyHexagonHor(double fCx, double fCy, double fHexagonWidth, double fHexagonHeight, double fCornerSize,double x,double y);
BOOL CheckPointInMyTriangle(double fCx, double fCy, double fTriangleBase, double fTriangleHeight,double x,double y);
BOOL CheckPointInMyDiamond(double fCx, double fCy, double fRectWidth, double ffRectHeight,double x,double y);
BOOL CheckPointInMyDonutSquare(double fCx, double fCy, double fDmo, double fDmi,double x,double y);
BOOL CheckPointInMyEllipse(double fCx, double fCy, double fWidth, double fHeight,double x,double y);
BOOL CheckPointInMyCircle(double fOX, double fOY, double R, UINT nSeg,double x,double y);
BOOL CheckPointInMyDonut(double fCx, double fCy, double fDmo, double fDmi,double x,double y);
BOOL CheckPointInMyArc(double fSx, double fSy, double fEx, double fEy, double fCX, double fCY, double fWidth, int nDir,double x,double y);	
BOOL CheckPointInMyRectChamfferd(double fCx, double fCy, double fWidth, double fHeight, double fRadius, int nCorners,double x,double y);	
BOOL CheckPointInMyRectRound(double fCx, double fCy, double fWidth, double fHeight, double fRadius, int nCorners,double x,double y);	
BOOL CheckPointInMyRectCenter(double fSx, double fSy, double fLineWidth, double fLineHeight, double fAngle,double x,double y);

BOOL CheckPointInMyRect(double fSx, double fSy, double fEx, double fEy,double x,double y);
BOOL CheckPointInMyRect(double fSx, double fSy, double fLineWidth, double fLineHeight, double fAngle,double x,double y);

BOOL CheckPointInMyLineRect(double fSx, double fSy, double fEx, double fEy, double fLineWidth, double fLineHeight,double x,double y);
BOOL CheckPointInMyLineSquare(double fSx, double fSy, double fEx, double fEy, double fLineWidth,double x,double y);
BOOL CheckPointInMyLineRound(double fSx, double fSy, double fEx, double fEy, double fLineWidth,double x,double y);
BOOL CheckPointInMyLine(double fSx, double fSy, double fEx, double fEy, double fLineWidth,double x,double y);
BOOL CheckPointInArc(double fSx, double fSy, double fEx, double fEy, double fCx, double fCy, int nDir,double x,double y);
BOOL CheckPointInArc(double cx,double cy,double radius,double startAngle,double endAngle,double x,double y);
BOOL CheckPointInArc(double cx,double cy,double radius,double startAngle,double arcAngle,int nDir,double x,double y);
BOOL CheckPointInCircle(double cx,double cy,double radius,double x,double y);
BOOL CheckPointInCircle(const DPOINT &cp, const double radius, double x, double y);
BOOL CheckPointInCircle(const DPOINT &cp, const double radius, const DPOINT &pt);
BOOL CheckPointInEllipse(double cx, double cy, double fWidth, double fHeight,double x,double y);
BOOL CheckPointInQuad(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double x,double y);
BOOL CheckPointInQuad(DQUAD fptQuad, double x, double y);
BOOL CheckPointInQuad(vector<DPOINT> &vecPt,double x,double y);
BOOL CheckPointInQuad(const DPOINT *fptVert,double x,double y);
BOOL CheckPointInTriangle(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y);

BOOL CheckPointInPolygon(double p[], int polySides, double x, double y);
BOOL CheckPointInPolygon(const DPOINT *fptVert,int nCount,double x,double y);
BOOL IsConvex(vector<DPOINT> &vecPt);
BOOL IsConvex(const DPOINT *fptVert,int nCount);

BOOL CheckPointInPolygonFont(vector<FPOINT> &vecTest,double x,double y);

int GetOverlapPointOnLine(DLINE fLine1, DLINE fLine2, DPOINT &fpt1, DPOINT &fpt2);
int GetOverlapPointOnLine(CdPoint fptStart, CdPoint fptEnd, CdPoint fptStart1, CdPoint fptEnd1, CdPoint &fpt1, CdPoint &fpt2);
int GetOverlapPointOnLine(DPOINT fptStart, DPOINT fptEnd, DPOINT fptStart1, DPOINT fptEnd1, DPOINT &fpt1, DPOINT &fpt2);
int GetOverlapPointOnLine(CPoint fptStart, CPoint fptEnd, CPoint fptStart1, CPoint fptEnd1, CPoint &fpt1, CPoint &fpt2);

void GetCornerPoint(double x1,double y1,double x2,double y2,double x3,double y3,double *x0,double *y0);
void GetPolygonClipping(vector<DPOINT> &vecPolygonVertex,vector<DPOINT> &vecLine,vector<DPOINT> &vecPoint);
int GetVectorDir(double ax, double ay, double bx, double by, double cx, double cy);
int GetVectorDir(DPOINT start,DPOINT middle,DPOINT end);
int GetVectorDir(DPOINT3D start,DPOINT3D middle,DPOINT3D end);
int GetVectorDir(CdPoint start,CdPoint middle,CdPoint end);
double GetInteriorAngle(double x1,double y1,double x2,double y2,double x3,double y3);
double GetInteriorAngle(DPOINT start,DPOINT middle,DPOINT end);
double GetInteriorAngle(DPOINT3D start,DPOINT3D middle,DPOINT3D end);
double GetInteriorAngle(CdPoint start,CdPoint middle,CdPoint end);
double GetLineAngle(double x1, double y1, double x2, double y2);
double GetLineAngle(DPOINT start, DPOINT end);
double GetLineAngle(DPOINT3D start, DPOINT3D end);
double GetLineAngle(CdPoint start, CdPoint end);
int CheckIntersect(DLINE fLine1,DLINE fLine2);
int CheckIntersect(CdPoint fptStart,CdPoint fptEnd, CdPoint fptStart1,CdPoint fptEnd1);
BOOL GetIntersectPoint(CPoint fPt1, CPoint fPt2, CPoint fPt3, CPoint fPt4, CPoint &fPt);
BOOL GetIntersectPoint(DPOINT fPt1,DPOINT fPt2,DPOINT fPt3,DPOINT fPt4,DPOINT &fPt);
BOOL GetIntersectPoint(DPOINT3D fPt1,DPOINT3D fPt2,DPOINT3D fPt3,DPOINT3D fPt4,DPOINT3D &fPt);
BOOL GetIntersectPoint(CLINE fLine1, CLINE fLine2, CPoint &fPt);
BOOL GetIntersectPoint(DLINE fLine1,DLINE fLine2,DPOINT &fPt);
BOOL GetIntersectPoint(DLINE3D fLine1,DLINE3D fLine2,DPOINT3D &fPt);
double GetDistance(int x1, int y1, int x2, int y2);
double GetDistance(float x1, float y1, float x2, float y2);
double GetDistance(double x1, double y1, double x2, double y2);
double GetDistance(CPoint FirstPoint, CPoint SecondPoint);
double GetDistance(DPOINT FirstPoint, DPOINT SecondPoint);
double GetDistance(CdPoint3D FirstPoint, CdPoint3D SecondPoint); // 두점 사이의 거리를 얻는다 
double GetDistance(CdPoint FirstPoint, CdPoint SecondPoint); // 두점 사이의 거리를 얻는다 
double GetDistancePointToLine(CdPoint fpt1, CdPoint fpt2, double x, double y);	// 임의의 Point에서 두점에 의한 Line과의 최소거리 
double GetDistancePointToLine(DPOINT fpt1, DPOINT fpt2, double x, double y);	// 임의의 Point에서 두점에 의한 Line과의 최소거리 
double GetDistancePointToLine(CPoint fpt1, CPoint fpt2, int x, int y);	// 임의의 Point에서 두점에 의한 Line과의 최소거리 
void GetOrthogonalPointOfLineAndPoint(DPOINT start, DPOINT end, double x, double y, DPOINT &fpt);
BOOL CheckLineToLineIntersectionPoint(CdPoint fptStart, CdPoint fptEnd, CdPoint LineStart, CdPoint LineEnd, CdPoint &GetPoint);
BOOL CheckLineToLineIntersectionPoint(DPOINT fptStart, DPOINT fptEnd, DPOINT LineStart, DPOINT LineEnd, DPOINT &GetPoint);
BOOL CheckPolygonLineIntersection(vector <CdPoint> &vecPolygonVertex, CdPoint LineStart, CdPoint LineEnd);
BOOL CheckPolygonLineIntersection(vector<DPOINT> &vecPolygonVertex, DPOINT LineStart, DPOINT LineEnd);
void GetPolygonLineIntersection(vector <CdPoint> &vecPolygonVertex, CdPoint LineStart, CdPoint LineEnd, vector<CdPoint> &vecPoint);
void GetPolygonLineIntersection(vector<DPOINT> &vecPolygonVertex, DPOINT LineStart, DPOINT LineEnd, vector<DPOINT> &vecPoint);
void GetPolygonLineIntersection(const DPOINT *fptVertex, int nSize, DPOINT LineStart, DPOINT LineEnd, vector<DPOINT> &vecPoint);
BOOL CheckLineToLineIntersectionPointPlus(CdPoint fptStart, CdPoint fptEnd, CdPoint LineStart, CdPoint LineEnd, CdPoint &GetPoint);
BOOL CheckLineToLineIntersectionPointPlus(DPOINT fptStart, DPOINT fptEnd, DPOINT LineStart, DPOINT LineEnd, DPOINT &GetPoint);

int ConvertInt(double dValue);
int ConvertInt(float fValue);
double SafeAcos(double x);
double SafeAsin(double x);

int OrganizePolygonVertices(vector <DPOINT> &vecVertices, double dGap = 0.000001);
#endif // !defined(AFX_GVISMATH_H__B8E4F205_0089_4CD3_A7D4_EB5CEF56B11D__INCLUDED_)
