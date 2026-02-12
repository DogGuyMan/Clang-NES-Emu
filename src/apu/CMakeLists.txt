add_library(nes_apu STATIC
    apu.c
)
target_include_directories(nes_apu PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_apu)
