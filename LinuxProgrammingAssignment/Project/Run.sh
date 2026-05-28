#!/bin/bash
# =============================================================================
# run_experiment.sh
#
# Purpose:
#   1. Compile timer_threads.c (if needed).
#   2. Start the C program (timer_threads) in the background.
#   3. Change the period X in freq.txt every DURATION_PER_STEP seconds:
#         minute 0-1 : 1 000 000 ns  (1 ms)
#         minute 1-2 :   100 000 ns  (0.1 ms)
#         minute 2-3 :    10 000 ns  (10 µs)
#         minute 3-4 :     1 000 ns  (1 µs)
#         minute 4-5 :       100 ns
#   4. After TOTAL_STEPS, stop the C program.
#
# Usage:
#   chmod +x run_experiment.sh
#   ./run_experiment.sh
# =============================================================================

set -euo pipefail

PROG="./timer_threads"
SRC="./src/src.c"
FREQ_FILE="freq.txt"
OUTPUT_FILE="time_and_interval.txt"

# Array of period values (in ns), ordered per minute
PERIODS=(1000000 100000 10000 1000 100)
LABELS=("1 000 000 ns (1 ms)" "100 000 ns (0.1 ms)" "10 000 ns (10 µs)" "1 000 ns (1 µs)" "100 ns")

DURATION_PER_STEP=30   # seconds per step
TOTAL_STEPS=${#PERIODS[@]}   # = 5

# ---------------------------------------------------------------------------
# 1. Compile if needed (prefer Makefile.mk -> Makefile -> gcc)
# ---------------------------------------------------------------------------
if [ ! -f "$PROG" ] || [ "$SRC" -nt "$PROG" ]; then
    echo "[$(date '+%T')] Building (using Makefile if present) ..."

    if [ -f Makefile.mk ]; then
        echo "[$(date '+%T')] Found Makefile.mk — running: make -f Makefile.mk"
        make -f Makefile.mk
    elif [ -f Makefile ]; then
        echo "[$(date '+%T')] Found Makefile — running: make"
        make
    else
        echo "[$(date '+%T')] No Makefile found. Compiling $SRC directly with gcc"
        gcc -O2 -o timer_threads "$SRC" -lpthread -lrt
    fi

    echo "[$(date '+%T')] Checking for executable..."
    # If the expected executable name does not exist, try to detect a produced executable
    if [ ! -f "$PROG" ]; then
        EXE=$(find . -maxdepth 1 -type f -perm -111 -printf "%f\n" | head -n1 || true)
        if [ -n "$EXE" ]; then
            PROG="./$EXE"
            echo "[$(date '+%T')] Detected executable: $PROG"
        else
            echo "[$(date '+%T')] Warning: no executable found after build."
        fi
    fi
    echo "[$(date '+%T')] Build finished."
fi

# ---------------------------------------------------------------------------
# 2. Write the initial period to freq.txt
# ---------------------------------------------------------------------------
echo "${PERIODS[0]}" > "$FREQ_FILE"
echo "[$(date '+%T')] Wrote initial period: ${LABELS[0]} to $FREQ_FILE"

# ---------------------------------------------------------------------------
# 3. Start the C program
# ---------------------------------------------------------------------------
echo "[$(date '+%T')] Starting $PROG ..."
"$PROG" &
PROG_PID=$!
echo "[$(date '+%T')] PID = $PROG_PID"

# Cleanup function for early script termination
cleanup() {
    echo ""
    echo "[$(date '+%T')] Received signal — stopping $PROG (PID $PROG_PID) ..."
    kill "$PROG_PID" 2>/dev/null || true
    wait "$PROG_PID" 2>/dev/null || true
    echo "[$(date '+%T')] Done."
    exit 0
}
trap cleanup INT TERM

# ---------------------------------------------------------------------------
# 4. Loop to change the period each minute
# ---------------------------------------------------------------------------
for (( i=0; i<TOTAL_STEPS; i++ )); do
    echo ""
    echo "[$(date '+%T')] === Step $((i+1))/$TOTAL_STEPS: period = ${LABELS[$i]} ==="

    # Write the new period (step 0 was written above, but rewrite for consistency)
    echo "${PERIODS[$i]}" > "$FREQ_FILE"
    echo "[$(date '+%T')] Wrote ${PERIODS[$i]} to $FREQ_FILE"

    # Countdown
    echo -n "[$(date '+%T')] Waiting $DURATION_PER_STEP seconds"
    for (( s=0; s<DURATION_PER_STEP; s++ )); do
        sleep 1
        # Print progress marker every 10 seconds
        if (( (s+1) % 10 == 0 )); then
            echo -n " $((s+1))s"
        fi
    done
    echo ""
done

# ---------------------------------------------------------------------------
# 5. Stop the C program
# ---------------------------------------------------------------------------
echo ""
echo "[$(date '+%T')] 5 minutes complete. Stopping $PROG (PID $PROG_PID) ..."
kill "$PROG_PID" 2>/dev/null || true
wait "$PROG_PID" 2>/dev/null || true

echo "[$(date '+%T')] Program stopped."
echo "[$(date '+%T')] Data saved at: $OUTPUT_FILE"
echo ""
echo "Experiment summary:"
echo "  Total runtime       : $((TOTAL_STEPS * DURATION_PER_STEP)) seconds"
echo "  Periods used        : ${PERIODS[*]} (ns)"
if [ -f "$OUTPUT_FILE" ]; then
    LINES=$(wc -l < "$OUTPUT_FILE")
    echo "  Lines written       : $LINES"
fi