#include "stdafx.h"
#include "OpenGLFBO.h"
#include "glext.h"
#include "GlobalDefine.h"
#include "glInfo.h"

// Framebuffer object
static PFNGLGENFRAMEBUFFERSPROC                     pglGenFramebuffers = 0;                      // FBO name generation procedure
static PFNGLDELETEFRAMEBUFFERSPROC                  pglDeleteFramebuffers = 0;                   // FBO deletion procedure
static PFNGLBINDFRAMEBUFFERPROC                     pglBindFramebuffer = 0;                      // FBO bind procedure
static PFNGLCHECKFRAMEBUFFERSTATUSPROC              pglCheckFramebufferStatus = 0;               // FBO completeness test procedure
static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pglGetFramebufferAttachmentParameteriv = 0;  // return various FBO parameters
static PFNGLGENERATEMIPMAPPROC                      pglGenerateMipmap = 0;                       // FBO automatic mipmap generation procedure
static PFNGLFRAMEBUFFERTEXTURE2DPROC                pglFramebufferTexture2D = 0;                 // FBO texdture attachement procedure
static PFNGLFRAMEBUFFERRENDERBUFFERPROC             pglFramebufferRenderbuffer = 0;              // FBO renderbuffer attachement procedure
// Renderbuffer object
static PFNGLGENRENDERBUFFERSPROC                    pglGenRenderbuffers = 0;                     // renderbuffer generation procedure
static PFNGLDELETERENDERBUFFERSPROC                 pglDeleteRenderbuffers = 0;                  // renderbuffer deletion procedure
static PFNGLBINDRENDERBUFFERPROC                    pglBindRenderbuffer = 0;                     // renderbuffer bind procedure
static PFNGLRENDERBUFFERSTORAGEPROC                 pglRenderbufferStorage = 0;                  // renderbuffer memory allocation procedure
static PFNGLGETRENDERBUFFERPARAMETERIVPROC          pglGetRenderbufferParameteriv = 0;           // return various renderbuffer parameters
static PFNGLISRENDERBUFFERPROC                      pglIsRenderbuffer = 0;                       // determine renderbuffer object type

#define glGenFramebuffers							pglGenFramebuffers
#define glDeleteFramebuffers						pglDeleteFramebuffers
#define glBindFramebuffer							pglBindFramebuffer
#define glCheckFramebufferStatus					pglCheckFramebufferStatus
#define glGetFramebufferAttachmentParameteriv		pglGetFramebufferAttachmentParameteriv
#define glGenerateMipmap							pglGenerateMipmap
#define glFramebufferTexture2D						pglFramebufferTexture2D
#define glFramebufferRenderbuffer					pglFramebufferRenderbuffer

#define glGenRenderbuffers							pglGenRenderbuffers
#define glDeleteRenderbuffers						pglDeleteRenderbuffers
#define glBindRenderbuffer							pglBindRenderbuffer
#define glRenderbufferStorage						pglRenderbufferStorage
#define glGetRenderbufferParameteriv				pglGetRenderbufferParameteriv
#define glIsRenderbuffer							pglIsRenderbuffer

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGLFBO::COpenGLFBO()
{
	m_bInit=FALSE;
	m_crBackColor = 0;
	int i;

	m_bFboReady = FALSE;
	for(i=0;i<10;i++)
	{
		m_nTextureId[i] = 0;
		m_nFboId[i] = 0;
		m_nRboId[i] = 0;
	}
	for(i=0;i<10;i++)
	{
		m_nTexturePanelId[i] = 0;
		m_nFboPanelId[i] = 0;
		m_nRboPanelId[i] = 0;
	}
	m_nNumOfSize = 0;
	m_nFboImgId = 0;
	m_nRboImgColorId = 0;
	m_nRboImgDepthStencilId = 0;


	m_nFboAttrId = 0;      
	m_nTextureAttrId = 0;       
	m_nRboAttrId = 0;  
	m_nFboAttrPanelId = 0;      
	m_nTextureAttrPanelId = 0;       
	m_nRboAttrPanelId = 0; 
}

