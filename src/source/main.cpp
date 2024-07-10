#include <iostream>
#include "WinSock2.h"
#include "InfraredTempSDK.h"


enum DeviceType { DEVICE_TYPE_A = 0, DEVICE_TYPE_B = 1, DEVICE_TYPE_C = 2 };
enum SdkReturnType {
	SDK_RETURN_SUCCESS = 0, SDK_RETURN_FAIL = -1, SDK_RETURN_NULL = 1
};

void main() {
	ChannelInfo _deviceInfo;

	//��ʼ��SDK
	int a = sdk_initialize();
	cout << a << endl;

	//�����豸 IP ��ַ
	char* username = "admin";
	char* password = "admin";
	char* oldIP = "192.168.1.123";
	char* newIP = "192.168.1.122";
	int iDeviceType = 1;   //0��A 1��B

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

	//��¼�豸
	int _isLogin = sdk_loginDevice(pHandle, _deviceInfo) == SDK_RETURN_SUCCESS;
	cout << (_isLogin ? "\n\n ��¼�ɹ���" : "\n\n ��¼ʧ�ܣ�") << endl;

	//�޸��豸�� IP ��ַ ��ע��ֻ�� A ���Ʒ֧���޸Ķ˿ں�,��¼�ɹ�������޸�
	//int iRes = sdk_set_device_ip(pHandle, _deviceInfo, newIP, 0);
	//if (iRes != 0)
	//{
	//	cout << "set device ip fail" << endl;
	//}
	
	//��ȡ�����û��б� ���豸��֧��
	User_Online* user_online = new User_Online();
	int _online_ret = sdk_get_user_online(pHandle, _deviceInfo, user_online);


	//�ǳ��豸
	int logout_ret = sdk_logoutDevice(pHandle);
	if (logout_ret == 0) {
		cout << "�ǳ��ɹ�" << endl;
	}
	else {
		cout << "�ǳ�ʧ��" << endl;
	}


}