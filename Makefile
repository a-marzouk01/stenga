CC := gcc
STD := c11
CFLAGS  := -std=$(STD) -Wall -Wextra -pedantic -g
LDLIBS  := 

SRCS := main.c libs/dray.c
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

clean:
	rm -f $(TARGET) $(OBJS)
