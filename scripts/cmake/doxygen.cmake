function(setupDoxygen)
    string(REPLACE "." "_" LODESTONE_DOXYGEN_TAG "${PROJECT_NAME}")
    string(TOUPPER "${LODESTONE_DOXYGEN_TAG}" LODESTONE_TAG_UPPER_NAME)

    option(${LODESTONE_TAG_UPPER_NAME}_DOCS_TARGET "Create documentation target" ON)
    if (${LODESTONE_TAG_UPPER_NAME}_DOCS_TARGET STREQUAL "ON")
        include(FetchContent)
        # https://github.com/jothepro/doxygen-awesome-css?tab=readme-ov-file#cmake-with-fetchcontent
        FetchContent_Declare(
                doxygen-awesome-css
                URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
        )
        FetchContent_MakeAvailable(doxygen-awesome-css)

        FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

        FIND_PACKAGE(Doxygen)
        IF (DOXYGEN_FOUND)
            file(MAKE_DIRECTORY "${LODESTONE_ROOT_BINARY_DIR}/docs/html/modules/${PROJECT_NAME}")
            file(MAKE_DIRECTORY "${LODESTONE_ROOT_BINARY_DIR}/docs/latex/modules/${PROJECT_NAME}")
            
            set(DOXYFILE_IN "${LODESTONE_ROOT_SOURCE_DIR}/docs/subproject/Doxyfile.in")
            set(DOXYFILE_OUT_INTERMEDIATE "${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJECT_NAME}/Doxyfile.in")
            set(DOXYFILE_OUT "${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJECT_NAME}/Doxyfile")

            CONFIGURE_FILE(${DOXYFILE_IN} ${DOXYFILE_OUT_INTERMEDIATE} @ONLY)

            set(HEADER_IN "${LODESTONE_ROOT_SOURCE_DIR}/docs/subproject/layout/header.html")
            set(HEADER_OUT "${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJECT_NAME}/layout/header.html")

            CONFIGURE_FILE(${HEADER_IN} ${HEADER_OUT} @ONLY)

            ADD_CUSTOM_TARGET(${PROJECT_NAME}.Documentation
                    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
                    VERBATIM
            )
            
            message(STATUS "Created documentation task for ${PROJECT_NAME} (${PROJECT_NAME}.Documentation)")

            set(LODESTONE_DOCUMENTATION_INCLUDE_PATHS "${LODESTONE_DOCUMENTATION_INCLUDE_PATHS};${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "Include Paths")
            set(LODESTONE_DOCUMENTATION_TASKS "${LODESTONE_DOCUMENTATION_TASKS};${PROJECT_NAME}.Documentation" CACHE INTERNAL "Documentation Tasks")
            set(LODESTONE_DOCUMENTATION_TAGS "${LODESTONE_DOCUMENTATION_TAGS};${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJECT_NAME}/${LODESTONE_DOXYGEN_TAG}.tag=${LODESTONE_ROOT_BINARY_DIR}/docs/html/modules/${PROJECT_NAME}" CACHE INTERNAL "Documentation Tags")
            set(LODESTONE_DOCUMENTATION_TABS "${LODESTONE_DOCUMENTATION_TABS};<tab type=\"user\" url=\"https://Team-Lodestone.github.io/libLodestone/modules/${PROJECT_NAME}/index.html\" title=\"${PROJECT_NAME}\" />" CACHE INTERNAL "Documentation Tabs")
        ENDIF ()
    endif ()
endfunction()
