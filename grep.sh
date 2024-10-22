#!/bin/bash

# Step 1: Create a text file named data.txt with at least 5 lines of text
cat <<EOL > data.txt
This is the first line.
The second line contains a word.
Here is the third line.
Another word appears in the fourth line.
Finally, this is the fifth line.
EOL
echo "File 'data.txt' created with 5 lines of text."

# Step 2: Use the grep command to search for a specific word in data.txt
read -p "Enter the word to search for: " search_word
grep -n "$search_word" data.txt > /dev/null 2>&1

# Step 3 & 4: Display the line numbers along with matching lines, or a message if not found
if [ $? -eq 0 ]
then
    echo "Matching lines with line numbers:"
    grep -n "$search_word" data.txt
else
    echo "The word '$search_word' was not found in 'data.txt'."
fi

