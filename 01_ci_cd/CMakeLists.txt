cmake_minimum_required(VERSION 3.2)

set(BUILD_NUMBER "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${BUILD_NUMBER})

project(helloworld VERSION ${PROJECT_VESRION})


include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         58d77fa8070e8cec2dc1ed015d66b454c8d78850
)

FetchContent_MakeAvailable(googletest)

configure_file(build.h.in build.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

add_executable(test_build test_build.cpp)
target_link_libraries(test_build gtest_main)
include(GoogleTest)
gtest_discover_tests(test_build)

set_target_properties(helloworld_cli helloworld test_build PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)
target_link_libraries(test_build
    helloworld
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    target_compile_options(test_build PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_build PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_build test_build)
