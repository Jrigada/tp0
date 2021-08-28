include_directories(include)
set(SOURCES
        src/client.c
        src/utils.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/target")
add_executable(client ${SOURCES})

target_link_libraries(client commons)