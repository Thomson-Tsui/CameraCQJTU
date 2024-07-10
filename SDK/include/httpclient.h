#pragma once

#include <string>



class  CHttpClient
{
public:
	CHttpClient(void);
	~CHttpClient(void);

public:
	/**
	* @brief HTTP POST����
	* @param strUrl �������,�����Url��ַ,��:http://www.baidu.com
	* @param strPost �������,ʹ�����¸�ʽpara1=val1&para2=val2&��
	* @param strResponse �������,���ص�����
	* @return �����Ƿ�Post�ɹ�
	*/
	int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken);

	int Post_Json(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken);

	/**
	* @brief HTTP GET����
	* @param strUrl �������,�����Url��ַ,��:http://www.baidu.com
	* @param strResponse �������,���ص�����
	* @return �����Ƿ�Post�ɹ�
	*/
	int Get(const std::string & strUrl, std::string & strResponse, bool bToken);

	/**
	* @brief HTTPS POST����,��֤��汾
	* @param strUrl �������,�����Url��ַ,��:https://www.alipay.com
	* @param strPost �������,ʹ�����¸�ʽppara1=val1&para2=val2&��
	* @param strResponse �������,���ص�����
	* @param pCaPath �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
	* @return �����Ƿ�Post�ɹ�
	*/
	int Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken, const char * pCaPath = NULL);

	int Posts_Json(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken, const char * pCaPath = NULL);

	int Posts_Json1(char* strUrl, char* strPost, std::string &strResponse, bool bToken, const char * pCaPath = NULL);
	/**
	* @brief HTTPS GET����,��֤��汾
	* @param strUrl �������,�����Url��ַ,��:https://www.alipay.com
	* @param strResponse �������,���ص�����
	* @param pCaPath �������,ΪCA֤���·��.�������ΪNULL,����֤��������֤�����Ч��.
	* @return �����Ƿ�Post�ɹ�
	*/
	int Gets(const std::string & strUrl, std::string & strResponse, bool bToken, const char * pCaPath = NULL);


	int SetToken(std::string sTokenName, std::string token);


	int Posts_Format(const std::string & strUrl, const std::string sPath, std::string & strResponse, bool bToken, const char * pCaPath=NULL);
	int Post_Format(const std::string & strUrl, const std::string sPath, std::string & strResponse, bool bToken);
	int Put(const std::string & strUrl, const std::string & strPut, std::string & strResponse, bool bToken);

	int Put_Json(const std::string & strUrl, const std::string & strPut, std::string & strResponse, bool bToken);

	int Puts(const std::string & strUrl, const std::string & strPut, std::string & strResponse, bool bToken, const char * pCaPath = NULL);

	int Puts_Json(const std::string & strUrl, const std::string & strPut, std::string & strResponse, bool bToken, const char * pCaPath);

	int Delete(const std::string & strUrl, const std::string & strPut, std::string & strResponse, bool bToken);

	int Deletes(const std::string & strUrl, const std::string & strPut, std::string & strResponse, bool bToken, const char * pCaPath);
public:
	void SetDebug(bool bDebug);
	std::string UTF8_To_string(const std::string & str);

private:
	std::string m_token;
	bool m_bDebug;
	std::string X_token;
	std::string CHttpClient::string_To_UTF8(const std::string & str);
};

