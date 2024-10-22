#!/bin/bash

count=1
multiple=3

echo "First ten multiples of 3:"

until [[ $count -gt 10 ]]; do
    echo $(( multiple * count ))
    ((count++))
done

