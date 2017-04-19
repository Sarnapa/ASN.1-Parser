// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <ctype.h>
#include "ScannerToken.h"

using namespace std;

class Scanner
{
public:
    Scanner(const string&);
    virtual ~Scanner();

    ScannerToken getNextToken();
    void scanCode();
private:
    ScannerToken getSpecialCharToken();
    ScannerToken getIsUpperToken();
    ScannerToken getIsLowerToken();
    ScannerToken getNumberToken();
    ScannerToken getAsciiStringToken();
    bool isWhiteSpace();
    void skipWhiteSpaces();
    void skipComments();
    bool isSpecialCharacter();
    string getString(unsigned int);

    string input;
    unsigned int currentPos;
    unsigned int currentLine;
    bool isInQuote = false;
};

#endif
