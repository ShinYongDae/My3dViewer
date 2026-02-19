
#if !defined(AFX_ENTITIES_H__118242D4_4CA0_45FE_84F6_AE9468839650__INCLUDED_)
#define AFX_ENTITIES_H__118242D4_4CA0_45FE_84F6_AE9468839650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeoDataType.h"
//////////////////////////////////////////////////////////////////////////
#define SEM_FC_PLC_DATA _T("C:\\AorSet\\PLCData.ini")
#define SEM_FC_PLC_DATA2 _T("C:\\AorSet\\PLCData2.ini")

typedef enum tagSemFCReg
{
	SEM_REPAIR_STATUS,
	SEM_AOI_ORG_POS,
	SEM_USE_CCL = 2,
	SEM_READ_SUCCESS = 2, // 삼성전용
	SEM_USE_WORKING,
	SEM_CLAMP_ON,
	SEM_CLAMP_OFF,
	SEM_USE_2D,
	SEM_USE_VAC,
	SEM_RESERVE1,
	SEM_RESERVE2,
	SEM_RESERVE3,
	SEM_RESERVE4,
	SEM_RESERVE5,
	SEM_RESERVE6,
	SEM_RESERVE7,
	SEM_RESERVE8,
	SEM_HEARTBEAT
}SEM_PLC_REGISTER;
//////////////////////////////////////////////////////////////////////////


typedef enum tagSemLoaderStep
{
	LOADER_READY = 0,
	LOADER_START = 1,
	LOADER_START_ING1 = 2,
	LOADER_START_ING2 = 3,
	LOADER_START_ING3 = 4,
	LOADER_START_ING4 = 5,
	LOADER_START_ING5 = 6,
	LOADER_START_END = 7,

	LOADER_END = 8,
	LOADER_END_ING1 = 9,
	LOADER_END_ING2 = 10,

	LOADER_GO_BARCODE = 15,
	LOADER_GO_BARCODE_ING = 16,
	LOADER_GO_BARCODE_DONE = 17,
	LOADER_GO_BARCODE_QUERY = 18,

	LOADER_PANEL_ON_OFF = 25,
	LOADER_PANEL_ON_OFF_ING1 = 26,
	LOADER_PANEL_ON_OFF_ING2 = 27,
	LOADER_PANEL_ON_OFF_ING3 = 28,
	LOADER_PANEL_ON_OFF_ING4 = 29,
	LOADER_PANEL_ON_OFF_ING5 = 30,
	LOADER_PANEL_ON_OFF_ING6 = 31,
	LOADER_PANEL_ON_OFF_ING7 = 32,
	LOADER_PANEL_ON_OFF_ING8 = 33,

	LOADER_DATA_LOAD = 9,
}SEM_LOADER_STEP;





//////////////////////////////////////////////////////////////////////////
#define INCHTOMM	25.4
//////////////////////////////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++
namespace INSPECTION_MODE
{
	enum MODE
	{
		PATTERN,
		VIA,
		PTH,
		CCL,
		ENCAP,				//// 20170629 Add
		SPUTTER,
		UBM,
		SRO_PAD,			//// 20210603 Add
		NONE
	};
}

namespace DRAW_DRILL
{
	enum SHAPE
	{
		CIRCLE,
		LINE,
		OVAL,
		ARC,
		POLYGON,
		TEXT
	};
}

//// 20181125 Add
namespace OBJECT_INFO
{
	enum SHAPE
	{	
		CIRCLE,
		ELLIPSE,
		ROUND_LINE,
		RECTANGLE_LINE,
		SQUARE_LINE,
		OVAL,
		ARC_CW,
		ARC_CCW,
		POLYGON,
		RECTANGULA,
		TEXT,
		NONE
	};
}
namespace LanguageType
{
	enum ENUM
	{
		DEFAULT,	// Default language , may be local 
		KOREAN,		// Korean
		ENGLISH,	// English 
		JAPANESE,	// Japanese
		CHINESE,	// Chinese
		VIETNAMESE	// VIETNAMESE
	};
}

namespace TRANSFORM_DATA
{
	enum TYPE 
	{ 
		NONE,
		MIRROR_V,		// rect zoom
		MIRROR_H,		
		ROTATE_180,
		ROTATE_CCW,
		ROTATE_CW,
		MIRROR_VH,
		SCALE,
		TRANSLATE,
		RESIZE
	};
};
namespace CAM_WORK
{
	enum REGION
	{
		NONE,
		PANEL,	
		STRIP,
		PIECE,
		INSPECTION,		
		CHILD_INSPECTION,
		MPOINT,		
		MASK,		
		LEAD,		
		FINE,		
		ROI,
		SCALEALIGNREGIONPTMODEL,
		MCAUNITREGION,
		PTMODELAUTOSKIPAREA,
		ALIGN_POINT,
		MEASURE_POINT,
		MARKING_POINT,
		UNDER_REGION,
		COPPER_RESIDUAL_RATE_AREA,
		CAVITY_REGION,
		PIECE_SEGMENT_REGION,
		TRACE_LOGIC_MASK_AREA,
		GAS_EMISSION_AREA_MASK,
		EXTERNAL_INSPECTION_POINT,
		SRO_PAD_OBJ,
		REPAIR_MASK_AREA
	};
	enum WORK_STATUS
	{
		WORK_NONE,
		WORK_CREATE,
		WORK_EDIT,
		WORK_EDIT_SUB,
		WORK_SELECT,
		WORK_SELECT_PROCESS_REGION
	};

	enum SET_REGION
	{
		SET_NONE,
		SET_PANEL,	
		SET_STRIP,
		SET_PIECE,
		SET_INSPECTION,		
		SET_CHILD_INSPECTION,
		SET_MPOINT,		
		SET_MASK,		
		SET_LEAD,		
		SET_FINE,		
		SET_ROI,
		SET_ORIGINPOINT,
		SET_ALIGNPOINT,
		SET_SCALEALIGNREGIONPTMODEL,
		SET_FIDUCIALMARK,
		SET_AFPOINT,
		SET_MEASUREPOINT,
		SET_MCAUNITREGION,
		SET_PTMODELAUTOSKIPAREA,
		SET_EXT_AREA,
		SET_MARKING_POINT,
		SET_EXTERNAL_INSPECTION_POINT,
		SET_UNDER_REGION,
		SET_COPPER_RESIDUAL_RATE_AREA,
		SET_PIECE_SEGMENT_REGION,
		SET_TRACE_LOGIC_MASK_AREA,
		SET_SRO_PAD_OBJ,
		SET_REPAIR_MASK_AREA
	};

	enum REGION_SHAPE
	{
		TRIANGLE,
		RECTANGULA,
		QUAD,
		POLYGON,
		ELLIPSE,
		CROSS
	};

	enum ARRAY_WORK
	{
		ARRAY_NONE,
		ARRAY_PIECE = 1,
		ARRAY_STRIP = 2,
		ARRAY_INSPECTION = 3,
		ARRAY_MASK=4,
		ARRAY_LEADAREA=5,
		ARRAY_FINEAREA=6,
		ARRAY_ROI=7,
		ARRAY_MEASUREPOINT,
		ARRAY_SCALEALIGNPOINT,
		ARRAY_FIDUCIALMARK,
		ARRAY_MCAUNITREGION,
		ARRAY_MCAUNITBLOCK,
		ARRAY_MPOINT,
		ARRAY_MARKING_POINT,
		ARRAY_UNDER_REGION,
		ARRAY_TRACE_LOGIC_MASK_AREA,
		ARRAY_EXTERNAL_INSPECTION_POINT,
		ARRAY_REPAIR_MASK_AREA
	};

	enum EDIT_REGION
	{
		EDIT_NONE,
		EDIT_PANEL,
		EDIT_STRIP,
		EDIT_PIECE,
		EDIT_INSPECTION,
		EDIT_CHILD_INSPECTION,
		EDIT_MPOINT,
		EDIT_SCALEALIGNREGIONPTMODEL,
		EDIT_MASK,
		EDIT_LEADAREA,
		EDIT_FINEAREA,
		EDIT_ROI,
		EDIT_MCAUNITREGION,
		EDIT_MEASUREPOINT,
		EDIT_FIDUCIALMARK,
		EDIT_PTMODELAUTOSKIPAREA,
		EDIT_EXT_AREA,
		EDIT_UNDER_REGION,
		EDIT_COPPER_RESIDUAL_RATE_AREA,
		EDIT_PIECE_SEGMENT_REGION,
		EDIT_TRACE_LOGIC_MASK_AREA,
		EDIT_REPAIR_MASK_AREA,
		SELECTION_MODE
	};

	enum SELECT_REGION
	{
		SELECT_NONE,
		SELECT_PANEL,
		SELECT_STRIP,
		SELECT_PIECE,
		SELECT_INSPECTION,
		SELECT_CHILD_INSPECTION,
		SELECT_MPOINT,
		SELECT_SCALEALIGNREGIONPTMODEL,
		SELECT_SCALEALIGNPOINT,
		SELECT_FIDUCIALMARK,
		SELECT_MASK,		
		SELECT_LEADAREA,
		SELECT_FINEAREA,
		SELECT_MEASUREPOINT,
		SELECT_MCAUNITREGION,
		SELECT_MCAUNITBLOCK,
		SELECT_ROI,
		SELECT_PTMODELAUTOSKIPAREA,
		SELECT_EXT_AREA,
		SELECT_MARKING_POINT,
		SELECT_UNDER_REGION,
		SELECT_COPPER_RESIDUAL_RATE_AREA,
		SELECT_PIECE_SEGMENT_REGION,
		SELECT_TRACE_LOGIC_MASK_AREA,
		SELECT_GAS_EMISSION_AREA_MASK,
		SELECT_EXTERNAL_INSPECTION_POINT,
		SELECT_SRO_PAD_OBJ,
		SELECT_REPAIR_MASK_AREA
	};

	enum EDIT_STATUS
	{		
		EDIT_READY,
		REGION_SELECT,
		ADD_VERTEX,
		REGION_MOVE,
		VERTEX_SELECT
	};

	enum ACTION_STATUS
	{
		ACTION_NONE,
		ACTION_CREATE,
		ACTION_VERTEX_ADD,
		ACTION_VERTEX_DELETE,
		ACTION_TRANSLATE,
		ACTION_MOVE,
		ACTION_TRANSFORMATION,
		ACTION_SELECT,
		ACTION_ARRAY,
		ACTION_REGION_DELETE,		
		ACTION_MIRROR_V,
		ACTION_MIRROR_H,
		ACTION_ROTATE_CW,
		ACTION_ROTATE_180,
		ACTION_ROTATE_CCW,
		ACTION_SCALE,
		ACTION_ADD_INSPECTION_REGION, 
		ACTION_RECONSTITUTE,
		ACTION_MPOINT,
		ACTION_ORIGIN_POINT,
		ACTION_AOI_ALIGN_POINT,
		ACTION_VRS_ALIGN_POINT,
		ACTION_FIDUCIAL_POINT,
		ACTION_PIECE_TOOL_MODE,
		ACTION_LAYER_VIEW,
		ACTION_ADJ_OFFSET,								//// 20160829 Add
		ACTION_RESIZE,									//// 20200629 Add
		ACTION_COPPER_RESIDUAL_RATE_AREA,
		ACTION_PIECE_SEGMENT_REGION,
		ACTION_EXTERNAL_INSPECTION_POINT	,	//// 20200716 Add
		ACTION_SRO_PAD_OBJ,
		ACTION_REPAIR_MASK_AREA
	};

	enum BOUNDARY
	{
		EXTENT,
		PROFILE,
		MANUAL
	};
};
namespace DRAW_TYPE
{
	enum REGION
	{
		PIECE = 16,
		MASK
	};
	enum TYPE
	{
		LINE,
		ARC_CW,
		ARC_CCW,
		POLYGON,
		SURFACE,
		POLYGON_SQ, // Single quadrant arc for RS274X
		POLYGON_MQ, // Multi quadrant arc for RS274X
		FLASH,
		TEXT,
		BARCODE,
		SNR
	};

	enum ATTRIBUTE
	{
		PATTERN,
		THROUGH_HOLE,
		VIA_HOLE,
		LEAD,
		DUMMY,
		VIRTUAL_DRILL,
		FINE_PAD,
		FILLED_VIA,
		GROUND,
		FIDUCIAL,
		ROUTE,
		INSPECTION,
		RESERVE1,
		ASD_DRILL,		
		RESERVE2,		
		NONE
	};

	enum POLARITY
	{
		POSITIVE,
		NEGATIVE
	};

	enum ORIENT
	{
		DEGREE_0 = 0,
		DEGREE_90 = 1,
		DEGREE_180 = 2,
		DEGREE_270 = 3,
		MIRROR_D0 = 4,
		MIRROR_D90 = 5,
		MIRROR_D180 = 6,
		MIRROR_D270 = 7,
		DEGREE_ANY = 8,
		MIRROR_D_ANY = 9
	};

	enum TEXT_VERSION
	{
		PREVIOUS = 0,
		CURRENT = 1
	};
}

namespace FONT_TYPE
{
	enum POLARITY
	{
		POSITIVE,
		NEGATIVE,
	};

	enum SHAPE
	{
		ROUND,
		SQUARE,
	};

	enum MODE
	{
		VERTEX,
		BITMAP,
	};
}
namespace LAYER_TYPE
{
	enum STEP
	{
		PIECE,
		STRIP,
		PANEL
	};

	enum TYPE
	{
		PATTERN = 0,
		THROUGH_HOLE = 1,
		VIA_HOLE = 2,
		FINE_AREA = 3,
		SOLDER_REGIST = 4,
		INSPECTION_AREA = 5,
		MASK = 6,
		MASK_FREE = 7,
		ANOTHER_LAYER_DRILL = 8,	//LIQUID_PHOTO_RESIST= 8,
		VIRTUAL_DRILL = 9,
		ROUTER = 10,
		GROUND = 11,
		FILLED_VIA = 12,
		UNDER_LAYER = 13,
		COVERLAY = 14,
		LEAD = 15,
		AICL = 16,
		NETLIST = 17,
		PROBE_CARD_VIA = 18,
		CAVITY = 19,							//// 20170621 PLP CAVITY LAYER
		CHIP_OUTLINE = 20,				//// 20180314 PLP DIE OUTLINE
		PASSIVATION_PAD = 21,		//// 20180324 PLP PASSIVATION PAD
		SRO_PAD = 22,						//// 20210603 SRO PAD
		REPAIR_MASK_AREA = 23			//// 20210831 Repair Mask Area
	};
	enum POLARITY
	{
		POSITIVE,
		NEGATIVE,
	};
	enum UNIT
	{
		METRIC,
		INCH,
	};
};
namespace REPAIR_TYPE
{
	enum DEFECT
	{
		DEFECT_MAX = 0,
		DEFECT_NONE = 1,
		DEFECT_FINAL_FAIL = 2,
		DEFECT_SKIP_ALARM = 3,
		MAX_NUM_OF_DEFECT = 4
	};
};

namespace CAM_DATA
{
	enum FORMAT 
	{ 
		RS274X = 0,
		RS274D = 1,		// rect zoom
		ODB = 2,
		DXF = 3,
		DPF = 4,
		EXCELLON = 5,
		GDS2 = 6,
		UNKNOWN = 7
	};
};
namespace STANDARD_SYMBOLS
{
	enum NAME
	{
		ROUND = 0,					// 'r'
		SQUARE = 1,					// 's'
		RECTANGLE = 2,				// 're'
		ROUNDED_RECT = 3,			// 'rr'
		CHAMFERED_RECT = 4,			// 'rc'
		OVAL = 5,					// 'ov'
		DIAMOND = 6,				// 'di'
		OCTAGON = 7,				// 'oc'
		DONUT_ROUND = 8,			// 'do'
		DONUT_SQUARE = 9,			// 'ds'
		HOR_HEXAGON = 10,			// 'hh'
		VER_HEXAGON = 11,			// 'hv'
		BUTTERFLY = 12,				// 'br'
		BUTTERFLY_SQ = 13,			// 'bs'
		TRIANGLE = 14,				// 'ti'
		OVAL_HALF = 15,				// 'oh'
		THERMAL_ROUND_ROUND = 16,			// 'tr'
		THERMAL_ROUND_SQ = 17,			// 'ts'
		THERMAL_SQUARE = 18,				// 'st'
		THERMAL_SQ_OPEN = 19,			// 'so'
		THERMAL_SQ_ROUND = 20,			// 'sr'
		THERMAL_RECT = 21,          // 'rt'
		THERMAL_RECT_OPEN = 22,		// 'ro'
		ELLIPSIS = 23,				// 'el'
		MOIRE = 24,					// 'mr'
		HOLE = 25,					// 'ho'
		ETC = 26					// 'us'
	};
}

namespace EQ_STATUS
{
	enum EQ
	{
		INITIALIZING = 1,
		READY = 2,
		DONE = 3,
		IN_PRODUCTION = 4,
		DOWN = 5,
		STOPPED = 6
	};
	enum EQ_CONTROL_STATUS //YSI
	{
		AUTO_OPERATION = 1,
		MANUAL_OPERATION = 2
	};
	enum SIGNAL_TOWER
	{
		LAMP_OFF = 0,
		LAMP_ON = 1,
		LAMP_FLASH = 2
	};
}

namespace EQ_ALARM
{
	enum NAME	
	{
		ESTOP = 1,
		SAFETY_SENSOR = 2,
		POWER_METER_INIT_FAIL = 3,
		POWER_MAPPING_AGAIN = 4,
		ALIGNMENT_FAIL = 5,
		LOT_NAME_DUPLICATE_OR_NOT_FIND = 6,
		TWO_D_CODE_READ_FAIL = 7
	};
}


namespace SEJONG_ALARM
{
	enum NAME
	{
		NO_DEFECT = 1,
		PATTERN_MATCHING_FAIL = 2,
		AUTO_FOCUS_FAIL = 3,
		MASK_REGION_DEFECT = 4,
		CONTINUOUS_ABLATION_FAIL = 5,
		NO_ALIGN_POINT = 6,
		PANEL_ALIGN_FAIL = 7,
		NO_ORIGIN_POINT = 8,
		MAX_PROCESSING_REGION = 9,
		LOT_NAME_MATCHING_FAIL = 10,
		DO_NOT_SELECT_RECIPE = 11,
		DO_NOT_SELECT_THICKNESS = 12,
		DO_NOT_CHECK_LASER_POWER = 13,
		DO_NOT_CHECK_LASER_OFFSET = 14,
		OUT_OF_ROI_DEFECT = 15,
		IMAGE_PATH_NOT_FOUND = 16,
		OUT_OF_MEMORY = 17,
		FAIL_ERT_UPDATE = 18,
		FINAL_DEFECT_FAIL = 19,
		LIGHT_CHANGE = 20,
		FAIL_FIND_AUTO_CD = 21,
		NO_DEFECT_SKIP = 22,
	};
}

namespace SEJONG_ALARM_CLEAR
{
	enum NAME
	{
		NEXT_WORK = 1,
		MANUAL_FLAG = 2,
		SERIAL_END = 3,
		NEXT_AF = 4,
		JOG_MOVE = 5,
		MANUAL_ALIGN = 6,
		AUTO_ALIGN = 7,
		MANUAL_ORIGIN = 8,
		NEXT_OPEN_DEFECT = 9,
	};
}


namespace WORKING_LIST
{
	enum NAME
	{
		OPEN_DEFECT_FILE = 1,
		TWO_D_ERROR_MAP = 2,
		SET_CAMERA_PARAM_SCALE_X = 3,
		SET_CAMERA_PARAM_SCALE_Y = 4,
		SET_CAMERA_PARAM_THETA = 5,
		AUTO_MEAS_AOM = 6,
		MEAS_CAMERA_CALIB = 7,
		MEAS_SCANNER_CORRECTION = 8,
		MEAS_POWER_CALIB = 9,
		MEAS_AUTO_LIGHT = 10,
		LOAD_TWO_D_DATA = 11,
		AUTO_REPAIR = 12,
		MOTION_HOME = 13,
		PANEL_ALIGNMENT = 14,
		AUTO_FIT_MOTION = 15,
		MEAS_CAMERA_RES = 16,
		MEAS_CAMERA_RES_ALIGN = 17,
		CLAMP_WORKING = 18,
		MEAS_THREE_D = 19,
		MEAS_THREE_D_MATCHING = 20,
		LOAD_REVIEW_IMAGE = 21,
		AUTO_FOCUS = 22,
		SET_SW_LIMIT = 23,
		CHECK_LIGHT = 24,
		MEAS_THREE_D_AUTO_SET = 25,
		TEST_MODE = 26
	};
}

#pragma pack(push,1)
///////////////////////////////////////////////////////////////////////////////////////////////
// Draw Object data structure
struct DrawListAPerture
{
	vector <int> nDcode;
	vector <int> nListNum;
};
struct GraphObj{
 	// Constructor.
	// Parameters: see member variables.
	GraphObj()
	{
		dCode = 0;
		dAttrListCode = 0;
		Type.nType = 0;
		Type.nAttr = 0;
		Type.nPolarity = 0;
		Type.nOrient = 0;
		Type.nReserve1 = 0;
		Type.nReserve2 = 0;
		Type.nParentid =0;
		nStPnt = 0;
//		nNumOfCoord = 0;
	}

	union{
		struct TYPE{
			UINT16 nType : 4 ;		// allocation 4 bit, max 16 : Line arc Polygon 
			UINT16 nAttr : 6 ;		// allocation 5 bit, max 64 Drill or Pattern
			UINT16 nPolarity : 1 ;	// allocation 1 bit, Positive or Negative
			UINT16 nOrient : 3 ;	// allocation 3 bit, max 8
			UINT16 nReserve1 : 1 ;	// allocation 1 bit, max 2
			UINT16 nReserve2 : 1 ;	// allocation 1 bit, max 2
			UINT16 nParentid : 16 ;	// allocation 16 bit, max 65535
		};
		TYPE Type;
		UINT nValue;
	};

	UINT dCode;	 // Specifies the Pointer to the Standard Symbol of the Object.
	UINT dAttrListCode;				 // (Specifies the number of vertexes if the object is surface type)
	int nStPnt;		 // Start Point
	DRECT Extent;   // Specifies the minmax area of an Object

};
typedef CArray<GraphObj, GraphObj> CArGraphObj;
typedef struct tagLayerStruct{
	UINT nObject;
	UINT nCoord;
}LAYER_STRUCT, *LPLAYER_STRUCT;
//++++++++++++++++++++++++++++++++++++++++++++++++
// for ODB++ Format
typedef struct tagStandardSymbol{	
	tagStandardSymbol()
	{
		nGlListIndex = -1;
		nSymbolName = STANDARD_SYMBOLS::ROUND;
		Param.clear();
		Extent = DRECT();
	}
	int nGlListIndex;
	STANDARD_SYMBOLS::NAME nSymbolName;
	vector <double> Param;
	DRECT Extent;
}STANDARD_SYMBOL, *LPSTANDARD_SYMBOL;

typedef struct tagSymbolObject{	
	tagSymbolObject()
	{
		nGlListIndex = -1;
		strSymbolName = _T("");
		SymbolObjList.clear();
		Extent = DRECT();
	}
	int nGlListIndex;
	CString strSymbolName;
	CMap <int, int, LPSTANDARD_SYMBOL, LPSTANDARD_SYMBOL> mapStdSymbol;
	vector <GraphObj> SymbolObjList;
	DRECT Extent;
}SYMBOL_OBJ, *LPSYMBOL_OBJ;
typedef CArray <LPSYMBOL_OBJ,LPSYMBOL_OBJ> CpArSymbolObject;

