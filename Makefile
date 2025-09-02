CC := gcc
STD := c11
CFLAGS  := -std=$(STD) -Wall -Wextra -pedantic -g
LDLIBS  := 

SRCS := main.c libs/dray.c libs/builtins.c
OBJS := $(SRCS:.c=.o)
TARGET := main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) -Ilibs $(CFLAGS) -c -o $@ $<

# make run ARGS="com"
run: $(TARGET)
	./$(TARGET) $(ARGS)

run-sim: $(TARGET)
	./$(TARGET) sim

run-com: $(TARGET)
	./$(TARGET) com

run-asm: output.asm
	nasm -felf64 -o output.o output.asm
	ld output.o -o output
	./output

clean:
	rm -f $(TARGET) $(OBJS)
