
COMPILE=gcc
RM=rm -f
CFLAGS=-g
LDFLAGS=-g
LDLIBS=
SRCS=main.c dict.c vm.c words/io.c words/math.c words/stack.c words/cond.c words/variable.c words/compile.c
OBJS=$(subst .c,.o,$(SRCS))
TARGET=forthish

all: $(OBJS)
	$(COMPILE) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS) $(TARGET)
