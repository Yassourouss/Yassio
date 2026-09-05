cmake_minimum_required(VERSION 3.16)

project(Yassio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/headers)

add_subdirectory(headers/message)
add_subdirectory(headers/tsqueue)
add_subdirectory(headers/connection)
add_subdirectory(headers/server)
add_subdirectory(headers/client)
add_subdirectory(test)

find_package(Threads REQUIRED)

add_executable(EulerPClient src/EulerPClient.cpp)
add_executable(EulerYClient src/EulerYClient.cpp)
add_executable(HelloClient src/HelloClient.cpp)
add_executable(ComplexServer src/ComplexServer.cpp)

target_link_libraries(EulerPClient PRIVATE Threads::Threads)
target_link_libraries(EulerYClient PRIVATE Threads::Threads)
target_link_libraries(HelloClient PRIVATE Threads::Threads)
target_link_libraries(ComplexServer PRIVATE Threads::Threads)
