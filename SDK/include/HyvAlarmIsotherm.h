#pragma once
#include <winsock2.h>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>

#ifdef HYVSTREAM_EXPORTS
#define HYVSTREAM_API __declspec(dllexport)
#else
#define HYVSTREAM_API __declspec(dllimport)
#endif
#define TRANSPARENT_SERIAL_TCP_PORT	80
using namespace std;
class HYVSTREAM_API CHyvAlarmIsotherm
{
private:
	CHyvAlarmIsotherm(char *sIp);
	static string UtfToGbk(const char* utf8);
	// 参数sIp:要连接的服务端IP地址
	// 返回值0:成功，-1:失败,-2:失败，可需重新Connect
	int Connect();
	void Logout();
	string m_sIp;
	string m_sToken;
	SOCKET Socket;
public:
	// 创建对象
	static CHyvAlarmIsotherm* Create(char *sIp);

	//参数alarmEnable(报警使能开关) true:使能,false:关
	//参数isOthermEnable(等温线使能开关) true:使能,false:关
	//参数alarmType(报警类型) 0：无 1：低温报警 2：高温报警 3：高低温报警，
	//参数tempUp(高温阈值) 单位开尔文------要比低温阈值高，否则设置失败,0-16383(14bit)
	//参数tempLow(低温阈值) 单位开尔文--------要比高温阈值低，否则设置失败0-16383(14bit)
	//返回值0:成功,-1:失败
	int SetAlarmIsotherm(BOOL alarmEnable, BOOL isOthermEnable, int alarmType, int tempUp, int tempLow);

	//获取报警使能开关及等温线使能开关状态,报警类型,高低温阈值
	//获得的状态分别以字符串的形态存放在参数sAE,sIE中
	//获取的报警类型，高温阈值，低温阈值分别存放在pAlarmType,pTempUp,pTempLow中
	//返回值0：成功，-1:失败
	int GetAlarmIsotherm(char *sAE,char *sIE,char *pAlarmType,char *pTempUp,char *pTempLow);

	//设置温度数据开关及帧率
	//参数tempDataEnable(温度数据开关) true:使能,false:关
	//参数tempDataFps(温度数据帧率1-50)
	//返回值0:成功,-1:失败
	int SetTempDataParam(BOOL tempDataEnable, int tempDataFps);

	//获取温度数据开关及帧率
	//参数tempDataEnable(温度数据开关) true:使能,false:关
	//参数tempDataFps(温度数据帧率1-50)
	//返回值0:成功,-1:失败
	int GetTempDataParam(BOOL& tempDataEnable, int& tempDataFps);

	//获取系统版本号
	//sSystemVersion:要获取的系统版本号
	//返回值0:成功,-1:失败
	int GetSystemVersion(char *pSystemVersion);

	//关闭连接，销毁对象
	void Close();
};

