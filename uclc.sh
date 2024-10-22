#!/bin/bash

read -p "Enter a character: " char

if [[ $char =~ [A-Z] ]]; then
    echo "$char is an uppercase alphabet."
elif [[ $char =~ [a-z] ]]; then
    echo "$char is a lowercase alphabet."
else
    echo "$char is not an alphabet."
fi

