///////////////////////////////////////////////////////////////////////////////
// glInfo.cpp
// ==========
// get GL vendor, version, supported extensions and other states using glGet*
// functions and store them glInfo struct variable
//
// To get valid OpenGL infos, OpenGL rendering context (RC) must be opened
// before calling glInfo::getInfo(). Otherwise it returns false.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2005-10-04
// UPDATED: 2013-03-06
//
// Copyright (c) 2005-2013 Song Ho Ahn
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include "glInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include <gl/freeglut_std.h>
#pragma comment (lib, "freeglut.lib")


// WGL specific extensions for v3.0+ //////////////////////////////////////////
#ifdef _WIN32
#include <windows.h>
#ifndef WGLGETEXTENSIONSSTRINGARB_DEF
#define WGLGETEXTENSIONSSTRINGARB_DEF
typedef const char* (WINAPI * PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
PFNWGLGETEXTENSIONSSTRINGARBPROC    pwglGetExtensionsStringARB = 0;
#define wglGetExtensionsStringARB  pwglGetExtensionsStringARB
#endif
#endif

// version 2.0 or greater
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C



///////////////////////////////////////////////////////////////////////////////
// extract openGL info
// This function must be called after GL rendering context opened.
///////////////////////////////////////////////////////////////////////////////
void GL_INFO::getInfo(unsigned int param)
{
    CString str;
    // get vendor string
    str = (const char *)glGetString(GL_VENDOR);
    this->vendor = str;             // check NULL return value

    // get renderer string
    str = (const char*)glGetString(GL_RENDERER);
    this->renderer = str;           // check NULL return value

    // get version string
    str = (const char*)glGetString(GL_VERSION);
    this->version = str;            // check NULL return value

    // get all extensions as a string
    str = (const char*)glGetString(GL_EXTENSIONS);

    // split extensions
    if(str.GetLength() > 0)
    {
        TCHAR* str2 = new TCHAR[str.GetLength() + 1];
#ifdef UNDER_VS2008
        _tcscpy(str2, str);
#else
		_tcscpy_s(str2, str.GetLength() + 1,str);
#endif
        TCHAR* tok = _tcstok(str2, _T(" "));
        while(tok)
        {
            tok = _tcstok(0, _T(" "));               // next token
        }
        delete [] str2;
    }

    // get GLSL version string (v2.0+)
    str = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    if(str.GetLength() > 0)
        this->glslVersion = str;
    else
    {
        // "GL_SHADING_LANGUAGE_VERSION" token is added later (v2.0) after the
        // first GLSL included in OpenGL (v1.5). If "GL_SHADING_LANGUAGE_VERSION"
        // is invalid token but "GL_ARB_shading_language_100" is supported, then
        // the GLSL version should be 1.0.rev.51
        if(isExtensionSupported("GL_ARB_shading_language_100"))
            glslVersion = _T("1.0.51"); // the first GLSL version
        else
            glslVersion = _T("");
    }

    // get WGL specific extensions for v3.0+
#ifdef _WIN32 //===========================================
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
    if(wglGetExtensionsStringARB && param)
    {
        str = (const char*)wglGetExtensionsStringARB((HDC)param);
        if(str.GetLength() > 0)
        {
            TCHAR* str2 = new TCHAR[str.GetLength() + 1];
#ifdef UNDER_VS2008
            _tcscpy(str2,str);
#else
			_tcscpy_s(str2,str.GetLength() + 1,str);
#endif
            TCHAR* tok = _tcstok(str2, _T(" "));
            while(tok)
            {
                tok = _tcstok(0, _T(" "));               // next token
            }
            delete [] str2;
        }
    }
#endif //==================================================

    // sort extension by alphabetical order


    // get number of color bits
    glGetIntegerv(GL_RED_BITS, &this->redBits);
    glGetIntegerv(GL_GREEN_BITS, &this->greenBits);
    glGetIntegerv(GL_BLUE_BITS, &this->blueBits);
    glGetIntegerv(GL_ALPHA_BITS, &this->alphaBits);

    // get depth bits
    glGetIntegerv(GL_DEPTH_BITS, &this->depthBits);

    // get stecil bits
    glGetIntegerv(GL_STENCIL_BITS, &this->stencilBits);

    // get max number of lights allowed
    glGetIntegerv(GL_MAX_LIGHTS, &this->maxLights);

    // get max texture resolution
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->maxTextureSize);

    // get max number of clipping planes
    glGetIntegerv(GL_MAX_CLIP_PLANES, &this->maxClipPlanes);

    // get max modelview and projection matrix stacks
    glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &this->maxModelViewStacks);
    glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &this->maxProjectionStacks);
    glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &this->maxAttribStacks);

    // get max texture stacks
    glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &this->maxTextureStacks);
}



///////////////////////////////////////////////////////////////////////////////
// check if the video card support a certain extension
///////////////////////////////////////////////////////////////////////////////
bool GL_INFO::isExtensionSupported(const std::string& ext)
{
    return true;
}



///////////////////////////////////////////////////////////////////////////////
// print OpenGL info to screen and save to a file
///////////////////////////////////////////////////////////////////////////////
void GL_INFO::printSelf()
{
	CString strMsg;
    strMsg.Format(_T("OpenGL Driver Info"));
    TRACE(strMsg);
	strMsg.Format(_T("=================="));
	TRACE(strMsg);
    strMsg.Format(_T("Vendor: %s") , this->vendor);
    TRACE(strMsg);
	strMsg.Format(_T("Version: %s" ), this->version);
    TRACE(strMsg);
	strMsg.Format(_T("GLSL Version: %s") , this->glslVersion);
    TRACE(strMsg);
	strMsg.Format(_T("Renderer: %s") , this->renderer);
	TRACE(strMsg);
	strMsg.Format(_T("Color Bits(R,G,B,A): (%d %d %d %d)") , this->redBits , this->greenBits, this->blueBits,  this->alphaBits );
    TRACE(strMsg);
	strMsg.Format(_T("Depth Bits: %d") , this->depthBits);
    TRACE(strMsg);
	strMsg.Format(_T("Stencil Bits: %d") , this->stencilBits);
	TRACE(strMsg);
    strMsg.Format(_T("Max Texture Size: %d * %d") , this->maxTextureSize , this->maxTextureSize);
	TRACE(strMsg);
    strMsg.Format(_T("Max Lights: %d") , this->maxLights);
	TRACE(strMsg);
    strMsg.Format(_T("Max Clip Planes: %d") , this->maxClipPlanes);
	TRACE(strMsg);
    strMsg.Format(_T("Max Modelview Matrix Stacks: %d" ), this->maxModelViewStacks);
	TRACE(strMsg);
    strMsg.Format(_T("Max Projection Matrix Stacks: %d") , this->maxProjectionStacks);
	TRACE(strMsg);
    strMsg.Format(_T("Max Attribute Stacks: %d") , this->maxAttribStacks);
	TRACE(strMsg);
    strMsg.Format(_T("Max Texture Stacks: %d") , this->maxTextureStacks);
	TRACE(strMsg);
    strMsg.Format(_T("\r\n"));
	TRACE(strMsg);
    strMsg.Format(_T("=============================="));
	TRACE(strMsg);

    strMsg.Format(_T("======================================================================"));
	TRACE(strMsg);


}
