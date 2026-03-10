#pragma once

//opencv header file include
#include <opencv2/opencv.hpp>

#include "Entities.h"

class Matching
{
private:
	float m_fMin, m_fMax; // [mm]
	float m_fRealMin, m_fRealMax;
	float m_fScaleX,m_fScaleY;
	float m_fMatchTheta;
	float m_fMatchErode;
	cv::Point m_ptMatchLoc;
	double m_dMatchScore;

public:
	//3D Calibration
	AllArea_3D m_3DAllArea;
	BOOL m_bISDefectValue;
	BOOL m_bISResinValue;
	BOOL m_bISCutValue;
	float m_fTotalMin;
	//float Findscale2(cv::Mat matFlu, cv::Mat mat3D);
	//cv::Mat AdjustFLUMatchingTheta(cv::Mat matFlu, cv::Mat mat3D, float fScaleX, float fScaleY, float fThetaMax, float fThetaMin, float fThetaStep); // 형광을 돌리고 형광의 스케일을 조정한다.
	////

	float m_fResinDamage, m_fSpaceGap, m_fCudamage, m_fDamageSpec, m_fSpaceGapSpec, m_fCuDamageSpec;

	cv::Point m_ptMaxDamage;
	cv::Point m_ptMaxCuDamage;
	vector<cv::Point> m_vecThinningPt;
	cv::Mat m_matLineWidth;
	
	double m_dAverage, m_dAverageUpper, m_dAverageLower;
	double m_dStdev;

	BOOL m_bNotDefact;
	BOOL m_bCuDamage, m_bResinGap, m_bResinDamage;

	void ApplyMinMax(cv::Mat &mat3D);
	cv::Mat ApplyGrayScale(cv::Mat mat3D);
	cv::Mat ApplyGrayScaleAuto(cv::Mat mat3D);
	cv::Mat ApplyConvertImage(cv::Mat mat3D, float fMin, float fMax);
	cv::Mat ApplyConvertImageAuto(cv::Mat mat3D);
	cv::Point GetMatchPt();
	
	

	/////20190320 JCH 
	void GetRealMinMax(float &fRealMin, float &fRealMax);
	void GetMinMax(float &fMin, float &fMax);
	void GetAverage(float &fLower, float &fUpper);

	void SetMatchScole(double dScole);
	double GetMatchSdScore();
	float GetMatchTheta();
	float GetMatchErode();


	
	//cv::Mat GetCutImg(cv::Mat matImg, double dScaleXY, cv::Point ptStart);
	
	void SetMatchPt(cv::Point pt);
	//void MatchingExactLocation(cv::Mat matFlu , cv::Mat mat3D,cv::Point pt, double dMatchingRange, float fScaleXY, float fTheta);
	vector<std::vector<cv::Point> > m_ProcessContours;
	vector<cv::Vec4i> m_ProcessHierarchy;
	
	//void CalcAllArea(cv::Mat &matCheckResin, cv::Mat &matCheckDefect, cv::Mat &matCheckCu);
	//void FindAutoProfileLine(cv::Mat& DefectArea, cv::Mat& ResinArea);
	//void CalculCuResin(cv::Mat matDefect);
	//void CalculJudgment(cv::Mat matDefect, cv::Mat matResin);
	void CalcSortLine(cv::Mat matLineImg, cv::Point pt);
	//float GetSpaceGap();
	//float GetCuDamage(cv::Mat matDefect, cv::Mat matResin);
	
	//cv::Mat GetNormalize3DImg();
	int GetThinningSize(cv::Mat matThinning);
	/////////////////////////
	//20190930 JCH 
	void ApplyMinMaxAuto(cv::Mat &mat3D);
	void ApplyRangeAuto(cv::Mat &mat3D);
	void ApplyUpperRange(cv::Mat &mat3D);
	void ApplyLowerRange(cv::Mat &mat3D);



	////
	Matching();
	~Matching();
};
