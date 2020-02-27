project(TestSuite VERSION "${CMAKE_PROJECT_VERSION}")

set(${PROJECT_NAME}_HEADERS
    CommonComponents.h

    catch.hpp
)

set(${PROJECT_NAME}_SOURCES
    Entities.cpp
    Families.cpp
    FamilyHelps.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ad::aunteater
)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      VERSION "${${PROJECT_NAME}_VERSION}"
)


##
## Install
##

install(TARGETS ${PROJECT_NAME})
