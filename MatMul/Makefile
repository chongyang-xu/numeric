# This is a makefile intended for compiling simple C++ projects.
# It assumes that you have one or more source files in the main directory,
#    each of which contains an "int main()".
# There may also be a "src" directory, containing additional source files.
# All include files will be automatically listed as dependencies.

# Default build variables, can be overridden by command line options.

CXX      = g++
CPPFLAGS = -std=c++11 
CXXFLAGS = -fopenmp -mavx2  -mfma -Wall  -Wextra -O3
LDFLAGS  =
LDLIBS   = -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl -lgomp
RM       = rm -f

# Additional flags that are necessary to compile.
# Even if not specified on the command line, these should be present.

override CPPFLAGS += -Iinclude 	-I../../dev_util -I/opt/intel-2017.6.064/compilers_and_libraries_2017.6.256/linux/mkl/include
override CXXFLAGS += -D MKL
override LDFLAGS  += -L/opt/intel-2018/compilers_and_libraries_2018.2.199/linux/mkl/lib/intel64/
override LDLIBS   +=

# EVERYTHING PAST HERE SHOULD WORK AUTOMATICALLY

.SECONDARY:

include PrettyPrint.inc

# Find the source files that will be used.
EXE_SRC_FILES = $(wildcard *.cpp)
EXECUTABLES = $(patsubst %.cpp,bin/%,$(EXE_SRC_FILES))
SRC_FILES = $(wildcard src/*.cpp)
O_FILES = $(patsubst %.cpp,build/%.o,$(SRC_FILES))

all: $(EXECUTABLES)

# Update dependencies with each compilation
override CPPFLAGS += -MMD
-include $(shell find build -name "*.d" 2> /dev/null)

bin/%: build/%.o $(O_FILES)
	@mkdir -p bin
	@$(call run_and_test,$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@)

build/%.o: %.cpp
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build
