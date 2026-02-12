add_library(nes_ppu STATIC
    ppu.c
)
target_include_directories(nes_ppu PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_ppu)
