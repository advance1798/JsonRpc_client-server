#include <iostream>
#include <string>
#include <string.h>
#include <curl/curl.h>
#include "client.h"

using namespace std;


JsonRpcClient::JsonRpcClient()
{
	recvdata = " ";
}

static size_t receive_data(void *ptr,size_t size,size_t nmemb,void *stream)
{
    	size_t nsize = size * nmemb;

    	//可以用全局变量/成员变量memcpy把ptr拷贝出来
    	//memcpy(recvdata,buffer,nsize);
    	std::string *s = (std::string *)stream;

    	//std::string str;
    	//str = (char *)ptr;
    	//cout << str << endl;
    	s->append((const char *)ptr,nsize);

		//c->recvdata += str;
    
    	//c->recvdata += string((const char *)ptr,nsize);

    	//std::string *buffer = (std::string*)stream;
        //buffer->append((char*)ptr, nsize);

      //  memcpy(&(c->recvdata),ptr,nsize);
    	return nsize; 
}

void JsonRpcClient::SendData(const char *jsondata, const char *url)
{
	struct curl_slist *header;

	CURL *curl = NULL;
	curl = curl_easy_init();

	CURLcode res;

	CURLcode p1,p2,p3,p4,p5;

	if(curl != NULL)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		
		//设置http发送的内容类型为JSON
		header  = curl_slist_append(header,"Content_Type:json");
		//构建HTTP报文头,请求消息头用于告诉服务器如何处理请求
		p1 = curl_easy_setopt(curl,CURLOPT_HTTPHEADER,header);

		//自定义请求方式p
		//curl_easy_setopt(curl,CURLOPT_CUSTOMREQUEST,"GET");
		
		//设置为非0表示本次操作为POST
		//	curl_easy_setopt(curl,CURLOPT_POST,1);

		p2 = curl_easy_setopt(curl,CURLOPT_VERBOSE,1);

		//设置要POST的JSON数据
		p3 = curl_easy_setopt(curl,CURLOPT_POSTFIELDS,jsondata);

		p4 = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_data);
   		p5 = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(this->recvdata));

		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
		{
				cout << "curl_easy_perform failed" << endl;
		}
		
		//if(res == CURLE_OK)
		//{
		// cout << "curl_easy_perform successfully" << endl;
		//}
	
	curl_easy_cleanup(curl);
	}


}




JsonRpcResponse JsonRpcClient::doRequest(const char *url, const char * jsondata) 
{
			JsonRpcClient temp;

			temp.SendData(jsondata, url);

			return JsonRpcResponse(temp.recvdata);
}