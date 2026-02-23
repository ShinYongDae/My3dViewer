#pragma once

#include <gl/freeglut_std.h>
#pragma comment (lib, "freeglut.lib")

//opencv header file include
#include <opencv2/opencv.hpp>

struct stTagTriangles
{
	double x[3], y[3], z[3];
	double dNormalVec[3];
	double TexPosX[3], TexPosY[3];
	float ColorR[3], ColorG[3], ColorB[3];


	void CalcNormalVec()
	{
		float v1[3], v2[3], length;

		double fNormalX = 0; //Py*Qz - Pz*Qy;
		double fNormalY = 0; //Pz*Qx - Px*Qz;
		double fNormalZ = 1;// Px*Qy - Py*Qx;

		v1[0] = x[0] - x[1]; v1[1] = y[0] - y[1]; v1[2] = z[0] - z[1];
		v2[0] = x[2] - x[1]; v2[1] = y[2] - y[1]; v2[2] = z[2] - z[1];

		fNormalX = v1[1] * v2[2] - v1[2] * v2[1];
		fNormalY = v1[2] * v2[0] - v1[0] * v2[2];
		fNormalZ = v1[0] * v2[1] - v1[1] * v2[0];

		length = (float)sqrt(fNormalX * fNormalX + fNormalY * fNormalY + fNormalZ * fNormalZ);
		if (length == 0.0f)
			length = 1.0f;

		fNormalX /= length;
		fNormalY /= length;
		fNormalZ /= length;

		dNormalVec[0] = fNormalX;
		dNormalVec[1] = fNormalY;
		dNormalVec[2] = fNormalZ;

	}
};

typedef enum tagTexMode
{
	TEX_LUT,
	TEX_COLOR,
	TEX_AMPLITUDE
}TextureMode;

class C3DModel
{
	GLuint m_Texture;
	GLuint m_TextureGray;
	BOOL m_bTextureLoaded;
	BOOL m_bTextureLoadedGray;
	BOOL m_bMeshCreated;

	float HueToRGB(float v1, float v2, float vH);
	void  HSLToRGB(float H, float S, float L, float& r, float& g, float &b);
	void LoadTexture(cv::Mat mat);
	void LoadTextureGray(cv::Mat mat);
	void Draw(TextureMode mode);
	void FreeTexture();
	void FreeTextureGray();

public:
	C3DModel();
	~C3DModel();

public:
	cv::Mat m_ZMap;
	cv::Mat m_ColorImg;
	cv::Mat m_GrayImg;
	cv::Mat m_ResinImg;
	std::vector<stTagTriangles>m_triangles;

	void MakeModel();
	void ApplyScaleAndOffset(double dOffsetX, double dOffsetY, double dOffsetZ, double dX, double dY, double dZ);
};

