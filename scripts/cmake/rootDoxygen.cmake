function(configureRootDoxygen)

if (LODESTONE_DOCS_TARGET STREQUAL "ON")
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
        file(MAKE_DIRECTORY "${LODESTONE_ROOT_BINARY_DIR}/docs/")

        set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in")
        set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
        string(REPLACE ";" " \\\n" LODESTONE_DOCUMENTATION_TAGS_LIST "${LODESTONE_DOCUMENTATION_TAGS}")

        CONFIGURE_FILE(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

        set(LAYOUT_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/layout/layout.xml")
        set(LAYOUT_OUT "${LODESTONE_ROOT_BINARY_DIR}/docs/layout/layout.xml")
        string(REPLACE ";" "\n" LODESTONE_DOCUMENTATION_TABS_LIST "${LODESTONE_DOCUMENTATION_TABS}")

        CONFIGURE_FILE(${LAYOUT_IN} ${LAYOUT_OUT} @ONLY)

        foreach (proj IN LISTS LODESTONE_DOCUMENTATION_TASKS)
            if (proj STREQUAL "")
                continue()
            endif()

            string(REGEX REPLACE "\\.Documentation$" "" PROJ_NAME "${proj}")

            set(PROJ_LAYOUT_IN "${LODESTONE_ROOT_SOURCE_DIR}/docs/subproject/layout/layout.xml")
            set(PROJ_LAYOUT_OUT "${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJ_NAME}/layout/layout.xml")
            string(REPLACE ";" "\n" LODESTONE_DOCUMENTATION_TABS_LIST "${LODESTONE_DOCUMENTATION_TABS}")

            CONFIGURE_FILE(${PROJ_LAYOUT_IN} ${PROJ_LAYOUT_OUT} @ONLY)

            set(PROJ_DOXYFILE_IN "${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJ_NAME}/Doxyfile.in")
            set(PROJ_DOXYFILE_OUT "${LODESTONE_ROOT_BINARY_DIR}/docs/subprojects/${PROJ_NAME}/Doxyfile")

            set(LODESTONE_SUBPROJECT_REL_DOCUMENTATION_TAGS ${LODESTONE_DOCUMENTATION_TAGS})
            list(FILTER LODESTONE_SUBPROJECT_REL_DOCUMENTATION_TAGS EXCLUDE REGEX "/${PROJ_NAME}.tag")
            string(REPLACE ";" " \\\n" LODESTONE_DOCUMENTATION_SUBPROJECT_TAGS_LIST "${LODESTONE_SUBPROJECT_REL_DOCUMENTATION_TAGS}")

            string(REPLACE ";" " \\\n" LODESTONE_DOCUMENTATION_SUBPROJECT_INCLUDE_PATHS "${LODESTONE_DOCUMENTATION_INCLUDE_PATHS}")

            CONFIGURE_FILE(${PROJ_DOXYFILE_IN} ${PROJ_DOXYFILE_OUT} @ONLY)
        endforeach ()

        ADD_CUSTOM_TARGET(Lodestone.Documentation
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                VERBATIM
                DEPENDS
                ${LODESTONE_DOCUMENTATION_TASKS}
        )
    ENDIF ()
endif ()

endfunction()