CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(prog)

set(HEADER_FILES
)

set(SOURCE_FILES
    main.cpp
)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE EventEngine Threads::Threads)