typedef struct tagLayerInform_ODB{
	tagLayerInform_ODB()
	{
		strName.Empty();
		strFilePath.Empty();

		Type = LAYER_TYPE::PATTERN;
		bPolarity = LAYER_TYPE::POSITIVE;
		bUnit = LAYER_TYPE::METRIC;
		Step = LAYER_TYPE::PANEL;

		nFormat = CAM_DATA::ODB;

		fAdjScaleX = 1.0;
		fAdjScaleY = 1.0;
		fAdjOffsetX = 0.0;
		fAdjOffsetY = 0.0;

		bView = TRUE;
		Extent = DRECT();
		Exterior = 0;
		nGlListIndex = 0;
		nGlList90Index = 0;
		nGlListAttrIndex = 0;
		nGlList90AttrIndex = 0;
		nLayerGroupID = 0;

		listObj.clear();
		vecObjCoord.clear();
		mapObjColor.RemoveAll();
		mapStdSymbol.RemoveAll();
	}

	CString strFilePath; 
	CString strName; // fetch layer name from gerber file
	
	CAM_DATA::FORMAT nFormat;

	LAYER_TYPE::TYPE Type;
	LAYER_TYPE::POLARITY  bPolarity;	
	LAYER_TYPE::UNIT bUnit; // Metric Or Inch	
	LAYER_TYPE::STEP Step;

	double fAdjScaleX;	// scaling X by external cam operation
	double fAdjScaleY;	// scaling X by external cam operation
	double fAdjOffsetX;	// translate X by external cam operation
	double fAdjOffsetY;	// translate X by external cam operation

	DRECT Extent;

	BOOL bView;

	int Exterior;
	int nGlListIndex;
	int nGlList90Index;
	int nGlListAttrIndex;
	int nGlList90AttrIndex;
	int nLayerGroupID;

	vector <GraphObj> listObj; 
	vector <DPOINT> vecObjCoord;
	CMap <int,int,COLORREF,COLORREF> mapObjColor;
	CMap <int, int, LPSTANDARD_SYMBOL, LPSTANDARD_SYMBOL> mapStdSymbol;
	
}LAYER_INFORM_ODB, *LPLAYER_INFORM_ODB;
typedef CArray <LPLAYER_INFORM_ODB,LPLAYER_INFORM_ODB> CArLayerInform_ODB;

// The MatrixLayer structure defines the Left-Bottom and Right-Top coordinates of a point.
struct MatrixLayer{
	MatrixLayer(int pRow=0,LAYER_TYPE::POLARITY pPolarity=LAYER_TYPE::POSITIVE)
	{
		Row=pRow;
		Polarity = pPolarity;

		Context.Empty();
		Type.Empty();
		LayerName.Empty();
		
		Start_Name.Empty();
		End_Name.Empty();
		Old_Name.Empty();
		Layer_ID.Empty(); 
	}

	int Row;				// Specifies the row number of a layer.
	CString Context;   // 
	CString Type;		// 
	CString LayerName;	// Specifies the name of a layer.
	LAYER_TYPE::POLARITY Polarity;	// Specifies the polarity of a layer.
	CString Start_Name; // Specifies the start name of a layer. 
	CString End_Name;	// Specifies the end name of a layer.
	CString Old_Name;	// Specifies the old name of a layer.
	CString Layer_ID;	// Specifies the id of a layer.
} ;
typedef CArray<MatrixLayer, MatrixLayer> CArMatrixLayer;

// The StepRepeat structure defines the step & repeat of a stephdr file.
struct StepRepeat{
	StepRepeat(int pCol=0,int pColSR=0,double pAng=0,
		double px=0.0,double py=0.0,double pdX=0.0,double pdY=0.0,
		int pnX=0,int pnY=0,BOOL pbMirror=FALSE, int pGlListIndex = 0, int pGlList90Index = 0)
	{
		Col = pCol;
		ColSR = pColSR;
		Ang = pAng;
		sX = px;
		sY = py;
		dX = pdX;
		dY = pdY;
		nX = pnX;
		nY = pnY;
		bMirror = pbMirror;
		StepName.Empty();

		nGlListIndex = pGlListIndex;
		nGlList90Index = pGlList90Index;
	}
	int Col;  // Specifies the col number of a layer.
	int ColSR;    // Specifies the col number of step repeat.
	double Ang;   // Specifies the angle of Step Repeat. 
	double sX;	// Specifies the x-coordinate of an origin point.
	double sY;	// Specifies the y-coordinate of an origin point.
	double dX;	// Specifies the delta x of step repeat.
	double dY;   // Specifies the delta y of step repeat.
	int nX;   // Specifies the x number of step repeat.
	int nY;   // Specifies the y number of step repeat.
	BOOL bMirror;  // Specifies mirror information of step repeat.
	CString StepName;  // Specifies the step name of step repeat.

	int nGlListIndex;
	int nGlList90Index;
} ;
typedef CArray<StepRepeat, StepRepeat> CArStepRepeat;

//// 20181111 Add
typedef struct tagStepRepeatInfo {
	tagStepRepeatInfo(int pCol = 0)
	{
		nCol = pCol;
		strStepName.Empty();
		vecStepRepeat.clear();
	}
	int nCol;			// Specifies the col number of a layer.	
	CString strStepName;   // Specifies the step name of step repeat.
	vector <StepRepeat>  vecStepRepeat;
}STEP_REPEAT_INFO, *LPSTEP_REPEAT_INFO;
typedef CArray<STEP_REPEAT_INFO, STEP_REPEAT_INFO> CArStepRepeatInfo;
////////////////////////////////////////////////////////////////////////////////////////////////

// The StepHdr structure defines the step header of a Stephdr file.
struct StepHdr{
	StepHdr(double pX_DATUM=0.0,double pY_DATUM=0.0,double pX_ORIGIN=0.0,double pY_ORIGIN=0.0,
		double pTOP_ACTIVE=0.0,double pBOTTOM_ACTIVE=0.0,double pRIGHT_ACTIVE=0.0,double pLEFT_ACTIVE=0.0)
	{
		X_DATUM = pX_DATUM;
		Y_DATUM = pY_DATUM;
		X_ORIGIN = pX_ORIGIN;
		Y_ORIGIN = pY_ORIGIN;
		TOP_ACTIVE = pTOP_ACTIVE;
		BOTTOM_ACTIVE = pBOTTOM_ACTIVE;
		RIGHT_ACTIVE = pRIGHT_ACTIVE;
		LEFT_ACTIVE = pLEFT_ACTIVE;
		ONLINE_DRC_NAME.Empty();
		ONLINE_DRC_MODE.Empty();
		ONLINE_DRC_STAT.Empty();
		ONLINE_NET_MODE.Empty();
		ONLINE_NET_STAT.Empty();
	}  
	double X_DATUM;  // Specifies the X_DATUM of a stephdr file.
	double Y_DATUM;    // Specifies the Y_DATUM of a stephdr file.
	double X_ORIGIN;   // Specifies the X_ORIGIN of a stephdr file.
	double Y_ORIGIN;	// Specifies the Y_ORIGIN of a stephdr file.
	double TOP_ACTIVE;  // Specifies the TOP_ACTIVE of a stephdr file.
	double BOTTOM_ACTIVE;  // Specifies the BOTTOM_ACTIVE of a stephdr file.
	double RIGHT_ACTIVE;  // Specifies the RIGHT_ACTIVE of a stephdr file.
	double LEFT_ACTIVE;  // Specifies the LEFT_ACTIVE of a stephdr file.
	CString ONLINE_DRC_NAME;
	CString ONLINE_DRC_MODE;
	CString ONLINE_DRC_STAT;
	int ONLINE_DRC_TIME;
	int ONLINE_DRC_BEEP_VOL;
	int ONLINE_DRC_BEEP_TONE;
	CString ONLINE_NET_MODE;
	CString ONLINE_NET_STAT;
	int ONLINE_NET_TIME;
	int ONLINE_NET_BEEP_VOL;
	int ONLINE_NET_BEEP_TONE;
} ;
typedef CArray<StepHdr, StepHdr> CArStepHdr;

struct Profile{
	Profile(DRAW_TYPE::POLARITY pPolarity = DRAW_TYPE::POSITIVE)
	{
		bPolarity = pPolarity;
		Extent = DRECT();
		CoordList.clear();
	}
	DRAW_TYPE::POLARITY  bPolarity;
	DRECT Extent;   // Specifies the minmax information of a profile.
	vector <DPOINT> CoordList;
} ;
typedef CArray<Profile, Profile> CArProfile;

typedef struct tagObjAttrInfo{
	CMap <int,int,COLORREF,COLORREF> mapObjColor;
}OBJ_ATTRIBUTE, *LPOBJ_ATTRIBUTE;

// The FontL structure defines the Left-Bottom and Right-Top coordinates of a point.
struct FontL{  
	FontL(int pPnt=0,int pnChar=0,double pxSize=0.0,double pySize=0.0,double poffset=0.0)
	{
		name.Empty();
		Pnt = pPnt;
		nChar = pnChar;
		xSize = pxSize;
		ySize = pySize;
		offset = poffset;
		minmax = DRECT();
	}
	CString name;  // Specifies the name of a font.
	long Pnt;    // Specifies the start Number of a font char.
	long nChar;   // Specifies the number of a character entity.
	double xSize;  // Specifies the x Size of a character.
	double ySize;  // Specifies the y Size of a character.
	double offset;
	DRECT minmax;
};
typedef CArray<FontL, FontL> CArFontL;

// The FontC structure defines the Left-Bottom and Right-Top coordinates of a point.
struct FontC{
	FontC(int  pPnt=0, int  pnObj=0)
	{
		name.Empty();
		Pnt = pPnt;
		nObj = pnObj;
		minmax = DRECT();
	}
    int Pnt;    // Specifies the start Number of a font object list.
    int nObj;   // Specifies the number of a font object list.
	CString name;  // Specifies the name of a font.    
    DRECT minmax;
};
typedef CArray<FontC, FontC> CArFontC;

// The FontObject structure defines the Left-Bottom and Right-Top coordinates of a point.
struct FontObject{
	FontObject(double pWidth=0.0, FONT_TYPE::POLARITY pPolarity = FONT_TYPE::POSITIVE, FONT_TYPE::SHAPE pShape = FONT_TYPE::ROUND)
	{
		pS = tagdPOINT(0.0, 0.0);
		pE = tagdPOINT(0.0, 0.0);	
		Width = pWidth;
		nPolarity = pPolarity;
		nShape = pShape;
	}
	DPOINT pS;  // Specifies the start point of a font Object.
	DPOINT pE;  // Specifies the end point of a font object.
	FONT_TYPE::POLARITY nPolarity;  // 1st bit : Polarity 0: Positive, 1: Negative
	FONT_TYPE::SHAPE nShape;			// 8th bit : Shape 0: Round, 1: Square
	double Width; 
};
typedef CArray<FontObject, FontObject> CArFontObj;

// The TextObject structure defines the Left-Bottom and Right-Top coordinates of a point.
struct TextObject{
	TextObject(int  pPnt=0, double pxSize=0.0,double pySize=0.0,double pWidthFactor=0.0, int pVersion=0)
	{
		Pnt = pPnt;
		txtStr.Empty();
		xSize = pxSize;
		ySize = pySize;
		WidthFactor = pWidthFactor;
		p = tagdPOINT(0.0, 0.0);
		Version = pVersion;
	}
	int  Pnt;    // Specifies the start Number of a Font List.
	int Version;
	double xSize;  // Specifies the x size of a character.
	double ySize;  // Specifies the y size of a character.
	double WidthFactor; // 1= 12 mils, 0.5= 6 mils 
	CString txtStr;   // Specifies the character.
	DPOINT p;  // Specifies the x and y-coordinate of a left bottom point.
};
typedef CArray<TextObject, TextObject> CArTextObj;

// The Barcode Object structure defines the Left-Bottom and Right-Top coordinates of a point.
struct BarcodeObject {
	BarcodeObject()
	{
		fasc = _T('Y');
		cs = _T('N');
		bg = _T('Y');
		astr = _T('Y');
		astr_pos = _T('T');
		w = 0.008;
		h = 0.2;
		tObj = TextObject();
		p = tagdPOINT(0.0, 0.0);
	}
	TCHAR fasc; // Y for full ASCII, N for partial ASCII.
	TCHAR cs; // Y for checksum, N for no checksum.
	TCHAR bg; // Y for inverted background, N for no background.
	TCHAR astr;   // Y for an addition of a text string; N for only the barcode.
	TCHAR astr_pos;   // T for adding the string on top, B for adding the string on the bottom.
	double w;  // Element width.
	double h;  // Barcode height.
	TextObject tObj;		// Specifies the Text Object.
	DPOINT p;  // Specifies the x and y-coordinate of a left bottom point.
};
typedef CArray<BarcodeObject, BarcodeObject> CArBarcodeObj;

//// 20201015 Add
typedef struct tagBarcodInfo {
	tagBarcodInfo()
	{
		nCol = 15;
		vecBarInfo.clear();
	}
	int nCol;
	vector <int> vecBarInfo;
}BARCODE_INFO, *LPBARCODE_INFO;

struct Attribute{
	Attribute()
	{
		strName.Empty();
		strAttr.Empty();
	}
	CString strName;
	CString strAttr;
};
typedef CArray<Attribute, Attribute> CArAttribute;

//// 20201015 Add
typedef struct tagStepAttrlistInfo {
	tagStepAttrlistInfo()
	{
		ArAttribute.RemoveAll();
	}
	CArAttribute ArAttribute;
}STEP_ATTRLIST_INFO, *LPSTEP_ATTRLIST_INFO;
typedef CArray<LPSTEP_ATTRLIST_INFO, LPSTEP_ATTRLIST_INFO> CpArStepAttrlistInfo;

//// 20181111 Add
typedef struct tagFeatureFileSizeInfo {
	tagFeatureFileSizeInfo()
	{
		qwSize = 0;
		strLayerName.Empty();
	}
	unsigned __int64 qwSize;
	CString strLayerName;
}FEATURE_FILE_SIZE_INFO, *LPFEATURE_FILE_SIZE_INFO;

typedef struct tagFeatureFileSizeInfoBySteps {
	tagFeatureFileSizeInfoBySteps()
	{
		nCol = 0;
		strStepName.Empty();
		vecFeatureFileSizeInfo.clear();
	}
	int nCol;
	CString strStepName;
	vector <FEATURE_FILE_SIZE_INFO>  vecFeatureFileSizeInfo;
}FEATURE_FILE_SIZE_INFO_BY_STEPS, *LPFEATURE_FILE_SIZE_INFO_BY_STEPS;
typedef CArray<FEATURE_FILE_SIZE_INFO_BY_STEPS, FEATURE_FILE_SIZE_INFO_BY_STEPS> CArFeatureFileSizeInfoBySteps;

//// 20181113 Shinko Option
typedef struct tagLayerRevisionStepInfo {
	tagLayerRevisionStepInfo()
	{
		bExchange = FALSE;
		nLayerID = 1;
		strOriginStep.Empty();
		strRevisionStep.Empty();
	}
	BOOL bExchange;
	int nLayerID;
	CString strOriginStep;
	CString strRevisionStep;
}LAYER_REVISION_STEP_INFO;

typedef struct tagGasEmissionAreaInfo {
	tagGasEmissionAreaInfo()
	{
		nStepID = 0;
		nLayerID = 0;
		nObjID = -1;
		nSurfaceID = -1;
		dDiameter = 0.0;
		fptCenter = tagdPOINT();
		fptStart = tagdPOINT();
		fptEnd = tagdPOINT();
		nShape = OBJECT_INFO::CIRCLE;
	}
	int nStepID;
	int nLayerID;
	int nObjID;
	int nSurfaceID;
	double dDiameter;
	DPOINT fptCenter;
	DPOINT fptStart;
	DPOINT fptEnd;
	OBJECT_INFO::SHAPE nShape;
	GraphObj gObj;
}GAS_EMISSION_AREA_INFO;
/////////////////////////////////////////////////////////////////////

typedef struct tagMatrixSteps{
	tagMatrixSteps(int pCol=0)
	{
		nCol = pCol;
		strStepName.Empty();
		stepLayerInfo.RemoveAll();
		stepSnRList.clear();
	}
	int nCol;			// Specifies the col number of a layer.	
    CString strStepName;   // Specifies the step name of step repeat.

	StepHdr				stepHeader;
	Profile				stepProfileInfo;
	CArLayerInform_ODB	stepLayerInfo;
	vector <StepRepeat>  stepSnRList;	
}MATRIX_STEPS, *LPMATRIX_STEPS;
typedef CArray<LPMATRIX_STEPS, LPMATRIX_STEPS> CpArMatrixSteps;

typedef struct tagStepExtentInfo{
	tagStepExtentInfo()
	{
		nStepID = 0;
		nStPnt = 0;
		nEdPnt = 0;
		fExtent.left = 999999;
		fExtent.bottom = 999999;
		fExtent.right = -999999;
		fExtent.top = -999999;
		TransformMatrix = Matrix3by3();
	}
	int nStepID;
	int nStPnt;
	int nEdPnt;
	DRECT fExtent;
	Matrix3by3 TransformMatrix;
}STEP_EXTENT_INFO, *LPSTEP_EXTENT_INFO;
typedef CArray<STEP_EXTENT_INFO, STEP_EXTENT_INFO> CArStepsExtentInfo;

