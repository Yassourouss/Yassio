cmake_minimum_required(VERSION "3.16.3")

project("SimpleClient")
include_directories("../yassio/headers")
add_executable(SimpleClient src/SimpleClient.cpp)
add_executable(SimpleServer src/SimpleServer.cpp)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
