cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(VkZiggurat_01_SimpleSurface VERSION 0.1.0 LANGUAGES C)

add_executable(VkZiggurat_01_SimpleSurface 
	Main.c)

# Add VkClay and Ziggurat as subprojects. Ziggurat adds VkClay For us
add_subdirectory(../../../Framework/Ziggurat Ziggurat)

# Link and include Ziggurat
target_link_libraries(VkZiggurat_01_SimpleSurface Ziggurat)
target_include_directories(VkZiggurat_01_SimpleSurface PRIVATE ${Ziggurat_INCLUDE_DIRS})
