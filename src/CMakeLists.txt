set(BINARY_NAME ${PROJECT_NAME})
set(SRC_LIBRARY_NAME ${BINARY_NAME}Lib)
set(SRC_LIBRARY_NAME ${SRC_LIBRARY_NAME} PARENT_SCOPE)

set(SOURCES core/math/Matrix.h core/math/numbers/Rational.cc core/math/numbers/Rational.h core/types.h core/math/greatest_common_divisor.h)

add_library(${SRC_LIBRARY_NAME} STATIC ${SOURCES})
target_include_directories(${SRC_LIBRARY_NAME} PRIVATE ${SRC_DIR})

add_executable(${BINARY_NAME} main.cc)
target_link_libraries(${BINARY_NAME} PRIVATE ${SRC_LIBRARY_NAME})
