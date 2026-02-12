# CompilerWarnings.cmake
# Defines nes_set_warnings() to apply project-wide compiler warning flags.

function(nes_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4
            /permissive-
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wformat=2
            -Wcast-align
            -Wconversion
            -Wsign-conversion
            -Wnull-dereference
        )
    endif()

    # Sanitizers for Debug builds (GCC/Clang only)
    if(NOT MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(${target} PRIVATE
            -fsanitize=address,undefined
        )
    endif()
endfunction()
