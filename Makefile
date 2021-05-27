all: main.exe

main.exe: String.o BigInt.o BigNumTest.o
	
	g++ -o main String.o BigInt.o BigNumTest.o

unit2: Unit2.o BigInt.o String.o catch_amalgamated.o
	g++ -o unit2 Unit2.o BigInt.o String.o catch_amalgamated.o

Unit2.o: Unit2.cpp
	g++ -c Unit2.cpp

String.o: String.cpp
	g++ -c String.cpp

BigInt.o: BigInt.cpp
	g++ -c BigInt.cpp

utest: UnitTests.o BigInt.o String.o catch_amalgamated.o
	g++ -o utest UnitTests.o BigInt.o String.o catch_amalgamated.o

catch_amalgamated.o: catch_amalgamated.cpp
	g++ -c catch_amalgamated.cpp

BigNumTest.o: BigNumTest.cpp
	g++ -c BigNumTest.cpp

UnitTests.o: UnitTests.cpp
	g++ -c UnitTests.cpp

clean:
	del /f *.o main.exe