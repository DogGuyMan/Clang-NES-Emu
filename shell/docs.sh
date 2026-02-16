#!/bin/bash
# docs.sh — Generate Doxygen documentation.
# Usage: ./shell/docs.sh
set -e
source "$(dirname "$0")/env.sh"

if [ ! -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    "${SCRIPT_DIR}/configure.sh" release
fi

echo "=== Generating docs ==="
cmake --build --preset release --target doxygen
echo "=== Docs generated at ${PROJECT_DIR}/doc/html/ ==="
