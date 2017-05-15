// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "InputService/InputFile.h"
#include "Scanner/Scanner.h"
#include "Parser/Parser.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    if(argc == 2)
    {
        InputFile codeFile;
        Scanner scanner(codeFile.getCode(argv[1]));
        Parser parser(scanner);
        parser.parse();
    }
    return 0;
}
