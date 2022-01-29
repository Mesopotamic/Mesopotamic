cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(Examples 
	01_SimpleSurface)

foreach(example ${Examples})
	add_subdirectory(${example})

	set_target_properties("VkZiggurat_${example}" PROPERTIES FOLDER "Examples/VkZiggurat")
endforeach()