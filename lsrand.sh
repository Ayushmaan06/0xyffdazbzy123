#!/bin/bash

# Step 1: Create a directory named file_listing and add 5 random files of different sizes
mkdir -p file_listing

# Create 5 files with random content and different sizes
for i in {1..5}; do
    base64 /dev/urandom | head -c $((RANDOM % 1024 + 256)) > file_listing/file"$i".txt
done

echo "5 random files created in 'file_listing' directory."

# Step 2: List the files in the directory, showing their size, modification time, and permissions
echo -e "\nListing files with details:"
ls -lh file_listing

# Step 3: Sort the files by size and display them
echo -e "\nFiles sorted by size:"
ls -lhS file_listing

# Step 4: Count the number of files in the directory and display the total count
file_count=$(ls -1 file_listing | wc -l)
echo -e "\nTotal number of files in 'file_listing': $file_count"

