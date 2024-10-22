#!/bin/bash

# 1. Create 5 directories named dir1 through dir5
for i in {1..5}; do
    mkdir "dir$i"
done
echo "Directories dir1 to dir5 created."

# 2. Inside each directory, create a file with the same name as the directory
for i in {1..5}; do
    touch "dir$i/dir$i.txt"
done
echo "Files dir1.txt to dir5.txt created in their respective directories."

# 3. Display the structure of all directories and files
echo "Directory structure:"
ls -R

# 4. Delete all the directories and files created
for i in {1..5}; do
    rm -r "dir$i"
done
echo "All directories and files deleted."

# Confirm deletion
echo "Current directory structure after deletion:"
ls

