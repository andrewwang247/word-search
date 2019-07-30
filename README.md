# Word Search

The word search program takes in a grid as a text file and queries the user for a list of words to search.
Suggested usage: ./wordsearch word_grid.txt < target_words.txt > results.txt

## Approach

The CharGrid is a two-dimensional array of characters that holds the search space.
The program iterates over each character in the array and looks in the 8 compass directions for matches.
Should it find a match, it highlights that word and logs the hit in a vector.
Finally, the program prints out all matches that were found in a neat format.
