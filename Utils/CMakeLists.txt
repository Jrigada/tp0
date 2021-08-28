include_directories(include)
set(SOURCES
        src/filesUtilities.c
        src/monitors-adm.c
        src/serialize-adm.c
        src/socket-adm.c
        )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/target")
add_library(utils SHARED ${SOURCES})

target_link_libraries(utils -lcommons pthread)