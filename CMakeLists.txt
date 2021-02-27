CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(EventEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g")

set(HEADER_FILES
    src/EventEngine/EventLoop.h
    src/EventEngine/Events.h
    src/EventEngine/Object.h
    src/EventEngine/ObjectRegistry.h
    src/EventEngine/Pointer.h
    src/EventEngine/Registry.h

    src/EventEngine/private/Dispatcher.h
    src/EventEngine/private/EventConverter.h
    src/EventEngine/private/EventLoopPrivate.h
    src/EventEngine/private/EventRegistry.h
    src/EventEngine/private/MetaRegistering.h
)

set(SOURCE_FILES
    src/EventEngine/EventLoop.cpp
    src/EventEngine/Events.cpp
    src/EventEngine/Object.cpp
    src/EventEngine/ObjectRegistry.cpp
    src/EventEngine/Pointer.cpp
    src/EventEngine/Registry.cpp

    src/EventEngine/private/Dispatcher.cpp
    src/EventEngine/private/EventConverter.cpp
    src/EventEngine/private/EventLoopPrivate.cpp
    src/EventEngine/private/EventRegistry.cpp
    src/EventEngine/private/MetaRegistering.cpp
)

add_subdirectory(applications)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE zmqpp)
