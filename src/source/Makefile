# All .cc files are assumed to be source files
SRCS=$(wildcard *.cpp)
# Dependency files, automatically generated and put into `build` folder
DEPS=$(patsubst %.cpp,build/%.d,$(SRCS))
# Object files (also in `build` folder)
OBJS=$(DEPS:.d=.o)
# C compiler and its compilation flags (can be overriden on the command line)
CXX?=-c
CXXFLAGS?=-std=c++14 -O3 -Wall -g -Werror
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

# Default target (it comes first), conventionally called `all`

all:	Pacoronam

# Removes the build folder, but keeps generated executable if present
clean:
	rm -rf build

# Removes both the build folder and generated executable
dist-clean:	clean
	rm -f power11


Pacoronam:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBFLAGS)

# Include generated dependencies, rebuilding them if necessary
include $(DEPS)

# Rule to build dependency files
build/%.d:	%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $< -MM -MT $(patsubst %.cpp,build/%.o,$<) -MF $@ $(LIBFLAGS)

# Rule to build object files
build/%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBFLAGS)

# Phony rules are those that do not correspond to an actual file
.PHONY: all clean dist-clean