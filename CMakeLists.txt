cmake_minimum_required(VERSION 3.13)
project(ELF_exporter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

if (NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, running conan install.")
    string(REPLACE "." ";" VERSION_LIST "${CMAKE_C_COMPILER_VERSION}")
    list(GET VERSION_LIST 0 VERSION)
    list(GET VERSION_LIST 1 MINOR)
    if (NOT MINOR MATCHES 0)
        SET(VERSION ${VERSION}.${MINOR})
    endif()
    if (NOT WINDOWS)
        execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR} --install-folder=${CMAKE_BINARY_DIR} --build missing
                -s compiler=clang -s compiler.libcxx=libstdc++11 -s compiler.version=${VERSION} -s build_type=Debug)
    else()
        execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR} --install-folder=${CMAKE_BINARY_DIR} --build missing
                -s compiler=gcc -s compiler.libcxx=libstdc++11 -s compiler.version=${VERSION} -s os=Windows)
    endif()
endif ()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.hpp" "extern/*.hpp", "extern/*.h")
add_executable(ELF_exporter ${SRC_FILES})

target_link_libraries(ELF_exporter PUBLIC Arbutils)

install(TARGETS ELF_exporter
        CONFIGURATIONS Release
        RUNTIME DESTINATION bin)