// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "Scanner.h"

using namespace std;

Scanner::Scanner(const string& input): input(input), currentPos(0),
currentLine(1)
{}

Scanner::~Scanner()
{}

ScannerToken Scanner::getNextToken()
{
    skipWhiteSpaces();
    if(input[currentPos] == '\0')
        return ScannerToken(EOF_CHAR, "\0");

    if(isSpecialCharacter())
        return getSpecialCharToken();

    if(!isInQuote)
    {
        if(isalpha(input[currentPos]))
        {
            if(isupper(input[currentPos]))
                return getIsUpperToken();
            else
                return getIsLowerToken();
        }
        else if(isdigit(input[currentPos]))
        {
            return getNumberToken();
        }
    }
    else
    {
        if(isgraph(input[currentPos]))
            return getAsciiStringToken();
    }

    currentPos++;
    return ScannerToken(INVALID_TOKEN, "");
}

ScannerToken Scanner::getSpecialCharToken()
{
    switch(input[currentPos])
    {
        case ';':
            currentPos++;
            return ScannerToken(SEMILICON, ";");
        case '{':
            currentPos++;
            return ScannerToken(LEFT_CURLY_BRACKET, "{");
        case '}':
            currentPos++;
            return ScannerToken(RIGHT_CURLY_BRACKET, "}");
        case '(':
            currentPos++;
            return ScannerToken(LEFT_ROUND_BRACKET, "(");
        case ')':
            currentPos++;
            return ScannerToken(RIGHT_ROUND_BRACKET, ")");
        case ',':
            currentPos++;
            return ScannerToken(COMMA, ",");
        case '|':
            currentPos++;
            return ScannerToken(VERTICAL_LINE, "|");
        case ':':
            currentPos++;
            if(input[currentPos] != ':')
            {
                currentPos++;
                return ScannerToken(INVALID_TOKEN, "::=");
            }
            currentPos++;
            if(input[currentPos] != '=')
            {
                currentPos++;
                return ScannerToken(INVALID_TOKEN, "::=");
            }
            currentPos++;
            return ScannerToken(EQUALS, "::=");
        case '.':
            currentPos++;
            if(input[currentPos] != '.')
            {
                return ScannerToken(INVALID_TOKEN, "..");
            }
            currentPos++;
            return ScannerToken(DOTS, "..");
        case '\"':
            isInQuote = !isInQuote;
            currentPos++;
            return ScannerToken(QUOTES, "\"");
        case '-':
            currentPos++;
            if(input[currentPos] == '-')
            {
                currentPos++;
                skipComments();
                return getNextToken();
            }
            return ScannerToken(MINUS, "-");
    }
}

ScannerToken Scanner::getIsUpperToken()
{
    bool isNotAlNumChar = false;
    unsigned int startPos = currentPos;
    currentPos++;
    while(isalnum(input[currentPos]) || input[currentPos] == '_' || input[currentPos] == '-')
    {
        if(!isNotAlNumChar)
            if(input[currentPos] == '_' || input[currentPos] == '-')
                isNotAlNumChar = true;
        currentPos++;
    }
    string fromCode = getString(startPos);
    if(!isNotAlNumChar)
    {
        pair<bool, ScannerTokenType> result = ScannerToken::isKeyword(fromCode);
        if(result.first)
            return ScannerToken(result.second, fromCode);
    }
    return ScannerToken(NAME_TAG, fromCode);
}

bool Scanner::isWhiteSpace()
{
    if(input[currentPos] == '\n')
    {
        currentLine++;
        return true;
    }
    else if(isspace(input[currentPos]))
        return true;
    return false;
}

ScannerToken Scanner::getIsLowerToken()
{
    unsigned int startPos = currentPos;
    currentPos++;
    while(isalnum(input[currentPos]) || input[currentPos] == '_' || input[currentPos] == '-')
        currentPos++;
    string fromCode = getString(startPos);
    return ScannerToken(IDENTIFIER_TAG, fromCode);
}

ScannerToken Scanner::getNumberToken()
{
    unsigned int startPos = currentPos;
    currentPos++;
    while(isdigit(input[currentPos]))
        currentPos++;
    string fromCode = getString(startPos);
    return ScannerToken(NUMBER, fromCode);
}

ScannerToken Scanner::getAsciiStringToken()
{
    unsigned int startPos = currentPos;
    currentPos++;
    while((isgraph(input[currentPos]) && input[currentPos] != '\"') || input[currentPos] == ' '
    || input[currentPos] == '\n')
    {
        if(input[currentPos] == '\n')
            currentLine++;
        currentPos++;
    }
    if(input[currentPos] == '\0')
        return getNextToken();
    string fromCode = getString(startPos);
    return ScannerToken(ASCII_STRING, fromCode);
}

void Scanner::skipWhiteSpaces()
{
    while(isWhiteSpace())
        ++currentPos;
}

void Scanner::skipComments()
{
    unsigned int tmp = currentPos;
    if(input[currentPos] == '\n')
        currentLine++;
    else if(input[currentPos] == '\0')
        return;
    while(input[tmp] != '-' || input[++tmp] != '-')
    {
        tmp = ++currentPos;
        if(input[currentPos] == '\n')
            currentLine++;
        else if(input[currentPos] == '\0')
            return;
    }
    currentPos = ++tmp;
}

bool Scanner::isSpecialCharacter()
{
    if(!isInQuote)
    {
        if(input[currentPos] == ';' || input[currentPos] == '{' ||
        input[currentPos] == '}' || input[currentPos] == '(' ||
        input[currentPos] == ')' || input[currentPos] == ',' ||
        input[currentPos] == '|' || input[currentPos] == ':' ||
        input[currentPos] == '.' || input[currentPos] == '-')
            return true;
    }
    if(input[currentPos] == '\"')
        return true;
    return false;
}

string Scanner::getString(unsigned int startPos)
{
    if (startPos < currentPos)
    {
        return input.substr(startPos, currentPos - startPos);
    }
    return NULL;
}

unsigned int Scanner::getCurrentLine()
{
    return currentLine;
}

void Scanner::scanCode()
{
    while(input[currentPos] != '\0')
    {
        ScannerToken token = getNextToken();
        string tokenTypeName = token.getTokenTypeName();
        cout << "Token Type: " << tokenTypeName << " | Token Value: " << token.getContent() << " | Line: " << currentLine << endl << endl;
    }
}
