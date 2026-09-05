add_executable(net_client_tests
    test/net_client_test.cpp
)

target_include_directories(net_client_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(net_client_tests PRIVATE GTest::gtest_main)

add_test(NAME net_client_tests COMMAND net_client_tests)
