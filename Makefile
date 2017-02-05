CC = gcc
CFLAGS = -O -Wall
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)


all: ass3

ass3: $(OBJS)
	$(CC) $(CFLAGS) -o ass3 $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
