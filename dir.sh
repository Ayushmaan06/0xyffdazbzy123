#!/bin/bash

# Step 1: Create a directory named "test_directory"
mkdir test_directory
cd test_directory

touch file1.txt file2.txt file3.txt

cd ..
echo "Files in test_directory before deletion:"
ls test_directory
cd test_directory
rm file2.txt
echo "'file2.txt' deleted."

cd ..
x=$(ls test_directory | wc -l)  # Capturing number of remaining files
if [[ $x -eq 0 ]]; then
    rmdir test_directory
    echo "'test_directory' is empty and has been deleted."
else
    echo "'test_directory' is not empty, cannot delete."
fi

