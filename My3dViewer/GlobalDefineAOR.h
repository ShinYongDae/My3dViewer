#ifndef _GLOBAL_DEFINE_AOR_
#define _GLOBAL_DEFINE_AOR_
#define WM_DISP_PROGRESS									(WM_USER+0)
#define WM_UPDATE_DISPLAY_INDEX								(WM_USER+1)
#define WM_QUIT_MOTION_HOME									(WM_USER+2)
#define WM_ADD_WORK_MESSAGE									(WM_USER+3)
#define WM_QUIT_AUTO_FOCUS									(WM_USER+4)
#define WM_CHECK_IO											(WM_USER+5)
#define WM_DISP_MESSAGE										(WM_USER+6)
#define WM_QUIT_AUTO_MEAS									(WM_USER+7)
#define WM_FREEZE											(WM_USER+10)
#define WM_JOG_DN											(WM_USER+11)
#define WM_JOG_UP											(WM_USER+12)
#define WM_QUIT_ALIGNMENT									(WM_USER+13)	
#define WM_QUIT_CALC_ALIGN_CAMERA_PIXEL_SIZE				(WM_USER+14)	
#define WM_QUIT_AUTO_FIT									(WM_USER+15)
#define WM_QUIT_CALC_CAMERA_PIXEL_SIZE						(WM_USER+16)
#define WM_QUIT_AUTO_FOCUS_ALIGN							(WM_USER+17)
#define WM_QUIT_DLG_SET_SCANNER								(WM_USER+19)
#define WM_QUIT_DLG_HELI_3D_IMAGE							(WM_USER+20)
#define WM_QUIT_DLG_DTS_REGISTERED_LAYER_INFO				(WM_USER+21)
#define WM_QUIT_DLG_LASER_MONITOR							(WM_USER+22)
#define WM_QUIT_DLG_LASER_POWER_MONITOR						(WM_USER+23)
#define WM_QUIT_DLG_LIGHT_CONTROL							(WM_USER+24)
#define WM_QUIT_DLG_MOTION_CONTROL							(WM_USER+25)
#define WM_QUIT_DLG_LASER_FOCUS								(WM_USER+26)
#define WM_QUIT_DLG_IN_OUT_CONTROL							(WM_USER+27)
#define WM_QUIT_DLG_CAMERA_ALIGN							(WM_USER+28)
#define WM_QUIT_DLG_GALVANO_FIELD_CORRECTION				(WM_USER+29)
#define WM_QUIT_DLG_SET_ATTENUATOR							(WM_USER+30)
#define WM_QUIT_DLG_LASER_SENSOR_CONTROL					(WM_USER+31)
#define WM_PROC_MSG_LASER									(WM_USER+32)
#define WM_QUIT_DLG_LASER_SENSOR_CONTROL_SUB				(WM_USER+33)
#define WM_CHANGE_GRID										(WM_USER+34)
#define WM_CHANGE_AXIS										(WM_USER+35)
#define WM_CHANGE_LASER_SENSOR_CONTROL_PORT					(WM_USER+36)
#define WM_SET_LASER_SENSOR_CONTROL_PORT					(WM_USER+37)
#define WM_START_LASER_SENSOR_CONTROL_PORT					(WM_USER+38)
#define WM_STOP_LASER_SENSOR_CONTROL_PORT					(WM_USER+39)
#define WM_QUIT_DLG_SET_LASER_SENSOR						(WM_USER+40)
#define WM_SET_LASER_SENSOR_INIT							(WM_USER+41)
#define WM_QUIT_DLG_CHUCK_FIELD_CORRECTION					(WM_USER+42)
#define WM_QUIT_DLG_TOOL_PATH_DATA							(WM_USER+43)
#define WM_QUIT_DLG_DEFECT_DATA								(WM_USER+44)
#define WM_QUIT_AUTO_LIGHT									(WM_USER+45)
#define WM_QUIT_DLG_SET_CORRECTION							(WM_USER+50)
#define WM_QUIT_DLG_DISPLAY_GRID							(WM_USER+60)
#define WM_QUIT_DLG_SET_TABLE_3D_POS						(WM_USER+61)
#define WM_QUIT_DLG_PLC_REPAIR								(WM_USER+62)
#define WM_OPEN_DLG_PLC_REPAIR								(WM_USER+63)
#define WM_QUIT_DLG_DISPLAY_ROI_PATH						(WM_USER+65)
#define WM_QUIT_DLG_DISPLAY_POWER_MAPPING					(WM_USER+66)
#define WM_QUIT_DLG_APPLY_POWER_MAPPING						(WM_USER+67)
#define WM_QUIT_DLG_DISPLAY_FOCUS_SCORE						(WM_USER+68)
#define WM_QUIT_DLG_SET_3D_OFFSET_TABLE						(WM_USER+69)
#define WM_QUIT_DLG_SET_RECIPE								(WM_USER+70)
#define WM_QUIT_DLG_SET_RECIPE_EX							(WM_USER+75)
#define WM_QUIT_DLG_SET_CAMERA								(WM_USER+80)
#define WM_QUIT_DLG_SET_IPU									(WM_USER+81)	//20211129 add
#define WM_QUIT_DLG_SET_MANUAL_THRES						(WM_USER+90)
#define WM_QUIT_DLG_GV_3D_IMAGE								(WM_USER+91)
#define WM_QUIT_DLG_DISPLAY_ALIGN_VIEW						(WM_USER+92)
#define WM_QUIT_DISP_POWER_MONITOR							(WM_USER+100)
#define WM_QUIT_DLG_SET_SYSTEM_PARAM						(WM_USER+110)
#define WM_QUIT_DLG_SET_ATTENUATOR_MAP						(WM_USER+120)
#define WM_MOVE_ROI_CENTER									(WM_USER+130)
#define WM_QUIT_DLG_SET_CAMERA_CALIBRATION					(WM_USER+140)
#define WM_QUIT_DLG_SET_AOM									(WM_USER+150)
#define WM_QUIT_DLG_SET_AOM_MAP								(WM_USER+160)
#define WM_QUIT_DLG_SET_TABLE_FLATNESS						(WM_USER+170)
#define WM_QUIT_DLG_SET_SCANNER_OFFSET_CALIBRATION			(WM_USER+180)
#define WM_QUIT_DLG_SET_AUTO_SCANNER_OFFSET					(WM_USER+190)
#define WM_QUIT_DLG_SET_ALIGN_CAMERA_PARAM					(WM_USER+199)
#define WM_QUIT_DLG_SET_ALIGN_CAMERA						(WM_USER+200)
#define WM_QUIT_DLG_EDIT_PASSWORD							(WM_USER+201)
#define WM_QUIT_DLG_SET_SYSTEM								(WM_USER+202)
#define WM_QUIT_DLG_CHUCK_FLATNESS							(WM_USER+203)
#define WM_QUIT_DLG_SET_MOTION_CONTROLLER					(WM_USER+204)
#define WM_QUIT_DLG_SET_GALVANO_CONTROLLER					(WM_USER+205)
#define WM_QUIT_DLG_SET_LIGHT_CONTROLLER					(WM_USER+206)
#define WM_QUIT_DLG_SET_LASER_MONITOR						(WM_USER+207)
#define WM_QUIT_DLG_SET_MANUAL_MOTION						(WM_USER+210)
#define WM_QUIT_DLG_SET_FOCUS_OFFSET						(WM_USER+211)
#define WM_QUIT_DLG_SET_AUTO_MEAS							(WM_USER+215)
#define WM_QUIT_GET_FOCUS_VALUE								(WM_USER+216)
#define WM_QUIT_DLG_SET_AUTO_LIGHT							(WM_USER+217)
#define WM_QUIT_DLG_HOT_KEY									(WM_USER+220)
#define WM_QUIT_DLG_DISPLAY_IO								(WM_USER+230)
#define WM_QUIT_DLG_SET_USER_ATTRIBUTE						(WM_USER+240)
#define WM_QUIT_DLG_CHANGE_DEFECT_FILE						(WM_USER+250)
#define WM_QUIT_DLG_CHANGE_DEFECT_FILE2						(WM_USER+251)
#define WM_QUIT_DLG_CHANGE_DEFECT_FILE_UMTC					(WM_USER+253)
#define WM_QUIT_DLG_CLAMP_SETTING							(WM_USER+255)
#define WM_QUIT_DLG_MEAS_CAMERA_PARAM						(WM_USER+260)
#define WM_QUIT_DLG_MENAGEMENT_OF_LIGHT_INTENSITY			(WM_USER+265)
#define WM_QUIT_DLG_SET_MULTI_RECIPE						(WM_USER+275)
#define WM_QUIT_DLG_LASER_OFFSET_TIME_INFO					(WM_USER+276)
#define WM_QUIT_DLG_GALVANO_CONTROL							(WM_USER+280)
#define WM_QUIT_DLG_SET_LASER_POWER_MONITOR					(WM_USER+281)
#define WM_QUIT_DLG_SET_LABMAX								(WM_USER+282)
#define WM_SET_LABMAX_INIT									(WM_USER+283)
#define	WM_QUIT_DLG_LABMAX_CONTROL							(WM_USER+284)
#define WM_QUIT_DLG_PROCESS_OPTION							(WM_USER+285)
#define WM_CHANGE_PROCESS_OPTION							(WM_USER+286)
#define WM_QUIT_DLG_SET_POWER_CALIBRATION					(WM_USER+290)
#define WM_QUIT_DLG_SET_MASK								(WM_USER+291)
#define WM_QUIT_DLG_SET_PIECE								(WM_USER+292)
#define WM_QUIT_DLG_SET_3D_OFFSET_CALIBRATION				(WM_USER+300)
#define WM_QUIT_DLG_IDS_CAMERA_CONTROL						(WM_USER+330)
#define WM_QUIT_DLG_ALIGN_IMAGE_VIEW						(WM_USER+340)
#define WM_QUIT_DLG_SHOW_PROCESSING_STATUS					(WM_USER+345)
#define WM_QUIT_DLG_THICKNESS								(WM_USER+346)
#define WM_MY_IO											(WM_USER+350)
#define WM_MYBTN_UP											(WM_USER+351)
#define WM_MYBTN_DOWN										(WM_USER+352)
#define WM_DISP_IO											(WM_USER+353)
#define WM_QUIT_DLG_POWERMAX								(WM_USER+360)
#define WM_PROC_MSG_POWERMAX								(WM_USER+361)
#define WM_QUIT_DLG_DISPLAY_LASER_INFO						(WM_USER+362)
#define WM_QUIT_DLG_SET_POWERMAX							(WM_USER+370)
#define WM_SET_POWERMAX_INIT								(WM_USER+371)
#define WM_PROC_MSG_SOCKET									(WM_USER+380)
#define WM_PING_END											(WM_USER+381)
#define  WM_FILE_NEW_MESSAGE								(WM_USER+390)
#define  WM_FILE_OPEN_MESSAGE								(WM_USER+391)
#define  WM_FILE_SAVE_MESSAGE								(WM_USER+392)
#define  WM_FILE_SAVE_AS_MESSAGE							(WM_USER+393)
#define  WM_UPDATE_LAYER_INFO								(WM_USER+400)
#define  WM_UPDATE_LOAD_LAYER_INFO							(WM_USER+401)
#define  WM_QUIT_DLG_DXF_VIEWER								(WM_USER+410)
#define  WM_UPDATE_VIEW										(WM_USER+420)
#define  WM_QUIT_DLG_SET_MACHINE_SYSTEM						(WM_USER+430)
#define  WM_QUIT_DLG_SET_CAM								(WM_USER+440)
#define  WM_QUIT_DLG_IMPORT									(WM_USER+450)
#define  WM_QUIT_DLG_COLOR_PICKER							(WM_USER+455)
#define  WM_QUIT_DLG_DISPLAY_GENERAL						(WM_USER+460)
#define  WM_QUIT_DLG_DISPLAY_REF_DATA_INFO					(WM_USER+461)
#define  WM_UPDATA_MEASURE_POINT_BUTTON						(WM_USER+470)
#define  WM_FIT_TO_SCREEN									(WM_USER+480)
#define  WM_QUIT_DLG_HARDWARE_INFO							(WM_USER+490)
#define  WM_QUIT_DLG_HARDWARE_INFO_EX						(WM_USER+491)
#define  WM_SET_MINIMAP_EXTENT_RECT							(WM_USER+500)
#define  WM_SET_MINIMAP_WORLD_RECT							(WM_USER+501)
#define  WM_QUIT_DLG_AUTO_SET_ROI							(WM_USER+510)
#define  WM_REF_BUILDER_STATE								(WM_USER+520)
#define  WM_SH_MEM_DATA_LOAD								(WM_USER+530)
#define  WM_QUIT_DLG_COMPARE_REF_IMAGE						(WM_USER+540)
#define  WM_QUIT_DLG_DISPLAY_REF_BUILD						(WM_USER+550)
#define  WM_RPU_REF_DATA_PROCESSING							(WM_USER+560)
#define  WM_RPU_DRAW_ERROR_MSG								(WM_USER+570)
#define  WM_QUIT_DLG_SET_OPENGL_IMG							(WM_USER+580)
#define  WM_QUIT_DLG_SET_NORMINAL_LINE						(WM_USER+590)
#define  WM_UNDO_REDO_EDIT_REGION							(WM_USER+600)
#define  WM_QUIT_RPU_PROCESSING_MODEL						(WM_USER+610)
#define  WM_FIND_NOMINAL_LINEWIDTH							(WM_USER+620)
#define  WM_GET_LINE_WIDTH									(WM_USER+630)
#define  WM_USER_RENDER_MESSAGE								(WM_USER+631)
#define  WM_USER_CONTROL_AUTOCAM							(WM_USER+632)
#define  WM_START_LEGACY_CONVERT_PROC						(WM_USER+640)
#define WM_UPDATE_MSG										(WM_USER+650)
#define WM_UPDATE_DEFECT									(WM_USER+670)
#define WM_NEXT_DEFECT										(WM_USER+671)
#define WM_MOVE_REFERENCE_POS								(WM_USER+672)
#define WM_UPDATE_LIST_BACK_COLOR							(WM_USER+680)
#define WM_UPDATE_DEFECT_STATE								(WM_USER+690)
#define WM_INIT_UPDATE_DEFECT								(WM_USER+700)
#define WM_JAI_STREAM										(WM_USER+701)
#define IS_JAI_MESSAGE										(WM_USER+702)
#define WM_CONTROL_MESSAGE_BOX								(WM_USER+710)
#define WM_UPDATE_MESSAGE_BOX_TIME							(WM_USER+711)
#define WM_APPLY_MULTI_LANG									(WM_USER+712)
#define WM_OPEN_CHANGE_DEFECT_FILE							(WM_USER+713)
#define WM_ENABLE_WINDOW_UI									(WM_USER+714)
#define WM_CONTROL_MESSAGE_BOX_SUB							(WM_USER+715)
#define WM_UPDATE_MESSAGE_BOX_TIME_SUB						(WM_USER+716)
#define WM_UPDATE_3D_MODEL									(WM_USER+717)
#define WM_QUIT_DLG_SELECT_BAD_CODE							(WM_USER+719)
#define WM_QUIT_DLG_INFO									(WM_USER+720)
#define WM_QUIT_DLG_INFO_SUB								(WM_USER+721)
#define WM_QUIT_DLG_LIST_DATA								(WM_USER+722)
#define WM_UPDATE_CHART_CUSTOM								(WM_USER+723)
#define WM_QUIT_DLG_DISPLAY_REVIEW							(WM_USER+724)
#define WM_QUIT_DLG_SET_POSITION_NAME						(WM_USER+725)
#define WM_QUIT_DLG_3D_JUDGMENT								(WM_USER+726)
#define WM_QUIT_DLG_SELECT_PANEL_INFO						(WM_USER+727)
#define WM_QUIT_DLG_SELECT_LOT_INFO							(WM_USER+728)
#define WM_WRITE_LOG_EQUIP_STATUS							(WM_USER+730)
#define WM_WRITE_LOG_EQUIP_ALARM							(WM_USER+731)
#define WM_WRITE_LOG_REGULAR								(WM_USER+732)
#define WM_QUIT_DLG_READ_2D_CODE							(WM_USER+733)
#define WM_QUIT_DLG_3D_CALIBRATION							(WM_USER+735)
#define WM_QUIT_DLG_SELECT_SKIP_CODE						(WM_USER+736)
#define WM_QUIT_DLG_SET_AOI_CONFIG							(WM_USER+737)
#define WM_QUIT_DLG_SET_ZEUS_CONFIG							(WM_USER+738)
#define WM_QUIT_DLG_RI_RESULT_ANAYSIS						(WM_USER+739)
#define WM_WRITE_DB_DEFECT_INFO								(WM_USER+740)
#define WM_OPEN_BATCH_VEIWER								(WM_USER+745)
#define WM_SERIAL_END										(WM_USER+747)
#define WM_READ_2D_AND_LOAD_SERIAL							(WM_USER+748)
#define WM_UPDATE_MINIMAP									(WM_USER+750)
#define WM_QUIT_DLG_ALARM_PANEL_INFO						(WM_USER+751)
#define WM_UPDATE_MOTION_POS								(WM_USER+752)
#define WM_SAVE_IMAGE_COLOR									(WM_USER+753)
#define WM_SAVE_IMAGE_MONO									(WM_USER+754)
#define WM_COMPLETE_AUTO_REPAIR								(WM_USER+755)
#define WM_QUIT_DLG_SET_GFV									(WM_USER+756)
#define WM_ALIGNMENTSEQ										(WM_USER+757)
#define WM_SET_ALIGN_LIGHT_VALUE1							(WM_USER+761)
#define WM_SET_ALIGN_LIGHT_VALUE2							(WM_USER+762)

