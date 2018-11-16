#to use release, run 'make ver=release'
ver = debug

CC = g++
LD = g++
CFLAGS += -Wall -I./inc --std=c++11 -g -Wno-sign-compare
#LDFLAGS = -lpthread -Wunused-command-line-argument

ifeq ($(ver), debug)
CFLAGS += -D_DEBUG
endif

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
TARGET = lottery

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

