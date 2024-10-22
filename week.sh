#!/bin/bash

days=("Mon" "Tue" "Wed" "Thu" "Fri" "Sat" "Sun")

for day in "${days[@]}"; do
    if [[ "$day" == "Sat" || "$day" == "Sun" ]]; then
        echo "$day (WEEKEND)"
    else
        echo "$day (weekday)"
    fi
done