#define WM_USER_RENDER										(WM_USER+1000)
#define WM_USER_RUN_THREAD_COMPLETED						(WM_USER+1001)
#define WM_USER_LOAD_CAM_DATA								(WM_USER+1003)
#define WM_CHANGE_PROCESS_REGION							(WM_USER+1004)
#define WM_QUIT_DLG_PROGRESS								(WM_USER+1005)
#define WM_USER_PROGRESS									(WM_USER+1006)
#define WM_QUIT_DLG_SPEC									(WM_USER+1008)
#define WM_USER_INC_PROGRESS								(WM_USER+1010)
#define WM_USER_TASK_COMPLETED								(WM_USER+1011)
#define WM_USER_TASK_THREAD_COMPLETED						(WM_USER+1012)
#define WM_USER_HELP_MESSAGE								(WM_USER+1013)
#define WM_USER_STATUS_MESSAGE								(WM_USER+1014)
#define WM_USER_CUR_POS_MESSAGE								(WM_USER+1015)
#define WM_USER_READ_COMPLETED								(WM_USER+1016)
#define WM_USER_THREAD_COMPLETED							(WM_USER+1017)
#define WM_USER_THREAD_MESSAGE								(WM_USER+1020)
#define WM_USER_DISPLAY_MESSAGE								(WM_USER+1021)
#define WM_USER_REMOVE_MESSAGE								(WM_USER+1022)
#define WM_USER_QUIT_MESSAGE								(WM_USER+1023)
#define WM_USER_DLG_MSG_BOX_TIME_OUT						(WM_USER+1025)
#define WM_USER_DLG_MSG_BOX_CLOSED							(WM_USER+1026)
#define WM_USER_UPDATE_TIME									(WM_USER+1027)
#define WM_USER_UPDATE_MESSAGE								(WM_USER+1028)
#define WM_QUIT_DLG_LOAD_JOB								(WM_USER+1029)
#define WM_QUIT_DLG_ADJUST_SCALE							(WM_USER+1030)
#define WM_SERIAL_PORT_INIT									(WM_USER+1031)
#define WM_QUIT_DLG_SET_SERIAL_PORT							(WM_USER+1032)
#define WM_QUIT_DLG_REF_SPEC								(WM_USER+1033)
#define WM_USER_RENDER_FRAME_BUFFER							(WM_USER+1034)
#define WM_USER_SET_RENDERING_TRANSLATE						(WM_USER+1035)
#define	WM_USER_SET_RENDERING_RECTZOOM						(WM_USER+1036)
#define WM_QUIT_DLG_LINE_LIST_INFORM						(WM_USER+1037)
#define WM_QUIT_DLG_IMAGE_PROCESS							(WM_USER+1038)
#define WM_QUIT_DISPLAY_ONE_CELL_REGION						(WM_USER+1039)
#define WM_QUIT_DLG_LASER_SOURCE_CONTROL					(WM_USER+1040)
#define WM_QUIT_DLG_TEST_MOTION								(WM_USER+1041)
#define WM_QUIT_DLG_CLIENT									(WM_USER+1042)
#define WM_QUIT_DLG_ANALYSIS								(WM_USER+1043)
#define WM_QUIT_DLG_MANUAL_CHECK							(WM_USER+1044)
#define WM_QUIT_DLG_SELECT_REPAIR							(WM_USER+1045)
#define WM_OPEN_SELECT_REPAIR								(WM_USER+1046)
#define WM_LOADER_DATA_LOAD									(WM_USER+1047)
#define WM_READ_BARCODE										(WM_USER+1048)
#define WM_QUIT_DLG_3D_REPEATABILITY						(WM_USER+1049)
#define WM_UPDATE_SURFACEREPEATABILITYDATA					(WM_USER+1050)
#define WM_QUIT_DLG_INPUT_PASSWORD							(WM_USER+1051)
#define WM_QUIT_AUTO_LIGHT_NEW								(WM_USER+1052)

