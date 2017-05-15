// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "Parser.h"

Parser::Parser(Scanner &scan): scan(scan)
{}

Parser::~Parser()
{

}

void Parser::parse()
{
    currentToken = scan.getNextToken();

    while(!isTokenType(ScannerTokenType::EOF_CHAR))
    {
        if(parseOneDefinition() != 0)
            break;
        currentToken = scan.getNextToken();
    }
}

unsigned int Parser::parseOneDefinition()
{
    unsigned int result = parseDefBeginning();
    if(result != 0)
        return errorInfo.getErrorInfo(result, currentToken, scan.getCurrentLine());

    currentToken = scan.getNextToken();
    while(!isTokenType(ScannerTokenType::END_TAG))
    {
        switch(currentToken.getType())
        {
            case ScannerTokenType::IDENTIFIER_TAG:
                result = parseVariable();
                if(result != 0)
                    return errorInfo.getErrorInfo(result, currentToken, scan.getCurrentLine());
                break;
            case ScannerTokenType::NAME_TAG:
                result = parseType();
                if(result != 0)
                    return errorInfo.getErrorInfo(result, currentToken, scan.getCurrentLine());
                break;
        }
        currentToken = scan.getNextToken();
    }
}

unsigned int Parser::parseDefBeginning()
{
    if(!isTokenType(ScannerTokenType::NAME_TAG))
        return 1;

    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::DEFINITIONS_TAG))
        return 2;

    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::EQUALS))
        return 3;

    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::BEGIN_TAG))
    {
        return 4;
    }
    return 0;
}

unsigned int Parser::parseVariable()
{

}

unsigned int Parser::parseType()
{

}
