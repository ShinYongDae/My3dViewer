#include "stdafx.h"
#include "Matching.h"
#include "GvisMath.h"

void Matching::SetMatchScole(double dScole)
{
	m_dMatchScore = dScole;
}

double Matching::GetMatchSdScore()
{
	return m_dMatchScore;
}



Matching::Matching()
{
	m_fRealMin = m_fMin = -20;
	m_fRealMax = m_fMax = 20;
	m_fScaleX = m_fScaleY = 4.26;
	m_fMatchTheta = 0;
	m_ptMatchLoc = cv::Point(0, 0);
	m_bResinGap = FALSE;
	m_bResinDamage = FALSE;
	m_bCuDamage = FALSE;
	m_bISDefectValue = FALSE;
	m_bISResinValue = FALSE;
	m_bISCutValue = FALSE;
	m_fTotalMin = 9999;
	m_dMatchScore = 0;
}


Matching::~Matching()
{

}



cv::Mat Matching::ApplyConvertImageAuto(cv::Mat mat3D)
{
	m_fRealMin = 999999;
	m_fRealMax = -999999;
	m_dAverage = 0;
	m_dStdev = 0;
	cv::Mat dst;
	ApplyMinMaxAuto(mat3D);
	dst = ApplyGrayScaleAuto(mat3D);

	return dst;
}

cv::Mat Matching::ApplyConvertImage(cv::Mat mat3D, float fMin, float fMax)
{
	m_fRealMin = 999999;
	m_fRealMax = -999999;
	m_fMin = fMin;
	m_fMax = fMax;
	m_dAverage = 0;
	m_dStdev = 0;
	cv::Mat dst;
	ApplyMinMax(mat3D);
	dst = ApplyGrayScale(mat3D);




	return dst;
}


void Matching::ApplyMinMaxAuto(cv::Mat &mat3D)
{

	m_fRealMax = -99999;
	m_fRealMin = 99999;

	double dAvg = 0;
	int nPixels = 0;
	double dStdev = 0;
	double dVar = 0;

	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 

			dAvg += fColor;
			nPixels++;

			if (fColor >= m_fRealMax)
			{
				m_fRealMax = fColor;
			}
			else if (fColor <= m_fRealMin)
			{
				m_fRealMin = fColor;
			}
		}
	}

	double dDiff = m_fRealMax - m_fRealMin;


	dAvg /= nPixels;
	m_dAverage = dAvg;
	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 

			dVar += (dAvg - fColor)*(dAvg - fColor);
		}
	}
	dStdev = sqrt(dVar / nPixels);
	m_dStdev = dStdev;

}



void Matching::ApplyMinMax(cv::Mat &mat3D)
{

	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 
			if (fColor > m_fRealMax)
			{
				m_fRealMax = fColor;
			}
			else if (fColor < m_fRealMin)
			{
				m_fRealMin = fColor;
			}
		}
	}

	double dDiff = m_fRealMax - m_fRealMin;

	if (fabs(dDiff > (m_fMax - m_fMin)))
	{
		int qwe = 0;
	}

	double dAvg = 0;
	int nPixels = 0;
	double dStdev = 0;
	double dVar = 0;

	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 

			dAvg += fColor;
			nPixels++;
		}
	}

	dAvg /= nPixels;
	m_dAverage = dAvg;
	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 

			dVar +=  (dAvg-fColor)*(dAvg - fColor);
		}
	}
	dStdev = sqrt(dVar/ nPixels);
	m_dStdev = dStdev;

	//튀는 값들은 낮은값을 갖는다?

	//for (int j = 0; j < mat3D.rows; j++)
	//{
	//	for (int i = 0; i < mat3D.cols; i++)
	//	{
	//		float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 

	//		if (fabs(fColor - dAvg) > dStdev * 3)
	//		{
	//			fColor = dAvg;
	//		}


	//		mat3D.at<float>(j, i) = fColor;
	//	}
	//}
	m_fRealMax = -99999;
	m_fRealMin = 99999;
	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);// 한 픽셀식 검사 
			if (fColor > m_fRealMax)
			{
				m_fRealMax = fColor;
			}
			else if (fColor < m_fRealMin)
			{
				m_fRealMin = fColor;
			}
		}
	}



	
}



cv::Mat Matching::ApplyGrayScale(cv::Mat mat3D)
{
	cv::Mat dst(mat3D.rows, mat3D.cols, CV_8UC1);

	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);


			int nValue = 255 - ConvertInt((fColor - m_fMin) / (m_fMax - m_fMin) * 255.0);
			if (nValue < 0)
			{
				nValue = 0;
			}
			if (nValue > 255)
			{
				nValue = 255;
			}
			dst.at<unsigned char>(j, i) = nValue;
		}
	}
	return dst;
}

cv::Mat Matching::ApplyGrayScaleAuto(cv::Mat mat3D)
{
	cv::Mat dst(mat3D.rows, mat3D.cols, CV_8UC1);

	for (int j = 0; j < mat3D.rows; j++)
	{
		for (int i = 0; i < mat3D.cols; i++)
		{
			float fColor = mat3D.at<float>(j, i);
			int nValue = 255 - ConvertInt((fColor - m_fRealMin) / (m_fRealMax - m_fRealMin) * 255.0);
			if (nValue < 0)
			{
				nValue = 0;
			}
			else if (nValue > 255)
			{
				nValue = 255;
			}
			dst.at<unsigned char>(j, i) = nValue;
		}
	}
	return dst;
}

cv::Point Matching::GetMatchPt()
{
	return m_ptMatchLoc;
}
void Matching::GetRealMinMax(float &fRealMin, float &fRealMax)
{
	fRealMin = m_fRealMin;
	fRealMax = m_fRealMax;
}

