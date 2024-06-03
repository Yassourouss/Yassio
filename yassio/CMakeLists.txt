cmake_minimum_required(VERSION "3.16.3")


project("ComplexClient")
include_directories("../yassio/headers")
add_executable(ComplexClient src/ComplexClient.cpp)
add_executable(ComplexServer src/ComplexServer.cpp)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)