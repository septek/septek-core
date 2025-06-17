cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(septek-core LANGUAGES C)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_executable(septek-core
    src/main.c
)

if (NOT SF_DEVENV)
    include(FetchContent)
    FetchContent_Declare(
        sf-gfx
        GIT_REPOSITORY https://github.com/septek/sf-gfx.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(sf-gfx)
endif()

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET septek-core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:septek-core> $<TARGET_RUNTIME_DLLS:septek-core>
        USES_TERMINAL COMMAND_EXPAND_LISTS
    )
endif()

target_link_libraries(septek-core PRIVATE sf-gfx)
target_compile_options(septek-core PRIVATE
    -Wall -Werror -Wextra -pedantic -Wconversion
    -Wsign-conversion -Wformat=2 -Wundef
    -Wdouble-promotion -Wnull-dereference -Wstrict-overflow
)