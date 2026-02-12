#!/bin/bash
# env.sh — Shared environment variables for all build scripts.
# Source this file, do not execute directly.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build_project"

# vcpkg
VCPKG_ROOT="${VCPKG_ROOT:-$HOME/vcpkg}"
TOOLCHAIN="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

# Parallel jobs
JOBS="$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 4)"

# Validation
validate_vcpkg() {
    if [ ! -f "${TOOLCHAIN}" ]; then
        echo "Error: vcpkg toolchain not found at ${TOOLCHAIN}"
        echo "Set VCPKG_ROOT or install vcpkg at ~/vcpkg"
        exit 1
    fi
}
