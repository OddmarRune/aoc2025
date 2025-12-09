#!/usr/bin/env bash

BIN_DIR="./bin"

# Optional argument to pass to each binary
ARG="$1"

# Ensure bin directory exists
if [[ ! -d "$BIN_DIR" ]]; then
    echo "Error: '$BIN_DIR' directory does not exist."
    exit 1
fi

# Loop through all files in bin directory
for exe in "$BIN_DIR"/*; do
    # Skip if not a file or not executable
    [[ -f "$exe" && -x "$exe" ]] || continue

    echo "Running: $exe $ARG"
    "$exe" $ARG
    echo
done

