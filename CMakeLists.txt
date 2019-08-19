cmake_minimum_required(VERSION 3.14)
project(CppLearning)

set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(google/benchmark)

add_executable(CppLearning Basics.cpp Arguments.cpp MovableType.cpp MovableType.h HashMap.cpp HashMap.h Utils.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)

add_executable("${PROJECT_NAME}Benchmark" Arguments.cpp Benchmarks.cpp)
target_link_libraries("${PROJECT_NAME}Benchmark" benchmark)

find_package(
    Boost 1.54.0 REQUIRED #1.54.0 or greater
    COMPONENTS
    context
    thread
)

if (Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(folly CONFIG REQUIRED)

if (folly_FOUND)
    message(STATUS "folly_INCLUDE_DIRS: ${FOLLY_INCLUDE_DIR}")
    message(STATUS "folly_LIBRARIES: ${FOLLY_LIBRARIES}")

    include_directories(${FOLLY_INCLUDE_DIR})
endif()

#find_library(BENCHMARK follybenchmark PATHS)

add_executable("${PROJECT_NAME}FollyBasics" Arguments.cpp FollyBasics.cpp)
target_link_libraries("${PROJECT_NAME}FollyBasics" ${Boost_LIBRARIES} ${FOLLY_LIBRARIES})

