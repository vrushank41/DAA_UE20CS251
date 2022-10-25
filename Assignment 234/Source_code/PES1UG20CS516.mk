PES1UG20CS516.exe: client.o PES1UG20CS516.o
				gcc client.o PES1UG20CS516.o -o  PES1UG20CS516.exe

client.o : client.c header.h
			gcc -c client.c

PES1UG20CS516.o : PES1UG20CS516.c header.h
				gcc -c PES1UG20CS516.c