#if USE_SSR_L_UL  ==USE  //JCH 정리필요
#define WM_QUIT_PINALIGNMENT								(WM_USER+1099)
#define WM_UPDATE_READY_STEP								(WM_USER+1100)
#define WM_USER_MESSAGE										(WM_USER+1101)
#define WM_ECS_REMOTECOMMAND								(WM_USER+1102)
#define WM_AUTOSTART_CHANGEMODEL_SHINKO						(WM_USER+1103)
#define WM_SET_LOT_SERIAL									(WM_USER+1104)
#define WM_LOAD_RECIPE										(WM_USER+1105)
#define WM_SET_COLOR										(WM_USER+1106)
#define WM_BRING_TOP										(WM_USER+1107)
#define WM_CALL_READYUI										(WM_USER+1109)
#define WM_LOAD_SERIAL										(WM_USER+1110)
#define WM_ALIGN_LIGHT_UI									(WM_USER+1111)
#endif

#define MAX_SAVED_POS										10
#define ANGLE_RANGE											46
#define PIECE_USER_ID_PATH	_T("C:\\AorSet\\PieceCode.ini")

#include <vector>
using namespace std;

#include "GeoDataType.h"

namespace SHAPE 
{
enum Shape {
	SHAPE_NONE = -1, POLYGON, RECTANGLE, TRIANGLE, LINE
};
}
enum WORK{WORK_NONE=-1, EDIT, MANUAL_ALIGN, VIEW_PIXEL , MEASURE_LINE, SET_MASK};