//cv::Mat Matching::AdjustFLUMatchingTheta(cv::Mat matFlu, cv::Mat mat3D, float fScaleX, float fScaleY, float fThetaMax, float fThetaMin, float fThetaStep)
//{
//	
//	m_fScaleX = fScaleX;
//	m_fScaleY = fScaleY;
//
//	cv::Mat mat3DGray, mat3DBin;
//	cv::Mat mat3DBinResize = cv::Mat(mat3D.rows, mat3D.cols, CV_8UC1);
//	cv::Mat matFluBin,matResizeFlu, matFluBinRotation;
//	cv::Mat matRotation, mat3DBinRotation, matResult, matFluResult;
//	cv::Point ptMinLoc, ptMaxLoc;
//	cv::Size szModel, szResize;
//
//
//	szResize.width = ConvertInt(matFlu.cols * m_fScaleX) ;
//	szResize.height = ConvertInt(matFlu.rows * m_fScaleY) ;
//	double dMinVal, dMaxVal, dScore = 0, value;
//
//	normalize(mat3D, mat3DGray, 0, 255, cv::NORM_MINMAX, CV_8UC1);
//	cv::threshold(mat3DGray, mat3DBin, 0, 255, cv::THRESH_BINARY_INV  | cv::THRESH_OTSU );
//	cv::threshold(matFlu, matFluBin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
//	cv::resize(matFluBin, matResizeFlu, szResize);
//
//
//
//
//	szModel.width = mat3DBinResize.cols;
//	szModel.height = mat3DBinResize.rows;
//	if (szModel.width % 2 == 1)
//	{
//		szModel.width++;
//	}
//	if (szModel.height % 2 == 1)
//	{
//		szModel.height++;
//	}
//	m_ptMatchLoc = cv::Point(0, 0);
//	int iMethodSearch = CV_TM_CCORR_NORMED;
//	for (float fTheta = fThetaMin; fTheta <= fThetaMax; fTheta += fThetaStep)
//	{
//		matRotation = cv::getRotationMatrix2D(cv::Point2f((float)matResizeFlu.cols / 2.0f, (float)matResizeFlu.rows / 2.0f), fTheta, 1);
//		warpAffine(matResizeFlu, matFluBinRotation, matRotation, cv::Size(matResizeFlu.cols, matResizeFlu.rows));
//		//matModel = matFluBinRotation(cv::Rect(matFluBinRotation.cols / 2 - szModel.width / 2, matFluBinRotation.rows / 2 - szModel.height / 2, szModel.width, szModel.height));
//		if (CGvisAORDoc::m_pAORMasterDoc->m_bUseGPU)
//		{
//			cv::cuda::GpuMat gSource, gModel, gResult;
//			gSource.upload(matFluBinRotation);
//			gModel.upload(mat3DBin);
//			cv::Ptr<cv::cuda::TemplateMatching> matcher = cv::cuda::createTemplateMatching(CV_8UC1, iMethodSearch);
//			matcher->match(gSource, gModel, gResult);
//			cv::cuda::minMaxLoc(gResult, &dMinVal, &dMaxVal, &ptMinLoc, &ptMaxLoc, cv::Mat());
//			gResult.download(matResult);
//			gSource.release();
//			gModel.release();
//			gResult.release();
//		}
//		else
//		{
//			matchTemplate(matFluBinRotation, mat3DBin, matResult, iMethodSearch);
//			minMaxLoc(matResult, &dMinVal, &dMaxVal, &ptMinLoc, &ptMaxLoc, cv::Mat());
//		}
//
//
//
//
//		if (iMethodSearch == CV_TM_SQDIFF || iMethodSearch == CV_TM_SQDIFF_NORMED)
//		{
//			value = dMinVal;
//			if (dScore > value)
//			{
//				dScore = value;// 스코어 값 
//				m_ptMatchLoc = ptMinLoc; // 최적위치의 위치 값 
//				m_fMatchTheta = fTheta; // 최적 위치의 theta 값
//			}
//
//		}
//		else
//		{
//			value = dMaxVal;
//			if (dScore < value)
//			{
//				dScore = value;// 스코어 값 
//				m_ptMatchLoc = ptMaxLoc; // 최적위치의 위치 값 
//				m_fMatchTheta = fTheta; // 최적 위치의 theta 값
//			}
//		}
//		
//	}
//	if (iMethodSearch == CV_TM_SQDIFF || iMethodSearch == CV_TM_SQDIFF_NORMED)
//	{
//		m_dMatchScore = (1.0 - dScore) * 100.0;
//	}
//	else
//	{
//		m_dMatchScore = dScore * 100.0;
//	}
//	
//
//	
//	resize(mat3DGray, mat3DBinResize, szResize);
//
//	// 여기서 FLU를 회전시킨다.
//	matRotation = getRotationMatrix2D(cv::Point2f((float)matResizeFlu.cols / 2.0f, (float)matResizeFlu.rows / 2.0f), m_fMatchTheta, 1);
//	warpAffine(matResizeFlu, matFluResult, matRotation, cv::Size(matResizeFlu.cols, matResizeFlu.rows));
//
//	
//	return matFluResult;
//}

//cv::Mat Matching::GetCutImg(cv::Mat matImg, double dScaleXY, cv::Point ptStart)
//{
//	SSR3DData *S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	cv::Mat matCuttingImg;
//	double dScore = GetMatchSdScore();
//	
//#if USE_3D_GFV == USE
//	matCuttingImg = cv::Mat(S3DData->m_matDepthMap.rows, S3DData->m_matDepthMap.cols, CV_32FC1);
//#else
//	matCuttingImg = cv::Mat(MAX_3D_HEIGHT_SIZE, MAX_3D_WIDTH_SIZE, CV_32FC1);
//#endif
//	matCuttingImg.setTo(0);
//
//	cv::Mat matFullImage;
//	matFullImage = matImg.clone();
//	
//
//	if (dScore >= CGvisAORView::m_pAORMasterView->m_pManager->m_dStandardScore)
//	{
//		cv::Size szResize;
//		szResize.width = ConvertInt(matFullImage.cols * dScaleXY);
//		szResize.height = ConvertInt(matFullImage.rows * dScaleXY);
//		cv::Mat matRsFullImage, matFullRotation;
//		cv::resize(matFullImage, matRsFullImage, szResize);
//
//		cv::Mat matRotation;
//		matRotation = getRotationMatrix2D(cv::Point2f((float)matRsFullImage.cols / 2.0f, (float)matRsFullImage.rows / 2.0f), GetMatchTheta(), 1);
//		warpAffine(matRsFullImage, matFullRotation, matRotation, cv::Size(matRsFullImage.cols, matRsFullImage.rows));
//
//		findContours(matFullRotation, m_ProcessContours, m_ProcessHierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
//
//
//		for (int i = 0; i < m_ProcessContours.size(); i++)
//		{
//			for (int j = 0; j < m_ProcessContours.at(i).size(); j++)
//			{
//				m_ProcessContours.at(i).at(j).x -= ptStart.x;
//				m_ProcessContours.at(i).at(j).y -= ptStart.y;
//			}
//		}
//
//		if (m_ProcessContours.size() > 0 && m_ProcessHierarchy.size() > 0)
//		{
//
//			for (int idx = 0; idx >= 0; idx = m_ProcessHierarchy[idx][0])
//			{
//				cv::Scalar color(255, 255, 255);
//				drawContours(matCuttingImg, m_ProcessContours, idx, color, -1, cv::LINE_8, m_ProcessHierarchy);
//			}
//		}
//	}
//
//	return matCuttingImg;
//}

