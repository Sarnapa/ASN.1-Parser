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
            cout << "Line " + to_string(line) + ": " << endl;
            break;
        case 4:
            cout << "Line " + to_string(line) + ": " << endl;
            break;
        case 5:
            cout << "Line " + to_string(line) + ": " << endl;
            break;
        case 6:
            cout << "Line " + to_string(line) + ": " << endl;
            break;
        case 7:
            cout << "Line " + to_string(line) + ": " << endl;
            break;
    }
    return id;
}
