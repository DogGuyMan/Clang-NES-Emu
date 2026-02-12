add_library(nes_input STATIC
    input.c
)
target_include_directories(nes_input PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_input)
