CXX=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb
BIN=hrachjar
RM=rm -rf

all: clean compile doc

compile: $(BIN)

$(BIN):
	mkdir -p ./temp
	$(CXX) -c $(CXXFLAGS) -o ./temp/CException.o src/CException.cpp
	$(CXX) -c $(CXXFLAGS) -o ./temp/CExpression.o src/CExpression.cpp
	$(CXX) -c $(CXXFLAGS) -o ./temp/CExpSeg.o src/CExpSeg.cpp
	$(CXX) -c $(CXXFLAGS) -o ./temp/CNumber.o src/CNumber.cpp
	$(CXX) -c $(CXXFLAGS) -o ./temp/main.o src/main.cpp
	g++ $(CXXFLAGS) -o ./hrachjar ./temp/CException.o ./temp/CExpression.o ./temp/CExpSeg.o ./temp/CNumber.o ./temp/main.o

run:
	./hrachjar

valgrind:
	valgrind --leak-check=full ./hrachjar

doc:
	$(RM) doc
	doxygen Doxyfile

clean:
	$(RM) doc temp $(BIN)
	$(RM) ./examples/*_out