COpenGLFBO::~COpenGLFBO()
{
	Remove();
	int nErrorCode;
	CString strMsg;
	nErrorCode = glGetError();
	if(m_nFboImgId>0)
	{
		glDeleteFramebuffers(1,&m_nFboImgId);
		m_nFboImgId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
                strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
		}
	}
	if(m_nRboImgColorId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboImgColorId);
		m_nRboImgColorId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
                strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"), nErrorCode);
			AfxMessageBox(strMsg);
		}
	}
	if(m_nRboImgDepthStencilId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboImgDepthStencilId);
		m_nRboImgDepthStencilId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
                strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"), nErrorCode);
			AfxMessageBox(strMsg);
		}
	}

}

BOOL COpenGLFBO::GenerateFrameBuffer(int nSize)
{
	if(!m_bFboReady)
		return FALSE;
	int nError = glGetError(); 
	CString strMsg;
	glGenFramebuffers(nSize, m_nFboId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenFramebuffers ErrorCode: %d"),nError);
        AfxMessageBox(strMsg);
		return FALSE;
	}
	nError = glGetError();
	glGenFramebuffers(nSize, m_nFboPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenFramebuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glGenFramebuffers(1, &m_nFboAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenFramebuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glGenFramebuffers(1, &m_nFboAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenFramebuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	return TRUE;
}

BOOL COpenGLFBO::GenerateRenderBuffer(int nSize,int nWindowWidth, int nWindowHeight)
{
	if(!m_bFboReady)
		return FALSE;
	int i,nError = glGetError();
	CString strMsg;
	glGenRenderbuffers(nSize, m_nRboId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenRenderbuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glGenRenderbuffers(nSize, m_nRboPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenRenderbuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glGenRenderbuffers(1, &m_nRboAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenRenderbuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glGenRenderbuffers(1, &m_nRboAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenRenderbuffers ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}

	for(i=0;i<nSize;i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
        glBindRenderbuffer(GL_RENDERBUFFER, m_nRboId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL,nWindowWidth, nWindowHeight);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glRenderbufferStorage ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
        	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nTextureId[i], 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glFramebufferTexture2D ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_nRboId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_nRboId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	for(i=0;i<nSize;i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboPanelId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
        glBindRenderbuffer(GL_RENDERBUFFER, m_nRboPanelId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL,nWindowWidth, nWindowHeight);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glRenderbufferStorage ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nTexturePanelId[i], 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glFramebufferTexture2D ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_nRboPanelId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_nRboPanelId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}


	glBindFramebuffer(GL_FRAMEBUFFER, m_nFboAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, m_nRboAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL,nWindowWidth, nWindowHeight);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glRenderbufferStorage ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nTextureAttrId, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glFramebufferTexture2D ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_nRboAttrId);
	nError = glGetError();																																//// 20170901 Error
	if(nError)
	{
		strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_nRboAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	

	//////////////////////////////////////////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, m_nFboAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, m_nRboAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL,nWindowWidth, nWindowHeight);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glRenderbufferStorage ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nTextureAttrPanelId, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glFramebufferTexture2D ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_nRboAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_nRboAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}
BOOL COpenGLFBO::GenerateTexture(int nSize,int nWindowWidth, int nWindowHeight)
{
	if(!m_bFboReady)
		return FALSE;
	int i,nError = glGetError();
	CString strMsg;
	glGenTextures(nSize,m_nTextureId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenTextures ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	for(i=0;i<nSize;i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_nTextureId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWindowWidth, nWindowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexImage2D ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	glGenTextures(nSize,m_nTexturePanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenTextures ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	for(i=0;i<nSize;i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_nTexturePanelId[i]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWindowWidth, nWindowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glTexImage2D ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}


	nError = glGetError();
	glGenTextures(1,&m_nTextureAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenTextures ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, m_nTextureAttrId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWindowWidth, nWindowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexImage2D ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	} 


	nError = glGetError();
	glGenTextures(1,&m_nTextureAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glGenTextures ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, m_nTextureAttrPanelId);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameterf ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexParameteri ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWindowWidth, nWindowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glTexImage2D ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	} 
	return TRUE;
}

BOOL COpenGLFBO::Init(int nSize,int nWindowWidth, int nWindowHeight,BOOL bUsePBO)
{
	if(!m_bFboReady)
		return FALSE;
	m_nNumOfSize = nSize;
	m_nWidth=nWindowWidth;
	m_nHeight=nWindowHeight;
	CString strMsg;
	Remove();
	if(!GenerateTexture(nSize,nWindowWidth, nWindowHeight))
	{
		strMsg.Format(_T("Fail!! Init Error (GenerateTexture)"));
		AfxMessageBox(strMsg);
		return FALSE;
	}
	if(!GenerateFrameBuffer(nSize))
	{
		strMsg.Format(_T("Fail!! Init Error (GenerateFrameBuffer)"));
		AfxMessageBox(strMsg);
		return FALSE;
	}
	if(!GenerateRenderBuffer(nSize,nWindowWidth, nWindowHeight))
	{
		strMsg.Format(_T("Fail!! Init Error (GenerateRenderBuffer)"));
		AfxMessageBox(strMsg);
		return FALSE;
	}
	BOOL bStatus = CheckFramebufferStatus();
//	if(!bStatus)
//	{
//		m_bFboReady = bStatus;
//	}
	m_bUsePBO=bUsePBO;


	

	m_bInit=TRUE;
	return TRUE;
}

BOOL COpenGLFBO::Remove()
{
	if(!m_bFboReady)
		return FALSE;
	int i,nError = glGetError();
	CString strMsg;
	for( i=0;i<10;i++)
	{
		if(m_nTextureId[i]>0)
		{
			glDeleteTextures(1,&m_nTextureId[i]);
			m_nTextureId[i] = 0;
			nError = glGetError();
			if(nError)
			{
				strMsg.Format(_T("glDeleteTextures ErrorCode: %d"),nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
	}
	for( i=0;i<10;i++)
	{
		if(m_nFboId[i]>0)
		{
			glDeleteFramebuffers(1,&m_nFboId[i]);
			m_nFboId[i] = 0;
			nError = glGetError();
			if(nError)
			{
				strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
	}
	for( i=0;i<10;i++)
	{
		if(m_nRboId[i]>0)
		{
			glDeleteRenderbuffers(1,&m_nRboId[i]);
			m_nRboId[i] = 0;
			nError = glGetError();
			if(nError)
			{
				strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
	}
//////////////////////////
	for( i=0;i<10;i++)
	{
		if(m_nTexturePanelId[i]>0)
		{
			glDeleteTextures(1,&m_nTexturePanelId[i]);
			m_nTexturePanelId[i] = 0;
			nError = glGetError();
			if(nError)
			{
				strMsg.Format(_T("glDeleteTextures ErrorCode: %d"),nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
	}
	for( i=0;i<10;i++)
	{
		if(m_nFboPanelId[i]>0)
		{
			glDeleteFramebuffers(1,&m_nFboPanelId[i]);
			m_nFboPanelId[i] = 0;
			nError = glGetError();
			if(nError)
			{
				strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
	}
	for( i=0;i<10;i++)
	{
		if(m_nRboPanelId[i]>0)
		{
			glDeleteRenderbuffers(1,&m_nRboPanelId[i]);
			m_nRboPanelId[i] = 0;
			nError = glGetError();
			if(nError)
			{
				strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
		}
	}
	m_bInit=FALSE;
	if(m_nTextureAttrId>0)
	{
		glDeleteTextures(1,&m_nTextureAttrId);
		m_nTextureAttrId = 0;
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glDeleteTextures ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if(m_nFboAttrId>0)
	{
		glDeleteFramebuffers(1,&m_nFboAttrId);
		m_nFboAttrId = 0;
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if(m_nRboAttrId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboAttrId);
		m_nRboAttrId = 0;
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if (m_nTextureAttrPanelId > 0)
	{
		glDeleteTextures(1, &m_nTextureAttrPanelId);
		m_nTextureAttrPanelId = 0;
		nError = glGetError();
		if (nError)
		{
			strMsg.Format(_T("glDeleteTextures ErrorCode: %d"), nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if (m_nFboAttrPanelId > 0)
	{
		glDeleteFramebuffers(1, &m_nFboAttrPanelId);
		m_nFboAttrPanelId = 0;
		nError = glGetError();
		if (nError)
		{
			strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"), nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if (m_nRboAttrPanelId > 0)
	{
		glDeleteRenderbuffers(1, &m_nRboAttrPanelId);
		m_nRboAttrPanelId = 0;
		nError = glGetError();
		if (nError)
		{
			strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"), nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL COpenGLFBO::ClearAttrFrameBuffer(int nRenderMode)
{
	if(!m_bFboReady)
		return FALSE;

	int nError = glGetError();
	CString strMsg;
	if(nRenderMode == LOAD_TEXTURE_PARTIAL )
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboAttrId);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		GLfloat red = GetRValue(m_crBackColor) / 255.0f;
		GLfloat green = GetGValue(m_crBackColor) / 255.0f;
		GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
		glClearColor(red, green, blue, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	else if(nRenderMode == LOAD_TEXTURE_ALL)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboAttrPanelId);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		GLfloat red = GetRValue(m_crBackColor) / 255.0f;
		GLfloat green = GetGValue(m_crBackColor) / 255.0f;
		GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
		glClearColor(red, green, blue, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	return TRUE;
}
BOOL COpenGLFBO::ClearFrameBuffer(int nRenderMode, int nIndex)
{
	if(!m_bFboReady)
		return FALSE;
	int i,nError = glGetError();
	CString strMsg;
	if(nRenderMode == LOAD_TEXTURE_ALL )
	{
		if (nIndex >= 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			nError = glGetError();
			if (nError)
			{
				strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
			glBindFramebuffer(GL_FRAMEBUFFER, m_nFboPanelId[nIndex]);
			nError = glGetError();
			if (nError)
			{
				strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
			GLfloat red = GetRValue(m_crBackColor) / 255.0f;
			GLfloat green = GetGValue(m_crBackColor) / 255.0f;
			GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
			glClearColor(red, green, blue, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		else
		{
			for (i = 0; i < m_nNumOfSize; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				nError = glGetError();
				if (nError)
				{
					strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
					AfxMessageBox(strMsg);
					return FALSE;
				}
				glBindFramebuffer(GL_FRAMEBUFFER, m_nFboPanelId[i]);
				nError = glGetError();
				if (nError)
				{
					strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
					AfxMessageBox(strMsg);
					return FALSE;
				}
				GLfloat red = GetRValue(m_crBackColor) / 255.0f;
				GLfloat green = GetGValue(m_crBackColor) / 255.0f;
				GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
				glClearColor(red, green, blue, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			}
		}
	}
	else if(nRenderMode == LOAD_TEXTURE_PARTIAL)
	{
		if (nIndex >= 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			nError = glGetError();
			if (nError)
			{
				strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
			glBindFramebuffer(GL_FRAMEBUFFER, m_nFboId[nIndex]);
			nError = glGetError();
			if (nError)
			{
				strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
				AfxMessageBox(strMsg);
				return FALSE;
			}
			GLfloat red = GetRValue(m_crBackColor) / 255.0f;
			GLfloat green = GetGValue(m_crBackColor) / 255.0f;
			GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
			glClearColor(red, green, blue, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		else
		{
			for (i = 0; i < m_nNumOfSize; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				nError = glGetError();
				if (nError)
				{
					strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
					AfxMessageBox(strMsg);
					return FALSE;
				}
				glBindFramebuffer(GL_FRAMEBUFFER, m_nFboId[i]);
				nError = glGetError();
				if (nError)
				{
					strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
					AfxMessageBox(strMsg);
					return FALSE;
				}
				GLfloat red = GetRValue(m_crBackColor) / 255.0f;
				GLfloat green = GetGValue(m_crBackColor) / 255.0f;
				GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
				glClearColor(red, green, blue, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			}
		}
	}
	return TRUE;
}
BOOL COpenGLFBO::BindAttrFrameBuffer(int nRenderMode)
{
	if(!m_bFboReady)
		return FALSE;
	int nError = glGetError();	
	CString strMsg;
	if(nRenderMode == LOAD_TEXTURE_PARTIAL )
	{
		if(!UnBindAttrFrameBuffer(nRenderMode))
		{
			strMsg.Format(_T("Fail UnBindAttrFrameBuffer Error"));
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboAttrId);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	else if(nRenderMode == LOAD_TEXTURE_ALL)
	{
		if(!UnBindAttrFrameBuffer(nRenderMode))
		{
			strMsg.Format(_T("Fail UnBindAttrFrameBuffer Error"));
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboAttrPanelId);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL COpenGLFBO::BindFrameBuffer(int nRenderMode,int nIndex)
{
	if(!m_bFboReady)
		return FALSE;
	int nError = glGetError();
	CString strMsg;
	if(nRenderMode == LOAD_TEXTURE_PARTIAL )
	{				
		if(!UnBindFrameBuffer(nRenderMode,nIndex))
		{
			strMsg.Format(_T("Fail UnBindAttrFrameBuffer Error"));
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboId[nIndex]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		
	}
	else if(nRenderMode == LOAD_TEXTURE_ALL )
	{
		if(!UnBindFrameBuffer(nRenderMode,nIndex))
		{
			strMsg.Format(_T("Fail UnBindAttrFrameBuffer Error"));
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, m_nFboPanelId[nIndex]);		
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL COpenGLFBO::UnBindAttrFrameBuffer(int nRenderMode)
{
	if(!m_bFboReady)
		return FALSE;
	int nError = glGetError();
	CString strMsg;

	if(nRenderMode == LOAD_TEXTURE_PARTIAL )
	{				
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		GLfloat red = GetRValue(m_crBackColor) / 255.0f;
		GLfloat green = GetGValue(m_crBackColor) / 255.0f;
		GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
		glClearColor(red, green, blue, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
		glBindTexture(GL_TEXTURE_2D, m_nTextureAttrId);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glGenerateMipmap ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindTexture(GL_TEXTURE_2D, 0);			
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	else if(nRenderMode == LOAD_TEXTURE_ALL )
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		GLfloat red = GetRValue(m_crBackColor) / 255.0f;
		GLfloat green = GetGValue(m_crBackColor) / 255.0f;
		GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
		glClearColor(red, green, blue, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
		glBindTexture(GL_TEXTURE_2D, m_nTextureAttrPanelId);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glGenerateMipmap ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindTexture(GL_TEXTURE_2D, 0);			
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL COpenGLFBO::UnBindFrameBuffer(int nRenderMode,int nIndex)
{
	if(!m_bFboReady)
		return FALSE;
	int nError = glGetError();
	CString strMsg;
	if(nRenderMode == LOAD_TEXTURE_PARTIAL )
	{				
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		GLfloat red = GetRValue(m_crBackColor) / 255.0f;
		GLfloat green = GetGValue(m_crBackColor) / 255.0f;
		GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
		glClearColor(red, green, blue, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
		glBindTexture(GL_TEXTURE_2D, m_nTextureId[nIndex]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glGenerateMipmap ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindTexture(GL_TEXTURE_2D, 0);			
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	else if(nRenderMode == LOAD_TEXTURE_ALL )
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		GLfloat red = GetRValue(m_crBackColor) / 255.0f;
		GLfloat green = GetGValue(m_crBackColor) / 255.0f;
		GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
		glClearColor(red, green, blue, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
		glBindTexture(GL_TEXTURE_2D, m_nTexturePanelId[nIndex]);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glGenerateMipmap ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
		glBindTexture(GL_TEXTURE_2D, 0);			
		nError = glGetError();
		if(nError)
		{
			strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL COpenGLFBO::BindAttrTexture(int nRenderMode,CdPoint3D fptStart,CdPoint3D fptEnd)
{
	if(!m_bFboReady && m_nTextureAttrId<1)
		return FALSE;
	CString strMsg;
	int nError = glGetError();
	if(nRenderMode == LOAD_TEXTURE_PARTIAL || nRenderMode == DRAW_TEXTURE_PARTIAL)
	{
		glBindTexture(GL_TEXTURE_2D, m_nTextureAttrId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_nTextureAttrPanelId);
	}
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);  glVertex2f(fptStart.x , fptStart.y);
	glTexCoord2f(0,1);  glVertex2f(fptStart.x , fptEnd.y);
	glTexCoord2f(1,1);  glVertex2f(fptEnd.x, fptEnd.y);
	glTexCoord2f(1,0);  glVertex2f(fptEnd.x, fptStart.y);
	glEnd();
	return TRUE;
}
BOOL COpenGLFBO::BindTexture(int nRenderMode,int nIndex,CdPoint3D fptStart,CdPoint3D fptEnd)
{
	if(!m_bFboReady && m_nTextureId[nIndex]<1)
		return FALSE;
	CString strMsg;
	int nError = glGetError();
	if(nRenderMode == LOAD_TEXTURE_PARTIAL || nRenderMode == DRAW_TEXTURE_PARTIAL)
	{				
		glBindTexture(GL_TEXTURE_2D, m_nTextureId[nIndex]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_nTexturePanelId[nIndex]);
	}
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);  glVertex2f(fptStart.x , fptStart.y);
	glTexCoord2f(0,1);  glVertex2f(fptStart.x , fptEnd.y);
	glTexCoord2f(1,1);  glVertex2f(fptEnd.x, fptEnd.y);
	glTexCoord2f(1,0);  glVertex2f(fptEnd.x, fptStart.y);
	glEnd();
	return TRUE;
}
BOOL COpenGLFBO::UnBindTexture()
{
	if(!m_bFboReady)
		return FALSE;
	int nError = glGetError();
	CString strMsg;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	nError = glGetError();
	if(nError)
	{
		strMsg.Format(_T("glBindTexture ErrorCode: %d"),nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	GLfloat red = GetRValue(m_crBackColor) / 255.0f;
	GLfloat green = GetGValue(m_crBackColor) / 255.0f;
	GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
	glClearColor(red, green, blue, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	return TRUE;
}

BOOL COpenGLFBO::InitFboImage(int &nErrorCode,int nWidth,int nHeight)
{
	if(!m_bFboReady)
		return FALSE;
	CString strMsg;
	nErrorCode = glGetError();
	if(m_nFboImgId>0)
	{
		glDeleteFramebuffers(1,&m_nFboImgId);
		m_nFboImgId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
			strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if(m_nRboImgColorId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboImgColorId);
		m_nRboImgColorId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
			strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}
	if(m_nRboImgDepthStencilId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboImgDepthStencilId);
		m_nRboImgDepthStencilId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
			strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}

	if(!m_bFboReady)
	{
		return FALSE;
	}
	nErrorCode = glGetError();
	glGenFramebuffers(1, &m_nFboImgId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glGenFramebuffers ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, m_nFboImgId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}

	/////////////////////////////////////////
	// render buffer as color buffer
	glGenRenderbuffers(1, &m_nRboImgColorId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, m_nRboImgColorId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{

		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}			
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, nWidth, nHeight);
	nErrorCode = glGetError();
	if(nErrorCode == GL_INVALID_ENUM)
		nErrorCode = GL_INVALID_ENUM;
	else if(nErrorCode == GL_INVALID_VALUE)
		nErrorCode = GL_INVALID_VALUE;
	else if(nErrorCode == GL_OUT_OF_MEMORY)
		nErrorCode = GL_OUT_OF_MEMORY;
	else if(nErrorCode == GL_INVALID_OPERATION)
		nErrorCode = GL_INVALID_OPERATION;
	if(nErrorCode)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		strMsg.Format(_T("glRenderbufferStorage ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	// attach render buffer to the fbo as color buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_nRboImgColorId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}			

	//////////////////////////////////////////////
	// render buffer as stencil buffer
	glGenRenderbuffers(1, &m_nRboImgDepthStencilId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		strMsg.Format(_T("glGenRenderbuffers ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, m_nRboImgDepthStencilId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgDepthStencilId);
		m_nRboImgDepthStencilId = 0;
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, nWidth, nHeight);
	nErrorCode = glGetError();
	if(nErrorCode == GL_INVALID_ENUM)
		nErrorCode = GL_INVALID_ENUM;
	else if(nErrorCode == GL_INVALID_VALUE)
		nErrorCode = GL_INVALID_VALUE;
	else if(nErrorCode == GL_OUT_OF_MEMORY)
		nErrorCode = GL_OUT_OF_MEMORY;
	else if(nErrorCode == GL_INVALID_OPERATION)
		nErrorCode = GL_INVALID_OPERATION;
	if(nErrorCode) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgDepthStencilId);
		m_nRboImgDepthStencilId = 0;
		strMsg.Format(_T("glRenderbufferStorage ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	// attach render buffer to the fbo as stencil buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_nRboImgDepthStencilId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glDeleteFramebuffers(1, &m_nFboImgId);
		m_nFboImgId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgColorId);
		m_nRboImgColorId = 0;
		glBindRenderbuffer(GL_RENDERBUFFER,0);
		glDeleteRenderbuffers(1, &m_nRboImgDepthStencilId);
		m_nRboImgDepthStencilId = 0;
		strMsg.Format(_T("glFramebufferRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
		return FALSE;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	return TRUE;
}
BOOL COpenGLFBO::ClearFboImage()
{
	if (!m_bFboReady)
		return FALSE;

	int nError = glGetError();
	CString strMsg;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	nError = glGetError();
	if (nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, m_nFboImgId);
	nError = glGetError();
	if (nError)
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"), nError);
		AfxMessageBox(strMsg);
		return FALSE;
	}
	GLfloat red = GetRValue(m_crBackColor) / 255.0f;
	GLfloat green = GetGValue(m_crBackColor) / 255.0f;
	GLfloat blue = GetBValue(m_crBackColor) / 255.0f;
	glClearColor(red, green, blue, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	return TRUE;
}
BOOL COpenGLFBO::BindFboImage()
{
	if(!m_bFboReady)
		return FALSE;
	int nErrorCode = glGetError();
	CString strMsg;
	glBindFramebuffer(GL_FRAMEBUFFER,m_nFboImgId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
	}
	glBindRenderbuffer(GL_RENDERBUFFER,m_nRboImgColorId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
	}
	glBindRenderbuffer(GL_RENDERBUFFER,m_nRboImgDepthStencilId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
	}
	return TRUE;
}

BOOL COpenGLFBO::CleanFboImage()
{
	if(!m_bFboReady)
		return FALSE;
	CString strMsg;
	int nErrorCode = glGetError();
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glBindFramebuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
	}
	glDeleteFramebuffers(1, &m_nFboImgId);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
	}
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	nErrorCode = glGetError();
	if(nErrorCode) 
	{
		strMsg.Format(_T("glBindRenderbuffer ErrorCode: %d"),nErrorCode);
		AfxMessageBox(strMsg);
	}
	if(m_nFboImgId>0)
	{
		glDeleteFramebuffers(1,&m_nFboImgId);
		m_nFboImgId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
			strMsg.Format(_T("glDeleteFramebuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
		}
	}
	if(m_nRboImgColorId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboImgColorId);
		m_nRboImgColorId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
			strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
		}
	}
	if(m_nRboImgDepthStencilId>0)
	{
		glDeleteRenderbuffers(1,&m_nRboImgDepthStencilId);
		m_nRboImgDepthStencilId = 0;
		nErrorCode = glGetError();
		if(nErrorCode)
		{
			strMsg.Format(_T("glDeleteRenderbuffers ErrorCode: %d"),nErrorCode);
			AfxMessageBox(strMsg);
		}
	}
	glFinish();
	return TRUE;
}

BOOL COpenGLFBO::CreateFbo()
{
    // get OpenGL info
    GL_INFO stglInfo;


    // check if FBO is supported by your video card
    if(stglInfo.isExtensionSupported("GL_ARB_framebuffer_object"))
    {
		// get pointers to GL functions
		glGenFramebuffers                     = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
		glDeleteFramebuffers                  = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
		glBindFramebuffer                     = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
		glCheckFramebufferStatus              = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
		glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
		glGenerateMipmap                      = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
		glFramebufferTexture2D                = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
		glFramebufferRenderbuffer             = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
		glGenRenderbuffers                    = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
		glDeleteRenderbuffers                 = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
		glBindRenderbuffer                    = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
		glRenderbufferStorage                 = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
		glGetRenderbufferParameteriv          = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
		glIsRenderbuffer                      = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");

		// check once again FBO extension
		if(glGenFramebuffers && glDeleteFramebuffers && glBindFramebuffer && glCheckFramebufferStatus &&
		   glGetFramebufferAttachmentParameteriv && glGenerateMipmap && glFramebufferTexture2D && glFramebufferRenderbuffer &&
		   glGenRenderbuffers && glDeleteRenderbuffers && glBindRenderbuffer && glRenderbufferStorage &&
		   glGetRenderbufferParameteriv && glIsRenderbuffer)
		{
			m_bFboReady = TRUE;
		}
		else
		{
			m_bFboReady = FALSE;
		}
    }
	else
	{
		m_bFboReady = FALSE;
	}
	return m_bFboReady;
}

BOOL COpenGLFBO::CheckFramebufferStatus()
{
	// check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	CString strTemp;
	switch(status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		return true;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Attachment is NOT complete."));
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: No image is attached to FBO."));
		return false;
	
//	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
//		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Attached images have different dimensions."));
//		return false;

//	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
//		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Color attached images have different internal formats."));
//		return false;
	
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Draw buffer."));
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Read buffer."));
		return false;

	case GL_FRAMEBUFFER_UNSUPPORTED:
		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Unsupported by FBO implementation."));
		return false;

	default:
		AfxMessageBox(_T("[ERROR] Framebuffer incomplete: Unknown error."));
		return false;
	}
}
void COpenGLFBO::SetBackGroundColor(COLORREF crColor)
{
	m_crBackColor = crColor;
}