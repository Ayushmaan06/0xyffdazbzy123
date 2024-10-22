#!/bin/bash

# Prompt the user for input
read -p "Enter a number: " n

# Initialize factorial to 1
factorial=1

# Check if n is a valid positive integer
if [ $n -lt 0 ]; then
    echo "Factorial is not defined for negative numbers."
else
    # Calculate factorial using a for loop
    for (( i=1; i<=n; i++ ))
    do
        factorial=$((factorial * i))
    done

    # Display the result
    echo "Factorial of $n is: $factorial"
fi

