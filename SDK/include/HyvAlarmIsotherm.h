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
	// ����sIp:Ҫ���ӵķ����IP��ַ
	// ����ֵ0:�ɹ���-1:ʧ��,-2:ʧ�ܣ���������Connect
	int Connect();
	void Logout();
	string m_sIp;
	string m_sToken;
	SOCKET Socket;
public:
	// ��������
	static CHyvAlarmIsotherm* Create(char *sIp);

	//����alarmEnable(����ʹ�ܿ���) true:ʹ��,false:��
	//����isOthermEnable(������ʹ�ܿ���) true:ʹ��,false:��
	//����alarmType(��������) 0���� 1�����±��� 2�����±��� 3���ߵ��±�����
	//����tempUp(������ֵ) ��λ������------Ҫ�ȵ�����ֵ�ߣ���������ʧ��,0-16383(14bit)
	//����tempLow(������ֵ) ��λ������--------Ҫ�ȸ�����ֵ�ͣ���������ʧ��0-16383(14bit)
	//����ֵ0:�ɹ�,-1:ʧ��
	int SetAlarmIsotherm(BOOL alarmEnable, BOOL isOthermEnable, int alarmType, int tempUp, int tempLow);

	//��ȡ����ʹ�ܿ��ؼ�������ʹ�ܿ���״̬,��������,�ߵ�����ֵ
	//��õ�״̬�ֱ����ַ�������̬����ڲ���sAE,sIE��
	//��ȡ�ı������ͣ�������ֵ��������ֵ�ֱ�����pAlarmType,pTempUp,pTempLow��
	//����ֵ0���ɹ���-1:ʧ��
	int GetAlarmIsotherm(char *sAE,char *sIE,char *pAlarmType,char *pTempUp,char *pTempLow);

	//�����¶����ݿ��ؼ�֡��
	//����tempDataEnable(�¶����ݿ���) true:ʹ��,false:��
	//����tempDataFps(�¶�����֡��1-50)
	//����ֵ0:�ɹ�,-1:ʧ��
	int SetTempDataParam(BOOL tempDataEnable, int tempDataFps);

	//��ȡ�¶����ݿ��ؼ�֡��
	//����tempDataEnable(�¶����ݿ���) true:ʹ��,false:��
	//����tempDataFps(�¶�����֡��1-50)
	//����ֵ0:�ɹ�,-1:ʧ��
	int GetTempDataParam(BOOL& tempDataEnable, int& tempDataFps);

	//��ȡϵͳ�汾��
	//sSystemVersion:Ҫ��ȡ��ϵͳ�汾��
	//����ֵ0:�ɹ�,-1:ʧ��
	int GetSystemVersion(char *pSystemVersion);

	//�ر����ӣ����ٶ���
	void Close();
};

