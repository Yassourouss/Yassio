add_executable(net_server_tests
    test/net_server_test.cpp
)

target_include_directories(net_server_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(net_server_tests PRIVATE GTest::gtest_main)

add_test(NAME net_server_tests COMMAND net_server_tests)
