// GlobalDefine.h: 
///////////////////////////////////////////////////////////////////////////////////////
////                          GlobalDefine.h Ver 1.6                               ////
////                               Corp   : GIGAVIS                                ////
////																			   ////
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _GLOBAL_DEFINE_
#define _GLOBAL_DEFINE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NUMBER_OF_SPEC_ITEM 80

// Last Setting Data

typedef enum tagMS_ID{MS_XY = 0, MS_Y = 1, MS_X = 2, MS_Z = 3} MS_ID; 
typedef enum tagAXIS_ID{AXIS_Y = 0, AXIS_X = 1, AXIS_Z = 2} AXIS_ID; 

typedef enum { ERRORMSG = 0, POWERDATA = 2, TEMPERATURE = 3, CLEAR = 4 } POWERMAX_DATATYPE;

#define TIMER_HOMMING		10

#define  CLOSED_FOLDER 0
#define  OPEN_FOLDER   1
#define  FLOPPY_DRIVE  2
#define  FIXED_DRIVE   3
#define  NET_DRIVE     4
#define  CDROM_DRIVE   5
#define  MY_COM        6
#define  RECYCLE_BIN   7
#define  DESKTOP       8
#define  CONTROL_PANEL 9

#define PATH_ERROR		   -1
#define PATH_NOT_FOUND		0
#define PATH_IS_FILE		1
#define PATH_IS_FOLDER		2

//++++++++++++++++++++++++++++++++++++++++
//////////////////////////////////////////////////////////////////////////
//gv af
#define	OPTICS_COUNT		2

//enum AcquisitionSeq : uint8_t
//{
//	Acquisition_init,
//	ScanStart,
//	ScanWait,
//	ScanComplete
//};

//enum OpticsType : uint8_t
//{
//	UV_Optics,
//	Gv3D_Optics
//};
//////////////////////////////////////////////////////////////////////////
// CLogOn class
namespace LOGIN_USER
{
	enum LEVEL 
	{ 
		ADMINISTRATOR,
		ENGINEER,
		OPERATOR
	};
};

namespace ITEM_VIEW
{
	enum ITEM
	{
		MAINVIEW,
		MENU,
		ETC

	};
}

typedef struct tagUSER_INFO{
	CString	ID;		// ID
	CString PLevel;	// Permission level
	CString PW;		// PERSONAL Password
}USER_INFO;
typedef CArray<USER_INFO, USER_INFO> CArUserList;

class CUserInfo;
class CUserInfo : public tagUSER_INFO  
{
public:
	CUserInfo::CUserInfo()
	{
		ID = _T("");	// ID
		PLevel = _T("");	// Permission Level
		PW = _T("");	// PERSONAL Password
	}
	virtual ~CUserInfo()
	{

	}
	void    operator =(USER_INFO Param) // Nonzero if the points are equal; otherwise 0.
	{
		ID = Param.ID;	// ID
		PLevel = Param.PLevel;	// 부서
		PW = Param.PW;	// PERSONAL Password
	}
};

typedef struct tagLog_INFO{
	CString strDate;
	CString strJob;
	CString strDialog;
	CString strParam;
	CString strpreValue;
	CString strValue;
	CString strModel;
	CString strLayer;
	float fResolution;
	CString strUserID;
}Log_INFO;
typedef CArray<Log_INFO, Log_INFO> CArLogInfoList;

typedef struct tagPRCLOG_INFO{
	CString strModel;
	CString strLayer;
	float fResolution;
	CString strPrcTime;
	CString strResult;
	CString strUserID;
	CString strUserLevel;
	CString strDate;
}PRCLOG_INFO;
typedef CArray<PRCLOG_INFO, PRCLOG_INFO> CArPRCLogInfoList;

struct ADOConnetInfo{
	
	CString strServerIP;
	CString strDataBase;
	CString strUserID;
	CString strPasswrod;
};

typedef struct MyMessage {
	CString strTitleMsg;
	CString strMsg;
	COLORREF color;
	DWORD dwDispTime;
	BOOL bOverWrite;
	CString strErrorDispatchMsg;
}structMyMessage;


