cmake_minimum_required(VERSION 3.12)
project(lkcpp)
find_package(GTest REQUIRED)
set(CMAKE_BUILD_TYPE Debug)

add_library(lkcpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/except/failed_allocation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/except/out_of_bounds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/alloc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/memcpy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/memfill.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/pod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/pod_view.cpp
)

add_executable(test
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_dynamic_array.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_pod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_pod_view.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_unique_ptr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_vector.cpp
)

set_target_properties(lkcpp PROPERTIES
    CXX_STANDARD 20
)

set_target_properties(test PROPERTIES
    CXX_STANDARD 20
)

target_include_directories(lkcpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_include_directories(test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(test PUBLIC
    lkcpp
    ${GTEST_LIBRARIES}
    pthread
)