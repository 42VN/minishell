#!/bin/bash

# Path to your minishell executable
MINISHELL_PATH="./minishell"

# Check if minishell exists and is executable
if [ ! -x "$MINISHELL_PATH" ]; then
    echo "Minishell executable not found or not executable at $MINISHELL_PATH"
    exit 1
fi

# Base directory for command files
COMMANDS_DIR=./42_minishell_tester/cmds/mand

# Check if the command directory exists
if [ ! -d "$COMMANDS_DIR" ]; then
    echo "Command directory not found at $COMMANDS_DIR"
    exit 1
fi

# Track commands with leaks
LEAKY_COMMANDS=()

# Loop through each file in the cmds/mand directory
for COMMANDS_FILE in "$COMMANDS_DIR"/*; do
    # Check if the file is readable
    if [ ! -f "$COMMANDS_FILE" ] || [ ! -r "$COMMANDS_FILE" ]; then
        echo "Cannot read file $COMMANDS_FILE, skipping..."
        continue
    fi

    echo "Processing file: $COMMANDS_FILE"

    # Read each command from the current file and execute it with Valgrind
    while IFS= read -r command; do
        # Skip empty lines and comments
        [[ -z "$command" || "$command" =~ ^# ]] && continue

        echo "Running command: $command"
        TEMP_OUTPUT=$(mktemp)

        # Run Valgrind with the command piped to minishell and capture the output
        valgrind --leak-check=full --trace-children=yes --gen-suppressions=all --show-leak-kinds=all \
           --track-fds=yes --suppressions=readline.supp "$MINISHELL_PATH" <<< "$command" &> "$TEMP_OUTPUT"

        # Check the output for signs of memory leaks
        if grep -Eq "definitely lost: [1-9]|indirectly lost: [1-9]|possibly lost: [1-9]|still reachable: [1-9]" "$TEMP_OUTPUT"; then
            echo "Leak detected for command: $command in file: $COMMANDS_FILE"
            LEAKY_COMMANDS+=("File: $COMMANDS_FILE | Command: $command")
            cat "$TEMP_OUTPUT"
        fi

        # Check for file descriptor inconsistencies
        FD_LINE=$(grep -Eo "FILE DESCRIPTORS: [0-9]+ open \([0-9]+ std\)" "$TEMP_OUTPUT")
        if [[ "$FD_LINE" =~ ([0-9]+)\ open\ \(([0-9]+)\ std ]]; then
            TOTAL_FD="${BASH_REMATCH[1]}"
            STD_FD="${BASH_REMATCH[2]}"
            if [ "$TOTAL_FD" -ne "$STD_FD" ]; then
                echo "File descriptor mismatch detected for command: $command in file: $COMMANDS_FILE"
                FD_ISSUE_COMMANDS+=("File: $COMMANDS_FILE | Command: $command | Total FD: $TOTAL_FD, STD FD: $STD_FD")
                cat "$TEMP_OUTPUT"
            fi
        fi

        rm "$TEMP_OUTPUT"

    done < "$COMMANDS_FILE"
done

# Display all commands with leaks at the end
if [ ${#LEAKY_COMMANDS[@]} -gt 0 ]; then
    echo -e "\nCommands with memory leaks:"
    for entry in "${LEAKY_COMMANDS[@]}"; do
        echo "$entry"
    done
else
    echo -e "\nNo memory leaks detected in any commands."
fi

# Display all commands with file descriptor issues
if [ ${#FD_ISSUE_COMMANDS[@]} -gt 0 ]; then
    echo -e "\nCommands with file descriptor issues:"
    for entry in "${FD_ISSUE_COMMANDS[@]}"; do
        echo "$entry"
    done
else
    echo -e "\nNo file descriptor issues detected in any commands."
fi