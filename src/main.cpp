// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "Scanner/Scanner.h"
#include "Scanner/ScannerToken.h"
#include "InputService/InputFile.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    if(argc == 2)
    {
        InputFile codeFile;
        Scanner scanner(codeFile.getCode(argv[1]));
        scanner.scanCode();
    }
    return 0;
}
