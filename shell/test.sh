#!/bin/bash
# test.sh — Build (Debug) and run tests.
# Usage: ./shell/test.sh [test_name]
#   ./shell/test.sh           — run all tests
#   ./shell/test.sh test_cpu  — run specific test
set -e
source "$(dirname "$0")/env.sh"

# Always use Debug for tests (sanitizers enabled)
if [ ! -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    "${SCRIPT_DIR}/configure.sh" Debug
fi

cmake --build "${BUILD_DIR}" -j"${JOBS}"

echo "=== Running tests ==="
if [ -n "$1" ]; then
    cd "${BUILD_DIR}" && ctest -R "$1" --output-on-failure
else
    cd "${BUILD_DIR}" && ctest --output-on-failure
fi
