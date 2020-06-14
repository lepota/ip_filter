cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.1$ENV{TRAVIS_BUILD_NUMBER})

add_executable(ip_filter src/ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
    COMPILE_OPTIONS "-std=c++2a;-Wpedantic;-Wall;-Wextra;-Werror"
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT timelexa@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

get_property(dir VARIABLE PROPERTY PROJECT_SOURCE_DIR)
message("DIR = ${dir}")
add_test(
    NAME FirstTest
    COMMAND bash -c "cat ${dir}/tests/ip_filter.tsv | ./ip_filter > ${dir}/tests/out1.txt"
    VERBATIM
    WORKING_DIRECTORY "./"
)
add_test(
    NAME SecondTest
    COMMAND bash -c "diff out1.txt ip_filter.tst" WORKING_DIRECTORY "${dir}/tests"
)

set_tests_properties(FirstTest PROPERTIES
    PASS_REGULAR_EXPRESSION ""
)

set_tests_properties(SecondTest PROPERTIES
    PASS_REGULAR_EXPRESSION ""
)
