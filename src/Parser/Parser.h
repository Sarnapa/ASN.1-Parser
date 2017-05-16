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
    private:
        Scanner &scan;
        ScannerToken currentToken;
        ErrorInfo errorInfo;

        unsigned int parseOneDefinition();
        unsigned int parseDefBeginning();
        unsigned int parseExportsPart();
        unsigned int parseImportsPart();

        unsigned int parseVariable();
        unsigned int parseIntegerVariable();
        unsigned int parseBooleanVariable();
        unsigned int parseSequenceOfVariable();
        unsigned int parseOwnTypeVariable();
        unsigned int parseStringVariable();

        unsigned int parseType();
        unsigned int parseIntegerType();
        unsigned int parseSequenceOrChoiceType();
        unsigned int parseEnumaratedType();
        unsigned int parseStringType();

        unsigned int parseString();

        inline bool isTokenType(ScannerTokenType type)
        {
            return currentToken.getType() == type;
        }

        inline bool isStringType()
        {
            ScannerTokenType currentType = currentToken.getType();
            return currentType == ScannerTokenType::PRINTABLESTRING_TAG ||
                currentType == ScannerTokenType::NUMERICSTRING_TAG ||
                currentType == ScannerTokenType::IA5STRING_TAG;
        }

        bool isBuiltInValue()
        {
            ScannerTokenType currentType = currentToken.getType();
            return currentType == ScannerTokenType::NUMBER ||
            currentType == ScannerTokenType::TRUE_TAG || currentType == ScannerTokenType::FALSE_TAG ||
            parseString() == 0;
        }

        bool isTypeForSeqOf()
        {
            return isTokenType(ScannerTokenType::INTEGER_TAG) || isTokenType(ScannerTokenType::BOOLEAN_TAG)
                || isTokenType(ScannerTokenType::NAME_TAG) || isStringType();
        }
};

#endif
