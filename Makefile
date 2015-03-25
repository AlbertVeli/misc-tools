eXeS = bitreverse bitshiftleft ccoincidences entropy invert numunprintable outbin reverse subnet_calculator xorfiles
# Comment out the line below if you don't have libgmp
eXeS += isprime

ccoincidences_OBJS = ccoincidences.o hextools.o map.o xor.o
entropy_OBJS = entropy.o map.o
entropy_LIBS = -lm
invert_OBJS = hextools.o invert.o map.o
isprime_OBJS = isprime.o
isprime_LIBS = -lgmp
numunprintable_OBJS = hextools.o map.o numunprintable.o
outbin_OBJS = hextools.o map.o outbin.o
reverse_OBJS = map.o reverse.o
bitreverse_OBJS = map.o bitreverse.o
bitshiftleft_OBJS = map.o bitshiftleft.o
subnet_calculator_OBJS = subnet_calculator.o
xorfiles_OBJS = hextools.o map.o xor.o xorfiles.o

DEBUG = yes
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

invert: $(invert_OBJS)
	$(CC) $(CFLAGS) -o $@ $(invert_OBJS)

isprime: $(isprime_OBJS)
	$(CC) $(CFLAGS) -o $@ $(isprime_OBJS) $(isprime_LIBS)

numunprintable: $(numunprintable_OBJS)
	$(CC) $(CFLAGS) -o $@ $(numunprintable_OBJS)

outbin: $(outbin_OBJS)
	$(CC) $(CFLAGS) -o $@ $(outbin_OBJS)

reverse: $(reverse_OBJS)
	$(CC) $(CFLAGS) -o $@ $(reverse_OBJS)

bitreverse: $(bitreverse_OBJS)
	$(CC) $(CFLAGS) -o $@ $(bitreverse_OBJS)

bitshiftleft: $(bitshiftleft_OBJS)
	$(CC) $(CFLAGS) -o $@ $(bitshiftleft_OBJS)

subnet_calculator: $(subnet_calculator_OBJS)
	$(CC) $(CFLAGS) -o $@ $(subnet_calculator_OBJS)

xorfiles: $(xorfiles_OBJS)
	$(CC) $(CFLAGS) -o $@ $(xorfiles_OBJS)

.PHONY: clean check

check:
	clang --analyze $(CFLAGS) $(ccoincidences_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(entropy_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(invert_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(isprime_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(numunprintable_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(outbin_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(reverse_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(bitreverse_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(bitshiftleft_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(subnet_calculator_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(xorfiles_OBJS:.o=.c)

clean:
	rm -f $(eXeS) *.o *.plist *~
