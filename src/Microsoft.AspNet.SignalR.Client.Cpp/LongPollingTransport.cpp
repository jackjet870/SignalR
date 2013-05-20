#include "LongPollingTransport.h"


LongPollingTransport::LongPollingTransport(http_client* httpClient) :
    HttpBasedTransport(httpClient)
{
}


LongPollingTransport::~LongPollingTransport(void)
{
}

pplx::task<void> LongPollingTransport::Start(Connection* connection, START_CALLBACK startCallback, string data, void* state)
{    
    //string url = connection->GetUrl();

    //if(startCallback != NULL)
    //{
    //    url += "connect";
    //}

    //// TODO: Handle reconnect

    //url += TransportHelper::GetReceiveQueryString(connection, data, "longPolling");

    //auto info = new PollHttpRequestInfo();
    //info->CallbackState = state;
    //info->Transport = this;
    //info->Callback = startCallback;
    //info->Connection = connection;
    //info->Data = data;

    ////mHttpClient->Get(url, &LongPollingTransport::OnPollHttpResponse, info);

    //// TODO: Need to set a timer here to trigger connected after 2 seconds or so

    return pplx::task<void>();
}

void LongPollingTransport::OnPollHttpResponse(IHttpResponse* httpResponse, exception* error, void* state)
{
    auto pollInfo = (PollHttpRequestInfo*)state;
    bool timedOut, disconnected;

    if(NULL != error)
    {
        if(pollInfo->Callback != NULL)
        {
            pollInfo->Callback(NULL, pollInfo->CallbackState);
        }
        
        TransportHelper::ProcessMessages(pollInfo->Connection, httpResponse->GetResponseBody(), &timedOut, &disconnected);
    }
    else
    {
        if(pollInfo->Callback != NULL) 
        {
            pollInfo->Callback(error, pollInfo->CallbackState);
        }
        else
        {
            pollInfo->Connection->OnError(*error);
        }
    }

    if(disconnected)
    {
        pollInfo->Connection->Stop();
    }
    else
    {
        pollInfo->Transport->Start(pollInfo->Connection, NULL, pollInfo->Data);
    }

    delete pollInfo;
}
