cmake_minimum_required(VERSION 3.12)
project(lkcpp)
find_package(GTest REQUIRED)
set(CMAKE_BUILD_TYPE Debug)

add_library(lkcpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/except/failed_allocation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/except/out_of_bounds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/alloc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/memcmp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/memcpy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/memfill.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lkcpp/memory/memshift.cpp
)

add_executable(test
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_tuple.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_type_traits.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/memory/test_alloc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/memory/test_memcmp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/memory/test_memcpy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/memory/test_memfill.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/memory/test_memshift.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/memory/test_unique_ptr.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/test/utility/test_pair.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/test/util/instance_counter.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/test/
    ${GTEST_INCLUDE_DIRS}
)
    
target_link_libraries(test PUBLIC
    lkcpp
    ${GTEST_LIBRARIES}
    pthread
)
    
if(CMAKE_COMPILER_IS_GNUCXX)
    LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(GCOVR_ADDITIONAL_ARGS "--exclude-throw-branches")
    setup_target_for_coverage_gcovr_html(
        NAME lkcpp_coverage
        EXECUTABLE test -j ${PROCESSOR_COUNT}
        DEPENDENCIES lkcpp
        BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
    )
endif()