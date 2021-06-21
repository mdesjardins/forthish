
COMPILE=gcc
RM=rm -f
CFLAGS=-g
LDFLAGS=-g
LDLIBS=
SRCS=main.c stack.c dict.c words/io.c words/math.c words/stack_manip.c words/cond.c words/variable.c
OBJS=$(subst .c,.o,$(SRCS))
TARGET=forthish

all: $(OBJS)
	$(COMPILE) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS) $(TARGET)
