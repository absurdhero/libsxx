file(GLOB_RECURSE LIBSXX_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.hpp)

add_library(${LIBSXX_NAME} STATIC ${LIBSXX_SRC_FILES})
add_library(${LIBSXX_NAME}Shared SHARED ${LIBSXX_SRC_FILES})
include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
    )

# Installation steps
install(TARGETS ${LIBSXX_NAME} ${LIBSXX_NAME}Shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT libraries
    )

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
    DESTINATION .
    COMPONENT headers
    )