//++++++++++++++++++++++++++++++++++++++++
// Shared Memory Structure
#define SH_MEM_MODEL			0
#define SH_MEM_MODEL_FLAG		1
#define SH_MEM_LAYER			2
#define SH_MEM_LAYER_FLAG		3
#define SH_MEM_SPEC_DIR			4
#define SH_MEM_SPEC_DIR_FLAG	5
#define SH_MEM_MASTER_DIR		6
#define SH_MEM_MASTER_DIR_FLAG	7
#define SH_MEM_REF_INDEX		8
#define SH_MEM_REF_INDEX_FLAG	9
#define SH_MEM_REF_NUM			10
#define SH_MEM_REF_NUM_FLAG		11
#define SH_MEM_END				12
#define SH_MEM_END_FLAG			13

typedef struct tagShMemModelInfo{
	int nRPUID;
	int nEntireRPUNum;
	char SpecFolderPath[512];
	char ModelName[512];
	char LayerName[512];
	char RefSavePath[512];
} SH_MEM_MODEL_INFO;

typedef struct tagShMemStatus{
	BOOL bWriteOn;
	BOOL bReceiveOn;
	int nActionCode;
	int nStatus;
	int nStSwathID;
	int nEdSwathID;
} SH_MEM_STATUS;

typedef struct tagShMemSwathInfo{
	char cSwathAct[1000];
} SH_MEM_SWATH_INFO;

#define SH_MEM_BANK_NUM			7

#define SH_MEM_I2R_BANK				0
#define SH_MEM_I2R_RECEIVE_BANK		1
#define SH_MEM_R2I_BANK				2
#define SH_MEM_R2I_RECEIVE_BANK		3
#define SH_MEM_MODEL_INFO_BANK		4
#define SH_MEM_SWATH_BUILD_BANK		5
#define SH_MEM_SWATH_DELETE_BANK	6

#define SHMEM_ACT_INIT_STATUS			0
#define SHMEM_ACT_ON					1

#define SHMEM_IPU_ACT_DATA_TRANS_OK		1
#define SHMEM_IPU_ACT_REFBUILD_START	2
#define SHMEM_IPU_ACT_REFBUILD_STOP		3
#define SHMEM_IPU_ACT_REFDELETE_END		4

#define SHMEM_RPU_ACT_STANDBY_OK		11
#define SHMEM_RPU_ACT_STOP_OK			13


//++++++++++++++++++++++++++++++++++++++++
//CamView Timer//
#define TIMER_SHMEM_DATA_TRANS			10
#define TIMER_SHMEM_REFBUILD_START		20
#define TIMER_SHMEM_REFBUILD_STOP		30
#define TIMER_SHMEM_STATE_CHECK			40
#define TIMER_PROC_STATE_CHECK			50
#define TIMER_UPLOAD_CAM_STATUS			200
#define TIMER_STATUS_PROCESSING_INFO		300
#define TIMER_CHECK_RPU_PROCESSING_INFO		301
#define	TIMER_REMAKE_PTM_INFO				302
#define TIMER_DISPLAY_CREATE_REF_TIME		304
#define TIMER_END_REF_DATA_PROCESSING_INFO	305
#define TIMER_CHECK_NEXT_RPU_PROCESSING_INFO 306
#define TIMER_LEGACY_CONVERT_START			 400

#ifndef VER_PLATFORM_WIN32s
#define VER_PLATFORM_WIN32s             0
#endif
#ifndef VER_PLATFORM_WIN32_WINDOWS
#define VER_PLATFORM_WIN32_WINDOWS      1
#endif
#ifndef VER_PLATFORM_WIN32_NT
#define VER_PLATFORM_WIN32_NT           2
#endif
#ifndef VER_PLATFORM_WIN32_CE
#define VER_PLATFORM_WIN32_CE           3
#endif

