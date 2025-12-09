#!/usr/bin/env bash

BIN_DIR="./bin"

num_arg=""
word_arg=""

# --- Parse up to two arguments: one numeric, one non-numeric ---
for arg in "$@"; do
    if [[ "$arg" =~ ^[0-9]+$ ]]; then
        if [[ -z "$num_arg" ]]; then
            num_arg="$arg"
        else
            echo "Error: more than one numeric argument given: $num_arg and $arg" >&2
            exit 1
        fi
    else
        if [[ -z "$word_arg" ]]; then
            word_arg="$arg"
        else
            echo "Error: more than one non-numeric argument given: '$word_arg' and '$arg'" >&2
            exit 1
        fi
    fi
done

# --- Ensure bin directory exists ---
if [[ ! -d "$BIN_DIR" ]]; then
    echo "Error: '$BIN_DIR' directory does not exist." >&2
    exit 1
fi

# --- Run matching executables in BIN_DIR ---
for exe in "$BIN_DIR"/*; do
    [[ -f "$exe" && -x "$exe" ]] || continue

    base=$(basename "$exe")

    # If numeric filter is given, check first number in filename
    if [[ -n "$num_arg" ]]; then
        # Extract first contiguous digit sequence from filename
        if [[ "$base" =~ ([0-9]+) ]]; then
            first_num="${BASH_REMATCH[1]}"

            # Compare numeric values, ignoring leading zeros
            if (( 10#$first_num != 10#$num_arg )); then
                continue
            fi
        else
            # No number in filename, skip when numeric filter is used
            continue
        fi
    fi

    # Run the executable, optionally with the word argument
    if [[ -n "$word_arg" ]]; then
        "$exe" "$word_arg"
    else
        "$exe"
    fi
done

