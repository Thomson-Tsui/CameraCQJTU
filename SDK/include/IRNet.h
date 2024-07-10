//IRNet.h
#ifndef __IRNET_H__
#define __IRNET_H__

#include "VSNETStructDef.h"
#include <wtypes.h>


#if defined(PLATFORM_WIN_X64)
typedef __int64 INT_PFW, *PINT_PFW;
typedef unsigned __int64 UINT_PFW, *PUINT_PFW;

#else
typedef int INT_PFW, *PINT_PFW;
typedef unsigned int UINT_PFW, *PUINT_PFW;

typedef float FLOAT;
#endif // PLATFORM_WIN_X64

#ifndef CSTYLE
#ifdef __cplusplus
#define CSTYLE extern "C"
#else
#define CSTYLE
#endif
#endif//CSTYLE

#ifndef CNET_APIIMPORT
#if defined(WIN32)
#ifdef NET_API
#define CNET_APIIMPORT  CSTYLE __declspec(dllexport)
#else
#define CNET_APIIMPORT  CSTYLE __declspec(dllimport)
#endif // NET_API
#elif defined (SYS_LINUX)
#ifdef NET_API
#define CNET_APIIMPORT  CSTYLE __attribute__((visibility("default")))//__attribute__((__stdcall))
#else
#define CNET_APIIMPORT  CSTYLE 
#endif

#endif
#endif//CNET_APIIMPORT

#ifndef IRNET_HANDLE
#define IRNET_HANDLE
typedef void *IRNETHANDLE;
#endif // !IRNET_HANDLE

#ifndef IRNET_HANDLE_VALID
#define IRNET_HANDLE_VALID(handle) (handle != (IRNETHANDLE)-1)
#endif // !IRNET_FAILED

#ifndef CALLINGCONVEN
#ifdef WIN32
#define CALLINGCONVEN __stdcall
#else 
#define CALLINGCONVEN
#endif
#endif // !CALLINGCONVEN


#define LAUMSG_LINKMSG          1             ///< connect server link message

#define LAUMSG_ALARM            4             ///< sensor alarm
#define LAUMSG_OUTPUTSTATUS     5             ///< alarm out status

#define LAUMSG_SERVERRECORD     11            ///< server record status

#define LAUMSG_DISKFULL                23     ///<disk full
#define LAUMSG_DISKERROR               24     ///<disk error
#define LAUMSG_ACCESSVIOLATION         25     ///<access violation

#define LAUMSG_SERSTART                26     ///<server start
#define LAUMSG_SERSTOP                 27     ///<server stop


#define LAUMSG_UPDATESTREAMINFO        30     ///<update streaminfo

#define LAUMSG_ALARMMSG_GLOBAL_TEMP    117    ///< Alarm for global temperature limit
#define LAUMSG_ALARMMSG_REGION_TEMP    118    ///<Alarm for region temperature
#define LAUMSG_ALARMMSG_IN             119    ///<Alarm

#define LAUMSG_IR_HIGHT_ALARM          9001   ///<Alarm for IR Hight Temperature
#define LAUMSG_IR_LOW_ALARM            9002   ///<Alarm for IR Low Temperature

#define LAUMSG_ALARMMSG_FIRE           9003    ///<fire alarm
#define LAUMSG_ALARMMSG_TEMPDIFF       9004    ///< temperature compare alarm
#define LAUMSG_ALARMMSG_ITELLIGENT_ANALYSIS     9005    ///< itelligent analysis
#define LAUMSG_ALARMMSG_BH_SECURITE_FIRE        9006    ///< BH security and fire
#define LAUMSG_ALARMMSG_GRIDS_TEMP              9007    ///< GRIDS alarm

/**@brief �ͻ���ͨ����Ϣ�ص�����ָ��
* @param[in] hHandle    ���Ӿ��
* @param[in] wParam     �����
* @param[in] lParam     �Ҳ���
* @param[in] context    ����
* @return ��
*/
typedef void (WINAPI *CCICALLBACK)(IRNETHANDLE hHandle, WPARAM wParam, LPARAM lParam, void *context);

/**@brief raw���ݻص�
* @param[in] data       raw���ݵ�ַ
* @param[in] width      ��
* @param[in] height     ��
* @param[in] context    ����
* @see IRNET_ClientRegRawCallback
*/
typedef void(WINAPI*RAWCALLBACK)(char* data, int width, int height, void* context);

/**@brief ��ɻص��¼�
* @param[in] status     raw���ݵ�ַ
* @param[in] url        �豸IP
* @param[in] sername    �豸����
* @param[in] username   �û���
* @param[in] wserport   �˿ں�
* @param[in] context    �Զ�������
* @return ��
*/
typedef void(WINAPI*FINISHCALLBACK)(int status,char *url, char *sername, char *username, WORD wserport,void * context);


/**@brief ������ͨ������ͨ���ص�����
* @param[in] sername     ����������
* @param[in] url         ������IP
* @param[in] port        �������˿�
* @param[in] serialno    ���������к�
* @param[in] pyhmac      ������MAC��ַ
* @param[in] channels    ������ͨ����
* @param[in] AlarmInNum  ������������
* @param[in] AlarmOutNum �����������
* @param[in] ch          ��ǰ���޷�����ͨ����
* @param[in] bLogin      �Ƿ�ע������ TRUE-���� FALSE-����
* @param[in] hChHandle   ͨ�����
*/
typedef int(WINAPI *RVSCHANNELCALLBACK)(const char *sername, const char *url, WORD port, const char *serialno, unsigned char pyhmac[6], int channels, int AlarmInNum, int AlarmOutNum, int ch, BOOL bLogin, IRNETHANDLE hChHandle);

/**@brief ������������Ϣ�ص�����
* @param[in] hHandle ͨ�����
* @param[in] wParam  ��Ϣ����
* @param[in] lParam  ��Ϣ����
* @param[in] context �ص�����������
*/
typedef void(WINAPI *RVSALARMCALLBACK)(IRNETHANDLE hHandle, WPARAM wParam, LPARAM lParam, void *context);

/** @brief �������ݻص�
* @param[in] hSerial       ͸�����ھ����IRNET_ClientSerialStart����ֵ
* @param[in] pRecvDataBuff ��������ָ�룻(Ϊ��ʱ��ʾ���ӶϿ�)
* @param[in] BuffSize      ���ݳ��ȣ�(< 0ʱ��ʾ���ӶϿ�)
* @param[in] context       �û������ģ�
* @attention 1.�ûص������ǽ��յ����ݾͻص�������һ�λص���һ����һ�����������ݣ�Ҳ�п���һ�λص�����������������ݡ���������Բ�ͬЭ����н���
             2.�ûص��ڲ���ִ�������������Ƽ���ʽΪ���ûص�ֻ���򵥵Ŀ��������������ݿ������û��Զ��������У����������̷��أ��û����û��Զ��������н���Э��
*/
typedef void(WINAPI *pfSerialDataCallBack)(IRNETHANDLE hSerial, char *pRecvDataBuff, int BuffSize, void *context);

/**
*@brief FFF���¶�����
*/
struct FFFTemperatureData 
{
    float*          temperatueData; /**<�¶������׵�ַ*/
    unsigned short  width;          /**<ͼ��Ŀ�*/
    unsigned short  height;         /**<ͼ��ĸ�*/
};

/**
* @brief jpegץ�� ���ݻص�
* @param[in]    handle      IRNET_ClientJpegCapStart����ֵ
* @param[in]    m_ch        ͨ��
* @param[in]    pBuffer     ץ�������׵�ַ
* @param[in]    size        ץ�����ݴ�С
* @param[in]    extraData   ��������(��ץ�ĵ�����ΪFFF��ʽʱ�����ֶβ�Ϊ��ʱ��ʾ FFFTemperatureData )
* @param[in]    userdata    �û�����
* @attention extraDataЧ����ʱ��windows��ʵ��
* @see pfJpegdataCallbackGeneral
*/
typedef void(WINAPI *pfJpegdataCallback)(IRNETHANDLE hHandle, int m_ch, char *pBuffer, int size, void* extraData, void *userdata);

/**
* @brief jpegץ�� ���ݻص�
* @param[in]    handle      IRNET_ClientJpegCapStart����ֵ
* @param[in]    m_ch        ͨ��
* @param[in]    pBuffer     ץ�������׵�ַ
* @param[in]    size        ץ�����ݴ�С
* @param[in]    userdata    �û�����
* @see pfJpegdataCallback
*/
typedef void(WINAPI *pfJpegdataCallbackGeneral)(IRNETHANDLE hHandle, int m_ch, char *pBuffer, int size, void *userdata);

/**
* @brief ����У׼�ص�
* @param[in]    handle      IRNET_ClientSecondCalib4TmStart����ֵ
* @param[in]    m_ch        ͨ��
* @param[in]    status_code ״̬��(0-�ɹ�,����ʧ��)
* @param[in]    userdata    �û�����
*/
typedef void(WINAPI *pfSecondCalibTmCallback)(IRNETHANDLE hHandle, int m_ch, int status_code, void *userdata);

/**@brief �ͻ���ͨ����Ϣ�ṹ*/
typedef struct{
	char *m_sername;                    ///<server name
	char *m_username;                   ///<user name
	char *m_password;                   ///<password
	WORD m_tranType;                    ///<transmit type   
	WORD m_playstart;                   ///<is start view,linux�¸ò�������Ϊ0
	BYTE m_ch;                          ///<channel
	HWND m_hVideohWnd;                  ///<video wnd handle
	HWND m_hChMsgWnd;                   ///<message wnd handle
	UINT m_nChmsgid;                    ///<message id  
	int  m_buffnum;                     ///<buff num
	int  m_useoverlay;                  ///<is use overlay
	COLORREF nColorKey;                 ///<color key(reserved)
	char url[40];                       ///<url
    CCICALLBACK m_messagecallback;      ///<message callback function
	void *context;                      ///<message callback context
}CHANNEL_CLIENTINFO;


/**@brief ����ͼ��ץ�Ĵ�����*/
enum CaptureErrCode
{
    EN_CEC_SUCCESS              =   0x10,   /**<�ɹ�                      */
    EN_CEC_PARAM_INVALID        =   0x11,   /**<������Ч                  */
    EN_CEC_PATH_INVALID         =   0x12,   /**<�ļ�·����Ч              */
    EN_CEC_MEM_NOT_ENOUGH_RAW   =   0x13,   /**<�ڴ治�����raw����       */
    EN_CEC_WRITE_RAW            =   0x14,   /**<д��raw����ʧ��           */
    EN_CEC_MEM_NOT_ENOUGH_VIS   =   0x15,   /**<�ڴ治����޿ɼ�������    */
    EN_CEC_WRITE_VIS            =   0x16,   /**<д��ɼ�������ʧ��        */
    EN_CEC_MEM_NOT_ENOUGH_PRE   =   0x17,   /**<�ڴ治�����Ԥ������      */
    EN_CEC_WRITE_PRE            =   0x18,   /**<д��Ԥ������ʧ��          */
    EN_CEC_WRITE_SENSOR_INFO    =   0x19,   /**<д�봫������Ϣʧ��        */
    EN_CEC_WRITE_CALIB_INFO     =   0x1a,   /**<д��У׼��Ϣʧ��          */
    EN_CEC_WRITE_ENV_INFO       =   0x1b,   /**<д�뻷����Ϣʧ��          */
    EN_CEC_WRITE_PALETTE_INFO   =   0x1C,   /**<д���ɫ����Ϣʧ��        */
    EN_CEC_WRITE_STRENGTH_INFO  =   0x1D,   /**д��ǿ����Ϣʧ��           */
    EN_CEC_COLLECT_FILE_INFO    =   0x1E,   /**<д���Ѽ��ļ���Ϣʧ��      */
    EN_CEC_MEM_NOT_ENOUGH       =   0x1F,   /**<�ڴ治��                  */
    EN_CEC_DECODE_TEMPERATURE   =   0x20,   /**<�����¶�ʧ��              */
    EN_CEC_UNDEFINE             =   0x21,   /**<δ֪����                  */
};

/**@brief ����ͼ��ץ�ĵ��ļ����� 
*/
enum FileType
{
    EN_FT_SDK_LCR           =   0,  /**<��ͼ      */
    EN_FT_SDK_CHANNEL_JPG   =   1,  /**<ͨ��jpg   */
    EN_FT_SDK_CHANNEL_BMP   =   2,  /**<ͨ��bmp   */
};

/**! 
* @brief    �豸�����ⲿ����
* @warning  fWinTrans+fWinRefl<1.0
*/
typedef struct
{
	float	fEmissivity;	///< ����������(0-1)
	float	fWinTrans;		///< ���ڴ�����(0-1)
	float	fWinTemp;		///< �����¶�[K]
	float	fWinRefl;		///< ���ڷ�����(0-1)
	float	fReflTemp;		///< ���ڷ����¶�[k]
	float	fAtmTrans;		///< ����������(0-1) 
	float	fAtmTemp;		///< �����¶�[K]
	float	fBkgTemp;		///< �����¶�[K]
	float	fDistance;		///< ����[meters]
	float	fHumidity;		///< ���ʪ��[0-1]
    float   fRadRate;       ///< ������[0-1]
    float   fEnvTemp;       ///< �����¶�[��]
    int     osdena;         ///< ˮӡʹ��
}DEV_ENV_INFO;

/**@brief �豸�¿����*/
typedef struct 
{
	float	fTempMin;		///< ��С�¶�[C]
	float	fTempMax;		///< ����¶�[C]
	int	    bAuto;			///< �Զ�����(ΪTRUE-����fTempMin��fTempMax)
}DEV_TEMP_SPAN;

/**@brief �豸������Ϣ*/
struct DeviceBaseInfo 
{
    char *servername;   ///<�豸��
    char *username;     ///<�û���
    char *password;     ///<����
    char *url;          ///<�豸IP
    WORD wserport;      ///<�˿�
};

/**@brief ��ɫ��ģʽ*/
typedef enum
{
    DEV_PALETE_WHITEHOT     = 0,      /**< ����         */
    DEV_PALETE_BLACKHOT     = 1,      /**< ����         */
    DEV_PALETE_FUSION       = 2,      /**< �ں�         */
    DEV_PALETE_HOTMETAL     = 2,      /**< HOTMETAL     */
    DEV_PALETE_RAINBOW      = 3,      /**< �ʺ�         */
    DEV_PALETE_GLOBOW       = 4,      /**< GLOBOW       */
    DEV_PALETE_IRON         = 5,      /**< ����         */
    DEV_PALETE_IRON2        = 6,      /**< IRON2        */
    DEV_PALETE_SEPIA        = 7,      /**< SEPIA        */
    DEV_PALETE_COLOR        = 8,      /**< COLOR        */
    DEV_PALETE_COLOR2       = 9,      /**< COLOR2       */
    DEV_PALETE_ICEFIRE      = 10,     /**< ICEFIRE      */
    DEV_PALETE_RAIN         = 11,     /**< RAIN         */
    DEV_PALETE_REDHOT       = 12,     /**< REDHOT       */
    DEV_PALETE_GREENHOT     = 13,     /**< ����         */
    DEV_PALETE_GREYRED      = 14,     /**< �Һ�         */
    DEV_PALETE_LAVA         = 15,     /**< ����         */
    DEV_PALETE_INSTALERT    = 16,     /**< InstAlert    */
    DEV_PALETE_ARCTIC       = 17,     /**< ����         */
    DEV_PALETE_MAX,
}DEV_PALETTE_MODE;

/**@brief ¼���ļ���ʽ*/
enum RecordType
{
    RECDT_INVALID               =   10,     /**<¼���ʽ��Ч                      */
    RECDT_AUTO_BY_FILE_NAME     =   11,     /**<�����ļ����Զ��ж��ļ���ʽ()      */
    RECDT_PRIVATE_MP4           =   12,     /**<˽��mp4�ļ�(ֻ����˽�в���������) */
    RECDT_MP4                   =   13,     /**<MP4                               */
    RECDT_MOV                   =   14,     /**<MOV                               */
    RECDT_ASF                   =   15,     /**<asf                               */
    RECDT_AVI                   =   16,     /**<avi                               */
};


/**@brief �ں���ͼģʽ*/
enum EnumViewMode
{
    EN_MODE_VIS     = 1,    /**< �ɼ�����ͼ  */
    EN_MODE_FUSION  = 2,    /**< �ں���ͼ    */
};

/**@brief �豸У׼�ļ�����*/
enum DevCalibType 
{
    EN_DCT_TEMP         = 0x40,  /**<�����¶�                               */
    EN_DCT_K            = 0x41,  /**<Kֵ                                    */
    EN_DCT_SENSOR       = 0x42,  /**<sensor                                 */
    EN_DCT_BLIND        = 0x43,  /**<äԪ                                   */
    EN_DCT_TABLE_TEMP   = 0x44,  /**<�¶ȱ�  (֮ǰ���¶ȱ���ϲ����˴�)   */
    EN_DCT_B            = 0x45,  /**<Bֵ                                    */
    EN_DCT_COMPENSATE   = 0x46,  /**<������²���                           */
};
/**@brief �������� */
typedef struct _INTRUSION_AREA
{
	unsigned short usX;				///< ���Ͻ�X����
	unsigned short usY;				///< ���Ͻ�Y����
	unsigned short usWidth;			///< �����ȣ���λ������
	unsigned short usHeight;		///< ����߶ȣ���λ������
} LI_INTRUSION_AREA;
/**@brief ���ܷ�������*/
enum IntelligentAnalysisType
{
    EN_IAT_INVALID          = 0,    /**<��Ч              */
    EN_IAT_CORDON           = 1,    /**<������1           */
    EN_IAT_REGION_ENTRY     = 2,    /**<��������          */
    EN_IAT_REGION_LEAVE     = 3,    /**<�뿪����          */
    EN_IAT_GOODS_LEFT       = 4,    /**<��Ʒ����          */
    EN_IAT_GOODS_MOVE       = 5,    /**<��Ʒ��Ǩ          */
    EN_IAT_TARFILTER_MIN    = 6,    /**<����Ŀ��-��С�ߴ� */
    EN_IAT_TARFILTER_MAX    = 7,    /**<����Ŀ��-���ߴ� */
    EN_IAT_REGIONSHIELD     = 8,    /**<��������          */
    EN_IAT_MAX              = 9,
};
        
