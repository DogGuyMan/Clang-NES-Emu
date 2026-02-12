add_library(nes_bus STATIC
    bus.c
)
target_include_directories(nes_bus PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_bus)