union TEMPLATE_KEY{
	float Param[2];
	UINT64 key;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RS274XExcellon File Data structure
typedef struct tagMirrorImage{
	tagMirrorImage()
	{
		nStartObj = 0;
		nEndObj = 0;
		bMirrorX = FALSE;
		bMirrorY = FALSE;
	}
	BOOL bMirrorX;
	BOOL bMirrorY;
	int nStartObj;
	int nEndObj;
}MIRROR_IMAGE, *LPMIRROR_IMAGE;

typedef struct tagAptPrimitive{
	tagAptPrimitive()
	{
		nPriNum = 0;
		fParam.clear();
		minmax = DRECT();
	}
	BYTE nPriNum;
	vector <double> fParam;
	DRECT minmax;
}APERTURE_PRIMITIVE, *LPAPERTURE_PRIMITIVE;

typedef struct tagApertureDef{	
	tagApertureDef()
	{
		nGlListIndex = 0;
		chStdAptType = NULL;
		strAptName.Empty();
		Param.clear();
		minmax = DRECT();
	}
	UINT	nGlListIndex;
	TCHAR	chStdAptType;	// 'C' 'R' 'O' 'P
	CString strAptName;
	vector <APERTURE_PRIMITIVE> Param;
	DRECT minmax;
}APERTURE_DEF, *LPAPERTURE_DEF;

//// 20210908 Add
typedef struct tagReDefineToolSize {
	tagReDefineToolSize()
	{
		nToolNumber = 0;
		dToolSize = 0.0;
	}
	int nToolNumber;
	double dToolSize;
}REDEFINE_TOOL_SIZE, *LPREDEFINE_TOOL_SIZE;

typedef struct tagReDefineLayerToolInfo {
	tagReDefineLayerToolInfo()
	{
		nLayerID = 0;
		vecReDefineToolSize.clear();
	}
	int nLayerID;
	vector <REDEFINE_TOOL_SIZE> vecReDefineToolSize;
}REDEFINE_LAYER_TOOL_INFO, *LPREDEFINE_LAYER_TOOL_INFO;

typedef struct tagLayerInform_RS274X{
	tagLayerInform_RS274X()
	{
		strName.Empty();
		strFilePath.Empty();

		Type = LAYER_TYPE::PATTERN;
		bPolarity = LAYER_TYPE::POSITIVE;
		bUnit = LAYER_TYPE::METRIC;
		Step = LAYER_TYPE::PANEL;
		nFormat = CAM_DATA::RS274X;

		fScaleX = 1.0;
		fScaleY = 1.0;

		fAdjScaleX = 1.0;
		fAdjScaleY = 1.0;
		fAdjOffsetX = 0.0;
		fAdjOffsetY = 0.0;

		bView = TRUE;
		Extent = DRECT();
		Exterior = 0;
		nOrder = 0;
		
		nLayerGroupID = 0;
		vecObjCoord.clear();
		vecObjExtent.clear();
	}

	BOOL bView;
	int Exterior;
	int nLayerGroupID;
	int nOrder;

	CString strFilePath; 
	CString strName; // fetch layer name from gerber file
	
	LAYER_TYPE::TYPE Type;
	LAYER_TYPE::POLARITY  bPolarity;	
	LAYER_TYPE::UNIT bUnit; // Metric Or Inch	
	LAYER_TYPE::STEP Step;
	CAM_DATA::FORMAT nFormat;

	double fScaleX;		// X axis scale factor from gerber file analysis
	double fScaleY;		// Y axis scale factor from gerber file analysis

	double fAdjScaleX;	// scaling X by external cam operation
	double fAdjScaleY;	// scaling X by external cam operation
	double fAdjOffsetX;	// translate X by external cam operation
	double fAdjOffsetY;	// translate X by external cam operation
	
	DRECT Extent;
//	vector <UINT64> vecDrawTemplateList;
	vector <GraphObj> listObj; 
	vector <DPOINT> vecObjCoord;	
	vector <DRECT> vecObjExtent;
	CMap <int,int,COLORREF,COLORREF> mapObjColor;
	CMap <int, int, LPAPERTURE_DEF, LPAPERTURE_DEF> mapAptList;
	
}LAYER_INFORM_RS274X, LAYER_INFORM_EXCELLON, *LPLAYER_INFORM_RS274X, *LPLAYER_INFORM_EXCELLON;
typedef CArray <LPLAYER_INFORM_RS274X,LPLAYER_INFORM_RS274X> CArLayerInform_RS274X;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Excellon File Data structure
typedef CArray <LPLAYER_INFORM_EXCELLON,LPLAYER_INFORM_EXCELLON> CArLayerInform_Excellon;

//// 20181014 Add RS-274X S&R Region Info
typedef struct tagSnRRegionInfo {
	tagSnRRegionInfo()
	{
		nID = 0;
		nLayer = 0;
		nStIndex = 0;
		nEdIndex = 0;
		nNumOfObject = 0;
		nNumOfRegion = 0;
		Extent = tagdRECT();
	}
	int nID;
	int nLayer;
	int nStIndex;
	int nEdIndex;
	int nNumOfObject;
	int nNumOfRegion;
	DRECT Extent;
}SNR_REGION_INFO;

// for Layer Load Job Info
typedef struct tagLoadJobInformation{	
	int nNumOfProperty; // all
	int nObjSize; // gds
	int nFileSize; //all odbX
	COLORREF crColor; // all
	CString strPath; //all odbX
	CString strFormat;//all
	CString strNumOfSelected; //all
	CString strLayerName; //odb
	CString strType; //odb
	CString strContext; //odb
	CString strPolarity; //all
}LOAD_JOB_INFORMATION, *LPLOAD_JOB_INFORMATION;
typedef CArray <LOAD_JOB_INFORMATION,LOAD_JOB_INFORMATION> CArLOAD_JOB_INFORMATION;


// for Picking Object List
typedef struct tagPickingObjectInform{
	tagPickingObjectInform()
	{
		nLayerID = 0;
		nStepID = 0;
		nAngle = 0; 	
		nObjID = 0;
		nTmLevel = 0;
		bMirror = FALSE;
		dX = 0.0;
		dY = 0.0;
		fAdjScaleX = 0.0;
		fAdjScaleY = 0.0;
		fCenterPos = tagdPOINT(0.0, 0.0);
		vecAngle.clear();
		vecMirror.clear();
		vecDrawObjIDList.clear();
	}
	GraphObj gObj;
	int nLayerID;
	int nStepID;
	int nAngle;	
	int nObjID;
	int nTmLevel;
	BOOL bMirror;
	double dX;
	double dY;
	double fAdjScaleX;
	double fAdjScaleY;
	DPOINT  fCenterPos;
	vector <double> vecAngle;
	vector <int>	vecMirror;
	vector <int> vecDrawObjIDList;	
	Matrix3by3 TransformMatrix;
}PICKING_OBJ_INFORM, *LPPICKING_OBJ_INFORM;
typedef CArray <LPPICKING_OBJ_INFORM,LPPICKING_OBJ_INFORM> CArPICKING_OBJ_INFORM;

struct PREVIOUS_PICKING_OBJ_INFO{
	int nStepID;
	int nLayerID;
	int nObjID;
};

typedef struct tagPieceMarkingPoint {
	tagPieceMarkingPoint()
	{
		bSetMarking = FALSE;
		fptMarking = tagdPOINT();
	}
	BOOL bSetMarking;
	DPOINT fptMarking;
}PIECE_MARKING_POINT, *LPPIECE_MARKING_POINT;
//// Region 
typedef struct tagPieceRegion {
	tagPieceRegion(UINT pFlag = 0, UINT pRow = 0, UINT pCol = 0, UINT pGroupID = 0)
	{
		bDummy = FALSE;
		nID = 0;
		nFlag = pFlag;
		nRow = pRow;
		nCol = pCol;
		nGroupID = pGroupID;
		nShape = CAM_WORK::RECTANGULA;
		nMirror = TRANSFORM_DATA::NONE;
		nAngle = TRANSFORM_DATA::NONE;
		//		bSetMarking = FALSE;
		//		fptMarking = tagdPOINT();
		Extent = DRECT();
		CoordList.clear();
	}
	BOOL bDummy;
	int  nID;
	int nFlag;
	int nRow;
	int nCol;
	int nGroupID;
	CAM_WORK::REGION_SHAPE nShape;
	TRANSFORM_DATA::TYPE nMirror;
	TRANSFORM_DATA::TYPE nAngle;
	//	BOOL bSetMarking;										//// 20160808 sch Delete
	//	DPOINT fptMarking;                                       //// 20160808 sch Delete
	DRECT Extent;
	vector <DPOINT> CoordList;
	PIECE_MARKING_POINT MarkingPointList[30];     //// 20160808 Add
}PIECE_REGION, *LPPIECE_REGION;

typedef struct tagStripRegion{
	tagStripRegion(UINT pFlag = 0, UINT pGroupID=0)
	{
		nID = 0;
		nFlag = pFlag;
		nGroupID = pGroupID;
		nShape = CAM_WORK::RECTANGULA;
		nMirror = TRANSFORM_DATA::NONE;
		nAngle = TRANSFORM_DATA::NONE;
		Extent = DRECT();
		CoordList.clear();
		PieceList.clear();
	}
	int  nID;
	int nFlag;
	int nGroupID;
	CAM_WORK::REGION_SHAPE nShape;
	TRANSFORM_DATA::TYPE nMirror;
	TRANSFORM_DATA::TYPE nAngle;
	DRECT Extent;
	vector <DPOINT> CoordList;
	vector <PIECE_REGION> PieceList;
}STRIP_REGION, *LPSTRIP_REGION;
typedef CArray <LPSTRIP_REGION,LPSTRIP_REGION> CArSTRIP_REGION;

typedef struct tagCellRegion{
	tagCellRegion(UINT pId=0)
	{
		nCellSaveId = pId;
		bMpoint[0] = FALSE;
		bMpoint[1] = FALSE;
		Extent = DRECT();
	}
	UINT nCellSaveId;
	BOOL bMpoint[2];
	DRECT Extent;
}CELL_REGION, *LPCELL_REGION;

typedef struct tagINSPECTION_REGION{
	tagINSPECTION_REGION(UINT pFlag = 0)
	{
		nFlag = pFlag;
		Extent = DRECT();
	}
	int nID;
	int nFlag;
	DRECT Extent;
	vector <DPOINT> CoordList;
}INSPECTION_REGION, *LPINSPECTION_REGION;

typedef struct tagInspectionRegionInform{
	tagInspectionRegionInform(UINT pGroupId=0, UINT pID = 0, UINT pX = 0, UINT pY = 0)
	{
		nGroupId = pGroupId;
		nProcessingID = pID;
		nX = pX;
		nY = pY;
		nShape= CAM_WORK::RECTANGULA;
		Extent = DRECT();
		CellList.clear();
		InspRegionList.clear();
	}
	int nGroupId;
	UINT nProcessingID;
	UINT nX;
	UINT nY;
	CAM_WORK::REGION_SHAPE nShape;
	DRECT Extent;
	vector <CELL_REGION> CellList;
	vector <INSPECTION_REGION> InspRegionList;

}INSPECTION_REGION_INFORM, *LPINSPECTION_REGION_INFORM;
typedef CArray <LPINSPECTION_REGION_INFORM,LPINSPECTION_REGION_INFORM> CArINSPECTION_REGION;

typedef struct tagPanelRegion{
	tagPanelRegion()
	{
		Extent = DRECT();
		rectInspectionRegion = DRECT();
		ArStripList.RemoveAll();
		ArInspectionRegionList.RemoveAll();
	}
	DRECT Extent;
	DRECT rectInspectionRegion;
	CArSTRIP_REGION ArStripList;	
	CArINSPECTION_REGION ArInspectionRegionList;
}PANEL_REGION, *LPPANLE_REGION;

typedef struct tagGeneralStepRepeat{
	tagGeneralStepRepeat()
	{
		stPoint = tagdPOINT(0.0, 0.0);
		edPoint = tagdPOINT(0.0, 0.0);
		nX = 0;
		nY = 0;	
		dX = 0.0;
		dY = 0.0;
		nAngle = 0;
		nMask = 0;
		nTarget = -1;
	}	
	DPOINT	stPoint;
	DPOINT	edPoint;
	int		nX;
	int		nY;	
	double	dX;
	double	dY;
	int		nAngle;
	int		nMask;
	int		nTarget;
}GENERAL_STEP_REPEAT, *LPGENERAL_STEP_REPEAT;

typedef struct tagArrayObjecInform{
	tagArrayObjecInform()
	{
		nLayerID = 0;
		nStepID = -1;
		nObjectID = -1;
	}
	int		nLayerID;
	int		nStepID;
	int		nObjectID;
	GraphObj gObj;	
}ARRAY_OBJECT_INFO, *LPARRAY_OBJECT_INFO;

typedef struct tagArrayTargetObjInform {
	tagArrayTargetObjInform()
	{
		bFlag = FALSE;
		nAngle = TRANSFORM_DATA::NONE;
		dX = 0.0;
		dY = 0.0;
		dClickPointX = 0.0;
		dClickPointY = 0.0;
	}
	BOOL    bFlag;
	TRANSFORM_DATA::TYPE nAngle;
	double	dX;
	double	dY;
	double	dClickPointX;
	double	dClickPointY;
	ARRAY_OBJECT_INFO sttObjInfo;
}ARRAY_TARGET_OBJECT_INFO, *LPARRAY_TATGET_OBJECT_INFO;

typedef struct tagMaskInform{
	tagMaskInform()
	{
		nShape = CAM_WORK::RECTANGULA;
		nID = -1;
		nFlag = 0;
		nGroupID = -1;
		CoordList.clear();
	}
	CAM_WORK::REGION_SHAPE	nShape;
	int nID;
	int	nFlag;
	int	nGroupID;
	DRECT  Extent;
	vector <DPOINT> CoordList;
}MASK_INFORM, *LPMASK_INFORM;

typedef struct tagGasEmissionAreaMaskInfo {
	tagGasEmissionAreaMaskInfo()
	{
		nFlag = 0;
		nID = 0;
		nGroupID = 0;
		dDiameter = 0.0;
		fptCenter = tagdPOINT();
		fptStart = tagdPOINT();
		fptEnd = tagdPOINT();
		nShape = OBJECT_INFO::CIRCLE;
	}
	int nFlag;
	int nID;
	int nGroupID;
	double dDiameter;
	DPOINT fptCenter;
	DPOINT fptStart;
	DPOINT fptEnd;
	OBJECT_INFO::SHAPE nShape;
	DRECT  Extent;
}GAS_EMISSION_AREA_MASK_INFO;

typedef struct tagExtAreaInform{
	tagExtAreaInform()
	{
		nFlag = 0;
	}
	int nFlag;
	DRECT  Extent;
}EXT_AREA_INFORM, *LPEXT_AREA_INFORM;

typedef struct tagPropertyAreaInform{
	tagPropertyAreaInform()
	{
		nShape = CAM_WORK::RECTANGULA;
		nID = -1;
		nFlag = 0;
		nGroupID = -1;
		CoordList.clear();
	}
	CAM_WORK::REGION_SHAPE	nShape;
	int nID;
	int	nFlag;
	int	nGroupID;
	DRECT  Extent;
	vector <DPOINT> CoordList;
}PROPERTY_AREA_INFORM, *LPPROPERTY_AREA_INFORM;


struct VirtualPictureBox{
	// Constructor.
	// Parameters: see member variables.
	VirtualPictureBox()
	{
		hParentDC = NULL;
		hDC = NULL;
		nPxImage = 0;
		nPyImage = 0;

		ScaleWidth = 0.0;
		ScaleHeight = 0.0;
		ScaleLeft = 0.0;
		ScaleTop = 0.0;
		
		xSize = 0.0;
		ySize = 0.0;
		xPixel = 0.0;
		yPixel = 0.0;
		
		fbFlag = 0;
		cSet = 0;
		DrawWidth = 0;
		ForeColor = 0;
	}
	HDC hParentDC;
	HDC hDC;
	long nPxImage;
	long nPyImage;
	double ScaleWidth;
	double ScaleHeight;
	double ScaleLeft;
	double ScaleTop ;
	double xSize;
	double ySize;
	double xPixel;
	double yPixel;
	BOOL fbFlag; // 'True(Fore=White, Back=Black),  False(Fore=Black, Back=White)
	int cSet;	//'0:fbFlag에 따라,  1:강제White,  2:강제Black
	long DrawWidth;
	long ForeColor;
};

//// 20180716 sch
typedef struct tagGDSLayerSizeInfo {
	tagGDSLayerSizeInfo()
	{
		nFileSize = 0;
		nObjSize = 0;
	}
	int nFileSize;
	int nObjSize;
} GDS_LAYER_SIZE_INFO;

//////////////////////////////////
typedef struct tagRecentFilesInfo{
	tagRecentFilesInfo()
	{
		strRecentJobName.Empty();
		strRecentMachineModel.Empty();
		nCamDataFormat = CAM_DATA::ODB;

		strModelName.Empty();
		strLayerName.Empty();

		nNumOfLoadFile = 0;
		nTransformCode = 0;
		nTotalNumOfLayer = 1;

		strDataFolderPath.Empty();
		strTGZFileName.Empty();
		nSelectStepID = 0;

		//// 20181122 Add
		sttLayerRevisionStepInfo.bExchange = FALSE;
		sttLayerRevisionStepInfo.nLayerID = -1;
		sttLayerRevisionStepInfo.strOriginStep.Empty();
		sttLayerRevisionStepInfo.strRevisionStep.Empty();
		/////////////////////////////////////////////////////////////

		listGerberPath.RemoveAll();
		listFileName.RemoveAll();
		listStepName.RemoveAll();	
		listFileType.RemoveAll();
		listFileContext.RemoveAll();

		fResolution = 1.5;
		nResolutionIndex = 0;

		listProperty.clear();
		listPolarity.clear();
		listView.clear();
		listScaleX.clear();
		listScaleY.clear();
		listOffsetX.clear();
		listOffsetY.clear();
		listFileFormat.clear();
		listFileSize.clear();
		listbAdd.clear();

		nNumOfGDSLayer = 0;
		listGDSLayerInfo.clear();
	}

	CString		strRecentJobName;
	CString		strRecentMachineModel;
	CAM_DATA::FORMAT nCamDataFormat;
	INSPECTION_MODE::MODE nInspectionMode;				//// 20170802 Add
	
	CString		strModelName;
	CString		strLayerName;

	int			nNumOfLoadFile;
	int			nTransformCode;
	int			nTotalNumOfLayer;
		
	CString		strDataFolderPath;
	CString		strTGZFileName;
	int			nSelectStepID;

	double		fResolution;
	int		nResolutionIndex;

	LAYER_REVISION_STEP_INFO sttLayerRevisionStepInfo;					//// 20181122 Add

	CStringArray listGerberPath;
	CStringArray listFileName;
	CStringArray listStepName;	
	CStringArray listFileType;
	CStringArray listFileContext;
	
	vector <LAYER_TYPE::TYPE>	   listProperty;
	vector <LAYER_TYPE::POLARITY>  listPolarity;
	vector <BOOL>				   listView;
	vector <double>				   listScaleX;
	vector <double>				   listScaleY;
	vector <double>				   listOffsetX;
	vector <double>				   listOffsetY;
	vector <CAM_DATA::FORMAT>	   listFileFormat;
	vector <DWORD>                 listFileSize;
	vector <BOOL>				   listbAdd;

	//// 20180717 GDS Layer Info Add
	int nNumOfGDSLayer;
	vector <GDS_LAYER_SIZE_INFO>	listGDSLayerInfo;
}RECENT_FILES_INFO, *LPRECENT_FILES_INFO;
typedef CArray <LPRECENT_FILES_INFO, LPRECENT_FILES_INFO> CArRECENT_FILES_INFO;

struct EnvironmentCustomize{
	EnvironmentCustomize()
	{
		nDefaultCamDataFormat = CAM_DATA::RS274X;
		bUseFileDialog = FALSE;
	
		strMachineType = _T("PCB");
		bOutputLaserCuttingData = FALSE;
		bUseThicknessOfPanel = FALSE;
		bOutputR2RSpec = FALSE;
		bCameraBinningMode = FALSE;
	
		bSetAutoResolution = FALSE;
		nMinPixelForInspection = 4;

		fArcResolution = 0.0001;
		nDrawMinArcVertex = 2;

		nDrawAdjustLineWidth = 0;
		nAdjDrillDrawFactor = 100;
		nAdjLaserDrillDrawFactor = 100;
		fAdjDrillRadius = 1.0;
		fAdjLaserDrillRadius = 1.0;

		nRatioOfRealLineWidth = 100;
		nRatioOfMinLineWidth = 70;
		nRatioOfMinLineSpace = 70;	
		nMinOverlapPixelSize = 100;
		nMaxPixelSizeOfPatternModel = 384;
		nMaxPixelSizeOfAOIAlignMark = 512;
		fDistanceFactorBtwnHolePattern = 5.0;
		fHoleLandSizeFactor = 2.0;
		fMaxMagFactorOfHoleLandSize = 3.0;
		fRangeOfDuplicateDrill = 5.0;

		nNumberOfCellYAxis = 0;
		nMaxPixelSizeOfCellY = 4000;
		nMinPixelBtwnCellBoundaryAndmPoint = 32;
		nMinCellBoundaryMargin = 16;
		bSetFocusAdjustPosition = FALSE;
		bFiducialMarkInspection = FALSE;
		bOutputPieceRegion = TRUE;
		bOutputStripRegion = FALSE;
		bLoadPreviousSpecData = TRUE;
		bUseExtArea = FALSE;
	
		bOutputJGHoleData = TRUE;
		nMinRadiusOfLargeHole = 38;

		nOuputVirtualDrillOnCellBoundary = TRUE;
		bOutputDrillOnCellBoundary = TRUE;
		bExcludeduplicateDrill = TRUE;
		
		bExcludeDrillOnSpace = TRUE;

		bOutputArcData = TRUE;
		bIncludeOvalToArcData = TRUE;
		nMinPixelSizeOfArcData = 15;

		bExceptLeadLayerOutput = TRUE;
		bAcceptLeadObjWidthinPiece = TRUE;

		bRestrictSRDataOfRegionOuter = 0;

		bOutputExpandCircleImage = FALSE;
		nExpandCirclePlusPixelSize = 1;
		nMaxPixelSizeOfPanel = 15000;
		nMaxPixelSizeOfPiece = 5000;

		bAutoMaskOfPieceOuter = TRUE;
		bOutputMaskLayerNAutoMask = TRUE;
		bOutputMaskImage = FALSE;
	
		bSetLineWidthMeasurement = 0;
		bOutputMeasurementPointImage = TRUE;
		nMaxNumOfMeasurePoint = 100;
		fMLSResolution = 5.0;

		nScanMarginX = 320;
		nScanMarginY = 320;

		bApplayNewSortType = TRUE;
		nStripSortType = 3;
		nPieceSortType = 3;
		nPieceRowColRefPos = 0;

		bUseUnderLayer = FALSE;
		bSetUnderRegion = FALSE;
	}

	CAM_DATA::FORMAT nDefaultCamDataFormat;
	BOOL bUseFileDialog;
	BOOL bOutputLaserCuttingData;
	BOOL bUseThicknessOfPanel;
	BOOL bCameraBinningMode;
	BOOL bOutputR2RSpec;
	BOOL bSetAutoResolution;
	BOOL bFiducialMarkInspection;
	BOOL bSetFocusAdjustPosition;
	BOOL bOutputPieceRegion;
	BOOL bOutputStripRegion;
	BOOL bLoadPreviousSpecData;
	BOOL bUseExtArea;
	BOOL bOutputJGHoleData;
	BOOL bOutputDrillOnCellBoundary;
	BOOL bExcludeduplicateDrill;
	BOOL bExcludeDrillOnSpace;
	BOOL bOutputArcData;
	BOOL bIncludeOvalToArcData;
	BOOL bExceptLeadLayerOutput;
	BOOL bAcceptLeadObjWidthinPiece;
	BOOL bRestrictSRDataOfRegionOuter;
	BOOL bOutputExpandCircleImage;
	BOOL bAutoMaskOfPieceOuter;
	BOOL bOutputMaskLayerNAutoMask;
	BOOL bOutputMaskImage;							//// 20160629 Add
	BOOL bSetLineWidthMeasurement;
	BOOL bOutputMeasurementPointImage;
	BOOL bApplayNewSortType;
		
	BOOL bUseUnderLayer;
	BOOL bSetUnderRegion;							//// 20160812 Add

	int nMinPixelForInspection;
	int nDrawAdjustLineWidth;
	int nAdjDrillDrawFactor;
	int nAdjLaserDrillDrawFactor;
	int nRatioOfRealLineWidth;
	int nRatioOfMinLineWidth;
	int nRatioOfMinLineSpace;	
	int nMinOverlapPixelSize;
	int nMaxPixelSizeOfPatternModel;	
	int nMaxPixelSizeOfAOIAlignMark;
	int nNumberOfCellYAxis;
	int nMaxPixelSizeOfCellY;
	int nMinPixelBtwnCellBoundaryAndmPoint;
	int nMinCellBoundaryMargin;
	int	nMinRadiusOfLargeHole;
	int nOuputVirtualDrillOnCellBoundary;	
	int nMinPixelSizeOfArcData;
	int nExpandCirclePlusPixelSize;
	int nMaxPixelSizeOfPanel;
	int nMaxPixelSizeOfPiece;
	int nMaxNumOfMeasurePoint;
	int nScanMarginX;
	int nScanMarginY;
	int nStripSortType;
	int nPieceSortType;
	int nPieceRowColRefPos;
	int nDrawMinArcVertex;

	float fRangeOfDuplicateDrill;
	float fMLSResolution;
	float fHoleLandSizeFactor;
	float fMaxMagFactorOfHoleLandSize;
	float fDistanceFactorBtwnHolePattern;
	float fArcResolution;
	float fAdjDrillRadius;
	float fAdjLaserDrillRadius;

	CString strMachineType;
};

struct EnvironmentDevice{
	EnvironmentDevice()
	{
		nNumberOfRefBuilder = 0;
		strBuilderIpAddress1.Empty();
		strBuilderIpAddress2.Empty();
		strBuilderIpAddress3.Empty();		
		strBuilderIpAddress4.Empty();		
		strBuilderIpAddress5.Empty();		
		strBuilderIpAddress6.Empty();		
		strBuilderIpAddress7.Empty();		
		strBuilderIpAddress8.Empty();		
		strBuilderIpAddress9.Empty();		
		strBuilderIpAddress10.Empty();

		bUseSpecServer = FALSE;
		bUseDefaultSpecServer = FALSE;
		strSpecServerName.Empty();
		strSpecServerIpAddress.Empty();
		strDefaultSpecServerName.Empty();
		strDefaultSpecServerIpAddress.Empty();
			
		bUseBackupDevice = 0;
		strBackupDeviceIpAddress.Empty();

		bUseFTPServer = 0;
		nDownloadPeriod = 0;
		strFTPServerIpAddress.Empty();
		strFTPLoginName.Empty();
		strFTPLoginPassword.Empty();
			
		bUseDTSServer = 0;
		strDTSServerIpAddress.Empty();
		strDTSMasterCatalog.Empty();
		strDTSMasterAccessID.Empty();
		strDTSMasterPassword.Empty();
		strDTSCatalog = _T("GVISDB");
		strDTSAccessID = _T("root");
		strDTSPassword = _T("My3309");
		strDTSShareFolder.Empty();
		strDTSBizAreaName.Empty();
		strDTSShipType.Empty();
		nDTSStripOutLevel = 100;
		nDTSMaxLayerNumber = 64;
		bUseIpAddressToCamInfoTable = FALSE;					//// 20180322 Add
		bUseMultiModelName = TRUE;								//// 20210830 Add
		nDataBaseType = 1;			// 180517 hsm
		bDTSAutoLogin = FALSE;

		strBackupDeviceDomainName.Empty();
		strFTPServerDomainName.Empty();
		strDTSServerDomainName.Empty();
		strBuilderDomainName1.Empty();
		strBuilderDomainName2.Empty();
		strBuilderDomainName3.Empty();
		strBuilderDomainName4.Empty();
		strBuilderDomainName5.Empty();
		strBuilderDomainName6.Empty();
		strBuilderDomainName7.Empty();
		strBuilderDomainName8.Empty();
		strBuilderDomainName9.Empty();
		strBuilderDomainName10.Empty();

		bConnectRefBuilder[0] = FALSE;
		bConnectRefBuilder[1] = FALSE;
		bConnectRefBuilder[2] = FALSE;
		bConnectRefBuilder[3] = FALSE;
		bConnectRefBuilder[4] = FALSE;
		bConnectRefBuilder[5] = FALSE;
		bConnectRefBuilder[6] = FALSE;
		bConnectRefBuilder[7] = FALSE;
		bConnectRefBuilder[8] = FALSE;
		bConnectRefBuilder[9] = FALSE;
//		bUseDDE = TRUE;
		nREFSwathBufSize = 5;
	

		strCamBuilderFilePath1.Empty();
		strCamBuilderIniName1.Empty();
		strCamBuilderFilePath2.Empty();
		strCamBuilderIniName2.Empty();
		strCamBuilderFilePath3.Empty();
		strCamBuilderIniName3.Empty();
	}
	int  nREFSwathBufSize;
//	BOOL bUseDDE;
	BOOL bUseSpecServer;
	BOOL bUseDefaultSpecServer;				//// 20170611 Add
	BOOL bUseBackupDevice;
	BOOL bUseFTPServer;
	BOOL bUseDTSServer;
	BOOL bConnectRefBuilder[10];
	BOOL bUseLogDB;

	int nNumberOfRefBuilder;
	int nDownloadPeriod;
	CString strCamBuilderFilePath1;
	CString strCamBuilderIniName1;
	CString strCamBuilderFilePath2;
	CString strCamBuilderIniName2;
	CString strCamBuilderFilePath3;
	CString strCamBuilderIniName3;
	CString strBuilderDomainName1;
	CString strBuilderIpAddress1;
	CString strBuilderDomainName2;
	CString strBuilderIpAddress2;
	CString strBuilderDomainName3;
	CString strBuilderIpAddress3;
	CString strBuilderDomainName4;
	CString strBuilderIpAddress4;
	CString strBuilderDomainName5;
	CString strBuilderIpAddress5;
	CString strBuilderDomainName6;
	CString strBuilderIpAddress6;
	CString strBuilderDomainName7;
	CString strBuilderIpAddress7;
	CString strBuilderDomainName8;
	CString strBuilderIpAddress8;
	CString strBuilderDomainName9;
	CString strBuilderIpAddress9;
	CString strBuilderDomainName10;
	CString strBuilderIpAddress10;

	CString strSpecServerName;
	CString strSpecServerIpAddress;
	//// 20170611 Add
	CString strDefaultSpecServerName;
	CString strDefaultSpecServerIpAddress;
	
	CString strBackupDeviceDomainName;
	CString strBackupDeviceIpAddress;
	
	CString strFTPServerDomainName;
	CString strFTPServerIpAddress;
	CString strFTPLoginName;
	CString strFTPLoginPassword;
	
	CString strDTSServerDomainName;
	CString strDTSServerIpAddress;
	CString strDTSMasterCatalog;
	CString strDTSMasterAccessID;
	CString strDTSMasterPassword;
	CString strDTSCatalog;
	CString strDTSAccessID;
	CString strDTSPassword;
	CString strDTSShareFolder;

