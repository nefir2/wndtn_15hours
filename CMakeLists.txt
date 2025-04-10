cmake_minimum_required(VERSION 3.13)

project(serialization VERSION 1.0 LANGUAGES CXX) #project name and language definition

add_compile_options(-Wall) # define that will be shown all Warnings

set(CMAKE_CXX_STANDARD 11) # define version of the language
set(CMAKE_CXX_STANDARD_REQUIRED ON) # second line for version definition
set(CMAKE_CXX_EXTENSIONS OFF) # some extensions idk

#build serialization

file(GLOB_RECURSE serialization_SOURCES "sources/serialization/*.cpp") # define source files for dll
file(GLOB_RECURSE event_system_SOURCES "sources/userland/*.cpp") # define source files for exe

add_library(serialization SHARED ${serialization_SOURCES}) # add library to make | definition of headers are unnecessary  ${serialization_HEADERS}
target_include_directories(serialization PRIVATE sources/serialization) # define directories, or smth idk
target_compile_definitions(serialization PRIVATE BUILDDLL) # define argument for building program (build as dll)
# target_compile_definitions(serialization PRIVATE OGFN) # define additional argument for building program (output generated files' names to stdout)

add_executable(event_system ${event_system_SOURCES}) # add exe to make | definition of headers are unnecessary ${event_system_HEADERS}
target_include_directories(event_system PRIVATE sources/userland) # define directories, or smth idk
target_include_directories(event_system PRIVATE sources/serialization)
target_link_libraries(event_system PRIVATE serialization) # add generated library to executable.

#end of build serialization

# build client-server

file(GLOB_RECURSE client_SOURCES "sources/client/src/*.cpp") # define source files for dll
file(GLOB_RECURSE server_SOURCES "sources/server/src/*.cpp") # define source files for exe

add_executable(client ${client_SOURCES}) # add library to make | definition of headers are unnecessary  ${serialization_HEADERS}
target_include_directories(client PRIVATE sources/client/src sources/serialization) # define directories, or smth idk
target_link_libraries(client PRIVATE serialization ws2_32) # add libraries to executable.

add_executable(server ${server_SOURCES}) # add exeto make | definition of headers are unnecessary ${event_system_HEADERS}
target_include_directories(server PRIVATE sources/server/src sources/serialization) # define directories, or smth idk
target_link_libraries(server PRIVATE serialization ws2_32) # add libraries to executable.

# end of building client-server

# build EventSystem

file (GLOB_RECURSE EventSystem_SOURCES "sources/EventSystem/src/*.cpp")
set(GLFW_PATH "sources/EventSystem/deps/lib")
include_directories(
    "sources/EventSystem/deps/include"
    "sources/EventSystem/deps/include/GLFW"
)
link_directories(${GLFW_PATH})

message(STATUS "GLFW_PATH: ${GLFW_PATH}")

add_executable(EventSystem ${EventSystem_SOURCES})
target_include_directories(EventSystem PRIVATE sources/EventSystem/deps/include sources/EventSystem/deps/lib sources/serialization) # define directories, or smth idk
target_link_libraries(EventSystem PRIVATE glfw3dll OpenGL32 serialization)  # glfw3.lib, if not working

add_custom_command(TARGET EventSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${GLFW_PATH}/glfw3.dll"  # Источник
    "bin/glfw3.dll"  # Назначение
)

#end of Building EventSystem