float Matching::GetMatchTheta()
{
	return m_fMatchTheta;
}
float Matching::GetMatchErode()
{
	return m_fMatchErode;
}

//float Matching::Findscale2(cv::Mat matFlu, cv::Mat mat3D)
//{
//	RTC5Param *pstRTC5Param = CGvisAORDoc::m_pAORMasterDoc->GetRTC5Param();
//	cv::Mat mat3DGray = mat3D, mat3DBin, matModel;
//	cv::Mat matRotation, mat3DBinRotation, matResult, matFluResize;
//	cv::Mat mat3DBinResize = cv::Mat(mat3D.rows, mat3D.cols, CV_8UC1);
//	cv::Point ptMinLoc, ptMaxLoc;
//	cv::Size szModel, szResize;
//
//	double dMinVal, dMaxVal, dScore = 0, value;
//
//	cv::threshold(mat3DGray, mat3DBin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
//
//	szModel.width = mat3DBinResize.cols;
//	szModel.height = mat3DBinResize.rows;
//	if (szModel.width % 2 == 1)
//	{
//		szModel.width++;
//	}
//	if (szModel.height % 2 == 1)
//	{
//		szModel.height++;
//	}
//
//	m_ptMatchLoc = cv::Point(0, 0);
//	int iMethodSearch = CV_TM_CCORR_NORMED;
//	float fResolutionMatch;
//#if USE_3D_HELICAM == USE
//	fResolutionMatch = pstRTC5Param->dCameraResolutionX / _3D_RESOLUTION;
//#elif USE_3D_GFV == USE
//	fResolutionMatch = pstRTC5Param->dCameraResolutionX / (CGvisAORView::m_pAORMasterView->m_pGFV->GetPixelSize() / 12500);
//#endif
//	float fScaleXY = 0;
//	float fBestScaleXY = 0;
//	int nBestErode = 0;
//	cv::Mat mat3DErode;
//	cv::Mat kernel_circle = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
//	for (int nErode = 0; nErode < 4; nErode++)
//	{
//		if (nErode > 0)
//		{
//			cv::erode(mat3DBin, mat3DErode, kernel_circle, cv::Point(-1, -1), nErode);
//		}
//		else
//		{
//			mat3DErode = mat3DBin;
//		}
//		for (fScaleXY = fResolutionMatch - 0.1; fScaleXY < fResolutionMatch + 0.1; fScaleXY = fScaleXY + 0.01)
//		{
//
//			szResize.width = ConvertInt(matFlu.cols * fScaleXY);
//			szResize.height = ConvertInt(matFlu.rows * fScaleXY);
//			cv::resize(matFlu, matFluResize, szResize);
//
//			if (CGvisAORDoc::m_pAORMasterDoc->m_bUseGPU)
//			{
//				cv::cuda::GpuMat gSource, gModel, gResult;
//				gSource.upload(matFluResize);
//				gModel.upload(mat3DErode);
//				cv::Ptr<cv::cuda::TemplateMatching> matcher = cv::cuda::createTemplateMatching(CV_8UC1, iMethodSearch);
//				matcher->match(gSource, gModel, gResult);
//				cv::cuda::minMaxLoc(gResult, &dMinVal, &dMaxVal, &ptMinLoc, &ptMaxLoc, cv::Mat());
//				gResult.download(matResult);
//				gSource.release();
//				gModel.release();
//				gResult.release();
//			}
//			else
//			{
//				matchTemplate(matFluResize, mat3DErode, matResult, iMethodSearch);
//				minMaxLoc(matResult, &dMinVal, &dMaxVal, &ptMinLoc, &ptMaxLoc, cv::Mat());
//			}
//
//
//			
//			if (iMethodSearch == CV_TM_SQDIFF || iMethodSearch == CV_TM_SQDIFF_NORMED)
//			{
//				value = dMinVal;
//				if (dScore > value)
//				{
//					dScore = value;// 스코어 값 
//					m_ptMatchLoc = ptMinLoc; // 최적위치의 위치 값  
//					fBestScaleXY = fScaleXY;// 최적 위치의 Scale 값
//					nBestErode = nErode;
//				}
//
//			}
//			else
//			{
//				value = dMaxVal;
//				if (dScore < value)
//				{
//					dScore = value;// 스코어 값 
//					m_ptMatchLoc = ptMaxLoc; // 최적위치의 위치 값 
//					fBestScaleXY = fScaleXY; // 최적 위치의 theta 값
//					nBestErode = nErode;
//				}
//			}
//		}
//	}
//
//	if (iMethodSearch == CV_TM_SQDIFF || iMethodSearch == CV_TM_SQDIFF_NORMED)
//	{
//		m_dMatchScore = (1.0 - dScore) * 100.0;
//	}
//	else
//	{
//		m_dMatchScore = dScore * 100.0;
//	}
//	CGvisAORDoc::m_pAORMasterDoc->m_f3DErode = nBestErode;
//	return fBestScaleXY;
//}

void Matching::SetMatchPt(cv::Point pt)
{
	m_ptMatchLoc = pt;
}

