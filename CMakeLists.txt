cmake_minimum_required(VERSION 3.20)
project(nes-emulator VERSION 0.1.0 LANGUAGES C)

# ── C Standard ───────────────────────────────────────────────
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ── Export compile_commands.json for IDE / clangd ────────────
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Options ──────────────────────────────────────────────────
option(NES_BUILD_TESTS "Build test executables" ON)
option(NES_BUILD_DOCS  "Enable Doxygen doc target" ON)

# ── CMake helper modules ────────────────────────────────────
include(cmake/CompilerWarnings.cmake)
include(cmake/Doxygen.cmake)

# ── External dependencies (vcpkg manifest mode) ─────────────
find_package(SDL2 CONFIG REQUIRED)

# ── Source modules (static libraries) ────────────────────────
add_subdirectory(src)

# ── Main executable ─────────────────────────────────────────
add_subdirectory(app)

# ── Tests ────────────────────────────────────────────────────
if(NES_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# ── Documentation ───────────────────────────────────────────
if(NES_BUILD_DOCS)
    nes_setup_doxygen()
endif()
