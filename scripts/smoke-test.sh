#!/usr/bin/env bash
# Smoke test for the DAMIS Algorithms binary: runs every algorithm on the iris sample
# (with a class attribute added, needed by MLP/DECTREE) and checks the result files.
#
#   scripts/smoke-test.sh [path/to/Algorithms]      (default: ./Algorithms)
#   NP=4 scripts/smoke-test.sh                      (number of MPI processes, default 2)
set -u

cd "$(dirname "$0")/.."
BIN="$(realpath "${1:-./Algorithms}")"
NP="${NP:-2}"
MPIRUN=(mpirun --oversubscribe --bind-to none -np "$NP")
if [ "$(id -u)" = 0 ]; then
    export OMPI_ALLOW_RUN_AS_ROOT=1 OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1
fi

[ -x "$BIN" ] || { echo "Algorithms binary not found: $BIN (run make first)"; exit 1; }

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

# iris.arff has 150 objects in 3 consecutive groups of 50 -> add class labels A/B/C
awk '/^@DATA/ { print "@ATTRIBUTE class {A,B,C}"; print; data = 1; next }
     data && NF { n++; print $0 "," (n <= 50 ? "A" : n <= 100 ? "B" : "C"); next }
     { print }' arff_files/iris.arff > "$WORK/iris.arff"
ROWS=150

TESTS=(
    "PCA         -projType 0 -d 2"
    "PCA         -projType 1 -d 90"
    "SMACOFMDS   -maxIter 100 -d 2 -eps 0.0001 -zeidel 0"
    "SMACOFMDS   -maxIter 100 -d 2 -eps 0.0001 -zeidel 1"
    "RELATIVEMDS -maxIter 100 -d 2 -eps 0.0001 -noOfBaseVectors 10 -selStrategy 1"
    "RELATIVEMDS -maxIter 100 -d 2 -eps 0.0001 -noOfBaseVectors 10 -selStrategy 2"
    "RELATIVEMDS -maxIter 100 -d 2 -eps 0.0001 -noOfBaseVectors 10 -selStrategy 3"
    "DMA         -maxIter 100 -d 2 -eps 0.0001 -neighbour 10"
    "SAMANN      -maxIter 100 -d 2 -eta 0.1 -mTrain 10 -nNeurons 10"
    "SOMMDS      -rows 3 -columns 3 -eHat 10 -mdsIteration 50 -eps 0.0001 -mdsProjection 2"
    "SOM         -rows 3 -columns 3 -eHat 10"
    "KMEANS      -maxIter 100 -noOfClust 3"
    "MLP         -h1pNo 5 -h2pNo 0 -qty 80 -maxIter 100 -kFoldVal 0"
    "MLP         -h1pNo 5 -h2pNo 3 -qty 5 -maxIter 100 -kFoldVal 1"
    "DECTREE     -dL 0.8 -dT 0.2 -r 0.5 -nTree 10"
)

failed=0
i=0
for t in "${TESTS[@]}"; do
    i=$((i + 1))
    read -r -a args <<< "$t"
    out="$WORK/out_$i.arff"; stat="$WORK/stat_$i.arff"; log="$WORK/log_$i.txt"
    start=$(date +%s%N)
    "${MPIRUN[@]}" "$BIN" -al "${args[@]}" -i "$WORK/iris.arff" -o "$out" -s "$stat" > "$log" 2>&1
    rc=$?
    ms=$(( ($(date +%s%N) - start) / 1000000 ))
    secs="$((ms / 1000)).$(( (ms % 1000) / 100 ))"
    rows=$(grep -c -v -E '^(@|%|$)' "$out" 2>/dev/null || true)
    err=$(grep -v -E '^(@|%|$)' "$stat" 2>/dev/null | cut -d, -f1)
    status=OK
    if [ "$rc" != 0 ] || [ ! -s "$out" ] || [ -z "$err" ]; then
        status=FAIL
    elif [ "${args[0]}" != SOMMDS ] && [ "$rows" != "$ROWS" ]; then
        status=FAIL   # SOMMDS returns only the winning neurons, all others one row per object
    fi
    [ "$status" = FAIL ] && failed=$((failed + 1))
    printf '%-4s %-12s rc=%-3s rows=%-4s err=%-12s %5ss  %s\n' "$status" "${args[0]}" "$rc" "${rows:-0}" "${err:-?}" "$secs" "${t#* }"
    [ "$status" = FAIL ] && sed 's/^/       | /' "$log" | head -8
done

# the temporary X distance matrix files (*.bin) must be cleaned up by the binary
leftovers=$(find "$WORK" -name '*.bin' | wc -l)
if [ "$leftovers" != 0 ]; then
    echo "FAIL $leftovers temporary .bin file(s) left behind"; failed=$((failed + 1))
fi

# two runs started at the same moment in the same directory must not share temp files
"${MPIRUN[@]}" "$BIN" -al SMACOFMDS -maxIter 200 -d 2 -eps 0.00001 -zeidel 0 -i "$WORK/iris.arff" -o "$WORK/c1.arff" -s "$WORK/c1.stat" > "$WORK/c1.log" 2>&1 &
"${MPIRUN[@]}" "$BIN" -al SMACOFMDS -maxIter 200 -d 2 -eps 0.00001 -zeidel 0 -i "$WORK/iris.arff" -o "$WORK/c2.arff" -s "$WORK/c2.stat" > "$WORK/c2.log" 2>&1 &
wait
concurrent=OK
for c in c1 c2; do
    if [ "$(grep -c -v -E '^(@|%|$)' "$WORK/$c.arff" 2>/dev/null)" != "$ROWS" ]; then
        echo "FAIL concurrent run $c"; sed 's/^/       | /' "$WORK/$c.log" | head -8; failed=$((failed + 1)); concurrent=FAIL
    fi
done
[ "$concurrent" = OK ] && echo "OK   two concurrent runs in the same directory"

echo "----"
if [ "$failed" = 0 ]; then echo "All tests passed (NP=$NP)"; else echo "$failed test(s) FAILED"; fi
exit $((failed > 0))
