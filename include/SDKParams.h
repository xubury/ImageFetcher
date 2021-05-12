/*************************************************
Copyright (C), 2019-2029, GuideIR Tech. Co., Ltd.
File name	: SDKParams.h
Author		: Guide Sensmart RD
Version		: 1.0
Date		: 2019/7/6
Description	:
*************************************************/
#ifndef SDK_PARAMS_H
#define SDK_PARAMS_H

#include "common_type.h"
#include <string.h>

#ifdef WINDOWS_PLATFORM
#    define GUIDESDKAPI __declspec(dllexport)
#else
#    define GUIDESDKAPI
#endif // WINDOWS_PLATFORM

#ifdef __cplusplus
#    define GUIDESDK_STDC_START  extern "C" {
#    define GUIDESDK_STDC_END    };
#else
#    define GUIDESDK_STDC_START
#    define GUIDESDK_STDC_END
#endif

typedef enum
{
	NONE_MODE = 0,
	Y16_MODE = 1,
	H264_MODE = 2,
	Y16_AND_H264 = 3
}WORKING_MODE;

struct DEVICE_INFO
{
	INT32_T devID;
	CHAR_T  devName[16];
	INT32_T imgWidth;
	INT32_T imgHeight;
	CHAR_T 	serialNum[64];
	CHAR_T 	macAddr[32];
	CHAR_T  ipAddr[16];
	CHAR_T  subNetMask[16];
	CHAR_T  gateway[16];
	CHAR_T  dnsAddr[16];
	UINT16_T armPort;
	UINT16_T fpgaPort;
	UINT16_T y16Port;
	CHAR_T  model[16];
	BOOL_T  isConnected;		//本机是否已连接到设备。如果已连接不能重复再次连接同一台设备。
	WORKING_MODE workingMode;	//本机连接到设备时设置的工作方式，0 NONE_MODE表示未连接。
public:
	DEVICE_INFO()
	{
		memset(this, 0, sizeof(DEVICE_INFO));
	}
};

// RGB视频回调参数数据结构
struct GD_RGB_INFO
{
	BYTE_T *rgbData;			// RGB数据
	INT32_T imgWidth;			// 图像宽
	INT32_T imgHeight;			// 图像高
	INT32_T devID;				// rgbData对应的设备ID
public:
	GD_RGB_INFO()
	{
		memset(this, 0, sizeof(GD_RGB_INFO));
	}
};

// Y16回调参数数据结构
struct GD_Y16_INFO
{
	INT16_T *y16Data;			// Y16数据
	INT32_T imgWidth;			// 图像宽
	INT32_T imgHeight;			// 图像高
	INT32_T devID;				// y16Data对应的设备ID
public:
	GD_Y16_INFO()
	{
		memset(this, 0, sizeof(GD_Y16_INFO));
	}
};

typedef enum
{
	STREAM_DISCONNECT = 0,	// 已断开 
	STREAM_CONNECT = 1,		// 已连接 
}CONNECT_STATE;

// 网络状态回调参数数据结构
struct GD_STATE_INFO
{
	CONNECT_STATE state;
	INT32_T devID;
public:
	GD_STATE_INFO()
	{
		memset(this, 0, sizeof(GD_STATE_INFO));
	}
};

struct POINT_T
{
	INT32_T x;
	INT32_T y;
public:
	POINT_T()
	{
		memset(this, 0, sizeof(POINT_T));
	}
};

struct LINE_T
{
	INT32_T x1;
	INT32_T y1;
	INT32_T x2;
	INT32_T y2;
public:
	LINE_T()
	{
		memset(this, 0, sizeof(LINE_T));
	}
};

// 矩形区域数据结构
struct RECT_T
{
	INT16_T x;	// 矩形左上角X坐标
	INT16_T y;	// 矩形左上角Y坐标
	INT32_T w;	// 矩形宽度
	INT32_T h;	// 矩形高度
public:
	RECT_T()
	{
		memset(this, 0, sizeof(RECT_T));
	}
};

// 温度点数据结构
struct TEMP_POINT
{
	INT16_T x;		// 温度点X坐标
	INT16_T y;		// 温度点Y坐标
	FLOAT_T temp;	// 温度点温度
public:
	TEMP_POINT()
	{
		memset(this, 0, sizeof(TEMP_POINT));
	}
};

