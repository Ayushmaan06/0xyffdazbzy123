#!/bin/bash

random_number=$(( RANDOM % 20 + 1 ))
guess=0

echo "Guess the random number between 1 and 20."

while [[ $guess -ne $random_number ]]; do
    read -p "Enter your guess: " guess
    if [[ $guess -lt $random_number ]]; then
        echo "Too low! Try again."
    elif [[ $guess -gt $random_number ]]; then
        echo "Too high! Try again."
    else
        echo "Congratulations! You guessed the correct number: $random_number."
    fi
done

