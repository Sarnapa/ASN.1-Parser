// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <string>
#include <fstream>

using namespace std;

class InputFile
{
public:
    InputFile();
    virtual ~InputFile();
    string getCode(const char *);
};

#endif
