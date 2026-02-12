#!/bin/bash
# clean.sh — Remove the build directory.
# Usage: ./shell/clean.sh
set -e
source "$(dirname "$0")/env.sh"

echo "Cleaning ${BUILD_DIR}..."
rm -rf "${BUILD_DIR}"
echo "Done."
