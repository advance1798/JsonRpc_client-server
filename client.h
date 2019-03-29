#ifndef CLIENT_H_
#define CLIENT_H_ 

#include "JsonRpc.h"

class JsonRpcClient
{
	
	private:
		std::string recvdata;
		
		void SendData(const char *jsondata, const char *url);
		//size_t receive_data(void *ptr,size_t size,size_t nmemb,void *stream);

	public:
		JsonRpcClient();
		//void SendData(const char *jsondata, const char *url);
		JsonRpcResponse doRequest(const char *url, const char * jsondata);
		//JsonRpcResponse doRequest(const char *url, JsonRpcRequest &request);
		//friend size_t receive_data(void *ptr,size_t size,size_t nmemb,void *stream);
};

//size_t receive_data(void *ptr,size_t size,size_t nmemb,void *stream);

#endif
