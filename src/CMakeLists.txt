file(GLOB_RECURSE SXXPR_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.hpp)

add_library(${SXXPR_NAME} STATIC ${SXXPR_SRC_FILES})
add_library(${SXXPR_NAME}Shared SHARED ${SXXPR_SRC_FILES})
include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
    )

# Installation steps
install(TARGETS ${SXXPR_NAME} ${SXXPR_NAME}Shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT libraries
    )

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
    DESTINATION .
    COMPONENT headers
    )
