/*
Copyright 2019. Siwei Wang.
*/
#include "chargrid.h"
#include <algorithm>
#include <cctype>
#include <exception>
#include <sstream>
using std::endl;
using std::getline;
using std::ifstream;
using std::ostream;
using std::runtime_error;
using std::string;
using std::vector;

std::ostream& operator<<(std::ostream& os, Direction dir) {
  switch (dir) {
    case Direction::North:
      os << "North";
      break;
    case Direction::South:
      os << "South";
      break;
    case Direction::East:
      os << "East";
      break;
    case Direction::West:
      os << "West";
      break;
    case Direction::NorthEast:
      os << "NorthEast";
      break;
    case Direction::NorthWest:
      os << "NorthWest";
      break;
    case Direction::SouthEast:
      os << "SouthEast";
      break;
    case Direction::SouthWest:
      os << "SouthWest";
      break;
  }
  return os;
}

CharGrid::CharGrid(ifstream& fin) {
  // Get the first line.
  string line;
  getline(fin, line);
  auto first = process_string(line);
  // Set NUM_COLS to number of chars in the first line.
  NUM_COLS = first.length();
  grid.emplace_back(first.begin(), first.end());

  // Read the file line by line.
  while (getline(fin, line)) {
    auto row = process_string(line);
    // Throw an exception of the grid format is off.
    if (row.length() != NUM_COLS) throw runtime_error("Incorrect grid format.");
    grid.emplace_back(row.begin(), row.end());
  }

  NUM_ROWS = grid.size();
}

void CharGrid::check(const string& str) {
  original = str;
  target = process_string(str);
  if (str.empty()) return;

  for (size_t row = 0; row < NUM_ROWS; ++row) {
    for (size_t col = 0; col < NUM_COLS; ++col) {
      // Only continue check if the first letter is a match.
      if (target.front() == at(row, col)) {
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

ostream& operator<<(ostream& os, const CharGrid& cg) {
  os << "Search results for " << cg.original << ":\n";
  // Print the list of records.
  if (cg.hits.empty()) {
    os << "No matches were found.\n";
  } else {
    // Print out the grid.
    string buffer;
    for (const auto& v : cg.grid) {
      for (char c : v) {
        buffer.push_back(c);
        buffer.push_back(' ');
      }
      buffer.push_back('\n');
    }
    os << buffer;
    for (const auto& rec : cg.hits) {
      os << "Row " << rec.row + 1 << ", Column " << rec.col + 1 << ", Heading "
         << rec.dir << ".\n";
    }
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

CharGrid::Record::Record(size_t row_in, size_t col_in, Direction dir_in)
    : row(row_in), col(col_in), dir(dir_in) {}

string CharGrid::process_string(string str) const {
  // Get rid of all non alphabetic characters in the string
  str.erase(
      remove_if(str.begin(), str.end(), [](char c) { return !isalpha(c); }),
      str.end());
  // Convert all letters in the string to lowercase.
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

inline char CharGrid::at(size_t row, size_t col) const {
  // Vector's at function will throw exceptions for us.
  return grid.at(row).at(col);
}

/**
 * Helper function that returns false if the moves causes a zero index to be
 * decremented. Otherwise, modifies row and col so that they have moved in the
 * desired direction.
 */
bool move_dir(size_t* row, size_t* col, Direction dir) {
  // Switch case must also check for the case where row/col = 0 and we
  // decrement.
  switch (dir) {
    case Direction::North:
      if (!*row) return false;
      --*row;
      break;
    case Direction::South:
      ++*row;
      break;
    case Direction::East:
      ++*col;
      break;
    case Direction::West:
      if (!*col) return false;
      --*col;
      break;
    case Direction::NorthEast:
      if (!*row) return false;
      --*row;
      ++*col;
      break;
    case Direction::NorthWest:
      if (!*row) return false;
      if (!*col) return false;
      --*row;
      --*col;
      break;
    case Direction::SouthEast:
      ++*row;
      ++*col;
      break;
    case Direction::SouthWest:
      if (!*col) return false;
      ++*row;
      --*col;
      break;
  }
  return true;
}

bool CharGrid::check_dir(size_t row, size_t col, Direction dir) const {
  // Get iterator to first letter in target.
  string::const_iterator it(target.begin());
  do {
    // Checked to the end of the target, it's a match.
    if (it == target.end()) return true;
    // If the letters don't match, immediately toss out.
    if (*it++ != static_cast<char>(tolower(at(row, col)))) return false;
    // Move in direction. If out-of-bounds, see whether it's a full match.
    if (!move_dir(&row, &col, dir)) return it == target.end();
  } while (row < NUM_ROWS && col < NUM_COLS);
  // There is a match if we've made it to the end of the line.
  return it == target.end();
}

void CharGrid::highlight(size_t row, size_t col, Direction dir) {
  size_t i = 0;
  size_t row_original = row, col_original = col;
  do {
    grid.at(row).at(col) = static_cast<char>(toupper(at(row, col)));
    move_dir(&row, &col, dir);
  } while (++i < target.length() && row < NUM_ROWS && col < NUM_COLS);
  hits.emplace_back(row_original, col_original, dir);
}
