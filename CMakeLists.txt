cmake_minimum_required(VERSION 3.28.2)

set(TARGET_NAME neon)
set(VERSION 0.1.0)

project(${TARGET_NAME} VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(
    GLOB
    SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*/*.cpp
)

add_executable(${TARGET_NAME} ${SRC_FILES})

if(MSVC)
    # target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
    message(FATAL_ERROR "MSVC UNTESTED")
else()
    target_compile_options(
        ${TARGET_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wno-error=missing-field-initializers
        -Wno-missing-field-initializers
        -Wno-error=unused-parameter
        -Wno-error=comment
        -Wno-comment
        -Wno-error=unused-but-set-variable
        -Wno-error=unused-variable
    )
endif()

