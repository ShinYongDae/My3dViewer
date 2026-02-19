// OpenGLFont.h: interface for the COpenGLFontCam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLFONT_H__1FA9A1ED_EF9D_4D8D_842D_C73B5EF61A49__INCLUDED_)
#define AFX_OPENGLFONT_H__1FA9A1ED_EF9D_4D8D_842D_C73B5EF61A49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <gl/freeglut_std.h>
#pragma comment (lib, "freeglut.lib")

#include <vector>
using namespace std;

#include "Entities.h"
#include "GlobalDefine.h"

// Freetype font header
//#include "ft2build.h"
//#include "freetype.h"
//#include "ftglyph.h"
//#include "ftoutln.h"
//#include "fttrigon.h"
//#include "ftstroke.h"


///////////////////////////DXF
//#define FONTSCALE   0.0156
//#define FONTSCALE   0.0323
//#define FONTSCALE   0.023
#define FONTSCALE   0.0168
#define FONTUNITSCALE 0.00795
#define FONTLFGAP     0.66667
#define FONTLINEGAP	  0.294 
#define DOTLENGTH	0.001
#define LEFTUP      0
#define LEFTDOWN    1
#define RIGHTUP     2
#define RIGHTDOWN   3
#define CP949		949

typedef struct tag_SHP_FONT_INFO {
	int nListIndex;
	double fHeight,fWidth,fLowerPartHeight,fBearingX,fEndGapX;
} SHP_FONT_INFO, *PSHP_FONT_INFO;


typedef struct tag_SHPFONTSIZE {
	int BearingX;
	int	width;
	int RightGapX;
	int height;
	int LowerPartHeight;
} SHPFONTSIZE, *PSHPFONTSIZE;

typedef struct tag_SHPFONT {
	unsigned short   nIndex;
	CString strNum;
	vector<CString> vecElement;
} SHPFONT, *PSHPFONT;

typedef struct tag_SHPFILE {
	CString strFileName;
	vector<SHPFONT> vecShpFont;
	short nScale;
	BOOL bHex;
} SHPFILE, *PSHPFILE;

typedef struct tag_FONTGLIPH {
	vector<FPOINT> vecFPOINT;
	BOOL bDrak;
} FONTGLIPH, *PFONTGLIPH;


class COpenGLFontCam  
{
	char* StringToChar(CString str, int &nLen);

public:
	COpenGLFontCam();
	virtual ~COpenGLFontCam();

public:
	void DestroyFont();
	BOOL Initialize(FONT_TYPE::MODE nMode, const char * chFontName, unsigned int nSize);
	void GetFontSize(const unsigned char *chText,double &fWidth, double &fHeight,double &fLowerPartHeight,double fscale);
	void DrawBMPFont(const char *fmt);
	//void DrawUniTypeFont(const TCHAR *fname, unsigned int h, CString str);
	//void DrawUniTypeFontChar(const TCHAR *fname, unsigned int h, unsigned short nNum,double fScale,double &fFontWidth);
	void DrawFreeTypeFont(CString strText);
	void DrawFreeTypeFontChar(unsigned short nNum);
	vector<SHPFONTSIZE> *GetFontSize();
	void InitTessellation();
	CString GetFontFilePath();
private:
	FONT_TYPE::MODE m_nMode;
	CString m_strFontFilePath;
	int m_nSize;
	GLuint m_textures[129];
	GLuint m_nlist_base;	
	vector<SHPFONTSIZE> m_vecFontSize;
	GLUtesselator *m_tess;
private:
	static void CALLBACK tessBeginCB(GLenum which);
	static void CALLBACK tessEndCB();
	static void CALLBACK tessVertexCB(const GLvoid *data);
	void ConicToN(vector<DPOINT> vecControl,vector<FPOINT> &vecVertex, int nNum);
	BOOL CheckPolygonInPolygon(vector<FPOINT> vecPolygon1, vector<FPOINT> vecPolygon2);
	//BOOL InitFont(FT_Face &face,FT_Library &library,const char* chFontName);
	int next_p2 ( int a );
	//void MakeVertexFontList(FT_Face face, unsigned long ch,int &nFontWidth,int &nFontHeight,int &nFontLowerPartHeight,int &nBearingX,int &nRightGapX);
	//void MakeBitmapFontList(FT_Face face,  unsigned long ch,int &nFontWidth,int &nFontHeight,int &nFontLowerPartHeight);
};

#endif // !defined(AFX_OPENGLFONT_H__1FA9A1ED_EF9D_4D8D_842D_C73B5EF61A49__INCLUDED_)
