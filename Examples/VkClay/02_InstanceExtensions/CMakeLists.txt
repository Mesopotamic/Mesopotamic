cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(VkClay_01_Instance VERSION 0.1.0 LANGUAGES C)

add_executable(VkClay_02_InstanceExtensions Main.c)

# Add VkClay as a subproject
add_subdirectory(../../../Framework/VkClay VkClay)

# Link and include VkClay
target_link_libraries(VkClay_02_InstanceExtensions VkClay)
target_include_directories(VkClay_02_InstanceExtensions PRIVATE ${VkClay_INCLUDE_DIRS})