//////////////////////////////////////////////////////////////////////////
static COLORREF CadColor[256] = 
{
	RGB(128,255,255),
	RGB(255,  0,  0), RGB(255,255,  0), RGB(  0,255,  0), RGB(  0,255,255), RGB(  0,  0,255),	// 5
	RGB(255,  0,255), RGB(255,255,128), RGB(128,128,128), RGB(192,192,192), RGB(255,  0,  0),	// 10
	RGB(255,127,127), RGB(204,  0,  0), RGB(204,102,102), RGB(153,  0,  0), RGB(153, 76, 76),	// 15
	RGB(127,  0,  0), RGB(127, 63, 63), RGB( 76,  0,  0), RGB( 76, 38, 38), RGB(255, 63,  0),	// 20
	RGB(255,159,127), RGB(204, 51,  0), RGB(204,127,102), RGB(153, 38,  0), RGB(153, 95, 76),	// 25
	RGB(127, 31,  0), RGB(127, 79, 63), RGB( 76, 19,  0), RGB( 76, 47, 38), RGB(255,127,  0),	// 30
	RGB(255,191,127), RGB(204,102,  0), RGB(204,153,102), RGB(153, 76,  0), RGB(153,114, 76),	// 35
	RGB(127, 63,  0), RGB(127, 95, 63), RGB( 76, 38,  0), RGB( 76, 57, 38), RGB(255,191,  0),	// 40
	RGB(255,223,127), RGB(204,153,  0), RGB(204,178,102), RGB(153,114,  0), RGB(153,133, 76),	// 45
	RGB(127, 95,  0), RGB(127,111, 63), RGB( 76, 57,  0), RGB( 76, 66, 38), RGB(255,255,  0),	// 50
	RGB(255,255,127), RGB(204,204,  0), RGB(204,204,102), RGB(153,153,  0), RGB(153,153, 76),	// 55
	RGB(127,127,  0), RGB(127,127, 63), RGB( 76, 76,  0), RGB( 76, 76, 38), RGB(191,255,  0),	// 60
	RGB(223,255,127), RGB(153,204,  0), RGB(178,204,102), RGB(114,153,  0), RGB(133,153, 76),	// 65
	RGB( 95,127,  0), RGB(111,127, 63), RGB( 57, 76,  0), RGB( 66, 76, 38), RGB(127,255,  0),	// 70
	RGB(191,255,127), RGB(102,204,  0), RGB(153,204,102), RGB( 76,153,  0), RGB(114,153, 76),	// 75
	RGB( 63,127,  0), RGB( 95,127, 63), RGB( 38, 76,  0), RGB( 57, 76, 38), RGB( 63,255,  0),	// 80
	RGB(159,255,127), RGB( 51,204,  0), RGB(127,204,102), RGB( 38,153,  0), RGB( 95,153, 76),	// 85
	RGB( 31,127,  0), RGB( 79,127, 63), RGB( 19, 76,  0), RGB( 47, 76, 38), RGB(  0,255,  0),	// 90
	RGB(127,255,127), RGB(  0,204,  0), RGB(102,204,102), RGB(  0,153,  0), RGB( 76,153, 76),	// 95
	RGB(  0,127,  0), RGB( 63,127, 63), RGB(  0, 76,  0), RGB( 38, 76, 38), RGB(  0,255, 63),	// 100
	RGB(127,255,129), RGB(  0,204, 51), RGB(102,204,127), RGB(  0,153, 38), RGB( 76,153, 95),	// 105
	RGB(  0,127, 31), RGB( 63,127, 79), RGB(  0, 76, 19), RGB( 38, 76, 47), RGB(  0,255,127),	// 110
	RGB(127,255,191), RGB(  0,204,102), RGB(102,204,153), RGB(  0,153, 76), RGB( 76,153,114),	// 115
	RGB(  0,127, 63), RGB( 63,127, 95), RGB(  0, 76, 38), RGB( 38, 76, 57), RGB(  0,255,191),	// 120
	RGB(127,255,223), RGB(  0,204,153), RGB(102,204,178), RGB(  0,153,114), RGB( 76,153,133),	// 125
	RGB(  0,127, 95), RGB( 63,127,111), RGB(  0, 76, 57), RGB( 38, 76, 66), RGB(  0,255,255),	// 130
	RGB(127,255,255), RGB(  0,204,204), RGB(102,204,204), RGB(  0,153,153), RGB( 76,153,153),	// 135
	RGB(  0,127,127), RGB( 63,127,127), RGB(  0, 76, 76), RGB( 38, 76, 76), RGB(  0,191,255),	// 140
	RGB(127,223,255), RGB(  0,153,204), RGB(102,178,204), RGB(  0,114,153), RGB( 76,133,153),	// 145
	RGB(  0, 95,127), RGB( 63,111,127), RGB(  0, 57, 76), RGB( 38, 66, 76), RGB(  0,127,255),	// 150
	RGB(127,191,255), RGB(  0,102,204), RGB(102,153,204), RGB(  0, 76,153), RGB( 76,114,153),	// 155
	RGB(  0, 63,127), RGB( 63, 95,127), RGB(  0, 38, 76), RGB( 38, 57, 76), RGB(  0, 63,255),	// 160
	RGB(127,159,255), RGB(  0, 51,204), RGB(102,127,204), RGB(  0, 38,153), RGB( 76, 95,153),	// 165
	RGB(  0, 31,127), RGB( 63, 79,127), RGB(  0, 19, 76), RGB( 38, 47, 76), RGB(  0,  0,255),	// 170
	RGB(127,127,255), RGB(  0,  0,204), RGB(102,102,204), RGB(  0,  0,153), RGB( 76, 76,153),	// 175
	RGB(  0,  0,127), RGB( 63, 63,127), RGB(  0,  0, 76), RGB( 38, 38, 76), RGB( 63,  0,255),	// 180
	RGB(159,127,255), RGB( 51,  0,204), RGB(127,102,204), RGB( 38,  0,153), RGB( 95, 76,153),	// 185
	RGB( 31,  0,127), RGB( 79, 63,127), RGB( 19,  0, 76), RGB( 47, 38, 76), RGB(127,  0,255),	// 190
	RGB(191,127,255), RGB(102,  0,204), RGB(153,102,204), RGB( 76,  0,153), RGB(114, 76,153),	// 195
	RGB( 63,  0,127), RGB( 95, 63,127), RGB( 38,  0, 76), RGB( 57, 38, 76), RGB(191,  0,255),	// 200
	RGB(223,127,255), RGB(153,  0,204), RGB(178,102,204), RGB(114,  0,153), RGB(133, 76,153),	// 205
	RGB( 95,  0,127), RGB(111, 63,127), RGB( 57,  0, 76), RGB( 66, 38, 76), RGB(255,  0,255),	// 210
	RGB(255,127,255), RGB(204,  0,204), RGB(204,102,204), RGB(153,  0,153), RGB(153, 76,153),	// 215
	RGB(127,  0,127), RGB(127, 63,127), RGB( 76,  0, 76), RGB( 76, 38, 76), RGB(255,  0,191),	// 220
	RGB(255,127,223), RGB(204,  0,153), RGB(204,102,178), RGB(153,  0,114), RGB(153, 76,133),	// 225
	RGB(127,  0, 95), RGB(127, 63,111), RGB( 76,  0, 57), RGB( 76, 38, 66), RGB(255,  0,127),	// 230
	RGB(255,127,191), RGB(204,  0,102), RGB(204,102,153), RGB(153,  0, 76), RGB(153, 76,114),	// 235
	RGB(127,  0, 63), RGB(127, 63, 95), RGB( 76,  0, 38), RGB( 76, 38, 57), RGB(255,  0, 63),	// 240
	RGB(255,127,159), RGB(204,  0, 51), RGB(204,102,127), RGB(153,  0, 38), RGB(153, 76, 95),	// 245
	RGB(127,  0, 31), RGB(127, 63, 79), RGB( 76,  0, 19), RGB( 76, 38, 47), RGB( 51, 51, 51),	// 250
	RGB( 91, 91, 91), RGB(132,132,132), RGB(173,173,173), RGB(214,214,214), RGB(0,0,0)	// 255
};

