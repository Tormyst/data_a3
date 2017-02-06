CC = g++
CPPFLAGS = -std=c++11
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)


all: ass3

ass3: $(OBJS)
	$(CC) $(CPPFLAGS) -o ass3 $(OBJS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<