/**@brief ���ּ��ص�
* @param[in] hHandle                ͨ�����Ӿ��
* @param[in] LI_INTRUSION_AREA      ��⵽�������������ݵ�ַ
* @param[in] areaCount              ��⵽��������������
* @return ��
*/
typedef void (WINAPI*INTRDETECCALLBACK)(IRNETHANDLE hHandle,LI_INTRUSION_AREA*pArea,int areaCount);
/**@brief ���ܷ���-Ŀ����˻ص�
* @param[in] hHandle          ͨ�����Ӿ��
* @param[in] targetWidth      Ŀ��ߴ�Ŀ�
* @param[in] targetHeight     Ŀ��ߴ�ĸ�
* @param[in] context          �Զ�������
* @return ��
*/
typedef void (CALLBACK*TargeFilterCallback)(IRNETHANDLE hHandle, int targetWidth, int targetHeight, void*context);

/**@brief ��������������ע����Ϣ�ṹ*/
typedef struct
{
    char *m_rvsbindurl;        ///<RVS bind url��NULL if all url
    WORD m_rvsbindport;        ///<RVS bind port
}RVSINFOREG;

/**@brief ת����������Ϣ�ṹ*/
typedef struct
{
    char m_multiip[16];                 ///<multicast ipaddress
    WORD m_wMultiPort;                  ///<multicast port
    WORD m_wLocaport;                   ///<local port
    int  m_videobuff;                   ///<video buff num
    int  m_audiobuff;                   ///<audio buff num
    int  m_channuser;                   ///<channel user count
    int  m_totaluser;                   ///<totola user count
    int  (WINAPI *m_UserCheckcallback)(char *m_url, char *username, char *password);	///<user check callback function
    int  (WINAPI *m_UserConnectcallback)(char *m_sername, int channel, BOOL bStart, char *m_userurl, char *username, char *password, int transtype, IRNETHANDLE handle);	///<user login logout callback function
}IRNET_REDIRECTORINFO;

/**@brief ���»ص�����ָ��
* @param[in] hHandle        ���Ӿ��
* @param[in] fTemperature   �¶����ݵ�ַ����СΪͼ��Ŀ����,��λ��
* @param[in] uWidth         ͼ��Ŀ�
* @param[in] uHeight        ͼ��ĸ�
* @param[in] tempSpan       �¿�
* @param[in] context        ��IRNET_ClientRegTempCallBack��context��ͬһ�ݣ��˴�ֻ�����ش�
* @see IRNET_ClientRegTempCallBack
*/
typedef void(CALLBACK*TEMPCALLBACK)(IRNETHANDLE hHandle, float fTemperature[], UINT uWidth, UINT uHeight, DEV_TEMP_SPAN* tempSpan, void*context);
/**
 * @brief                   �Խ��ص�
 * @param[in]   pbuff       ��Ƶ����,���ΪNULL,��Ҫֹͣ�Խ�
 * @param[in]   size        ���ݴ�С,���<=0,��Ҫֹͣ�Խ�
 * @param[in]   context     �û�������
 * @attention �����ڻص�������ֹͣ�Խ�
 * @see IRNET_ClientTalkStart
*/
typedef void(WINAPI *TALKCALLBACK)(char *pbuff, int size, void * context);
/**
 * @brief ��ʾ�ص�
 * @param[in] m_y       Y����
 * @param[in] m_u       U����
 * @param[in] m_v       V����
 * @param[in] stridey   Y���
 * @param[in] strideuv  UV���
 * @param[in] width     ͼ���
 * @param[in] height    ͼ���
 * @param[in] context   �û�������
 * @see IRNET_ClientShowcallback
*/
typedef void(WINAPI *SHOWCALLBACK)(BYTE *m_y,
    BYTE *m_u,
    BYTE *m_v,
    int stridey,
    int strideuv,
    int width,
    int height,
    void *context);
