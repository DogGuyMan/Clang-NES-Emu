# ── Main Executable ──────────────────────────────────────────
add_executable(nes-emulator main.c)

target_include_directories(nes-emulator PRIVATE ${NES_SRC_DIR})

# Link all module static libraries
target_link_libraries(nes-emulator PRIVATE
    nes_emu
    nes_cpu
    nes_ppu
    nes_apu
    nes_bus
    nes_ppu_bus
    nes_mapper
    nes_input
    nes_rom
    nes_common
)

# SDL2 (via vcpkg)
target_link_libraries(nes-emulator PRIVATE
    nes_platform
    SDL2::SDL2
    SDL2::SDL2main
)

nes_set_warnings(nes-emulator)
