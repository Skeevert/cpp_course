cmake_minimum_required(VERSION 3.5)

set(PROJECT_VERSION 1.0.0)

project(my_allocator VERSION ${PROJECT_VERSION})

add_executable(my_allocator main.cpp)
set_target_properties(my_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(my_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(my_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS my_allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