	CString strDTSBizAreaName;
	CString strDTSShipType;
	int		nDTSStripOutLevel;
	int		nDTSMaxLayerNumber;
	int		nDataBaseType;						// 180517 hsm  1 :MYSQL 0; MSSQL
	BOOL bUseIpAddressToCamInfoTable;				//// 20180322 Add
	BOOL bUseMultiModelName;							//// 20210830 Add
	BOOL	bDTSAutoLogin;
};

struct EnvironmentEdit{
	EnvironmentEdit()
	{
		nPointCenterLineLength = 50;
		nInspectionRegionLineWidth = 1;
		nPanelRegionLineWidth = 1;
		nStripRegionLineWidth = 1;
		nPieceRegionLineWidth = 1;
		
		nSetBoundaryOfRegion = CAM_WORK::MANUAL;
		bIncludeDummyStep;

		bDisplayBackgroundImage = TRUE;
		bFillBackGroundScreen = FALSE;

		fLimitDisplayLineWidth = 5.0;
		fCanvasMargin = 10.0f;
		crFontColor = RGB(255,0,0);
		crFontBackColor = RGB(0,0,0);
		crCursorBackColor = RGB(0,0,0);
		nAutoSaveTimeInterval = 10;

		LangType = LanguageType::ENGLISH;
		nCursorType = 0;
		nCursorSize = 0;
	}
	int nPointCenterLineLength;
	int nInspectionRegionLineWidth;
	int nPanelRegionLineWidth;
	int nStripRegionLineWidth;
	int nPieceRegionLineWidth;	
	int nAutoSaveTimeInterval;
	int nCursorType;
	int nCursorSize;

	CAM_WORK::BOUNDARY  nSetBoundaryOfRegion;
        BOOL bIncludeDummyStep;
	
	BOOL bApplyDrillLayerMirror;
	BOOL bDisplayBackgroundImage;
	BOOL bFillBackGroundScreen;
	COLORREF crFontColor;
	COLORREF crFontBackColor;
	COLORREF crCursorBackColor;
	float fLimitDisplayLineWidth;
	float fCanvasMargin;
	LanguageType::ENUM LangType;
};

struct EnvironmentHW_Req{
	EnvironmentHW_Req()
	{
		
	}
	
};

struct EnvironmentPath{
	EnvironmentPath()
	{
		strSystemFilePath.Empty();
		strMachineInfoFilePath.Empty();
		strNetworkInfoFilePath.Empty();
		strTemplateDataFolderPath.Empty();
		strTemporaryFolderPath = _T("D:\\TempData");
		strLogFileFolder.Empty();
		strUnzipFileFolder = _T("D:\\UnzipData");
		strLanguageFileFolder.Empty();
		strSpecFileFolderName = _T("E:\\Sp-C1i3");
		strReferenceShareFolderName = _T("MasterData");
		strReferenceShareSubFolderName = _T("C1i3Refer");
		strCadImagePath = _T("D:\\MasterData\\CadLinkData3");
		strGerberFilePath = _T("D:\\UnzipData");

		strLaserCuttingDataPath.Empty();
		strCompressionRefShareFolderName.Empty();
		strCompressionRefShareSubFolderName.Empty();
		strCompressionCadImagePath.Empty();

		//// 20170609 Add
		strDefaultSpecFolder.Empty();
		strDefaultRefShareFolder.Empty();
		strDefaultRefShareSubFolder.Empty();
		strDefaultCadImagePath.Empty();
	}
	CString strSystemFilePath;
	CString strMachineInfoFilePath;
	CString strNetworkInfoFilePath;
	CString strTemplateDataFolderPath;
	CString strTemporaryFolderPath;
	CString strLogFileFolder;
	CString strUnzipFileFolder;
	CString strLanguageFileFolder;
	CString strSpecFileFolderName;
	CString strReferenceShareFolderName;
	CString strReferenceShareSubFolderName;
	CString strCadImagePath;
	CString strGerberFilePath;
	CString strLaserCuttingDataPath;
	CString strCompressionRefShareFolderName;
	CString strCompressionRefShareSubFolderName;
	CString strCompressionCadImagePath;

	//// 20170609 Add
	CString strDefaultSpecFolder;
	CString strDefaultRefShareFolder;
	CString strDefaultRefShareSubFolder;
	CString strDefaultCadImagePath;
};

struct EnvironmentStorage{
	EnvironmentStorage()
	{
		nNumberOfIPU = 3;
		nNumberOfStorage = 1;
		nDefaultNumberOfStorage = 1;
		bDivideSaveMode = FALSE;
		bRefDataDuplicateMode = FALSE;
		bDefaultRefDataDuplicateMode = FALSE;
		bDefaultDivideSaveMode = FALSE;

		bUseLocalDrive = FALSE;

		strRefStorage1.Empty();
		strRefStorage2.Empty();
		strRefStorage3.Empty();

		strDefaultRefStorage1.Empty();
		strDefaultRefStorage2.Empty();
		strDefaultRefStorage3.Empty();

		strRefIpAddress1.Empty();
		strRefIpAddress2.Empty();
		strRefIpAddress3.Empty();

		strDefaultRefIpAddress1.Empty();
		strDefaultRefIpAddress2.Empty();
		strDefaultRefIpAddress3.Empty();

		strCompressionRefStorage.Empty();
		strCompressionStorageIpAddr.Empty();
		strCompressionLocalDrive.Empty();

		strMasterStorageList.RemoveAll();
		strDefaultMasterStorageList.RemoveAll();
	}
	BOOL bRefDataDuplicateMode;
	BOOL bDivideSaveMode;
	BOOL bUseLocalDrive;

	BOOL bDefaultRefDataDuplicateMode;
	BOOL bDefaultDivideSaveMode;
	
	int nNumberOfIPU;
	int nNumberOfStorage;
	int nDefaultNumberOfStorage;

	CString strRefStorage1;
	CString strRefStorage2;
	CString strRefStorage3;

	CString strDefaultRefStorage1;
	CString strDefaultRefStorage2;
	CString strDefaultRefStorage3;

	CString strRefIpAddress1;
	CString strRefIpAddress2;
	CString strRefIpAddress3;

	CString strDefaultRefIpAddress1;
	CString strDefaultRefIpAddress2;
	CString strDefaultRefIpAddress3;

	CString strCompressionRefStorage;
	CString strCompressionStorageIpAddr;
	CString strCompressionLocalDrive;

	CStringArray strMasterStorageList;
	CStringArray strDefaultMasterStorageList;
};

struct EnvironmentSystem{
	EnvironmentSystem()
	{
#ifdef _DEBUG
		bUseGPUVbo=TRUE;
#else
		bUseGPUVbo=FALSE;
#endif
		bCamMasterMode = TRUE;
		bSave1BitRawImage = FALSE;
		bDraw1XRawImage = FALSE;
		bHPSProcessingMode = FALSE;
		bCamBuildProcessingMode = FALSE;
		bConCurrentOperationMode = FALSE;
		bRPUGerberDrawMode = FALSE;
		bGerberDataCompressionMode = FALSE;
		bCamDataBinaryMode = FALSE;
		bRefDataCompressionMode = FALSE;
		bUseIpAddressToRefDataPath = FALSE;
		bUseNetworkInfoFromConfigFile = FALSE;

		nRefFormatVersion = 2;
		nNumberOfProcThread = 2;

		fMinCapacityOfTemplateHDD = 1000.0;
		fMinCapacityOfMasterHDD = 2000.0;
		fMonitorSize = 0.0;

		nPixelPrecision = 3;
		nImageDepth = 1;
		nSystemIPIndex = 0;

		strSocketPortID = _T("2000");
		strSystemName.Empty();
		strSystemIPAddress.Empty();
		strCamMasterDomainName.Empty();
		strCamMasterIPAddress.Empty();
		strAspectRatio.Empty();
		strMyIPAddress.Empty();

		vecMonitorAspectRatio.clear();
		vecMonitorSize.clear();
	}
	BOOL bCamMasterMode;
	BOOL bSave1BitRawImage;
	BOOL bDraw1XRawImage;
	BOOL bHPSProcessingMode;
	BOOL bCamBuildProcessingMode;
	BOOL bConCurrentOperationMode;
	BOOL bRPUGerberDrawMode;
	BOOL bGerberDataCompressionMode;
	BOOL bCamDataBinaryMode;
	BOOL bUseGPUVbo;
	BOOL bRefDataCompressionMode;
	BOOL bUseIpAddressToRefDataPath;
	BOOL bUseNetworkInfoFromConfigFile;						//// 20210317

	int	nRefFormatVersion;
	int nNumberOfProcThread;
	int	nPixelPrecision;
	int	nImageDepth;
	int nSystemIPIndex;

	float fMinCapacityOfTemplateHDD;
	float fMinCapacityOfMasterHDD;
	float fMonitorSize;

	CString strSocketPortID;
	CString strSystemName;
	CString strSystemIPAddress;
	CString strCamMasterDomainName;
	CString strCamMasterIPAddress;
	CString strAspectRatio;
	CString strMyIPAddress;
	vector<CString> vecMonitorAspectRatio;
	vector<CString> vecMonitorSize;
};

struct EnvironmentGigaVis{
	EnvironmentGigaVis()
	{
		bMCATest = FALSE;
		bUseROI = FALSE;
		bApplyObjPositionScale = FALSE;
		bUseInverseMask = FALSE;
		bKeepPrevCameraEffectivePixels = FALSE;
		bApplyPieceAlignMode = FALSE;
		bExtractObjectFeaturePoint = FALSE;
		bDisplayAoiMachineEnvirSetWindow = FALSE;
		bMeasure5GAntennaPad = FALSE;
		bExtractRepeatPatternArea = TRUE;
		bApplyPanelExtentAfterExcludeOuterSmallObj = FALSE;
		bCreatePanelImgUseThread = TRUE;
		bAutoSetROIRegionOnVeriMaskDefect = FALSE;
		bMaintainCellSizeWhenSwithingHPStoVPS = FALSE;

		//// 20160922 Feature Region
		bUseFREProcessing = FALSE;
		nFeatureRegionSizeX = 100;
		nFeatureRegionSizeY = 100;
		fFREAngle = 3.0;
		fFRE_Th_Score = 0.1;
		nFREScanIntervalX = 20;
		nFREScanIntervalY = 20;
		nFRELogicNum = 1;
		/////////////////////////////////

		bDebugDrill = FALSE;
		bDebugPtModel = FALSE;
		bDebugRegion = FALSE;
		bOneCellProcessing = FALSE;
		bSaveCellImage_1X = FALSE;
		bSaveInputImages = FALSE;

		bOutputOldPieceFile = TRUE;
		bOutputNewPieceFile = TRUE;
		bCreatePolygonPiece = TRUE;

		bLineTraceLogic = TRUE;
		bSpTraceLogic = TRUE;
		bEdgeTraceLogic = TRUE;
		bPtRLELogic = TRUE;
		bSpRLELogic = TRUE;
		bSPEdgeLogic = FALSE;  // option

		//// 20170426 Cleanup
		bCompareLayer = FALSE;
		bContourizeCamData = TRUE;
		bViewCleanupCamData = TRUE;
		bCleanupSeletedStep = FALSE;
		bCleanupOnlyUnit = TRUE;
		nContourizeMethod = 1;
		nContourizeExportType = 0;		
		nNumOfCleanupThread = 6;
		bClippingMode = TRUE;
		bUseContourizeInspectionResolution = FALSE;
		fContourizeResolution = 1.0;

		bUsePartitionRegionCleanup = FALSE;
		//////////////////////////////////////////////

		bMeasureCopperResidualRate = FALSE;				//// 20170524

		fRegionSortRange = 0.005;

		bOutputRefScanImage = FALSE;
		strRefScanImagePath.Empty();
	}
	BOOL	bMCATest;
	BOOL	bUseROI;
	BOOL	bApplyObjPositionScale;
	BOOL	bUseInverseMask;
	BOOL	bKeepPrevCameraEffectivePixels;
	BOOL bApplyPieceAlignMode;										//// 20170907 Add
	BOOL bExtractObjectFeaturePoint;								//// 20171207 Add
	BOOL bDisplayAoiMachineEnvirSetWindow;					//// 20180102 Add    20211111 Modify : bUseDTSLinkageByAoiType => bDisplayAoiMachineEnvirSetWindow
	BOOL bMeasure5GAntennaPad;									//// 20180713 Add
	BOOL bExtractRepeatPatternArea;									//// 20190611 Add
	BOOL bApplyPanelExtentAfterExcludeOuterSmallObj;			//// 20190604 Add
	BOOL bCreatePanelImgUseThread;								//// 20191120 Add
	BOOL bAutoSetROIRegionOnVeriMaskDefect;					//// 20200818 Add
	BOOL bMaintainCellSizeWhenSwithingHPStoVPS;			//// 20210903 Add

	BOOL	bDebugDrill;
	BOOL	bDebugPtModel;
	BOOL	bDebugRegion;
	BOOL	bOneCellProcessing;
	BOOL	bSaveCellImage_1X;
	BOOL	bSaveInputImages;

	BOOL	bOutputOldPieceFile;
	BOOL	bOutputNewPieceFile;
	BOOL	bCreatePolygonPiece;
	
	BOOL	bLineTraceLogic;     // UI:Line 
	BOOL	bSpTraceLogic;       // UI:Space
	BOOL	bEdgeTraceLogic;     // UI:Edge
	BOOL	bPtRLELogic;         // UI:Pattern area
	BOOL	bSpRLELogic;         // UI:Space area
	BOOL    bSPEdgeLogic;

	//// 20160922 Feature Region
	BOOL	bUseFREProcessing;			
	int		nFeatureRegionSizeX;
	int		nFeatureRegionSizeY;	
	int		nFREScanIntervalX;
	int		nFREScanIntervalY;
	float	fFREAngle;
	float   fFRE_Th_Score;
	int     nFRELogicNum;
	///////////////////////////////

	//// 20170426 Contourize Option
	BOOL	bCompareLayer;
	BOOL	bContourizeCamData;
	BOOL	bViewCleanupCamData;
	BOOL	bCleanupSeletedStep;
	BOOL	bCleanupOnlyUnit;							
	int		nContourizeMethod;							// 0: Image, 1: Vector
	int		nContourizeExportType;	
	int		nNumOfCleanupThread;							//// 20210712
	BOOL	bClippingMode;
	BOOL	bUseContourizeInspectionResolution;
	double	fContourizeResolution;
	BOOL bUsePartitionRegionCleanup;						//// 20180305 Test Option
	////////////////////////////////////////////////////

	BOOL bMeasureCopperResidualRate;					//// 20170524

	float fRegionSortRange;

	BOOL	bOutputRefScanImage;
	CString strRefScanImagePath;
};
struct EnvironmentLGInnotek{
	EnvironmentLGInnotek()
	{
		bApplyITS = FALSE;
		bMeasureCopperResidualRate = FALSE;
		bDrillInspectionInMaskArea = TRUE;
		bRemoveMaskAroundDrillLand = TRUE;
		nMaskRemovalExtensionSize = 2;

		bExtractLWInfoFromCleanupData = TRUE;

		bOutputOldPieceFile = TRUE;
		bOutputNewPieceFile = TRUE;
		bCreatePolygonPiece = TRUE;
	}
	BOOL	bApplyITS;
	BOOL	bMeasureCopperResidualRate;				//// 20170524
	BOOL bDrillInspectionInMaskArea;				//// 20210428
	BOOL bRemoveMaskAroundDrillLand;			//// 20210503
	int nMaskRemovalExtensionSize;					//// 20210503

	BOOL bExtractLWInfoFromCleanupData;			//// 20210805

	BOOL	bOutputOldPieceFile;
	BOOL	bOutputNewPieceFile;
	BOOL	bCreatePolygonPiece;
};
struct EnvironmentSamsung{
	EnvironmentSamsung()
	{
		bSimplificationWork = FALSE;
		bApplySimplificationData = FALSE;
		bAutoSaveSpec = FALSE;
		bLoadLayerName = FALSE;
		bApplyITS = FALSE;
		bOutputNetList = FALSE;
		bAutoMaskOfObjAttr = FALSE;
		bAutoSelectLayer = TRUE;									//// 20170707
		bUseConversionRefPoint = FALSE;
		bSaveCamDataVersion = FALSE;
		bFixedTGZFileNameToModelName = FALSE;			//// 20170707
		bAutoSetInspectionRegion = FALSE;
		bOneUnitInspectionRegion = FALSE;
		bSelectPLPInspectionMode = FALSE;							//// 20170728
		bOutputDummyPieceAsMask = FALSE;						//// 20170907
		bAddLetterOfLayerName = FALSE;
		nPLPInspectionMode = INSPECTION_MODE::NONE;		//// 20170728 Add
		nNetListSortType = 1;
		nSimplificationUnit = LAYER_TYPE::INCH;
		strAddLetterByHMirror.Empty();
		strAddLetterByVMirror.Empty();
		bSetPieceCuttingPoint = FALSE;							//// 20170721
		dCuttingWidth = 0.0;
		dCuttingHeight = 0.0;

		bUseTemporaryJobFile = FALSE;						//// 20181001 Add
		bNotUsePieceToExtractDrillInfo = FALSE;
		bCharacterFormationCheck = FALSE;					//// 20210810 Add
		bExtractCharacterInfoInPiece = TRUE;					//// 20210825 Add
	}
	BOOL	bSimplificationWork;
	BOOL	bApplySimplificationData;
	BOOL	bAutoSaveSpec;
	BOOL	bLoadLayerName;
	BOOL	bApplyITS;
	BOOL	bOutputNetList;
	BOOL	bAutoMaskOfObjAttr;
	BOOL bAutoSelectLayer;									//// 20170707
	BOOL bUseConversionRefPoint;						//// 20170623
	BOOL bSaveCamDataVersion;							//// 20170706
	BOOL bFixedTGZFileNameToModelName;			//// 20170707
	BOOL bAutoSetInspectionRegion;						//// 20170721	
	BOOL bOneUnitInspectionRegion;						//// 20180212
	BOOL bSelectPLPInspectionMode;						//// 20170728	
	BOOL bOutputDummyPieceAsMask;					//// 20170907
	BOOL	bAddLetterOfLayerName;
	INSPECTION_MODE::MODE nPLPInspectionMode;		//// 20170728
	int		nNetListSortType;
	LAYER_TYPE::UNIT nSimplificationUnit;
	CString strAddLetterByHMirror;
	CString strAddLetterByVMirror;

	BOOL bSetPieceCuttingPoint;							//// 20170721
	double dCuttingWidth;
	double dCuttingHeight;

	BOOL bUseTemporaryJobFile;						//// 20181001 Add
	BOOL bNotUsePieceToExtractDrillInfo;			//// 20200410 Add
	BOOL bCharacterFormationCheck;					//// 20210810 Add
	BOOL bExtractCharacterInfoInPiece;				//// 20210825 Add
};
struct EnvironmentSimmtech{
	EnvironmentSimmtech()
	{
		bApplyITS = FALSE;
		bMeasureCopperResidualRate = FALSE;
	}
	BOOL	bApplyITS;
	BOOL	bMeasureCopperResidualRate;				//// 20170524
};
struct EnvironmentKyocera{
	EnvironmentKyocera()
	{
		bUseChildInspectionRegion = FALSE;
		bAutoSetChildInspRegion = FALSE;	
		bOutputStandardArrayPiece = FALSE;
		bCheckWorkMessageFromASMView = FALSE;
		bNotWorkUnregisteredModelFromASM = FALSE;
		nNumOfChildInspRegion = 1;
	}

	BOOL bUseChildInspectionRegion;
	BOOL bAutoSetChildInspRegion;	
	//// 20161130 ADD
	BOOL bOutputStandardArrayPiece;
	BOOL bCheckWorkMessageFromASMView;
	BOOL bNotWorkUnregisteredModelFromASM;
	//////////////////////////////////////////////////////////////////////////
	int  nNumOfChildInspRegion;
};
struct EnvironmentSumitomo{
	EnvironmentSumitomo()
	{
		bSetPieceMarkingPoint = FALSE;
		nNumOfMarkingPointInPiece = 1;
	}

	BOOL bSetPieceMarkingPoint;
	int nNumOfMarkingPointInPiece;
};
struct EnvironmentSoulBrain{
	EnvironmentSoulBrain()
	{
		bUseInverseMask = FALSE;
	}
	BOOL bUseInverseMask;
};
struct EnvironmentSDMassLam{
	EnvironmentSDMassLam()
	{
		bUseInverseMask = FALSE;
	}
	BOOL bUseInverseMask;
};
struct EnvironmentIBIDEN {
	EnvironmentIBIDEN()
	{
		bUseIpAddrToSelectDevice = FALSE;
		bMCATest = FALSE;
		bUseROI = FALSE;
		bSetExternalInspectionPoint = FALSE;

		bSetRepairMaskArea = FALSE;						//// 20210929 Add
		nMaxNumOfRepairMaskArea = 30;				//// 20210929 Add
		bDisplayAoiMachineEnvirSetWindow = FALSE; //// 20211112 Add
	}
	BOOL bUseIpAddrToSelectDevice;
	// 190829 add hsm
	BOOL bMCATest;
	BOOL bUseROI;
	BOOL bSetExternalInspectionPoint;					//// 20200701 Add

	BOOL bSetRepairMaskArea;						//// 20210929 Add
	int nMaxNumOfRepairMaskArea;				//// 20210929 Add
	BOOL bDisplayAoiMachineEnvirSetWindow;  //// 20211112 Add
	/////
};
//// 20170620 Add
struct EnvironmentDaeDuck {
	EnvironmentDaeDuck()
	{
		bApplyITS = FALSE;
		bUseInverseMask = FALSE;
		bAutoProcessingMode = FALSE;
		bStripBaseInspectionRegion = FALSE;
		bCheckMirrorType = FALSE;
		bSkipPreviousProcLayer = TRUE;
		bApplyUnitSize = TRUE;
		bUseBlockAreaInfo = TRUE;
		bAddAoiInfoToModelName = TRUE;
		
		dResolutionLimit = 4.5;

		strApplyPresetSpec = _T("Default.ini");
		strExtremeCamDataPath.Empty();
		strPremierCamDataPath.Empty();
		str30SCamDataPath.Empty();

		strExtremeInfoLabel = _T("EX");
		strPremierInfoLabel = _T("P");
		str30SInfoLabel = _T("");
	}
	BOOL	bApplyITS;
	BOOL	bUseInverseMask;
	BOOL bAutoProcessingMode;
	BOOL bStripBaseInspectionRegion;
	BOOL bCheckMirrorType;
	BOOL bSkipPreviousProcLayer;
	BOOL bApplyUnitSize;										//// 20200616 Add
	BOOL bUseBlockAreaInfo;									//// 20200616 Add
	BOOL bAddAoiInfoToModelName;						//// 20201126 Add

	double dResolutionLimit;

	CString strApplyPresetSpec;
	CString strExtremeCamDataPath;
	CString strPremierCamDataPath;
	CString str30SCamDataPath;

