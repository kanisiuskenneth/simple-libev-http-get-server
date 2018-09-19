#include "file.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
File::File(string filename) {
    ifstream inFile;
    inFile.open(filename);

    stringstream strStream;
    strStream << inFile.rdbuf();
    content = strStream.str();
    
}

string File::GetContent() {
    return content;
}
