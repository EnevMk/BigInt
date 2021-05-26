all: main.exe

main.exe: String.o BigInt.o BigNumTest.o
	
	g++ -o main String.o BigInt.o BigNumTest.o

String.o: String.cpp
	g++ -c String.cpp

BigInt.o: BigInt.cpp
	g++ -c BigInt.cpp

BigNumTest.o: BigNumTest.cpp
	g++ -c BigNumTest.cpp