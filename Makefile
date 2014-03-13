eXeS = ccoincidences entropy outbin reverse subnet_calculator
# Comment out the line below if you don't have libgmp
eXeS += isprime

ccoincidences_OBJS = ccoincidences.o hextools.o map.o xor.o
entropy_OBJS = entropy.o map.o
entropy_LIBS = -lm
isprime_OBJS = isprime.o
isprime_LIBS = -lgmp
outbin_OBJS = hextools.o map.o outbin.o
reverse_OBJS = map.o reverse.o
subnet_calculator_OBJS = subnet_calculator.o

#DEBUG = yes
ifdef DEBUG
DBGFLAGS = -g -O0
else
DBGFLAGS = -O3
endif
CFLAGS = $(DBGFLAGS) -pipe -W -Wall

all: $(eXeS)

ccoincidences: $(ccoincidences_OBJS)
	$(CC) $(CFLAGS) -o $@ $(ccoincidences_OBJS)

entropy: $(entropy_OBJS)
	$(CC) $(CFLAGS) -o $@ $(entropy_OBJS) $(entropy_LIBS)

isprime: $(isprime_OBJS)
	$(CC) $(CFLAGS) -o $@ $(isprime_OBJS) $(isprime_LIBS)

outbin: $(outbin_OBJS)
	$(CC) $(CFLAGS) -o $@ $(outbin_OBJS)

reverse: $(reverse_OBJS)
	$(CC) $(CFLAGS) -o $@ $(reverse_OBJS)

subnet_calculator: $(subnet_calculator_OBJS)
	$(CC) $(CFLAGS) -o $@ $(subnet_calculator_OBJS)

.PHONY: clean check

check:
	clang --analyze $(CFLAGS) $(ccoincidences_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(entropy_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(isprime_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(outbin_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(reverse_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(subnet_calculator_OBJS:.o=.c)

clean:
	rm -f $(eXeS) *.o *.plist *~
