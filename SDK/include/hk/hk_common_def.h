#ifndef _HK_COMMON_DEFINE_HEADER_
#define _HK_COMMON_DEFINE_HEADER_

#ifndef _DEFINE_HKHANDLE_
typedef void *HKHANDLE;
typedef void **PHKHANDLE;
#define _DEFINE_HKHANDLE_
#endif

#define MAX_IMAGE_WIDTH 20000
#define MAX_IMAGE_HEIGHT 20000
#define ABSOLUTE_ZERO_TEMP -273.15f
#define MIN_FLOAT_VALUE_AS_SAME 0.001f
#define ERROR_MAX_SENSOR_TEMP 300.0f

#define HK_EMISS_MIN 0.0f
#define HK_EMISS_MAX 1.0f
#define HK_DISTANCE_MIN 0.0f
#define HK_DISTANCE_MAX 100000.0f
#define HK_RELATIVE_HUMIDITY_MIN 0.0f
#define HK_RELATIVE_HUMIDITY_MAX 1.0f

#define ISOTHERM_START_INDEX 180

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

//< 绑定x的值不超出mn和mx的范围
#define HKMIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )	//< 找出x和y中的较小值
#define HKMAX( x, y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )	//< 找出x和y中的较大值
#define HK_RET_OK 0
#define HK_RET_FAILED -1
#define HK_PARA_ERROR -2

#ifndef _HK_UINT64_
#define _HK_UINT64_
#if ( defined( __linux__ ) || defined( __unix__ ) || defined( linux ) || defined( unix ) )
#define HKUINT64 unsigned long long
#else
#define HKUINT64 unsigned __int64
#endif
#endif //< _HK_UINT64_


#ifndef _ENUM_DETECTOR_RESOLUTION_
#define _ENUM_DETECTOR_RESOLUTION_
enum DetectorResolution{
    DR80 = 0,
    DR160 = 1,
    DR320 = 2,
    DR640 = 3,
    DR1024 = 4,
    DRMax = 5,

    DRError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_FPGA_OUTPUT_TYPE_
#define _ENUM_FPGA_OUTPUT_TYPE_
enum FPGAOutputType{
    FOTKValue = 0,
    FOTBValue = 1,
    FOTOriginal = 2,
    FOTColorBar = 3,
    FOTCorrectedWithBadPts = 4,
    FOTCorrected = 5,
    FOTLowAD = 6,
    FOTHighAD = 7,
    FOTBadPts = 8,
    FOTOuterCorrect = 0xd,
    FOTMax= 0xe,

    FOTError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_REVERSE_TYPE
#define _ENUM_REVERSE_TYPE
enum ReverseType {
    RTRL_BT = 0,
    RTLR_BT = 1,
    RTRL_TB = 2,
    RTLR_TB = 3,
    RTMax = 4,

    RTError = 0xFFFFFFFF,
};
#endif
		
#ifndef _ENUM_DATA_STATUS_
#define _ENUM_DATA_STATUS_
enum DataStatus {
    DSOriginal = 0,	//< 原始数据
    DSCorrected = 1,	//< 正常校正后的数据
    DSOnePtCorrect = 2,	//< 正在进行单点校正
    DSTwoPtsCorrectLow = 3,	//< 正在进行低温时的两点校正
    DSTwoPtsCorrectHigh = 4,	//< 正在进行高温时的两点校正
    DSMax = 5,

    DSError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_LEN_TYPE_
#define _ENUM_LEN_TYPE_
enum LenType{
    Len3 = 0,
    Len6 = 1,
    Len12 = 2,
    Len24 = 3,
    Len48 = 4,
	LenMacro = 5,
    LenMax = 6,

	LenError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_LEN_ADJUST_METHOD_
#define _ENUM_LEN_ADJUST_METHOD_
enum LenAdjustMethod {
    LAMManual = 0,
    LAMElectric = 1,
    LAMContinuousMagnification = 2,
    LAMMax = 3,

    LAMError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_BPDPTS_OP_FPGA
#define _ENUM_BPDPTS_OP_FPGA
enum BadPtsOpFPGA {
    BPOFCalc = 0x01,
    BPOFClear = 0x02,
    BPOFAddRectMax = 0x04,
    BPOFAddRectMin = 0x08,
    BPOFSave = 0x10,
    BPOFLoad = 0x20,
	
    BPOFError = 0xFFFF,
};
#endif

#ifndef _ENUM_MEASUREMENT_RANGE_
#define _ENUM_MEASUREMENT_RANGE_
#define TOTAL_MEAS_RANGE 4
enum MeasRange{
    MR0= 0,
    MR1= 1,
    MR2 = 2,
    MR3 = 3,
    MRMax = 4,

