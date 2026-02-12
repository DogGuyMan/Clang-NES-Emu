add_library(nes_platform STATIC
    platform.c
)
target_include_directories(nes_platform PUBLIC ${NES_SRC_DIR})
target_link_libraries(nes_platform PRIVATE SDL2::SDL2)
nes_set_warnings(nes_platform)
