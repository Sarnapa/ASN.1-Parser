// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "ScannerToken.h"

using namespace std;

// Due to problem with enum -> string conversion
const map<ScannerTokenType, string> ScannerToken::tokenTypeNameMap =
{
    { ScannerTokenType::DEFINITIONS_TAG, "DEFINITIONS TAG"},
	{ ScannerTokenType::BEGIN_TAG, "BEGIN TAG"},
	{ ScannerTokenType::END_TAG, "END TAG"},
	{ ScannerTokenType::IMPORTS_TAG, "IMPORTS TAG"},
	{ ScannerTokenType::EXPORTS_TAG, "EXPORTS TAG"},
	{ ScannerTokenType::FROM_TAG, "FROM TAG"},
	{ ScannerTokenType::NULL_TAG, "NULL TAG"},
	{ ScannerTokenType::OPTIONAL_TAG, "OPTIONAL TAG"},
    { ScannerTokenType::DEFAULT_TAG, "DEFAULT TAG"},
    { ScannerTokenType::SIZE_TAG, "SIZE TAG"},
    { ScannerTokenType::TRUE_TAG, "TRUE TAG"},
    { ScannerTokenType::FALSE_TAG, "FALSE TAG"},
    { ScannerTokenType::BOOLEAN_TAG, "BOOLEAN TAG"},
    { ScannerTokenType::INTEGER_TAG, "INTEGER TAG"},
    { ScannerTokenType::SEQUENCE_TAG, "SEQUENCE TAG"},
    { ScannerTokenType::OF_TAG, "OF TAG"},
    { ScannerTokenType::CHOICE_TAG, "CHOICE TAG"},
    { ScannerTokenType::ENUMERATED_TAG, "ENUMERATED TAG"},
    { ScannerTokenType::PRINTABLESTRING_TAG, "PRINTABLESTRING TAG"},
    { ScannerTokenType::NUMERICSTRING_TAG, "NUMERICSTRING TAG"},
    { ScannerTokenType::IA5STRING_TAG, "IA5STRING TAG"},
    { ScannerTokenType::SEMILICON, "SEMILICON"},
    { ScannerTokenType::LEFT_CURLY_BRACKET, "LEFT CURLY BRACKET"},
    { ScannerTokenType::RIGHT_CURLY_BRACKET, "RIGHT CURLY BRACKET"},
    { ScannerTokenType::LEFT_ROUND_BRACKET, "LEFT ROUND BRACKET"},
    { ScannerTokenType::RIGHT_ROUND_BRACKET, "RIGHT ROUND BRACKET"},
    { ScannerTokenType::COMMA, "COMMA"},
    { ScannerTokenType::VERTICAL_LINE, "VERTICAL LINE"},
    { ScannerTokenType::EQUALS, "EQUALS"},
    { ScannerTokenType::DOTS, "DOTS"},
    { ScannerTokenType::QUOTES, "QUOTES"},
    { ScannerTokenType::IDENTIFIER_TAG, "IDENTIFIER TAG"},
    { ScannerTokenType::NAME_TAG, "NAME TAG"},
    { ScannerTokenType::ASCII_STRING, "ASCII STRING"},
    { ScannerTokenType::NUMBER, "NUMBER"},
    { ScannerTokenType::MINUS, "MINUS"},
    { ScannerTokenType::EOF_CHAR, "EOF CHAR"},
    { ScannerTokenType::INVALID_TOKEN, "INVALID TOKEN"}
};

const map<ScannerTokenType, string> ScannerToken::keywordMap =
{
    { ScannerTokenType::DEFINITIONS_TAG, "DEFINITIONS"},
	{ ScannerTokenType::BEGIN_TAG, "BEGIN"},
	{ ScannerTokenType::END_TAG, "END"},
	{ ScannerTokenType::IMPORTS_TAG, "IMPORTS"},
	{ ScannerTokenType::EXPORTS_TAG, "EXPORTS"},
	{ ScannerTokenType::FROM_TAG, "FROM"},
	{ ScannerTokenType::NULL_TAG, "NULL"},
	{ ScannerTokenType::OPTIONAL_TAG, "OPTIONAL"},
    { ScannerTokenType::DEFAULT_TAG, "DEFAULT"},
    { ScannerTokenType::SIZE_TAG, "SIZE"},
    { ScannerTokenType::TRUE_TAG, "TRUE"},
    { ScannerTokenType::FALSE_TAG, "FALSE"},
    { ScannerTokenType::BOOLEAN_TAG, "BOOLEAN"},
    { ScannerTokenType::INTEGER_TAG, "INTEGER"},
    { ScannerTokenType::SEQUENCE_TAG, "SEQUENCE"},
    { ScannerTokenType::OF_TAG, "OF"},
    { ScannerTokenType::CHOICE_TAG, "CHOICE"},
    { ScannerTokenType::ENUMERATED_TAG, "ENUMERATED"},
    { ScannerTokenType::PRINTABLESTRING_TAG, "PrintableString"},
    { ScannerTokenType::NUMERICSTRING_TAG, "NumericString"},
    { ScannerTokenType::IA5STRING_TAG, "IA5String"},
};

ScannerToken::ScannerToken()
{

}

ScannerToken::ScannerToken(ScannerTokenType type, string tokenContent):
type(type), tokenContent(tokenContent)
{

}

ScannerToken::ScannerToken(const ScannerToken &token):
type(token.type), tokenContent(token.tokenContent)
{

}

ScannerToken::~ScannerToken()
{
}

ScannerTokenType ScannerToken::getType()
{
    return type;
}

string ScannerToken::getContent()
{
    return tokenContent;
}

string ScannerToken::getTokenTypeName()
{
    for(map<ScannerTokenType, string>::const_iterator it = tokenTypeNameMap.begin(); it != tokenTypeNameMap.end(); it++)
    {
        if(it->first == type)
            return it->second;
    }
}

pair<bool, ScannerTokenType> ScannerToken::isKeyword(string word)
{
    for(map<ScannerTokenType, string>::const_iterator it = keywordMap.begin(); it != keywordMap.end(); it++)
    {
        if(it->second == word)
            return make_pair(true, it->first);
    }
    return make_pair(false, INVALID_TOKEN); // second parameter is not significant
}
