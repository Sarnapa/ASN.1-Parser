// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "ErrorInfo.h"

unsigned int ErrorInfo::getErrorInfo(unsigned int id, ScannerToken currentToken, unsigned int line)
{
    switch(id)
    {
        case 1:
            cout << "Line " + to_string(line) + ": NAME_TAG token expected." << endl;
            break;
        case 2:
            cout << "Line " + to_string(line) + ": DEFINITIONS_TAG token expected." << endl;
            break;
        case 3:
            cout << "Line " + to_string(line) + ": EQUALS token expected." << endl;
            break;
        case 4:
            cout << "Line " + to_string(line) + ": BEGIN_TAG token expected." << endl;
            break;
        case 5:
            cout << "Line " + to_string(line) + ": COMMA token expected." << endl;
            break;
        case 6:
            cout << "Line " + to_string(line) + ": SEMILICON token expected." << endl;
            break;
        case 7:
            cout << "Line " + to_string(line) + ": IDENTIFIER_TAG token expected." << endl;
            break;
        case 8:
            cout << "Line " + to_string(line) + ": NUMBER token expected." << endl;
            break;
        case 9:
            cout << "Line " + to_string(line) + ": Boolean value expected." << endl;
            break;
        case 10:
            cout << "Line " + to_string(line) + ": SEQUENCE token expected." << endl;
            break;
        case 11:
            cout << "Line " + to_string(line) + ": OF token expected." << endl;
            break;
        case 12:
            cout << "Line " + to_string(line) + ": Type for 'SEQUENCE OF' expected." << endl;
            break;
        case 13:
            cout << "Line " + to_string(line) + ": LEFT_CURLY_BRACKET token expected." << endl;
            break;
        case 14:
            cout << "Line " + to_string(line) + ": QUOTES token expected." << endl;
            break;
        case 15:
            cout << "Line " + to_string(line) + ": Not valid value." << endl;
            break;
        case 16:
            cout << "Line " + to_string(line) + ": NAME_TAG or IDENTIFIER_TAG token expected." << endl;
            break;
        case 17:
            cout << "Line " + to_string(line) + ": END_TAG token expected." << endl;
            break;
        case 18:
            cout << "Line " + to_string(line) + ": Type for variable expected." << endl;
            break;
        case 19:
            cout << "Line " + to_string(line) + ": ASCII_STRING token expected." << endl;
            break;
        case 20:
            cout << "Line " + to_string(line) + ": LEFT_ROUND_BRACKET token expected." << endl;
            break;
        case 21:
            cout << "Line " + to_string(line) + ": DOTS or VERTICAL_LINE token expected." << endl;
            break;
        case 22:
            cout << "Line " + to_string(line) + ": RIGHT_ROUND_BRACKET token expected." << endl;
            break;
        case 23:
            cout << "Line " + to_string(line) + ": VERTICAL_LINE token expected." << endl;
            break;
        case 24:
            cout << "Line " + to_string(line) + ": Not valid type." << endl;
            break;
        case 25:
            cout << "Line " + to_string(line) + ": SIZE_TAG or FROM_TAG token expected" << endl;
            break;
        case 26:
            cout << "Line " + to_string(line) + ": DOTS or RIGHT_ROUND_BRACKET token expected" << endl;
            break;
    }
    return id;
}