typedef struct tagDefData {
	tagDefData(UINT pnNumOfCamera = 0, double pPosX = 0, double	pPosY = 0, UINT	pnType = 5, UINT	pnRTVal = 0, UINT pnCellID = 0, int pnMergeIndex = 0,
		int pnCx = 0, int pnCy = 0, double pfDefSize = 0.0, int pnPieceID = 0, int pnFinalCode = 0, UINT pnStripID = 0, CString pnDate = _T(" "),
		CString pnTime = _T(" "), CString	pstrStatusOfVME = _T(" "), UINT pnStripRow = 0, UINT pnStripCol = 0, UINT pnPieceRow = 0,
		UINT pnPieceCol = 0, double pfOffsetX = 0, double pfOffsetY = 0, CString pnResver1 = _T(" "), CString	pnResver2 = _T(" "), int	pnResver3 = 0,
		int	pnResver4 = 0, int	pnResver5 = 0, int	pnResver6 = 0, int	pnResver7 = 0)
	{
		nNumOfCamera = pnNumOfCamera;
		fptPos.x = pPosX; //
		fptPos.y = pPosY; //
		fptMergePos.x = pPosX;
		fptMergePos.y = pPosY;
		nType = pnType;
		nRTVal = pnRTVal;
		nMergeIndex = pnMergeIndex;
		nCellID = pnCellID;
		nCx = pnCx;
		nCy = pnCy;
		fDefSize = pfDefSize;
		nPieceID = pnPieceID;
		nFinalCode = pnFinalCode;
		nStripID = pnStripID;
		strDate = pnDate;
		strTime = pnTime;
		strStatusOfVME = pstrStatusOfVME;
		nStripRow = pnStripRow;
		nStripCol = pnStripCol;
		nPieceRow = pnPieceRow;
		nPieceCol = pnPieceCol;
		fOffsetX = pfOffsetX;
		fOffsetY = pfOffsetY;
		strDummyCode = pnResver1;
		strADCCode = pnResver2;
		nResver1 = pnResver3;
		nResver2 = pnResver4;
		nVRSBadCode = pnResver5;
		nAORCode = pnResver6;
		nRVMSBadCode = pnResver7;
		nAORIndex = 0;
		bNewGTCFormat = FALSE;
	}
	CString	strStatusOfVME;
	CString strInspAlgo;
	CString strImageFileName;
	CString	strDate;		
	CString	strTime;
	CString strGTCTemp1;
	CString strGTCTemp2;
	CString strGTCTemp3;
	CString strGTCTemp4;
	CString strGTCTemp5;
	CString strGTCTemp6;
	CString strGTCTemp7;
	CdPoint fptPos;
	CdPoint fptPosDB;
	CdPoint fptMergePos;
	double	fDefSize;
	double  fOffsetX;
	double  fOffsetY;
	UINT	nNumOfCamera;
	UINT	nType;
	UINT	nRTVal;
	UINT	nCellID;
	UINT	nStripID;
	UINT	nStripRow;
	UINT	nStripCol;
	UINT	nPieceRow;
	UINT	nPieceCol;
	int		nCx;
	int		nCy;
	int		nPieceID;
	int		nFinalCode;
	int		nAORIndex;
	CString		strDummyCode;
	CString		strADCCode;
	int		nResver1;
	int		nResver2;
	int		nVRSBadCode;
	int		nAORCode;
	int		nRVMSBadCode;
	int		nMergeIndex;
	int		nValid;
	BOOL	bNewGTCFormat;
}CDefData;

