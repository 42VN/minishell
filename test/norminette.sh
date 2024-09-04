#!/bin/bash

# Check if -s (suppress) flag is passed
suppress_output=false
if [ "$1" == "-s" ]; then
    suppress_output=true
fi

output=$(norminette ..)

ko_lines=$(echo "$output" | grep "Error!")
ko_lines_full=$(echo "$output" | grep "Error")

error_files=$(echo "$ko_lines" | cut -d':' -f1 | uniq)


if [ -n "$error_files" ]; then
    if [ "$suppress_output" = true ]; then
        echo -e "\033[0;31m====================================\033[0m"
        echo -e "\033[0;31m        Errors Detected in Files\033[0m"
        echo -e "\033[0;31m====================================\033[0m"
        echo "$error_files"
	else
		echo "$ko_lines_full"
    fi
    echo -e "\033[0;31mNorminette failed ❌\033[0m"
else
    if [ "$suppress_output" = false ]; then
        # Decorative border for passing test
        echo -e "\033[0;32m====================================\033[0m"
        echo -e "\033[0;32m         All Tests Passed\033[0m"
        echo -e "\033[0;32m====================================\033[0m"
    fi
    echo -e "\033[0;32mNorminette passed ✅\033[0m"
fi
