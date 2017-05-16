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
    if(isTokenType(ScannerTokenType::EXPORTS_TAG))
    {
        result = parseExportsPart();
        if(result != 0)
            return errorInfo.getErrorInfo(result, currentToken, scan.getCurrentLine());
        else
            currentToken = scan.getNextToken();
    }

    if(isTokenType(ScannerTokenType::IMPORTS_TAG))
    {
        result = parseImportsPart();
        if(result != 0)
            return errorInfo.getErrorInfo(result, currentToken, scan.getCurrentLine());
        else
            currentToken = scan.getNextToken();
    }

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
            case ScannerTokenType::EOF_CHAR:
                return errorInfo.getErrorInfo(17, currentToken, scan.getCurrentLine());
                break;
            default:
                return errorInfo.getErrorInfo(16, currentToken, scan.getCurrentLine());
                break;
        }
        currentToken = scan.getNextToken();
    }

    return 0;
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
        return 4;
    return 0;
}

unsigned int Parser::parseExportsPart()
{
    currentToken = scan.getNextToken();
    while(1)
    {
        if(!isTokenType(ScannerTokenType::NAME_TAG))
            return 1;
        currentToken = scan.getNextToken();
        if(isTokenType(ScannerTokenType::SEMILICON))
        {
            break;
        }
        else if(!isTokenType(ScannerTokenType::COMMA))
            return 5;
        currentToken = scan.getNextToken();
    }
    return 0;
}

unsigned int Parser::parseImportsPart()
{
    currentToken = scan.getNextToken();
    while(1)
    {
        if(!isTokenType(ScannerTokenType::NAME_TAG))
            return 1;
        currentToken = scan.getNextToken();
        if(isTokenType(ScannerTokenType::FROM_TAG))
        {
            currentToken = scan.getNextToken();
            if(!isTokenType(ScannerTokenType::NAME_TAG))
                return 1;
            currentToken = scan.getNextToken();
            if(!isTokenType(ScannerTokenType::SEMILICON))
                return 6;
            break;
        }
        else if(!isTokenType(ScannerTokenType::COMMA))
            return 5;
        currentToken = scan.getNextToken();
    }
    return 0;
}

unsigned int Parser::parseVariable()
{
    currentToken = scan.getNextToken();
    switch(currentToken.getType())
    {
        case ScannerTokenType::INTEGER_TAG:
            return  parseIntegerVariable();
        case ScannerTokenType::BOOLEAN_TAG:
            return parseBooleanVariable();
        case ScannerTokenType::SEQUENCE_TAG:
            return parseSequenceOfVariable();
        case ScannerTokenType::NAME_TAG:
            return parseOwnTypeVariable();
        case ScannerTokenType::PRINTABLESTRING_TAG:
        case ScannerTokenType::NUMERICSTRING_TAG:
        case ScannerTokenType::IA5STRING_TAG:
            return parseStringVariable();
    }
    return 18;
}

unsigned int Parser::parseIntegerVariable()
{
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::EQUALS))
        return 3;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::NUMBER))
        return 8;
    return 0;
}

unsigned int Parser::parseBooleanVariable()
{
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::EQUALS))
        return 3;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::TRUE_TAG) && !isTokenType(ScannerTokenType::FALSE_TAG))
        return 9;
    return 0;
}

unsigned int Parser::parseSequenceOfVariable()
{
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::OF_TAG))
        return 11;
    currentToken = scan.getNextToken();
    if(!isTypeForSeqOf())
        return 12;
    ScannerTokenType type = currentToken.getType();
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::EQUALS))
        return 3;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::LEFT_CURLY_BRACKET))
        return 13;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::RIGHT_CURLY_BRACKET))
    {
        while(1)
        {
            switch(type)
            {
                case ScannerTokenType::INTEGER_TAG:
                    if(!isTokenType(ScannerTokenType::NUMBER))
                        return 8;
                    break;
                case ScannerTokenType::BOOLEAN_TAG:
                    if(!isTokenType(ScannerTokenType::TRUE_TAG) && !isTokenType(ScannerTokenType::FALSE_TAG))
                        return 9;
                    break;
                case ScannerTokenType::NAME_TAG:
                    if(!isTokenType(ScannerTokenType::IDENTIFIER_TAG))
                        return 7;
                    break;
                case ScannerTokenType::PRINTABLESTRING_TAG:
                case ScannerTokenType::NUMERICSTRING_TAG:
                case ScannerTokenType::IA5STRING_TAG:
                    unsigned int result = parseString();
                    if(result != 0)
                        return result;
                    break;
            }
            currentToken = scan.getNextToken();
            if(isTokenType(ScannerTokenType::RIGHT_CURLY_BRACKET))
                break;
            else if(!isTokenType(ScannerTokenType::COMMA))
                return 5;
            currentToken = scan.getNextToken();
        }
    }
    return 0;
}

unsigned int Parser::parseOwnTypeVariable()
{
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::EQUALS))
        return 3;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::LEFT_CURLY_BRACKET))
        return 13;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::RIGHT_CURLY_BRACKET))
    {
        while(1)
        {
            if(!isTokenType(ScannerTokenType::IDENTIFIER_TAG))
                return 7;
            currentToken = scan.getNextToken();
            if(!isBuiltInValue())
                return 15;
            currentToken = scan.getNextToken();
            if(isTokenType(ScannerTokenType::RIGHT_CURLY_BRACKET))
                break;
            else if(!isTokenType(ScannerTokenType::COMMA))
                return 5;
            currentToken = scan.getNextToken();
        }
    }
    return 0;
}

unsigned int Parser::parseStringVariable()
{
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::EQUALS))
        return 3;
    currentToken = scan.getNextToken();
    unsigned int result = parseString();
    return result;
}

unsigned int Parser::parseType()
{
    currentToken = scan.getNextToken();

}

unsigned int Parser::parseString()
{
    if(!isTokenType(ScannerTokenType::QUOTES))
        return 14;
    currentToken = scan.getNextToken();
    if(!isTokenType(ScannerTokenType::QUOTES))
    {
        if(!isTokenType(ScannerTokenType::ASCII_STRING))
            return 19;
        currentToken = scan.getNextToken();
        if(!isTokenType(ScannerTokenType::QUOTES))
            return 14;
    }
    return 0;
}
