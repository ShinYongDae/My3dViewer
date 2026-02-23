#include "stdafx.h"
#include "C3DModel.h"


C3DModel::C3DModel()
{
	m_Texture = 0;
	m_bTextureLoaded = 0;
	m_bMeshCreated = 0;

	m_TextureGray = 0;
	m_bTextureLoaded = 0;
	m_bTextureLoadedGray = 0;
}

C3DModel::~C3DModel()
{
}

void C3DModel::FreeTexture()
{
	if (m_bTextureLoaded)
	{
		glDeleteTextures(1, &m_Texture);
		m_Texture = 0;
		m_bTextureLoaded = 0;
	}
}

void C3DModel::FreeTextureGray()
{
	if (m_bTextureLoadedGray)
	{
		glDeleteTextures(1, &m_TextureGray);
		m_TextureGray = 0;
		m_bTextureLoadedGray = 0;
	}
}

float C3DModel::HueToRGB(float v1, float v2, float vH)
{
	if (vH < 0)
		vH += 1;

	if (vH > 1)
		vH -= 1;

	if ((6 * vH) < 1)
		return (v1 + (v2 - v1) * 6 * vH);

	if ((2 * vH) < 1)
		return v2;

	if ((3 * vH) < 2)
		return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

	return v1;
}

void  C3DModel::HSLToRGB(float H, float S, float L, float& r, float& g, float &b)
{
	if (S == 0)
	{
		r = g = b = (unsigned char)(L * 255);
	}
	else
	{
		float v1, v2;
		float hue = (float)H / 360;

		v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
		v1 = 2 * L - v2;

		r = (HueToRGB(v1, v2, hue + (1.0f / 3)));
		g = (HueToRGB(v1, v2, hue));
		b = (HueToRGB(v1, v2, hue - (1.0f / 3)));
	}
}

void C3DModel::MakeModel()
{
	int y = 0;
	int x = 0;
	m_triangles.clear();
	m_triangles.reserve(200000);

	double dMax = -9999999;
	double dMin = 9999999;

	for (y = 0; y < m_ZMap.rows - 1; y++)
	{
		for (x = 0; x < m_ZMap.cols - 1; x++)
		{
			float fColor = m_ZMap.at<float>(y, x);

			if (fColor >= dMax)
				dMax = fColor;

			if (fColor <= dMin)
				dMin = fColor;
		}
	}

	if (dMin == dMax)
	{
		dMax = dMin + 0.1;
	}

	for (y = 0; y < m_ZMap.rows - 1; y++)
	{
		for (x = 0; x < m_ZMap.cols - 1; x++)
		{
			stTagTriangles tri;

			tri.x[0] = x;
			tri.y[0] = y;
			tri.z[0] = m_ZMap.at<float>(y, x);

			float h;

			h = 330 - ((tri.z[0] - dMin) / (dMax - dMin)) * 330;

			HSLToRGB(h, 1, 0.5, tri.ColorR[0], tri.ColorG[0], tri.ColorB[0]);

			tri.TexPosX[0] = tri.x[0] / m_ZMap.cols;
			tri.TexPosY[0] = tri.y[0] / m_ZMap.rows;

			tri.x[1] = x + 1;
			tri.y[1] = y;
			tri.z[1] = m_ZMap.at<float>(tri.y[1], tri.x[1]);

			h = 330 - ((tri.z[1] - dMin) / (dMax - dMin)) * 330;

			HSLToRGB(h, 1, 0.5, tri.ColorR[1], tri.ColorG[1], tri.ColorB[1]);

			tri.TexPosX[1] = tri.x[1] / m_ZMap.cols;
			tri.TexPosY[1] = tri.y[1] / m_ZMap.rows;

			tri.x[2] = x + 1;
			tri.y[2] = y + 1;
			tri.z[2] = m_ZMap.at<float>(tri.y[2], tri.x[2]);

			h = 330 - ((tri.z[1] - dMin) / (dMax - dMin)) * 330;

			HSLToRGB(h, 1, 0.5, tri.ColorR[2], tri.ColorG[2], tri.ColorB[2]);

			tri.TexPosX[2] = tri.x[2] / m_ZMap.cols;
			tri.TexPosY[2] = tri.y[2] / m_ZMap.rows;
			tri.CalcNormalVec();





			m_triangles.push_back(tri);

			tri.x[0] = x;
			tri.y[0] = y;
			tri.z[0] = m_ZMap.at<float>(y, x);
			tri.TexPosX[0] = tri.x[0] / m_ZMap.cols;
			tri.TexPosY[0] = tri.y[0] / m_ZMap.rows;

			h = 330 - ((tri.z[0] - dMin) / (dMax - dMin)) * 330;

			HSLToRGB(h, 1, 0.5, tri.ColorR[0], tri.ColorG[0], tri.ColorB[0]);

			tri.x[1] = x + 1;
			tri.y[1] = y + 1;
			tri.z[1] = m_ZMap.at<float>(tri.y[1], tri.x[1]);
			tri.TexPosX[1] = tri.x[1] / m_ZMap.cols;
			tri.TexPosY[1] = tri.y[1] / m_ZMap.rows;

			h = 330 - ((tri.z[1] - dMin) / (dMax - dMin)) * 330;

			HSLToRGB(h, 1, 0.5, tri.ColorR[1], tri.ColorG[1], tri.ColorB[1]);

			tri.x[2] = x;
			tri.y[2] = y + 1;
			tri.z[2] = m_ZMap.at<float>(tri.y[2], tri.x[2]);

			h = 330 - ((tri.z[1] - dMin) / (dMax - dMin)) * 330;

			HSLToRGB(h, 1, 0.5, tri.ColorR[2], tri.ColorG[2], tri.ColorB[2]);


			tri.TexPosX[2] = tri.x[2] / m_ZMap.cols;
			tri.TexPosY[2] = tri.y[2] / m_ZMap.rows;
			tri.CalcNormalVec();

			m_triangles.push_back(tri);
		}
	}
	if (!m_GrayImg.empty())
	{
		LoadTextureGray(m_GrayImg);
	}

	if (!m_ColorImg.empty())
	{
		LoadTexture(m_ColorImg);
	}
	m_bMeshCreated = 1;
}

