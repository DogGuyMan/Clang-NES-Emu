#!/bin/bash
# configure.sh — CMake configure + vcpkg install.
# Usage: ./shell/configure.sh [Release|Debug]
set -e
source "$(dirname "$0")/env.sh"
validate_vcpkg

BUILD_TYPE="${1:-Release}"

echo "=== Configuring (${BUILD_TYPE}) ==="
cmake -B "${BUILD_DIR}" -S "${PROJECT_DIR}" \
      -G "Unix Makefiles" \
      -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
      -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN}"

echo "=== Configure done ==="