/**
 * @brief ��Ƶԭʼ�����ص�
 * @param[in] pbuff         ֡����
 * @param[in] headsize      ֡ͷ��С
 * @param[in] datasize      ���ݴ�С
 * @param[in] timetick      ʱ���
 * @param[in] biskeyframe   �ؼ�֡���
 * @param[in] context       �û�������
 * @note ��Ҫ���н�������ʱ,֡��������[pbuff,pbuff+datasize)
 * @see IRNET_ClientStartNomalCap
*/
typedef void(WINAPI *ORIGINALVIDEO)(char *pbuff, int headsize, int datasize, int timetick, int biskeyframe, void *context);
/**
* @brief ��Ƶԭʼ�����ص�
* @param[in] pbuff         ֡����
* @param[in] headsize      ֡ͷ��С
* @param[in] datasize      ���ݴ�С
* @param[in] timetick      ʱ���
* @param[in] biskeyframe   �ؼ�֡���
* @param[in] context       �û�������
* @note ��Ҫ���н�������ʱ,֡��������[pbuff,pbuff+datasize)
* @see IRNET_ClientStartNomalCap
*/
typedef void(WINAPI *ORIGINALAUDIO)(char *pbuff, int headsize, int datasize, int timetick, int biskeyframe, void *context);
/**
* @brief    �豸��������
* @note     opt�Ĳ���ֵ
* @see      IRNET_ClientMessageOpen,IRNET_ClientMessageOpt,IRNET_ClientMessageClose
*/
enum MessageOpt
{
    MESSAGE_SERVERCHS                               = 1,        /**<���ͨ����̽ͷ�������������Ŀ          */
    MESSAGE_CMD_RESET                               = 2,        /**<����������                              */
    MESSAGE_CMD_GETGLOBALPARAM                      = 3,        /**<��ȡȫ�ֲ���                            */
    MESSAGE_CMD_SETGLOBALPARAM                      = 4,        /**<����ȫ�ֲ���                            */
    MESSAGE_GETCHANNELPARAM                         = 5,        /**<��ȡͨ������                            */
    MESSAGE_SETCHANNELPARAM                         = 6,        /**<����ͨ������                            */
    MESSAGE_CMD_PARAMDEFAULT                        = 7,        /**<�ָ�����Ĭ�ϲ���(��ͨ)                  */
    MESSAGE_CMD_GETSERIAL                           = 8,        /**<��ȡ���ڲ���                            */
    MESSAGE_CMD_SETSERIAL                           = 9,        /**<���ô��ڲ���                            */
    MESSAGE_CMD_GETSYSTIME                          = 10,       /**<��ȡϵͳʱ��                            */
    MESSAGE_CMD_SETSYSTIME                          = 11,       /**<����ϵͳʱ��                            */
    MESSAGE_CMD_GETSERIALNO                         = 12,       /**<��ȡ���������к�                        */
    MESSAGE_CMD_GETSYSUSER                          = 13,       /**<��÷��������û�                        */
    MESSAGE_CMD_SETSYSUSER                          = 14,       /**<���÷��������û�                        */
    MESSAGE_CMD_OUTPUTCTRL                          = 15,       /**<���Ʊ������(�û�����)                  */
    MESSAGE_CMD_OUTPUTSTATUS                        = 16,       /**<�������״̬                            */
    MESSAGE_CMD_PTZCMDFILE                          = 17,       /**<������̨�������������ļ�                */
    MESSAGE_CMD_PTZCMDNAME                          = 18,       /**<�����̨���������ļ�������              */
    MESSAGE_CMD_SETSUBCHANNELPARAM                  = 19,       /**<���÷�������ͨ������                    */
    MESSAGE_CMD_CAPTUREJPEG                         = 20,       /**<����jpegץͼ(ͼ�������Ӳ��)            */
    MESSAGE_CMD_GETDISKSTATE                        = 21,       /**<��ȡ����״̬                            */
    MESSAGE_CMD_FORMATDISK                          = 22,       /**<��ʽ������                              */
    MESSAGE_CMD_ENCKEYFRAME                         = 23,       /**<�÷���������һ��I֡                     */
    MESSAGE_CMD_GETPPPOEPARAM                       = 24,       /**<��ȡPPPOE����                           */
    MESSAGE_CMD_SETPPPOEPARAM                       = 25,       /**<����PPPOE����                           */
    MESSAGE_CMD_GETSERIAL232                        = 26,       /**<485��232�ϲ� ��ȡ����232����            */
    MESSAGE_CMD_SETSERIAL232                        = 27,       /**<���ô���232����                         */
    MESSAGE_CMD_GETDHCP                             = 28,       /**<��ȡDHCP����                            */
    MESSAGE_CMD_SETDHCP                             = 29,       /**<����DHCP����                            */
    MESSAGE_CMD_GETUPNPCFG                          = 30,       /**<��ȡUPNP���ò���                        */
    MESSAGE_CMD_SETUPNPCFG                          = 31,       /**<����UPNP���ò���                        */
    MESSAGE_CMD_GETUPNPSTATUS                       = 32,       /**<��ȡUPNP״̬                            */
    MESSAGE_CMD_GETMAILCFG                          = 33,       /**<��ȡ�ʼ�������Ϣ                        */
    MESSAGE_CMD_SETMAILCFG                          = 34,       /**<�����ʼ�������Ϣ                        */
    MESSAGE_CMD_GETTIMERCAP                         = 35,       /**<��ȡ��ʱץ�Ĳ���                        */
    MESSAGE_CMD_SETTIMERCAP                         = 36,       /**<���ö�ʱץ�Ĳ���                        */
    MESSAGE_CMD_GETSYSSUPPORTEX                     = 37,       /**<��ȡϵͳ��չ֧����Ϣ                    */
    MESSAGE_CMD_GETDVRSENSORALARM                   = 38,       /**<��ȡDVR̽ͷ��������                     */
    MESSAGE_CMD_SETDVRSENSORALARM                   = 39,       /**<����DVR��ͷ��������                     */
    MESSAGE_CMD_GETENCODETYPE                       = 40,       /**<��ȡ��������                            */
    MESSAGE_CMD_SETENCODETYPE                       = 41,       /**<���ñ�������                            */
    MESSAGE_CMD_MAILTEST                            = 42,       /**<�ʼ�����                                */
    MESSAGE_CMD_GETRTSPPARAMEX                      = 43,       /**<��ȡRTSP����                            */
    MESSAGE_CMD_SETRTSPPARAMEX                      = 44,       /**<����RTSP����                            */
    MESSAGE_CMD_GETTIMEZONE                         = 45,       /**<��ȡ������ʱ������                      */
    MESSAGE_CMD_SETTIMEZONE                         = 46,       /**<���÷�����ʱ������                      */
    MESSAGE_CMD_GETCHANNELOSD_EX                    = 47,       /**<����OSD����(��չ)                       */
    MESSAGE_CMD_SETCHANNELOSD_EX                    = 48,       /**<��ȡOSD����(��չ)                       */
    MESSAGE_CMD_GETFLASHINFO                        = 49,       /**<���flash�汾��Ϣ                       */
    MESSAGE_CMD_GETUPNPPORTINFO                     = 50,       /**<��ȡUPNP�˿���Ϣ                        */
    MESSAGE_CMD_SET_FFCCTRL                         = 51,       /**<���ſ���                                */
    MESSAGE_CMD_GET_CAPTURETYPE                     = 52,       /**<��ȡץ������                            */
    MESSAGE_CMD_SET_CAPTURETYPE                     = 53,       /**<����ץ������                            */
    MESSSGE_CMD_GET_OSDPARAM                        = 54,       /**<��ȡOSD����                             */
    MESSSGE_CMD_SET_OSDPARAM                        = 55,       /**<����OSD����                             */
    MESSSGE_CMD_GET_IROSDPARAM                      = 56,       /**<��ȡ����OSD����                         */
    MESSSGE_CMD_SET_IROSDPARAM                      = 57,       /**<���ú���OSD����                         */
    MESSSGE_CMD_GET_REGIONTEMPPARAM                 = 58,       /**<��ȡ������²���(��ͨ)                  */
    MESSSGE_CMD_SET_REGIONTEMPPARAM                 = 59,       /**<����������²���(��ͨ)                  */
    MESSSGE_CMD_GET_REGIONTEMPALARM                 = 60,       /**<��ȡ������±�������                    */
    MESSSGE_CMD_SET_REGIONTEMPALARM                 = 61,       /**<����������±�������                    */
    MESSSGE_CMD_GET_REGIONTEMPVALUE                 = 62,       /**<��ȡ��������¶�ֵ                      */
    MESSSGE_CMD_GET_VIDEOOUTMODE                    = 63,       /**<��ȡ��Ƶ���ģʽ                        */
    MESSSGE_CMD_SET_VIDEOOUTMODE                    = 64,       /**<������Ƶ���ģʽ                        */
    MESSSGE_CMD_GET_TEMPDATA                        = 65,       /**<��ȡ��������                            */
    MESSSGE_CMD_GET_GLOBALTEMPALARM                 = 66,       /**<��ȡȫ�ֲ��±�������                    */
    MESSSGE_CMD_SET_GLOBALTEMPALARM                 = 67,       /**<����ȫ�ֲ��±�������                    */
    MESSAGE_CMD_GET_IR_VIPARAM                      = 68,       /**<��ȡ����ͼ�����������                */
    MESSAGE_CMD_SET_IR_VIPARAM                      = 69,       /**<���ú���ͼ�����������                */
    MESSAGE_CMD_GET_IR_DDEPARAM                     = 70,       /**<��ȡ����ͼ����DDE����                 */
    MESSAGE_CMD_SET_IR_DDEPARAM                     = 71,       /**<���ú���ͼ����DDE����                 */
    MESSAGE_CMD_GET_IR_STRETCHMODE                  = 72,       /**<��ȡ����ͼ��������ģʽ                */
    MESSAGE_CMD_SET_IR_STRETCHMODE                  = 73,       /**<���ú���ͼ��������ģʽ                */
    MESSAGE_CMD_GET_TAUGAINMODE                     = 74,       /**<��ȡTAU����ģʽ                         */
    MESSAGE_CMD_SET_TAUGAINMODE                     = 75,       /**<����TAU����ģʽ                         */
    MESSAGE_CMD_GET_GPSINFO                         = 76,       /**<��ȡGPS��Ϣ                             */
    MESSAGE_CMD_SET_GPSINFO                         = 77,       /**<����GPS��Ϣ                             */
    MESSAGE_CMD_GETDVRSYSUSEREX                     = 78,       /**<��ȡ�豸�û���Ϣ                        */
    MESSAGE_CMD_SETDVRSYSUSEREX                     = 79,       /**<�����豸�û���Ϣ                        */
    MESSAGE_CMD_REC_REMOTE_BEG                      = 80,       /**<Զ��¼��                                */
    MESSAGE_CMD_REC_REMOTE_END                      = 81,       /**<Զ��¼��                                */
    MESSAGE_CMD_GET_MSDSTATUS                       = 82,       /**<SD���ռ��ȡ                            */
    MESSAGE_CMD_GET_CAL_TEMP_IN_AREA                = 83,       /**<��ȡ�������                            */
    MESSAGE_CMD_SET_CAL_TEMP_IN_AREA                = 84,       /**<���û������                            */
    MESSAGE_CMD_GET_PWMUART_CFG                     = 85,       /**<��ȡ��������                            */
    MESSAGE_CMD_SET_PWMUART_CFG                     = 86,       /**<���ô�������                            */
    MESSAGE_CMD_GET_TEMP_ALARM_PARAM                = 87,       /**<�¶ȳ��ޱ���                            */
    MESSAGE_CMD_SET_TEMP_ALARM_PARAM                = 88,       /**<�¶ȳ��ޱ���                            */
    MESSAGE_CMD_GET_RADMET_PARAM                    = 89,       /**<����������                              */
    MESSAGE_CMD_SET_RADMET_PARAM                    = 90,       /**<����������                              */
    MESSAGE_CMD_GET_STILLCAPTURE                    = 91,       /**<��ʱץ�Ŀ���                            */
    MESSAGE_CMD_SET_STILLCAPTURE                    = 92,       /**<��ʱץ�Ŀ���                            */
    MESSAGE_CMD_GET_ALARM_INPUT_STATUS              = 93,       /**<��ȡ��������̽ͷ״̬                    */
    MESSAGE_CMD_GET_TEMPALARMCTRL                   = 94,       /**<���±�������                            */
    MESSAGE_CMD_SET_TEMPALARMCTRL                   = 95,       /**<���±�������                            */
    MESSAGE_CMD_GET_SDCARDFULLCTRL                  = 96,       /**<SD����������                            */
    MESSAGE_CMD_SET_SDCARDFULLCTRL                  = 97,       /**<SD����������                            */
    MESSAGE_CMD_GET_FIREPOINTPARAM                  = 98,       /**<��ȡ������                            */
    MESSAGE_CMD_SET_FIREPOINTPARAM                  = 99,       /**<���û�����                            */
    MESSAGE_CMD_GET_FIREPOINT                       = 100,      /**<��ȡ���                                */
    MESSAGE_CMD_GET_FIREBEHAVIOURPARAM              = 101,      /**<��ȡ���Ʋ���                            */
    MESSAGE_CMD_SET_FIREBEHAVIOURPARAM              = 102,      /**<���û��Ʋ���                            */
    MESSAGE_CMD_GET_FIREBEHAVIOUR                   = 103,      /**<��ȡ����                                */
    MESSAGE_CMD_GET_OSD_REGION_TRANSPARENT_PARAM    = 104,      /**<OSD����͸������*/
    MESSAGE_CMD_SET_OSD_REGION_TRANSPARENT_PARAM    = 105,      /**<OSD����͸������*/
    MESSAGE_CMD_GET_BUZZER_ENABLE                   = 106,      /**<������ʹ��*/
    MESSAGE_CMD_SET_BUZZER_ENABLE                   = 107,      /**<������ʹ��*/
    MESSAGE_CMD_GETREMOTEHOST                       = 108,      /**<Զ������*/
    MESSAGE_CMD_SETREMOTEHOST                       = 109,      /**<Զ������*/
    MESSAGE_CMD_GET_REGIONTEMPALARMCTRL             = 110,      /**<�����¶ȱ�������*/
    MESSAGE_CMD_SET_REGIONTEMPALARMCTRL             = 111,      /**<�����¶ȱ�������*/
    MESSAGE_CMD_GET_TEMPMEASURETYPE                 = 112,      /**<���������͵�������²���*/
    MESSAGE_CMD_SET_TEMPMEASURETYPE                 = 113,      /**<���������͵�������²���*/
    MESSAGE_CMD_GET_AREATEMPCOMPARECTRL             = 114,      /**<�����¶ȶԱȿ���*/
    MESSAGE_CMD_SET_AREATEMPCOMPARECTRL             = 115,      /**<�����¶ȶԱȿ���*/
    MESSAGE_CMD_GET_REGIONOSDNAME                   = 116,      /**<��������OSD*/
    MESSAGE_CMD_SET_REGIONOSDNAME                   = 117,      /**<��������OSD*/
    MESSAGE_GETALARMPARAM                           = 118,      /**<��������*/
    MESSAGE_SETALARMPARAM                           = 119,      /**<��������*/
    MESSAGE_CMD_GETMOTIONPARAM                      = 120,      /**<�ƶ�������*/
    MESSAGE_CMD_SETMOTIONPARAM                      = 121,      /**<�ƶ�������*/
    MESSAGE_CMD_GETVIDEOMASK                        = 122,      /**<��Ƶ���β���*/
    MESSAGE_CMD_SETVIDEOMASK                        = 123,      /**<��Ƶ���β���*/
    MESSAGE_CMD_GETCHANNELOSD                       = 124,      /**<��Ƶ���Ӳ���*/
    MESSAGE_CMD_SETCHANNELOSD                       = 125,      /**<��Ƶ���Ӳ���*/
    MESSAGE_CMD_AFFIRMUSER                          = 126,      /**<��֤�û�*/
    MESSAGE_CMD_GETTIMEDRESET                       = 127,      /**<��ʱ����*/
    MESSAGE_CMD_SETTIMEDRESET                       = 128,      /**<��ʱ����*/
    MESSAGE_CMD_GETHIDEALARM                        = 129,      /**<�ڵ�����*/
    MESSAGE_CMD_SETHIDEALARM                        = 130,      /**<�ڵ�����*/
    MESSAGE_CMD_GETSUBCHANNELPARAM                  = 131,      /**<��ͨ������*/
    MESSAGE_CMD_GETRECORDPARAM                      = 132,      /**<Ӳ��¼�����*/
    MESSAGE_CMD_SETRECORDPARAM                      = 133,      /**<Ӳ��¼�����*/
    MESSAGE_CMD_GETJPEGCAPPARAM                     = 134,      /**<JPEGץ�Ĳ���*/
    MESSAGE_CMD_SETJPEGCAPPARAM                     = 135,      /**<JPEGץ�Ĳ���*/
    MESSAGE_CMD_GETSENSORALARM                      = 136,      /**<����̽ͷ����*/
    MESSAGE_CMD_SETSENSORALARM                      = 137,      /**<����̽ͷ����*/
    MESSAGE_CMD_GETAUDIOPARAM                       = 138,      /**<��Ƶ����*/
    MESSAGE_CMD_SETAUDIOPARAM                       = 139,      /**<��Ƶ����*/
    MESSAGE_CMD_GETCDMAPARAM                        = 140,      /**<CDMA����*/
    MESSAGE_CMD_SETCDMAPARAM                        = 141,      /**<CDMA����*/
    MESSAGE_CMD_GETWIFIPARAM                        = 142,      /**<Wifi����*/
    MESSAGE_CMD_SETWIFIPARAM                        = 143,      /**<Wifi����*/
    MESSAGE_CMD_GETLINKCONFIG                       = 144,      /**<�������ò���*/
    MESSAGE_CMD_SETLINKCONFIG                       = 145,      /**<�������ò���*/
    MESSAGE_CMD_GETDDNSEXPARAM                      = 146,      /**<DDNS���Ӳ���*/
    MESSAGE_CMD_SETDDNSEXPARAM                      = 147,      /**<DDNS���Ӳ���*/
    MESSAGE_CMD_GETEXALARMPARAM                     = 148,      /**<�ⲿ��������*/
    MESSAGE_CMD_SETEXALARMPARAM                     = 149,      /**<�ⲿ��������*/
    MESSAGE_CMD_GETHUMITUREPRAM                     = 150,      /**<��ʪ�ȱ�������*/
    MESSAGE_CMD_SETHUMITUREPRAM                     = 151,      /**<��ʪ�ȱ�������*/
    MESSAGE_CMD_GETVIDEOOFFSET                      = 152,      /**<��Ƶƫ����*/
    MESSAGE_CMD_SETVIDEOOFFSET                      = 153,      /**<��Ƶƫ����*/
    MESSAGE_CMD_GETVIDEOMASKAREA                    = 154,      /**<��Ƶ������*/
    MESSAGE_CMD_SETVIDEOMASKAREA                    = 155,      /**<��Ƶ������*/
    MESSAGE_CMD_GETSNMPCONFIG                       = 156,      /**<����������*/
    MESSAGE_CMD_SETSNMPCONFIG                       = 157,      /**<����������*/
    MESSAGE_CMD_GETALARMSMS                         = 158,      /**<�������Ų���*/
    MESSAGE_CMD_SETALARMSMS                         = 159,      /**<�������Ų���*/
    MESSAGE_CMD_GETALARMTYPE                        = 160,      /**<̽ͷ����*/
    MESSAGE_CMD_SETALARMTYPE                        = 161,      /**<̽ͷ����*/
    MESSAGE_CMD_GETFTP                              = 162,      /**<FTP��Ϣ*/
    MESSAGE_CMD_SETFTP                              = 163,      /**<FTP��Ϣ*/
    MESSAGE_CMD_GETCCDPARAM                         = 164,      /**<CCD����*/
    MESSAGE_CMD_SETCCDPARAM                         = 165,      /**<CCD����*/
    MESSAGE_CMD_GETPLATFORMINFO                     = 166,      /**<ƽ̨��Ϣ*/
    MESSAGE_CMD_SETPLATFORMINFO                     = 167,      /**<ƽ̨��Ϣ*/
    MESSAGE_CMD_GETVI2VO                            = 168,      /**<ͼ�񻷳�ʹ��*/
    MESSAGE_CMD_SETVI2VO                            = 169,      /**<ͼ�񻷳�ʹ��*/
    MESSAGE_CMD_GETALARMFTPUPLOAD                   = 170,      /**<̽ͷ���������ϴ�FTP����*/
    MESSAGE_CMD_SETALARMFTPUPLOAD                   = 171,      /**<̽ͷ���������ϴ�FTP����*/
    MESSAGE_CMD_GETMOTIONCONTACTEX                  = 172,      /**<�ƶ���ⱨ��������չ����*/
    MESSAGE_CMD_SETMOTIONCONTACTEX                  = 173,      /**<�ƶ���ⱨ��������չ����*/
    MESSAGE_CMD_GETDVRMOTIONALARM                   = 174,      /**<DVR�ƶ���ⱨ������*/
    MESSAGE_CMD_SETDVRMOTIONALARM                   = 175,      /**<DVR�ƶ���ⱨ������*/
    MESSAGE_CMD_GETDVRHIDEALARM                     = 176,      /**<DVR��Ƶ�ڵ���������*/
    MESSAGE_CMD_SETDVRHIDEALARM                     = 177,      /**<DVR��Ƶ�ڵ���������*/
    MESSAGE_CMD_GETDVROTHERALARM                    = 178,      /**<DVR������������*/
    MESSAGE_CMD_SETDVROTHERALARM                    = 179,      /**<DVR������������*/
    MESSAGE_CMD_SETBKDISK                           = 180,      /**<DVR������*/
    MESSAGE_CMD_GETSMARTINFO                        = 181,      /**<DVRӲ��SMART��Ϣ*/
    MESSAGE_CMD_GETVIEWPARAM                        = 182,      /**<V0����*/
    MESSAGE_CMD_SETVIEWPARAM                        = 183,      /**<V0����*/
    MESSAGE_CMD_GETLOOPVIEW                         = 184,      /**<��ѯ���Ʋ���*/
    MESSAGE_CMD_SETLOOPVIEW                         = 185,      /**<��ѯ���Ʋ���*/
    MESSAGE_CMD_GETDVRUSER                          = 186,      /**<DVR�û���Ϣ*/
    MESSAGE_CMD_SETDVRUSER                          = 187,      /**<DVR�û���Ϣ*/
    MESSAGE_CMD_GETDVRCHANNELOSD                    = 188,      /**<DVR��Ƶ���Ӳ���*/
    MESSAGE_CMD_SETDVRCHANNELOSD                    = 189,      /**<DVR��Ƶ���Ӳ���*/
    MESSAGE_CMD_GETVIDEOOFFSETEX                    = 190,      /**<��Ƶƫ����*/
    MESSAGE_CMD_SETVIDEOOFFSETEX                    = 191,      /**<��Ƶƫ����*/
    MESSAGE_CMD_GETDEVICEID                         = 192,      /**<�豸ID*/
    MESSAGE_CMD_SETDEVICEID                         = 193,      /**<�豸ID*/
    MESSAGE_CMD_GETKEYBOARDEX                       = 194,      /**<���̲���*/
    MESSAGE_CMD_SETKEYBOARDEX                       = 195,      /**<���̲���*/
    MESSAGE_CMD_GETCHOOSEPTZ                        = 196,      /**<ѡ����̨*/
    MESSAGE_CMD_SETCHOOSEPTZ                        = 197,      /**<ѡ����̨*/
    MESSAGE_CMD_GETDVRDOUBLEBITS                    = 198,      /**<ѡ���������*/
    MESSAGE_CMD_SETDVRDOUBLEBITS                    = 199,      /**<ѡ���������*/
    MESSAGE_CMD_GETPROTOCOLPARAM                    = 200,      /**<ѡ���Э��*/
    MESSAGE_CMD_SETPROTOCOLPARAM                    = 201,      /**<ѡ���Э��*/
    MESSAGE_CMD_GETFTPTIMEREC                       = 202,      /**<FTP��ʱ¼��*/
    MESSAGE_CMD_SETFTPTIMEREC                       = 203,      /**<FTP��ʱ¼��*/
    MESSAGE_CMD_GETSUBENCODETYPE                    = 204,      /**<ѡ��ı�������*/
    MESSAGE_CMD_SETSUBENCODETYPE                    = 205,      /**<ѡ��ı�������*/
    MESSAGE_CMD_GETPROLOOP                          = 206,      /**<Ԥ�õ���ѯ*/
    MESSAGE_CMD_SETPROLOOP                          = 207,      /**<Ԥ�õ���ѯ*/
    MESSAGE_CMD_GETAUDIOSILENT                      = 208,      /**<��Ƶ��������*/
    MESSAGE_CMD_SETAUDIOSILENT                      = 209,      /**<��Ƶ��������*/
    MESSAGE_CMD_GETDVRUSERSTATE                     = 210,      /**<�û�״̬*/
    MESSAGE_CMD_SETDVRUSERSTATE                     = 211,      /**<�û�״̬*/
    MESSAGE_CMD_GETREDUNDANCERECORD                 = 212,      /**<����¼��״̬*/
    MESSAGE_CMD_SETREDUNDANCERECORD                 = 213,      /**<����¼��״̬*/
    MESSAGE_CMD_GETTHIRDENCODEPARA                  = 214,      /**<������������*/
    MESSAGE_CMD_SETTHIRDENCODEPARA                  = 215,      /**<������������*/
    MESSAGE_CMD_GETTHIRDENCODETYPE                  = 216,      /**<������������*/
    MESSAGE_CMD_SETTHIRDENCODETYPE                  = 217,      /**<������������*/
    MESSAGE_CMD_GETPTZCTRLTIME                      = 218,      /**<��̨��������ʱ��*/
    MESSAGE_CMD_SETPTZCTRLTIME                      = 219,      /**<��̨��������ʱ��*/
    MESSAGE_CMD_GETAUDIOPARAMTYPE                   = 220,      /**<��Ƶ����*/
    MESSAGE_CMD_SETAUDIOPARAMTYPE                   = 221,      /**<��Ƶ����*/
    MESSAGE_CMD_GETDVRVOPARAM                       = 222,      /**<DVR��V0�������*/
    MESSAGE_CMD_SETDVRVOPARAM                       = 223,      /**<DVR��V0�������*/
    MESSAGE_CMD_GETVLCPARAM                         = 224,      /**<VLC����*/
    MESSAGE_CMD_SETVLCPARAM                         = 225,      /**<VLC����*/
    MESSAGE_CMD_GETNTPPARAM                         = 226,      /**<NTP����*/
    MESSAGE_CMD_SETNTPPARAM                         = 227,      /**<NTP����*/
    MESSAGE_CMD_GETBKDISK                           = 228,      /**<������Ӳ��*/
    MESSAGE_CMD_GETVIDEOINTERESTAREA                = 229,      /**<��Ƶ����Ȥ�������*/
    MESSAGE_CMD_SETVIDEOINTERESTAREA                = 230,      /**<��Ƶ����Ȥ�������*/
    MESSAGE_CMD_GETVCAABILITY                       = 231,      /**<֧�ֵ����ܷ�������*/
    MESSAGE_CMD_GETCCDPARAMEX                       = 232,      /**<Sensor����*/
    MESSAGE_CMD_SETCCDPARAMEX                       = 233,      /**<Sensor����*/
    MESSAGE_CMD_GETSTORAGE                          = 234,      /**<Ӳ������Ϣ(��)*/
    MESSAGE_CMD_SETSTORAGE                          = 235,      /**<Ӳ������Ϣ(��)*/
    MESSAGE_CMD_GETSMART                            = 236,      /**<Ӳ��smart��Ϣ(��)*/
    MESSAGE_CMD_GETEXACTTIMEZONE                    = 237,      /**<׼ȷ��ʱ��*/
    MESSAGE_CMD_SETEXACTTIMEZONE                    = 238,      /**<׼ȷ��ʱ��*/
    MESSAGE_CMD_GETTRAFFICLIGHTCFG                  = 239,      /**<���̵�����*/
    MESSAGE_CMD_SETTRAFFICLIGHTCFG                  = 240,      /**<���̵�����*/
    MESSAGE_CMD_GETRECORDSTREAMTYPE                 = 241,      /**<¼�����������*/
    MESSAGE_CMD_SETRECORDSTREAMTYPE                 = 242,      /**<¼�����������*/
    MESSAGE_CMD_GETWIFIMODE                         = 243,      /**<wifiģʽ*/
    MESSAGE_CMD_SETWIFIMODE                         = 244,      /**<wifiģʽ*/
    MESSAGE_CMD_GETALARMSHORTMSGPARAM               = 245,      /**<�������Ų���*/
    MESSAGE_CMD_SETALARMSHORTMSGPARAM               = 246,      /**<�������Ų���*/
    MESSAGE_CMD_GETNETERRORPARAM                    = 247,      /**<�����쳣��������*/
    MESSAGE_CMD_SETNETERRORPARAM                    = 248,      /**<�����쳣��������*/
    MESSAGE_CMD_GETDISKSELECTPARAM                  = 249,      /**<�豸�洢����*/
    MESSAGE_CMD_SETDISKSELECTPARAM                  = 250,      /**<�豸�洢����*/
    MESSAGE_CMD_GETDAYNIGHTPARAM                    = 251,      /**<��ҹת������*/
    MESSAGE_CMD_SETDAYNIGHTPARAM                    = 252,      /**<��ҹת������*/
    MESSAGE_CMD_GETVIDEOINTYPE                      = 253,      /**<��Ƶ�������*/
    MESSAGE_CMD_SETVIDEOINTYPE                      = 254,      /**<��Ƶ�������*/
    MESSAGE_CMD_GETWIFIENABLE                       = 255,      /**<wifi��3g֧����Ϣ*/
    MESSAGE_CMD_GETNOISEMODEPARAM                   = 256,      /**<�������*/
    MESSAGE_CMD_SETNOISEMODEPARAM                   = 257,      /**<�������*/
    MESSAGE_CMD_GETVPNINFO                          = 258,      /**<VPN����*/
    MESSAGE_CMD_SETVPNINFO                          = 259,      /**<VPN����*/
    MESSAGE_CMD_GETWIFIINFO                         = 260,      /**<wifi����*/
    MESSAGE_CMD_GETPHOTO_SENSITIVE_TYPE             = 261,      /**<������������*/
    MESSAGE_CMD_SETPHOTO_SENSITIVE_TYPE             = 262,      /**<������������*/
    MESSAGE_CMD_GET_ENC_VPP_MAIN                    = 263,      /**<������ƵԤ��������*/
    MESSAGE_CMD_SET_ENC_VPP_MAIN                    = 264,      /**<������ƵԤ��������*/
    MESSAGE_CMD_SET_ENC_VPP_SUB                     = 265,      /**<������ƵԤ��������*/
    MESSAGE_CMD_GET_ENC_VPP_SUB                     = 266,      /**<������ƵԤ��������*/
    MESSAGE_CMD_SET_ENC_VPP_THIRD                   = 267,      /**<������ƵԤ��������*/
    MESSAGE_CMD_GET_ENC_VPP_THIRD                   = 268,      /**<������ƵԤ��������*/
    MESSAGE_CMD_SET_ENC_PROFILE_MAIN                = 269,      /**<���뼶������*/
    MESSAGE_CMD_GET_ENC_PROFILE_MAIN                = 270,      /**<���뼶������*/
    MESSAGE_CMD_SET_ENC_PROFILE_SUB                 = 271,      /**<���뼶������*/
    MESSAGE_CMD_GET_ENC_PROFILE_SUB                 = 272,      /**<���뼶������*/
    MESSAGE_CMD_SET_ENC_PROFILE_THIRD               = 273,      /**<���뼶������*/
    MESSAGE_CMD_GET_ENC_PROFILE_THIRD               = 274,      /**<���뼶������*/
    MESSAGE_CMD_GET_CCD_RGB_DEFAULT                 = 275,      /**<sensor��RGB����*/
    MESSAGE_CMD_SET_CCD_AI_CHECK                    = 276,      /**<AIУ��ֵ*/
    MESSAGE_CMD_GET_REMOTESTREAMTYPE                = 277,      /**<Զ�������ϴ�����������*/
    MESSAGE_CMD_SET_REMOTESTREAMTYPE                = 278,      /**<Զ�������ϴ�����������*/
    MESSAGE_CMD_GET_ENCRYPTIONTYPE                  = 279,      /**<���ܷ�ʽ(�ʼ�����)*/
    MESSAGE_CMD_SET_ENCRYPTIONTYPE                  = 280,      /**<���ܷ�ʽ(�ʼ�����)*/
    MESSAGE_CMD_GETSENSORPARAM_DEVTYPE              = 281,      /**<Զ�̲����е��豸����*/
    MESSAGE_CMD_SETSENSORPARAM_DEVTYPE              = 282,      /**<Զ�̲����е��豸����*/
    MESSAGE_CMD_GETDEVICECFG                        = 283,      /**<NVR��ģת������*/
    MESSAGE_CMD_SETDEVICECFG                        = 284,      /**<NVR��ģת������*/
    MESSAGE_CMD_GETCHANNELRECORDPLANEX              = 285,      /**<������ͨ������:¼��ƻ�*/
    MESSAGE_CMD_SETCHANNELRECORDPLANEX              = 286,      /**<������ͨ������:¼��ƻ�*/
    MESSAGE_CMD_GETMOTIONALARMAREA                  = 287,      /**<�ƶ��������*/
    MESSAGE_CMD_SETMOTIONALARMAREA                  = 288,      /**<�ƶ��������*/
    MESSAGE_CMD_GET_OSDBORDER                       = 289,      /**<OSD�߿����*/
    MESSAGE_CMD_SET_OSDBORDER                       = 290,      /**<OSD�߿����*/
    MESSAGE_CMD_GET_RESOLUTION                      = 291,      /**<����֧�ֵķֱ���*/
    MESSAGE_CMD_GET_QOS_TOS                         = 292,      /**<����ƵQOS���ȼ�*/
    MESSAGE_CMD_SET_QOS_TOS                         = 293,       /**<����ƵQOS���ȼ�*/
    MESSAGE_CMD_GET_SNMP_CFG                        = 294,      /**<SNMP����*/
    MESSAGE_CMD_SET_SNMP_CFG                        = 295,      /**<SNMP����*/
    MESSAGE_CMD_GET_IPV6_CFG                        = 296,      /**<����IPV6*/
    MESSAGE_CMD_SET_IPV6_CFG                        = 297,      /**<����IPV6*/
    MESSAGE_CMD_GET_SENSORVERSION                   = 298,      /**<��ȡSensor�汾��*/
    MESSAGE_CMD_GET_WINCALIPARAM                    = 299,      /**<���ڲ�������*/
    MESSAGE_CMD_SET_WINCALIPARAM                    = 300,      /**<���ڲ�������*/
    MESSAGE_CMD_GET_SMT_ANALY_ADVANCE               = 301,      /**<���ܷ���-�߼�����*/
    MESSAGE_CMD_SET_SMT_ANALY_ADVANCE               = 302,      /**<���ܷ���-�߼�����*/
    MESSAGE_CMD_GET_DAYNIGHTPARAM_EX                = 303,      /**<��ҹ����*/
    MESSAGE_CMD_SET_DAYNIGHTPARAM_EX                = 304,      /**<��ҹ����*/
    MESSAGE_CMD_GET_IROSD2VISPARAM                  = 305,      /**<�ɼ�����Ӳ���osd����*/
    MESSAGE_CMD_SET_IROSD2VISPARAM                  = 306,      /**<�ɼ�����Ӳ���osd����*/
    MESSAGE_CMD_GET_CHANNELTYPE                     = 307,      /**<ͨ������*/
    MESSAGE_CMD_GET_ANTIFLICKER                     = 308,      /**<��������*/
    MESSAGE_CMD_SET_ANTIFLICKER                     = 309,      /**<��������*/
    MESSAGE_CMD_GET_TEMPREGIONOFFSET                = 310,      /**<������λ��ƫ��(�ɼ���ͨ����Ч)*/
    MESSAGE_CMD_SET_TEMPREGIONOFFSET                = 311,      /**<������λ��ƫ��(�ɼ���ͨ����Ч)*/
    MESSAGE_CMD_GET_TEMPVALUE_EX                    = 312,      /**<�����¶�ֵ(��չ)*/
    MESSAGE_CMD_GET_SENSOR_SERIALNO                 = 313,      /**<��ȡsensor���к�                                 */
    MESSAGE_CMD_SET_SENSOR_SERIALNO                 = 314,      /**<����sensor���к�                                 */
    MESSAGE_CMD_GET_SWITCHMODE                      = 315,      /**<�л�У׼ģʽ                                     */
    MESSAGE_CMD_SET_SWITCHMODE                      = 316,      /**<�л�У׼ģʽ                                     */
    MESSAGE_CMD_TAU_FACDEFAULT                      = 317,      /**<TAU�ָ�Ĭ��                                      */
    MESSAGE_CMD_TAU_SAVEPARAM                       = 318,      /**<TAU�������                                      */
    MESSAGE_CMD_GET_TAU_SEGMENT                     = 319,      /**<TAU�α��                                        */
    MESSAGE_CMD_SET_TAU_SEGMENT                     = 320,      /**<TAU�α��                                        */
    MESSAGE_CMD_GET_HT_BLACK_CLIPPING               = 321,      /**<�ڱ߲ü�                                         */
    MESSAGE_CMD_SET_HT_BLACK_CLIPPING               = 322,      /**<�ڱ߲ü�                                         */
    MESSAGE_CMD_GET_DENOISEPARAM                    = 323,      /**<����                                             */
    MESSAGE_CMD_SET_DENOISEPARAM                    = 324,      /**<����                                             */
    MESSAGE_CMD_GET_ROLLPARAM                       = 325,      /**<��ת                                             */
    MESSAGE_CMD_SET_ROLLPARAM                       = 326,      /**<��ת                                             */
    MESSAGE_CMD_GET_DIGITALOUTMODE                  = 327,      /**<�������ģʽ                                     */
    MESSAGE_CMD_SET_DIGITALOUTMODE                  = 328,      /**<�������ģʽ                                     */
    MESSAGE_CMD_GET_FFCMODE                         = 329,      /**<FFCģʽ                                          */
    MESSAGE_CMD_SET_FFCMODE                         = 330,      /**<FFCģʽ                                          */
    MESSAGE_CMD_GET_FFCFRAMEPARAM                   = 331,      /**<�Զ�FFC֡������                                  */
    MESSAGE_CMD_SET_FFCFRAMEPARAM                   = 332,      /**<�Զ�FFC֡������                                  */
    MESSAGE_CMD_GET_FFCTEMPPARAM                    = 333,      /**<�Զ�FFC�¶Ȳ���                                  */
    MESSAGE_CMD_SET_FFCTEMPPARAM                    = 334,      /**<�Զ�FFC�¶Ȳ���                                  */
    MESSAGE_CMD_GET_VTEMPTEMP                       = 335,      /**<VTEMP�¶Ȳ���                                    */
    MESSAGE_CMD_SET_VTEMPTEMP                       = 336,      /**<VTEMP�¶Ȳ���                                    */
    MESSAGE_CMD_GET_VTEMPREGION                     = 337,      /**<VTEMP�������                                    */
    MESSAGE_CMD_SET_VTEMPREGION                     = 338,      /**<VTEMP�������                                    */
    MESSAGE_CMD_GET_KENABLE                         = 339,      /**<Kֵ��Ч                                          */
    MESSAGE_CMD_SET_KENABLE                         = 340,      /**<Kֵ��Ч                                          */
    MESSAGE_CMD_GET_BENABLE                         = 341,      /**<Bֵ��Ч                                          */
    MESSAGE_CMD_SET_BENABLE                         = 342,      /**<Bֵ��Ч                                          */
    MESSAGE_CMD_GET_BLINDENABLE                     = 343,      /**<äԪ��Ч                                         */
    MESSAGE_CMD_SET_BLINDENABLE                     = 344,      /**<äԪ��Ч                                         */
    MESSAGE_CMD_GET_FILTEENABLE                     = 345,      /**<ʱ���˲���Ч                                     */
    MESSAGE_CMD_SET_FILTEENABLE                     = 346,      /**<ʱ���˲���Ч                                     */
    MESSAGE_CMD_GET_FILTEPARAM                      = 347,      /**<ʱ���˲�ϵ��                                     */
    MESSAGE_CMD_SET_FILTEPARAM                      = 348,      /**<ʱ���˲�ϵ��                                     */
    MESSAGE_CMD_GET_TRAN                            = 349,      /**<͸��                                             */
    MESSAGE_CMD_SET_TRAN                            = 350,      /**<͸��                                             */
    MESSAGE_CMD_GET_SMART_DATA                      = 351,      /**<smartData����                                    */
    MESSAGE_CMD_SET_SMART_DATA                      = 352,      /**<smartData����                                    */
    MESSAGE_CMD_GET_SENSOR_TEMP                     = 353,      /**<��о�������¶�                                   */
    MESSAGE_CMD_SET_WRITE_FLASH                     = 354,      /**<�̻�flash                                        */
    MESSAGE_CMD_GET_SENSOR_STATE                    = 355,      /**<��ǰsensor״̬                                   */
    MESSAGE_CMD_GET_OBJTEMP_FLUXRANGE               = 356,      /**<�¶����ط�Χ                                     */
    MESSAGE_CMD_GET_TAUNUCTABLEINDEXES              = 357,      /**<��ȡ��ǰ֧�ֵ�NUC Table��������                  */
    MESSAGE_CMD_GET_TAUNUCTABLEFUNCTION             = 358,      /**<��ȡ��ǰTAU��֧�ֵ� NUC Table��⹦��            */
    MESSAGE_CMD_SET_TAUNUCTABLEFUNCTION             = 359,      /**<���õ�ǰTAU��֧�ֵ� NUC Table��⹦��            */
    MESSAGE_CMD_WNDCALIB_STARTUP                    = 360,      /**<����У׼ ����                                    */
    MESSAGE_CMD_WNDCALIB_CAPBASEDATA                = 361,      /**<ץȡ��N������Ļ�׼����                          */
    MESSAGE_CMD_WNDCALIB_CAPOBJDATA                 = 362,      /**<ץȡ��N�������Ŀ������                          */
    MESSAGE_CMD_WNDCALIB_CALC                       = 363,      /**<���㴰��У׼ϵ��                                 */
    MESSAGE_CMD_GET_WEBROMVER                       = 364,      /**<��ȡ��ҳ(ROM)�汾                                */
    MESSAGE_CMD_FILLLIGHT_ON                        = 365,      /**<����ƿ���                                       */
    MESSAGE_CMD_FILLLIGHT_OFF                       = 366,      /**<����ƹر�                                       */
    MESSAGE_CMD_GET_ONVIFPARAM                      = 367,      /**<onvif����                                        */
    MESSAGE_CMD_SET_ONVIFPARAM                      = 368,      /**<onvif����                                        */
    MESSAGE_CMD_GET_IMAGEFUSEPARAM_EX               = 369,      /**<ͼ���ںϲ���                                     */
    MESSAGE_CMD_SET_IMAGEFUSEPARAM_EX               = 370,      /**<ͼ���ںϲ���                                     */
    MESSAGE_CMD_GET_FUSEOFFSET                      = 371,      /**<�ں�ƫ��                                         */
    MESSAGE_CMD_SET_FUSEOFFSET                      = 372,      /**<�ں�ƫ��                                         */
    MESSAGE_CMD_GET_IMAGEFLIPPARAM                  = 373,      /**<ͼ��ת����                                     */
    MESSAGE_CMD_SET_IMAGEFLIPPARAM                  = 374,      /**<ͼ��ת����                                     */
    MESSAGE_CMD_GET_PIXLETEMPERATURE                = 375,      /**<��ȡ���ص���¶�                                 */
    MESSAGE_CMD_SET_PIXLETEMPERATURE                = 376,      /**<�������ص�λ��                                   */
    MESSAGE_CMD_GET_POLYGONTEMPPARAM                = 377,      /**<��ȡ����β��¶���β���                         */
    MESSAGE_CMD_SET_POLYGONTEMPPARAM                = 378,      /**<���ö���β��¶���β���                         */
    MESSAGE_CMD_GET_HUMANCALIPARAM                  = 379,      /**<�������У׼����                                 */
    MESSAGE_CMD_SET_HUMANCALIPARAM                  = 380,      /**<�������У׼����                                 */
    MESSAGE_CMD_GET_TEMPSHIELDPARAM                 = 381,      /**<����������                                       */
    MESSAGE_CMD_SET_TEMPSHIELDPARAM                 = 382,      /**<����������                                       */
    MESSAGE_CMD_HUMANCALI_MANUAL                    = 383,      /**<�������У׼�����ֶ�                             */
    MESSAGE_CMD_HUMANCALI_RESTORE                   = 384,      /**<�������У׼�����ָ�                             */
    MESSAGE_CMD_GET_HUMANCALI_VISMATCHIR            = 385,      /**<����Ϳɼ���ͼ���Ӧ����(�ɼ���+������Ӧ����)    */
    MESSAGE_CMD_SET_HUMANCALI_VISMATCHIR            = 386,      /**<����Ϳɼ���ͼ���Ӧ����(�ɼ���+������Ӧ����)    */
    MESSAGE_CMD_GET_HUMANCALI_TEMPTABLE             = 387,      /**<�������У׼�¶ȱ�                               */
    MESSAGE_CMD_SET_HUMANCALI_TEMPTABLE             = 388,      /**<�������У׼�¶ȱ�                               */
    MESSAGE_CMD_GET_TEMPUNIT                        = 389,      /**<�¶ȵ�λ                                         */
    MESSAGE_CMD_SET_TEMPUNIT                        = 390,      /**<�¶ȵ�λ                                         */
    MESSAGE_CMD_GET_TEMPINFOLIST                    = 391,      /**<��ȡȫ�ֺ���������¶�ֵ��Ϣ                     */
    MESSAGE_CMD_GET_TEMPALARMCTRLEX                 = 392,      /**<���±�������(֧��4������)                        */
    MESSAGE_CMD_SET_TEMPALARMCTRLEX                 = 393,      /**<���±�������(֧��4������)                        */
    MESSAGE_CMD_GET_REGIONTEMPALARMCTRLEX           = 394,      /**<�����¶ȱ�������(֧��4������)                    */
    MESSAGE_CMD_SET_REGIONTEMPALARMCTRLEX           = 395,      /**<�����¶ȱ�������(֧��4������)                    */
    MESSAGE_CMD_GET_GB28181PARAM                    = 396,      /**<GB28181����*/
    MESSAGE_CMD_SET_GB28181PARAM                    = 397,      /**<GB28181����*/
    MESSAGE_CMD_GET_REGIONTEMPPARAM_EX2             = 398,      /**<������²���(֧��24������)*/
    MESSAGE_CMD_SET_REGIONTEMPPARAM_EX2             = 399,      /**<������²���(֧��24������)*/
    MESSAGE_CMD_GET_POLYGONTEMPPARAM_EX             = 400,      /**<����β��²���(֧��24������)*/
    MESSAGE_CMD_SET_POLYGONTEMPPARAM_EX             = 401,      /**<����β��²���(֧��24������)*/
    MESSAGE_CMD_GET_SMARTANALYSIS_ENABLE            = 402,      /**<���ܷ�������ʹ��*/
    MESSAGE_CMD_SET_SMARTANALYSIS_ENABLE            = 403,      /**<���ܷ�������ʹ��*/
    MESSAGE_CMD_GET_SMARTANALYSIS_ALARM             = 404,      /**<���ܷ�����������*/
    MESSAGE_CMD_SET_SMARTANALYSIS_ALARM             = 405,      /**<���ܷ�����������*/
    MESSAGE_CMD_GET_TEMPOSDMODE                     = 406,      /**<�¶�OSDģʽ*/
    MESSAGE_CMD_SET_TEMPOSDMODE                     = 407,      /**<�¶�OSDģʽ*/
    MESSAGE_CMD_GET_GPSINFO_ABIF                    = 408,      /**<GPS��Ϣ(ABIF)*/
    MESSAGE_CMD_GET_CENTER_OSD                      = 409,      /**<���ĵ�OSDʹ��*/
    MESSAGE_CMD_SET_CENTER_OSD                      = 410,      /**<���ĵ�OSDʹ��*/
    MESSAGE_CMD_PARAMDEFAULT_DEEP                   = 411,      /**<�ָ�Ĭ�ϲ���(���)*/
    MESSAGE_CMD_GET_ONVIFPORT                       = 412,      /**<onvif�˿ں�*/
    MESSAGE_CMD_SET_ONVIFPORT                       = 413,      /**<onvif�˿ں�*/
    MESSAGE_CMD_GET_DAYNIGHT_STATE                  = 414,      /**<��ҹ״̬*/
    MESSAGE_CMD_GET_FLAME_DETECT_PARAM              = 415,      /**<���������*/
    MESSAGE_CMD_SET_FLAME_DETECT_PARAM              = 416,      /**<���������*/
    MESSAGE_CMD_FLAME_DETECT_PARAM_RESET            = 417,      /**<�����������λ*/
	MESSAGE_CMD_SET_GRIDSPARAM                      = 418,      /**<���ƹ�����*/
	MESSAGE_CMD_GET_GRIDSPARAM                      = 419,      /**<���ƹ�����*/
	MESSAGE_CMD_GET_GETREGIONTEMPVALUE_EX2          = 420,      /**<��ȡ��������¶�ֵ(64������)*/
	MESSAGE_CMD_SET_MANUAL_FOCUS                    = 421,      /**<�ֶ��۽���ʼ*/
	MESSAGE_CMD_SET_MANUAL_FOCUS_STOP               = 422,      /**<�ֶ��۽�����*/
	MESSAGE_CMD_GET_FOCUSPOS                        = 423,      /**<��ȡ�۽�λ��*/
	MESSAGE_CMD_SET_FOCUSPOS                        = 424,      /**<���þ۽�λ��*/
	MESSAGE_CMD_SET_FOCUSCTRL                       = 425,      /**<�Զ��Խ�����*/
	MESSAGE_CMD_GET_IMGFREEZE                       = 426,      /**<��ȡͼ�񶳽����*/
	MESSAGE_CMD_SET_IMGFREEZE                       = 427,      /**<����ͼ�񶳽����*/
	MESSAGE_CMD_GET_EXPOSUREPARAMEX                 = 428,      /**<��ȡ�ع������չ*/
	MESSAGE_CMD_SET_EXPOSUREPARAMEX                 = 429,      /**<�����ع������չ*/
	MESSAGE_CMD_GETVIPARAM                          = 430,      /**<��ȡ��Ƶ����*/
	MESSAGE_CMD_SETVIPARAM                          = 431,      /**<������Ƶ����*/
	MESSAGE_CMD_GET_AGCPARAM_EX                     = 432,      /**<��ȡ����AGC����*/
	MESSAGE_CMD_SET_AGCPARAM_EX                     = 433,      /**<���ú���AGC����*/
	MESSAGE_CMD_GET_TEMPPARAM_EX                    = 434,      /**<��ȡ������ز���*/
	MESSAGE_CMD_SET_TEMPPARAM_EX                    = 435,      /**<���ò�����ز���*/
	MESSAGE_CMD_GET_GETREGIONTEMPVALUE_EX           = 436,      /**<��ȡ��������¶�ֵ(24������)*/

