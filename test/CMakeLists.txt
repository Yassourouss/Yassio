add_executable(integration_tests
    integration_test.cpp
)

target_include_directories(integration_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
)

target_link_libraries(integration_tests PRIVATE GTest::gtest_main)

add_test(NAME integration_tests COMMAND integration_tests)
