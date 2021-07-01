
COMPILE=gcc
RM=rm -f
CFLAGS=-g
LDFLAGS=-g
LDLIBS=
SRCS=main.c dictutil.c vm.c tibutil.c words/io.c words/math.c words/stack.c words/cond.c words/define.c words/sys.c words/dict.c
OBJS=$(subst .c,.o,$(SRCS))
TARGET=forthish

all: $(OBJS)
	$(COMPILE) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS) $(TARGET)
