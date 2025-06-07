cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(septek-core LANGUAGES C)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(septek-core
    src/main.c
)


# Fetch Dependencies
include(FetchContent)

FetchContent_Declare(
    sf-structures
    GIT_REPOSITORY https://github.com/septumfunk/sf-structures.git
    GIT_TAG master
)
FetchContent_MakeAvailable(sf-structures)
add_custom_command(TARGET septek-core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sf-structures>
        $<TARGET_FILE_DIR:septek-core>
)


target_link_libraries(septek-core PRIVATE
    sf-structures
)