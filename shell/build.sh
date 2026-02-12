#!/bin/bash
# build.sh — Build the project (configure first if needed).
# Usage: ./shell/build.sh [Release|Debug]
set -e
source "$(dirname "$0")/env.sh"

BUILD_TYPE="${1:-Release}"

# Auto-configure if build directory doesn't exist
if [ ! -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    "${SCRIPT_DIR}/configure.sh" "${BUILD_TYPE}"
fi

echo "=== Building ==="
cmake --build "${BUILD_DIR}" -j"${JOBS}"

echo "=== Done ==="
echo "Executable: ${BUILD_DIR}/app/nes-emulator"
