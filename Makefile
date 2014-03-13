eXeS = entropy subnet_calculator

entropy_OBJS = entropy.o map.o
entropy_LIBS = -lm
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

subnet_calculator: $(subnet_calculator_OBJS)
	$(CC) $(CFLAGS) -o $@ $(subnet_calculator_OBJS) $(LIBS)

.PHONY: clean check

check:
	clang --analyze $(CFLAGS) $(entropy_OBJS:.o=.c)
	clang --analyze $(CFLAGS) $(subnet_calculator_OBJS:.o=.c)

clean:
	rm -f $(eXeS) $(entropy_OBJS) $(subnet_calculator_OBJS) *.plist *~