    MESSAGE_CMD_MAX                                 = 437,      /**<����*/
};

/**
 * @brief ��ʼ��SDK������SDK��Դ
 * @param[in] m_nMessage        Ӧ�ó����һ���û��Զ�����Ϣ
 * @param[in] m_hWnd            Ӧ�ó�����һ�����ھ��
 * @param[in] m_messagecallback ��Ϣ�ص������ӿ�
 * @param[in] context           �û�������
 * @param[in] key               �����ַ�����Ĭ��Ϊ��
 * @return 1-��ʾ�ɹ���0-��ʾʧ��
 * @note �豸���ӶϿ��������ӳɹ�����Ϣ����ͨ���ص�����m_messagecallback�첽֪ͨ
 * @see IRNET_ClientCleanup
 * @code 
 //�ص���������˵��
 hHandle [IN] ���Ӿ����IRNET_ClientStart����ֵ
 wParam  [IN] ����1
 lParam  [IN] ����2
 context [IN] �û������� 
 * @endcode
*/
CNET_APIIMPORT int  CALLINGCONVEN IRNET_ClientStartup(UINT m_nMessage,HWND m_hWnd,void (WINAPI *m_messagecallback)(IRNETHANDLE hHandle,WPARAM wParam,LPARAM lParam,void *context) = NULL,void *context = NULL, char *key = NULL);

