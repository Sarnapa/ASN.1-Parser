CXX := g++
COMPILEFLAG := -std=c++11
SCANNERPATH := src/Scanner
INPUTSERVICEPATH := src/InputService

asn1Parser: main.o Scanner.o ScannerToken.o InputFile.o
	$(CXX) $(COMPILEFLAG) -o asn1Parser main.o Scanner.o ScannerToken.o InputFile.o
main.o: src/main.cpp  $(SCANNERPATH)/Scanner.h $(SCANNERPATH)/ScannerToken.h $(INPUTSERVICEPATH)/InputFile.h
	$(CXX) $(COMPILEFLAG) -c src/main.cpp
Scanner.o: $(SCANNERPATH)/Scanner.cpp $(SCANNERPATH)/Scanner.h
	$(CXX) $(COMPILEFLAG) -c $(SCANNERPATH)/Scanner.cpp
ScannerToken.o: $(SCANNERPATH)/ScannerToken.cpp $(SCANNERPATH)/ScannerToken.h
	$(CXX) $(COMPILEFLAG) -c $(SCANNERPATH)/ScannerToken.cpp
InputFile.o: $(INPUTSERVICEPATH)/InputFile.cpp $(INPUTSERVICEPATH)/InputFile.h
	$(CXX) $(COMPILEFLAG) -c $(INPUTSERVICEPATH)/InputFile.cpp
