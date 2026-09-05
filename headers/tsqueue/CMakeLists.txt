add_executable(net_tsqueue_tests
    test/net_tsqueue_test.cpp
)

target_include_directories(net_tsqueue_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(net_tsqueue_tests PRIVATE GTest::gtest_main)

add_test(NAME net_tsqueue_tests COMMAND net_tsqueue_tests)
