#pragma once
#include "afxwin.h"
#include "OpenGLViewEx.h"

class CReferenceData : public CWnd
{
	BOOL InitCanvas(); 

public:
	CReferenceData(CWnd *pView, CWnd *pViewPiece, CWnd *pViewMask, CWnd *pParent, int nIndex);
	~CReferenceData();

public:
	COpenGLViewEx *m_pOpenGLView;

};

