#!/bin/bash

# Function to print a welcome message
function welcome() {
    echo "Welcome to the Shell Script Demonstration!"
}

# Function to check if a string is a palindrome
function is_palindrome() {
    str="$1"
    reversed_str=$(echo "$str" | rev)

    if [[ "$str" == "$reversed_str" ]]; then
        echo "$str is a palindrome."
    else
        echo "$str is not a palindrome."
    fi
}

# Function to slice a string
function slice_string() {
    str="$1"
    start_index="$2"
    length="$3"
    sliced_str="${str:start_index:length}"
    echo "Sliced string: '$sliced_str'"
}

# Function to demonstrate array operations
function array_operations() {
    local arr=("Apple" "Banana" "Cherry" "Date" "Elderberry")
    echo "Array elements:"
    
    # Loop through the array
    for fruit in "${arr[@]}"; do
        echo "$fruit"
    done

    # Add an element to the array
    arr+=("Fig")
    echo "Array after adding an element:"
    for fruit in "${arr[@]}"; do
        echo "$fruit"
    done

    # Remove the second element (index 1)
    unset arr[1]
    echo "Array after removing the second element:"
    for fruit in "${arr[@]}"; do
        echo "$fruit"
    done
}

# Function to count vowels in a string
function count_vowels() {
    str="$1"
    vowel_count=$(echo "$str" | grep -o -i '[aeiou]' | wc -l)
    echo "Number of vowels in '$str': $vowel_count"
}

# Main script execution
welcome

# User input for palindrome check
read -p "Enter a string to check if it's a palindrome: " user_string
is_palindrome "$user_string"

# User input for string slicing
read -p "Enter a string for slicing: " str_to_slice
read -p "Enter starting index for slicing: " start
read -p "Enter length for slicing: " len
slice_string "$str_to_slice" "$start" "$len"

# User input for vowel counting
read -p "Enter a string to count vowels: " vowel_string
count_vowels "$vowel_string"

# Demonstrate array operations
array_operations

# End of script
echo "Script execution completed."

