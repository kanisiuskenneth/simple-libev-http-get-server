#include <request.h>
#include <cstdio> 
HTTPRequest::HTTPRequest(const char* http_request) {
    char c_host[50];
    char c_method[8];
    char c_path[50];
    sscanf(http_request, "%s %s %*s %*s %s", c_method, c_host, c_path);
    host = std::string(c_host);
    method = std::string(c_method);
    path = std::string(c_path); 
    
}

std::string HTTPRequest::GetHost() {
    return this->host;
}

std::string HTTPRequest::GetMethod() {
    return this->method;
}

std::string HTTPRequest::GetPath() {
    return this->path;
}