# Personal Makefile for Word Search.
CXX = g++
CXX_FLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic
OPT = -O3 -DNDEBUG
DEBUG = -g3 -DDEBUG

EXECUTABLE = wordsearch
LINKEDFILES = chargrid

# Build optimized executable.
release : $(EXECUTABLE).cpp $(LINKEDFILES).cpp
	$(CXX) $(CXX_FLAGS) $(OPT) $(EXECUTABLE).cpp $(LINKEDFILES).cpp -o $(EXECUTABLE)

# Build with debug features.
debug : $(EXECUTABLE).cpp $(LINKEDFILES)
	$(CXX) $(CXX_FLAGS) $(DEBUG) $(EXECUTABLE).cpp $(LINKEDFILES).cpp -o $(EXECUTABLE)_debug


# Remove executable and all runtime outputs.
.PHONY : clean
clean : 
	rm -f $(EXECUTABLE) $(EXECUTABLE)_debug *.txt
