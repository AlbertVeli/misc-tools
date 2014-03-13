eXe = subnet_calculator
OBJS = $(eXe).o

#DEBUG = yes
ifdef DEBUG
DBGFLAGS = -g -O0
else
DBGFLAGS = -O3
endif
CFLAGS = $(DBGFLAGS) -pipe -W -Wall -D_GNU_SOURCE

all: $(eXe)

$(eXe): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean check

check:
	clang --analyze $(CFLAGS) $(OBJS:.o=.c)

clean:
	rm -f $(eXe) $(OBJS) *.plist *~
