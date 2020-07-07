cmake_minimum_required(VERSION 3.13)
project(ELF_exporter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.hpp" "extern/*.hpp", "extern/*.h")
add_executable(ELF_exporter ${SRC_FILES})

install(TARGETS ELF_exporter
        CONFIGURATIONS Release
        RUNTIME DESTINATION bin)