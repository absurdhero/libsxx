
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest-release-1.8.0)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# tests definition
set(TARGET sxx)
set(GTEST_TARGET ${TARGET}_GTest)
file(GLOB_RECURSE TESTS_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(
  ${source_dir}/include
  ${PROJECT_SOURCE_DIR}/src/include
)
target_link_libraries(${GTEST_TARGET}
    ${TARGET}
    gtest gtest_main
)

if(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(${GTEST_TARGET} pthread)
endif()

add_test(all_gtests ${GTEST_TARGET})
