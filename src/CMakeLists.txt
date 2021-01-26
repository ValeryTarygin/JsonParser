cmake_minimum_required(VERSION 3.10)

project(Main)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(SOURCE_FILES "main.cpp")

set(SOURCE_FILES_LIB_JSON "JsonParser/json_parser.cpp")
set(SOURCE_FILES_LIB_COMPOSITE "Composite/composite_values.cpp")

add_library(Json ${SOURCE_FILES_LIB_JSON})
add_library(Composite ${SOURCE_FILES_LIB_COMPOSITE})

add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main Json)
target_link_libraries(Main Composite)

enable_testing ()
add_subdirectory (test)
