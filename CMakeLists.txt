cmake_minimum_required(VERSION 3.28.2)

set(TARGET_NAME neon)
set(VERSION 0.1.0)

project(${TARGET_NAME} VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

add_definitions(
    -D__STDC_LIMIT_MACROS
    -D__STDC_CONSTANT_MACROS
)

## VERSION OF LLVM

execute_process(COMMAND llvm-config --version OUTPUT_VARIABLE LLVM_VERSION)
message("LLVM VERSION: " ${LLVM_VERSION})
string(STRIP ${LLVM_VERSION} LLVM_VERSION)

string(COMPARE NOTEQUAL ${LLVM_VERSION} "17.0.1" LLVM_VERSION_PASSED)

if(${LLVM_VERSION_PASSED})
    message(FATAL_ERROR "LLVM VERSION REQUIRED: 17.0.1")
endif()

### NEONC

execute_process(COMMAND llvm-config --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
execute_process(COMMAND llvm-config --libs all OUTPUT_VARIABLE LLVM_LIBRARIES)

string(STRIP ${LLVM_INCLUDE} LLVM_INCLUDE)
string(STRIP ${LLVM_LIBRARIES} LLVM_LIBRARIES)

file(
    GLOB
    NEONC_SRC_FILES
    ${PROJECT_SOURCE_DIR}/neon/neonc/*.cpp
    ${PROJECT_SOURCE_DIR}/neon/neonc/*/*.cpp
)

add_executable(neonc ${NEONC_SRC_FILES})

target_include_directories(neonc PRIVATE ${LLVM_INCLUDE} include)
target_link_libraries(neonc ${LLVM_LIBRARIES})

target_precompile_headers(neonc PRIVATE include/neonc.h)

###

if(MSVC)
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
        -Wno-error=maybe-uninitialized
    )
endif()

if (UNIX AND NOT APPLE)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE ld_version)
    if ("${ld_version}" MATCHES "GNU gold")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
    endif()
endif()
