// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "InputFile.h"

using namespace std;

InputFile::InputFile()
{}

InputFile::~InputFile()
{}

string InputFile::getCode(const char *fileName)
{
    ifstream file;
    string code, line;
    file.open(fileName);
    if(file.is_open())
    {
        while(getline(file, line))
            code += line + '\n';
        code += '\0';
        file.close();
    }
    return code;
}
