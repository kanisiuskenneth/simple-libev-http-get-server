#ifndef _FILE_
#define _FILE_
#include <string>
class File {
    private:
        std::string content;
    public:
        File(std::string filename);
        std::string GetContent();
};

#endif