//void Matching::MatchingExactLocation(cv::Mat matFlu, cv::Mat mat3D, cv::Point pt, double dMatchingRange, float fScaleXY, float fTheta)
//{
//
//	cv::Mat mat3DBin;
//	cv::Mat mat3DBinResize = cv::Mat(mat3D.rows, mat3D.cols, CV_8UC1);
//	cv::Mat matFluBin, matResizeFlu, matFluBinRotation;
//	cv::Mat matRotation, matResult, matFluResult;
//	cv::Point ptMinLoc, ptMaxLoc;
//	cv::Size szModel, szResize;
//
//	int nErode = CGvisAORDoc::m_pAORMasterDoc->m_f3DErode; //얘로 나중에 이값의 위아래 하나 값 추가 
//	cv::Mat mat3DErode;
//	float fBestScaleXY = 0;
//	double dMinVal, dMaxVal, dScore = 0, value;
//	int iMethodSearch = CV_TM_CCORR_NORMED;
//
//	cv::threshold(mat3D, mat3DBin, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
//
//	matFluBin = matFlu;
//
//	szModel.width = mat3DBinResize.cols;
//	szModel.height = mat3DBinResize.rows;
//	if (szModel.width % 2 == 1)
//	{
//		szModel.width++;
//	}
//	if (szModel.height % 2 == 1)
//	{
//		szModel.height++;
//	}
//
//	cv::Point ptConvert = (0, 0);
//	m_ptMatchLoc = cv::Point(0, 0);
//	ptConvert.x = pt.x - dMatchingRange;
//	if (ptConvert.x < 0)
//	{
//		ptConvert.x = 0;
//	}
//	ptConvert.y = pt.y - dMatchingRange;
//	if (ptConvert.y < 0)
//	{
//		ptConvert.y = 0;
//	}
//
//
//	szResize.width = ConvertInt(matFlu.cols * fScaleXY);
//	szResize.height = ConvertInt(matFlu.rows * fScaleXY);
//	cv::resize(matFluBin, matResizeFlu, szResize);
//
//
//
//	/////잘라내야지
//	cv::Mat kernel_circle = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
//	for (int j = nErode - 1; j <= nErode + 1; j++)
//	{
//		if (j > 0)
//		{
//			cv::erode(mat3DBin, mat3DErode, kernel_circle, cv::Point(-1, -1), j);
//		}
//		else
//		{
//			mat3DErode = mat3DBin;
//		}
//
//
//
//		for (float i = fTheta - 2; i <= fTheta + 2; i++)
//		{
//			matRotation = cv::getRotationMatrix2D(cv::Point2f((float)matResizeFlu.cols / 2.0f, (float)matResizeFlu.rows / 2.0f), i, 1);
//			warpAffine(matResizeFlu, matFluBinRotation, matRotation, cv::Size(matResizeFlu.cols, matResizeFlu.rows));
//
//			//matModel = matFluBinRotation(cv::Rect(matFluBinRotation.cols / 2 - szModel.width / 2, matFluBinRotation.rows / 2 - szModel.height / 2, szModel.width, szModel.height));
//			cv::Rect rectROI = cv::Rect(ptConvert.x, ptConvert.y, mat3DBinResize.cols + dMatchingRange * 2, mat3DBinResize.rows + dMatchingRange * 2);
//			cv::Mat matCUTFlu = matFluBinRotation(rectROI);
//			/////
//			if (CGvisAORDoc::m_pAORMasterDoc->m_bUseGPU)
//			{
//				cv::cuda::GpuMat gSource, gModel, gResult;
//				gSource.upload(matCUTFlu);
//				gModel.upload(mat3DErode);
//				cv::Ptr<cv::cuda::TemplateMatching> matcher = cv::cuda::createTemplateMatching(CV_8UC1, iMethodSearch);
//				matcher->match(gSource, gModel, gResult);
//				cv::cuda::minMaxLoc(gResult, &dMinVal, &dMaxVal, &ptMinLoc, &ptMaxLoc, cv::Mat());
//				gResult.download(matResult);
//				gSource.release();
//				gModel.release();
//				gResult.release();
//			}
//			else
//			{
//				matchTemplate(matCUTFlu, mat3DErode, matResult, iMethodSearch);
//				minMaxLoc(matResult, &dMinVal, &dMaxVal, &ptMinLoc, &ptMaxLoc, cv::Mat());
//			}
//
//
//
//
//			if (iMethodSearch == CV_TM_SQDIFF || iMethodSearch == CV_TM_SQDIFF_NORMED)
//			{
//				// 스코어 값 
//				value = dMinVal;
//				if (dScore > value)
//				{
//					dScore = dMinVal;
//					m_ptMatchLoc = ptMinLoc + ptConvert; // 최적위치의 위치 값 
//					m_fMatchTheta = i; // 최적 위치의 theta 값
//					m_dMatchScore = (1.0 - dScore) * 100.0;
//					m_fMatchErode = nErode;
//
//					// 확인을 위한 코드.
//					cv::Mat cut = matCUTFlu.clone();
//					cv::Rect RROI = cv::Rect(ptMinLoc.x, ptMinLoc.y, mat3D.cols, mat3D.rows);
//					cv::Mat ImgROI = cut(RROI);
//					mat3D.copyTo(ImgROI);
//				}
//			}
//			else
//			{
//				// 스코어 값 
//				value = dMaxVal;
//				if (dScore < value)
//				{
//					dScore = dMaxVal;
//					m_ptMatchLoc = ptMaxLoc + ptConvert; // 최적위치의 위치 값 
//					m_fMatchTheta = i; // 최적 위치의 theta 값
//					m_dMatchScore = dScore * 100.0;
//					m_fMatchErode = nErode;
//
//					// 확인을 위한 코드.
//					cv::Mat cut = matCUTFlu.clone();
//					cv::Rect RROI = cv::Rect(ptMaxLoc.x, ptMaxLoc.y, mat3D.cols, mat3D.rows);
//					cv::Mat ImgROI = cut(RROI);
//					mat3D.copyTo(ImgROI);
//				}
//			}
//		}
//	}
//
//	//나중에 여기다가 포인트의 최신 값들을 넣어서 전달하자
//
//}

