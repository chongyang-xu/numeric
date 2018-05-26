CC = g++
C_FLAGS = -g -Wall -std=c++11
INCLUDE = -I../include/numeric/
LIBS = -L../lib/ -lnumeric
SRCS := $(wildcard *.cpp)
TARGET  := $(patsubst %.cpp, %, $(SRCS))
OBJDIR = .

.cpp:
	$(CC) $(C_FLAGS) -o $@ $< $(INCLUDE) $(LIBS)
	mv $@ $(OBJDIR)
all: $(TARGET) clean
clean:
	rm -rf *.o
