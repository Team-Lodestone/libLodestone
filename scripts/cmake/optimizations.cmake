option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    message(NOTICE "Compiler optimizations enabled")

    if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
        add_compile_options(
                "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-ftree-vectorize>"
        )
    else()
        add_compile_options(
                "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-march=native;-ftree-vectorize>"
        )
    endif()
endif ()
unset(ENABLE_OPTIMIZATIONS CACHE)