//void Matching::CalcAllArea(cv::Mat &matCheckResin, cv::Mat &matCheckDefect, cv::Mat &matCheckCu)
//{
//	SSR3DData* S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	// 크기를 바꿔준다음 원레 사이즈에서의 불량 크기를 찾는다.
//	double dSum = 0, dRsSum = 0, dCuSum = 0;//총합
//	double dSquareSum = 0, dRsSquareSum = 0, dCuSquareSum = 0; // 제곱의 합
//	float fResinmin = 9999;
//	float fCumax = -9999;
//	float fCumin = 9999;
//	float fDamageMax = 9999;
//
//	m_bISDefectValue = FALSE;
//	m_bISResinValue = FALSE;
//	m_bISCutValue = FALSE;
//	m_fTotalMin = 9999;
//
//	int nPixelCount = 0, nResinPixelConut = 0, nCuPixelCount = 0;//픽셀수
//	float fVar = 0, fRsVar = 0, fCuVar = 0; //분산
//
//
//	float fStdv = 0, fRsStdv = 0, fCuStdv = 0;
//	float fRsAvg, fCuAvg;
//
//	int nSizeX, nSizeY;
//#if USE_3D_HELICAM == USE
//	nSizeX = MAX_3D_WIDTH_SIZE;
//	nSizeY = MAX_3D_HEIGHT_SIZE;
//#elif USE_3D_GFV == USE
//	nSizeX = S3DData->m_matDepthMap.cols;
//	nSizeY = S3DData->m_matDepthMap.rows;
//#endif
//
//	for (int j = 0; j < nSizeY; j++)
//	{
//		for (int i = 0; i < nSizeX; i++)
//		{
//			float fNearest = roundf(S3DData->m_matDepthMap.at<float>(j, i) * 10000) / 10;
//
//			m_fTotalMin = min(m_fTotalMin, fNearest);
//			if (matCheckResin.at<float>(j, i) == 255)//레진 전체 영역 
//			{
//				if (matCheckDefect.at<float>(j, i) == 255)
//				{// 불량 영역
//					if (fDamageMax > fNearest)
//					{
//						m_ptMaxDamage.x = i;
//						m_ptMaxDamage.y = j;
//					}
//					fDamageMax = min(fDamageMax, fNearest);
//					if (fNearest > 0)
//					{
//						fNearest = 0;
//					}
//					else
//					{
//						dSum += fNearest;// 한 픽셀식 불량 영역만 검사해서 더하기 
//						nPixelCount++;
//						dSquareSum += pow(fNearest, 2); // 제곱의 합
//						m_bISDefectValue = TRUE;
//					}
//
//				}
//				else
//				{ // 불량 제외한 레진 영역
//					if (fNearest > 0)
//					{
//						fNearest = 0;
//					}
//					else
//					{
//						dRsSum += fNearest;
//						nResinPixelConut++;
//						dRsSquareSum += pow(fNearest, 2);
//						fResinmin = min(fResinmin, fNearest);
//						m_bISResinValue = TRUE;
//					}
//				}
//			}
//			else//레진 아닌 영역
//			{
//				if (matCheckCu.at<float>(j, i) == 255)//커퍼 영역
//				{
//					if (fNearest > 0)
//					{
//						dCuSum += fNearest;
//						nCuPixelCount++;
//						dCuSquareSum += pow(fNearest, 2);
//						fCumin = min(fCumin, fNearest);
//						fCumax = max(fCumax, fNearest);
//						m_bISCutValue = TRUE;
//					}
//				}
//			}
//		}
//	}
//	if (nCuPixelCount > 0)
//	{
//		fCuAvg = dCuSum / nCuPixelCount;
//	}
//	else
//	{
//		fCuAvg = 0;
//	}
//	fCuVar = (dCuSquareSum / nCuPixelCount) - (pow(fCuAvg, 2));
//	fCuStdv = pow(fCuVar, 0.5);
//
//	if (fCumin < (fCuAvg - fCuStdv))
//	{
//		fCumin = 9999;
//		fCumax = 0;
//		dCuSum = 0;
//		nCuPixelCount = 0;
//		dCuSquareSum = 0;
//		for (int j = 0; j < nSizeY; j++)
//		{
//			for (int i = 0; i < nSizeX; i++)
//			{
//				float fNearest = roundf(S3DData->m_matDepthMap.at<float>(j, i) * 10000) / 10;
//
//				if (matCheckResin.at<float>(j, i) != 255) // Cupper Area 2 
//				{
//					if (fNearest > fCuAvg - (fCuStdv))
//					{
//						if (fNearest > 0)
//						{
//							dCuSum += fNearest;
//							nCuPixelCount++;
//							dCuSquareSum += pow(fNearest, 2);
//							fCumin = min(fCumin, fNearest);
//							fCumax = max(fCumax, fNearest);
//
//						}
//					}
//				}
//
//			}
//		}
//		fCuAvg = dCuSum / nCuPixelCount;
//		fCuVar = (dCuSquareSum / nCuPixelCount) - (pow(fCuAvg, 2));
//		fCuStdv = pow(fCuVar, 0.5);
//
//	}
//
//
//
//
//	m_3DAllArea.m_fCuAvg = fCuAvg;
//	m_3DAllArea.m_fResinAvg = dRsSum / nResinPixelConut;
//	m_3DAllArea.m_fDemageAvg = dSum / nPixelCount;
//
//
//	fRsVar = (dRsSquareSum / nResinPixelConut) - (pow(m_3DAllArea.m_fResinAvg, 2));
//	fVar = (dSquareSum / nPixelCount) - (pow(m_3DAllArea.m_fDemageAvg, 2));// 분산  = 제곱의 평균 - 평균의 제곱 
//
//	m_3DAllArea.m_fDemageMax = fDamageMax;
//	m_3DAllArea.m_fDemageStdv = pow(fVar, 0.5);
//	m_3DAllArea.m_fDemage3sig = m_3DAllArea.m_fDemageStdv * 3;
//
//	m_3DAllArea.m_fResinMin = fResinmin;
//	m_3DAllArea.m_fResinStdv = pow(fRsVar, 0.5);
//	m_3DAllArea.m_fResin3sig = m_3DAllArea.m_fResinStdv * 3;
//
//	m_3DAllArea.m_fCuMax = fCumax;
//	m_3DAllArea.m_fCuMin = fCumin;
//	m_3DAllArea.m_fCuStdv = fCuStdv;
//
//
//}

