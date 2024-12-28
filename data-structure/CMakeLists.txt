cmake_minimum_required(VERSION 3.20.0)

include(GNUInstallDirs)

project(cxx_datastructure)

add_library(data_structure_obj OBJECT)
target_include_directories(data_structure_obj PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	
)

add_subdirectory(src)

add_library(data_structure_static STATIC $<TARGET_OBJECTS:data_structure_obj>)
target_include_directories(data_structure_static PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	
)

option(ENABLE_SHARED_LIB "build shared library" OFF)
if(ENABLE_SHARED_LIB)
	add_library(data_structure_shared SHARED $<TARGET_OBJECTS:data_structure_obj>)
	target_include_directories(data_structure_shared PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	
	)
	set_target_properties(data_structure_shared PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

if(ENABLE_SHARED_LIB)
	install(TARGETS data_structure_static data_structure_shared
		EXPORT data_structureConfig
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
else()
	install(TARGETS data_structure_static
		EXPORT data_structureConfig
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
endif()

install(EXPORT data_structureConfig
	NAMESPACE data_structure::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

add_executable(example main.cpp "src/vector.cpp")

target_sources(example PRIVATE $<TARGET_OBJECTS:data_structure_obj>)
target_include_directories(example PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>	
)