/**
 * @brief ��ȡ��Ϣ
 * @param[in,out] m_sername  �豸����
 * @param[in,out] m_url      �豸IP��ַ
 * @param[in,out] m_port     �豸�˿�
 * @param[in,out] m_ch       �豸ͨ��
 * @param[in,out] wParam     ����Ϣ
 * @param[in,out] lParam     ����Ϣ
 * @return 1��ʾ�ɹ���0��ʾʧ��
*/
CNET_APIIMPORT int  CALLINGCONVEN IRNET_ClientReadMessage(char *m_sername,char *m_url,WORD *m_port,int *m_ch,WPARAM *wParam,LPARAM *lParam);

/**
 * @brief ����SDK�����豸�ĳ�ʱʱ��ͳ��Դ���
 * @param[in] m_waitnum  �ȴ�ʱ��(��)
 * @param[in] m_trynum   ���Դ���
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention ��Ҫ��m_waitnum��ֵ���õ�̫С�����ͨ��internet���ӷ��������п��ܻ�����ʧ��
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientWaitTime(int m_waitnum = 6, int m_trynum = 3);

/**
 * @brief ж�ؿͻ���SDK���ͷ�SDK��Դ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStartup
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientCleanup();

///////////////ͼ����ʾ///////////////////
/**
 * @brief ���豸�������ӣ���ʵʱԤ��ͼ��
 * @param[in] m_url       �豸��IP��ַ��ת����������IP��ַ
 * @param[in] m_pChaninfo CHANNEL_CLIENTINFO��ָ��
 * @param[in] wserport    �豸��ת���������Ķ˿ں�
 * @param[in] streamtype  ���ӵ���������,0:������ 1:������,������Ҫ�豸֧�֣�Ĭ��Ϊ������
 * @return -1��ʾʧ�ܣ�����ֵΪ���Ӿ��
 * @see IRNET_ClientStop
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientStart(char *m_url,CHANNEL_CLIENTINFO *m_pChaninfo,WORD wserport = 3000,int streamtype = 0);

/**
 * @brief ֹͣ���ţ��Ͽ����豸������
 * @param hHandle [IN] ���Ӿ����IRNET_ClientStart�ķ���ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientStop(IRNETHANDLE hHandle);

/**
 * @brief ����ͼ����ʾ
 * @param[in] hHandle    IRNET_ClientStart�ķ���ֵ
 * @param[in] decodesign �ͷŽ�������Դ��־��1���ͷŽ�������Դ��0�����ͷŽ�������Դ��
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @note ������ͨ��ʱ���m_playstartΪFALSE������Ҫ�ֶ����øýӿ���ʵ��ͼ�����ʾ
 * @see IRNET_ClientStopView,IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientStartView(IRNETHANDLE hHandle, BOOL decodesign = TRUE);

/**
 * @brief ֹͣͼ����ʾ
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStartView,IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientStopView(IRNETHANDLE hHandle);

/**
 * @brief ����ͼ����ʾ�Ĵ���
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @param[in] hWnd    ͼ�񴰿�
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSetWnd(IRNETHANDLE hHandle,HWND hWnd);

/**
 * @brief ˢ��ͼ����ʾ�Ĵ��� 
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @param[in] rect    ����ˢ�������Ժ���ʾ��ͼ���ڸ�������ʾ��
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientRefrenshWnd(IRNETHANDLE hHandle,RECT *rect = NULL);

/**
 * @brief ����ͼ����ӳ�ʱ�� 
 * @param[in] hHandle   IRNET_ClientStart�ķ���ֵ
 * @param[in] delaytime �ӳ�ʱ�䣬��λΪ֡,0:����ʱ��1-100Ϊ��ʱʱ�䣬ֵԽ����ʱԽ��ͼ��������Ը���
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSetDelayTime(IRNETHANDLE hHandle, int delaytime);

/**
 * @brief ����ͼ�������
 * @param[in] hHandle  IRNET_ClientStart�ķ���ֵ
 * @param[in] bsplit   ��ֹ������־
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientPreventImageSplit(IRNETHANDLE hHandle, BOOL bsplit);

/**
 * @brief ��ȡͼ��ߴ� 
 * @param[in]  hHandle   IRNET_ClientStart�ķ���ֵ
 * @param[out] m_pWidth  ���صĿ��
 * @param[out] m_pHeight ���صĸ߶�
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientGetVideoSize(IRNETHANDLE hHandle, DWORD *m_pWidth, DWORD *m_pHeight);

/**
 * @brief �����Ƿ���ʾͼ�� 
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @param[in] bShow   TRUE����ʾ��Ƶ�� FALSE������ʾ��Ƶ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSetImageShow(IRNETHANDLE hHandle, BOOL bShow);

/**
 * @brief ��ȡ�ͻ���״̬
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @return ������:\n
    -1 ���������豸,�м�״̬\n 
 -1000 ��Ч��hHandle\n
    0  �ɹ�\n
    1  �û�ֹͣԤ��\n
    2  ���豸������ʧ��\n
    3  �豸�Ͽ�\n
    4  �ﶨ�˿�ʧ�ܣ����öಥ��������ʱ���������豸�Ķಥ�˿���ͬ������ָô���\n
    5  �����ڴ�ʧ�ܣ�����ϵͳ��Դʧ�ܣ��󶨶˿�ʧ�ܵ�\n
    6  ��������������ʧ��\n
 -102  �û����������\n
 -103  ϵͳ�û���Ա��ÿ���豸����û���Ϊ40\n
 -105  ͨ���û���Ա����TCP��UDP��ʽÿ��ͨ������������10���û�,�����豸��������40���û������ڶಥ��ʽ���ӣ��û�������������\n
 -106  ������û��ָ����ͨ��\n
 -112  û���ҵ�����������������ͨ��ת������������ʱ��û���ҵ�ָ���ķ���������\n
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT LONG  CALLINGCONVEN IRNET_ClientGetState(IRNETHANDLE hHandle);

/////////////////////////////////�ص�����///////////////////////
/**
 * @brief ������ʾ�Ļص�����
 * @param[in] hHandle      IRNET_ClientStart�ķ���ֵ
 * @param[in] ShowCallBack �ص�����
 * @param[in] context      �û�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @par �ص���������˵��:
 * @code
 m_y      Y������ʼ��ַ
 m_u      U������ʼ��ַ
 m_v      V������ʼ��ַ
 stridey  ����Y�Ŀ��
 strideuv ����U��V���ݵĿ��
 width    ͼ�����ݵĿ��
 height   ͼ�����ݵĸ߶�
 context  �û������������
 * @endcode
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientShowcallback(IRNETHANDLE hHandle, SHOWCALLBACK ShowCallBack ,void *context);

/**
 * @brief ������Ƶ����Ļص����� 
 * @param[in] hHandle          IRNET_ClientStart�ķ���ֵ
 * @param[in] AudioDecCallBack �ص�����
 * @param[in] context          �û�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @par �ص���������˵��:
 * @code
 pBuffer �������������
 size    ���ݳ���
 context �û������������
 * @endcode
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientAudioDeccallback(IRNETHANDLE hHandle,void(WINAPI *AudioDecCallBack)(char *pBuffer,int size,void *context),void *context);

/**
 * @brief ���û�ͼ�ص�����
 * @param[in] hHandle      IRNET_ClientStart�ķ���ֵ
 * @param[in] DrawCallBack �ص�����
 * @param[in] context      �û�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @par �ص���������˵��:
 * @code
 hdc     ͼԪ�ļ�
 context �û������������
 * @endcode
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientDrawCallBack(IRNETHANDLE hHandle,void(WINAPI *DrawCallBack)(HDC hDC,void *context),void *context);
/**
 * @brief ����ͼ����ʾ���򣨻ص���ʽ��
 * @param[in] hHandle      IRNET_ClientStart�ķ���ֵ
 * @param[in] DrawCallBack �ص�����
 * @param[in] context      �û�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @par �ص���������˵��:
 * @code
 hdc     ͼԪ�ļ�
 context �û������������
 * @endcode
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientShowImageDrawCallback(IRNETHANDLE hHandle, void(WINAPI *DrawCallBack)(HDC hDC, void *context), void *context);


///////////////////��̨/////////////////////////
/**
 * @brief ������̨
 * @param[in] hHandle   IRNET_ClientStart�ķ���ֵ
 * @param[in] type      ��̨������ PTZCtrlCode
 * @param[in] value     ���Ʋ���[1,10]
 * @param[in] priority  ��̨�������ȼ�����Ҫ�豸֧��
 * @param[in] extrabuff ��Ҫ�����豸�Ķ�������
 * @param[in] extrasize ��Ҫ�����豸�Ķ������ݴ�С
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart, PTZCtrlCode 
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientPTZCtrl(IRNETHANDLE hHandle,int type,int value,int priority = 0, char *extrabuff = NULL, int extrasize = 0);

/**
 * @brief ������̨��ַ
 * @param[in] hHandle   IRNET_ClientStart�ķ���ֵ
 * @param[in] m_ptzaddr ��̨��ַ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSetPTZAddr(IRNETHANDLE hHandle,BYTE m_ptzaddr);

////////////////¼����������///////////////////////////
/**
 * @brief ����Ԥ¼��
 * @param[in] hHandle      IRNET_ClientStart�ķ���ֵ
 * @param[in] m_benable    ʹ�ܱ�־
 * @param[in] m_buffsize   ��������С
 * @param[in] m_framecount �����֡��
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention �ڰ汾6.16D�Ժ󣬲���m_buffsize����ʹ�ã�ֻ��m_framecount��Ч���ڰ汾6.19.20�Ժ����ӳɹ����Զ���Ԥ¼��m_framecountΪ250֡,Ҫ�������ã�Ԥ¼������Ҫ��ֹͣ�����ò����������ر�Ԥ¼��¼���ļ��м���������ӵļ����
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientPrerecord(IRNETHANDLE hHandle,BOOL m_benable,int m_buffsize,int m_framecount);

/**
 * @brief ���ͨ������Ƶ��Ƶѹ����Ϣ
 * @param[in]       hHandle       IRNET_ClientStart�ķ���ֵ
 * @param[in,out]   m_pStreamInfo �ṹVSTREAMINFO��ָ��
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientGetStreamInfo(IRNETHANDLE hHandle,VSTREAMINFO *m_pStreamInfo);


/**
 * @brief �������ԭʼ����
 * @param[in] hHandle       IRNET_ClientStart�ķ���ֵ
 * @param[in] m_nomalvideo  �����Ƶ���ݵĻص�����
 * @param[in] pvideocontext ��Ƶ�û�������
 * @param[in] m_nomalaudio  �����Ƶ���ݵĻص�����
 * @param[in] paudiocontext ��Ƶ�û�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientStartNomalCap(IRNETHANDLE hHandle,
    ORIGINALVIDEO m_nomalvideo, void *pvideocontext,
    ORIGINALAUDIO m_nomalaudio,void *paudiocontext);

/**
 * @brief ֹͣ��ȡԭʼ����
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientStopNomalCap(IRNETHANDLE hHandle);

/**
 * @brief �����ʾ����
 * @param[in] hHandle IRNET_ClientStart�ķ���ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_CleanVideoDisplayBuffer(IRNETHANDLE hHandle);


////////////////////////OPT//////////////////////
/**
 * @brief ��Զ�̲�����������
 * @param[in] sername  ����������,С�ڵ���24���ַ���
 * @param[in] url      ��������ַ
 * @param[in] username �û�����С�ڵ���20���ַ�
 * @param[in] password ����,С�ڵ���20���ַ�
 * @param[in] serport  �������˿ں�
 * @return -1��ʾʧ�ܣ�����ֵΪ������ȡ���
 * @attention �ӿڵ��óɹ��󣬱������IRNET_ClientMessageClose�ͷ���Դ����������Դй©
 * @see IRNET_ClientMessageOpt,IRNET_ClientMessageClose
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientMessageOpen(char *sername, char *url, char *username, char *password, WORD serport = 3000);

/**
 * @brief ���ò���
 * @param[in]       hHandle ������ȡ�����IRNET_ClientMessageOpen����ֵ
 * @param[in]       opt     ����ѡ�� @ref MessageOpt
 * @param[in]       ch      ͨ��
 * @param[in,out]   param1  ��ȡ�����б�
 * @param[in,out]   param2  ��ȡ�����б�
 * @param[in,out]   param3  ��ȡ�����б�
 * @return δ������˵���£�TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientMessageOpen,IRNET_ClientMessageClose
*/
CNET_APIIMPORT int   CALLINGCONVEN IRNET_ClientMessageOpt(IRNETHANDLE hHandle, int opt, int ch = 0, void *param1 = NULL, void *param2 = NULL, void *param3 = NULL);

