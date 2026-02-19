// OpenGLFont.cpp: implementation of the COpenGLFontCam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGLFontCam.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGLFontCam::COpenGLFontCam()
{
	m_nlist_base = 0;
	m_tess = NULL;

}

COpenGLFontCam::~COpenGLFontCam()
{
//	DestroyFont();
}

void COpenGLFontCam::DestroyFont()
{
	m_vecFontSize.clear();
	if(m_nlist_base != 0)
	glDeleteLists(m_nlist_base,129);
	if(m_tess)
		gluDeleteTess(m_tess); 
	if(m_nMode == FONT_TYPE::BITMAP)
	{
		glDeleteTextures(129,m_textures);
	}
}

BOOL COpenGLFontCam::Initialize(FONT_TYPE::MODE nMode, const char * chFontName, unsigned int nSize)
{
	////FT_Face face;
	////FT_Library library;
	//m_nSize = nSize;
	//m_strFontFilePath.Format(_T("%s"),chFontName);
	//InitFont(face,library,chFontName);
	//m_nMode = nMode;
	//unsigned long i;
	//if(m_nMode == FONT_TYPE::BITMAP)
	//{
	//	SHPFONTSIZE stFontSize;
	//	int nFontWidth,nFontHeight,nFontLowerPartHeight;
	//	glGenTextures( 129, m_textures );
	//	for(i=0;i<128;i++)
	//	{
	//		MakeBitmapFontList(face,i,nFontWidth,nFontHeight,nFontLowerPartHeight);
	//		stFontSize.height = nFontHeight;
	//		stFontSize.width  = nFontWidth;
	//		stFontSize.LowerPartHeight = nFontLowerPartHeight;
	//		m_vecFontSize.push_back(stFontSize);
	//	}
	//	i = 176;

	//	MakeBitmapFontList(face,i,nFontWidth,nFontHeight,nFontLowerPartHeight);
	//	stFontSize.height = nFontHeight;
	//	stFontSize.width  = nFontWidth;
	//	stFontSize.LowerPartHeight = nFontLowerPartHeight;
	//	m_vecFontSize.push_back(stFontSize);
	//	FT_Done_Face(face);
	//	FT_Done_FreeType(library);
	//	return TRUE;
	//}
	//else
	//{
	//	SHPFONTSIZE stFontSize;
	//	int nFontWidth,nFontHeight,nFontLowerPartHeight,nBearingX,nRightGapX;
	//	InitTessellation();
	//	glEnable(GL_STENCIL_TEST);
	//	for(i=0;i<128;i++)
	//	{
 //			MakeVertexFontList(face,i,nFontWidth,nFontHeight,nFontLowerPartHeight,nBearingX,nRightGapX);
	//		stFontSize.height = nFontHeight;
	//		stFontSize.width  = nFontWidth;
	//		stFontSize.LowerPartHeight = nFontLowerPartHeight;
	//		stFontSize.BearingX = nBearingX;
	//		stFontSize.RightGapX = nRightGapX;
	//		m_vecFontSize.push_back(stFontSize);
	//	}
	//	glDisable(GL_STENCIL_TEST);
	//	FT_Done_Face(face);
	//	FT_Done_FreeType(library);
	//	return TRUE;		
	//}
	return TRUE;
}