typedef struct {
	int iStartX, iStartY;
	int iEndX, iEndY;
	int FMirror;	//0 : Defult 1 : Up to Down Mirroring  2 : Left to Right Mirroring
	int FRotate;	//0 : 0  1 : 90  2 : 180  3 : 270 [Degree]
} REGIONS_PIECE;

typedef struct tagNewSerial {
	tagNewSerial(int	pnSerial = 0, int	pnDefault = 0)
	{
		nSerial = pnSerial;
		nDefault = pnDefault;
	}
	int		nSerial;
	int		nDefault;
}NewSerial;


typedef struct tagXML_REF_LAYER {
	tagXML_REF_LAYER(int	pnLayerType = 0)
	{
		nLayerType = pnLayerType;
	}
	int nLayerType;
	CString strLayerName;

}XML_REF_LAYER;

typedef struct tagXML_REF_DATA {
	CString strRefFileName;
	CString strRefStepName;
	DPOINT fptAlign[2];
	DPOINT fpt2DC;
	vector<XML_REF_LAYER> vecLayerInfo;
}XML_REF_DATA;

typedef struct tagPieceIdInfo {
	tagPieceIdInfo()
	{
		nRow = 0;
		nCol = 0;
	}
	int nID;
	int nRow;
	int nCol;
	CPoint ptCenter;
} PIECE_ID_INFO, *LPPIECE_ID_INFO;

typedef struct tagExtBadInfo {
	tagExtBadInfo()
	{
		bRepair = FALSE;
	}
	BOOL bRepair;
	CString strBadName;
} EXT_BAD_INFO, *LPEXT_BAD_INFO;

typedef struct tagDBDefectInfo {
	tagDBDefectInfo()
	{
		nActionCode = 0;
		nBKIndex = 0;
	}
	int nActionCode;
	int nBKIndex;
} DB_DEFECT_INFO, *LPDB_DEFECT_INFO;

#endif