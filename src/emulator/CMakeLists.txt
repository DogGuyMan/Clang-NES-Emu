add_library(nes_emu STATIC
    emulator.c
)
target_include_directories(nes_emu PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_emu)
