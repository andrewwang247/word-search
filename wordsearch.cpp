#include "chargrid.h"
#include <exception>
using namespace std;

/**
 * A simple driver program to run the word search algorithm.
 */
int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);

	if (argc != 2) throw invalid_argument("Provide only the text grid file.");
	ifstream fin (argv[1]);
	if (!fin.is_open()) throw runtime_error("Unable to text grid file.");
	CharGrid cg (fin);
	fin.close();

	for (string word; cin >> word; ) {
		cg.check(word);
		cout << cg;
		cg.reset();
	}
}