#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include "HyvSdk.h"
#include <vector>


using namespace std;


struct NetInfo
{
	string sIP;
	string sMac;
	string sSN;
};

class HYVSTREAM_API CHyvSNMac
{
private:
	CHyvSNMac();	
	int CheckIpMasksGateway(char *sIP,char *sMask,char *sGateway);	
#ifdef WIN32
#else
	struct sockaddr_in addrClient;	
#endif	
public:
	// 创建对象
	static CHyvSNMac * Create();
	// 查找设备信息
	// iOvertime:超时时间,单位毫秒
	// 返回值  0:成功  -1:失败  1:失败，重新查找
	int SearchDeviceAll(int iOvertime, vector <NetInfo>& netInfors);
	// 修改设备IP
	// sUsr:账户名,sPassword:密码,sSN:序列号(由GetSNMac获取), sNetName:网络名称(目前是"eth0")
	// sSourceIP:要修改的源IP地址,sDestIp:要修改的目标IP地址,sMask:子网掩码,sGateway:网关
	// 返回值-2:失败 -1:传入的子网掩码，网关，目标IP不匹配  1:修改失败 0:修改成功
	int Modify(char *sUsr, char *sPassword, char *sSN, char *sNetName, char *sSourceIP, char *sDestIP, char *sMask, char *sGateway);
	// 关闭，销毁对象
	void Close();
};