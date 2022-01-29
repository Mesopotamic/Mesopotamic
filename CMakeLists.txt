cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Mesopatamic VERSION 0.1.0 LANGUAGES C)

# Allow the examples to be packaged up into nice folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add a temporarily library as we have to piece all of the component parts together first!
add_library(Mesopatamic Source/Main.c)

# Add all of our component parts
add_subdirectory(VkClay)
add_subdirectory(Ziggurat)


# Now start adding all of the examples
add_subdirectory(Examples/VkClay)
add_subdirectory(Examples/VkZiggurat)