	CString strExtremeInfoLabel;
	CString strPremierInfoLabel;
	CString str30SInfoLabel;
};
//// 20170905 Add
struct EnvironmentYoungPoong {
	EnvironmentYoungPoong()
	{
		bSetPieceSegmentRegion = FALSE;
		bLoadPieceSegmentRegionFromDB = FALSE;
		bAddSubPixelResolutionToLayerName = FALSE;
	}
	BOOL bSetPieceSegmentRegion;
	BOOL bLoadPieceSegmentRegionFromDB;
	BOOL bAddSubPixelResolutionToLayerName;							//// 20180323 Add
};
//// 20180529 Add
struct EnvironmentEastern {
	EnvironmentEastern()
	{
		bApplyITS = FALSE;
		bOutputModelDataInfo = FALSE;
		bMeasureCopperResidualRate = FALSE;
	}
	BOOL	bApplyITS;
	BOOL	bOutputModelDataInfo;
	BOOL	bMeasureCopperResidualRate;				//// 20180615
};
//// 20180717 KCG Option
struct EnvironmentKCG {
	EnvironmentKCG()
	{
		bApplyITS = FALSE;
		bSetInspectionRegionWithoutMargin = FALSE;
	}
	BOOL	bApplyITS;
	BOOL	bSetInspectionRegionWithoutMargin;				
};
//// 20180813 Newway Option
struct EnvironmentNewway {
	EnvironmentNewway()
	{
		bCellEqualDividedProcessingPerRPU = TRUE;
		bDeleteRefDataByCell = TRUE;
		bSaveAsRefDataToLocalDrive = TRUE;
		bUseInverseMask = TRUE;
		bSetRepairOriginPoint = TRUE;
		bSetTraceLogicMaskArea = TRUE;
		bUseRefDataSplittingCompression = TRUE;
		nNumberOfDivisions = 12;
		nRPUResponseWaitTime = 60;
	}
	BOOL	bCellEqualDividedProcessingPerRPU;
	BOOL bDeleteRefDataByCell;							//// 20190714 Add
	BOOL bSaveAsRefDataToLocalDrive;
	BOOL bUseInverseMask;
	BOOL bSetRepairOriginPoint;
	BOOL bSetTraceLogicMaskArea;
	BOOL bUseRefDataSplittingCompression;			//// 20200822 Add
	int nNumberOfDivisions;									//// 20200822 Add
	int nRPUResponseWaitTime;
};
//// 20181005 Add
typedef struct tagMinLineAndSpaceSpecInfo {
	tagMinLineAndSpaceSpecInfo()
	{
		dNominalLineWidth = 10.0;
		dMinLineWidth = 5.0;
		dMinLineSpaceWidth = 5.0;
	}
	double dNominalLineWidth;
	double dMinLineWidth;
	double dMinLineSpaceWidth;
}MIN_LINE_AND_SPACE_SPEC_INFO;

//// 20181005 Add
typedef struct tagLineAndSpaceWidthInfo {
	tagLineAndSpaceWidthInfo()
	{
		dLineWidth = 10.0;
		dSpaceWidth = 5.0;
	}
	double dLineWidth;
	double dSpaceWidth;
}LINE_AND_SPACE_WIDTH_INFO;

struct EnvironmentShinKo {
	EnvironmentShinKo()
	{
		bAutoMaskToGasEmissionArea = TRUE;
		bCircleShapeGasEmissionMask = TRUE;
		bLineShapeGasEmissionMask = TRUE;
		bAutoMaskTextOnUnit = TRUE;
		bAutoSetInspectionRegion = TRUE;
		bUnitBaseInspectionRegion = TRUE;
		bBlockBaseInspectionRegion = FALSE;
		bAutoSetStripRegion = TRUE;
		bAutoSetFocusAdjPosition = TRUE;
		bAutoSelectLayer = TRUE;
		bAutoMirrorStrPcsIndexOfMirroredBtmLayer = TRUE;					//// 20190714
		bLeftRightMirror = TRUE;												//// 20190714
		bSpecifyDrillPropertyToVirtualDrill = TRUE;							//// 20190714
		bExchangeRevisionStep = TRUE;
		bDisplayLineWidthInfo = TRUE;
		bOutputPieceRowColInfo = TRUE;
		bUseProfileInfoForPanelSize = TRUE;
		bUseFixedResolutionByMachine = TRUE;		
		bAutoApplyPanelScale = FALSE;									//// 20191213 Add
		dAdjScaleX = 1.0;
		dAdjScaleY = 1.0;

		nGasEmissionAreaMaskExtendedSize = 1;
		vecMinLineAndSpaceSpecInfo.clear();
	}
	BOOL bAutoMaskToGasEmissionArea;
	BOOL bCircleShapeGasEmissionMask;
	BOOL bLineShapeGasEmissionMask;
	BOOL bAutoMaskTextOnUnit;
	BOOL bAutoSetInspectionRegion;
	BOOL bUnitBaseInspectionRegion;								//// 20191205
	BOOL bBlockBaseInspectionRegion;								//// 20191211
	BOOL bAutoSetStripRegion;
	BOOL bBlockBaseStripRegion;
	BOOL bAutoSetFocusAdjPosition;
	BOOL bAutoSelectLayer;
	BOOL bAutoMirrorStrPcsIndexOfMirroredBtmLayer;				//// 20190714
	BOOL bLeftRightMirror;												//// 20190714
	BOOL bSpecifyDrillPropertyToVirtualDrill;						//// 20190714
	BOOL bExchangeRevisionStep;
	BOOL bDisplayLineWidthInfo;
	BOOL bOutputPieceRowColInfo;						//// 20190326 Add
	BOOL bUseProfileInfoForPanelSize;
	BOOL bUseFixedResolutionByMachine;
	BOOL bAutoApplyPanelScale;									//// 20191213 Add
	double dAdjScaleX;
	double dAdjScaleY;
	
	int nGasEmissionAreaMaskExtendedSize;				//// 20190218 Unit : Pixel

	vector <MIN_LINE_AND_SPACE_SPEC_INFO> vecMinLineAndSpaceSpecInfo;
};

struct EnvironmentUMTC {
	EnvironmentUMTC()
	{
		bMCATest = TRUE;
		bUseROI = TRUE;
		bSetRepairMaskArea = FALSE;						//// 20210929 Add
		nMaxNumOfRepairMaskArea = 30;				//// 20210929 Add
	}
	BOOL	bMCATest;
	BOOL	bUseROI;
	BOOL bSetRepairMaskArea;						//// 20210929 Add
	int nMaxNumOfRepairMaskArea;				//// 20210929 Add
};

struct EnvironmentNanya {
	EnvironmentNanya()
	{
		bUseInverseMask = FALSE;
		bOutputPieceRowColInfo = TRUE;
		bOutputLayerInfo = TRUE;
		bMCATest = FALSE;
		bUseROI = FALSE;
		bCamDataCopyParsingMode = TRUE;
		bSROPadInspection = TRUE;

		bSetRepairMaskArea = FALSE;						//// 20210929 Add
		nMaxNumOfRepairMaskArea = 30;				//// 20210929 Add

		bAutoSetLineWidthSpec = FALSE;
		bDisplayErrorMsgAutoSetLineSpec = FALSE;

		strCompLayerName = _T("CO");
		strSoldLayerName = _T("SO");
	}
	BOOL bUseInverseMask;
	BOOL bOutputPieceRowColInfo;
	BOOL bOutputLayerInfo;
	BOOL	bMCATest;
	BOOL	bUseROI;
	BOOL bCamDataCopyParsingMode;						//// 20201105 Add
	BOOL bSROPadInspection;

	BOOL bSetRepairMaskArea;						//// 20210929 Add
	int nMaxNumOfRepairMaskArea;				//// 20210929 Add

	BOOL bAutoSetLineWidthSpec;			//// 20211018 Add
	BOOL bDisplayErrorMsgAutoSetLineSpec;		//// 20211026

	CString strCompLayerName;
	CString strSoldLayerName;
};

struct EnvironmentLMTEC {
	EnvironmentLMTEC()
	{
		bSaveResizeFactorAsDefaultSpec = FALSE;
		bApplyPanelExtentAfterExcludeOuterSmallObj = FALSE;
		bDisplayPanelResizeInfo = FALSE;
	}
	BOOL	bSaveResizeFactorAsDefaultSpec;
	BOOL bApplyPanelExtentAfterExcludeOuterSmallObj;
	BOOL bDisplayPanelResizeInfo;
};
///////////////////////////////////////////////////////////////////////////////
struct EnvironmentSpecConfig{
	EnvironmentSpecConfig()
	{
		bWidthAverageFilter = TRUE;
		bReMeasureTrace = FALSE;

		nAverageNumberOfPixel = 0;
		nNumOfRLEPrecisionStep = 7;
		nCRICBasePixel = 0;
		nNumOfDefectSizePrecisionStep = 7;
		nJGHSpaceSkeletionPositionPixel = 4;

		nReferenceDataVersion = 4;
		nLargeRLESplitRegionLimit = 400;
		nMinDTSStripOutLevel = 50;
		
		fPixelSizeOfRLEPrecisionStep = 1.0f;
		fSizeOfDefectSizePrecisionStep = 10.0f;
		fMaxSizeOfDefectSizePrecisionStep = 90.0;
		fMinSizeOfDefectSizePrecisionStep = 30.0;
		fMagXNominalLineForRecognizeWidth = 3.0f;
		fMagXNoninalLineForEdgeExclude = 1.5f;
		fMakeMDrillRLE1stParamRadiusMultiplyValue = 1.2;  // 1.05-> 1.2 20170605 ljg mod
		fLineOpenEndWidthCutPixels = 3.5f;
		fSpaceOpenEndWidthCutPixels = 3.5f;
	}
	BOOL bWidthAverageFilter;
	BOOL bReMeasureTrace;

	int nAverageNumberOfPixel;
	int nNumOfRLEPrecisionStep;
	int nCRICBasePixel;
	int nNumOfDefectSizePrecisionStep;	
	int nJGHSpaceSkeletionPositionPixel;

	int nReferenceDataVersion;				//// 20170411 Add	
	int nLargeRLESplitRegionLimit;			//// 20170928 Default : 400 Pixel Add
	int nMinDTSStripOutLevel;

	float fPixelSizeOfRLEPrecisionStep;
	float fSizeOfDefectSizePrecisionStep;
	float fMaxSizeOfDefectSizePrecisionStep;
	float fMinSizeOfDefectSizePrecisionStep;
	float fMagXNominalLineForRecognizeWidth;
	float fMagXNoninalLineForEdgeExclude;
	float fMakeMDrillRLE1stParamRadiusMultiplyValue;
	float fLineOpenEndWidthCutPixels;
	float fSpaceOpenEndWidthCutPixels;
};

typedef struct tagENVIRONMENT_CAM{
	EnvironmentCustomize envCustomize;
	EnvironmentDevice envDevice;
	EnvironmentEdit envEdit;
	EnvironmentHW_Req envHW_Req;
	EnvironmentPath envPath;
	EnvironmentStorage envStorage;
	EnvironmentSystem envSystem;
	EnvironmentSpecConfig envSpecConfig;
	EnvironmentGigaVis envGigaVis;
	EnvironmentKyocera envKyocera;
	EnvironmentSamsung envSamSung;	
	EnvironmentLGInnotek envLGInnotek;
	EnvironmentSimmtech envSimmtech;
	EnvironmentSumitomo envSumitomo;
	EnvironmentSoulBrain envSoulBrain;
	EnvironmentSDMassLam envSDMassLam;					//// 20160923 ADD
	EnvironmentIBIDEN envIBIDEN;								//// 20170209 Add
	EnvironmentDaeDuck envDaeDuck;							//// 20170620 Add
	EnvironmentYoungPoong envYoungPoong;					//// 20170905 Add
	EnvironmentEastern envEastern;								//// 20180529 Add
	EnvironmentKCG envKCG;										//// 20180717 Add
	EnvironmentNewway envNewway;								//// 20180813 Add
	EnvironmentShinKo envShinKo;								//// 20181005 Add
	EnvironmentUMTC envUMTC;									//// 20181215 Add
	EnvironmentNanya envNanya;									//// 20200403 Add
	EnvironmentLMTEC envLMTEC;							//// 20200627 Add
}ENVIRONMENT_CAM, *LPENVIRONMENT_CAM;

struct EnvAOIConfig {
	EnvAOIConfig()
	{
		nPCBLocationDir = 1;
		nRefSavePath = 2;
		dResolutionAOI = 5.0;
		bGTCAOI = FALSE;
		bUseNas = FALSE;
		bUseDTS = FALSE;
		nDefectFileType = DEFECT_FILE_RST;
	}
	CString strMachineName;
	CString strAOIModel;
	CString strSpecPath;
	CString strRefPath;
	CString strNasPath;
	CString arrGTCUnzipPath[10];
	double dResolutionAOI;
	int nPCBLocationDir;
	int nRefSavePath;
	BOOL bGTCAOI;
	BOOL bUseNas;
	BOOL bUseDTS;
	int nDefectFileType;
};

struct SejongLogForm {
	SejongLogForm()
	{
		strOperatorMode = _T(" ");
		strDate = _T(" ");
		strMachineName = _T(" ");
		strRecipeName = _T(" ");
		strModel = _T(" ");
		strLayer = _T(" ");
		strLot = _T(" ");
		strSirialNum = _T(" ");
		strStartTime = _T(" ");
		strEndTime = _T(" ");
		strWorkTime = _T(" ");
		strRepairTime = _T(" ");
		strLightType = _T(" ");
		strAutoFocusTime = _T(" ");
		strAutoLightTime = _T(" ");
		strLightValue = _T(" ");
		strGainValue = _T(" ");
		strResult = _T(" ");
		strCopperThick = _T(" ");
		strImageName = _T(" ");
		nPieceNum = 0;
		nAoiDefectNum = 0;
		dPanelX = 0;
		dPanelY = 0;
		nAORDefectNum = 0;
		dArea = 0;
		nTotalStep = 0;
		nTotaScan = 0;
		nTotalClean = 0;
		strPanelThick = _T(" ");
	}
	//1번 오버레이터 모드
	CString strOperatorMode;
	//Date
	CString strDate;
	//MachineName
	CString strMachineName;
	//Recipe
	CString strRecipeName;
	//Model
	CString strModel;
	//Layer
	CString strLayer;
	//Lot
	CString strLot;
	//PieceNum
	int nPieceNum;
	//SiralNum
	CString strSirialNum;
	//AoiDefectNum 
	int nAoiDefectNum;
	//Panel X
	double dPanelX;
	//Panel Y
	double dPanelY;
	//AOR DefectNum
	int nAORDefectNum;
	//AREA
	double dArea;
	// Start Time
	CString strStartTime;
	// End TIME
	CString strEndTime;
	// Time 종료 - 시작
	CString strWorkTime;
	// 영역 추출 시간 
	CString strDefectViewTime;
	// Repair Time 순수 가공 시간
	CString strRepairTime;
	// Auto Focus Time 
	CString strAutoFocusTime;
	// Result 가공 결과
	CString strResult;
	// Total Step
	int nTotalStep;
	// Total Scan
	int nTotaScan;
	// Total Clean
	int nTotalClean;
	// Panel Tic
	CString strPanelThick;
	// copper tic
	CString strCopperThick;
	//Image Name
	CString strImageName;
	// Auto Light Time 
	CString strAutoLightTime;

	CString strLightValue;
	CString strLightType;
	CString strGainValue;
	
};

struct BusanLogForm {
	BusanLogForm()
	{
		strOperatorName = _T(" ");
		strOperatorID = _T(" ");
		strDate = _T(" ");
		strMachineName = _T(" ");
		strJobName = _T(" ");
		strLayerName = _T(" ");
		strLotName = _T(" ");
		strSirialNum = _T(" ");
		strFrame = _T(" ");
		strDefectStatus = _T(" ");
		strReworkStartTime = _T(" ");
		strReworkEndTime = _T(" ");
		strOverallReworkTime = _T(" ");
		strMaterialName = _T(" ");
		strPenetrationValidationStatus = _T(" ");
		strPenetrationValueCriteria = _T(" ");
		strFinalReworkIterations1 = _T(" ");
		strFinalReworkIterations2 = _T(" ");
		strRepairType = _T(" ");
		strNet0verallReworkTime = _T(" ");
		nAoiDefectNum = 0;
		nAorDefectNum = 0;
		nDefectNumber = 0;
		nReworkIterations = 0;
		dReworkSize = 0;
		dPanelThickness = 0;
		dCopperThickness = 0;
	}
	//1.
	CString strOperatorName;
	//2
	CString strOperatorID;
	//3
	CString strDate;
	//4
	CString strMachineName;
	//5
	CString strJobName;
	//Laye
	CString strLayerName;
	//Lot
	CString strLotName;
	//SiralNum
	CString strSirialNum;
	//AoiDefectNum 
	int nAoiDefectNum;
	//Panel X
	int nAorDefectNum;
	//Panel Y
	double dReworkSize;
	//AOR DefectNum
	CString strDefectStatus;
	//AREA
	CString strReworkStartTime;
	// Start Time
	CString strReworkEndTime;
	// [sec]
	CString strOverallReworkTime;
	// Time 종료 - 시작
	int nReworkIterations;
	// 영역 추출 시간 
	CString strMaterialName;
	// [mirons]
	double dPanelThickness;
	// [mirons]
	double dCopperThickness;
	// Result 가공 결과
	CString strRepairType;
	// [sec]
	CString strNet0verallReworkTime;
	// Total Scan
	CString strFinalReworkIterations1;
	// Total Clean
	CString strPenetrationValidationStatus;
	// Panel Tic
	CString strPenetrationValueCriteria;
	// copper tic
	CString strFinalReworkIterations2;
	//Image Name
	int nDefectNumber;
	//27
	CString strFrame;


};

struct EnvMarkPoint {
	EnvMarkPoint()
	{
		nPieceID = 0;
		nPieceIndex = 0;
		fptMarking.x = 0;
		fptMarking.y = 0;
	}
	int nPieceID;
	int nPieceIndex;
	DPOINT fptMarking;
};

struct TableFlatnessParam{
	TableFlatnessParam()
	{
		fptStartPos.x = 0;
		fptStartPos.y = 0;
		fptEndPos.x = 0;//JCH
		fptEndPos.y = 0;//JCH
		dWidth = 0;
		dHeight = 0;
		dPitchX = 0;
		dPitchY = 0;
		dOffset = 0;
		pFocus = NULL;
		nNumStepX = 0;
		nNumStepY = 0;
		vecMotionPos.clear();
		vecScannerOffset.clear();
	}
	DPOINT fptStartPos;
	DPOINT fptEndPos;//JCH
	double dWidth, dHeight, dPitchX, dPitchY;
	double dOffset;
	double *pFocus;
	int nNumStepX, nNumStepY;
	vector<DPOINT> vecMotionPos;
	vector<DPOINT> vecScannerOffset;
};

struct MEAS_THETA {
	MEAS_THETA()
	{
		dValue = 0.0f;
		dScore = 0.0f;
	}
	float dValue;
	float dScore;
};

struct AUTOMAP_DATA {
	AUTOMAP_DATA()
	{
		strDate.Empty();
		strTime.Empty();
		strMaterial.Format(_T(" "));
		strJob.Empty();
		strLot.Empty();
		strLayer.Empty();
		strSide.Empty();
		strUnit.Empty();
		strMode.Empty();
		strPosX.Empty();
		strPosY.Empty();
		nSerial = 0;
	}
	CString strDate;
	CString strTime;
	CString strMaterial;
	CString strJob;
	CString strLot;
	CString strLayer;
	CString strSide;
	CString strUnit;
	CString strMode;
	CString strPosX;
	CString strPosY;
	CString strVRSCode;
	CString strArea;
	CString strRepairTime;
	CString strRecipe;
	int nSerial;
};

struct EnvRecipeSelectionSub {
	EnvRecipeSelectionSub()
	{
		strSubRouteType = _T("Raster");
		strSubRegionType = _T("Resin");
		bUseSubFocusOffset = TRUE;
		nSubDiffer = 40;
		nSubThreshold = 150;
		nSubTotalScanNum = 2;
		nSubWidth = 1;
		fSubFocusOffsetPer = 0;
		dSubPower = 3;
		dSubIncreaseRegion = 1.0;
		dSubIncreaseRegionV = 1.0;
		dSubIncreaseRegionH = 1.0;
		dSubLimitRegion = 30.0;
		dSubPitch = 1.0;
		dSubRoutePitch = 1.0;
		dSubFocusOffset = 0;
	}
	CString strSubRouteType;
	CString strSubRegionType;
	BOOL bUseSubFocusOffset;
	int nSubDiffer;
	int nSubThreshold;
	int nSubTotalScanNum;
	int nSubWidth;
	float fSubFocusOffsetPer;
	double dSubPower;
	double dSubIncreaseRegion;
	double dSubIncreaseRegionV;
	double dSubIncreaseRegionH;
	double dSubLimitRegion;
	double dSubPitch;
	double dSubRoutePitch;
	double dSubFocusOffset;

};
struct EnvRecipeSelection {
	EnvRecipeSelection()
	{
		strRecipeType = _T("Ablation");
		strRouteType = _T("Raster");
		strRegionType = _T("Resin");
		strThresholdType = _T("Auto");
		nThreshold = 150;
		nThresholdExpand = 0;
		nScanPerTurn = 10;
		nTurnNum = 10;
		nOriTurnNum = 10;
		nTotalScanNum = 4;
		nResetRegion = 0;
		bCheckDefect = FALSE;
		bAutoFocus = FALSE;
		bProtectionMode = FALSE;
		dPower = 3;
		dExpandingPower = 3;
		fFocusOffsetPer = 0;
		dFocusUnitStep = 0;
		fFocusEndPosPer = 0;
		dFocusOffset = 0;
		dFocusEndPos = 0;
		dTermination = 20;
		dIncreaseRegion = 1.0;
		dLimitRegion = 30;
		dPitch = 1.0;
		dRoutePitch = 1.0;
		dIncreaseRegionV = 1.0;
		dIncreaseRegionH = 1.0;
		nClean = 0;
		dRemoverTime = 1.0;
		nTotalCleanSteps = 1;
		nTaperWidth = 1;
	}
	CString strRecipeType;
	CString strRouteType;
	CString strRegionType;
	CString strThresholdType;
	int nThreshold;
	int nThresholdExpand;
	int nScanPerTurn;
	int nTurnNum;
	int nOriTurnNum;
	int nTotalScanNum;
	int nResetRegion;
	int nClean;
	int nTotalCleanSteps;
	int nTaperWidth;
	float fFocusOffsetPer;
	float fFocusEndPosPer;
	BOOL bCheckDefect;
	BOOL bAutoFocus;
	BOOL bProtectionMode;
	double dPower;
	double dExpandingPower;
	double dFocusOffset;
	double dFocusEndPos;
	double dFocusUnitStep;
	double dTermination;
	double dIncreaseRegion;
	double dLimitRegion;
	double dRemoverTime;
	double dPitch;
	double dRoutePitch;
	double dIncreaseRegionV;
	double dIncreaseRegionH;
	EnvRecipeSelectionSub stRecipeSub[MAX_RECIPE_STEPS];
};
struct RECIPE_VER0 {
	RECIPE_VER0()
	{
#if CUSTOMER == IBI_SSR || CUSTOMER == TOPPAN_SSR
		nLightValue = 50;
#endif
		nCustomAngle = 0;
#if CUSTOMER != SHINKO_SSR
		nTotalWorkTime = 600;
#endif
		nTotalSteps = 1;
		nTotalPreSteps = 0;
		nValueAdjustCD = 0;
#if CUSTOMER == SAMSUNG_LCM
		nValueExtractRegionCD = 2;
		nExpanding = 2;
#else
		nValueExtractRegionCD = 1;
		nExpanding = 1;
#endif
		nExpandingH = 0;
		nThreshold = 0;
		nCheckThreshold = 0;
#if CUSTOMER == SHINKO_SSR || CUSTOMER == SAMSUNG_SEJONG || CUSTOMER == SAMSUNG_BUSAN || CUSTOMER == SIMMTECH
		nMaxDefectArea = 40000;
#endif
		fOriThickness = 10;
		dCheckLimitArea = 0;
		dCheckLimitDistance = 1.0;
		dLimitArea = 0;
		dLimitDistance = 2.0;
		dCuttingWidth = 50;
		nDefaultROISize = 70;
		bApplyAutoCD = FALSE;
		bUnderSearch = FALSE;
		fImageLocation = 0;
#if CUSTOMER == SAMSUNG_SEJONG
		bUseAutoCD = TRUE;
#else
		bUseAutoCD = FALSE;
#endif
		strRecipeName = _T("Default");
	}
#if CUSTOMER == IBI_SSR || CUSTOMER == TOPPAN_SSR
	int nLightValue;
#endif
	int nCustomAngle;
#if CUSTOMER != SHINKO_SSR
	int nTotalWorkTime;
#endif
	int nTotalSteps;
	int nTotalPreSteps;
	int nValueAdjustCD;
	int nValueExtractRegionCD;
	int nThreshold;
	int nCheckThreshold;
	int nExpanding;
	int nExpandingH;
	int nRouteOffset;
#if CUSTOMER == SHINKO_SSR || CUSTOMER == SAMSUNG_SEJONG || CUSTOMER == SAMSUNG_BUSAN || CUSTOMER == SIMMTECH
	int nMaxDefectArea;
#endif
	float fOriThickness;
	float fApplyThickness;
	double dCheckLimitArea;
	double dCheckLimitDistance;
	double dLimitArea;
	double dLimitDistance;
	double dCuttingWidth;
	float fImageLocation;
	int nDefaultROISize;
	BOOL bApplyAutoCD;
	BOOL bUnderSearch;
	BOOL bUseAutoCD;
	CString strRecipeName;
	EnvRecipeSelection stRecipe[MAX_RECIPE_STEPS];
	EnvRecipeSelection stRecipePre[MAX_RECIPE_STEPS];
};

struct SEJONG_LOG_FORMAT
{
	int nAlarmCode;
	CTime cTimeStart, cTimeEnd;
};

struct NEW_AUTO_FOCUS_INFO
{
	float fFocusPos;
	float fScore;
};

struct DFF_FORMAT
{
	DFF_FORMAT()
	{
		strLotName.Empty();
		strAOIName.Empty();
		strModelName.Empty();
		strLayerName.Empty();
		strConfirm.Empty();
		strSSRName.Empty();
		strDateAOI.Empty();
		strStartTime.Empty();
		strRepairTime.Empty();
		strArea = _T(" ");
		strRecipe.Empty();
		strPower.Empty();
		strSuccess = _T(" ");
		strPieceX.Empty();
		strPieceY.Empty();
		strPosX.Empty();
		strPosY.Empty();
		strRepair.Empty();
		strRepairArea = _T(" ");
	}
	CString strLotName;
	CString strAOIName;
	CString strModelName;
	CString strLayerName;
	CString strConfirm;
	CString strSSRName;
	CString strDateAOI;
	CString strStartTime;
	CString strRepairTime;
	CString strArea;
	CString strRecipe;
	CString strPower;
	CString strSuccess;
	CString strPieceX;
	CString strPieceY;
	CString strPosX;
	CString strPosY;
	CString strRepair;
	CString strRepairArea;// 20190522 JCH
	DPOINT fptPos;
	int nPieceID;
	int nIndex;
	int nFinalCode;
};

struct USER_ATTR_ITEM {
	USER_ATTR_ITEM()
	{
		bView = TRUE;
		strName = _T("Default");
		nControlID = 0;

	}
	BOOL bView;
	int nControlID;
	CString strName;
	CString strUIName;

};

struct DIALOG_ATTRIBUTE {
	DIALOG_ATTRIBUTE()
	{
		nDataSize = 0;
		pstButton = NULL;
		nDlgID = 0;
	}
	USER_ATTR_ITEM *pstButton;
	int nDataSize;
	int nDlgID;
	CString strName;
};
#define MAX_DLG_SIZE 100
struct USER_ATTRIBUTE {
	USER_ATTRIBUTE()
	{
		nDlgSize = 0;
	}
	DIALOG_ATTRIBUTE stDlgAttr[MAX_DLG_SIZE];
	int nDlgSize;
};
#define IDC_PROPERTY_GRID               101
typedef struct stRTC5Param
{
	UINT	  nLaserMode, nLaserControl;
	UINT      nStandbyHalfPeriod;	//  100 us [1/8 us]
	UINT      nStandbyPulseWidth;		//    0 us [1/8 us]
	UINT      nLaserHalfPeriod;		// 12.5 us [1/64 us] -> 40 KHz
	UINT      nLaserPulseWidth;		// 6.25 us [1/64 us]
	UINT      nLaserOffDelay;     //  100 us [1 us]
	UINT      nJumpDelay;        //  250 us [10 us]
	UINT      nMarkDelay;        //  100 us [10 us]
	UINT      nPolygonDelay;      //   50 us [10 us]
	UINT	  nQswDelay;
	UINT	  nFirstPulseKiller;
	long      nLaserOnDelay;      //  100 us [1 us]
	double    dScanArea;
	double    dMarkParam[9][11];
	double    dPitch;
	double    dRoutePitch;
	double	  dMarkingDelayMs;
	double    dLaserPulseFreqency;
	double    dumScale; 	// [um/Bit]
	double    dCameraResolutionX, dCameraResolutionY;
	double    dAlignCameraResolutionX, dAlignCameraResolutionY;
	double    dCameraOffsetX, dCameraOffsetY;
	double    dCameraOffsetRefPtX, dCameraOffsetRefPtY;
	double	  dCameraOffsetRange;
	CString   strImportPath; //#define RTC5_PROG_PATH	"C:\\LcmSet\\Rtc5Import\\"
	CString	  strCorrectionFilePath;//#define RTC5_CT_PATH	"C:\\LcmSet\\CorrectionData.ct5"
	CString	  strDataFilePath;
	CString	  strOriFilePath;
}RTC5Param;
struct IOInfo {
	IOInfo()
	{
		nID = 0;
		strName.Empty();
	}
	CString strName;
	int nID;
};
struct CorrectionParam{
	CorrectionParam()
	{
		nPosSize = 3;
		dGap = 100.0;
		dOffset = 0.0;
	}
	int nPosSize;
	double dGap;
	double dOffset;
};
struct ScannerOffsetParam {
	ScannerOffsetParam()
	{
		nThres = 60;
		dMarkDelayMs = 1000;
	}
	int nThres;
	double dMarkDelayMs;
};
struct CameraCalibParam {
	CameraCalibParam()
	{
		nThres[0] = 128;
		nThres[1] = 128;
		nLightValue[0] = 50;
		nLightValue[1] = 50;
		nLightValue[2] = 50;
	}
	int nLightValue[3];
	int nThres[2];
};

struct DOT_POS 
{
	DOT_POS()
	{
		dPosX = 0;
		dPosY = 0;
	}
	double 	dPosX;
	double 	dPosY;
};

struct MASTER_GLASS_XY
{
	MASTER_GLASS_XY()
	{
		nTotalPointX = 0;
		nTotalPointY = 0;
		dDotPiSize = 0;
		dOrgPosX = 0;		// 기계상의 비젼 위치.
		dOrgPosY = 0;		// 기계상의 비젼 위치.
		dPitchX = 0;
		dPitchY = 0;
	}
	int   	nTotalPointX;
	int   	nTotalPointY;
	double 	dDotPiSize;
	double 	dOrgPosX;		// 기계상의 비젼 위치.
	double 	dOrgPosY;		// 기계상의 비젼 위치.
	double 	dPitchX;
	double 	dPitchY;
	DOT_POS	Dot[3500]; // 20mm 간격으로 최큱EMaster Glass Size : root(1000) = 31 * 31 = 620mm * 620mm
};

struct WORK_TABLE_XY
{
	WORK_TABLE_XY()
	{
		nTotalPointX = 0;
		nTotalPointY = 0;
		dDotPiSize = 0;
		nOrgPosCol = 0;		// Dumy와 Real 값의 구분 위치. ( 0 ~ )
		nOrgPosRow = 0;		// Dumy와 Real 값의 구분 위치. ( 0 ~ )
		dPitchX = 0;
		dPitchY = 0;
	}
	int   	nTotalPointX;
	int   	nTotalPointY;
	double 	dDotPiSize;
	int 	nOrgPosCol;		// Dumy와 Real 값의 구분 위치. ( 0 ~ )
	int  	nOrgPosRow;		// Dumy와 Real 값의 구분 위치. ( 0 ~ )
	double 	dPitchX;
	double 	dPitchY;
	DOT_POS	Dot[5000]; // 20mm 간격으로 최큱EWork Table Size : root(1000) = 54 * 54 =  1080mm * 1080mm 
};

#define CIRCLE_LEFT		0
#define CIRCLE_RIGHT	1
#define CIRCLE_CENTER	2
#define CIRCLE_TOP		3
#define CIRCLE_BOTTOM	4

struct GENERAL_SPEC{
	GENERAL_SPEC()
	{
		bNotUsingPTModel = FALSE;
		bAutoGeneratePTModel = TRUE;
		bExcluedPTModelOnMaskArea = FALSE;
		bSearchMODEdgePriority = TRUE;
		bSearchMODBlobPriority = TRUE;
		bSearchMODEdge45Priority = TRUE;
		bSearchMODEdge225Priority = TRUE;
		bCheckOnly1DirPattern	= TRUE;
		bSearchMODMassedPatternPriority = TRUE;
		bApplyLargePtModel = FALSE;
		bMeshPatternModel = FALSE;
		bThinPatternMergingForAutoPTModel = FALSE;
		bTinyPatternOpeningForAutoPTModel = FALSE;
		bCheckSelfPtModelShrinkMode = FALSE;
		bMakePtModelWithFillHole = FALSE;
		bSrchPtModelUsingOpenEnd = FALSE;
		bCheckUniqueModForJCnOE = FALSE;
		bSrchPtModelUsingTinyFeature = FALSE;
		bUseScaleAlignRegion = FALSE;
		bScaleAlignRegionWidth = FALSE;
		bScaleAlignRegionHeight = FALSE;
		bSetGlobalScaleAlignPoint = FALSE;
		bAlignPointForAOI = FALSE;
		bAlignPointForVRS = FALSE;
		bAutoResolutionForVrsAlign = FALSE;	

		bUseClippingMode = FALSE;
		bUseManualAlignPoint = FALSE;
		bMeshJunctionPriority = TRUE;

		nPixelSizeOfVrsAlignObj = 512;

		nPtModelLimitMaxSize = 512;
		nPtModelLimitMaxSizeHole = 576;
		nPtModelLimitMinSize = 25;
		nPtModelLimitMinSizeHole = 25;
		nPtModelSizeOfJC_OE = 64;

		nNumberOfPTModel = 2;	  
		nPtModelPatternGrayClosingIteration = 10;
		nDistOfSimilarPatternMerge = 150;
		fPixelIntervalBtwTwoPtModel = 2000;		// Resolution 2.5um
		fPtModelAutoSearchIntervalRatio = 0.5;

		strModelName.Empty();
		strLayerName.Empty();
		strSharedFolder.Empty();
		strReferenceStorage.Empty();

		fResolution = 5.0;
		fOverlapSize = 1.0;
		
		fWidthOfNominalLine = 10.0;
		fMinLineWidth = 5.0;
		fMinLineSpace = 5.0;
		fWidthOfRealLine = 10.0;
		fThicknessOfPanel = 0.0;

		fTinyFeaturePitch = 1.0;

		nPixelsOfCamera = 0;
		nPixelSizeOfPatternModel = 256;
		nFindOptionOfAOIAlignPoint = 1;
		nNumberOfAOIAlignPoint = 2;
		nNumberOfVRSAlignPoint = 2;
		nPixelSizeOfAOIAlignPoint = 384;
	}		
	BOOL bNotUsingPTModel;
	BOOL bAutoGeneratePTModel;
	BOOL bExcluedPTModelOnMaskArea;
	BOOL bSearchMODEdgePriority;
	BOOL bSearchMODBlobPriority;
	BOOL bSearchMODEdge45Priority;
	BOOL bSearchMODEdge225Priority;
	BOOL bCheckOnly1DirPattern;  // 160520 add hsm
	BOOL bSearchMODMassedPatternPriority;
	BOOL bApplyLargePtModel;
	BOOL bMeshPatternModel;
	BOOL bThinPatternMergingForAutoPTModel;
	BOOL bTinyPatternOpeningForAutoPTModel;
	BOOL bCheckSelfPtModelShrinkMode;			//// 20160125 Delete
	BOOL bMakePtModelWithFillHole;
	BOOL bSrchPtModelUsingOpenEnd;
	BOOL bCheckUniqueModForJCnOE;
	BOOL bSrchPtModelUsingTinyFeature;

