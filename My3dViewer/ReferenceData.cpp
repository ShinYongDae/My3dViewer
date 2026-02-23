#include "stdafx.h"
#include "ReferenceData.h"


CReferenceData::CReferenceData(CWnd *pView, CWnd *pViewPiece, CWnd *pViewMask, CWnd *pParent, int nIndex)
{
	m_pOpenGLView = NULL;

}


CReferenceData::~CReferenceData()
{
	m_pOpenGLView->MakeCurrent();

	if (m_pOpenGLView)
	{
		delete m_pOpenGLView;
		m_pOpenGLView = NULL;
	}
}

BOOL CReferenceData::InitCanvas()
{
	if (!m_pOpenGLView)
	{
		m_pOpenGLView = new COpenGLViewEx();
	}

	return TRUE;
}