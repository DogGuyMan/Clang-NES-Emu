#!/bin/bash
# run.sh — Manager script that dispatches to individual build scripts.
# Usage: ./shell/run.sh <command> [args...]
#
# Commands:
#   configure [Release|Debug]   — CMake configure + vcpkg install
#   build     [Release|Debug]   — Build (auto-configures if needed)
#   test      [test_name]       — Build (Debug) + run tests
#   clean                       — Remove build directory
#   docs                        — Generate Doxygen documentation
#   help                        — Show this message

set -e
SHELL_DIR="$(cd "$(dirname "$0")" && pwd)"

usage() {
    echo "Usage: $0 <command> [args...]"
    echo ""
    echo "Commands:"
    echo "  configure [Release|Debug]   — CMake configure + vcpkg install"
    echo "  build     [Release|Debug]   — Build (auto-configures if needed)"
    echo "  test      [test_name]       — Build (Debug) + run tests"
    echo "  clean                       — Remove build directory"
    echo "  docs                        — Generate Doxygen documentation"
    echo "  help                        — Show this message"
}

COMMAND="${1:-help}"
shift 2>/dev/null || true

case "${COMMAND}" in
    configure)  "${SHELL_DIR}/configure.sh" "$@" ;;
    build)      "${SHELL_DIR}/build.sh"     "$@" ;;
    test)       "${SHELL_DIR}/test.sh"      "$@" ;;
    clean)      "${SHELL_DIR}/clean.sh"     "$@" ;;
    docs)       "${SHELL_DIR}/docs.sh"      "$@" ;;
    help|-h|--help) usage ;;
    *)
        echo "Unknown command: ${COMMAND}"
        echo ""
        usage
        exit 1
        ;;
esac
