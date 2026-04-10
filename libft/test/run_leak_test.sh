#!/bin/bash
# Memory leak detection script for libft tests
# Usage: ./run_leak_test.sh <test_executable>

VALGRIND_LOG="/tmp/libft_valgrind_$$.log"
TEST_EXEC="$1"

if [ -z "$TEST_EXEC" ]; then
    echo "Usage: $0 <test_executable>"
    exit 1
fi

if [ ! -f "$TEST_EXEC" ]; then
    echo "Error: Test executable not found: $TEST_EXEC"
    exit 1
fi

# Check if valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo "⚠️  Valgrind not installed. Skipping memory leak detection."
    echo "   Install with: sudo apt-get install valgrind"
    "$TEST_EXEC"
    exit $?
fi

echo "🔍 Running memory leak detection with Valgrind..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# Temporary file for processed output
TEST_OUTPUT_RAW="/tmp/libft_test_raw_$$.txt"
TEST_OUTPUT_FINAL="/tmp/libft_test_final_$$.txt"

# Run valgrind and capture output
export RUNNING_ON_VALGRIND=1
valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --verbose \
    --log-file="$VALGRIND_LOG" \
    --error-exitcode=42 \
    "$TEST_EXEC" 2>&1 | tee "$TEST_OUTPUT_RAW"

TEST_EXIT_CODE=$?

# Extract test function names that have leaks from valgrind log
# Look for test functions in stack traces
LEAKING_TESTS=$(grep "test_[a-zA-Z_0-9]* (" "$VALGRIND_LOG" 2>/dev/null | \
    grep "by 0x" | \
    sed -E 's/.*by 0x[0-9A-F]+: (test_[a-zA-Z_0-9]+) \(.*/\1/' | \
    sort -u)

# Post-process the output to replace [No leak] with [Leak] for leaking tests  
if [ ! -z "$LEAKING_TESTS" ]; then
    cp "$TEST_OUTPUT_RAW" "$TEST_OUTPUT_FINAL"
    
    # For each leaking test function, find and mark related test lines
    echo "$LEAKING_TESTS" | while IFS= read -r test_func; do
        if [ ! -z "$test_func" ]; then
            # Extract test context from the test file to understand which assertions are in this function
            # For now, we'll add a warning section after the main output
            :
        fi
    done
    
    # Display the final output
    cat "$TEST_OUTPUT_FINAL"
else
    # No leaks found or couldn't parse - just show raw output
    cat "$TEST_OUTPUT_RAW"
fi

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📊 Memory Leak Analysis Results"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# Parse valgrind output
DEFINITELY_LOST=$(grep "definitely lost:" "$VALGRIND_LOG" | awk '{print $4}' | sed 's/,//')
INDIRECTLY_LOST=$(grep "indirectly lost:" "$VALGRIND_LOG" | awk '{print $4}' | sed 's/,//')
POSSIBLY_LOST=$(grep "possibly lost:" "$VALGRIND_LOG" | awk '{print $4}' | sed 's/,//')
STILL_REACHABLE=$(grep "still reachable:" "$VALGRIND_LOG" | awk '{print $4}' | sed 's/,//')
SUPPRESSED=$(grep "suppressed:" "$VALGRIND_LOG" | awk '{print $2}' | sed 's/,//')

# Default to 0 if not found
DEFINITELY_LOST=${DEFINITELY_LOST:-0}
INDIRECTLY_LOST=${INDIRECTLY_LOST:-0}
POSSIBLY_LOST=${POSSIBLY_LOST:-0}
STILL_REACHABLE=${STILL_REACHABLE:-0}
SUPPRESSED=${SUPPRESSED:-0}

echo ""
echo "Memory Leak Summary:"
echo "  • Definitely lost:  $DEFINITELY_LOST bytes"
echo "  • Indirectly lost:  $INDIRECTLY_LOST bytes"
echo "  • Possibly lost:    $POSSIBLY_LOST bytes"
echo "  • Still reachable:  $STILL_REACHABLE bytes"
echo "  • Suppressed:       $SUPPRESSED bytes"
echo ""

# Check for memory leaks
TOTAL_LEAKS=$((DEFINITELY_LOST + INDIRECTLY_LOST + POSSIBLY_LOST))

if [ $TOTAL_LEAKS -gt 0 ]; then
    echo "❌ MEMORY LEAKS DETECTED!"
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "🔎 Detailed Leak Information:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    
    # Show relevant sections from valgrind log
    awk '
        /HEAP SUMMARY/,/LEAK SUMMARY/ { print "  " $0 }
        /LEAK SUMMARY/,/ERROR SUMMARY/ { print "  " $0 }
    ' "$VALGRIND_LOG"
    
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "📝 Stack Traces for Memory Leaks:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    
    # Extract and display stack traces
    awk '
        /blocks are definitely lost/ { leak=1 }
        /blocks are indirectly lost/ { leak=1 }
        /blocks are possibly lost/ { leak=1 }
        leak && /^==/ { print "  " $0 }
        /^$/ { leak=0 }
    ' "$VALGRIND_LOG" | head -100
    
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "💡 Full valgrind log saved to: $VALGRIND_LOG"
    echo "   View with: cat $VALGRIND_LOG"
    echo "   or:        less $VALGRIND_LOG"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    
    # Show which test functions have leaks
    if [ ! -z "$LEAKING_TESTS" ]; then
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo "⚠️  Test Functions with Memory Leaks:"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo ""
        
        # For each leaking test function, show details
        echo "$LEAKING_TESTS" | while IFS= read -r test_func; do
            if [ ! -z "$test_func" ]; then
                # Get file and line number for this test function
                FILE_LINE=$(grep "$test_func (" "$VALGRIND_LOG" | grep "\.c:" | head -1 | sed -E 's/.*\((.*)\).*/\1/')
                
                # Count how many leak blocks mention this function
                LEAK_COUNT=$(grep "$test_func" "$VALGRIND_LOG" | grep "by 0x" | wc -l)
                
                if [ ! -z "$FILE_LINE" ]; then
                    printf "  \033[0;33m•\033[0m \033[0;36m%-40s\033[0m" "$test_func"
                    if [ $LEAK_COUNT -gt 0 ]; then
                        printf " \033[0;31m[%d leak site(s)]\033[0m" "$LEAK_COUNT"
                    fi
                    printf "\n"
                    printf "    \033[0;90m└─ %s\033[0m\n" "$FILE_LINE"
                else
                    printf "  \033[0;33m•\033[0m \033[0;36m%s\033[0m\n" "$test_func"
                fi
            fi
        done
        echo ""
    fi
    
    # Cleanup temp files
    rm -f "$TEST_OUTPUT_RAW" "$TEST_OUTPUT_FINAL"
    
    exit 1
else
    echo "✅ NO MEMORY LEAKS DETECTED!"
    echo ""
    echo "All memory allocations were properly freed."
    rm -f "$VALGRIND_LOG" "$TEST_OUTPUT_RAW" "$TEST_OUTPUT_FINAL"
    exit $TEST_EXIT_CODE
fi
