cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Mesopatamic VERSION 0.1.0 LANGUAGES C)

# User controllable options, most are defaulted to on
# But they can be switched off with -D<OPTION_NAME>=off
# When configuring the build on commandline
option(MESO_BUILD_EXAMPLES "Build Mesopatamic Examples" ON)
option(MESO_BUILD_LAYERS "Build experimental Vulkan layers" ON)

# Allow the examples to be packaged up into nice folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add a temporarily library as we have to piece all of the component parts together first!
add_library(Mesopatamic Source/Main.c)

# Add all of our component parts
add_subdirectory(Framework/VkClay)
add_subdirectory(Framework/Ziggurat)

# Add the experimental layer
if(${MESO_BUILD_LAYERS})
	message(STATUS "Adding Experimental Vulkan Layer")
	add_subdirectory(Layer)
endif()

# Now start adding all of the examples
if(${MESO_BUILD_EXAMPLES})
	add_subdirectory(Examples/VkClay)
	add_subdirectory(Examples/VkZiggurat)
endif()