/**
 * @brief �ر�Զ�̲�����������
 * @param[in] hHandle ������ȡ�����IRNET_ClientMessageOpen����ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientMessageOpen,IRNET_ClientMessageOpt
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientMessageClose(IRNETHANDLE hHandle);


///////////�ض�Զ�̲�������///////////////////////////


/**
 * @brief ��ȡ�ݴ�����
 * @param[in]    m_sername  �豸����,С�ڵ���24���ַ���
 * @param[in]    m_url      �豸IP��ַ
 * @param[in]    m_username �û�����С�ڵ���20���ַ�
 * @param[in]    m_password ���룬С�ڵ���20���ַ�
 * @param[in,out] pbuff      ����ָ��
 * @param[in]    wserport   �豸�˿�
 * @return ���ڵ���0��ʾ�ɹ����������ݳ��ȣ�С��0��ʾʧ��
*/
CNET_APIIMPORT int   CALLINGCONVEN IRNET_ClientGetTempData(char *m_sername, char *m_url, char *m_username, char *m_password, char *pbuff, WORD wserport = 3000);

/**
 * @brief ���ö����½ӿڲ���
 * @param[in] m_sername  ����������,С�ڵ���24���ַ���
 * @param[in] m_url      ��������ַ
 * @param[in] m_username �û�����С�ڵ���20���ַ�
 * @param[in] m_password ����,С�ڵ���20���ַ�
 * @param[in] pbuff      ����ָ��
 * @param[in] size       ���ݳ��ȣ���*��*sizeof��char����
 * @param[in] wserport   �������˿�
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
*/
CNET_APIIMPORT BOOL  __stdcall IRNET_Set_Points_Param(char *m_sername,char *m_url,char *m_username,char *m_password,char *pbuff,int size,WORD wserport = 3000);

/**
 * @brief ��ȡ�����½ӿڲ���
 * @param[in]     m_sername  �豸����,С�ڵ���24���ַ���
 * @param[in]     m_url      �豸IP��ַ
 * @param[in]     m_username �û�����С�ڵ���20���ַ�
 * @param[in]     m_password ���룬С�ڵ���20���ַ�
 * @param[in,out] pbuff      ����ָ��
 * @param[in]     size       pbuff��С����*��*sizeof��char����
 * @param[in]     wserport   �豸�˿�
 * @return ���ڵ���0��ʾ�ɹ����������ݳ��ȣ�С��0��ʾʧ��
 * @attention 
*/
CNET_APIIMPORT int   CALLINGCONVEN IRNET_Get_Points_Param(char* m_sername, char* m_url, char* m_username, char* m_password, char* pbuff, int size, WORD wserport = 3000);
/**
 * @brief ��ȡ�����½ӿ��¶�
 * @param[in]    m_sername  �豸����,С�ڵ���24���ַ���
 * @param[in]    m_url      �豸IP��ַ
 * @param[in]    m_username �û�����С�ڵ���20���ַ�
 * @param[in]    m_password ���룬С�ڵ���20���ַ�
 * @param[in,out] pbuff     ����ָ��
 * @param[in]    size       pbuff��С����*��*sizeof��float����
 * @param[in]    wserport   �豸�˿�
 * @return ���ڵ���0��ʾ�ɹ����������ݳ��ȣ�С��0��ʾʧ��
*/
CNET_APIIMPORT int   CALLINGCONVEN IRNET_Get_Points_Temp(char* m_sername, char* m_url, char* m_username, char* m_password, char* pbuff, int size, WORD wserport = 3000);

/////////////////��������������////////////////////////////////
/**
* @brief �������
* @param[in] m_sername  �豸���ƣ�С�ڵ���24�ַ�
* @param[in] m_url      �豸IP��ַ
* @param[in] m_username �û�����С�ڵ���20�ַ�
* @param[in] m_password ���룬С�ڵ���20�ַ�
* @param[in] wserport   �豸�˿ں�
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention ����޸��˲��������Ҫ���ñ��������Ҫ���øú�����Ĭ������������˲���δ����Ļ�������h��ỹԭ�ϴα���Ĳ���
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSaveServerPara(char *m_sername, char *m_url, char *m_username, char *m_password, WORD wserport = 3000);


/////////////�������ļ�����//////////////////


/**
 * @brief ����Զ�������豸�̼�
 * @param[in] m_url       �豸IP��ַ
 * @param[in] m_username  �û�����С�ڵ���20���ַ�
 * @param[in] m_password  ���룬С�ڵ���20���ַ�
 * @param[in] m_filename  �̼��ļ���
 * @param[in] m_hEndEvent �豸���������¼�(�����linuxƽ̨����HANDLEӦ����LINUX_EVENT_HANDLE)
 * @param[in] wserport    �豸�˿ں�
 * @param[in] m_sername   �豸����
 * @return -1��ʧ�ܣ�����ֵ��ΪIRNET_ClientUpdateStop�Ĳ���
 * @see IRNET_ClientUpdateStop
 * @attention �ýӿڵ��ú�һ��Ҫ����IRNET_ClientUpdateStop�ͷ���Դ
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientUpdateStart(char *m_url, char *m_username, char *m_password, char *m_filename, HANDLE m_hEndEvent, WORD wserport = 3000, char *m_sername = NULL);

/**
 * @brief ����Զ�������豸�̼�
 * @param hHandle [IN] IRNET_ClientUpdateStart�ķ���ֵ
 * @return 
 0�������ɹ�\n
 2������ʧ��\n
 -102��������û���������
 * @attention ��Ҫ�ȵ�m_hEndEvent���ٵ���IRNET_ClientUpdateStop������IRNET_ClientUpdateStop�ķ���ֵ�ж�������״̬��
 * @see IRNET_ClientUpdateStart
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientUpdateStop(IRNETHANDLE hHandle);



/**
 * @brief ��������
 * @param[in] hHandle  IRNET_ClientStart�ķ���ֵ
 * @param[in] m_Volume ���õ�������ֵ��ȡֵ��Χ��0x0000-0xffff:0x0000������0xffff�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention �������ڹ���ģʽ��ʹ�õģ���ÿ��ͨ���ڿ�������������ֹͣ���������ú���IRNET_ClientAudioVolume���Զ�������
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientAudioVolume(IRNETHANDLE hHandle, WORD m_Volume);



/**
 * @brief ����ͼ��Ԥ������
 * @param[in] hHandle ͨ�����Ӿ����IRNET_ClientStart�ķ���ֵ
 * @param[in] pRect   �������򣬸���ͼ��ֱ������Ϊ(0,0,width,height)
 * @param[in] bEnable ʹ�ܿ���
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart,IRNET_ClientElectronicZoomMoveEnable
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSetZoomRect(IRNETHANDLE hHandle, RECT *pRect, BOOL bEnable);

/**
 * @brief �����豸���»�����Ϣ
 * @param[in] hHandle       ���Ӿ����IRNET_ClientStart�ķ���ֵ
 * @param[in] devInfo       �豸������Ϣ
 * @param[in] DeviceMode    ʹ���豸ģʽ(FALSE-ʹ��PC�˵Ĳ���,TRUE-ʹ���豸�˵Ĳ���)
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetDevInfo(IRNETHANDLE hHandle, DEV_ENV_INFO* devInfo, BOOL DeviceMode = FALSE);

/**
* @brief ��ȡ�豸���»�����Ϣ
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] devInfo    �豸������Ϣ
* @param[in] DeviceMode ʹ���豸ģʽ(FALSE-ʹ��PC�˵Ĳ���,TRUE-ʹ���豸�˵Ĳ���)
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientGetDevInfo(IRNETHANDLE hHandle, DEV_ENV_INFO* devInfo, BOOL DeviceMode = FALSE);

/**
 * @brief ���ò����¿���Ϣ
 * @param[in] hHandle          ���Ӿ����IRNET_ClientStart�ķ���ֵ
 * @param[in] tempSpan         �¿���Ϣ
 * @param[in] DeviceMode       ʹ���豸ģʽ(FALSE-ʹ��PC�˵Ĳ���,TRUE-ʹ���豸�˵Ĳ���)
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetTempSpan(IRNETHANDLE hHandle, DEV_TEMP_SPAN* tempSpan, BOOL DeviceMode = FALSE);

/**
* @brief ��ȡ�����¿���Ϣ
* @param[in]        hHandle                 ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in,out]    tempSpan                �¿���Ϣ
* @param[in]        DeviceMode              ʹ���豸ģʽ(FALSE-ʹ��PC�˵Ĳ���,TRUE-ʹ���豸�˵Ĳ���)
* @return           TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientGetTempSpan(IRNETHANDLE hHandle, DEV_TEMP_SPAN* tempSpan, BOOL DeviceMode = FALSE);

/**
 * @brief ���õ�ɫ��ģʽ 
 * @param[in] hHandle       ���Ӿ����IRNET_ClientStart�ķ���ֵ
 * @param[in] enMode        ��ɫ��ģʽ
 * @param[in] DeviceMode    ʹ���豸ģʽ(FALSE-ʹ��PC�˵Ĳ���,TRUE-ʹ���豸�˵Ĳ���)
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention �豸�˵ĵ�ɫ���PC�˵ĵ�ɫ��֧�ֵ�������һ��,��ʵ�ʲ������Ϊ׼
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetPaletteMode(IRNETHANDLE hHandle, DEV_PALETTE_MODE enMode, BOOL DeviceMode = FALSE);

/**
* @brief ��ȡ��ɫ��ģʽ
* @param[in]        hHandle       ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in,out]    enMode        ��ɫ��ģʽ
* @param[in]        DeviceMode    ʹ���豸ģʽ(FALSE-ʹ��PC�˵Ĳ���,TRUE-ʹ���豸�˵Ĳ���)
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention �豸�˵ĵ�ɫ���PC�˵ĵ�ɫ��֧�ֵ�������һ��,��ʵ�ʲ������Ϊ׼
* @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientGetPaletteMode(IRNETHANDLE hHandle, DEV_PALETTE_MODE* enMode, BOOL DeviceMode = FALSE);

/**
 * @brief ע����»ص�
 * @param[in]       hHandle			���Ӿ����IRNET_ClientStart�ķ���ֵ
 * @param[in]       pCallBack		�ص�������ַ
 * @param[in,out]   tempSpan		�¿�
 * @param[in]       context			�Զ�������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientRegTempCallBack(IRNETHANDLE hHandle, TEMPCALLBACK pCallBack, DEV_TEMP_SPAN*tempSpan, void*context);

/**
* @brief ע���ȡ����ͨ����raw���ݻص�
* @param[in] hHandle     ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] pFunc       �ص�������ַ
* @param[in] context     ����
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientRegRawCallback(IRNETHANDLE hHandle, RAWCALLBACK pFunc, void* context);

/**
* @brief ��ȡ�����¶�ֵ
* @param[in] hHandle         ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] tempValue       �����¶�ֵ
* @param[in] DeviceMode      ʹ���豸ģʽ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @deprecated �˽ӿڷ���,��MESSAGE_CMD_GET_TEMPVALUE_EX�����ȡ ,IRNET_ClientMessageOpen,IRNET_ClientMessageOpt,IRNET_ClientMessageClose 
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientGetTemperatureValue(IRNETHANDLE hHandle, VSNETTEMPVALUE * tempValue, BOOL DeviceMode = FALSE);

/**
 * @brief ����ͼ��ץ��
 * @param[in]       hHandle       ���Ӿ����IRNET_ClientStart�ķ���ֵ
 * @param[in]       type          �ļ����͡�ΪEN_FT_SDK_LCRʱ��dataAddr��ʾ�¶�����
 * @param[in]       fileName      �ļ���(·��+�ļ���+�ļ���չ��)
 * @param[in]       quality       ͼ������(0-100)
 * @param[in,out]   dataAddr      ͼ�����ݵ�ַ(�ⲿ�����ڴ�) 
 * @param[in,out]   dataSize      ���ݴ�С(�ⲿ������ڴ����Ϊ:����ߡ�3Bytes,��typeΪEN_FT_SDK_LCRʱ��������ڴ��СΪ ����ͼ��Ŀ������ͼ��ĸߡ�sizeof(float) )���ɹ����޸�Ϊʵ�����ݴ�С,�����޸�Ϊ0����ζ���ⲿ�����ڴ治��
 * @return ������(@ref CaptureErrCode)
 * @attention ����ͼ��ץ����Ҫ��������������,�����޷�ץ��
 * @attention typeΪEN_FT_SDK_LCRʱ��dataAddr��ʾ�¶�����
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientCapture(IRNETHANDLE hHandle, FileType type, char fileName[], int quality = 100, char* dataAddr = NULL, unsigned int* dataSize = 0);

/**
* @brief �����豸JPEGץ�Ļش�
* @param[in] m_sername        ���������ƣ�С�ڵ���24�ַ�
* @param[in] m_url            ��������ַ
* @param[in] m_username       �����û�����С�ڵ���20�ַ�
* @param[in] m_password       �������룬С�ڵ���20�ַ�
* @param[in] wserport         ���Ӷ˿�
* @param[in] jpegdatacallback �ش��ص�����
* @param[in] userdata         �û��Զ������
* @return -1 ����ʧ��\n
* @see IRNET_ClientJpegCapSingle,IRNET_ClientJpegCapSingleEx,IRNET_ClientJpegCapStop
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientJpegCapStart(char *m_sername,
    char *m_url,
    char *m_username,
    char *m_password,
    WORD wserport,
    pfJpegdataCallback jpegdatacallback,
    void *userdata);

/**
* @brief �����豸JPEGץ�Ļش�
* @param[in] m_sername        ���������ƣ�С�ڵ���24�ַ�
* @param[in] m_url            ��������ַ
* @param[in] m_username       �����û�����С�ڵ���20�ַ�
* @param[in] m_password       �������룬С�ڵ���20�ַ�
* @param[in] wserport         ���Ӷ˿�
* @param[in] jpegdatacallback �ش��ص�����
* @param[in] userdata         �û��Զ������
* @return -1 ����ʧ��\n
* @see IRNET_ClientJpegCapSingle,IRNET_ClientJpegCapSingleEx,IRNET_ClientJpegCapStop
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientJpegCapStartGeneral(char *m_sername,
    char *m_url,
    char *m_username,
    char *m_password,
    WORD wserport,
    pfJpegdataCallbackGeneral jpegdatacallback,
    void *userdata);

/**
* @brief ����һ���豸ץͼ�ش�
* @param[in] hHandle   ���Ӿ����IRNET_ClientJpegCapStart����ֵ
* @param[in] m_ch      ����ͨ��
* @param[in] m_quality JPEGѹ������(1:���-100:���)
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientJpegCapStart,IRNET_ClientJpegCapSingleEx,IRNET_ClientJpegCapStop
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientJpegCapSingle(IRNETHANDLE hHandle, int m_ch, int m_quality);

/**
* @brief ����һ���豸ץͼ�ش�
* @param[in] hHandle   ���Ӿ����IRNET_ClientJpegCapStart����ֵ
* @param[in] m_ch      ����ͨ��
* @param[in] m_quality JPEGѹ������(1:���-100:���)
* @param[in] type      ץ������ 0x1-�ɼ��� 0x10-����   ����ֵ��Ч
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention ĳЩ�豸��֧��type��������Uranus��ͨ����IRNET_ClientJpegCapSingle
* @see IRNET_ClientJpegCapStart,IRNET_ClientJpegCapSingle,IRNET_ClientJpegCapStop
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientJpegCapSingleEx(IRNETHANDLE hHandle, int m_ch, int m_quality, int type);

/**
* @brief ֹͣ�豸JPEGץͼ�ش�
* @param[in] hHandle ���Ӿ����IRNET_ClientJpegCapStart����ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientJpegCapStart,IRNET_ClientJpegCapSingle,IRNET_ClientJpegCapSingleEx
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientJpegCapStop(IRNETHANDLE hHandle);

/**
* @brief ¼��ʼ
* @param[in] hHandle     ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] filename    �ļ���(·��+�ļ���+��չ��)
* @param[in] filetype    �ļ�����
* @param[in] framerate   ֡��(һ��ɼ���ͨ����30������ͨ����9)
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientRecordEnd
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientRecordBegin(IRNETHANDLE hHandle, char filename[], RecordType filetype, float framerate);

/**
* @brief ¼����ͣ
* @param[in] hHandle     ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientRecordBegin,IRNET_ClientRecordEnd
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientRecordPause(IRNETHANDLE hHandle);

/**
* @brief ¼��ָ�
* @param[in] hHandle     ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientRecordBegin,IRNET_ClientRecordEnd
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientRecordResume(IRNETHANDLE hHandle);

/**
* @brief ¼�����
* @param[in] hHandle     ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientRecordBegin
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientRecordEnd(IRNETHANDLE hHandle);

/**
* @brief �ں�ͼ��
* @param[in] hMainHandle ���Ӿ����IRNET_ClientStart�ķ���ֵ(����ͨ��)
* @param[in] hSubHandle  ���Ӿ����IRNET_ClientStart�ķ���ֵ(�ɼ���ͨ��)
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention ����ͨ����������raw�������������ӿڵ��óɹ���Ҳ���ں�Ч��
* @see IRNET_ClientFuseStop
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientFuseStart(IRNETHANDLE hMainHandle, IRNETHANDLE hSubHandle);

/**
* @brief ֹͣͼ���ں�
* @param[in] hHandle ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention ����hHandleֻ��Ҫ��IRNET_ClientFuseStart�е�hMainHandle��ͬһ������
* @see IRNET_ClientFuseStart
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientFuseStop(IRNETHANDLE hHandle);

/**
* @brief �����ں�ǿ��
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ(����ͨ��)
* @param[in] byStrength �ں�ǿ��0-100
* @param[in] DeviceMode ʹ���豸ģʽ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop,IRNET_ClientGetFusionStrength
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetFusionStrength(IRNETHANDLE hHandle, BYTE byStrength, BOOL DeviceMode = FALSE);

/**
* @brief ��ȡ�ں�ǿ��
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ(����ͨ��)
* @param[in] DeviceMode ʹ���豸ģʽ
* @return �ں�ǿ�� <0 ʧ�� ����ɹ�
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop,IRNET_ClientSetFusionStrength
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientGetFusionStrength(IRNETHANDLE hHandle, BOOL DeviceMode = FALSE);

/**
* @brief �����ں�ͼ��ɼ����ˮƽƫ��
* @param[in] hHandle ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] iOffset ˮƽƫ��
* @param[in] DeviceMode ʹ���豸ģʽ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop,IRNET_ClientGetFusionOffsetHorz
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetFusionOffsetHorz(IRNETHANDLE hHandle, int iOffset, BOOL DeviceMode = FALSE);

/**
* @brief ��ȡ�ں�ͼ��ɼ����ˮƽƫ��
* @param[in] hHandle ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] DeviceMode ʹ���豸ģʽ
* @return ˮƽƫ��
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop,IRNET_ClientSetFusionOffsetHorz
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientGetFusionOffsetHorz(IRNETHANDLE hHandle, BOOL DeviceMode = FALSE);
/**
* @brief �����ں�ͼ��ɼ���Ĵ�ֱƫ��
* @param[in] hHandle ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] iOffset ��ֱƫ��
* @param[in] DeviceMode ʹ���豸ģʽ
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop,IRNET_ClientGetFusionOffsetVert
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetFusionOffsetVert(IRNETHANDLE hHandle, int iOffset, BOOL DeviceMode = FALSE);
/**
* @brief ��ȡ�ں�ͼ��ɼ���Ĵ�ֱƫ��
* @param[in] hHandle ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] DeviceMode ʹ���豸ģʽ
* @return    ��ֱƫ��
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop,IRNET_ClientSetFusionOffsetVert
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientGetFusionOffsetVert(IRNETHANDLE hHandle, BOOL DeviceMode = FALSE);

/**
* @brief �����ں�ͼ����ͼģʽ
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] mode       ��ͼģʽ
* @param[in] DeviceMode ʹ���豸ģʽ 
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientFuseStart,IRNET_ClientFuseStop
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSetFusionViewMode(IRNETHANDLE hHandle, EnumViewMode mode, BOOL DeviceMode = FALSE);
/**
* @brief ע�����ּ��ص�
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] pFuncAddr  ���ֻص�
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention �˹�����ֻ֧��Linuxƽ̨
* @see IRNET_ClientIntrDetectBegin,IRNET_ClientIntrDetectEnd
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientRegIntrDetectCallback(IRNETHANDLE hHandle, INTRDETECCALLBACK pFuncAddr);

/**
* @brief ��ʼ���ּ��
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @param[in] areaUpper  ���������������
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention �˹�����ֻ֧��Linuxƽ̨
* @see IRNET_ClientIntrDetectEnd
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientIntrDetectBegin(IRNETHANDLE hHandle,int areaUpper);

/**
* @brief �������ּ��
* @param[in] hHandle    ���Ӿ����IRNET_ClientStart�ķ���ֵ
* @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention �˹�����ֻ֧��Linuxƽ̨
* @see IRNET_ClientIntrDetectBegin
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientIntrDetectEnd(IRNETHANDLE hHandle);

/**
* @brief �豸У׼
* @param[in] info       �豸������Ϣ
* @param[in] type       У׼����
* @param[in] filename   �ļ���
* @param[in] memaddr    �ڴ��ַ
* @param[in] memsize    �ڴ��С
* @param[in] group      ��
* @param[in] context    �Զ�������
* @param[in] pCallback  ������ɻص�

* @return -1��ʧ�ܣ�����ֵ>0:�ɹ�
* @attention ����filenameΪNULLʱ���Ż����memaddr
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_DevCalib(DeviceBaseInfo info, DevCalibType type, char *filename, unsigned char* memaddr = NULL, unsigned int memsize = 0, short group = 0, void* context = NULL, FINISHCALLBACK pCallback = NULL);

/**
 * @brief ע�������ͨ�����߼��ص�����
 * @param[in] pchancheck ������ͨ�����߼��ص����� 
 * @return    TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention �ڷ�����ͨ��ע��ص�������ֻ�ܵ���IRNET_RVSRegMsgCallback��IRNET_RVSSetChanServerID��IRNET_ClientMediaData��������
 ���ܵ�������SDK��������������SDK�����������������������Ҫ��������SDK��������ͨ����Ϣ�ص�������֪ͨ���ӳɹ����ٵ���
 * @see IRNET_RVSStartServer
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_RVSRegSerCheckCallback(RVSCHANNELCALLBACK pchancheck);

/**
 * @brief ������������������ע�����
 * @param[in] m_pRvsInfo �󶨼����˿���Ϣ��ָ��ṹVSNETRVSINFO��ָ��
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention �������ʹ��ת�������豸���ߺ����ʹ��IRNET_RVSSetChanServerID�����豸��ת���������е����֡�ת��������ο�IRNET_StartListenClient
 * @see IRNET_RVSStopServer
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_RVSStartServer(RVSINFOREG *m_pRvsInfo);

/**
 * @brief ע�������ͨ��������Ϣ�ص�����
 * @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
 * @param[in] palarmcallback ������������Ϣ�ص����� 
 * @param[in] context        �ص�����������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
  * @see IRNET_RVSStartServer,IRNET_RVSRegSerCheckCallback
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_RVSRegMsgCallback(IRNETHANDLE hHandle, RVSALARMCALLBACK palarmcallback, void *context);

/**
 * @brief ���÷�������ID����ID����ת��
 * @param[in] hHandle ͨ�����,IRNET_ClientStart�ķ���ֵ
 * @param[in] pSerID  ������ID����Ϊת���ķ�����Ψһ��ʶ�������ͻ�������ʱm_sername��Ϊ��ID
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @attention Ҫʹ�ÿͷ���ͨ��ת�����Ӹ��豸ʱ���豸���ƾ���pSerID���õ�ֵ��
  * @see IRNET_RVSStartServer,IRNET_RVSRegSerCheckCallback
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_RVSSetChanServerID(IRNETHANDLE hHandle, char *pSerID);

/**
* @brief ������ֹͣ���ݴ���
* @param[in] hHandle ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] bStart  TRUE���豸��������Ƶ����Ƶ���ݴ�������û���FALSE���豸ֹͣ���ݴ���
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @attention �ýӿ�ֻ�Ƕ���TCP��UDP����ʱ����ֹͣ���ݴ��䣬���ڶಥ����ֹͣ���ݴ��䣬�����������߳̿���������
* @see IRNET_RVSStartServer,IRNET_RVSRegSerCheckCallback
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientMediaData(IRNETHANDLE hHandle, BOOL bStart);

/**
 * @brief ֹͣ��������������ע�����
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_RVSStartServer
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_RVSStopServer();

/**
 * @brief ����ת������������
 * @param[in] m_pRedirect ָ��ṹIRNET_REDIRECTORINFO��ָ��
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_RVSStartServer
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_SetRedirectorInfo(IRNET_REDIRECTORINFO *m_pRedirect);

/**
 * @brief ����ת��������
 * @param[in] m_localAddrIP ������IP��ַ�����ΪNULL��SDK���Զ���ȡ����������IP��ַ����������ж��IP��ַ������ָ��һ��IP��ַ���м���
 * @return 0���ɹ� 4���ﶨ�˿ڴ��� 5�������ڴ����
 * @attention IRNET_RVSStartServer �����������豸����ע�����ߣ�Ҳ������ģʽ����IRNET_ClientStartNtFile ����������ͨ��ת������������ǰ���豸���ļ�����ת������������չ��Ŀǰֻ����ģʽ�Ͳ����豸֧��
 * @see IRNET_StopListenClient
*/
CNET_APIIMPORT int   CALLINGCONVEN IRNET_StartListenClient(char *m_localAddrIP = NULL);

