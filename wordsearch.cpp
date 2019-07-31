#include "chargrid.h"
#include <exception>
#include <algorithm>
using namespace std;

/**
 * Cleans the input string by removing any new line, tab, and
 * carriage return characters commonly seen in lf and crlf formats.
 */
void clean_string(string& str) {
	str.erase( remove_if(str.begin(), str.end(), [](char c){
		return c == '\n' || c == '\r' || c == '\t';
	}), str.end() );
}

/**
 * A simple driver program to run the word search algorithm.
 */
int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);

	// Open input grid file, construct CharGrid, and close file.
	if (argc != 2) throw invalid_argument("Usage: ./wordsearch grid.txt < word_list.txt > result.txt");
	ifstream fin (argv[1]);
	if (!fin.is_open()) throw runtime_error("Unable to open text grid file.");
	CharGrid cg (fin);
	fin.close();

	// Process each word coming in from standard input.
	for (string word; getline(cin, word); ) {
		clean_string(word);
		cg.check(word);
		cout << cg;
		cg.reset();
	}
}