// 温度回调参数数据结构
struct GD_TEMP_INFO
{
	TEMP_POINT highTemp;		// 高温
	TEMP_POINT lowTemp;			// 低温
	TEMP_POINT avgTemp;			// 平均温
	TEMP_POINT centTemp;		// 中心温
	INT32_T devID;
public:
	GD_TEMP_INFO()
	{
		memset(this, 0, sizeof(GD_TEMP_INFO));
	}
};

typedef enum
{
	CALC_TEMP_HIGH = 1,			//只计算最高温
	CALC_TEMP_LOW = 2,			//只计算最低温
	CALC_TEMP_AVG = 3,			//只计算平均温
	CALC_TEMP_ALL = 4,			//同时计算最高温、最低温、平均温度
	CALC_TEMP_CENTRE = 5,		//只计算中心温
}CALC_TEMP_TYPE;

typedef enum
{
	SHUTTER_NOW = 1,
	SHUTTER_CLOSE = 2,
	SHUTTER_OPEN = 3,
	AUTO_SHUTTER_ENABLE = 4,
	AUTO_SHUTTER_DISABLE = 5,
	SET_SHUTTER_TIME = 6,		//单位：分钟。
	GET_SHUTTER_TIME = 7
}CMD_SHUTTER_TYPE;

typedef enum
{
	NEAR_FOCUS = 1,
	FAR_FOCUS = 2,
	STOP_FOCUS = 3,
	AUTO_FOCUS = 4,
	NEAR_FOCUS_FINE = 5,
	FAR_FOCUS_FINE = 6,
	SET_MOTOR_POSITION = 7,
	GET_MOTOR_POSITION = 8
}CMD_FOCUS_TYPE;

typedef enum
{
	JPG_WITH_TEMP = 1,
	ONLY_TEMP = 2,
	ONLY_JPG = 3
}IMG_TYPE;

typedef enum
{
	MP4_MEDIA = 1,
	AVI_MEDIA = 2,
}GD_MEDIA_TYPE;

typedef enum
{
	RGB24_PIXEL_FORMAT = 1,
	BGR24_PIXEL_FORMAT = 2,
}GD_PIXEL_FORMAT;

typedef VOID(*RGBDataCB)(GD_RGB_INFO rgbInfo, VOID *param);
typedef VOID(*Y16DataCB)(GD_Y16_INFO y16Info, VOID *param);
typedef VOID(*StateCB)(GD_STATE_INFO stateInfo, VOID *param);
typedef VOID(*TempCB)(GD_TEMP_INFO tempInfo, VOID *param);

// 电子变焦倍数
typedef enum 
{
	GD_EZ_1,
	GD_EZ_2,
	GD_EZ_4
}GD_EZ_TIMES;

// 电子变焦信息
struct GD_EZ_INFO
{
	GD_EZ_TIMES nExLevel;
	INT32_T nCenterX;
	INT32_T nCenterY;
public:
	GD_EZ_INFO()
	{
		memset(this, 0, sizeof(GD_EZ_INFO));
	}
};

typedef enum
{
	ADD_RECT_ANALYSIS = 1,		//添加矩形分析对象
	DELETE_TEMP_ANALYSIS = 2,	//删除分析对象
	ADD_TEMP_DIS = 3,			//显示温度分析，delete用DELETE_TEMP_ANALYSIS
	TEMP_WITH_CURSOR = 4,		//数字温跟随光标，1启用，0禁用。
	GET_RECT_ANALYSIS = 5,		//获取矩形分析对象信息
}CMD_ANALYSIS_TYPE;

struct ANALYSIS_PARAM_INFO
{
	INT32_T combinaType;		//7种温度信息组合方式：0 MAX 1 MIN 2 AVG 3 MAX+MIN 4 MAX+AVG 5 MIN+AVG 6 MAX+MIN+AVG
	RECT_T rect;
	BOOL_T	enableTempWithCursor;//使能数字温跟随光标，1启用，0禁用。
	INT32_T	analyzeMode;		//分析模式 0-关闭分析 1-全屏分析 2-区域分析
public:
	ANALYSIS_PARAM_INFO()
	{
		memset(this, 0, sizeof(ANALYSIS_PARAM_INFO));
	}
};

// 显示色带信息方式
enum SHOW_PALETTE_TYPE
{
	PALETTE_HIDE = 0,		//不显示
	PALETTE_LEFT = 1,		//显示左边
	PALETTE_RIGHT = 2,		//显示右边
};

