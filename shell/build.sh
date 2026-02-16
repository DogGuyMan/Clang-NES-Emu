#!/bin/bash
# build.sh — Build the project via presets (configure first if needed).
# Usage: ./shell/build.sh [release|debug]
set -e
source "$(dirname "$0")/env.sh"

PRESET="${1:-release}"

# Auto-configure if build directory doesn't exist
if [ ! -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    "${SCRIPT_DIR}/configure.sh" "${PRESET}"
fi

echo "=== Building (${PRESET}) ==="
cmake --build --preset "${PRESET}" -j"${JOBS}"

echo "=== Done ==="
echo "Executable: ${BUILD_DIR}/app/nes-emulator"
