#!/bin/bash

# Prompt the user for input
read -p "Enter the number of terms: " n

# Initialize the first two terms of the Fibonacci sequence
a=0
b=1

# Print the Fibonacci series up to n terms
echo "Fibonacci series up to $n terms:"

for (( i=0; i<n; i++ ))
do
    echo -n "$a "
    # Calculate the next term
    fn=$((a + b))
    a=$b
    b=$fn
done

echo # Print a new line at the end

