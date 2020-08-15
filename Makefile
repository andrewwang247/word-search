# Personal Makefile for Word Search.
CXX := g++ -std=c++17
CXX_FLAGS := -Wall -Werror -Wextra -Wconversion -pedantic -Wfloat-equal -Wduplicated-branches -Wduplicated-cond -Wshadow -Wdouble-promotion -Wundef 
OPT := -O3 -DNDEBUG
DEBUG := -g3 -DDEBUG

EXECUTABLE = wordsearch
LINKEDFILE = chargrid

# Build optimized executable.
release : $(EXECUTABLE).cpp $(LINKEDFILE).cpp
	$(CXX) $(CXX_FLAGS) $(OPT) $(EXECUTABLE).cpp $(LINKEDFILE).cpp -o $(EXECUTABLE)

# Build with debug features.
debug : $(EXECUTABLE).cpp $(LINKEDFILE)
	$(CXX) $(CXX_FLAGS) $(DEBUG) $(EXECUTABLE).cpp $(LINKEDFILE).cpp -o $(EXECUTABLE)


# Remove executable and all runtime outputs.
.PHONY : clean
clean : 
	rm -f $(EXECUTABLE) *.txt