	BOOL bUseScaleAlignRegion;
	BOOL bScaleAlignRegionWidth;
	BOOL bScaleAlignRegionHeight;
	BOOL bSetGlobalScaleAlignPoint;
	BOOL bAlignPointForAOI;
	BOOL bAlignPointForVRS;
	BOOL bAutoResolutionForVrsAlign;	

	BOOL bUseClippingMode;
	BOOL bUseManualAlignPoint;

	BOOL bMeshJunctionPriority;

	int	  nPixelSizeOfVrsAlignObj;
	int	  nPixelsOfCamera;
	int	  nPixelSizeOfPatternModel;
	int  nFindOptionOfAOIAlignPoint;
	int	  nNumberOfAOIAlignPoint;
	int  nNumberOfVRSAlignPoint;
	int   nPixelSizeOfAOIAlignPoint;
	
	int  nNumberOfPTModel;	  
	int nPtModelPatternGrayClosingIteration;
	int nDistOfSimilarPatternMerge;					//// 20190312 Add

	int nPtModelLimitMaxSize;
	int nPtModelLimitMaxSizeHole;
	int nPtModelLimitMinSize;
	int nPtModelLimitMinSizeHole;
	int nPtModelSizeOfJC_OE;
	double fResolution;
	double fOverlapSize;	

	float fWidthOfNominalLine;
	float fMinLineWidth;
	float fMinLineSpace;
	float fWidthOfRealLine;
	float fThicknessOfPanel;
	
	float fPtModelAutoSearchIntervalRatio;
	float fPixelIntervalBtwTwoPtModel;
	float fTinyFeaturePitch;

	CString strModelName;
	CString strLayerName;
	CString strSharedFolder;
	CString strReferenceStorage;
};

struct BUILD_SPEC{
	BUILD_SPEC()
	{
		bCheckAR = TRUE;
		bCheckCS = FALSE;
		fARHighF = 500.0;
		fARLowF = 90.0;
		fCSHighF = 500.0;
		fCSLowF = 10.0;

		bCheckAutoAdjust = TRUE;
		bOnTHF = FALSE;
	
		bAutoMaskOnCrossShield = FALSE;
		bCrossShieldPositiveObj = FALSE;
		bExcludeMPointOnCrossShield = FALSE;
		bOutputCrossShieldAsMask = FALSE;							//// 20170807 Add
		nWidthOfCrossShield = 0;
		nHeightOfCrossShield = 0;
		nCrossShieldShape = 2;
		nCrossShieldDilate = 1;
		nCrossShieldNoiseFilter = 2;
		fCrossShieldMaskCompactness = 1.17;
		fPadAreaLowF = 50.0;

		fHoleAreaLowF = 50.0;
		fHoleAreaHighF = 1000.0;

		fIslandHighF = 500.0;
		fVoidHighF = 500.0;

		bUseLegacySeparationSpec = FALSE;					//// 20170910 Add

		fSmallBlobRLEExcludeEdge = 2.0f;
		fSmallBlobSpRLEExcludeEdge = 2.0f;
		fSmallPatternRLEExcludeEdge = 4.0f;
		fPatternRLEExcludeEdge = 4.0f;
		fSpaceRLEExcludeEdge = 4.0f;       
		fSmallSpaceRLEExcludeEdge = 4.0f;
		fMDrillLandRLEExcludeEdge = 4.0f;	
		fLDrillLandRLEExcludeEdge = 4.0f;
		fPadTipRLEExcludeEdge = 4.0f;
		fAICLRLEExcludeEdge = 4.0f;
		fPadTipRLEExcludeEdge = 4.0f;
		fFinePatternRLEExcludeEdge = 4.0f;
/*	//// 2018042 Delete
//		fCavityMaskExpandSize = 15.0;			// 20170709 PLP Cavity Mask Expand Pixel Size
//		fCavityRLEExcludeEdge = 10.0f;			// 20170707 PLP Cavity RLE
//		fDieRLEExcludeEdge = 10.0f;				 // 20170707 PLP Cavity RLE
//		fPassivationPadRLEExcludeEdge = 10.0f;				 // 20170707 PLP Cavity RLE
*/
		strSmallBlobRLEExcludeEdge = _T("VeryHigh");
		strSmallBlobSpRLEExcludeEdge = _T("VeryHigh");
		strPrecisionOfSmallPattern = _T("Normal");
		strPrecisionOfPattern = _T("Normal");
		strPrecisionOfSpace = _T("Normal");		
		strPrecisionOfARLand = _T("Normal");		
		strPrecisionOfViaLand = _T("Normal");
		strPrecisionOfPadTip = _T("Normal");
		strPrecisionOfAICLRLEEdge = _T("Normal");
		strPrecisionOfSmallSpace = _T("Normal");
		strPrecisionOfFinePattern = _T("Normal");
/*	//// 2018042 Delete
//		strPrecisionOfCavity = _T("Normal");
//		strPrecisionOfDie = _T("Normal");
//		strPrecisionOfPassivationPad = _T("Normal");;			//// 20180327 PLP Passivation Pad RLE
*/
		fCRICPatternOffset = 0.0;
		fCRICSpaceOffset = 0.0;

		// Old Spec 
//		strPrecisionOfFinePattern = _T("Normal");
//		strPrecisionOfSRPad = _T("Normal");		
		////////////////////////////////////////

		fHoleRegistrationToleranceSize = 60.0f;

		bSmallBlobLogic = TRUE;
		fSmallBlobMaxSize = 20.0f;
		fSmallBlobCompactness = 1.5f;     // 20160408 add
		fPatRLECompactness = 1.5f;        // 20160408 add
		fSpaceRLECompactness = 1.5f;      // 20160408 add

		nImageNoiseFilter = 2;
		nEdgeDetectionType = 0;			//// 20181109 Add
		fAICLShrinkSize = 8.0f;
		fAICLExpandSize = 7.0f;
		bCompareOfCADRefImage = FALSE;
		bInspectionOfGroundOpenCheckPass = FALSE;
		bRemoveChessPatternTrace = FALSE;
		bBoundaryTrace = FALSE;
		bSpecialUserDefineSRMode = FALSE;
		bBeforeImageProcedure = TRUE;
		bExcludeEdgeSpire = FALSE;		
		bRoundingEffect = FALSE;
		bExcludeSpireArea = FALSE;
		bJuncExtention	= FALSE;
		bImprovedTinyObjAccuracy = FALSE;
		bBlankCellSkip = FALSE;
		bUseEdgeExcludeLineWidth = FALSE;
		bDRCViolationMask = FALSE;
		bSpaceTraceSpirePointMask = FALSE;
		fSpaceTraceSpirePointMaskSize = 1.5f;    // 20201103 rename fAutoShortDistanceMaskSize to fSpaceTraceSpirePointMaskSize by ljg

		nDeviationOfSRGold = 50;
		nSizeOfWindowBoundary = 50;
		nTinyObjSplitDiameterPixelSize = 8;
		fDistanceBtwnHoleAndPattern = 25.0;		
		
		nSpireConnectNum = 3;
		nSpireDilateIteration = 2;
		nAreaInspSpireValleyExtNum = 2;
	//	nExcludeSmallSpireSize = 20;
		nSpaceRLESizeLimit = 1000;
		nPatternRLESizeLimit = 1000;
		nRoundEffectIteration = 2;
		nDRCViolationMaskExpand	= 3;

		nEdgeExcludeLineWidthPixel = 15;
		strEdgeExcludeLineWidthAccuracy = _T("NORMAL");
		strEdgeExcludeLineWidthSpeed = _T("NORMAL");		
	}
	BOOL bAutoMaskOnCrossShield;	
	BOOL bCrossShieldPositiveObj;
	BOOL bExcludeMPointOnCrossShield;
	BOOL bOutputCrossShieldAsMask;				//// 20170807 Add 
	BOOL bCompareOfCADRefImage;
	BOOL bInspectionOfGroundOpenCheckPass;
	BOOL bRemoveChessPatternTrace;
	BOOL bBoundaryTrace;
	BOOL bSpecialUserDefineSRMode;
	BOOL bBeforeImageProcedure;
	BOOL bExcludeEdgeSpire;
	BOOL bCheckAR;
	BOOL bCheckCS;
	BOOL bCheckAutoAdjust;
	BOOL bOnTHF;	
	BOOL bRoundingEffect;
	BOOL bExcludeSpireArea;
	BOOL bJuncExtention;
	BOOL bImprovedTinyObjAccuracy;	//// 20200822 Add
	BOOL bBlankCellSkip;						//// 20160628 Add 
	BOOL bUseEdgeExcludeLineWidth;
	BOOL bDRCViolationMask;
	BOOL bSpaceTraceSpirePointMask;    // 20201103 rename bAutoShortDistanceMask to bSpaceTraceSpirePointMask by ljg
	
	int nCrossShieldNoiseFilter;
	int nImageNoiseFilter;
	int nEdgeDetectionType;						//// 20181109 Add
	float fHoleRegistrationToleranceSize;

	BOOL bSmallBlobLogic;			// UI:Small area
	float fSmallBlobMaxSize;
	float fSmallBlobCompactness;     // 20160408 add
	float fPatRLECompactness;        // 20160408 add
	float fSpaceRLECompactness;      // 20160408 add
	
	int nDeviationOfSRGold;
	int nSizeOfWindowBoundary;
	int nTinyObjSplitDiameterPixelSize;					//// 20181126 Add Pixel
	
	int  nWidthOfCrossShield;
	int  nHeightOfCrossShield;
	int  nCrossShieldShape;
	int  nCrossShieldDilate;

	int nSpireConnectNum;				//// 20161013 
	int nSpireDilateIteration;
	int	nAreaInspSpireValleyExtNum;		//// 20170102
//	int nExcludeSmallSpireSize;
	int nSpaceRLESizeLimit;
	int nPatternRLESizeLimit;
	int nRoundEffectIteration;
	int nDRCViolationMaskExpand;
	int nEdgeExcludeLineWidthPixel;

//	float fCavityMaskExpandSize;							//// 20170709 PLP Cavity Mask Expand Size   -> 20170804 Pixel->float		20180402 Delete

	float fCRICPatternOffset;
	float fCRICSpaceOffset;
	float fAICLShrinkSize;
	float fAICLExpandSize;
	float fDistanceBtwnHoleAndPattern;	
	float fCrossShieldMaskCompactness;
	float fARHighF;
	float fARLowF;
	float fCSHighF;
	float fCSLowF;	
	float fPadAreaLowF;
	float fHoleAreaLowF;
	float fHoleAreaHighF;
	float fIslandHighF;
	float fVoidHighF;

	BOOL bUseLegacySeparationSpec;							//// 20170910 Add

	// 20170112 total RLE precision  number = 11
	//          AOI RLE use  = 8
	float fSmallPatternRLEExcludeEdge;   // PAD
	float fPatternRLEExcludeEdge;        // LPAD  
	float fSpaceRLEExcludeEdge;          // SPACEEXT
	float fSmallSpaceRLEExcludeEdge;     // SPACE
	float fMDrillLandRLEExcludeEdge;	 // ARland
	float fLDrillLandRLEExcludeEdge;     // CO2Land
	float fFinePatternRLEExcludeEdge;    // PadFine
	float fPadTipRLEExcludeEdge;         // PadTip
	float fAICLRLEExcludeEdge;           // Not yet use
	float fSmallBlobRLEExcludeEdge;      // Only CAM use, AOI need not
	float fSmallBlobSpRLEExcludeEdge;    // Only CAM use, AOI need not

/*	//// 2018042 Delete
//	float fCavityRLEExcludeEdge;				// 20170707 PLP Cavity RLE
//	float fDieRLEExcludeEdge;					 // 20170707 PLP Cavity RLE
//	float fPassivationPadRLEExcludeEdge;		//// 20180327 PLP Passivation Pad RLE
*/
	float fSpaceTraceSpirePointMaskSize;      // 20201103 rename fAutoShortDistanceMask to fSpaceTraceSpirePointMaskSize by ljg
	
	CString strSmallBlobRLEExcludeEdge;
	CString strSmallBlobSpRLEExcludeEdge;
	CString strPrecisionOfSmallPattern;
	CString strPrecisionOfPattern;
	CString strPrecisionOfSpace;
	CString strPrecisionOfARLand;	
	CString strPrecisionOfViaLand;	
	CString strPrecisionOfPadTip;
	CString strPrecisionOfAICLRLEEdge;
	CString strPrecisionOfSmallSpace;
	CString strPrecisionOfFinePattern;			
/*	//// 2018042 Delete
//	CString strPrecisionOfCavity;					//// 20170707 PLP Cavity RLE
//	CString strPrecisionOfDie;						//// 20170707 PLP Die RLE
//	CString strPrecisionOfPassivationPad;			//// 20180327 PLP Passivation Pad RLE
*/
	CString strEdgeExcludeLineWidthAccuracy;
	CString strEdgeExcludeLineWidthSpeed;

