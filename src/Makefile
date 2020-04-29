CC=g++
FLAGS=-c -Wall -std=c++14 
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SOURCEDIR = source
BUILDDIR = build
EXECUTABLE = pacoronam

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: dir $(BUILDDIR)/$(EXECUTABLE) run

dir:
	@mkdir -p $(BUILDDIR)

run: 
	@./$(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LIBFLAGS)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(FLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm -f $(BUILDDIR)/*o $(BUILDDIR)/$(EXECUTABLE)