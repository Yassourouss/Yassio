add_executable(net_message_tests
    test/net_message_test.cpp
)

target_include_directories(net_message_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(net_message_tests PRIVATE GTest::gtest_main)

add_test(NAME net_message_tests COMMAND net_message_tests)
