CC = gcc
CFLAGS = -g -Wall -Werror -pedantic
CFLAGS += -pthread

parser:	parser.o card.h  read_csv.o  format_csv.o utils.o

parser.o:	parser.c card.h config.h read_csv.h apue.h utils.h

read_csv.o:	read_csv.c card.h format_csv.h read_csv.h error.c apue.h config.h utils.h

format_csv.o:	format_csv.c format_csv.h card.h read_csv.h config.h

utils.o:	utils.c card.h config.h apue.h

error.o:	error.c apue.h

clean:
	rm -f *.o core parser *.bin *.txt

run:
	./parser