struct VERSION_INFO
{
	CHAR_T  serialNum[64];
	CHAR_T  macAddr[32];
	CHAR_T  armVersion[32];
	CHAR_T  fpgaVersion[32];
	CHAR_T  sdkVersion[32];
public:
	VERSION_INFO()
	{
		memset(this, 0, sizeof(VERSION_INFO));
	}
};

struct STRING_INFO
{
	INT32_T status;			//使能状态，1 显示字符串，0 不显示字符串。
	INT32_T x;
	INT32_T y;
	INT32_T contentLen;
	CHAR_T  content[1280];	//Unicode, UTF16，添加长字符串
public:
	STRING_INFO()
	{
		memset(this, 0, sizeof(STRING_INFO));
	}
};

typedef enum
{
	ADD_STRING = 1,			//添加字符串
	GET_STRING = 2,			//获取字符串
	ENABLE_STRING = 3,		//使能字符串
	DISABLE_STRING = 4,		//禁用字符串
}CMD_STRING_TYPE;

struct ALARM_INFO
{
	INT32_T state;		//1 高温报警；	2 低温报警； 3 高低温同时报警。0，取消报警。
	INT32_T highLimit;
	INT32_T lowLimit;
	INT32_T mode;		//0 持续报警； 1 自动停止
public:
	ALARM_INFO()
	{
		memset(this, 0, sizeof(ALARM_INFO));
	}
};

typedef enum
{
	ALARM_SWITCH = 1,
	ALARM_STATE = 2,
	ALARM_HIGH = 3,	
	ALARM_LOW = 4,	
	ALARM_MODE = 5,	
	ALARM_ALL_PARAM = 6, //此命令一次完成以上5个参数一起设置。使用上面5个命令可逐个参数分别设置。
}CMD_ALARM_TYPE;

/*取值范围说明：
发射率（0.01~1.00）
距离（0.4m~25m）
湿度(0 % ~100 % )
背景温度(0.1℃~650℃)
B参数（ - 100℃~100℃）
KF参数（1~100）*/
struct CALC_PARAM_INFO
{
	FLOAT_T emiss;		//发射率 0.01-1
	FLOAT_T distance;	//距离	0.4-25
	INT32_T humidity;	//湿度	0-100
	FLOAT_T backTemp;	//背景温度 0.1-650
	INT32_T backFlag;	//背温开关
	FLOAT_T B;			//CorrectionTemp -100-100
	INT32_T KF;			// 0-255
	FLOAT_T transmittance;//透过率 0.00-100.00
public:
	CALC_PARAM_INFO()
	{
		memset(this, 0, sizeof(CALC_PARAM_INFO));
	}
};

enum CALC_PARAM_TYPE
{
	CALC_PARAM_EMISS = 1,
	CALC_PARAM_DISTANCE = 2,
	CALC_PARAM_HUMIDITY = 3,
	CALC_PARAM_BACKTEMP = 4,
	CALC_PARAM_BACKFLAG = 5,
	CALC_PARAM_B = 6,
	CALC_PARAM_KF = 7,
	CALC_PARAM_TRANSMIT = 8,
	CALC_PARAM_ALL = 9,		//以上8个测温参数一起set或者get，一条命令可以完成。
	CALC_PARAM_SAVE = 10,	//保存前面操作设置的参数，掉电后再开机仍然有效。
};

enum DEVICE_PARAM_TYPE
{
	DEVICE_PARAM_RANGE = 1,		//切换测温范围，INT16_T。
	DEVICE_PARAM_RSADDR = 2,	//UART校验，INT32_T。
	DEVICE_PARAM_UARTSPEED = 3,	//UART速率，INT32_T。
	BLACK_BODY_DIAMETER = 4,	//黑体直径，浮点参数。
	AUTO_SWITCH_RANGE = 5,		//是否启用自动切换测温范围，INT32_T。1，自动切换。0，不会自动切换。
};

enum DEVICE_PORT_TYPE
{
	DEVICE_Y16_PORT = 1,
	DEVICE_ARM_PORT = 2,
	DEVICE_FPGA_PORT = 3,
	DEVICE_ALL_PORT = 4,	//以上3个端口信息一起set或者get，一条命令可以完成。
	DEVICE_HTTP_PORT = 5,
};

