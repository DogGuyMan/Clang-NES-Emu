#!/bin/bash
# configure.sh — CMake configure via presets.
# Usage: ./shell/configure.sh [release|debug]
set -e
source "$(dirname "$0")/env.sh"
validate_vcpkg

PRESET="${1:-release}"

echo "=== Configuring (${PRESET}) ==="
cmake --preset "${PRESET}" -S "${PROJECT_DIR}"

echo "=== Configure done ==="
