CXX := g++
COMPILEFLAG := -std=c++11
SCANNERPATH := src/Scanner
INPUTSERVICEPATH := src/InputService
PARSERPATH := src/Parser
RANGESERVICE := src/RangeService

asn1Parser: main.o Scanner.o ScannerToken.o InputFile.o Parser.o ErrorInfo.o RangeService.o RangeObject.o
	$(CXX) $(COMPILEFLAG) -o asn1Parser main.o Scanner.o ScannerToken.o InputFile.o Parser.o ErrorInfo.o RangeService.o RangeObject.o
main.o: src/main.cpp  $(SCANNERPATH)/Scanner.h $(SCANNERPATH)/ScannerToken.h $(INPUTSERVICEPATH)/InputFile.h $(PARSERPATH)/Parser.h $(PARSERPATH)/ErrorInfo.h $(RANGESERVICE)/RangeService.h $(RANGESERVICE)/RangeObject.h
	$(CXX) $(COMPILEFLAG) -c src/main.cpp
Scanner.o: $(SCANNERPATH)/Scanner.cpp $(SCANNERPATH)/Scanner.h
	$(CXX) $(COMPILEFLAG) -c $(SCANNERPATH)/Scanner.cpp
ScannerToken.o: $(SCANNERPATH)/ScannerToken.cpp $(SCANNERPATH)/ScannerToken.h
	$(CXX) $(COMPILEFLAG) -c $(SCANNERPATH)/ScannerToken.cpp
InputFile.o: $(INPUTSERVICEPATH)/InputFile.cpp $(INPUTSERVICEPATH)/InputFile.h
	$(CXX) $(COMPILEFLAG) -c $(INPUTSERVICEPATH)/InputFile.cpp
Parser.o: $(PARSERPATH)/Parser.cpp $(PARSERPATH)/Parser.h
	$(CXX) $(COMPILEFLAG) -c $(PARSERPATH)/Parser.cpp
ErrorInfo.o: $(PARSERPATH)/ErrorInfo.cpp $(PARSERPATH)/ErrorInfo.h
	$(CXX) $(COMPILEFLAG) -c $(PARSERPATH)/ErrorInfo.cpp
RangeService.o: $(RANGESERVICE)/RangeService.cpp $(RANGESERVICE)/RangeService.h
	$(CXX) $(COMPILEFLAG) -c $(RANGESERVICE)/RangeService.cpp
RangeObject.o: $(RANGESERVICE)/RangeObject.cpp $(RANGESERVICE)/RangeObject.h
	$(CXX) $(COMPILEFLAG) -c $(RANGESERVICE)/RangeObject.cpp
