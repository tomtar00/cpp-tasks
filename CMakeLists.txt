cmake_minimum_required(VERSION 3.16)
project(cpp-tasks CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# SFML setup (from submodule)
# =========================
add_subdirectory(deps/SFML EXCLUDE_FROM_ALL)
set(SFML_STATIC_LIBRARIES TRUE)

# =========================
# Catch2 setup (from submodule)
# =========================
add_subdirectory(deps/Catch2 EXCLUDE_FROM_ALL)
include(Catch)

# =========================
# Task 1 (lib + exe)
# =========================
add_library(task1_lib
    src/task1/QueryEngine.cpp
)
target_include_directories(task1_lib PUBLIC src)

add_executable(task1
    src/task1/main.cpp
)
target_link_libraries(task1 PRIVATE task1_lib)

# =========================
# Task 2 (lib + exe)
# =========================
add_library(task2_lib
    src/task2/Collision.cpp
)
target_include_directories(task2_lib PUBLIC src)

add_executable(task2
    src/task2/main.cpp
)
target_include_directories(task2 PRIVATE deps/SFML/include)
target_link_libraries(task2 PRIVATE task2_lib sfml-graphics sfml-window sfml-system)

# =========================
# Task 3 (exe)
# =========================
add_executable(task3
    src/task3/main.cpp
)

# =========================
# Tests
# =========================
add_executable(tests
    tests/test_task1.cpp
    tests/test_task3.cpp
)
target_include_directories(tests PRIVATE src)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        task1_lib
        task2_lib
)
catch_discover_tests(tests)