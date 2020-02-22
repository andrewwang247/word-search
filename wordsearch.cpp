/*
Copyright 2019. Siwei Wang.
*/
#include <algorithm>
#include <exception>
#include "chargrid.h"
using std::cin;
using std::cout;
using std::ifstream;
using std::invalid_argument;
using std::ios_base;
using std::remove_if;
using std::string;

/**
 * Cleans the input string by removing any new line, tab, and
 * carriage return characters commonly seen in lf and crlf formats.
 */
string clean_string(string str) {
  str.erase(
      remove_if(str.begin(), str.end(),
                [](char c) { return c == '\n' || c == '\r' || c == '\t'; }),
      str.end());
  return str;
}

/**
 * A simple driver program to run the word search algorithm.
 */
int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);

  // Open input grid file, construct CharGrid, and close file.
  if (argc != 2)
    throw invalid_argument(
        "Usage: ./wordsearch grid.txt < word_list.txt > result.txt");
  ifstream fin(argv[1]);
  CharGrid cg(fin);
  fin.close();

  // Process each word coming in from standard input.
  for (string word; getline(cin, word);) {
    cg.check(clean_string(word));
    cout << cg;
    cg.reset();
  }
}
