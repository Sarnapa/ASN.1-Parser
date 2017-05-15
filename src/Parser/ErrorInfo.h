// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef ERRORINFO_H
#define ERRORINFO_H

#include <iostream>
#include <string>
#include "../Scanner/ScannerToken.h"

using namespace std;

class ErrorInfo
{
    public:
        unsigned int getErrorInfo(unsigned int id, ScannerToken currentToken, unsigned int line);
};

#endif
