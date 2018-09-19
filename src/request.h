#ifndef _HTTP_REQUEST_
#define _HTTP_REQUEST_
#include <string>
class HTTPRequest {
    private:
        std::string host;
        std::string method; 
        std::string path;
    public:
        HTTPRequest(const char*);
        std::string GetHost();
        std::string GetMethod();
        std::string GetPath();
};

#endif