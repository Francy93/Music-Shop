#creating the g++ variable containing the compiler instruction
CC = g++
#creating the -c -Wall variable containing compilation parameters
CFLAGS = -c -Wall

#compiling the two files to get the final one which would be musicShop.cpp and components.cpp
final: musicShop.o components.o
	$(CC) musicShop.o components.o -o final

#compiling just the musicShop.cpp file even though musicShop,h is not compulsory, it is just for precaution
musicShop.o: musicShop.cpp components.hpp
	$(CC) $(CFLAGS) musicShop.cpp

#compiling just the components.cpp file
components.o: components.cpp components.hpp
	$(CC) $(CFLAGS) components.cpp

#clearing all copild files
clear:
	rm *.o final