cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(VkClay_01_Instance VERSION 0.1.0 LANGUAGES C)

add_executable(VkClay_01_Instance Main.c)

# Add VkClay as a subproject
add_subdirectory(../../../VkClay VkClay)

# Link and include VkClay
target_link_libraries(VkClay_01_Instance VkClay)
target_include_directories(VkClay_01_Instance PRIVATE ${VkClay_INCLUDE_DIRS})