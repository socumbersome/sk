CC=gcc
CFLAGS=-std=gnu99 -Wall -W

client-udp: client-udp.c honest_utils.o receiving_utils.o sending_utils.o parsing_utils.o sockwrap.o -lrt

honest_utils.o: honest_utils.c

receiving_utils.o: receiving_utils.c

sending_utils.o: sending_utils.c

parsing_utils.o: parsing_utils.c

sockwrap.o: sockwrap.c

clean:
	rm -f *.o

distclean: clean
	rm -f client-udp
