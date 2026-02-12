# ── Tests ────────────────────────────────────────────────────

# CPU test — runs nestest.nes and compares logs
add_executable(test_cpu test_cpu.c)
target_include_directories(test_cpu PRIVATE ${NES_SRC_DIR})
target_link_libraries(test_cpu PRIVATE
    nes_cpu
    nes_bus
    nes_ppu
    nes_ppu_bus
    nes_apu
    nes_mapper
    nes_rom
    nes_input
    nes_common
)
nes_set_warnings(test_cpu)

add_test(
    NAME test_cpu
    COMMAND test_cpu "${CMAKE_CURRENT_SOURCE_DIR}/roms/nestest.nes"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