void COpenGLFontCam::InitTessellation()
{
	m_tess = gluNewTess();
	gluTessCallback(m_tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
	gluTessCallback(m_tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
	gluTessCallback(m_tess, GLU_TESS_VERTEX, (void (__stdcall*)())tessVertexCB);
}
/*
BOOL COpenGLFontCam::InitFont(FT_Face &face,FT_Library &library,const char* chFontName)
{
	if (FT_Init_FreeType( &library )) 
	{
        AfxMessageBox(_T("Error!! FT_Init_FreeType Fail"));
		return FALSE;
	}
	if (FT_New_Face( library, chFontName, 0, &face )) 
	{
        AfxMessageBox(_T("Error!! FT_New_Face Fail"));
		return FALSE;
	}
	FT_CharMap found = 0;
	FT_CharMap charmap;
	unsigned short encoding_id,platform_id;
	int n;
	for( n=0; n<face->num_charmaps; n++)
	{
		charmap = face->charmaps[n];
		encoding_id = charmap->encoding_id;
		platform_id = charmap->platform_id;
		if(encoding_id ==0 && platform_id == 1)
		{
			found = charmap;
			break;
		}
	}
	if(found != 0)
		FT_Set_Charmap( face, found );
	FT_Set_Char_Size( face, m_nSize *64, m_nSize *64, 96, 96);
	m_nlist_base=glGenLists(129);
	return TRUE;
}


void COpenGLFontCam::MakeBitmapFontList(FT_Face face, unsigned long ch,int &nFontWidth,int &nFontHeight,int &nFontLowerPartHeight)
{

	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ),FT_LOAD_DEFAULT))
		AfxMessageBox(_T("Error!! FT_Load_Glyph Fail"));

//	FT_Outline_Embolden( &face->glyph->outline, (face->size->metrics.x_ppem*5/100)*64);

	int i, j;
    FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
		AfxMessageBox(_T("Error!! FT_Get_Glyph Fail"));


	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	nFontWidth = face->glyph->advance.x;
	nFontHeight = face->glyph->metrics.horiBearingY;
	nFontLowerPartHeight = face->glyph->metrics.horiBearingY-face->glyph->metrics.height;


	int width = next_p2( bitmap.width );
	int height = next_p2( bitmap.rows );

	GLubyte* expanded_data = new GLubyte[ 2 * width * height];


	for(j=0; j <height;j++) {
		for(i=0; i < width; i++){
			expanded_data[2*(i+j*width)]= expanded_data[2*(i+j*width)+1] = 
				(i>=bitmap.width || j>=bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
		}
	}
	if(ch == 176)
	{
		ch = 128;
	}


    glBindTexture( GL_TEXTURE_2D, m_textures[ch]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		  0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );


    delete [] expanded_data;


	glNewList(m_nlist_base+ch,GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D,m_textures[ch]);

	glPushMatrix();


	glTranslatef(bitmap_glyph->left,0,0);


	glTranslatef(0,bitmap_glyph->top-bitmap.rows,0);

	double	x=(double)bitmap.width / (double)width,
			y=(double)bitmap.rows / (double)height;

	
	glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
	glTexCoord2d(0,y); glVertex2f(0,0);
	glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
	glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(face->glyph->advance.x >> 6 ,0,0);
	glEndList();
	
	FT_Done_Glyph(glyph);
	
}

void COpenGLFontCam::MakeVertexFontList( FT_Face face, unsigned long ch,int &nFontWidth,int &nFontHeight,int &nFontLowerPartHeight,int &nBearingX,int &nRightGapX)
{
	FT_UInt charIndex = FT_Get_Char_Index( face,ch );
	if(FT_Load_Glyph( face, charIndex,FT_LOAD_NO_BITMAP))
	{
		AfxMessageBox(_T("Error!! FT_Load_Glyph Fail"));
	}

	int a = face->glyph->outline.flags;
    FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
	{
		AfxMessageBox(_T("Error!! FT_Get_Glyph Fail"));
	}

	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	nFontWidth = face->glyph->metrics.horiAdvance;
	nBearingX = face->glyph->metrics.horiBearingX;
	nFontHeight = face->glyph->metrics.horiBearingY;
	nFontLowerPartHeight = face->glyph->metrics.horiBearingY-face->glyph->metrics.height;
	nRightGapX = face->glyph->metrics.horiAdvance-face->glyph->metrics.horiBearingX-face->glyph->metrics.width;

	int c,p,i,j,bufp;

	int cs,ce;

	FT_Vector pt;
	DPOINT P0,P1,P2,BeforePt = tagdPOINT(0,0),MiddlePt;
	glNewList(m_nlist_base+ch,GL_COMPILE);
	FPOINT vectorpt;
	FONTGLIPH stFontGliph;
	DPOINT stVertex;
	vector<FONTGLIPH> vecFontGliph;
	vector<DPOINT> vecCurve;
	double Test[2];
	char* tags = face->glyph->outline.tags;
	int nextIndex,next1,next2;
	int nNumOfConic;
	for (c=0;c<face->glyph->outline.n_contours;c++) 
	{

		cs=(c==0 ? 0:face->glyph->outline.contours[c-1]+1);
		ce=face->glyph->outline.contours[c];
		pt=face->glyph->outline.points[ce];
		P1.x=(double)pt.x / 64.0;
		P1.y=(double)pt.y / 64.0;
		BeforePt = P1;
		for (p=cs;p<=ce; p++) 
		{

			pt=face->glyph->outline.points[p];

			P0.x=(double)pt.x / 64.0;
			P0.y=(double)pt.y / 64.0;
	
			if(p == cs)
			{
				if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Conic)
				{
					pt=face->glyph->outline.points[ce];
					P0.x=(double)pt.x / 64.0;
					P0.y=(double)pt.y / 64.0;

					vectorpt.x = P0.x;
					vectorpt.y = P0.y;
					stFontGliph.vecFPOINT.push_back(vectorpt); 
					BeforePt = P0;
					p = cs;
				}
				else
				{
					vectorpt.x = P0.x;
					vectorpt.y = P0.y;
					stFontGliph.vecFPOINT.push_back(vectorpt); 
					BeforePt = P0;
				}
			}

		
			if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_On)
			{
				if (p != cs)
				{
					vectorpt.x = P0.x;
					vectorpt.y = P0.y;
					stFontGliph.vecFPOINT.push_back(vectorpt);
					BeforePt = P0;
				}
			}
			else if(FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Conic)
			{
				nNumOfConic = 0;
				bufp = p;
				while(FT_CURVE_TAG (tags[bufp]) == FT_Curve_Tag_Conic)
				{
					if(bufp == ce)
						bufp= cs;
					else
						bufp ++;
					nNumOfConic ++;
					if(bufp == p)
						break;
				}

				if(nNumOfConic == 1)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 2)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
					
				}
				else if(nNumOfConic == 3)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 4)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 5)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 6)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
			}
			else if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Cubic)
			{
				next1 = p + 1;
				next2 = (p == (ce - 1)) ? cs : (p + 2);
			
				if (p >= ce
					 || FT_CURVE_TAG (tags[next1]) != FT_Curve_Tag_Cubic
					 || FT_CURVE_TAG (tags[next2]) != FT_Curve_Tag_On)
				break;
				pt=face->glyph->outline.points[next1];
				P1.x=(double)pt.x / 64.0;
				P1.y=(double)pt.y / 64.0;
				pt=face->glyph->outline.points[next2];
				P2.x=(double)pt.x / 64.0;
				P2.y=(double)pt.y / 64.0;

//                destShape.cubicTo (x, y, x2, y2, x3, y3);
				p += 2;
				

			}
					
		}
		stFontGliph.bDrak = TRUE;
		vecFontGliph.push_back(stFontGliph);
		stFontGliph.vecFPOINT.clear();
	}
	if(vecFontGliph.size()==1)
	{
		gluTessBeginPolygon(m_tess, 0);
		for(i=0;i<vecFontGliph.size();i++)
		{
			for(j=0;j<vecFontGliph[i].vecFPOINT.size();j++)
			{
				Test[0]= vecFontGliph[i].vecFPOINT[j].x;
				Test[1]= vecFontGliph[i].vecFPOINT[j].y;
				gluTessVertex(m_tess, Test, &vecFontGliph[i].vecFPOINT[j]);
			}
		}	
		gluTessEndPolygon(m_tess);
	}
	else if(vecFontGliph.size()>1)
	{
		for(i=0;i<vecFontGliph.size();i++)
		{
			for(j=0;j<vecFontGliph.size();j++)
			{
				if(i==j)
					continue;
				else
				{
					if(CheckPolygonInPolygon(vecFontGliph[i].vecFPOINT,vecFontGliph[j].vecFPOINT))
					{
						vecFontGliph[i].bDrak = TRUE;
						vecFontGliph[j].bDrak = FALSE;
					}
				}
			}
		}
		for(i=0;i<vecFontGliph.size();i++)
		{
			if(!vecFontGliph[i].bDrak)
			{
				glStencilFunc(GL_NEVER,1,1);
				glStencilOp(GL_INCR,GL_INCR,GL_INCR);			
				gluTessBeginPolygon(m_tess, 0);
				for(j=0;j<vecFontGliph[i].vecFPOINT.size();j++)
				{
					Test[0]= vecFontGliph[i].vecFPOINT[j].x;
					Test[1]= vecFontGliph[i].vecFPOINT[j].y;
					gluTessVertex(m_tess, Test, &vecFontGliph[i].vecFPOINT[j]);
				}
				gluTessEndPolygon(m_tess);
			}
		}
		for(i=0;i<vecFontGliph.size();i++)
		{
			
			if(vecFontGliph[i].bDrak)
			{
				glStencilFunc(GL_EQUAL,0,15);
				glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);		
				gluTessBeginPolygon(m_tess, 0);
				for(j=0;j<vecFontGliph[i].vecFPOINT.size();j++)
				{
					Test[0]= vecFontGliph[i].vecFPOINT[j].x;
					Test[1]= vecFontGliph[i].vecFPOINT[j].y;
					gluTessVertex(m_tess, Test, &vecFontGliph[i].vecFPOINT[j]);
				}
				gluTessEndPolygon(m_tess);
				glClear(GL_STENCIL_BUFFER_BIT);
			}			
		}
	}	
	
	glTranslatef(face->glyph->advance.x >> 6 ,0,0);
	glEndList();
	for(i=0;i<vecFontGliph.size();i++)
		vecFontGliph[i].vecFPOINT.clear();
	vecFontGliph.clear();
	FT_Done_Glyph(glyph);
}
*/
int COpenGLFontCam::next_p2(int a)
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}
void CALLBACK COpenGLFontCam::tessBeginCB(GLenum which)
{
	glBegin(which);//GL_TRIANGLE_STRIP or GL_TRIANGLES 
}

void CALLBACK COpenGLFontCam::tessEndCB()
{
	glEnd();
}

void CALLBACK COpenGLFontCam::tessVertexCB(const GLvoid *data)
{
    const FPOINT *ptr = (const FPOINT*)data;
    glVertex2f(ptr->x,ptr->y);
}
void COpenGLFontCam::ConicToN(vector<DPOINT> vecControl,vector<FPOINT> &vecVertex, int nNum)
{
	double buf,buf1,buf2;
	double factory0,factory1,factory2;
	double incr = (double)1/nNum;
	FPOINT stVertex;
	int nSize = (int)vecControl.size();
	int i,j,k;
	for(buf =0; buf< 1; buf += incr)
	{
		for(i=0;i<vecControl.size();i++)
		{
			buf1 = 1;
			buf2 = 1;
			factory0 = 1;
			factory1 = 1;
			factory2 = 1;
			for(k=1;k<nSize;k++)
			{
				factory0 *=k;
			}
			for(k=1;k<nSize-i;k++)
			{
				factory1 *=k;
			}
			for(k=1;k<=i;k++)
			{
				factory2 *=k;
			}
			for(j=i;j<nSize-1;j++)
			{
				buf1 *= (1-buf);
			}
			for(j=i;j>0;j--)
			{
				buf2 *= buf;
			}
			if(i==0)
			{
				stVertex.x =buf1*buf2*vecControl[i].x*factory0/(factory1*factory2);
				stVertex.y =buf1*buf2*vecControl[i].y*factory0/(factory1*factory2);
			}
			else
			{
				stVertex.x +=buf1*buf2*vecControl[i].x*factory0/(factory1*factory2);
				stVertex.y +=buf1*buf2*vecControl[i].y*factory0/(factory1*factory2);
			}
		}
		vecVertex.push_back(stVertex);

	}

}
BOOL COpenGLFontCam::CheckPolygonInPolygon(vector<FPOINT> vecPolygon1, vector<FPOINT> vecPolygon2)
{
	//BOOL bBuf;
	//int i;
	//if(vecPolygon1.size()<3 || vecPolygon2.size()<3)
	//	return FALSE;
	//for(i=0;i<vecPolygon2.size();i++)
	//{
	//	bBuf=CheckPointInPolygonFont(vecPolygon1,vecPolygon2[i].x,vecPolygon2[i].y);
	//	if(!bBuf)
	//		return FALSE;
	//}
	return TRUE;
}
void COpenGLFontCam::DrawBMPFont(const char *fmt)
{
	
	int size = strlen(fmt);
    glEnable(GL_TEXTURE_2D); 
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
	glListBase(m_nlist_base);
	glCallLists(size,GL_UNSIGNED_BYTE,fmt);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void COpenGLFontCam::GetFontSize(const unsigned char *chText,double &fWidth, double &fHeight,double &fLowerPartHeight,double fscale)
{
	int nWidth=0,nHeight=0,nbuf,nbuf1,nLowerPartHeight=10000;
	while(*chText)
	{
		nbuf = m_vecFontSize[*chText].height;
		nWidth += m_vecFontSize[*chText].width;
		nbuf1 = m_vecFontSize[*chText].LowerPartHeight;
		chText++;
		if(nbuf>nHeight)
			nHeight = nbuf;
		if(nbuf1<nLowerPartHeight)
			nLowerPartHeight = nbuf1;
	}
	fWidth = (double)nWidth*fscale;
	fHeight = (double)nHeight*fscale;
	fLowerPartHeight = (double)nLowerPartHeight*fscale;
}
void COpenGLFontCam::DrawFreeTypeFontChar(unsigned short nNum)
{
	if(nNum == 0)
		return;
	glEnable(GL_STENCIL_TEST);
	glCallList(m_nlist_base+nNum);
	glDisable(GL_STENCIL_TEST);

}

void COpenGLFontCam::DrawFreeTypeFont(CString strText)
{
#ifdef _UNICODE
	int len;
	char *chText = StringToChar(strText,len);

	glListBase(m_nlist_base);
	glEnable(GL_STENCIL_TEST);
	glCallLists(len,GL_UNSIGNED_BYTE,chText);
	glDisable(GL_STENCIL_TEST);
	delete chText;
	chText = NULL;
#else
	int size =strText.GetLength();
	char *fmt = strText.GetBuffer(0);
	glListBase(m_nlist_base);
	glEnable(GL_STENCIL_TEST);
	glCallLists(size,GL_UNSIGNED_BYTE,fmt);
	glDisable(GL_STENCIL_TEST);
#endif
}
/*
void COpenGLFontCam::DrawUniTypeFontChar(const TCHAR *fname, unsigned int h, unsigned short nNum,double fScale,double &fFontWidth)
{
	FT_Glyph glyph;
	int c,p,i,j,bufp;

	int cs,ce;

	FT_Vector pt;
	DPOINT P0,P1,P2,BeforePt = tagdPOINT(0,0),MiddlePt;
	//So now we can create the display list
	FPOINT vectorpt;
	FONTGLIPH stFontGliph;
	DPOINT stVertex;
	vector<FONTGLIPH> vecFontGliph;
	vector<DPOINT> vecCurve;
	double Test[2];
	char* tags;
	int nextIndex,next1,next2;
	int nNumOfConic,nWidth;
	glEnable(GL_STENCIL_TEST);
	FT_Library library;
	if (FT_Init_FreeType( &library )) 
		AfxMessageBox(_T("Error!! FT_Init_FreeType Fail"));
	FT_Face face;
#ifdef _UNICODE
	char *strMultibyte = TCHARToChar(fname);
	if (FT_New_Face( library, strMultibyte, 0, &face )) 
	{
		delete strMultibyte;
		strMultibyte = NULL;
		AfxMessageBox(_T("Error!! FT_New_Face Fail"));
		return;
	}
	delete strMultibyte;
	strMultibyte = NULL;
#else
	if (FT_New_Face( library, fname, 0, &face )) 
	{
		AfxMessageBox(fname);
        AfxMessageBox(_T("Error!! FT_New_Face Fail"));
		return;
	}
#endif
	FT_Set_Char_Size( face, h *64, h *64, 96, 96);	
	
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, nNum ),FT_LOAD_NO_BITMAP))
	{
		AfxMessageBox(_T("Error!! FT_Load_Glyph Fail"));
	}
	
	if(FT_Get_Glyph( face->glyph, &glyph ))
	{
		AfxMessageBox(_T("Error!! FT_Get_Glyph Fail"));
	}
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//This reference will make accessing the bitmap easier
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	nWidth = face->glyph->metrics.horiAdvance;
	
	fFontWidth = (double)nWidth*fScale;
	tags = face->glyph->outline.tags;
	for (c=0;c<face->glyph->outline.n_contours;c++) 
	{
		cs=(c==0 ? 0:face->glyph->outline.contours[c-1]+1);
		ce=face->glyph->outline.contours[c];
		pt=face->glyph->outline.points[ce];
		P1.x=(double)pt.x / 64.0;
		P1.y=(double)pt.y / 64.0;
		BeforePt = P1;
		for (p=cs;p<=ce; p++) 
		{

			pt=face->glyph->outline.points[p];

			P0.x=(double)pt.x / 64.0;
			P0.y=(double)pt.y / 64.0;
	
			if(p == cs)
			{
				if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Conic)
				{
					pt=face->glyph->outline.points[ce];
					P0.x=(double)pt.x / 64.0;
					P0.y=(double)pt.y / 64.0;

					vectorpt.x = P0.x;
					vectorpt.y = P0.y;
					stFontGliph.vecFPOINT.push_back(vectorpt); 
					BeforePt = P0;
					p = cs;
				}
				else
				{
					vectorpt.x = P0.x;
					vectorpt.y = P0.y;
					stFontGliph.vecFPOINT.push_back(vectorpt); 
					BeforePt = P0;
				}
			}

		
			if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_On)
			{
				if (p != cs)
				{
					vectorpt.x = P0.x;
					vectorpt.y = P0.y;
					stFontGliph.vecFPOINT.push_back(vectorpt);
					BeforePt = P0;
				}
			}
			else if(FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Conic)
			{
				nNumOfConic = 0;
				bufp = p;
				while(FT_CURVE_TAG (tags[bufp]) == FT_Curve_Tag_Conic)
				{
					if(bufp == ce)
						bufp= cs;
					else
						bufp ++;
					nNumOfConic ++;
					if(bufp == p)
						break;
				}

				if(nNumOfConic == 1)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 2)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
					
				}
				else if(nNumOfConic == 3)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 4)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 5)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
				else if(nNumOfConic == 6)
				{
					vecCurve.push_back(BeforePt);
					vecCurve.push_back(P0);
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P0.x+P1.x)/2.0;
					MiddlePt.y = (P0.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P2);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;

					MiddlePt.x = (P2.x+P1.x)/2.0;
					MiddlePt.y = (P2.y+P1.y)/2.0;
					vecCurve.push_back(MiddlePt);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					vecCurve.push_back(MiddlePt);
					vecCurve.push_back(P1);
					++p;
					nextIndex = (p == ce) ? cs : p+1;
					pt=face->glyph->outline.points[nextIndex];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					vecCurve.push_back(P1);
					ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
					vecCurve.clear();
					BeforePt = P1;
					++p;
				}
			}
			else if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Cubic)
			{
				next1 = p + 1;
				next2 = (p == (ce - 1)) ? cs : (p + 2);
			
				if (p >= ce
					 || FT_CURVE_TAG (tags[next1]) != FT_Curve_Tag_Cubic
					 || FT_CURVE_TAG (tags[next2]) != FT_Curve_Tag_On)
				break;
				pt=face->glyph->outline.points[next1];
				P1.x=(double)pt.x / 64.0;
				P1.y=(double)pt.y / 64.0;
				pt=face->glyph->outline.points[next2];
				P2.x=(double)pt.x / 64.0;
				P2.y=(double)pt.y / 64.0;

//                destShape.cubicTo (x, y, x2, y2, x3, y3);
				p += 2;
				

			}
					
		}
		stFontGliph.bDrak = TRUE;
		vecFontGliph.push_back(stFontGliph);
		stFontGliph.vecFPOINT.clear();
	}
	if(vecFontGliph.size()==1)
	{
		gluTessBeginPolygon(m_tess, 0);
		for(i=0;i<vecFontGliph.size();i++)
		{
			for(j=0;j<vecFontGliph[i].vecFPOINT.size();j++)
			{
				Test[0]= vecFontGliph[i].vecFPOINT[j].x;
				Test[1]= vecFontGliph[i].vecFPOINT[j].y;
				gluTessVertex(m_tess, Test, &vecFontGliph[i].vecFPOINT[j]);
			}
		}	
		gluTessEndPolygon(m_tess);
	}
	else if(vecFontGliph.size()>1)
	{
		for(i=0;i<vecFontGliph.size();i++)
		{
			for(j=0;j<vecFontGliph.size();j++)
			{
				if(i==j)
					continue;
				else
				{
					if(CheckPolygonInPolygon(vecFontGliph[i].vecFPOINT,vecFontGliph[j].vecFPOINT))
					{
						vecFontGliph[i].bDrak = TRUE;
						vecFontGliph[j].bDrak = FALSE;
					}
				}
			}
		}
		for(i=0;i<vecFontGliph.size();i++)
		{
			if(!vecFontGliph[i].bDrak)
			{
				glStencilFunc(GL_NEVER,1,1);
				glStencilOp(GL_INCR,GL_INCR,GL_INCR);			
				gluTessBeginPolygon(m_tess, 0);
				for(j=0;j<vecFontGliph[i].vecFPOINT.size();j++)
				{
					Test[0]= vecFontGliph[i].vecFPOINT[j].x;
					Test[1]= vecFontGliph[i].vecFPOINT[j].y;
					gluTessVertex(m_tess, Test, &vecFontGliph[i].vecFPOINT[j]);
				}
				gluTessEndPolygon(m_tess);
			}
		}
		for(i=0;i<vecFontGliph.size();i++)
		{
			
			if(vecFontGliph[i].bDrak)
			{
				glStencilFunc(GL_EQUAL,0,15);
				glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);		
				gluTessBeginPolygon(m_tess, 0);
				for(j=0;j<vecFontGliph[i].vecFPOINT.size();j++)
				{
					Test[0]= vecFontGliph[i].vecFPOINT[j].x;
					Test[1]= vecFontGliph[i].vecFPOINT[j].y;
					gluTessVertex(m_tess, Test, &vecFontGliph[i].vecFPOINT[j]);
				}
				gluTessEndPolygon(m_tess);
				glClear(GL_STENCIL_BUFFER_BIT);
			}			
		}
	}
	for(i=0;i<vecFontGliph.size();i++)
	{
		vecFontGliph[i].vecFPOINT.clear();
	}
	vecFontGliph.clear();
	glDisable(GL_STENCIL_TEST);
	FT_Done_Glyph(glyph);
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}
void COpenGLFontCam::DrawUniTypeFont(const TCHAR *fname, unsigned int h, CString str)
{
	FT_Library library;
	if (FT_Init_FreeType( &library ))
	{
		AfxMessageBox(_T("Error!! FT_Init_FreeType Fail"));
	}
	FT_Face face;
#ifdef _UNICODE
	char *strMultibyte = TCHARToChar(fname);

	if (FT_New_Face( library, strMultibyte, 0, &face )) 
	{
		delete strMultibyte;
		strMultibyte = NULL;
        AfxMessageBox(_T("Error!! FT_New_Face Fail"));
		return;
	}
	delete strMultibyte;
	strMultibyte = NULL;
#else
	if (FT_New_Face( library, fname, 0, &face )) 
	{
		AfxMessageBox(fname);
        AfxMessageBox(_T("Error!! FT_New_Face Fail"));
		return;
	}
#endif
	FT_Set_Char_Size( face, h *64, h *64, 96, 96);
	int nLen;
#ifdef _UNICODE
	wchar_t* szCh;
	szCh = str.GetBuffer(0);
	nLen = str.GetLength();
#else
	char *ch;
	ch = (char *)str.GetBuffer(0);
	wchar_t *szCh = NULL;
	szCh = CharToWCHAR(ch,nLen);
#endif
	FT_Glyph glyph;
	int c,p,i,j,bufp,k;

	int cs,ce;

	FT_Vector pt;
	DPOINT P0,P1,P2,BeforePt = tagdPOINT(0,0),MiddlePt;
	//So now we can create the display list
	FPOINT vectorpt;
	FONTGLIPH stFontGliph;
	DPOINT stVertex;
	vector<FONTGLIPH> vecFontGliph;
	vector<DPOINT> vecCurve;
	double Test[2];
	char* tags;
	int nextIndex,next1,next2;
	int nNumOfConic;
	int nWidth;
	double fFontWidth;
	glEnable(GL_STENCIL_TEST);
	glPushMatrix();
	for(i=0;i<nLen;i++)
	{
		if(FT_Load_Glyph( face, FT_Get_Char_Index( face, szCh[i] ),FT_LOAD_NO_BITMAP))
		{
			AfxMessageBox(_T("Error!! FT_Load_Glyph Fail"));
		}
		
		if(FT_Get_Glyph( face->glyph, &glyph ))
		{
			AfxMessageBox(_T("Error!! FT_Get_Glyph Fail"));
		}
		if(szCh[i]=='\0')
			continue;
		nWidth = face->glyph->metrics.horiAdvance;
		fFontWidth = (double)nWidth*FONTSCALE;
		tags = face->glyph->outline.tags;
		for (c=0;c<face->glyph->outline.n_contours;c++) 
		{
			cs=(c==0 ? 0:face->glyph->outline.contours[c-1]+1);
			ce=face->glyph->outline.contours[c];
			pt=face->glyph->outline.points[ce];
			P1.x=(double)pt.x / 64.0;
			P1.y=(double)pt.y / 64.0;
			BeforePt = P1;
			for (p=cs;p<=ce;p++) 
			{

				pt=face->glyph->outline.points[p];

				P0.x=(double)pt.x / 64.0;
				P0.y=(double)pt.y / 64.0;

				if(p == cs)
				{
					if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Conic)
					{
						pt=face->glyph->outline.points[ce];
						P0.x=(double)pt.x / 64.0;
						P0.y=(double)pt.y / 64.0;

						vectorpt.x = P0.x;
						vectorpt.y = P0.y;
						stFontGliph.vecFPOINT.push_back(vectorpt); 
						BeforePt = P0;
						p = cs;
					}
					else
					{
						vectorpt.x = P0.x;
						vectorpt.y = P0.y;
						stFontGliph.vecFPOINT.push_back(vectorpt); 
						BeforePt = P0;
					}
				}


				if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_On)
				{
					if (p != cs)
				{
						vectorpt.x = P0.x;
						vectorpt.y = P0.y;
						stFontGliph.vecFPOINT.push_back(vectorpt);
						BeforePt = P0;
				} 
				} 
				else if(FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Conic)
				{
					nNumOfConic = 0;
					bufp = p;
					while(FT_CURVE_TAG (tags[bufp]) == FT_Curve_Tag_Conic)
					{
						if(bufp == ce)
							bufp= cs;
						else 
							bufp ++;
						nNumOfConic ++;
						if(bufp == p)
							break;
					}

					if(nNumOfConic == 1)
					{
						vecCurve.push_back(BeforePt);
						vecCurve.push_back(P0);
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;
						vecCurve.push_back(P1);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						BeforePt = P1;
						++p;
					}
					else if(nNumOfConic == 2)
					{
						vecCurve.push_back(BeforePt);
						vecCurve.push_back(P0);
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P0.x+P1.x)/2.0;
						MiddlePt.y = (P0.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;
						vecCurve.push_back(P1);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						BeforePt = P1;
						++p;
						
					}
					else if(nNumOfConic == 3)
				{
						vecCurve.push_back(BeforePt);
						vecCurve.push_back(P0);
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P0.x+P1.x)/2.0;
						MiddlePt.y = (P0.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P2.x=(double)pt.x / 64.0;
						P2.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P2);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;
						vecCurve.push_back(P1);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						BeforePt = P1;
						++p;
				}
					else if(nNumOfConic == 4)
					{
						vecCurve.push_back(BeforePt);
						vecCurve.push_back(P0);
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P0.x+P1.x)/2.0;
						MiddlePt.y = (P0.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P2.x=(double)pt.x / 64.0;
						P2.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P2);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;
						vecCurve.push_back(P1);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						BeforePt = P1;
						++p;
					}
					else if(nNumOfConic == 5)
					{
						vecCurve.push_back(BeforePt);
						vecCurve.push_back(P0);
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P0.x+P1.x)/2.0;
						MiddlePt.y = (P0.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P2.x=(double)pt.x / 64.0;
						P2.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P2);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P2.x=(double)pt.x / 64.0;
						P2.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P2);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;
						vecCurve.push_back(P1);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						BeforePt = P1;
						++p;
					}
					else if(nNumOfConic == 6)
					{
						vecCurve.push_back(BeforePt);
						vecCurve.push_back(P0);
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P0.x+P1.x)/2.0;
						MiddlePt.y = (P0.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P2.x=(double)pt.x / 64.0;
						P2.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P2);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];

						P2.x=(double)pt.x / 64.0;
						P2.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P2);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];

						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;

						MiddlePt.x = (P2.x+P1.x)/2.0;
						MiddlePt.y = (P2.y+P1.y)/2.0;
						vecCurve.push_back(MiddlePt);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						vecCurve.push_back(MiddlePt);
						vecCurve.push_back(P1);
						++p;
						nextIndex = (p == ce) ? cs : p+1;
						pt=face->glyph->outline.points[nextIndex];
						P1.x=(double)pt.x / 64.0;
						P1.y=(double)pt.y / 64.0;
						vecCurve.push_back(P1);
						ConicToN(vecCurve,stFontGliph.vecFPOINT,10);
						vecCurve.clear();
						BeforePt = P1;
						++p;
					}
				}
				else if (FT_CURVE_TAG (tags[p]) == FT_Curve_Tag_Cubic)
				{
					next1 = p + 1;
					next2 = (p == (ce - 1)) ? cs : (p + 2);

					if (p >= ce
						 || FT_CURVE_TAG (tags[next1]) != FT_Curve_Tag_Cubic
						 || FT_CURVE_TAG (tags[next2]) != FT_Curve_Tag_On)
					break;
					pt=face->glyph->outline.points[next1];
					P1.x=(double)pt.x / 64.0;
					P1.y=(double)pt.y / 64.0;
					pt=face->glyph->outline.points[next2];
					P2.x=(double)pt.x / 64.0;
					P2.y=(double)pt.y / 64.0;

	//                destShape.cubicTo (x, y, x2, y2, x3, y3);
					p += 2;


				}

			}
			stFontGliph.bDrak = TRUE;
			vecFontGliph.push_back(stFontGliph);
			stFontGliph.vecFPOINT.clear();
		}
		if(vecFontGliph.size()==1)
		{
			gluTessBeginPolygon(m_tess, 0);
			for(k=0;k<vecFontGliph.size();k++)
			{
				for(j=0;j<vecFontGliph[k].vecFPOINT.size();j++)
				{
					Test[0]= vecFontGliph[k].vecFPOINT[j].x;
					Test[1]= vecFontGliph[k].vecFPOINT[j].y;
					gluTessVertex(m_tess, Test, &vecFontGliph[k].vecFPOINT[j]);
				}
			}	
			gluTessEndPolygon(m_tess);
		}
		else if(vecFontGliph.size()>1)
		{
			for(k=0;k<vecFontGliph.size();k++)
			{
				for(j=0;j<vecFontGliph.size();j++)
				{
					if(k==j)
						continue;
					else
					{
						if(CheckPolygonInPolygon(vecFontGliph[k].vecFPOINT,vecFontGliph[j].vecFPOINT))
						{
							vecFontGliph[k].bDrak = TRUE;
							vecFontGliph[j].bDrak = FALSE;
						}
					}
				}
			}
			for(k=0;k<vecFontGliph.size();k++)
			{
				if(!vecFontGliph[k].bDrak)
				{
					glStencilFunc(GL_NEVER,1,1);
					glStencilOp(GL_INCR,GL_INCR,GL_INCR);			
					gluTessBeginPolygon(m_tess, 0);
					for(j=0;j<vecFontGliph[k].vecFPOINT.size();j++)
					{
						Test[0]= vecFontGliph[k].vecFPOINT[j].x;
						Test[1]= vecFontGliph[k].vecFPOINT[j].y;
						gluTessVertex(m_tess, Test, &vecFontGliph[k].vecFPOINT[j]);
					}
					gluTessEndPolygon(m_tess);
				}
			}
			for(k=0;k<vecFontGliph.size();k++)
			{

				if(vecFontGliph[k].bDrak)
				{
					glStencilFunc(GL_EQUAL,0,15);
					glStencilOp(GL_ZERO,GL_ZERO,GL_ZERO);		
					gluTessBeginPolygon(m_tess, 0);
					for(j=0;j<vecFontGliph[k].vecFPOINT.size();j++)
					{
						Test[0]= vecFontGliph[k].vecFPOINT[j].x;
						Test[1]= vecFontGliph[k].vecFPOINT[j].y;
						gluTessVertex(m_tess, Test, &vecFontGliph[k].vecFPOINT[j]);
					}
					gluTessEndPolygon(m_tess);
					glClear(GL_STENCIL_BUFFER_BIT);
				}			
			}
		}
		FT_Done_Glyph(glyph);
		glTranslatef(fFontWidth ,0,0);
		for(k=0;k<vecFontGliph.size();k++)
		{
			vecFontGliph[k].vecFPOINT.clear();
		}
		vecFontGliph.clear();
	}
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	FT_Done_Face(face);
	FT_Done_FreeType(library);
#ifndef _UNICODE
	delete szCh;
	szCh = NULL;
#endif
}
*/
vector<SHPFONTSIZE> *COpenGLFontCam::GetFontSize()
{
	return &m_vecFontSize;
}

CString COpenGLFontCam::GetFontFilePath()
{
	return m_strFontFilePath;
}

char* COpenGLFontCam::StringToChar(CString str, int &nLen)
{
	char*		szStr = NULL;
	wchar_t*	wszStr;

	USES_CONVERSION;
	//1. CString to wchar_t* conversion
	wszStr = T2W(str.GetBuffer(str.GetLength()));

	//2. wchar_t* to char* conversion
	nLen = WideCharToMultiByte(CP_ACP, 0, wszStr, -1, NULL, 0, NULL, NULL); //char* 형에 대한길이를 구함 
	szStr = new char[nLen];  //메모리 할당 

							 //3. wchar_t* to char* conversion
	WideCharToMultiByte(CP_ACP, 0, wszStr, -1, szStr, nLen, 0, 0);
	return szStr;
}
