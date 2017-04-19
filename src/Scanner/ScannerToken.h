// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef SCANNERTOKEN_H
#define SCANNERTOKEN_H

#include <string>
#include <map>
#include <utility>

using namespace std;

enum ScannerTokenType
{
	DEFINITIONS_TAG,
	BEGIN_TAG,
	END_TAG,
	IMPORTS_TAG,
	EXPORTS_TAG,
	FROM_TAG,
	NULL_TAG,
	OPTIONAL_TAG,
    DEFAULT_TAG,
    SIZE_TAG,
    TRUE_TAG,
    FALSE_TAG,
    BOOLEAN_TAG,
    INTEGER_TAG,
    SEQUENCE_TAG,
    OF_TAG,
    CHOICE_TAG,
    ENUMERATED_TAG,
    PRINTABLESTRING_TAG,
    NUMERICSTRING_TAG,
    IA5STRING_TAG,
    SEMILICON,
    LEFT_CURLY_BRACKET,
    RIGHT_CURLY_BRACKET,
    LEFT_ROUND_BRACKET,
    RIGHT_ROUND_BRACKET,
    COMMA,
    VERTICAL_LINE,
    EQUALS,
    DOTS,
    QUOTES,
    IDENTIFIER_TAG,
    NAME_TAG,
    ASCII_STRING,
    NUMBER,
    MINUS,
    EOF_CHAR,
    INVALID_TOKEN
};

class ScannerToken
{
public:
    ScannerToken(ScannerTokenType, string);
    virtual ~ScannerToken();

    ScannerTokenType getType();
    string getContent();
    string getTokenTypeName();
    static pair<bool, ScannerTokenType> isKeyword(string);
private:
    ScannerTokenType type;
    string tokenContent;
    static const map<ScannerTokenType, string> tokenTypeNameMap;
    static const map<ScannerTokenType, string> keywordMap;
};

#endif
