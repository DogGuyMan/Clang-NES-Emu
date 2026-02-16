#!/bin/bash
# env.sh — Shared environment variables for all build scripts.
# Source this file, do not execute directly.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build_$(uname -s)"

# vcpkg — set default if not already defined, export for CMake Presets
export VCPKG_ROOT="${VCPKG_ROOT:-$HOME/vcpkg}"

# Parallel jobs
JOBS="$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)"

# Validation
validate_vcpkg() {
    if [ ! -d "${VCPKG_ROOT}" ]; then
        echo "Error: VCPKG_ROOT not found at ${VCPKG_ROOT}"
        echo "Set VCPKG_ROOT or install vcpkg at ~/vcpkg"
        exit 1
    fi
}
