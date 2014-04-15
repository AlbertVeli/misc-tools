eXeS = aesnitest
OBJS = aes.o aes128ni.o aesnitest.o caps.o ../hextools.o ../xor.o

CFLAGS = -O3 -W -Wall
ASFLAGS =

all: $(eXeS)

aesnitest: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(eXeS) $(OBJS) *~
