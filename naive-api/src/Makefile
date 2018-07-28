# Makefile template for shared library

CXX = g++ # C compiler
CXXFLAGS = -fPIC -Wall -Wextra -O2 -g -std=c++11 -I../include/numeric/ # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = libnumeric.so # target lib

SRCS = blas.cpp decompose.cpp  eigen.cpp  lineareq.cpp mat_vec.cpp # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CXX) ${LDFLAGS} -o $@ $^

$(SRCS:.cpp=.d):%.d:%.cpp
	$(CXX) $(CXXFLAGS) -MM $< >$@

include $(SRCS:.cpp=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.d)
