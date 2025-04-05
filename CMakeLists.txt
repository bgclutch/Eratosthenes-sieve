cmake_minimum_required(VERSION 3.11)
project(sieve)
add_executable(sieve)

target_include_directories(sieve PUBLIC ${PROJECT_SOURCE_DIR}/inc)

target_sources(sieve PRIVATE
    src/sieve.c
    src/main.c
)

target_compile_options(sieve PRIVATE
    $<$<CONFIG:DEBUG>:
        -Wall
        -Wextra
        -Wpedantic
        -g
        -O0
        -DDEBUG
        -Wmissing-declarations
        -Wcast-align
        -Wunused
        -Wshadow
        -Wsign-conversion
        -fsanitize=address>
)

target_link_libraries(sieve PRIVATE m)

set_property(TARGET sieve PROPERTY C_STANDARD 99)

target_link_options(sieve PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)