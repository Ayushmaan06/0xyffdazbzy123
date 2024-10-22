#!/bin/bash

# Step 1: Create two text files: file1.txt and file2.txt
touch file1.txt file2.txt
echo "file1.txt and file2.txt created."

# Step 2: Add some content to both files
echo "This is the content of file1." > file1.txt
echo "This is the content of file2." > file2.txt
echo "Content added to file1.txt and file2.txt."

# Step 3: Display the contents of both files using cat
echo "Displaying contents of file1.txt:"
cat file1.txt
echo ""
echo "Displaying contents of file2.txt:"
cat file2.txt
echo ""

# Step 4: Combine the contents of both files into a new file called combined.txt
cat file1.txt file2.txt > combined.txt
echo "Contents of file1.txt and file2.txt combined into combined.txt."

# Step 5: Display the contents of combined.txt on the terminal
echo "Displaying contents of combined.txt:"
cat combined.txt

