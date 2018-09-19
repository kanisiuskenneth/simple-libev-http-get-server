#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_
#include <string> 
class HTTPResponse {
    private:
        int status;
        std::string status_message;
        int content_length;
        std::string body;
    public:
        HTTPResponse(int status, std::string status_message, std::string body); 
        std::string ToString();

};

#endif