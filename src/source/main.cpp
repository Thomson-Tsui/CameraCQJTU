#include <iostream>
#include "WinSock2.h"
#include "InfraredTempSDK.h"


enum DeviceType { DEVICE_TYPE_A = 0, DEVICE_TYPE_B = 1, DEVICE_TYPE_C = 2 };
enum SdkReturnType {
	SDK_RETURN_SUCCESS = 0, SDK_RETURN_FAIL = -1, SDK_RETURN_NULL = 1
};

void main() {
	ChannelInfo _deviceInfo;

	//初始化SDK
	int a = sdk_initialize();
	cout << a << endl;

	//搜索设备 IP 地址
	char* username = "admin";
	char* password = "admin";
	char* oldIP = "192.168.1.123";
	char* newIP = "192.168.1.122";
	int iDeviceType = 1;   //0：A 1：B

	IRNETHANDLE pHandle;
	DeviceList deviceList;

	sdk_set_type(iDeviceType, username, password);
	pHandle = sdk_create();
	int sdk_search_device_ret = sdk_search_device(pHandle, deviceList);
	cout << sdk_search_device_ret << endl;
	for (int i = 0; i < deviceList.iNumber; i++) {
		cout << deviceList.DevInfo[i].szIP << endl;
		memcpy(&_deviceInfo, &deviceList.DevInfo[i], sizeof(ChannelInfo));
	}

	_deviceInfo.channel = 0; 
	_deviceInfo.wPortNum = 3000;
	_deviceInfo.byChanNum = 0;
	_deviceInfo.byChanNum2 = 0;
	_deviceInfo.iStreamNum = 0;
	_deviceInfo.iStreamNum2 = 0;
	strcpy(_deviceInfo.szServerName, "IRCAM");
	memcpy(_deviceInfo.szUserName, username, sizeof(username));
	memcpy(_deviceInfo.szPWD, password, sizeof(password));

	//登录设备
	int _isLogin = sdk_loginDevice(pHandle, _deviceInfo) == SDK_RETURN_SUCCESS;
	cout << (_isLogin ? "\n\n 登录成功！" : "\n\n 登录失败！") << endl;

	//修改设备的 IP 地址 备注：只有 A 类产品支持修改端口号,登录成功后才能修改
	//int iRes = sdk_set_device_ip(pHandle, _deviceInfo, newIP, 0);
	//if (iRes != 0)
	//{
	//	cout << "set device ip fail" << endl;
	//}
	
	//获取在线用户列表 该设备不支持
	User_Online* user_online = new User_Online();
	int _online_ret = sdk_get_user_online(pHandle, _deviceInfo, user_online);


	//登出设备
	int logout_ret = sdk_logoutDevice(pHandle);
	if (logout_ret == 0) {
		cout << "登出成功" << endl;
	}
	else {
		cout << "登出失败" << endl;
	}


}