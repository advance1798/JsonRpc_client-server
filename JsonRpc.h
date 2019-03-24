#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif


#ifndef OMA_DM_SAMPLE_JSON_RPC_H_
#define OMA_DM_SAMPLE_JSON_RPC_H_

#define NO_JSONRPC 3
#define NO_METH 4
#define NO_ID 5
#define NO_PARAMS 6

#define INVALID_INCLUDE 7
#define NO_THIS_CODE 8
#define NO_THIS_MESSAGE 9
#define MISMATCH_CODE_MESSAGE 10


#include <string>

#include <json/json.h>

class JsonRpcRequest {
private:
	Json::Value json_str;
public:
	JsonRpcRequest();//构造函数
    JsonRpcRequest(const std::string &json);//带参构造函数，初始化成员变量，json格式的字符串，转化为json对象类型

    int Validate();
    std::string ToString();//

	void SetJsonRpc(const std::string &jsonrpc);

    void SetMethod(const std::string &method);
    std::string GetMethod();

    void SetParams(const std::string &param);
	std::string GetParams();
	
	void SetId(int id);
	int GetId();
};

class JsonRpcResponse {
private:
	Json::Value json_str;

public:
    JsonRpcResponse();
    JsonRpcResponse(const std::string &json);

    int Validate();
    std::string ToString();

    //void SetResult(int result);
	void SetResult(const std::string &Result);

	//int GetResult();
	std::string GetResult();

    void SetError(const std::string &Error);
	std::string GetError();

	void SetId(int id);
	int GetId();
};



#endif /* OMA_DM_SAMPLE_JSON_RPC_H_ */
