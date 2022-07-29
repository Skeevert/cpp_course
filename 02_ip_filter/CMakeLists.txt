cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION ${PROJECT_VERSION})

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         58d77fa8070e8cec2dc1ed015d66b454c8d78850
)

FetchContent_MakeAvailable(googletest)

add_executable(ip_filter
  ipaddress.cpp
  ip_filter.cpp
)

add_executable(ip_filter_test
  ip_filter_test.cpp
  ipaddress.cpp
)

enable_testing()

target_link_libraries(ip_filter_test gtest_main)
include(GoogleTest)
gtest_discover_tests(ip_filter_test)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(ip_filter_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


target_include_directories(ip_filter
  PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

add_test(ip_filter_test ip_filter_test)