/**
 * @brief ֹͣת��������
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_StartListenClient
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_StopListenClient();

///////////////////͸������///////////////////////////
/**
 * @brief ����͸����������
 * @param[in] m_sername           �豸���ƣ�С�ڵ���24���ַ�
 * @param[in] m_url               �豸��ַ
 * @param[in] m_username          �û�����С�ڵ���20���ַ�
 * @param[in] m_password          ���룬С�ڵ���20���ַ�
 * @param[in] iSerialPort         ���ںţ�0��RS485��1��RS232
 * @param[in] pSerialInfo         ���ڲ���
 * @param[in] fSerialDataCallBack ���ڽ��ջص�����
 * @param[in] context             �û�������
 * @param[in] wserport            �豸�˿�
 * @return -1������ʧ�ܣ���0��͸�����ھ��
 * @par VSSERIAL_INFO�ṹ 
 * @code
 typedef struct{
 int baudrate;       //������, 50,75,110,150,300,600,1200,2400,4800,9600,19200\n
 char databit;       //����λ, 5,6,7,8\n
 char stopbit;       //ֹͣλ, 1,2
 char checkbit;      //Ч��λ, 0-��У��,1-��У��,2-żУ��,3-�̶�Ϊ1��4-�̶�Ϊ0
 char flowcontrol;   //����, 0-������,1-������,2-Ӳ����
 }VSSERIAL_INFO;
 * @endcode
 * @par �ص���������˵��
 * @code

 * @endcode
 * @see IRNET_ClientSerialStop,IRNET_ClientSerialRecvRestart,IRNET_ClientSerialRecvPause,IRNET_ClientSerialSendNew
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientSerialStart(char *m_sername,char *m_url,char *m_username,char *m_password,int iSerialPort,
	VSSERIAL_INFO *pSerialInfo,
    pfSerialDataCallBack fSerialDataCallBack,
	void *context,WORD wserport);

/**
 * @brief �ر�͸����������
 * @param[in] hSerial ͸�����ھ����IRNET_ClientSerialStart����ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientSerialStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSerialStop(IRNETHANDLE hSerial);

/**
 * @brief ͨ��͸�����ڷ�������
 * @param[in] hSerial   ͸�����ھ����IRNET_ClientSerialStart����ֵ
 * @param[in] pSendBuff ��������ָ��
 * @param[in] BuffSize  ���ݳ���
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientSerialStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSerialSendNew(IRNETHANDLE hSerial,char *pSendBuff,DWORD BuffSize);

/**
 * @brief ͸�����ڽ���������ͣ
 * @param[in] hSerial ͸�����ھ����IRNET_ClientSerialStart����ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientSerialStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSerialRecvPause(IRNETHANDLE hSerial);

/**
 * @brief ͸�����ڽ����������¿�ʼ
 * @param[in] hSerial ͸�����ھ����IRNET_ClientSerialStart����ֵ
 * @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
 * @see IRNET_ClientSerialStart
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSerialRecvRestart(IRNETHANDLE hSerial);
/**
* @brief ������Ƶ
* @param[in] hHandle ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientStart,IRNET_ClientStopAudio
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientPlayAudio(IRNETHANDLE hHandle);
/**
* @brief ֹͣ��Ƶ
* @param[in] hHandle ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientStart,IRNET_ClientPlayAudio
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientStopAudio(IRNETHANDLE hHandle);

/**
* @brief ����rom
* @param[in] m_sername        �豸���ƣ�С�ڵ���24�ַ�
* @param[in] m_url            �豸IP��ַ
* @param[in] m_username       �����û�����С�ڵ���20�ַ�
* @param[in] m_password       �������룬С�ڵ���20�ַ�
* @param[in] m_wserport       ���Ӷ˿�
* @param[in] m_szRomPath      rom�ļ�·��
* @return void ��
* @attention ��Ҫ�ڶ��߳���ʹ�øýӿ�,�˽ӿ�Ϊ���̰߳�ȫ
* @see IRNET_GetUploadRomRst
*/
CNET_APIIMPORT void CALLINGCONVEN IRNET_StartUploadRom(char *m_sername, char *m_url, char *m_username, char *m_password, WORD m_wserport, char* m_szRomPath);