// 画面调光模式
enum ADJUST_LIGHT_MODE
{
	LIGHT_BRIGHTNESS_CONTRAST = 1,
	LIGHT_TEMPERATURE_MANUAL = 2,
	LIGHT_TEMPERATURE_AUTO = 3,
};

struct LIGHT_PARAM_INFO
{
	ADJUST_LIGHT_MODE mode;
	INT32_T brightness;
	INT32_T contrast;
	FLOAT_T maxT;
	FLOAT_T minT;
public:
	LIGHT_PARAM_INFO()
	{
		memset(this, 0, sizeof(LIGHT_PARAM_INFO));
	}
};

typedef enum
{
	LIGHT_MODE = 1,
	LIGHT_BRIGHT = 2,
	LIGHT_CONTRAST = 3,
	LIGHT_MAX_TEMP = 4,
	LIGHT_MIN_TEMP = 5,
	LIGHT_ALL_PARAM = 6, //此命令一次完成以上5个参数一起设置。使用上面5个命令可逐个参数分别设置。
}CMD_LIGHT_TYPE;

typedef enum
{
	PTZ_GET_ADDR = 0x01,
	PTZ_SET_ADDR,
	PTZ_MOVE_UP,
	PTZ_MOVE_DOWN,
	PTZ_MOVE_LEFT,
	PTZ_MOVE_RIGHT,
	PTZ_MOVE_STOP,
	PTZ_MOVE_LEFT_UP,
	PTZ_MOVE_RIGHT_UP,
	PTZ_MOVE_LEFT_DOWN,
	PTZ_MOVE_RIGHT_DOWN,
	PTZ_ZOOM_IN,
	PTZ_ZOOM_OUT,
	PTZ_ZOOM_STOP,
	PTZ_FOCUS_NEAR,
	PTZ_FOCUS_FAR,
	PTZ_FOCUS_STOP,
	PTZ_APERTURE_OPEN,
	PTZ_APERTURE_CLOSE,
	PTZ_SET_HORI_ANGLE,
	PTZ_GET_HORI_ANGLE,
	PTZ_SET_VERT_ANGLE,
	PTZ_GET_VERT_ANGLE,
	PTZ_SET_LOCA_SPEED,
	PTZ_SET_SCAN_SPEED,
	PTZ_SET_CRUI_INTERVAL,
	PTZ_PRESET_SET,
	PTZ_PRESET_CALL,
	PTZ_PRESET_DELETE,
	PTZ_SET_CRUI_SPEED,
	PTZ_CRUI_START,
	PTZ_CRUI_STOP,
	PTZ_CHECK_POWERON,
	PTZ_FACTORY_SETTINGS,
}PTZ_COMMAND_TYPE;

typedef enum
{
	PLP_GET_POINTS = 0x01,
	PLP_GET_LINES,
	PLP_GET_RECTS,
	PLP_ADD_POINTS,
	PLP_ADD_LINES,
	PLP_ADD_RECTS,
	PLP_UPDATE_POINTS,
	PLP_UPDATE_LINES,
	PLP_UPDATE_RECTS,
	PLP_DELETE_OBJ,
}PLP_COMMAND_TYPE;

struct PLP_OBJ_INFO
{
	INT32_T id;
	CHAR_T name[32];
	INT32_T combinaType;		//7种温度信息组合方式：0 MAX 1 MIN 2 AVG 3 MAX+MIN 4 MAX+AVG 5 MIN+AVG 6 MAX+MIN+AVG
	BOOL_T isHide;
	union {
		POINT_T point;
		LINE_T line;
		RECT_T rect;
	};
public:
	PLP_OBJ_INFO()
	{
		memset(this, 0, sizeof(PLP_OBJ_INFO));
	}
};

//ARM设备状态码
#define ARM_NO_CURVE_FILE_ERROR						0x00000001
#define ARM_Y16_ABNORMAL_ERROR						0x00000002
#define ARM_NO_MEASURE_PARAM_ERROR					0x00000004
#define ARM_FONT_MISSING_ERROR						0x00000008
//FPGA设备状态码
#define FPGA_INVALID_SENSOR_CONFIG_ERROR			0x00000010
#define FPGA_LOAD_FLASH_PARAM_FAILED_ERROR			0x00000020
#define FPGA_DEVICE_WORK_TEMP_OVER_RANGE_ERROR		0x00000040

#endif // !SDK_PARAMS_H
