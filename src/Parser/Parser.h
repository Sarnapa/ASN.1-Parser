// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef PARSER_H
#define PARSER_H

#include <list>
#include "../Scanner/Scanner.h"
#include "ErrorInfo.h"

using namespace std;

class Parser
{
    public:
        Parser(Scanner&);
        virtual ~Parser();

        void parse();
        unsigned int parseOneDefinition();
        unsigned int parseDefBeginning();
        unsigned int parseType();
        unsigned int parseVariable();
    private:
        Scanner &scan;
        ScannerToken currentToken;
        ErrorInfo errorInfo;

        inline bool isTokenType(ScannerTokenType type)
        {
            return currentToken.getType() == type;
        }
};

#endif
