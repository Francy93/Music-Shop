#creating the g++ variable containing the compiler instruction
CC = g++
#creating the -c -Wall variable containing compilation parameters
CFLAGS = -c -Wall

#compiling the two files to get the final one which would be myshell.cpp and utility.cpp
final: myshell.o utility.o
	$(CC) myshell.o utility.o -o final

#compiling just the myshell.cpp file even though myshell,h is not compulsory, it is just fr precaution
myshell.o: myshell.cpp myshell.h
	$(CC) $(CFLAGS) myshell.cpp

#compiling just the utility.cpp file
utility.o: utility.cpp myshell.h
	$(CC) $(CFLAGS) utility.cpp

#clearing all copild files
clear:
	rm *.o final