//void Matching::FindAutoProfileLine(cv::Mat& DefectArea, cv::Mat& ResinArea)
//{
//	SSR3DData *S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	cv::Mat srcThinning, matResin = ResinArea.clone(), matDefect = DefectArea.clone();
//	matResin.convertTo(matResin, CV_8UC1);
//	matDefect.convertTo(matDefect, CV_8UC1);
//	for (int j = 0; j < matResin.rows; j++)
//	{
//		for (int i = 0; i < matResin.cols; i++)
//		{
//			if (i == 0 || j == 0 || i == matResin.cols - 1 || j == matResin.rows - 1)
//			{
//				matResin.at<unsigned char>(j, i) = 0;
//			}
//		}
//	}
//	cv::ximgproc::thinning(matResin, srcThinning, cv::ximgproc::THINNING_GUOHALL);
//
//	int nSizeX, nSizeY;
//#if USE_3D_HELICAM == USE
//	nSizeX = MAX_3D_WIDTH_SIZE;
//	nSizeY = MAX_3D_HEIGHT_SIZE;
//#elif USE_3D_GFV == USE
//	nSizeX = S3DData->m_matDepthMap.cols;
//	nSizeY = S3DData->m_matDepthMap.rows;
//#endif
//	cv::Mat kernel_circle = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
//	cv::dilate(matDefect, matDefect, kernel_circle, cv::Point(-1, -1), 6);
//	cv::Mat matAutoLine = cv::Mat(nSizeY, nSizeX, CV_8UC1);
//	matAutoLine.setTo(0);
//	m_vecThinningPt.clear();
//
//
//	for (int j = 0; j < nSizeY; j++)
//	{
//		for (int i = 0; i < nSizeX; i++)
//		{
//			if (matDefect.at<unsigned char>(j, i) == 255 && srcThinning.at<unsigned char>(j, i) == 255)
//			{
//				matAutoLine.at<unsigned char>(j, i) = 255;
//			}
//		}
//	}
//	std::vector<std::vector<cv::Point> > contours;
//	std::vector<cv::Vec4i> hierarchy;
//	cv::findContours(matAutoLine, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
//
//	double dBiggestArea = 0;
//	int nBiggestIndex = -1;
//
//	matAutoLine.setTo(0);
//	if (contours.size() > 0 && hierarchy.size() > 0)
//	{
//		for (int idx = 0; idx >= 0; idx = hierarchy[idx][0])
//		{
//			cv::Mat matLine = matAutoLine.clone();
//			cv::Scalar color(255, 255, 255);
//			drawContours(matLine, contours, idx, color, -1, cv::LINE_8, hierarchy);
//			double dSize = GetThinningSize(matLine);
//			if (dBiggestArea < dSize)
//			{
//				dBiggestArea = dSize;
//				nBiggestIndex = idx;
//			}
//		}
//		cv::Scalar color(255, 255, 255);
//		drawContours(matAutoLine, contours, nBiggestIndex, color, -1, cv::LINE_8, hierarchy);
//		//20200213 JCH 변경 Find FirstPT and LastPT
//
//		int nCount = 0;
//		vector<cv::Point>vecTwoEndPt;
//
//		for (int j = 0; j < contours.at(nBiggestIndex).size(); j++)
//		{
//			cv::Point StartPt = contours.at(nBiggestIndex).at(j);
//			cv::Mat matCopy = matAutoLine.clone();
//			matCopy.at<unsigned char>(StartPt.y, StartPt.x) = 128;
//			nCount = 0;
//			for (int y = StartPt.y - 1; y <= StartPt.y + 1; y++)
//			{
//				for (int x = StartPt.x - 1; x <= StartPt.x + 1; x++)
//				{
//					if (matCopy.at<unsigned char>(y, x) == 255)
//					{
//						nCount++;
//					}
//				}
//			}
//			if (nCount == 1)
//			{
//				vecTwoEndPt.push_back(cv::Point(StartPt.x, StartPt.y));
//			}
//		}
//
//		// 20200214 변경
//		CalcSortLine(matAutoLine, vecTwoEndPt.at(0));
//		
//	}
//}

//void Matching::CalculCuResin(cv::Mat matDefect)
//{
//	SSR3DData* S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	cv::Mat matOnlyResin = S3DData->m_matDepthMap.clone();
//
//	int nSizeX, nSizeY;
//#if USE_3D_HELICAM == USE
//	nSizeX = MAX_3D_WIDTH_SIZE;
//	nSizeY = MAX_3D_HEIGHT_SIZE;
//#elif USE_3D_GFV == USE
//	nSizeX = S3DData->m_matDepthMap.cols;
//	nSizeY = S3DData->m_matDepthMap.rows;
//#endif
//
//	m_matLineWidth = cv::Mat(nSizeY, nSizeX, CV_8UC1);
//	m_matLineWidth.setTo(0);
//	cv::Mat matDefectDilate;
//	cv::Mat kernel_circle = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
//	cv::dilate(matDefect, matDefectDilate, kernel_circle, cv::Point(-1, -1), 6);
//	for (int j = 0; j < nSizeY; j++)
//	{
//		for (int i = 0; i < nSizeX; i++)
//		{
//			float fNearest = roundf(S3DData->m_matDepthMap.at<float>(j, i) * 10000) / 10;
//
//			if (fNearest > m_3DAllArea.m_fCuAvg / 10)//커퍼 영역이면 !
//			{
//				m_matLineWidth.at<unsigned char>(j, i) = 255;
//			}
//			if (fNearest > 0)
//			{
//				matOnlyResin.at<float>(j, i) = 0;
//			}
//		}
//	}
//
//	S3DData->m_matOnlyResin = matOnlyResin;
//
//}

//void Matching::CalculJudgment(cv::Mat matDefect, cv::Mat matResin)
//{
//	SSR3DData *S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	m_fResinDamage = m_3DAllArea.m_fDemageMax;
//	m_fSpaceGap = GetSpaceGap() * S3DData->m_dXResolution *1000.0;
//	m_fCudamage = GetCuDamage(matDefect, matResin);
//
//	m_fDamageSpec = CGvisAORDoc::m_pAORMasterDoc->m_fDamageSpec;
//	m_fSpaceGapSpec = CGvisAORDoc::m_pAORMasterDoc->m_fSpaceGapSpec;
//	m_fCuDamageSpec = CGvisAORDoc::m_pAORMasterDoc->m_fCuDamageSpec;
//
//
//
//	if (m_fCudamage == 0 && m_fResinDamage == 9999 && m_fSpaceGap == 9999)
//	{
//		m_bNotDefact = TRUE;
//	}
//	else
//	{
//		m_bNotDefact = FALSE;
//	}
//
//
//	if (m_fCudamage > m_fCuDamageSpec)
//	{
//		m_bCuDamage = TRUE;
//	}
//	else
//	{
//		m_bCuDamage = FALSE;
//	}
//	if (m_fResinDamage < 0)
//	{
//		m_fResinDamage *= -1;
//		if (m_fResinDamage > m_fDamageSpec) // 최고 대미지
//		{
//			m_bResinDamage = TRUE;
//		}
//		else
//		{
//			m_bResinDamage = FALSE;
//		}
//	}
//	else
//	{
//		if (m_fResinDamage > 1)
//		{
//			m_bResinDamage = TRUE;
//		}
//		else
//		{
//			m_bResinDamage = FALSE;
//		}
//	}
//	
//
//	if (m_fSpaceGapSpec > m_fSpaceGap)
//	{
//		m_bResinGap = TRUE;
//	}
//	else
//	{
//		m_bResinGap = FALSE;
//	}
//}

