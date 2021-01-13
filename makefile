#creating the g++ variable containing the compiler instruction
CC = g++
#creating the -c -Wall variable containing compilation parameters
CFLAGS = -c -Wall

#compiling the two files to get the final one which would be musicShop.cpp and components.cpp
final: musicShop.o util.o components.o
	$(CC) musicShop.o components.o util.o -o final

#compiling just the musicShop.cpp file even though musicShop,h is not compulsory, it is just for precaution
musicShop.o: musicShop.cpp musicShop.hpp
	$(CC) $(CFLAGS) musicShop.cpp

util.o: util.cpp musicShop.hpp
	$(CC) $(CFLAGS) util.cpp

#compiling just the components.cpp file
components.o: components.cpp musicShop.hpp
	$(CC) $(CFLAGS) components.cpp

#clearing all copild files
clear:
	rm *.o final