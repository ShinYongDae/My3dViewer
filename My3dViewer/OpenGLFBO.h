// OpenGLFBO.h: interface for the COpenGLFBO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLFBO_H__EC7ACB92_63D7_4276_9B13_A1CA7AD4CE51__INCLUDED_)
#define AFX_OPENGLFBO_H__EC7ACB92_63D7_4276_9B13_A1CA7AD4CE51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gl/freeglut_std.h>
#pragma comment (lib, "freeglut.lib")


#include "GeoDataType.h"

class COpenGLFBO  
{
public:
	int m_nWidth;
	int m_nHeight;
	BOOL m_bUsePBO;
	void SetBackGroundColor(COLORREF crColor);
	BOOL CheckFramebufferStatus();
	BOOL CreateFbo();
	BOOL Remove();
	BOOL GenerateTexture(int nSize,int nWindowWidth, int nWindowHeight);
	BOOL Init(int nSize,int nWindowWidth, int nWindowHeight,BOOL bUsePBO=FALSE);
	BOOL GenerateRenderBuffer(int nSize,int nWindowWidth, int nWindowHeight);
	BOOL GenerateFrameBuffer(int nSize);
	BOOL BindFrameBuffer(int nRenderMode,int nIndex);
	BOOL UnBindFrameBuffer(int nRenderMode,int nIndex);
	BOOL ClearFrameBuffer(int nRenderMode, int nIndex = -1);


	BOOL BindAttrFrameBuffer(int nRenderMode);
	BOOL UnBindAttrFrameBuffer(int nRenderMode);
	BOOL ClearAttrFrameBuffer(int nRenderMode);
	BOOL BindAttrTexture(int nRenderMode,CdPoint3D fptStart,CdPoint3D fptEnd);

	BOOL BindTexture(int nRenderMode,int nIndex,CdPoint3D fptStart,CdPoint3D fptEnd);
	BOOL UnBindTexture();

	BOOL InitFboImage(int &nErrorCode,int nWidth,int nHeight);
	BOOL CleanFboImage();
	BOOL BindFboImage();
	BOOL ClearFboImage();







	COpenGLFBO();
	virtual ~COpenGLFBO();
public: 
	BOOL m_bInit; //140827 lgh add
	BOOL m_bFboReady;
	GLuint m_nFboId[10];                       // ID of FBO
	GLuint m_nTextureId[10];                   // ID of texture
	GLuint m_nRboId[10];                       // ID of Renderbuffer object


	GLuint m_nFboPanelId[10];
	GLuint m_nTexturePanelId[10];
	GLuint m_nRboPanelId[10];
	GLuint m_nFboImgId;
	GLuint m_nRboImgColorId;
	GLuint m_nRboImgDepthStencilId;

	GLuint m_nFboAttrId;      
	GLuint m_nTextureAttrId;       
	GLuint m_nRboAttrId;   
	
	GLuint m_nFboAttrPanelId;      
	GLuint m_nTextureAttrPanelId;       
	GLuint m_nRboAttrPanelId;   
	int m_nNumOfSize;
	COLORREF m_crBackColor;

};

#endif // !defined(AFX_OPENGLFBO_H__EC7ACB92_63D7_4276_9B13_A1CA7AD4CE51__INCLUDED_)
