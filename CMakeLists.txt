cmake_minimum_required(VERSION 3.28.2)

set(TARGET_NAME neon)
set(VERSION 0.1.0)

project(${TARGET_NAME} VERSION ${VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

### LLVM

find_package(LLVM REQUIRED CONFIG PATHS ${PROJECT_SOURCE_DIR}/build/debug/llvm/build/debug/llvm/installed)

message(STATUS "LLVM version: ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVMConfig.cmake path: ${LLVM_DIR}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM definitions: ${LLVM_DEFINITIONS}")

llvm_map_components_to_libnames(LLVM_LIBRARIES core support irreader passes native)
message(STATUS "LLVM libs: ${LLVM_LIBRARIES}")

add_definitions(${LLVM_DEFINITIONS})

###

### NEONC

file(
    GLOB
    NEONC_SRC_FILES
    ${PROJECT_SOURCE_DIR}/neon/neonc/*.cpp
    ${PROJECT_SOURCE_DIR}/neon/neonc/*/*.cpp
    ${PROJECT_SOURCE_DIR}/neon/neonc/*/*/*.cpp
)

add_library(neonc STATIC ${NEONC_SRC_FILES})

target_include_directories(neonc PRIVATE ${LLVM_INCLUDE_DIRS} include neon)
target_link_libraries(neonc ${LLVM_LIBRARIES})

target_precompile_headers(neonc PRIVATE include/neonc.h)

###

### NEON

file(
    GLOB
    NEON_SRC_FILES
    ${PROJECT_SOURCE_DIR}/neon/neon/*.cpp
    ${PROJECT_SOURCE_DIR}/neon/neon/*/*.cpp
)

add_executable(neon ${NEON_SRC_FILES})

target_include_directories(neon PRIVATE neon)
target_link_libraries(neon neonc)

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
        -Wno-error=overloaded-virtual
    )
endif()

# if (UNIX AND NOT APPLE)
#     execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE ld_version)
#     if ("${ld_version}" MATCHES "GNU gold")
#         set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
#         set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
#     endif()
# endif()
