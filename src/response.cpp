#include <response.h> 
#include <string>
#include <sstream>
using namespace std;

HTTPResponse::HTTPResponse(int status, string status_message,  string body) {
    this->status = status;
    this->body = body; 
}


string HTTPResponse::ToString() {
    ostringstream ss;
    ss << "HTTP/1.1 " << this->status << " " << this->status_message << endl;
    ss << "Content-Type: text/html" << endl;
    ss << "Content-Length: " << this->body.length() << endl;
    ss << endl;
    ss << this->body << endl;
    return ss.str();
}