    MRError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_CALIBRATE_ENVIRONMENT_
#define _ENUM_CALIBRATE_ENVIRONMENT_
enum CalibrateEnviroment {
    CENormal = 0,
    CELow = 1,
    CEMax = 2,
    CEError = 0xFF,
};
#endif

#ifndef _ENUM_TEMPERATURE_UNIT_
#define _ENUM_TEMPERATURE_UNIT_
enum TemperatureUnit {
    TUCelsius = 0,
    TUFahrenheit = 1,
    TUMax = 2,
};
#endif

#ifndef _ENUM_ANA_TYPE_LOCATION
#define _ENUM_ANA_TYPE_LOCATION
enum AnaTextLocation{
    ATLLeftTop = 0,
    ATLLeftBottom = 1,
    ATLLeft = 2,
    ATLRight = 3,
    ATLMax = 4,
    ATLError = 0xF,
};
#endif

#ifndef _ENUM_SHOW_TEXT_TYPE
#define _ENUM_SHOW_TEXT_TYPE
enum ShowTextType {
    STTNone = 0,		//< 000
    STTMax = 1,			//< 001
    STTMaxMin = 3,  	//< 011
    STTMaxAvg = 5,	    //< 101
    STTMin = 2,			//< 010
    STTMinAvg = 6,		//< 110
    STTAvg = 4,			//< 100
    STTAll = 7,		    //< 111

    STTError = 0xF,
};
#endif

#ifndef _ENUM_PALETTE_
#define _ENUM_PALETTE_
//#define COLOR_DEPTH 256
enum PALETTE {
    PIron = 0,					//< 铁红
    PRainbow = 1,				//< 彩虹
    PFeather = 2,				//< 医疗
    PGray = 3,					//< 灰度
    PCWFeather = 4,             //< 测温医疗
    PALETTEReverse = 5,     //< 该位置开始是反转调色板
    PIronReverse = 5,		//< 反转铁红
    PRainbowReverse = 6,    //< 反转彩虹
    PFeatherReverse = 7,	//< 反转医疗
    PGrayReverse = 8,		//< 反转灰度
    PCWFeatherReverse = 9,  //< 测温反转医疗
    PALETTEMax = 10,

    PALETTEError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_ROTATE_ANGLE_
#define _ENUM_ROTATE_ANGLE_
enum RotationAngle{
    RANormal = 0,       //< 正常
    RARight90 = 1,	    //< 右转90度
    RALeft90 = 2,		//< 左转90度
    RARight180 = 3, 	//< 右转180度
    RALeft180 = 4,	    //< 左转180度
    RAMax = 5,

    RAError = 0xFFFFFFFF,
};
#endif

#ifndef _ENUM_IAMGING_TYPE_
#define _ENUM_IAMGING_TYPE_
enum ImagingType {
	ITAuto = 0,
	ITManual = 1,
    ITFF = 0xFF,
};
#endif
#ifndef _ENUM_IMAGING_ALGORITHM_MODE_
#define _ENUM_IMAGING_ALGORITHM_MODE_
enum ImagingAlgorithmMode{
    IASECTIONLINE = 0,
    IAPLATHIST = 1,
    IAMMax = 2,
};

#endif //< _ENUM_IMAGING_ALGORITHM_MODE_
#ifndef _HK_TEMPERATURE_CACULATE_TYPE
#define _HK_TEMPERATURE_CACULATE_TYPE
enum TemperatureCaculateType {
    TCTFPGA = 0,
    TCTCPU = 1,
    TCTMax = 2,
};
#endif

#ifndef _HK_IMAGING_CACULATE_TYPE
#define _HK_IMAGING_CACULATE_TYPE
enum ImagingCaculateType {
    ICTFPGA = 0,
    ICTCPU = 1,
    ICTMax = 2,
};
#endif

#ifndef _HK_REALTION_TYPE
#define _HK_REALTION_TYPE
enum RelationType {
    RTELessThan = 0,
    RTEGreaterThan = 1,
    RTEMax = 2,
};
#endif

#ifndef _ENUM_IMAGE_SACLE_FACTOR
#define _ENUM_IMAGE_SACLE_FACTOR
enum ImageZoomFactor {
    IZFOne = 1,
    IZFTwo = 2,
    IZFFour = 4,
    IZFEight = 8,
    IZFFifteen = 16,
    IZFMax = 17,

    IZFError = 0xFFFFFFFF,
};
#endif

//< 统一各分析的名称和缩写首字母为，点-P，直线-L，圆-E，框-R，多边形-A，折线-S
#ifndef _ENUM_ANA_TYPE_
#define _ENUM_ANA_TYPE_
enum AnaType {	
    ATPoint = 0,	

