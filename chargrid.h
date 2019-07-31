#pragma once
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// The 8 possible directions on a two-dimensional rectangular grid.
enum class Direction {
	North, South, East, West, NorthEast, NorthWest, SouthEast, SouthWest
};

// Print operator for Directions
std::ostream& operator<< (std::ostream& os, Direction cg);

/**
 * The CharGrid class holds the word search space containing the letter to be searched.
 * It allows for quick character retrieval and toggling of upper/lower cases.
 * Furthermore, the API supports adjacent searches that include bound checking.
 * The first vector dimension is the row number (up/down). The second is the column.
 */
class CharGrid {
public:

	// Constructor reads from input file.
	explicit CharGrid(std::ifstream& fin);

	/**
	 * The public interface function for finding all instances of str in grid
	 * If str is found, check highlights all instance of them.
	 * Cleans str so that it is the correct format.
	 * MODIFIES: grid, hits, str, original.
	 */
	void check(std::string& str);

	/**
	 * Prints to output stream os. Format as follows.
	 * 
	 * Search results for <target>:
	 * |--------------------------------|		(hits are capitalized)
	 * |--------------------------------|
	 * |--------------------------------|
	 * |--------------------------------|
	 * |--------------------------------|
	 * |--------------------------------|
	 * Row r, Col c, Direction dir (list all results verbally)
	 */
	friend std::ostream& operator<< (std::ostream& os, const CharGrid& cg);

	// Reset everything back to original state after constructor.
	void reset() noexcept;

private:

	// A record-keeping of each hit of target found in grid.
	struct Record {
		size_t row, col;
		Direction dir;
	};

	// Two-dimensional array of characters that stores word search space.
	std::vector< std::vector<char> > grid;

	// Keeps track of all hits of target found in grid.
	std::vector<Record> hits;

	// Stores the number of rows and columns for easy access. Effectively const.
	size_t NUM_ROWS, NUM_COLS;

	// The target string that we are looking for + the original input string for printing.
	std::string target, original;

	// Processes str such that it is in the correct format for insertion.
	void process_string(std::string& str) const;

	// Retrieves the character at the given coordinates.
	inline char at(size_t row, size_t col) const;

	// Checks for target at (row, col) in direction dir.
	bool check_dir(size_t row, size_t col, Direction dir) const;

	/**
	 * Causes the letters starting from (row, col) going target.length distance in
	 * direction dir to be uppercased. Does not modify already uppercase letters.
	 * Furthermore, adds to the hits vector.
	 * REQUIRES: No boundary overflows. Confirm first with check_dir.
	 * MODIFIES: grid, hits
	 */
	void highlight(size_t row, size_t col, Direction dir);
};