void C3DModel::LoadTexture(cv::Mat mat)
{
	if (m_bTextureLoaded)
		FreeTexture();

	cv::Mat matResize;
	cv::resize(mat, matResize, cv::Size(512, 512));

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, matResize.cols, matResize.rows, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, matResize.ptr<BYTE>(0));
	m_bTextureLoaded = 1;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void C3DModel::LoadTextureGray(cv::Mat mat)
{
	if (m_bTextureLoadedGray)
		FreeTextureGray();
	cv::Mat matResize;
	cv::Mat matColor;

	cv::cvtColor(mat, matColor, cv::COLOR_GRAY2BGR);

	cv::resize(matColor, matResize, cv::Size(512, 512));
	glBindTexture(GL_TEXTURE_2D, m_TextureGray);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, matResize.cols, matResize.rows, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, matResize.ptr<BYTE>(0));
	m_bTextureLoadedGray = 1;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void C3DModel::ApplyScaleAndOffset(double dOffsetX, double dOffsetY, double dOffsetZ, double dX, double dY, double dZ)
{
	size_t nSize = m_triangles.size();

	for (int i = 0; i < nSize; i++)
	{
		stTagTriangles& tri = m_triangles[i];

		int k = 0;

		tri.x[0] = (tri.x[0] + dOffsetX) *dX;
		tri.x[1] = (tri.x[1] + dOffsetX) *dX;
		tri.x[2] = (tri.x[2] + dOffsetX) * dX;

		tri.y[0] = (tri.y[0] + dOffsetY) * dY;
		tri.y[1] = (tri.y[1] + dOffsetY) * dY;
		tri.y[2] = (tri.y[2] + dOffsetY) * dY;

		tri.z[0] = (tri.z[0] + dOffsetZ) * dZ;
		tri.z[1] = (tri.z[1] + dOffsetZ) * dZ;
		tri.z[2] = (tri.z[2] + dOffsetZ) * dZ;
	}
}

void C3DModel::Draw(TextureMode mode)
{
	if (m_bMeshCreated)
	{
		int nSize = m_triangles.size();
		//m_draw.SetColor(RGB_WHITE);
		glColor3f(1, 1, 1);
		if (mode == TEX_LUT)
		{
			if (m_bTextureLoaded)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, m_Texture);
			}
		}
		else if (mode == TEX_AMPLITUDE)
		{
			if (m_bTextureLoadedGray)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, m_TextureGray);
			}
		}

		if (mode == TEX_COLOR)
		{
			for (int i = 0; i < nSize; i++)
			{
				glBegin(GL_POLYGON);

				stTagTriangles tri = m_triangles[i];

				int k = 0;

				for (k = 0; k < 3; k++)
				{
					glColor3f(tri.ColorR[k], tri.ColorG[k], tri.ColorB[k]);
					glTexCoord2f(tri.TexPosX[k], tri.TexPosY[k]);
					glVertex3f(tri.x[k], tri.y[k], tri.z[k]);
				}

				glNormal3f(tri.dNormalVec[0], tri.dNormalVec[1], tri.dNormalVec[2]);
				glEnd();

			}
		}
		else
		{
			for (int i = 0; i < nSize; i++)
			{
				glBegin(GL_POLYGON);

				stTagTriangles tri = m_triangles[i];

				int k = 0;
				for (k = 0; k < 3; k++)
				{
					glTexCoord2f(tri.TexPosX[k], tri.TexPosY[k]);
					glVertex3f(tri.x[k], tri.y[k], tri.z[k]);
				}

				glNormal3f(tri.dNormalVec[0], tri.dNormalVec[1], tri.dNormalVec[2]);
				glEnd();
			}
		}

		if (mode == TEX_LUT)
		{
			if (m_bTextureLoaded)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisable(GL_TEXTURE_2D);
			}
		}
		else if (mode == TEX_AMPLITUDE)
		{
			if (m_bTextureLoadedGray)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisable(GL_TEXTURE_2D);
			}
		}
	}
}

