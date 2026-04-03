option(ENABLE_LINTERS "Enable source linters" ON)

add_custom_target(LodestoneScripts.CheckIncludePaths
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/checkIncludePaths.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

function(setupLinter n)
    if (ENABLE_LINTERS STREQUAL "ON")
        add_dependencies(${n} LodestoneScripts.CheckIncludePaths)
    endif ()
endfunction()