	// Old Spec 
// 20170112 not use, delete	
//	CString strPrecisionOfSRPad;	
};

struct LINE_WIDTH_SPEC{
	LINE_WIDTH_SPEC()
	{
		nWidthRange = 0;
		fNarrowSpec = 0.0;
		fWideSpec = 0.0;
	}	
	int nWidthRange;
	float fNarrowSpec;
	float fWideSpec;
};

struct NEW_LINE_WIDTH_SPEC {
	NEW_LINE_WIDTH_SPEC()
	{
		nWidthRange = 0;
		fEtchingCorrection = 0.0;
		nNickSize = 60;
		nProtrusionSize = 140;
		nNickRelativeSize = 60;
		nProtrusionRelativeSize = 140;
		fPeakLWViolationNickSize = 5.0;
		fPeakLWViolationProtSize = 5.0;
		fNarrowToleranceSize = 0.0;
		fWideToleranceSize = 0.0;
	}
	int nWidthRange;
	float fEtchingCorrection;
	int nNickSize;
	int nProtrusionSize;
	int nNickRelativeSize;
	int nProtrusionRelativeSize;
	float fPeakLWViolationNickSize;
	float fPeakLWViolationProtSize;
	float fNarrowToleranceSize;
	float fWideToleranceSize;
};

struct INSPECTION_SPEC{
	INSPECTION_SPEC()
	{
//		bUseLineWidthSpec = FALSE;
		strSizeOfNick = _T("Normal");
		nNickSizeRatio = 50;
		nBrightnessOfNick = 0;
		nGrayOfOpen = 0;
		strSizeOfNickOnPad = _T("Normal");
		nNickSizeOnPadRatio = 50;
		strSizeOfProtrusion = _T("Normal");
		nProtrusionSizeRatio = 150;
		nBrightnessOfProtrusion = 0;
		strMinSizeOfLineSpaceWidth = _T("Normal");
		nBrightnessOfMinLineSpaceWidth = 0;
		nSizeOfDefectMask = 0;
		nDistanceOfDefectMerge = 0;

		nBrightnessOfPinHole = 0;
		fMinSizeOfPinHole = 0.0;

		nBrightnessOfIsland = 0;
		fMinSizeOfIsland = 0.0;

		bMeasureCopperResidualRate = FALSE;
		bMeausreCopperResidualRateAllUnit = FALSE;
		nCopperResidualRateMeasureUnit = 0;
		nCopperResidualRateMeasurePanelStep = 1;
		dCopperHeight = 1.0;
	}	
	CString strSizeOfNick;
	int nNickSizeRatio;
	int nBrightnessOfNick;
	int nGrayOfOpen;	
	CString strSizeOfNickOnPad;
	int nNickSizeOnPadRatio;
	CString strSizeOfProtrusion;
	int nProtrusionSizeRatio;
	int nBrightnessOfProtrusion;
	CString strMinSizeOfLineSpaceWidth;

	int nBrightnessOfMinLineSpaceWidth;
	int nSizeOfDefectMask;
	int nDistanceOfDefectMerge;

	int nBrightnessOfPinHole;
	float fMinSizeOfPinHole;

	int nBrightnessOfIsland;
	float fMinSizeOfIsland;

	//// 20170523 Add
	BOOL bMeasureCopperResidualRate;
	BOOL bMeausreCopperResidualRateAllUnit;		//// 20170822 Add
	int nCopperResidualRateMeasureUnit;				//// Measure Area Type : 0: Unit Area, 1: Manual Area
	int nCopperResidualRateMeasurePanelStep;
	double dCopperHeight;									//// 20170921 Simmtech	
};

//// Multi Line Spec
struct MULTI_LINE_WIDTH_SPEC {
	MULTI_LINE_WIDTH_SPEC()
	{
		bUseMultiLineWidthSpec = FALSE;
		nNumOfLineWidthSpec = 1;
		vecLineWidthNormalSpec.clear();
		vecLineWidthFineSpec.clear();
	}
	BOOL bUseMultiLineWidthSpec;
	int nNumOfLineWidthSpec;
	vector <NEW_LINE_WIDTH_SPEC> vecLineWidthNormalSpec;    //// 20210514 Add
	vector <NEW_LINE_WIDTH_SPEC> vecLineWidthFineSpec;    //// 20210514 Add
};

struct R2R_SPEC{
	R2R_SPEC()
	{
		bSRPattern = FALSE;
		bTopBottomInspection = FALSE;
		fStripInterval = 0.0;
		strOppLayerName.Empty();
	}
	BOOL bSRPattern;
	BOOL bTopBottomInspection;
	float fStripInterval;
	CString strOppLayerName;
};

//// 20180205 Add Hole Master Spec
struct HOLE_SPEC {
	HOLE_SPEC()
	{
		bAlignPointForAOI = TRUE;

		nPixelsOfCamera = 12000;
		nNumberOfAOIAlignPoint = 4;
		nPixelSizeOfAOIAlignPoint = 1024;

		fResolution = 1.75;
		fOverlapSize = 0.4;

		fHoleCorrectionSize = 0.0;			//// Unit : Micron

		strModelName.Empty();
		strLayerName.Empty();
		strSharedFolder.Empty();
		strReferenceStorage.Empty();
	}
	BOOL bAlignPointForAOI;
	
	int	 nPixelsOfCamera;
	int	 nNumberOfAOIAlignPoint;
	int  nPixelSizeOfAOIAlignPoint;

	double fResolution;
	double fOverlapSize;

	double fHoleCorrectionSize;			//// Unit : Micron

	CString strModelName;
	CString strLayerName;
	CString strSharedFolder;
	CString strReferenceStorage;
};

//// 20180330 Add
struct PLP_SPEC {
	PLP_SPEC()
	{
		fCavityMaskExpandSize = 15.0;			// 20170709 PLP Cavity Mask Expand Pixel Size
		fCavityRLEExcludeEdge = 10.0f;			// 20170707 PLP Cavity RLE
		fDieRLEExcludeEdge = 10.0f;				 // 20170707 PLP Cavity RLE
		fPassivationPadRLEExcludeEdge = 10.0f;				 // 20170707 PLP Cavity RLE

		bBigSizeViaBoundaryMask = FALSE;
		fBigSizeViaBounaryInnerMaskSize = 10.0;
		fBigSizeViaBounaryOuterMaskSize = 10.0;
		fBigSizeViaMinSize = 100.0;
		fChipOutLineInnerExpandSize = 5.0;
		fChipOutLineOuterExpandSize = 5.0;

		strPrecisionOfCavity = _T("Normal");
		strPrecisionOfDie = _T("Normal");
		strPrecisionOfPassivationPad = _T("Normal");;			//// 20180327 PLP Passivation Pad RLE

	}
	float fCavityMaskExpandSize;							//// 20170709 PLP Cavity Mask Expand Size   -> 20170804 Pixel->float
	float fCavityRLEExcludeEdge;				// 20170707 PLP Cavity RLE
	float fDieRLEExcludeEdge;					 // 20170707 PLP Cavity RLE
	float fPassivationPadRLEExcludeEdge;		//// 20180327 PLP Passivation Pad RLE

												//// 20180330 Big Size Via
	BOOL bBigSizeViaBoundaryMask;
	float fBigSizeViaBounaryInnerMaskSize;		//// Unit : um
	float fBigSizeViaBounaryOuterMaskSize;		//// Unit : um
	float fBigSizeViaMinSize;							//// Unit : um

	float fChipOutLineInnerExpandSize;			//// 20190212 Add Unit : um
	float fChipOutLineOuterExpandSize;			//// 20190212 Add Unit : um

	CString strPrecisionOfCavity;					//// 20170707 PLP Cavity RLE
	CString strPrecisionOfDie;						//// 20170707 PLP Die RLE
	CString strPrecisionOfPassivationPad;			//// 20180327 PLP Passivation Pad RLE
};

typedef struct tagINSPECTION_SPECIFICATION{
	GENERAL_SPEC specGeneral;
	BUILD_SPEC specBuild;
	INSPECTION_SPEC specInspect;
	R2R_SPEC	specR2R;
	HOLE_SPEC specHole;					//// 20180205 Add Hole Master Spec		
	PLP_SPEC specPLP;
	MULTI_LINE_WIDTH_SPEC specMultiLineWidth;			//// 20210713 Add Multi Line Width Spec
}INSPECTION_SPECIFICATION, *LPINSPECTION_SPECIFICATION;

struct ENVIRONMENT_RS274X_FORMAT{
	ENVIRONMENT_RS274X_FORMAT()
	{
		bAutoPolarityReversal = FALSE;
		bMergeConcavePolygonAperture = FALSE;
		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		nTransformOrder = 0;
		fDetermineZero = 0.00001;
		strInputFolder = _T("D:\\GerberData");
		nFormatStatement = 43;
		strLeadingTrailingZeros = _T("LZ");
	}
	BOOL	bAutoPolarityReversal;
	BOOL bMergeConcavePolygonAperture;
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	int		nFormatStatement;
	int		nTransformOrder;
	double	fDetermineZero;
	CString strInputFolder;	
	CString strLeadingTrailingZeros;
};
struct ENVIRONMENT_GDS2_FORMAT{
	ENVIRONMENT_GDS2_FORMAT()
	{
		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		strInputFolder = _T("D:\\GDS2");
		bFillMode = TRUE;
		bUseTextureDraw = TRUE;
	}
	BOOL    bFillMode;
	BOOL	bUseTextureDraw;					//// 20190623
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	CString strInputFolder;	
};
struct ENVIRONMENT_RS274D_FORMAT{
	ENVIRONMENT_RS274D_FORMAT()
	{
		bAutoPolarityReversal = FALSE;
		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		fDetermineZero = 0.00001;
		strInputFolder = _T("D:\\GerberData");
		nFormatStatement = 43;
		strLeadingTrailingZeros = _T("LZ");
	}
	BOOL	bAutoPolarityReversal;
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	int		nFormatStatement;
	double	fDetermineZero;
	CString strInputFolder;	
	CString strLeadingTrailingZeros;
};

struct ENVIRONMENT_ODB_FORMAT{
	ENVIRONMENT_ODB_FORMAT()
	{
		bAutoPolarityReversal = FALSE;
		bXycronBarcodeType = FALSE;
		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		nTransformOrder = 0;
		fDetermineZero = 0.000001;

		strInputFolder = _T("D:\\ODB++DATA");
		
		strPanelNameList.RemoveAll();
		strStripNameList.RemoveAll();
		strPieceNameList.RemoveAll();
	}
	BOOL	bAutoPolarityReversal;
	BOOL bXycronBarcodeType;							//// 20210311 Add
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	int		nTransformOrder;
	double	fDetermineZero;

	CString strInputFolder;
	
