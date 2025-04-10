cmake_minimum_required(VERSION 3.13)

project(serialization VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE serialization_SOURCES "src/serialization/*.cpp") # CMAKE_CONFIGURE_DEPENDS
file(GLOB_RECURSE serialization_HEADERS "src/serialization/*.h") # CMAKE_CONFIGURE_DEPENDS
file(GLOB_RECURSE event_system_SOURCES "src/userland/*.cpp") # CMAKE_CONFIGURE_DEPENDS
file(GLOB_RECURSE event_system_HEADERS "src/userland/*.h") # CMAKE_CONFIGURE_DEPENDS

add_library(serialization SHARED ${serialization_SOURCES} ${serialization_HEADERS})
target_include_directories(serialization PRIVATE src/serialization)
target_compile_definitions(serialization PRIVATE BUILDDLL)

add_executable(event_system ${event_system_SOURCES} ${event_system_HEADERS})
target_include_directories(event_system PRIVATE src/userland)
target_link_libraries(event_system PRIVATE serialization)


# set (serialization_INCLUDE_DIRS "")
# foreach (_headerFile ${serialization_HEADERS})
#     get_filename_component(_dir ${_headerFile} PATH)
#     list (APPEND serialization_INCLUDE_DIRS ${_dir})
# endforeach()

# list (REMOVE_DUPLICATES serialization_INCLUDE_DIRS)
# add_library(serialization src/serialization/)
# add_executable(event_system src/userland/)