//float Matching::GetSpaceGap()
//{
//
//	float fSpaceGap = 0;
//	float fBestMinSpaceGap = 9999;
//	for (int j = 0; j < m_vecThinningPt.size(); j++)
//	{
//		CGvisAORView::m_pAORMasterView->m_pManager->m_cVision.GetMinLineWidthResin(m_matLineWidth, m_vecThinningPt[j], fSpaceGap);
//		fBestMinSpaceGap = min(fBestMinSpaceGap, fSpaceGap);
//	}
//	return fBestMinSpaceGap;
//}

//float Matching::GetCuDamage(cv::Mat matDefect, cv::Mat matResin)
//{
//	SSR3DData *S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	float fCuDamageAvg = 0;
//	cv::Mat dMATilate, matResinDilate;
//	cv::Mat kernel_circle = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
//	cv::dilate(matDefect, dMATilate, kernel_circle, cv::Point(-1, -1), 6);
//
//	int nSizeX, nSizeY;
//#if USE_3D_HELICAM == USE
//	nSizeX = MAX_3D_WIDTH_SIZE;
//	nSizeY = MAX_3D_HEIGHT_SIZE;
//#elif USE_3D_GFV == USE
//	nSizeX = S3DData->m_matDepthMap.cols;
//	nSizeY = S3DData->m_matDepthMap.rows;
//#endif
//
//	
//	float fCuCount = 0, fBestDamage = 9999;
//	for (int j = 0; j < nSizeY; j++)
//	{
//		for (int i = 0; i < nSizeX; i++)
//		{
//			if (matResin.at<float>(j, i) != 255)//레진 아닌 영역
//			{
//				//살짝 침범한 커퍼 영역
//				if (dMATilate.at<float>(j, i) == 255)
//				{
//					float fNearest = roundf(S3DData->m_matDepthMap.at<float>(j, i) * 10000) / 10;
//					if (fNearest > m_3DAllArea.m_fCuAvg*0.7)
//					{
//						fCuDamageAvg += fNearest;
//						fCuCount++;
//						if (fBestDamage > fNearest)
//						{
//							m_ptMaxCuDamage.x = i;
//							m_ptMaxCuDamage.y = j;
//						}
//						fBestDamage = min(fBestDamage, fNearest);
//					}
//				}
//			}
//
//		}
//	}
//	if (fCuCount > 0)
//	{
//		fCuDamageAvg = fCuDamageAvg / fCuCount;
//	}
//	else
//	{
//		fCuDamageAvg = 0;
//	}
//	return m_3DAllArea.m_fCuAvg - fCuDamageAvg;
//}

//cv::Mat Matching::GetNormalize3DImg()
//{
//	SSR3DData *S3DData = CGvisAORDoc::m_pAORMasterDoc->Get3DData();
//	
//	CString strPath = CGvisAORDoc::m_pAORMasterDoc->m_strData3DFilePath + _T("m_matrixZ.exr");
//	std::string ss = (CT2A(strPath));
//#if USE_3D_HELICAM == USE
//	cv::Mat matHeliData = S3DData->m_matDepthMap;
//#else
//	cv::Mat matHeliData = S3DData->m_matDepthMap;
//#endif
//	return ApplyConvertImageAuto(matHeliData);
//}

int Matching::GetThinningSize(cv::Mat matThinning)
{
	int nPixelCount = 0;
	for (int j = 0; j < matThinning.rows; j++)
	{
		for (int i = 0; i < matThinning.cols; i++)
		{
			if (matThinning.at<unsigned char>(j, i) == 255)
			{
				nPixelCount++;
			}

		}
	}

	return nPixelCount;
}



