cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(VkClay_03_Zig_Surface VERSION 0.1.0 LANGUAGES C)

add_executable(VkClay_03_Zig_Surface 
	Main.c
	VkObjects.h
	VkInstance.c
	VkDevice.c
	VkSurface.c)

# Add VkClay as a subproject
add_subdirectory(../../../VkClay VkClay)

# Link and include VkClay
target_link_libraries(VkClay_03_Zig_Surface VkClay)
target_include_directories(VkClay_03_Zig_Surface PRIVATE ${VkClay_INCLUDE_DIRS})