// Jog define
#define NO_MOTOR		-1
#define NO_DIRECTION	2
#define DIR_CW	1
#define DIR_CCW	-1

// socket
#define MAX_CONNECTION		15
const int SOCK_TCP	= 0;
const int SOCK_UDP  = 1;


				
				


enum NotificationTypes { NOTIFY_INC_PROGRESS,NOTIFY_TASK_COMPLETED ,NOTIFY_TASK_THREAD_COMPLETED };

enum VectDir{CCW=-1,PARALLEL,CW};
enum OnOffAction {OFF, ON};

typedef struct stFiducial
{
	double dPtX; // Cam Position X
	double dPtY; // Cam Position Y
	double dMpX; // Motion Position X
	double dMpY; // Motion Position Y

	int nFlag;
	int nShape;
	double dWidth;
	double dHeight;
	double dArea;
}Fiducial;

// enumeration
namespace FRAME_STYLE
{
	enum STYLE
	{
		CODEJOCK,
		OFFICE2007,
		OFFICE2010,
		VISTA,
		WINDOWS8,
		WINXPLUNA,
		WINXPROYALE
	};

	enum THEME
	{
		MAC,
		GRAY, 
		ICY, 
		GRADIENT, 
		BREVEL,
		FANCY,
		ACD 
	};
}
namespace FILE_ERROR_CODE
{
	enum CODE 
	{ 
		NONE,
		FILE_NOT_FOUND,		// 파일이 없을때
		FILE_TYPE_MISMATCH,		// 
		FILE_CONTENTS_ERROR,
		FILE_ZERO_SIZE,
		FILE_MAPPING_ERROR,
		FILE_MAP_VIEW_ERROR,
		FILE_PATH_ERROR,
		MEMORY_ALLOC_ERROR
	};
};

