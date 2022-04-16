cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(Mesopotamic VERSION 0.1.0 LANGUAGES C)

# Ensure that the Mesopotamic project doesn't get built multiple times
# By adding an interface phony target
if(TARGET Mesopotamic)
	return()
endif()
add_library(Mesopotamic INTERFACE)

# The most important thing that Mesopotamic root build does is declaring the path
# To each of the different core components. These are force pushed into the cache
# Then later in the build process when the components try to cache the paths to 
# their dependencies, they won't be able to overwrite them 
#
# This way components will build either by looking locally for their submodules
# or when building the whole mesopotamic, they will already be feed an external
# path to those modules. This helps us save many repeated clones
set(MESO_BUILD_ROOT TRUE CACHE BOOL "Mesopotamic is building from root" FORCE)
set(MESO_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "" FORCE)

set(MESO_CMAKE 		"${MESO_ROOT_DIR}/Helpers/MesoCMake" 		CACHE PATH "" FORCE)
set(MESO_XML 		"${MESO_ROOT_DIR}/Helpers/MesoXML" 			CACHE PATH "" FORCE)
set(MESO_VKCLAY 	"${MESO_ROOT_DIR}/Vulkan/Headers/VkClay" 	CACHE PATH "" FORCE)
set(MESO_VKTABLET 	"${MESO_ROOT_DIR}/Vulkan/Headers/VkTablet" 	CACHE PATH "" FORCE)
set(MESO_SOLOMON 	"${MESO_ROOT_DIR}/Windowing/Solomon" 		CACHE PATH "" FORCE)

# Decide when to build the examples as static or dynamic. When users are working 
# on the libraries themselves it's easiest to make the builds static 
# It's easier because then the libraries don't have to copied across to the 
# executables working directory
# 
# Because Mesopotamic is masively under development right now, we're gonna
# set that to on by default
option(MESO_BUILD_STATIC "Build all Mesopotamic libraries as static" ON)

# Decide when to build the examples, if the user is calling Mesopotamic from a 
# Higher directory, then there's no point in building the examples! However 
# if not, we'll use an option, options won't override user choices but will
# still cache the variable
option(MESO_BUILD_EXAMPLES "Build any Mesopotamic examples" ON)

# Now add the CMake helper functions used in every Mesopotamic project
list(APPEND CMAKE_MODULE_PATH ${MESO_CMAKE})
include(Mesopotamic)

# Now start adding all of the Mesopotamic projects into the build tree
add_subdirectory(${MESO_SOLOMON})
add_subdirectory(${MESO_XML})