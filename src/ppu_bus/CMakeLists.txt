add_library(nes_ppu_bus STATIC
    ppu_bus.c
)
target_include_directories(nes_ppu_bus PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_ppu_bus)
