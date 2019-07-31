#include "chargrid.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <exception>
using namespace std;

CharGrid::CharGrid(ifstream& fin) {
	// Get the first line.
	string line;
	getline(fin, line);
	process_string(line);
	// Set NUM_COLS to number of chars in the first line.
	NUM_COLS = line.length();
	grid.push_back( vector<char> (line.begin(), line.end()) );

	// Read the file line by line.
	while( getline(fin, line) ) {
		process_string(line);
		// Throw an exception of the grid format is off.
		if (line.length() != NUM_COLS) throw domain_error("Incorrect grid format.");
		grid.push_back( vector<char> (line.begin(), line.end()) );
	}

	NUM_ROWS = grid.size();
}

void CharGrid::check(string& str) {
	// Set original to exact input and new target to input string.
	original = str;
	process_string(str);
	target = str;
	if (str.empty()) return;
	
	for (size_t row = 0; row < NUM_ROWS; ++row) {
		for (size_t col = 0; col < NUM_COLS; ++col) {
			// Only continue check if the first letter is a match.
			if ( target.front() == at(row, col) ) {
				if (check_dir(row, col, Direction::North))
					highlight(row, col, Direction::North);

				if (check_dir(row, col, Direction::South))
					highlight(row, col, Direction::South);

				if (check_dir(row, col, Direction::East))
					highlight(row, col, Direction::East);

				if (check_dir(row, col, Direction::West))
					highlight(row, col, Direction::West);

				if (check_dir(row, col, Direction::NorthEast))
					highlight(row, col, Direction::NorthEast);

				if (check_dir(row, col, Direction::NorthWest))
					highlight(row, col, Direction::NorthWest);

				if (check_dir(row, col, Direction::SouthEast))
					highlight(row, col, Direction::SouthEast);

				if (check_dir(row, col, Direction::SouthWest))
					highlight(row, col, Direction::SouthWest);
			}
		}
	}
}

ostream& operator<< (ostream& os, const CharGrid& cg) {
	os << "Search results for " << cg.original << ":\n";
	// Print the list of records.
	if (cg.hits.empty()) {
		os << "No matches were found.\n";
	} else {
		// Print out the grid.
		string buffer;
		for_each(cg.grid.begin(), cg.grid.end(), [&buffer](const vector<char>& v){
			for_each(v.begin(), v.end(), [&buffer](char c){
				buffer.push_back(c);
				buffer.push_back(' ');
			});
			buffer.push_back('\n');
		});
		os << buffer;
		for_each(cg.hits.begin(), cg.hits.end(), [&os](const CharGrid::Record& rec) {
			os << "Row " << rec.row + 1 << ", Column " << rec.col + 1 << ", Heading ";
			switch (rec.dir) {
				case Direction::North:
					os << "North.\n";
					break;
				case Direction::South:
					os << "South.\n";
					break;
				case Direction::East:
					os << "East.\n";
					break;
				case Direction::West:
					os << "West.\n";
					break;
				case Direction::NorthEast:
					os << "NorthEast.\n";
					break;
				case Direction::NorthWest:
					os << "NorthWest.\n";
					break;
				case Direction::SouthEast:
					os << "SouthEast.\n";
					break;
				case Direction::SouthWest:
					os << "SouthWest.\n";
					break;
			}
		});
	}
	os << endl;
	return os;
}

void CharGrid::reset() noexcept {
	hits.clear();
	target.clear();
	original.clear();
	for (auto& v : grid)
		for (char& c : v) c = static_cast<char>(tolower(c));
}

void CharGrid::process_string(string& str) const {
	// Get rid of all non alphabetic characters in the string
	str.erase( remove_if(str.begin(), str.end(), [](char c){ return !isalpha(c); }), str.end());
	// Convert all letters in the string to lowercase.
	for_each(str.begin(), str.end(), [](char& c){ c = static_cast<char>(tolower(c)); });
}

inline char CharGrid::at(size_t row, size_t col) const {
	// Vector's at function will throw exceptions for us.
	return grid.at(row).at(col);
}

/**
 * Helper function that returns false if the moves causes a zero index to be decremented.
 * Otherwise, modifies row and col so that they have moved in the desired direction.
 */
bool move_dir(size_t& row, size_t& col, Direction dir) {
	// Switch case must also check for the case where row/col = 0 and we decrement.
	switch (dir) {
		case Direction::North:
			if (!row) return false;
			--row;
			break;
		case Direction::South:
			++row;
			break;
		case Direction::East:
			++col;
			break;
		case Direction::West:
			if (!col) return false;
			--col;
			break;
		case Direction::NorthEast:
			if (!row) return false;
			--row;
			++col;
			break;
		case Direction::NorthWest:
			if (!row) return false;
			if (!col) return false;
			--row;
			--col;
			break;
		case Direction::SouthEast:
			++row;
			++col;
			break;
		case Direction::SouthWest:
			if (!col) return false;
			++row;
			--col;
			break;
	}
	return true;	
}

bool CharGrid::check_dir(size_t row, size_t col, Direction dir) const {
	// Get iterator to first letter in target.
	string::const_iterator it ( target.begin() );
	do {
		// Checked to the end of the target, it's a match.
		if ( it == target.end() ) return true;
		// If the letters don't match, immediately toss out.
		if (*it++ != static_cast<char>( tolower( at(row, col) ) ) ) return false;
		// Move in direction. If out-of-bounds, see whether it's a full match.
		if ( !move_dir(row, col, dir) ) return it == target.end();		
	} while ( row < NUM_ROWS && col < NUM_COLS );
	// There is a match if we've made it to the end of the line.
	return it == target.end();
}

void CharGrid::highlight(size_t row, size_t col, Direction dir) {
	size_t i = 0;
	size_t row_original = row, col_original = col;
	do {
		grid.at(row).at(col) = static_cast<char>( toupper( at(row, col) ) );
		move_dir(row, col, dir);
	} while (++i < target.length() && row < NUM_ROWS && col < NUM_COLS );
	hits.push_back( {row_original, col_original, dir} );
}