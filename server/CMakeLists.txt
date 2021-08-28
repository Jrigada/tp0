include_directories(include)
set(SOURCES
        src/server.c
        src/utils.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/target")
add_executable(server ${SOURCES})

target_link_libraries(server commons)