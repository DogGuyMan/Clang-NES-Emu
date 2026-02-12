add_library(nes_common STATIC
    log.c
)
target_include_directories(nes_common PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_common)
