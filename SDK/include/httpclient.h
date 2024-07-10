#pragma once

#include <string>



class  CHttpClient
{
public:
	CHttpClient(void);
	~CHttpClient(void);

public:
	/**
	* @brief HTTP POST请求
	* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
	* @param strPost 输入参数,使用如下格式para1=val1&para2=val2&…
	* @param strResponse 输出参数,返回的内容
	* @return 返回是否Post成功
	*/
	int Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken);

	int Post_Json(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken);

	/**
	* @brief HTTP GET请求
	* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
	* @param strResponse 输出参数,返回的内容
	* @return 返回是否Post成功
	*/
	int Get(const std::string & strUrl, std::string & strResponse, bool bToken);

	/**
	* @brief HTTPS POST请求,无证书版本
	* @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
	* @param strPost 输入参数,使用如下格式ppara1=val1&para2=val2&…
	* @param strResponse 输出参数,返回的内容
	* @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
	* @return 返回是否Post成功
	*/
	int Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken, const char * pCaPath = NULL);

	int Posts_Json(const std::string & strUrl, const std::string & strPost, std::string & strResponse, bool bToken, const char * pCaPath = NULL);

	int Posts_Json1(char* strUrl, char* strPost, std::string &strResponse, bool bToken, const char * pCaPath = NULL);
	/**
	* @brief HTTPS GET请求,无证书版本
	* @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
	* @param strResponse 输出参数,返回的内容
	* @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
	* @return 返回是否Post成功
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

