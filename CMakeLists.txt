cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(Sxxpr)

if($ENV{BUILD_NUMBER})
    set(BUILD_NUMBER $ENV{BUILD_NUMBER})
else()
    set(BUILD_NUMBER 0)
endif()

set(SXXPR_NAME "sxxpr")
set(SXXPR_VERSION "0.1.0.${BUILD_NUMBER}")
set(SXXPR_BRIEF "${SXXPR_NAME} an s-expression library for C++14")

add_subdirectory(src)
add_subdirectory(test)
