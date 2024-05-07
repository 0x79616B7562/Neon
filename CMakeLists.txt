cmake_minimum_required(VERSION 3.28.2)

set(TARGET_NAME neon)
set(VERSION 0.1.0)

project(${TARGET_NAME} VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_definitions(
    -D__STDC_LIMIT_MACROS
    -D__STDC_CONSTANT_MACROS
)

### NIR

execute_process(COMMAND llvm-config --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
execute_process(COMMAND llvm-config --libs all OUTPUT_VARIABLE LLVM_LIBRARIES)

string(STRIP ${LLVM_INCLUDE} LLVM_INCLUDE)
string(STRIP ${LLVM_LIBRARIES} LLVM_LIBRARIES)

file(
    GLOB
    NIR_SRC_FILES
    ${PROJECT_SOURCE_DIR}/nir/*.cpp
)

add_library(nir STATIC ${NIR_SRC_FILES})

target_include_directories(nir PRIVATE ${LLVM_INCLUDE})
target_link_libraries(nir ${LLVM_LIBRARIES})

### FRONTEND

file(
    GLOB
    FRONTEND_SRC_FILES
    ${PROJECT_SOURCE_DIR}/frontend/*.cpp
    ${PROJECT_SOURCE_DIR}/frontend/*/*.cpp
)

add_library(frontend STATIC ${FRONTEND_SRC_FILES})

###

file(
    GLOB
    NEONC_SRC_FILES
    ${PROJECT_SOURCE_DIR}/neonc/*.cpp
)

add_executable(neonc ${NEONC_SRC_FILES})

target_include_directories(neonc PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(neonc PRIVATE nir frontend)

###

if(MSVC)
    # target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
    message(FATAL_ERROR "MSVC UNTESTED")
else()
    target_compile_options(
        neonc PRIVATE
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
        -Wno-error=reorder
        -Wno-reorder
    )
endif()