/**
 * @brief ��ȡrom����״̬
 * @return ״̬
2: "Ŀǰû�������¼�";\n
1: "��������";\n
0: "�����ɹ�";\n
-1: "��rom�ļ�ʧ��";\n
-2: "��ȡrom�ļ�ʧ��";\n
-3: "url��Ч";\n
-4: "����ʧ��";\n
-5:  "��������ʧ��";\n
-6: "�û����������";\n
-7: "�����߳�����ʧ��";\n
 	"��������
 * @see IRNET_StartUploadRom
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_GetUploadRomRst();
/**
* @brief �������õ�wifi
* @param[in] m_sername        �豸���ƣ�С�ڵ���24�ַ�
* @param[in] m_url            �豸IP��ַ
* @param[in] m_username       �����û�����С�ڵ���20�ַ�
* @param[in] m_password       �������룬С�ڵ���20�ַ�
* @param[in] m_pWifiList      wifi�б�
* @param[in] wserport       ���Ӷ˿�
* @return 0-ʧ��,����ɹ�
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientWifiSearch(char *m_sername, char *m_url, char *m_username, char *m_password, VSNETWIFISSIDLIST *m_pWifiList, WORD wserport);
/****----------���ܷ���--------------****/
/**
* @brief ���ܷ���ʹ��
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] bEnalbe    ʹ�� true-���� false-����
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientIntelligentAnalysisAddShield,IRNET_ClientIntelligentAnalysisGetShield,IRNET_ClientIntelligentAnalysisSetShield,IRNET_ClientIntelligentAnalysisDeleteShield,IRNET_ClientIntelligentAnalysisSaveShield
* @see IRNET_ClientIntelligentAnalysisTargetFilterCallback,IRNET_ClientIntelligentAnalysisSetMinTargetFilter,IRNET_ClientIntelligentAnalysisSetMaxTargetFilter,IRNET_ClientIntelligentAnalysisSaveTargetFilter
* @see IRNET_ClientIntelligentAnalysisAddCordon,IRNET_ClientIntelligentAnalysisGetCordon,IRNET_ClientIntelligentAnalysisSetCordon,IRNET_ClientIntelligentAnalysisCordonDirc,IRNET_ClientIntelligentAnalysisDeleteCordon,IRNET_ClientIntelligentAnalysisSaveCordon
* @see IRNET_ClientIntelligentAnalysisAddSmart,IRNET_ClientIntelligentAnalysisGetSmart,IRNET_ClientIntelligentAnalysisSetSmart,IRNET_ClientIntelligentAnalysisDeleteSmart,IRNET_ClientIntelligentAnalysisSaveSmart
* @attention ���ܷ���������ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisEnable(IRNETHANDLE hHandle, bool bEnalbe);
/**
* @brief ���������
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return ��ǰ����������
* @retval >= 0 ��ǰ����
* @retval <0 ʧ��
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientIntelligentAnalysisAddShield(IRNETHANDLE hHandle);
/**
* @brief ��ȡ����������
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return ����
* @retval >= 0 ��ǰ����
* @retval <0 ʧ��
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientIntelligentAnalysisGetShield(IRNETHANDLE hHandle);
/**
* @brief ���õ�ǰ����������������
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] regionIndex ��������
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSetShield(IRNETHANDLE hHandle, int regionIndex);
/**
* @brief ɾ��ָ����������
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] regionIndex ��������
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisDeleteShield(IRNETHANDLE hHandle, int regionIndex);
/**
* @brief ������������Ϣ
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSaveShield(IRNETHANDLE hHandle);
/**
* @brief ����Ŀ����˳ߴ�ص�(�����Ƴߴ��ʱ�����ߴ��С)
* @param[in] hHandle            ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] maxSizeCallback    ���ߴ�ص�
* @param[in] maxSizeContext     ���ߴ�ص����ӵ��Զ�������
* @param[in] minSizeCallback    ��С�ߴ�ص�
* @param[in] minSizeContext     ��С�ߴ�ص����ӵ��Զ�������
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisTargetFilterCallback(IRNETHANDLE hHandle, TargeFilterCallback maxSizeCallback, void* maxSizeContext, TargeFilterCallback minSizeCallback, void* minSizeContext);
/**
* @brief ������СĿ����˳ߴ�
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in,out] curWidth   ��ǰ�ߴ�Ŀ�(�ò�����ΪNULLʱ,�������ǰ�Ŀ�)
* @param[in,out] curHeight  ��ǰ�ߴ�ĸ�(�ò�����ΪNULLʱ,�������ǰ�ĸ�)
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSetMinTargetFilter(IRNETHANDLE hHandle, int * curWidth, int*curHeight);
/**
* @brief �������Ŀ����˳ߴ�
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in,out] curWidth   ��ǰ�ߴ�Ŀ�(�ò�����ΪNULLʱ,�������ǰ�Ŀ�)
* @param[in,out] curHeight  ��ǰ�ߴ�ĸ�(�ò�����ΪNULLʱ,�������ǰ�ĸ�)
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSetMaxTargetFilter(IRNETHANDLE hHandle, int * curWidth, int*curHeight);
/**
* @brief ����Ŀ����˳ߴ�
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @attention ���ߴ���������С�ߴ���������ܱ���
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSaveTargetFilter(IRNETHANDLE hHandle);
/**
* @brief ��Ӿ�����
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] arrowDir ��ͷ���� 0-�� 1-�� 2-˫��(����)
* @return ��ǰ�����ľ���������
* @retval >= 0 ��ǰ����
* @retval <0 ʧ��
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientIntelligentAnalysisAddCordon(IRNETHANDLE hHandle, int arrowDir);
/**
* @brief ��ȡ����������
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return ��ǰ����������
* @retval >= 0 ����
* @retval <0 ʧ��
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientIntelligentAnalysisGetCordon(IRNETHANDLE hHandle);
/**
* @brief ���õ�ǰ����������
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] regionIndex    ����
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSetCordon(IRNETHANDLE hHandle, int regionIndex);
/**
* @brief ���û��ȡ��ǰ�����߼�ⷽ��
* @param[in]     hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in]     isSet          ����   1-���� 0-��ȡ
* @param[in,out] cordonDirc     ��ǰ�����ߵķ��� 0-��� 1-�Ҳ� 2-����\n
                                ��isSet=1ʱ *cordonDircΪ������� ��0=isSetʱ cordonDirc�ɵ����߷����ڴ�
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisCordonDirc(IRNETHANDLE hHandle, BOOL isSet, int* cordonDirc);
/**
* @brief ɾ��ָ���ľ�����
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] regionIndex    ����
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisDeleteCordon(IRNETHANDLE hHandle, int regionIndex);
/**
* @brief ���澯������Ϣ
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSaveCordon(IRNETHANDLE hHandle );
/**
* @brief ������ܷ���(���޽��������뿪������Ʒ��������Ʒ��Ǩ)
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] smartType  ����,��Χ[EN_IAT_REGION_ENTRY,EN_IAT_GOODS_MOVE]
* @return ��ǰ���������ܷ�������
* @retval >= 0 ��ǰ����
* @retval <0 ʧ��
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientIntelligentAnalysisAddSmart(IRNETHANDLE hHandle, int smartType);
/**
* @brief ��ȡ������ܷ�������(���޽��������뿪������Ʒ��������Ʒ��Ǩ)
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] smartType  ����,��Χ[EN_IAT_REGION_ENTRY,EN_IAT_GOODS_MOVE]
* @return ���ܷ�������
* @retval >= 0 ����
* @retval <0 ʧ��
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientIntelligentAnalysisGetSmart(IRNETHANDLE hHandle, int smartType);
/**
* @brief ���õ�ǰ���ܷ�������
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] regionIndex    ����
* @param[in] smartType      ����,��Χ[EN_IAT_REGION_ENTRY,EN_IAT_GOODS_MOVE]
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSetSmart(IRNETHANDLE hHandle, int regionIndex, int smartType);
/**
* @brief ɾ����ǰ���ܷ���
* @param[in] hHandle        ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] regionIndex    ����
* @param[in] smartType      ����,��Χ[EN_IAT_REGION_ENTRY,EN_IAT_GOODS_MOVE]
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisDeleteSmart(IRNETHANDLE hHandle, int regionIndex, int smartType);
/**
* @brief �������ܷ���
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] smartType  ����,��Χ[EN_IAT_REGION_ENTRY,EN_IAT_GOODS_MOVE]
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientIntelligentAnalysisEnable
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientIntelligentAnalysisSaveSmart(IRNETHANDLE hHandle, int smartType);
/****----------���ܷ���--------------****/

/**
* @brief ���Ʊ�������豸
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] devCH      ���ͨ��
* @param[in] bOn        1-��,0-�ر�
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientOutPut(IRNETHANDLE hHandle, char devCH, BOOL bOn);

/**
* @brief ����rom(�ص�����)
* @param[in] upromhandle    ���,IRNET_UpgradeROM�ķ���ֵ
* @param[in] upromresult    rom�����Ľ��
* @param[in] userdata       �������Զ�������
* @return ��
* @note upromresult˵��\n
0�� �����ɹ�\n
-50:�ڴ治��\n
-49:�豸IP��ַΪ��\n
-48:�û���Ϊ��\n
-47:����Ϊ��\n
-46:rom�ļ�·��Ϊ��\n
-45:�̴߳���ʧ��\n
-44:�޷���rom�ļ�\n
-43:�ڴ治��,���ܴ����ļ�����\n
-42:�޷���ȡrom�ļ�������\n
-41:�豸IP��ַ��Ч\n
-40:�����豸ʧ��\n
-39:��������ʧ��\n
-38:�û��������벻ƥ��\n
����:δ֪����
* @see IRNET_UpgradeROM
*/
typedef void (CALLBACK* UpRomCallback)(IRNETHANDLE upromhandle, int upromresult, void* userdata);

/**
* @brief ����rom(֧�ֶ��߳�)
* @param[in] m_sername        �豸���ƣ�С�ڵ���24�ַ�
* @param[in] m_url            �豸IP��ַ
* @param[in] m_username       �����û�����С�ڵ���20�ַ�
* @param[in] m_password       �������룬С�ڵ���20�ַ�
* @param[in] m_wserport       ���Ӷ˿�
* @param[in] m_szRomPath      rom�ļ�·��
* @param[in] callback         ���������ص�����
* @param[in] userdata         �������Զ�������(����Ϊ�ص��������Զ������ݲ���)
* @return ���
* @retval -1:�ӿڵ���ʧ��,������óɹ�
* @note �˽ӿ�������óɹ�,��ͨ���ص������������������������������κνӿ�
*/
CNET_APIIMPORT IRNETHANDLE CALLINGCONVEN IRNET_UpgradeROM(char *m_sername, char *m_url, char *m_username, char *m_password, WORD m_wserport, char* m_szRomPath, UpRomCallback callback, void*userdata);

/**
* @brief ����(�ص�����)
* @param[in] upflashhandle    ���,IRNET_UpgradeFlash�ķ���ֵ
* @param[in] upflashresult    flash�����Ľ��
* @param[in] userdata       �������Զ�������
* @return ��
* @note upflashresult˵��\n
 0�� �����ɹ�\n
-2:��֧�ֵ�Э��\n
-3:�û��������벻ƥ��\n
-4:��������ʧ��\n
-5:�����豸ʧ��\n
-6:�豸IP��ַ��Ч\n
-7:�޷���ȡflash�ļ�������\n
-8:�ڴ治��,���ܴ����ļ�����\n
-9:�޷���flash�ļ�\n
-10:�̴߳���ʧ��\n
-11:flash�ļ�·��Ϊ��\n
-12:����Ϊ��\n
-13:�û���Ϊ��\n
-14:�豸IP��ַΪ��\n
-15:�ڴ治��\n
����:δ֪����
* @see IRNET_UpgradeFlash
*/
typedef void (CALLBACK* UpFlashCallback)(IRNETHANDLE upflashhandle, int upflashresult, void* userdata);

/**
* @brief ����flash
* @param[in] sername        �豸���ƣ�С�ڵ���24�ַ�
* @param[in] url            �豸IP��ַ
* @param[in] username       �����û�����С�ڵ���20�ַ�
* @param[in] password       �������룬С�ڵ���20�ַ�
* @param[in] wserport       ���Ӷ˿�
* @param[in] filepath       �ļ�·��
* @param[in] callback       ���������ص�����
* @param[in] userdata       �������Զ�������(����Ϊ�ص��������Զ������ݲ���)
* @return ���
* @retval -1:�ӿڵ���ʧ��,������óɹ�
* @note �˽ӿ�������óɹ�,��ͨ���ص����������������
*/
CNET_APIIMPORT IRNETHANDLE CALLINGCONVEN IRNET_UpgradeFlash(char *sername, char *url, char *username, char *password, WORD wserport, char* filepath, UpFlashCallback callback, void*userdata);
/**
* @brief ���ӷŴ��ƶ�ʹ��
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] bEnalbe    ʹ�� true-���� false-����
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientSetZoomRect
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientElectronicZoomMoveEnable(IRNETHANDLE hHandle, bool bEnalbe);
/**
* @brief ����β��»���(����α߿�)ʹ��
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] bEnalbe    ʹ��(0-����,����,ʹ��)
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientPolygonTempMeasureSetIndex,IRNET_ClientPolygonTempMeasureSave
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientPolygonTempMeasureDrawEnable(IRNETHANDLE hHandle, BOOL bEnalbe);
/**
* @brief ���ö���β�������
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] index      ����������()
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientPolygonTempMeasureDrawEnable,IRNET_ClientPolygonTempMeasureSave
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientPolygonTempMeasureSetIndex(IRNETHANDLE hHandle, int index);
/**
* @brief �����������ݵ��豸
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart,IRNET_ClientPolygonTempMeasureDrawEnable,IRNET_ClientPolygonTempMeasureSetIndex
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientPolygonTempMeasureSave(IRNETHANDLE hHandle);
/**
* @brief ����BMPץ��(�Ż�)
* @param[in] hHandle    ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in] m_filename ����ļ���
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @see IRNET_ClientStart
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientBMPOptimize(IRNETHANDLE hHandle, char const * m_filename);
typedef struct
{
#ifdef SYS_LINUX
	pthread_mutex_t mutex;
	pthread_cond_t	cond;
#endif
}*LINUX_EVENT_HANDLE;
/**
* @brief ��ȡ��ͷ���ʱͼ���ͼ���С
* @param[in]        hHandle     ͨ�����,IRNET_ClientStart�ķ���ֵ
* @param[in,out]    videoWidth  ��Ƶ��
* @param[in,out]    videoHeight ��Ƶ��
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @attention ��ͷ��⹦��������raw����
* @see IRNET_ClientStart,IRNET_ClientSetBodyTemperatureThreshold,IRNET_ClientHeadDetection
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientGetHeadDetectionVideoSize(IRNETHANDLE hHandle, int * videoWidth, int*videoHeight);
/*��ͷ������Ϣ*/
struct VSNET_HEADAREA
{
	int	iDetId;	///< �����ID
	int	x;		///< ���Ͻ�����X
	int	y;		///< ���Ͻ�����Y
	int	w;		///< ���ο��
	int	h;		///< ���θ߶�
	float temp; ///< �¶�
};
/**
* @brief ��ͷ������Ϣ�ص�
* @param[in] handle			VSNET_ClientStart�ķ���ֵ
* @param[in] headArea		��ͷ����
* @param[in] headAreaCnt	��ͷ������
* @param[in] context		�Զ�������
* @see IRNET_ClientStart
*/
typedef void (WINAPI*HeadAreaCallback)(IRNETHANDLE handle, VSNET_HEADAREA*headArea, int headAreaCnt,void*context);
/**
* @brief ��ͷ���ص�ע��
* @param[in] hHandle		ͨ�����
* @param[in] callbackfun	�ص�������ַ
* @param[in] context		�Զ�������
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @attention ��ͷ��⹦��������raw����
* @see IRNET_ClientStart,IRNET_ClientSetBodyTemperatureThreshold,IRNET_ClientGetHeadDetectionVideoSize
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientHeadDetection(IRNETHANDLE hHandle, HeadAreaCallback callbackfun, void*context);
/**
* @brief ���������ͷ�����¶�����
* @param[in] hHandle		ͨ�����
* @param[in] threshold		����
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @note ��������ʱ��ͷ�����ú�ɫ��ʾ,������ɫ��ʾ
* @attention ��ͷ��⹦��������raw����
* @see IRNET_ClientStart,IRNET_ClientHeadDetection,IRNET_ClientGetHeadDetectionVideoSize
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetBodyTemperatureThreshold(IRNETHANDLE hHandle, float threshold);
/**
* @brief �����������У������
* @param[in] hHandle		ͨ�����
* @param[in] par			У������
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @note ��raw������ͼ����Ϊ336����ʱ��Ч
* @see IRNET_ClientStart,IRNET_ClientGetBodyDisCorrParam
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientSetBodyDisCorrParam(IRNETHANDLE hHandle, VSNET_TED_CORRECTION_S*par);
/**
* @brief ��ȡ�������У������
* @param[in] hHandle		ͨ�����
* @param[in] par			У������
* @return �ɹ�����ʧ��
* @retval 0-ʧ��
* @retval 1-�ɹ�
* @note ��raw������ͼ����Ϊ336����ʱ��Ч
* @see IRNET_ClientStart,IRNET_ClientSetBodyDisCorrParam
* @attention �ýӿ���ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT BOOL CALLINGCONVEN IRNET_ClientGetBodyDisCorrParam(IRNETHANDLE hHandle, VSNET_TED_CORRECTION_S*par);
/**
 * @brief �����Խ�
 * @param[in] servername        �豸��
 * @param[in] url               IP��ַ
 * @param[in] username          �û���
 * @param[in] password          ����
 * @param[in] serport           �˿�
 * @param[in] talkcallback      �Խ��ص�
 * @param[in] samplerate        ������(Ĭ��8000)
 * @param[in] context           �û�������
 * @return �������
 * @retval -1-ֻ������һ���Խ�,-2-��Ƶ�ɼ�����ʧ��,-3-IP��ַ����,>0-��Ч���,-4-��֧�ֵĲ���ϵͳ
 * @see IRNET_ClientTalkStop
 * @attention ��ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT IRNETHANDLE CALLINGCONVEN IRNET_ClientTalkStart(char *servername,
    char *url,
    char *username,
    char *password,
    unsigned short serport,
    TALKCALLBACK talkcallback,
    int samplerate,
    void * context);
/**
 * @brief                   ֹͣ�Խ�
 * @param[in] talkhandle    �Խ����
 * @return                  �������
 * @retval                  1-�ɹ�,0-ʧ��
 * @see IRNET_ClientTalkStart
 * @attention ��ֻ֧��windowsƽ̨
*/
CNET_APIIMPORT int CALLINGCONVEN IRNET_ClientTalkStop(IRNETHANDLE talkhandle);

/**
* @brief ���α궨��ʼ(TM)
* @param[in] m_sername        ���������ƣ�С�ڵ���24�ַ�
* @param[in] m_url            ��������ַ
* @param[in] m_username       �����û�����С�ڵ���20�ַ�
* @param[in] m_password       �������룬С�ڵ���20�ַ�
* @param[in] wserport         ���Ӷ˿�
* @param[in] seccalibcallback У׼�ص�����
* @param[in] userdata         �û��Զ������
* @return -1 ����ʧ��
* @see IRNET_ClientSecondCalib4TmDo,IRNET_ClientSecondCalib4TmStop
*/
CNET_APIIMPORT IRNETHANDLE  CALLINGCONVEN IRNET_ClientSecondCalib4TmStart(char *m_sername,
    char *m_url,
    char *m_username,
    char *m_password,
    WORD wserport,
    pfSecondCalibTmCallback seccalibcallback,
    void *userdata);
/**
* @brief ���α궨ִ��(TM)
* @param[in] hHandle        ���Ӿ����IRNET_ClientSecondCalib4TmStart����ֵ
* @param[in] channel        ͨ����
* @param[in] calib_temp     �궨�¶�(��)
* @return 0��ʾ�ɹ��������ʾʧ��
* @see IRNET_ClientSecondCalib4TmStart,IRNET_ClientSecondCalib4TmStop
*/
CNET_APIIMPORT int  CALLINGCONVEN IRNET_ClientSecondCalib4TmDo(IRNETHANDLE hHandle, int channel, float calib_temp);
/**
* @brief ���α궨����(TM)
* @param[in] hHandle   ���Ӿ����IRNET_ClientSecondCalib4TmStart����ֵ
* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
* @see IRNET_ClientSecondCalib4TmStart,IRNET_ClientSecondCalib4TmDo
*/
CNET_APIIMPORT BOOL  CALLINGCONVEN IRNET_ClientSecondCalib4TmStop(IRNETHANDLE hHandle);
#endif//__IRNET_H__
