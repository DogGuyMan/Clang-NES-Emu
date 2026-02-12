add_library(nes_mapper STATIC
    mapper.c
    mapper_000.c
)
target_include_directories(nes_mapper PUBLIC ${NES_SRC_DIR})
nes_set_warnings(nes_mapper)
