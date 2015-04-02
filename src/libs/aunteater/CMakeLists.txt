project(aunteater)

# Configure (and thus copy) the template export file to the build dir
# The export file will be added to the project headers list (and installed with them)
#configure_file(${CMAKE_SOURCE_DIR}/cmake/Export.h.in
#        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
#        @ONLY)

# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    Component.h
    Engine.h
    Entity.h
    Family.h
    Handle.h
    Node.h
    System.h
    globals.h
    make.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    Component.cpp
    Engine.cpp
    Entity.cpp
    Family.cpp
    Node.cpp
    System.cpp
)


add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
        PUBLIC_HEADER "${${PROJECT_NAME}_HEADERS}"
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${ARCHIVE_OUTPUT_DIRECTORY}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)

# Install the Config file, making it easy for other CMake projects to depend on this one.
install(FILES AuntEaterConfig.cmake DESTINATION ${CMAKE_INSTALL_PREFIX} )
