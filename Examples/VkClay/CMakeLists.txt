cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(Examples 
	01_Instance
	02_InstanceExtensions)

foreach(example ${Examples})
	add_subdirectory(${example})

	set_target_properties("VkClay_${example}" PROPERTIES FOLDER "Examples/VkClay")
endforeach()