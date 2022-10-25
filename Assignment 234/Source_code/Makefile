##
# DAA Assignment 234
#
# @file
# @version 0.1
all: a.out

a.out: $(PES1UG20CS516).o client.o
	$(CC) $(PES1UG20CS516).o client.o

client.o: client.c
	$(CC) -c client.c

$(PES1UG20CS516).o: $(PES1UG20CS516).c
	$(CC) -c -Wall -pedantic $(PES1UG20CS516).c

.PHONEY: clean

clean:
	rm client.o $(PES1UG20CS516).o a.out

# end
