CC=gcc
CFLAGS=-std=gnu99 -Wall -W

traceroute: traceroute.c icmp.o honest_utils.o printing_utils.o receiving_utils.o sending_utils.o sockwrap.o

icmp.o: icmp.c

honest_utils.o: honest_utils.c

printing_utils.o: printing_utils.c

receiving_utils.o: receiving_utils.c

sending_utils.o: sending_utils.c

sockwrap.o: sockwrap.c

clean:
	rm -f *.o

distclean: clean
	rm -f traceroute