    ATLine = 10,
    ATLineStart = 11,
    ATLineEnd = 12,
    ATLineCursorMoveX = 13,
    ATLineCursorMoveY = 14,

    ATEllipse = 20,	
    ATEllipseBorderNW = 21,
    ATEllipseBorderNE = 22,

    ATRect = 30,
    ATRectLT = 31,
    ATRectT = 32,
    ATRectRT = 33,
    ATRectR = 34,
    ATRectRB = 35,
    ATRectB = 36,
    ATRectLB = 37,
    ATRectL = 38,

    ATPoly = 40,
    ATPolyBorder = 41,
    ATPolyPoint = 42,

    ATPolyline = 50,
    ATPolylineBorder = 51,
    ATPolylinePoint = 52,

    ATWholeImage = 100,
    ATMax = 101,
};
#endif

#ifndef _HK_COMPRESS_TYPE_
#define _HK_COMPRESS_TYPE_
enum CompressType {
    CTNoCompress = 0,
    CTHighLow = 1,
    CTFrontBackFrame = 2,
    CTMax = 3,
};
#endif

#ifndef _HK_IR_DETECTOR_TYPE_
#define _HK_IR_DETECTOR_TYPE_
enum IRDetectorType {
    IDTULIS = 0,
    IDTIRay = 1,
    IDMax = 2,
};
#endif

#ifndef _HK_TIME_VAL_
#define _HK_TIME_VAL_
typedef struct tagTimeVal{
    unsigned int tv_sec;         /* seconds */
    unsigned int tv_usec;        /* and microseconds */
}S_TimeVal, *P_S_TimeVal;
#endif //< _HK_TIME_VAL_

#ifndef _HK_POINT_DEF_
#define _HK_POINT_DEF_
typedef struct tagHKPoint {
    unsigned short us_x, us_y;
    tagHKPoint(){
        us_x = us_y = 0;
    }
    tagHKPoint(unsigned short x, unsigned short y) : us_x(x), us_y(y){}
}S_POINT;
#endif

#ifndef _HK_LEN_INFO_DEF_
#define _HK_LEN_INFO_DEF_
typedef struct tagMeasRangeInfo{
    MeasRange range;
    short w_low_of_range, w_high_of_range;
}S_MEAS_RANGE_INFO, *P_S_MEAS_RANGE_INFO;

typedef struct tagLenInfo{
    LenType type;
    char sz_sn[16];
    char sz_des[16];
    unsigned char c_meas_range_count;
    S_MEAS_RANGE_INFO meas_range[MRMax];
}S_LEN_INFO, *P_S_LEN_INFO;
#endif

#ifndef _HK_AD_DEF_
#define _HK_AD_DEF_
typedef struct tagPAD {
    unsigned short	us_x, us_y;
    unsigned short	us_ad;
    tagPAD() {
        us_x = us_y = us_ad = 0;
    }
}S_MAX_AD, S_MIN_AD, *P_S_MAX_AD, *P_S_MIN_AD;
#endif  //< _HK_AD_DEF_

#ifndef _HK_LINE_TBL_DEF_
#define _HK_LINE_TBL_DEF_
typedef struct tagLineTbl {
    unsigned short	us_height;
    unsigned short	us_start, us_end;
    tagLineTbl() : us_height(0), us_start(0), us_end(0) {
    }
}S_LINE_TABLE, *P_S_LINE_TABLE;
#endif

#ifndef _HK_ANA_INFO_DEF_
#define _HK_ANA_INFO_DEF_
typedef struct tagLineCurosr{
    bool show_cursor;
    bool show_temp_of_cursor;
    float f_scale;
}S_LINE_CURSOR, *P_S_LINE_CURSOR;

typedef struct tagAnaInfo{
    char *sz_alias;
    char *sz_label;
    unsigned int ui_line_clr;
    unsigned int ui_line_width;
    unsigned int ui_line_style;
    unsigned short us_avg_ad;
    unsigned short us_low_of_range;
    unsigned short us_high_of_range;
    float f_self_emiss;
    float f_self_dist;
    bool has_self_para;
    bool is_visible;
    bool is_show_max_point;
    bool is_show_min_point;
    bool can_moved;
    bool has_self_imaging_para;
    bool show_alias;
    bool show_label;
    AnaType ana_type;
    S_MAX_AD max_ad;
    S_MIN_AD min_ad;
    PALETTE self_palette;
    ShowTextType show_text_type;
    AnaTextLocation text_location;

    P_S_LINE_CURSOR p_line_cursor;
}S_ANA_INFO, *P_S_ANA_INFO;
#endif

#endif //< _HK_COMMON_DEFINE_HEADER_