void Matching::CalcSortLine(cv::Mat matLineImg, cv::Point pt)
{

	int value, valueExpanding = 0, tempvalue;
	int blob = 0;
	int countpixel = 0;
	int stopinspection = 1;
	int startx, starty, bexit;
	int flag = 1;
	int cx;
	int cy;
	int passflag;
	int endflag;
	int direction;

	cv::Mat matCopy;
	//////////////////////////////
	//////////////////////////////

	while (stopinspection)
	{
		//////////////////////////////
		startx = 0;
		starty = 0;
		bexit = 0;

		flag = 1;
		countpixel = 0;
		cx = pt.x;
		cy = pt.y;
		passflag = 0;
		endflag = 0;
		direction = 3;

		do
		{

			passflag = 0;
			endflag = 0;
			countpixel++;



			matLineImg.at<unsigned char>(cy, cx) = 128;//중간값 루트처리
			m_vecThinningPt.push_back(cv::Point(cx, cy));

			switch (direction)
			{
			case 3:
				//Direct == 1
				if (!passflag)
				{
					if ((cy - 1) >= 0)
					{
						tempvalue = matLineImg.at<unsigned char>(cy - 1, cx);
						if (tempvalue > 128)
						{
							direction = 1;
							passflag = 1;
							endflag = 0;
							cy--;
						}
						else
						{
							endflag = 1;
						}
					}
				}
			case 4:
				//Direct == 2
				if (!passflag)
				{
					if ((cx + 1) <= (matLineImg.cols - 1))
					{
						if ((cy - 1) >= 0)
						{
							tempvalue = matLineImg.at<unsigned char>(cy - 1, cx + 1);
							if (tempvalue > 128)
							{
								direction = 2;
								cx++;
								cy--;
								passflag = 1;
								flag = 1;
								endflag = 0;

							}
							else
							{
								endflag = 1;
							}
						}
					}
				}
			case 5:
				//Direct == 3
				if (!passflag)
				{
					if ((cx + 1) <= (matLineImg.cols - 1))
					{
						tempvalue = matLineImg.at<unsigned char>(cy, cx + 1);
						if (tempvalue > 128)
						{
							direction = 3;
							passflag = 1;

							cx++;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}
			case 6:
				//Direct == 4
				if (!passflag)
				{
					if ((cx + 1) <= (matLineImg.cols - 1))
					{
						if ((cy + 1) <= (matLineImg.rows - 1))
						{
							tempvalue = matLineImg.at<unsigned char>(cy + 1, cx + 1);
							if (tempvalue > 128)
							{
								direction = 4;
								cx++;
								cy++;
								passflag = 1;
								flag = 3;
								endflag = 0;
							}
							else
							{
								endflag = 1;
							}
						}
					}
				}
			case 7:
				//Direct == 5
				if (!passflag)
				{
					if ((cy + 1) <= (matLineImg.rows - 1))
					{
						tempvalue = matLineImg.at<unsigned char>(cy + 1, cx);
						if (tempvalue > 128)
						{
							direction = 5;
							passflag = 1;

							cy++;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}
			case 8:
				//Direct == 6
				if (!passflag)
				{
					if ((cx - 1) >= 0)
					{
						if ((cy + 1) <= (matLineImg.rows - 1))
						{
							tempvalue = matLineImg.at<unsigned char>(cy + 1, cx - 1);

							if (tempvalue > 128)
							{
								direction = 6;

								cx--;
								cy++;
								passflag = 1;
								flag = 2;
								endflag = 0;

							}
							else
							{
								endflag = 1;
							}
						}
					}
				}
			case 1:
				//Direct == 7
				if (!passflag)
				{
					if ((cx - 1) >= 0)
					{
						tempvalue = tempvalue = matLineImg.at<unsigned char>(cy, cx - 1);
						if (tempvalue > 128)
						{
							direction = 7;
							passflag = 1;

							cx--;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}
			case 2:
				//Direct == 8
				if (!passflag)
				{
					if ((cx - 1) >= 0)
					{
						if ((cy - 1) >= 0)
						{
							tempvalue = matLineImg.at<unsigned char>(cy - 1, cx - 1);

							if (tempvalue > 128)
							{
								direction = 8;
								cx--;
								cy--;
								passflag = 1;
								flag = 1;
								endflag = 0;
							}
							else
							{
								endflag = 1;
							}
						}
					}
				}

				//////////////////////////////////////////////////////////////////////
				//Direct == 1
				if (!passflag)
				{
					if ((cy - 1) >= 0)
					{
						tempvalue = matLineImg.at<unsigned char>(cy - 1, cx);
						if (tempvalue > 128)
						{
							passflag = 1;
							direction = 1;
							cy--;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}

				//Direct == 2
				if (!passflag)
				{
					if ((cx + 1) <= (matLineImg.cols - 1))
					{
						if ((cy - 1) >= 0)
						{
							tempvalue = matLineImg.at<unsigned char>(cy - 1, cx + 1);
							if (tempvalue > 128)
							{
								cx++;
								cy--;
								passflag = 1;
								flag = 1;
								direction = 2;
								endflag = 0;
							}
							else
							{
								endflag = 1;
							}
						}

					}
				}

				//Direct == 3
				if (!passflag)
				{
					if ((cx + 1) <= (matLineImg.cols - 1))
					{
						tempvalue = matLineImg.at<unsigned char>(cy, cx + 1);
						if (tempvalue > 128)
						{
							passflag = 1;
							direction = 3;
							cx++;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}

				//Direct == 4
				if (!passflag)
				{
					if ((cx + 1) <= (matLineImg.cols - 1))
					{
						if ((cy + 1) <= (matLineImg.rows - 1))
						{
							tempvalue = matLineImg.at<unsigned char>(cy + 1, cx + 1);
							if (tempvalue > 128)
							{
								cx++;
								cy++;
								passflag = 1;
								flag = 3;
								direction = 4;
								endflag = 0;
							}
							else
							{
								endflag = 1;
							}
						}
					}
				}

				//Direct == 5
				if (!passflag)
				{
					if ((cy + 1) <= (matLineImg.rows - 1))
					{
						tempvalue = matLineImg.at<unsigned char>(cy + 1, cx);
						if (tempvalue > 128)
						{
							passflag = 1;
							direction = 5;
							cy++;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}

				//Direct == 6
				if (!passflag)
				{
					if ((cx - 1) >= 0)
					{
						if ((cy + 1) <= (matLineImg.rows - 1))
						{
							tempvalue = matLineImg.at<unsigned char>(cy + 1, cx - 1);

							if (tempvalue > 128)
							{
								cx--;
								cy++;
								passflag = 1;
								flag = 2;
								direction = 6;
								endflag = 0;
							}
							else
							{
								endflag = 1;
							}
						}
					}
				}


				//Direct == 7
				if (!passflag)
				{
					if ((cx - 1) >= 0)
					{
						tempvalue = matLineImg.at<unsigned char>(cy, cx - 1);
						if (tempvalue > 128)
						{
							passflag = 1;
							direction = 7;
							cx--;
							endflag = 0;
						}
						else
						{
							endflag = 1;
						}
					}
				}

				//Direct == 8
				if (!passflag)
				{
					if ((cx - 1) >= 0)
					{
						if ((cy - 1) >= 0)
						{
							tempvalue = matLineImg.at<unsigned char>(cy - 1, cx - 1);

							if (tempvalue > 128)
							{
								cx--;
								cy--;
								passflag = 1;
								flag = 1;
								direction = 8;
								endflag = 0;
							}
							else
							{
								endflag = 1;
							}
						}
					}
				}


			default: int kkk = 0;
			}

			/////////////////////////////////////////////////////////////////////////







		} while (passflag);

		//이게 끊겼을때 혹시 있는지 검사하는 로직-이렇게 되면 왼쪽 상단부터 시작하게 됩니다

		for (int j = 0; j < matLineImg.rows; j++)
		{
			for (int i = 0; i < matLineImg.cols; i++)
			{
				value = matLineImg.at<unsigned char>(j, i);

				if (value > 128)
				{
					pt.x = i;
					pt.y = j;
					bexit = 1;
					break;
				}
			}
			if (bexit)
				break;
		}
		//만약 찾았던게 아무것도 없는경우에 빠져나오세요.
		if (!bexit)
			break;

	}

}