namespace SAFETY_THREAD
{
	enum STATUS 
	{ 
		STOPPED,
		START,
		PAUSE,
		RESUME
	};
};

namespace DEFECT_DATA
{
	enum TYPE		{ DEFECT, BAD};
	enum SOURCE  	{ ORIGINAL=0,CURRENT};
	enum STORAGE    { NONE, SERIAL, LOT, LAYER, MODEL};

};

namespace TOOL_TYPE
{
	enum TYPE {
		SPOT, LINE, LINE_GRID, SPOT_GRID, ARC, CIRCLE, TREPAN, SPIRAL, SPIRAL_CIRCLE
	};

};

namespace CHUCK
{
	enum DATA_TYPE
	{
		REFERENCE,
		TARGET
	};
};

namespace PROCESS_TARGET
{
	enum TARGET_TYPE
	{
		GOOD_PIECE,
		BAD_PIECE,
		ALL_PIECE
	};
};

namespace LOG_CODE
{
	enum LOG_NAME
	{
		LOGIN,
		CHANGE_SETTING,
		PROCESSING_INFO
	};
};

namespace DIALOG_CODE
{
	enum DIALOG_NAME
	{
		SET_CAM_SYSTEM,
		SET_CAM_DEVICE,
		SET_CAM_STORAGE,
		SET_CAM_PATH,
		SET_CAM_EDIT_ENVIRONMENT,
		SET_CAM_DISPLAY_COLOR,
		SET_CAM_CUSTOMIZE,
		SET_CAM_SPEC_CONFIG,
		SET_CAM_GIGAVIS,
		SET_CAM_SAMSUNG,
		SET_CAM_KYOCERA,
		MACHINE_SYSTEM,
		RS274X_FORMAT,
		RS274D_FORMAT,
		DPF_FORMAT,
		ODB_FORMAT,
		EXCELLON_FORMAT,
		DXF_FORMAT,
		GDS_FORMAT,
		SELECT_UNIT,
		ADJUST_SCALE
	};
};


#define	ASCII_STX		(0x02)
#define	ASCII_ETX		(0x03)
#define	ASCII_ENQ		(0x05)
#define	ASCII_TAB		(0x09)
#define	ASCII_LF		(0x0a)
#define	ASCII_CR		(0x0d)
#define	ASCII_XON		(0x11)
#define	ASCII_XOFF		(0x13)
#define ASCII_SPACE		(0x20)

// Farpoint Spread Sheet Cell Type
#define TYPE_DEFAULT	1
#define TYPE_EDIT		1
#define TYPE_COMBO		8
#define TYPE_CHECK		10
#define TYPE_BUTTON		7
#define TYPE_STATIC		5

#define ALIGN_LEFT		0
#define ALIGN_RIGHT		1
#define ALIGN_CENTER	2





