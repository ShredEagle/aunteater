set(TARGET_NAME aunteater)

set(${TARGET_NAME}_HEADERS
    Archetype.h
    Component.h
    Entity.h
    EntityManager.h
    Family.h
    FamilyHelp.h
    System.h
    SystemManager.h
    Timer.h
    UpdateTiming.h

    globals.h
    make.h
)

set(${TARGET_NAME}_SOURCES
    Entity.cpp
    EntityManager.cpp
    Family.cpp
)

add_library(${TARGET_NAME}
    ${${TARGET_NAME}_SOURCES}
    ${${TARGET_NAME}_HEADERS}
)
add_library(ad::${TARGET_NAME} ALIAS ${TARGET_NAME})

cmc_target_current_include_directory(${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES
                      VERSION "${${TARGET_NAME}_VERSION}"
)


##
## Dependencies
##

cmc_find_dependencies()

target_link_libraries(${TARGET_NAME}
    PUBLIC Boost::boost
)


##
## Install
##

install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME}Targets)

include(cmc-install)
# Install the headers preserving the directory hierarchy
cmc_install_with_folders(FILES ${${TARGET_NAME}_HEADERS}
                         DESTINATION include/${TARGET_NAME}/${TARGET_NAME}
)
cmc_install_packageconfig(${TARGET_NAME} ${TARGET_NAME}Targets ${PROJECT_NAME}
                          FIND_FILE CMakeFinds.cmake.in
                          NAMESPACE ad::
)
