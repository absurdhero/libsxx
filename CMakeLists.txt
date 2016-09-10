cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(libsxx)

if($ENV{BUILD_NUMBER})
    set(BUILD_NUMBER $ENV{BUILD_NUMBER})
else()
    set(BUILD_NUMBER 0)
endif()

set(LIBSXX_NAME "sxx")
set(LIBSXX_VERSION "0.1.0.${BUILD_NUMBER}")
set(LIBSXX_BRIEF "an s-expression library for C++14")

add_subdirectory(src)
add_subdirectory(test)
