CC = g++
AR = ar
CFLAGES = -std=c++11 -Wall -I../lib

OBJS = homework1.o homework2.o homework3.o

TARGET = ./libnum.a

$(TARGET):$(OBJS)
	$(AR)  -r  $(TARGET) $(OBJS)

$(OBJS):%.o:%.cpp
	$(CC) -c $<  $(CFLAGES) -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)
