function(setupExports target)
    string(TOUPPER "${target}" upperTarget)
    string(REPLACE "." "_" targetExports "${upperTarget}")

    target_compile_definitions(${target} PRIVATE ${targetExports}_EXPORTS)
endfunction()
