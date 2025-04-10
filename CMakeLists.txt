cmake_minimum_required(VERSION 3.13)

project(serialization VERSION 1.0 LANGUAGES CXX) #project name and language definition

add_compile_options(-Wall) # define that will be shown all Warnings

set(CMAKE_CXX_STANDARD 11) # define version of the language
set(CMAKE_CXX_STANDARD_REQUIRED ON) # second line for version definition
set(CMAKE_CXX_EXTENSIONS OFF) # some extensions idk

file(GLOB_RECURSE serialization_SOURCES "src/serialization/*.cpp") # define source files for dll
file(GLOB_RECURSE serialization_HEADERS "src/serialization/*.h") # define header files for dll
file(GLOB_RECURSE event_system_SOURCES "src/userland/*.cpp") # define source files for exe
file(GLOB_RECURSE event_system_HEADERS "src/userland/*.h") # define header files for exe

add_library(serialization SHARED ${serialization_SOURCES} ${serialization_HEADERS}) # add library to make | definition of headers are unnecessary 
target_include_directories(serialization PRIVATE src/serialization) # define directories, or smth idk
target_compile_definitions(serialization PRIVATE BUILDDLL) # define argument for building program (build as dll)
target_compile_definitions(serialization PRIVATE OGFN) # define additional argument for building program (output generated files' names to stdout)

add_executable(event_system ${event_system_SOURCES} ${event_system_HEADERS}) # add exeto make | definition of headers are unnecessary
target_include_directories(event_system PRIVATE src/userland) # define directories, or smth idk
target_link_libraries(event_system PRIVATE serialization) # add generated library to executable.