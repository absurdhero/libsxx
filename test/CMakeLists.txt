enable_testing()

# gtest definition
include(ExternalProject)

ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.6.0
    TIMEOUT 10
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    PREFIX "gtest"
)

ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

# tests definition
set(TARGET sxxpr)
set(GTEST_TARGET ${TARGET}_GTest)
file(GLOB_RECURSE TESTS_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(
  ${source_dir}/include
  ${PROJECT_SOURCE_DIR}/src/include
)
add_dependencies(${GTEST_TARGET} googletest)
target_link_libraries(${GTEST_TARGET}
    ${TARGET}
    #gtest gtest_main
    ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
)

if(CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(${GTEST_TARGET} pthread)
endif()

