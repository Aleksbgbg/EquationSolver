set(BINARY_NAME ${PROJECT_NAME}Test)
set(TEST_NAME ${PROJECT_NAME}Test)

set(SOURCES test_main.cc core/math/MatrixTest.cc)

add_executable(${BINARY_NAME} ${SOURCES})
target_include_directories(${BINARY_NAME} PRIVATE ${SRC_DIR} ${TEST_DIR})
target_link_libraries(${BINARY_NAME} PRIVATE ${SRC_LIBRARY_NAME} gtest gmock)

add_test(NAME ${TEST_NAME} COMMAND ${BINARY_NAME})