// COpenGLView Class Picking Flag
#define G_PICK_CFPOINT3D 1
#define G_PICK_QAUD3D 2
#define G_GET_COLVALUE 4
// COpenGLDraw Class DrawOption
#define D_SELECT_XDIR 0
#define D_SELECT_YDIR 1
#define D_SELECT_XYDIR 2
#define D_LINES 1
#define D_VERTEX 2
#define D_HISTO_YZ_INVERT 4
#define D_HISTO_XY_INVERT 8


// QAUD3D ARRAY VIEW OPTION 
#define QUAD_FULL3D 1
#define QUAD_LINES 2
#define QUAD_VERTEX 3
#define QUAD_LINES_CENTROID_DOTTED 4
#define QUAD_LINES_CENTROID_DOTTED_2D 6
#define QUAD_FULL2D 5

//USE FOR GL3D START
//GLPOINT3D 클래스는 각 버텍스를 관리하는 클래스 X,Y,Z좌표 및 정점에대한 컬러값을 기억한다.
#define G_COLORED 1
#define G_DEFAULT 1// R->B HIGH->LOW

// BaseVal flag
#define G_SELECT_X 0 // X값의 배열을 기준으로 삼는다 
#define G_SELECT_Y 1 // Y
#define G_SELECT_Z 2 // Z 

// Operation Flag
#define G_MATH_FIND_MAX 1 // 최대값을 찾는다 
#define G_MATH_FIND_MIN 2 // 최소값을 찾는다 
#define G_MATH_FIND_MEAN 3 // 평균값을 찾는다 
#define G_MATH_FIND_STD 4 // 표준편차를 찾는다 

// ModeFlag
#define G_Math_CALC_DEFAULT 1 //기본모드.. 전체 포인트에 대한 값
#define G_Math_CALC_DIRX 2 // X좌표 방향에 대한 계산 
#define G_Math_CALC_DIRY 3 // Y좌표 방향에 대한 계산

#define G_DONTCARE -1 // 사용하지 않는 함수 인자에 사용.

#define G_COLOR_GET_ARRAY 1
#define G_COLOR_GET_LEVELARRAY 2
#define G_COLOR_CONVERT_INVERTED 2// B->R LOW ->HIGH
#define G_COLOR_NO_FREE 3

// GRID OPTION
#define G_GRID_3D 1 // 그리드를 그리되 Z값을 가지는 그리드를 그린다
#define G_GRID_2D 2 // 그리드를 그리되 Z값이 동일한 그리드를 그린다 
#define G_GRID_TEXT 1// 그리드를 그리되 각 축의 값에대한 Z값을 뿌려준다 
#define G_GRID_TEXT_INVERT 2


#define G_SHARE_ARRAY 1 // 각 개체는 버퍼를 새로 할당하지 않고 하나의 버퍼를 공유한다... 대신 THREAD SAFE하지 않음. 버퍼가 깨지면 모두 죽음

//MESH OPTION
#define G_MESH_3D 1
#define G_MESH_2D 2
#define G_MESH_3D_QAUD 4
#define G_MESH_SELECT_DIRX 0
#define G_MESH_SELECT_DIRY 1
#define G_MESH_HISTO_Z 1

#define G_MESH_SEARCH_MEASUREPOINT 2
#define G_MESH_SEARCH_INTERPOLATION 3
#define G_MESH_QUAD_CENTER 6
#define G_MESH_MEASURE_POINT 7

#define SQR(X) ((X)*(X))
//END


//보간 모드 
#define G_BILINEAR 5

#define DetGcode 99999

#define LOAD_TEXTURE_ALL	 0
#define LOAD_TEXTURE_PARTIAL 1
#define DRAW_TEXTURE_ALL	 2
#define DRAW_TEXTURE_PARTIAL 3

#define NONE_TEXTURE		0
#define LOAD_TEXTURE		1
#define DRAW_TEXTURE		2


#define MAXGLLISTSNRCNT  10000

// DefectData class
#define PIECE_START_NUMBER 1
#define STRIP_START_NUMBER 1

#define MAX_INSPECTION_REGION_GROUP	10
#define MAX_PIECE_REGION_GROUP	10

#define MAX_PROCESS_CODE_TYPE 56

#endif // !defined(_GLOBAL_DEFINE_)


