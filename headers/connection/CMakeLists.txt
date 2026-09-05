add_executable(net_connection_tests
    test/net_connection_test.cpp
)

target_include_directories(net_connection_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(net_connection_tests PRIVATE GTest::gtest_main)

add_test(NAME net_connection_tests COMMAND net_connection_tests)
