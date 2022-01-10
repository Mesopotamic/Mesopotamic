cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(Examples 
	01_Instance
	02_InstanceExtensions
	03_ZigSurface)

foreach(example ${Examples})
	add_subdirectory(${example})
endforeach()