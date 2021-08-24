string(TOLOWER ${PROJECT_NAME} _lower_project_name)
set(TARGET_NAME ${_lower_project_name}_tests)

set(${TARGET_NAME}_HEADERS
    CommonComponents.h

    catch.hpp
)

set(${TARGET_NAME}_SOURCES
    EntityManager_tests.cpp
    Entities.cpp
    Families.cpp
    FamilyHelps.cpp
    SystemManager_tests.cpp
)

add_executable(${TARGET_NAME}
    main.cpp
    ${${TARGET_NAME}_SOURCES}
    ${${TARGET_NAME}_HEADERS})


target_link_libraries(${TARGET_NAME}
    PRIVATE
        ad::aunteater
)

set_target_properties(${TARGET_NAME} PROPERTIES
                      VERSION "${${TARGET_NAME}_VERSION}"
)


##
## Install
##

install(TARGETS ${TARGET_NAME})
