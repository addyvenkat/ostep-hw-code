#!/bin/zsh

# Configuration
MAX_PAGES=32768
NUM_TRIALS=10000 # Increase trials for reliability
EXECUTABLE="./build/tlb"

echo "Pages, AverageTimeNS"

for ((pages = 1; pages <= MAX_PAGES; pages *= 2)); do
    # Run the compiled C program and capture its output
    OUTPUT=$($EXECUTABLE $pages $NUM_TRIALS)
    
    # Use awk to extract just the numerical average time from the C program's output
    # The output format is "Average time per page access: X.XX ns"
    TIME_NS=$(echo $OUTPUT | awk '{print $NF}')
    
    echo "$pages, $TIME_NS"
done
