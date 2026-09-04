cmake_minimum_required(VERSION 3.16.3)

project(EulerClient)

include_directories("../yassio/headers")

find_package(Threads REQUIRED)

# Define the executables
add_executable(EulerPClient src/EulerPClient.cpp)
add_executable(EulerYClient src/EulerYClient.cpp)
add_executable(HelloClient src/HelloClient.cpp)
add_executable(ComplexServer src/ComplexServer.cpp)

# Link libraries to each executable
target_link_libraries(EulerPClient PRIVATE Threads::Threads)
target_link_libraries(EulerYClient PRIVATE Threads::Threads)
target_link_libraries(HelloClient PRIVATE Threads::Threads)
target_link_libraries(ComplexServer PRIVATE Threads::Threads)
