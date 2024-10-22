#!/bin/bash

# 1. Display the top 5 memory-consuming processes
echo "Top 5 Memory-Consuming Processes:"
ps -eo pid,comm,%mem --sort=-%mem | head -n 6  # The first line is the header

# Save the list of these processes in a file called process_report.txt
ps -eo pid,comm,%mem --sort=-%mem | head -n 6 > process_report.txt
echo "Process report saved to process_report.txt"

# 2. Count the number of running processes
process_count=$(ps aux | wc -l)
echo "Number of running processes: $process_count"

# 3. Display the username of the user running the most memory-consuming process
most_memory_user=$(ps -eo user,%mem --sort=-%mem | awk 'NR==2 {print $1}')
echo "User running the most memory-consuming process: $most_memory_user"

# 4. Prompt to kill a specific process
echo "Do you want to kill a specific process? (yes/no)"
read kill_process

if [[ "$kill_process" == "yes" ]]; then
    echo "Enter the PID or name of the process to kill:"
    read process_name

    # Check if the input is a PID (numeric) or a process name (string)
    if [[ $process_name =~ ^[0-9]+$ ]]; then
        # Kill the process by PID
        kill -9 $process_name 2>/dev/null
        if [[ $? -eq 0 ]]; then
            echo "Process with PID $process_name has been killed."
        else
            echo "Failed to kill the process with PID $process_name. It may not exist."
        fi
    else
        # Kill the process by name
        pkill -f "$process_name"
        if [[ $? -eq 0 ]]; then
            echo "Process named '$process_name' has been killed."
        else
            echo "Failed to kill the process named '$process_name'. It may not exist."
        fi
    fi
else
    echo "No process will be killed."
fi

