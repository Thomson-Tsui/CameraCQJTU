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
	// ��������
	static CHyvSNMac * Create();
	// �����豸��Ϣ
	// iOvertime:��ʱʱ��,��λ����
	// ����ֵ  0:�ɹ�  -1:ʧ��  1:ʧ�ܣ����²���
	int SearchDeviceAll(int iOvertime, vector <NetInfo>& netInfors);
	// �޸��豸IP
	// sUsr:�˻���,sPassword:����,sSN:���к�(��GetSNMac��ȡ), sNetName:��������(Ŀǰ��"eth0")
	// sSourceIP:Ҫ�޸ĵ�ԴIP��ַ,sDestIp:Ҫ�޸ĵ�Ŀ��IP��ַ,sMask:��������,sGateway:����
	// ����ֵ-2:ʧ�� -1:������������룬���أ�Ŀ��IP��ƥ��  1:�޸�ʧ�� 0:�޸ĳɹ�
	int Modify(char *sUsr, char *sPassword, char *sSN, char *sNetName, char *sSourceIP, char *sDestIP, char *sMask, char *sGateway);
	// �رգ����ٶ���
	void Close();
};