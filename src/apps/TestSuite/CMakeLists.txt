project(TestSuite)


# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    CommonComponents.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    Entities.cpp
    Families.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})
    
# include CppUTest headers
include_directories(${Cpputest_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    aunteater
    ${Cpputest_LIBRARIES}
    ${Boost_LIBRARIES})

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
)


