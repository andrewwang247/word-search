# Personal Makefile for Word Search.
CXX = g++
CXX_FLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic
OPT = -O3 -DNDEBUG
DEBUG = -g3 -DDEBUG
EXECUTABLE = wordsearch
OBJECTFILES = chargrid.cpp

# Build optimized executable.
scrabble : $(EXECUTABLE).cpp
	$(CXX) $(CXX_FLAGS) $(OPT) $(EXECUTABLE).cpp $(OBJECTFILES) -o $(EXECUTABLE)

# Build with debug features.
debug : $(EXECUTABLE).cpp
	$(CXX) $(CXX_FLAGS) $(DEBUG) $(EXECUTABLE).cpp $(OBJECTFILES) -o $(EXECUTABLE)_debug


# Remove executable and all runtime outputs.
.PHONY : clean
clean : 
	rm -f $(EXECUTABLE) $(EXECUTABLE)_debug *.o
