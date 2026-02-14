# ── Diagnostic Tools Helper ──────────────────────
function(add_diagnostic_tool name)
    add_executable(${name} ${name}.c)
    target_include_directories(${name} PRIVATE ${NES_SRC_DIR})
    target_link_libraries(${name} PRIVATE nes_common ${ARGN})
    nes_set_warnings(${name})
endfunction()

# ── Diagnostic Tools ─────────────────────────────
add_diagnostic_tool(check_platform)
add_diagnostic_tool(check_structs nes_rom)
