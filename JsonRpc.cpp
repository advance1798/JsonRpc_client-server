#include "JsonRpc.h"
#include <iostream>
#include <string.h>
#include <cstring>

using std::string;

using namespace std;

JsonRpcRequest::JsonRpcRequest()
{
	cout << "create JsonRpcRequest obj successfully" << endl;
}
JsonRpcRequest::JsonRpcRequest(const std::string &json)
{
	Json::Reader reader;
    //reader将Json字符串解析到json_str，json_str将包含Json里所有子元素
    if (!reader.parse(json,json_str))
    {
		cerr << "json parse failed" << endl;
	    return;
	}
}

int JsonRpcRequest::Validate()
{
	if((json_str.isMember("jsonrpc") != true))
	
		return NO_JSONRPC;
	
	if((json_str.isMember("method")) != true )
	
		return NO_METH;

	if((json_str.isMember("id")) != true )

		return NO_ID;

	if((json_str.isMember("params")) != true)

		return NO_PARAMS;
	else 

	return 0;
}

std::string JsonRpcRequest::ToString()
{
	Json::FastWriter writer;
 	//生成请求json格式报文
 	return writer.write(json_str);
 }

void JsonRpcRequest::SetJsonRpc(const std::string &jsonrpc) 
{
	json_str["jsonrpc"] = jsonrpc;
}

void JsonRpcRequest::SetMethod(const std::string &method)
{
	json_str["method"] = method;
}

std::string JsonRpcRequest::GetMethod()
{
	return (json_str["method"].asString());
}

//这是个数组,或者是嵌套的json数据格式，很多形式怎么操作呢？
void JsonRpcRequest::SetParams(const std::string &param)
{
	Json::Reader reader;
	Json::Value params;

    reader.parse(param,params);

    json_str["params"] = params;
}

std::string JsonRpcRequest::GetParams()
{
   
   Json::FastWriter writer;

   return writer.write(json_str["params"]);
}

void JsonRpcRequest::SetId(int id)
{
	json_str["id"] = id;
}

int JsonRpcRequest::GetId()
{
	return (json_str["id"].asInt());
}

JsonRpcResponse::JsonRpcResponse()
{
	cout << "create JsonRpcResponse obj successfully" <<endl;
}

JsonRpcResponse::JsonRpcResponse(const std::string &json)
{
	Json::Reader reader;
    //reader将Json字符串解析到json_str，json_str将包含Json里所有子元素
    if (!reader.parse(json,json_str))
    {
		cerr << "json parse failed" << endl;
	    return;
	}
	else cout << "json parse successfully" << endl;
}

