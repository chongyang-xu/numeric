CC = g++
C_FLAGS = -g -Wall -std=c++11
INCLUDE =
LIBS =
#wildcard对cpp文件进行展开
SRCS := $(wildcard *.cpp)
#将SRCS中后缀.cpp替换成空，即可执行程序的名字与cpp名字相同
TARGET  := $(patsubst %.cpp, %, $(SRCS))
OBJDIR = ./run

.cpp:
	$(CC) $(C_FLAGS) -o $@ $< $(INCLUDE) $(LIBS)
	mv $@ $(OBJDIR)
all: $(TARGET) clean
clean:
	rm -rf *.o
