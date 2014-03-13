eXeS = entropy reverse subnet_calculator
# Comment out the line below if you don't have libgmp
eXeS += isprime

entropy_OBJS = entropy.o map.o
entropy_LIBS = -lm
isprime_OBJS = isprime.o
isprime_LIBS = -lgmp
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

entropy: $(entropy_OBJS)
	$(CC) $(CFLAGS) -o $@ $(entropy_OBJS) $(entropy_LIBS)

isprime: $(isprime_OBJS)
	$(CC) $(CFLAGS) -o $@ $(isprime_OBJS) $(isprime_LIBS)

reverse: $(reverse_OBJS)
	$(CC) $(CFLAGS) -o $@ $(reverse_OBJS) $(reverse_LIBS)

subnet_calculator: $(subnet_calculator_OBJS)
	$(CC) $(CFLAGS) -o $@ $(subnet_calculator_OBJS)

.PHONY: clean check

check:
	clang --analyze $(CFLAGS) $(entropy_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(isprime_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(reverse_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(subnet_calculator_OBJS:.o=.c)

clean:
	rm -f $(eXeS) $(entropy_OBJS) $(isprime_OBJS) $(reverse_OBJS) $(subnet_calculator_OBJS) *.plist *~
