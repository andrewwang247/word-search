# Word Search

The word search program takes in a grid as a text file and queries the user for a list of words to search. For each word, the program searches for and logs every possible match in the grid. When finished, the user receives (for each word):

- A formatted grid with all instances of the word highlighted.

- A listing of every match that includes the row/column coordinates of the first letter and the directional orientation of the rest of the word.

Suggested usage: ./wordsearch word_grid.txt < target_words.txt > results.txt

## Approach

The CharGrid is a two-dimensional array of characters that holds the search space.
The program iterates over each character in the array and looks in the 8 compass directions for matches.
Should it find a match, it highlights that word and logs the hit in a vector.
Finally, the program prints all matches that were found to std::cout.
If any runtime errors are encountered, exceptions will be thrown and the program terminated.

## Format

- The input grid text file must be a rectangular character grid. All white spaces except new-lines are ignored.
- For the list of words piped into std::cin, I recommend using a text file where each word is on its own line. Valid words may include non-alphabetic characters may be included - they are ignored by the search.