int JsonRpcResponse::Validate()
{
	if((json_str.isMember("result"))&&(json_str.isMember("error")))
	
		return INVALID_INCLUDE;
	
//以下是code不符合
	if(json_str.isMember("error"))
	{

	if( !((json_str["error"]["code"].asInt() == -32700) 
			|| (json_str["error"]["code"].asInt() == -32600) 
			|| (json_str["error"]["code"].asInt() == -32601) 
			|| (json_str["error"]["code"].asInt() == -32602) 
			|| (json_str["error"]["code"].asInt() == -32603) 
			|| ((json_str["error"]["code"].asInt() < -32000) && (json_str["error"]["code"].asInt()) > -32099)))
		
		return NO_THIS_CODE;
//以下是message不符合
    if(strcmp(json_str["error"]["message"].asString().c_str(),"Parse error") != 0 
		&& strcmp(json_str["error"]["message"].asString().c_str(),"Invalid Request") != 0 
		&& strcmp(json_str["error"]["message"].asString().c_str(),"Method not found") != 0 
		&& strcmp(json_str["error"]["message"].asString().c_str(),"Invalid params") != 0 
		&& strcmp(json_str["error"]["message"].asString().c_str(),"Internal error") != 0 
		&& strcmp(json_str["error"]["message"].asString().c_str(),"Server error") != 0 ) 

		return NO_THIS_MESSAGE;
//以下是code,message不匹配
	if(json_str["error"]["code"].asInt() == -32700) 
	{
		strcmp(json_str["error"]["message"].asString().c_str(),"Parse error") != 0;
		return MISMATCH_CODE_MESSAGE;
	}

	if(json_str["error"]["code"].asInt() == -32600) 
	{
		strcmp(json_str["error"]["message"].asString().c_str(),"Invalid Request") != 0;
		return MISMATCH_CODE_MESSAGE;
	}

	if(json_str["error"]["code"].asInt() == -32601)
	{
		strcmp(json_str["error"]["message"].asString().c_str(),"Method not found") != 0;
		return MISMATCH_CODE_MESSAGE;
	}

	if(json_str["error"]["code"].asInt() == -32602)
	{
		strcmp(json_str["error"]["message"].asString().c_str(),"Invalid params") != 0;
		return MISMATCH_CODE_MESSAGE;
	}

	if(json_str["error"]["code"].asInt() == -32603)
	{
		strcmp(json_str["error"]["message"].asString().c_str(),"Internal error") != 0;
		return MISMATCH_CODE_MESSAGE;
	}

	if(json_str["error"]["code"].asInt() > -32099 && json_str["error"]["code"].asInt() < -32000)
	{
			strcmp(json_str["error"]["message"].asString().c_str(),"Server error") != 0;
			return MISMATCH_CODE_MESSAGE;
	}

	}

//以下判断的匹配重复
//    if(strcmp(json_str["error"]["message"].asString().c_str(),"Parse error") == 0)
//	{
//		json_str["error"]["code"].asInt() != -32700;
//		return MISMATCH_CODE;
//	}
//
//	if(strcmp(json_str["error"]["message"].asString().c_str(),"Invalid Request") == 0)
//	{
//		json_str["error"]["code"].asInt() != -32600;
//		return MISMATCH_CODE;
//	}
//
//	if(strcmp(json_str["error"]["message"].asString().c_str(),"Method not found") == 0)
//	{
//		json_str["error"]["code"].asInt() != -32601;
//		return MISMATCH_CODE;
//	}
//
//	if(strcmp(json_str["error"]["message"].asString().c_str(),"Invalid params") == 0)
//	{
//		json_str["error"]["code"].asInt() != -32602;
//		return MISMATCH_CODE;
//	}
//
//	if(strcmp(json_str["error"]["message"].asString().c_str(),"Internal error") == 0)
//	{
//		json_str["error"]["code"].asInt() != -32603;
//		return MISMATCH_CODE;
//	}
//	if(strcmp(json_str["error"]["message"].asString().c_str(),"Server error") == 0)
//	{
//		(json_str["error"]["code"].asInt() < -32099 && json_str["error"]["code"].asInt()> -32000);
//		return MISMATCH_CODE;
//	}
	
	return 0;
}

std::string JsonRpcResponse::ToString()
{
	Json::FastWriter writer;
	
 	return writer.write(json_str);
}


//void JsonRpcResponse::SetResult(int result)
//{
//		json_str["result"] = result;
//}

void JsonRpcResponse::SetResult(const std::string &Result)
{
	Json::Value result;
	Json::Reader reader;


	reader.parse(Result,result);

	json_str["result"] = result;
}

//int JsonRpcResponse::GetResult()
//{
//	return (json_str["result"].asInt()) ;
//}

std::string JsonRpcResponse::GetResult()
{
	Json::FastWriter writer;

	return writer.write(json_str["result"]);
}

void JsonRpcResponse::SetError(const std::string &Error)
{
		Json::Reader reader;
		Json::Value error;
		
		reader.parse(Error,error);

		json_str["error"] = error;//对象嵌套
}

std::string JsonRpcResponse::GetError()
{
	Json::FastWriter writer;
	return writer.write(json_str["error"]);
}

void JsonRpcResponse::SetId(int id)
{
	json_str["id"] = id;
}

int JsonRpcResponse::GetId()
{
	return (json_str["id"].asInt());
}

