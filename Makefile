CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -pthread

# List of source files
SRCS = shellex.c csapp.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = sh257

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJS)
