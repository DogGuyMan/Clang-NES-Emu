add_library(nes_cpu STATIC
    cpu.c
)
target_include_directories(nes_cpu PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_cpu)
