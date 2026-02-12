add_library(nes_rom STATIC
    rom.c
)
target_include_directories(nes_rom PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_rom)
