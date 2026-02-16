#!/bin/bash
# test.sh — Build (Debug) and run tests via presets.
# Usage: ./shell/test.sh [test_name]
#   ./shell/test.sh           — run all tests
#   ./shell/test.sh test_cpu  — run specific test
set -e
source "$(dirname "$0")/env.sh"

# Always use debug preset for tests
if [ ! -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    "${SCRIPT_DIR}/configure.sh" debug
fi

cmake --build --preset debug -j"${JOBS}"

echo "=== Running tests ==="
if [ -n "$1" ]; then
    ctest --preset debug -R "$1"
else
    ctest --preset debug
fi