	CStringArray strPanelNameList;
	CStringArray strStripNameList;
	CStringArray strPieceNameList;
};

struct ENVIRONMENT_DXF_FORMAT{
	ENVIRONMENT_DXF_FORMAT()
	{
		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		fDetermineZero = 0.00001;
		strInputFolder.Empty();
		strLtypeShpFilePath.Empty();
		bFill = TRUE;
		bText = FALSE;
		bLType = FALSE;
		bHatchPattern = FALSE;
		bMovePanelPos = FALSE;
	}
	BOOL bFill;
	BOOL bText;
	BOOL bLType;
	BOOL bHatchPattern;
	BOOL bMovePanelPos;
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	double	fDetermineZero;
	CString strInputFolder;
	CString strLtypeShpFilePath;
};

struct ENVIRONMENT_DPF_FORMAT{
	ENVIRONMENT_DPF_FORMAT()
	{
		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		fDetermineZero = 0.0;
		strInputFolder = _T("D:\\DPF");
	}
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	double	fDetermineZero;
	CString strInputFolder;
};

struct ENVIRONMENT_EXCELLON_FORMAT{
	ENVIRONMENT_EXCELLON_FORMAT()
	{
		bDisplayExpandCircle = TRUE;

		nAutoMirrorMode = 0;
		nAutoRotateAngle = 0;
		nTransformOrder = 0;
		fDetermineZero = 0.00001;
		nFormatStatement = 43;
		strInputFolder = _T("D:\\GerberData");
		strUnit = _T("METRIC");
		strToolUnit = _T("METRIC");
		strLeadingTrailingZeros = _T("LZ");
	}
	BOOL bDisplayExpandCircle;										//// 20170928 Add	
	int		nAutoMirrorMode;
	int		nAutoRotateAngle;
	int		nFormatStatement;
	int		nTransformOrder;
	double	fDetermineZero;
	CString strUnit;
	CString strToolUnit;													//// 20180928 Add
	CString strInputFolder;	
	CString strLeadingTrailingZeros;
};

typedef struct tagEnvironmentCamDataFormat{
	ENVIRONMENT_GDS2_FORMAT envirGDS2;
	ENVIRONMENT_RS274X_FORMAT envirRS274X;
	ENVIRONMENT_RS274D_FORMAT envirRS274D;
	ENVIRONMENT_ODB_FORMAT envirODB;
	ENVIRONMENT_DXF_FORMAT envirDXF;
	ENVIRONMENT_DPF_FORMAT envirDPF;
	ENVIRONMENT_EXCELLON_FORMAT envirExcellon;
}ENVIRONMENT_CAM_DATA_FORMAT, *LPENVIRONMENT_CAM_DATA_FORMAT;

typedef struct tagLAYER_VIEW_INFO{
	tagLAYER_VIEW_INFO()
	{
		nLayer = 0;
		bView = 1;
		bLocalColor = FALSE;
		crColor = RGB(0,255,0);
	}
	int nLayer;
	BOOL bView;
	BOOL bLocalColor;
	COLORREF crColor;
}LAYER_VIEW_INFO, *LLAYER_VIEW_INFO;

typedef struct tagDRILL_INFO{
	tagDRILL_INFO()
	{
		nType = 0;
		fRadius = 0.0;
		fLandRadius = 0.0;
		fptCoord = tagdPOINT(0.0, 0.0);
	}
	short nType;						// 0 : Circle, 1: Large Hole
	float fRadius;
	float fLandRadius;
	DPOINT fptCoord;
}DRILL_INFO, *LPDRILL_INFORM;
//// 20180422 Add
typedef struct tagPTH_DRILL_INFO {
	tagPTH_DRILL_INFO()
	{
//		nType = 0;
		fRadius = 0.0;
//		fLandRadius = 0.0;
		fptCoord = tagdPOINT(0.0, 0.0);
	}
//	short nType;						// 0 : Circle, 1: Large Hole
	double fRadius;
//	float fLandRadius;
	DPOINT fptCoord;
}PTH_DRILL_INFO, *LPPTH_DRILL_INFORM;

typedef struct tagCELL_DRILL_INFO {
	tagCELL_DRILL_INFO()
	{
		bSpace = FALSE;
		nID = 0;
		sttDrillInfo = tagDRILL_INFO();
	}
	BOOL bSpace;
	int nID;
	DRILL_INFO sttDrillInfo;
}CELL_DRILL_INFO, *LPCELL_DRILL_INFORM;

typedef struct tagLARGE_DRILL_INFO{
	tagLARGE_DRILL_INFO()
	{
		nShape = DRAW_DRILL::CIRCLE;
		DrillInfo = tagDRILL_INFO();
		fParam.clear();
	}
	DRAW_DRILL::SHAPE nShape;
	DRILL_INFO DrillInfo;
	vector <double> fParam;
}LARGE_DRILL_INFO, *LPLARGE_DRILL_INFORM;

typedef struct tagPOINT_DRILL{
	tagPOINT_DRILL()
	{
		x = 0;
		y = 0;
		R = 0;
	}
	short x;
	short y;
	short R;
}POINT_DRILL, *LPPOINT_DRILL;

typedef struct tagHOLE_LAND_INFO{
	tagHOLE_LAND_INFO()
	{
		nType = LAYER_TYPE::VIA_HOLE;
		nHoledCode = 0;
		nLanddCode = 0;
		fHoleRadius = 0.0;
		fLandRadius = 0.0;
	}
	LAYER_TYPE::TYPE nType;
	int nHoledCode;
	int nLanddCode;
	double fHoleRadius;
	double fLandRadius;
}HOLE_LAND_INFO, *LPHOLE_LAND_INFO;

typedef struct tagCIRCLE_OBJ_INFO{
	tagCIRCLE_OBJ_INFO()
	{
		dCode = 0;
		nStepID = 0;
		fDiameter = 0.0;
		fptCoord = tagdPOINT();
	}
	int dCode;
	int nStepID;
	double fDiameter;
	DPOINT fptCoord;
}CIRCLE_OBJ_INFO, *LPCIRCLE_OBJ_INFO;

typedef struct tagPROPERTY_OBJ{
	tagPROPERTY_OBJ()
	{
		nStepID = 0;
		nLayerID = 0;
		nObjID = 0;
	}
	int nStepID;
	int nLayerID;
	int nObjID;
}PROPERTY_OBJECT, *LPPROPERTY_OBJECT;

typedef struct tagLineInfo{
	tagLineInfo()
	{
		nNumOfLine = 0;
		dCode = 0;
		nLayerID = 0;
		nStepID = 0;
	}
	int nNumOfLine;
	int dCode;
	int nLayerID;
	int nStepID;
}LINE_INFO, LPLINE_INFO;

typedef struct tagLineWidthNumInfo {
	tagLineWidthNumInfo()
	{
		nNumOfLine = 0;
		dWidth = 0.0;
	}
	int nNumOfLine;
	double dWidth;
}LINE_WIDTH_NUM_INFO, LPLINE_WIDTH_NUM_INFO;

typedef struct tagProcessModelInfo{
	tagProcessModelInfo()
	{		
		bOutputMaskLayerNAutoMask = FALSE;
		bAutoMaskOfPieceOuter = FALSE;	
		bOutputMaskImage = FALSE;
		bOutputCrossShieldAsMask = FALSE;
		bOutputArcData = FALSE;
		bIncludeOvalToArcData = FALSE;
		bExceptLeadLayerOutput = FALSE;
		bAcceptLeadObjWidthinPiece = FALSE;
		bRestrictSRDataOfRegionOuter = FALSE;
		bOutputExpandCircleImage = FALSE;
		bExtRgn = FALSE;
		bExtRgnPositiveSign = 1;
		
		nMinPixelSizeOfArcData = 10;
		nExpandCirclePlusPixelSize = 1;
		nAdjDrillDrawFactor = 100;
		nAdjLaserDrillDrawFactor = 100;
		fCavityMaskExpandSize = 15.0;									//// 20170709 PLP Cavity Mask Expand Pixel Size
		fAdjDrillRadius = 1.0;
		fAdjLaserDrillRadius = 1.0;
		fResolutionSize = 5.0;
		
		nInspectionMode = INSPECTION_MODE::PATTERN;

		strModelName.Empty();
		strLayerName.Empty();
		strLayName.Empty();
		strOutputPath.Empty();
		strCadImagePath.Empty();
	}		
	BOOL bOutputMaskLayerNAutoMask;
	BOOL bAutoMaskOfPieceOuter;	
	BOOL bOutputMaskImage;
	BOOL bOutputCrossShieldAsMask;						//// 20170807 Add
	BOOL bOutputArcData;
	BOOL bIncludeOvalToArcData;
	BOOL bExceptLeadLayerOutput;
	BOOL bAcceptLeadObjWidthinPiece;
	BOOL bRestrictSRDataOfRegionOuter;
	BOOL bOutputExpandCircleImage;
	BOOL bExtRgn;
	BOOL bExtRgnPositiveSign;
	int nMinPixelSizeOfArcData;
	int nExpandCirclePlusPixelSize;
	int nAdjDrillDrawFactor;
	int nAdjLaserDrillDrawFactor;
	float fCavityMaskExpandSize;						//// 20170709 PLP Cavity Mask Expand Pixel Size			
	float fAdjDrillRadius;
	float fAdjLaserDrillRadius;
	double fResolutionSize;
	INSPECTION_MODE::MODE nInspectionMode;
	CString strModelName;
	CString strLayerName;
	CString strLayName;
	CString strOutputPath;
	CString strCadImagePath;
}PROCESS_MODEL_INFO, *LPPROCESS_MODEL_INFO;

typedef struct tagLayerPpropertyInfo{
	tagLayerPpropertyInfo()
	{
		bLoadAICLayer = FALSE;
		bLoadProbeCardViaLayer = FALSE;		//// 20160727 sch Soul Brain Probe Card Via
		bLoadCavityLayer = FALSE;						//// 20170621 PLP Cavity Layer
		bLoadPassivationPadLayer = FALSE;		//// 20180326 PLP Passivation Pad Layer
		bLoadChipOutLineLayer = FALSE;			//// 20190212 PLP Chip OutLine Layer
		bLoadSROPadLayer = FALSE;				//// 20210603 SRO Pad Layer
		bLoadRepairMaskAreaLayer = FALSE;			//// 20210906 Repair Mask Area
		nNumOfLeadLayer = 0;
		nNumOfMaskLayer = 0;
		nNumOfSRLayer = 0;
		nNumOfFineAreaLayer = 0;
		nNumOfALDLayer = 0;
		nNumOfGroundLayer = 0;
		nNumOfInspectLayer = 0;
		nNumOfWindowLayer = 0;
		nNumOfUnderLayer = 0;
	}
	BOOL bLoadAICLayer;
	BOOL bLoadProbeCardViaLayer;		//// 20160727 sch Soul Brain Probe Card Via
	BOOL bLoadCavityLayer;					//// 20170621 PLP Cavity Layer
	BOOL bLoadPassivationPadLayer;		//// 20180326 PLP Passivation Pad Layer
	BOOL bLoadChipOutLineLayer;			//// 20190212 PLP Chip OutLine Layer
	BOOL bLoadSROPadLayer;				//// 20210603 SRO Pad Layer
	BOOL bLoadRepairMaskAreaLayer;		//// 20210906 Repair Mask Area
	int nNumOfLeadLayer;
	int nNumOfMaskLayer;
	int nNumOfSRLayer;
	int nNumOfFineAreaLayer;						//// 20180601 Change nNumOfPadLayer
	int nNumOfALDLayer;
	int nNumOfGroundLayer;
	int nNumOfInspectLayer;
	int nNumOfWindowLayer;
	int nNumOfUnderLayer;
}LAYER_PROPERTY_INFO, *LPLAYER_PROPERTY_INFO;

typedef struct tagDrillDataInfo{
	tagDrillDataInfo()
	{
		bThroughHole = FALSE;
		bViaDrill = FALSE;
		bVirtualDrill = FALSE;
		bFilledVia = FALSE;
		bOutputJGHoleData = FALSE;
		bExcludeDrillOnSpace = FALSE;
		nOuputVirtualDrillOnCellBoundary = 1;
		fRangeOfDuplicateDrill = 5.0;

		listThroughHole = NULL;
		listViaDrill = NULL;
		listFilledVia = NULL;
		listVirtualDrill = NULL;
		listLargeDrill = NULL;
		listAnotherLayerDrill = NULL;
		listHoleLandInfo = NULL;		
	}
	BOOL bThroughHole;
	BOOL bViaDrill;
	BOOL bVirtualDrill;
	BOOL bFilledVia;

	BOOL bOutputJGHoleData;
	BOOL bExcludeDrillOnSpace;
	BOOL bExcludeduplicateDrill;
	int  nOuputVirtualDrillOnCellBoundary;

	float fRangeOfDuplicateDrill;
	vector <DRILL_INFO>	*listThroughHole;
	vector <DRILL_INFO> *listViaDrill;
	vector <DRILL_INFO> *listFilledVia;
	vector <DRILL_INFO> *listVirtualDrill;
	vector <LARGE_DRILL_INFO> *listLargeDrill;
	vector <DRILL_INFO> *listAnotherLayerDrill;
	vector <HOLE_LAND_INFO> *listHoleLandInfo;
}DRILL_DATA_INFO, *LPDRILL_DATA_INFO;

typedef struct tagObjectPropertyInfo{
	tagObjectPropertyInfo()
	{
		bDummyObject = FALSE;
		bLeadObject = FALSE;
		bFinePadObject = FALSE;
		bGroundObject = FALSE;
		bInspectObject = FALSE;
		bFiducialObject = FALSE;
		bRouteObject = FALSE;
		bNothingObject = FALSE;

		bCouponAreaInspection = FALSE;							//// 20240401 Add
		bImageMask = FALSE;
		bLeadArea = FALSE;
		bFineArea = FALSE;
		bUnderRegion = FALSE;
		bTraceLogicMaskArea = FALSE;

		listCouponInspectionArea = NULL;						//// 20240401 Add
		listMaskOnCouponArea = NULL;							//// 20240401 Add
		listImageMask = NULL;
		listLeadArea = NULL;
		listFineArea = NULL;
		listExtArea = NULL;
		listUnderRegion = NULL;
		listTraceLogicMaskArea = NULL;
	}
	BOOL bDummyObject;
	BOOL bLeadObject;
	BOOL bFinePadObject;
	BOOL bGroundObject;
	BOOL bInspectObject;
	BOOL bFiducialObject;
	BOOL bRouteObject;
	BOOL bNothingObject;

	BOOL bCouponAreaInspection;								//// 20240130 Add
	BOOL bImageMask;
	BOOL bLeadArea;
	BOOL bFineArea;
	BOOL bUnderRegion;									//// 20160816 Under Region			
	BOOL bTraceLogicMaskArea;						//// 20181129 Trace Logic Mask Area
	vector <DRECT> *listCouponInspectionArea;						//// 20240130 ZDT Coupon Area Inspection
	vector <DRECT> *listMaskOnCouponArea;							//// 20240130 Add
	vector <MASK_INFORM> *listImageMask;
	vector <PROPERTY_AREA_INFORM> *listLeadArea;
	vector <PROPERTY_AREA_INFORM> *listFineArea;
	vector <EXT_AREA_INFORM> *listExtArea;
	vector <PROPERTY_AREA_INFORM> *listUnderRegion;
	vector <PROPERTY_AREA_INFORM> *listTraceLogicMaskArea;

}OBJECT_PROPERTY_INFO, *LPOBJECT_PROPERTY_INFO;

typedef struct tagReferenceDataSummaryInfo{
	tagReferenceDataSummaryInfo()
	{
		bLoadRefDataSummaryInfo = FALSE;
		bMPointAutoGenerate = FALSE;

		nRPUNum = 1;
		nInspectionRegionGroup = 1;
		nCameraPixels = 8192;
		nOverlapPixelSize = 0;
		nPanelCellNum = 0;
		nPanelSwathNum = 0;
		nPanelCellNodeNum = 0;
		nMPointNumInCell = 0;
		nMPointSizeX = 0;
		nMPointSizeY = 0;
		nBlankCellNum = 0;
		nRefDataNum = 0;
		nLowRefDataNum = 0;
		nCreationTime = 0;

		fRefDataCapacity = 0.0;
		fResolution = 2.5;

		strModelName.Empty();
		strLayerName.Empty();
		strRefDataPath.Empty();
		strSpecDataPath.Empty();
		strCadImagePath.Empty();

		vecCellWidth.clear();
		vecCellHeight.clear();
		vecMasterCellNum.clear();
		vecMasterSwathNum.clear();
		vecMasterCellNodeNum.clear();
	}
	BOOL bLoadRefDataSummaryInfo;
	BOOL bMPointAutoGenerate;
	int nRPUNum;
	int nInspectionRegionGroup;
	int nCameraPixels;
	int nOverlapPixelSize;
	int nPanelCellNum;
	int nPanelSwathNum;
	int nPanelCellNodeNum;
	int nMPointNumInCell;
	int nMPointSizeX;
	int nMPointSizeY;
	int nBlankCellNum;
	int nRefDataNum;
	int nLowRefDataNum;
	int nCreationTime;

	float fRefDataCapacity;
	float fResolution;
	
	CString strModelName;
	CString strLayerName;
	CString strRefDataPath;
	CString strSpecDataPath;
	CString strCadImagePath;

	vector <int> vecCellWidth;
	vector <int> vecCellHeight;
	vector <int> vecMasterCellNum;
	vector <int> vecMasterSwathNum;
	vector <int> vecMasterCellNodeNum;
}REFERENCE_DATA_SUMMARY_INFO;

typedef struct tagAutoFocusPositionInfo{
	tagAutoFocusPositionInfo()
	{
		nCellID = 0;
		dPatternRatio = 100.0;
		fptCenter = tagdPOINT(0.0, 0.0);
		Extent = DRECT();
	}
	int nCellID;
	double dPatternRatio;
	DPOINT fptCenter;
	DRECT Extent;
}AUTO_FOCUS_POSITION_INFO;

typedef struct GDS2MapViewInfo{
	GDS2MapViewInfo()
	{
		nKey = 0;
		bView = FALSE;
		bPolarity = TRUE;
	}
	int nKey;
	BOOL bView;
	BOOL bPolarity;
}GDS2_MAP_VIEW_INFO;

typedef struct tagODBSymbolUseScale{
	tagODBSymbolUseScale()
	{
		bUseScaleSymbol = FALSE;

		bRound = FALSE;
		bSquare = FALSE;
		bRectangle = FALSE;
		bRoundRectangle = FALSE;
		bChamferedRectangle = FALSE;
		bOval = FALSE;
		bDiamond = FALSE;
		bOctagon = FALSE;
		bRoundDonut = FALSE;
		bSquareDonut = FALSE;
		bHorizontalHexagon = FALSE;
		bVerticalHexagon = FALSE;
		bButterfly = FALSE;
		bSquareButterfly = FALSE;
		bTriangle = FALSE;
		bHalfOval = FALSE;
		bRoundThermalRounded = FALSE;
		bRoundThermalSquare = FALSE;
		bSquareThermal = FALSE;
		bSquareThermalOpenCorners = FALSE;
		bSquareRoundThermal = FALSE;
		bRectanglarThermal = FALSE;
		bRectanglarThermalOpenCorners = FALSE;
		bEllipsis = FALSE;
		bMoire = FALSE;
		bHole = FALSE;

		bSymbolLine = FALSE;
		bSymbolArc = FALSE;
		bSymbolSurface = FALSE;
		bSymbolText = FALSE;
	}
	BOOL bUseScaleSymbol;

	BOOL bRound;
	BOOL bSquare;
	BOOL bRectangle;
	BOOL bRoundRectangle;
	BOOL bChamferedRectangle;
	BOOL bOval;
	BOOL bDiamond;
	BOOL bOctagon;
	BOOL bRoundDonut;
	BOOL bSquareDonut;
	BOOL bHorizontalHexagon;
	BOOL bVerticalHexagon;
	BOOL bButterfly;
	BOOL bSquareButterfly;
	BOOL bTriangle;
	BOOL bHalfOval;
	BOOL bRoundThermalRounded;
	BOOL bRoundThermalSquare;
	BOOL bSquareThermal;
	BOOL bSquareThermalOpenCorners;
	BOOL bSquareRoundThermal;
	BOOL bRectanglarThermal;
	BOOL bRectanglarThermalOpenCorners;
	BOOL bEllipsis;
	BOOL bMoire;
	BOOL bHole;

	BOOL bSymbolLine;		//// 20160521 Add Line, Arc, Surface, Text
	BOOL bSymbolArc;
	BOOL bSymbolSurface;
	BOOL bSymbolText;
}ODB_SYMBOL_USE_SCALE;

typedef struct tagAutoFocusPointInfo{
	tagAutoFocusPointInfo()
	{
		nSwathID = 0;
		nGroupID = 0;
		nPointNum = 0;
		Extent = DRECT();
		vecAFPosList.clear();
	}
	int nSwathID;
	int nGroupID;
	int nPointNum;
	DRECT Extent;
	vector <AUTO_FOCUS_POSITION_INFO> vecAFPosList;
}AUTO_FOCUS_POINT_INFO;

typedef struct tagMasterSummary{
	int nMasterMode;
	int nMSwath;
	int nNodeNumX;
	int nNodeNumY;
	int nPanelPixelX;
	int nPanelPixelY;
	int nOverlapX;
	int nOverlapY;
	int nProcSizeX;
	int nProcSizeY;
	int nCell;
	int nIPU;
	int nCameraValidPixel;
	int nScanMarginX;
	int nScanMarginY;
	int nRegionX;
	int nRegionY;
	int nCol;
	int nRow;
	int nPinPosX;
	int nPinPosY;
	int nRegionDx;
	int nRegionDy;
}MASTER_SUMMARY, *LPMASTER_SUMMARY;
typedef struct tagCellRegionInfo{
	tagCellRegionInfo()
	{
		fEntireRegion.left = 0.0f;
		fEntireRegion.bottom = 0.0f;
		fEntireRegion.right = 0.0f;
		fEntireRegion.top = 0.0f;
	
		fRegion.clear();
	}
	DRECT	fEntireRegion;
	vector <DRECT> fRegion;
}CELL_REGION_INFO;
//// 20170718 
typedef struct tagCellSwathInfo {
	tagCellSwathInfo()
	{
		bAutoSearch = FALSE;
		nPiece = 1;
		nSwath = 0;
		nDxCell = 0;
		nCellSizeX = 0;
		nOverlapSize = 0;
		dOverlapSize = 0.1;
	}
	BOOL bAutoSearch;
	int nPiece;
	int nSwath;
	int nDxCell;
	int nCellSizeX;
	int nOverlapSize;
	double dOverlapSize;
}CELL_SWATH_INFO, *LPCELL_SWATH_INFO;
/////////////////////////////////////////////////////////////////////

typedef struct tagLayerSpecInfo{
	tagLayerSpecInfo()
	{
		bFirstSwath = FALSE;
		nStep = -1;
		nProcessingRate = 0;
		strLayerName.Empty();
	}
	BOOL bFirstSwath;
	int nStep;
	int nProcessingRate;
	CString strLayerName;
}LAYER_SPEC_INFO;

typedef struct tagRefProcessingModel{
	tagRefProcessingModel()
	{
		bProcessingMode = FALSE;
		bHPSProcessingMode = FALSE;

		st_clock = 0;
		ed_clock_one_cell = 0;
		ed_clock = 0;

		nElaseTime = 0;
		nPredictionTime = 0;

		nPrevProcessingRate = 0;
		nPrevPercent = 0;
		nProgressUpdateStep = 0;
		nLayerSpecInfoID = 0;

		nCameraPixels = 12000;

		nAoiMachineID = 0;

		strModelName.Empty();
		strLayerName.Empty();
		strLayName.Empty();
		strSpecFolder.Empty();
		strRefDataLoc.Empty();

		nCamProcStep = 0;
		strModelCode.Empty();
		strLayerCode.Empty();

		sttRefDataSummaryInfo = tagReferenceDataSummaryInfo();
		
		sttLayerSpecInfo = tagLayerSpecInfo();
		listCellRegionInfo.clear();		
		listRefMasterSummary.clear();
	}
	BOOL bProcessingMode;
	BOOL bHPSProcessingMode;
	clock_t	st_clock;
	clock_t ed_clock_one_cell;
	clock_t ed_clock;

	int		nElaseTime;
	int		nPredictionTime;
	int		nPrevProcessingRate;
	int		nPrevPercent;
	int		nProgressUpdateStep;
	int		nLayerSpecInfoID;
	int		nCameraPixels;
	int		nAoiMachineID;					//// 20200417 Add AOI Machine Type

	CString strModelName;
	CString strLayerName;
	CString strLayName;
	CString strSpecFolder;
	CString strRefDataLoc;

	//// DTS
	int		nCamProcStep;
	CString strModelCode;
	CString strLayerCode;

	REFERENCE_DATA_SUMMARY_INFO sttRefDataSummaryInfo;
	LAYER_SPEC_INFO sttLayerSpecInfo;

	vector <CELL_REGION_INFO>	listCellRegionInfo;
	vector <MASTER_SUMMARY> listRefMasterSummary;
}REF_PROCESSING_MODEL, *LPREF_PROCESSING_MODEL;

///// DB Upload Structure
typedef struct tagUploadModelInfo{
	tagUploadModelInfo()
	{
		strModelCode.Empty();
		strModelName.Empty();
		strBizName.Empty();
		strTotalLayer.Empty();
		strShipType.Empty();
		strInspAreaWidth.Empty();
		strInspAreaHeight.Empty();
		strMasterRegionNum.Empty();
		strMasterGroup.Empty();
		strNumOfStrip.Empty();
		strNumOfPiece.Empty();
		strNumOfStripOut.Empty();
		strMixMaster.Empty();
		strCustomer.Empty();
		strReMark.Empty();
		strRegister.Empty();
		strCoordOfRefPiece.Empty();
		strNumOfRefPiece.Empty();
		strPieceWidth.Empty();
		strPieceHeight.Empty();
		strStripWidth.Empty();
		strStripHeight.Empty();
		strStartPoint.Empty();
	}
	CString strModelCode;
	CString strModelName;
	CString strBizName;
	CString strTotalLayer;
	CString strShipType;
	CString strInspAreaWidth;
	CString strInspAreaHeight;
	CString strMasterRegionNum;
	CString strMasterGroup;
	CString strNumOfStrip;
	CString strNumOfPiece;
	CString strNumOfStripOut;
	CString strMixMaster;
	CString strCustomer;
	CString strReMark;
	CString strRegister;
	CString strCoordOfRefPiece;
	CString strNumOfRefPiece;
	CString strPieceWidth;
	CString strPieceHeight;
	CString strStripWidth;
	CString strStripHeight;
	CString strStartPoint;
}UPLOAD_MODEL_INFO;

typedef struct tagUploadLayerInfo{
	tagUploadLayerInfo()
	{
		strModelCode.Empty();
		strLayerCode.Empty();
		strLayerName.Empty();
		strCamSpecDir.Empty();
		strOffsetX.Empty();
		strOffsetY.Empty();
		strOriginX.Empty();
		strOriginY.Empty(); 
		strSide.Empty();
		strMirror.Empty();
		strRotate.Empty(); 
		strResolution.Empty();
		strSpecPath.Empty();
		strGerberPath.Empty();
		strMasterPath.Empty();
		strCadLinkPath.Empty();
		strRegister.Empty();
		strDate.Empty();
		strScaleX.Empty();
		strScaleY.Empty();
		strInspAreaX1.Empty();
		strInspAreaY1.Empty();
		strInspAreaX2.Empty();
		strInspAreaY2.Empty();
		strSOffsetX1.Empty();
		strSOffsetY1.Empty();
		strSOffsetX2.Empty();
		strSOffsetY2.Empty();
		strPOffsetX1.Empty();
		strPOffsetY1.Empty();
		strPOffsetX2.Empty();
		strPOffsetY2.Empty();
		strRefLayer.Empty();
		strActionCode.Empty();
	}
	CString strModelCode;
	CString strLayerCode;
	CString strLayerName;
	CString strCamSpecDir;
	CString strOffsetX;
	CString strOffsetY;
	CString strOriginX;
	CString strOriginY; 
	CString strSide;
	CString strMirror;
	CString strRotate; 
	CString strResolution;
	CString strSpecPath;
	CString strGerberPath;
	CString strMasterPath;
	CString strCadLinkPath;
	CString strRegister;
	CString strDate;
	CString strScaleX;
	CString strScaleY;
	CString strInspAreaX1;
	CString strInspAreaY1;
	CString strInspAreaX2;
	CString strInspAreaY2;
	CString strSOffsetX1;
	CString strSOffsetY1;
	CString strSOffsetX2;
	CString strSOffsetY2;
	CString strPOffsetX1;
	CString strPOffsetY1;
	CString strPOffsetX2;
	CString strPOffsetY2;
	CString strRefLayer;
	CString strActionCode;
}UPLOAD_LAYER_INFO;

typedef struct tagUpdateStripRegion{
	tagUpdateStripRegion()
	{
		strStripCode.Empty();
		strStripName.Empty();
		strCol.Empty();
		strRow.Empty();
		strCoordinate.Empty();
		strRotate.Empty();
		strCenterCoord.Empty();
		strReMark.Empty();
		strRegister.Empty();
		strType.Empty();
		strStartPoint.Empty();
		strHorDir.Empty();
		OrgCoordList.clear();
	}
	CString strStripCode;
	CString strStripName;
	CString strCol;
	CString strRow;
	CString strCoordinate;
	CString strRotate;
	CString 	strCenterCoord;
	CString strReMark;
	CString strRegister;
	CString strType;
	CString strStartPoint;
	CString strHorDir;
	vector <DPOINT> OrgCoordList;
}UPDATE_STRIP_REGION;

typedef struct tagUpdatePieceRegion{
	tagUpdatePieceRegion()
	{
		bPolygonPiece = FALSE;
		strStripCode.Empty();
		strPieceCode.Empty();
		strCol.Empty();
		strRow.Empty();
		strCoordinate.Empty();
		strRotate.Empty();
		strCenterCoord.Empty();
		strReMark.Empty();
		strRegister.Empty();
		strType.Empty();
		OrgCoordList.clear();
	}
	BOOL bPolygonPiece;
	CString strStripCode;
	CString strPieceCode;
	CString strCol;
	CString strRow;
	CString strCoordinate;
	CString strRotate;
	CString 	strCenterCoord;
	CString strReMark;
	CString strRegister;
	CString strType;
	vector <DPOINT> OrgCoordList;
}UPDATE_PIECE_REGION;

typedef struct tagFeatureRegion{
	tagFeatureRegion()
	{
		nCellID = 0;
		nFlag = 0;
	}
	int nCellID;
	int nFlag;
	vector <IRECT> vecRect;
}FEATURE_REGION;

typedef struct tagObjCenterPointInfo{
	tagObjCenterPointInfo()
	{
		nID = 0;
		nFlag = 0;
		fptCenter = tagdPOINT(0.0, 0.0);
	}
	int nID;
	int nFlag;
	DPOINT fptCenter;
}OBJ_CENTER_POINT_INFO;

typedef struct tagHostPcInfo {
	tagHostPcInfo()
	{
		nNumOfIpAddr = 1;
		strHostName = _T("");
		strIpAddr = _T("");
	}
	int nNumOfIpAddr;
	CString strHostName;
	CString strIpAddr;
}HOST_PC_INFO;

//// YoungPoong Piece Segment Region
typedef struct tagSegmentRegionInfo {
	tagSegmentRegionInfo()
	{
		nID = 0;
		nFlag = 0;
		nVertex = 0;
		CoordList.clear();
	}
	int nID;
	int nFlag;
	int nVertex;
	DRECT Extent;
	vector <DPOINT> CoordList;
}SEGMENT_REGION_INFO;

typedef struct tagPieceSegmentRegionInfo {
	tagPieceSegmentRegionInfo()
	{
		nFlag = 0;
		nPieceID = -1;
		nPieceGroupID = 0;
		nNumOfSegmentRegion = 0;
		nAngle = TRANSFORM_DATA::NONE;
		listSegmentRegion.clear();
	}
	int nFlag;
	int nPieceID;
	int nPieceGroupID;	
	int nNumOfSegmentRegion;
	TRANSFORM_DATA::TYPE nAngle;
	DRECT Extent;
	vector <SEGMENT_REGION_INFO> listSegmentRegion;
}PIECE_SEGMENT_REGION_INFO, *LPPIECE_SEGMENT_REGION_INFO;
typedef CArray <LPPIECE_SEGMENT_REGION_INFO, LPPIECE_SEGMENT_REGION_INFO> CpArPieceSegmentRegionInfo;

typedef struct tagImageHistogram {
	tagImageHistogram()
	{
		nGray = 0;
		fValue = 0;
	}
	int nGray;
	float fValue;
}IMAGE_HISTOGRAM;


typedef struct tagEQUIP_STATUS {
	tagEQUIP_STATUS()
	{
		nAlarm = 0;
		nEQ = 0;
		nEQMoving = 0;
		nProcessWait = 0;
		nEQControl = 0;
		nSignalTowerRed = EQ_STATUS::LAMP_OFF;
		nSignalTowerGreen = EQ_STATUS::LAMP_OFF;
		nSignalTowerYellow = EQ_STATUS::LAMP_OFF;
	}
	int nAlarm;
	int nEQ;
	int nEQMoving;
	int nProcessWait;
	int nEQControl;
	int nSignalTowerRed;
	int nSignalTowerGreen;
	int nSignalTowerYellow;
}EQUIP_STATUS;


typedef struct tagREGULAR_INFO {
	tagREGULAR_INFO()
	{
		fUpEQWaitTime = 0.0f;
		fDnEQWaitTime = 0.0f;
		fMoveOutTact = 0.0f;
		fStopTime = 0.0f;
		nProcessedCount = 0;
		nStayCount = 0;
		fLaserPower = 0.0f;
		fptScannerOffset.x = 0.0f;
		fptScannerOffset.y = 0.0f;
	}
	float fUpEQWaitTime;
	float fDnEQWaitTime;
	float fMoveOutTact;
	float fStopTime;
	float fLaserPower;
	FPOINT fptScannerOffset;
	int nProcessedCount;
	int nStayCount;
	CString strCurrentRecipe;
}REGULAR_INFO;


typedef struct tagLASER_OFFSET_INFO {
	tagLASER_OFFSET_INFO()
	{
		cCurrentTime = CTime::GetCurrentTime();
		nOffsetHour = 0;
	}
	CTime cCurrentTime;
	int nOffsetHour;
	TCHAR chSerial[256];
}LASER_OFFSET_INFO;

typedef struct SSR3DData
{
	SSR3DData()
	{
		m_nVersion = 5;
		m_bLoadManual3D = FALSE;
		m_nSizeX = 0;
		m_nSizeY = 0;
		m_dXResolution = 0;
		m_dYResolution = 0;
		m_bValid = 0;
		m_AmpMatrix = 0;
		m_dMax = 0;
		m_dMin = 0;
		m_dAvg = 0;
		m_dStdev = 0;
		m_dScanStart = 0;
		m_dScanEnd = 0;
		m_dTgu = 0;
		m_dTgd = 0;
		m_dRange = 0;
		m_dRamp = 0;
		m_dMatchingPTX = 0;
		m_dMatchingPTY = 0;
		m_dMatchingScale = 0;
		m_dMatchingTheta = 0;
		m_dMatchingErode = 0;
	}
	int m_nVersion;
	BOOL m_bLoadManual3D;
	int m_nSizeX;
	int m_nSizeY;
	double m_dXResolution;
	double m_dYResolution;
	BOOL m_bValid;
	cv::Mat m_AmpMatrix;
	cv::Mat m_matDepthMap;
	cv::Mat m_matDepthMapColor;
	cv::Mat m_matAllDefect;
	cv::Mat m_matFlu;
	cv::Mat m_matRefCD;
	cv::Mat m_matRefImg;
	cv::Mat m_matOnlyResin;
	double m_dMax;
	double m_dMin;
	double m_dAvg;
	double m_dStdev;
	double m_dScanStart;
	double m_dScanEnd;
	double m_dTgu;
	double m_dTgd;
	double m_dRange;
	double m_dRamp;
	double m_dMatchingPTX;
	double m_dMatchingPTY;
	double m_dMatchingScale;
	double m_dMatchingTheta;
	double m_dMatchingErode;
};
typedef struct AllArea_3D
{
	AllArea_3D()
	{
		m_fCuMax = -9999;
		m_fCuMin = 9999;
		m_fCuAvg = 0;
		m_fCuStdv = 0;
		m_fResinMin = 9999;
		m_fResinAvg = 0;
		m_fResinStdv = 0;
		m_fResin3sig = -9999;
		m_fDemageMax = 9999;
		m_fDemageAvg = 0;
		m_fDemageStdv = 0;
		m_fDemage3sig = 0;
	}

	float m_fCuMax;
	float m_fCuMin;
	float m_fCuAvg;
	float m_fCuStdv;
	float m_fResinMin;
	float m_fResinAvg;
	float m_fResinStdv;
	float m_fResin3sig;
	float m_fDemageMax;
	float m_fDemageAvg;
	float m_fDemageStdv;
	float m_fDemage3sig;

};


typedef struct IMAGE_SAVE_PARAM
{
	IMAGE_SAVE_PARAM()
	{
		nIndex = 0;
		strFilePath.Empty();
	}

	int nIndex;
	CString strFilePath;
};


typedef struct LIGHT_INFO
{
	LIGHT_INFO()
	{
		nMax = 0;
		nMin = 0;
		nMid = 0;
		histLowMax = 0;
		histHeightMax = 0;
		histLowSum = 0;
		histHeightSum = 0;
		dPerCentH = 0; 
		dPerCentL = 0;
		nGain = 0;
	}
	int nMax;
	int nMin;
	int nMid;
#if USE_MVS_CAMERA == USE
	float nGain;
#else
	int nGain;
#endif

	double histLowMax;
	double histHeightMax;
	double histLowSum;
	double histHeightSum;
	double dPerCentH;
	double dPerCentL;
};
struct ZeusRI_Info {
	ZeusRI_Info()
	{
		strZeusInsPath.Empty();
		strZeusResultPath.Empty();

		strZeusRISaveDataPath.Empty();
		strZeusAlarmPath.Empty();
		strZeusImageZipPath.Empty();
		strZeusReferenceZipPath.Empty();

		nZeusRefCapacity = 100;
		nZeusImgCapacity = 100;
		nZeusRefPeriod = 30;
		nZeusImgPeriod = 30;

	}
	CString strZeusInsPath;
	CString strZeusResultPath;

	CString strZeusRISaveDataPath;
	CString strZeusAlarmPath;
	CString strZeusImageZipPath;
	CString strZeusReferenceZipPath;

	int nZeusRefCapacity;
	int nZeusImgCapacity;
	int nZeusRefPeriod;
	int nZeusImgPeriod;

};

#pragma pack(pop)
#endif // !defined(AFX_ENTITIES_H__118242D4_4CA0_45FE_84F6_AE9468839650__INCLUDED_)
