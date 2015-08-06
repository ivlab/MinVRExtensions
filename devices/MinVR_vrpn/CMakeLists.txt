#
# Copyright Regents of the University of Minnesota, 2014.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
# Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
#
# Code author(s):
# 		Dan Orban (dtorban)
#

cmake_minimum_required (VERSION 2.8.2)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

project (MinVR_vrpn)

#------------------------------------------
# Define the source and header files
#------------------------------------------

set (SOURCEFILES
VrpnPlugin.cpp
InputDeviceVRPNAnalog.cpp
InputDeviceVRPNButton.cpp
InputDeviceVRPNTracker.cpp
VrpnDeviceDriver.cpp
)

set (HEADERFILES
InputDeviceVRPNAnalog.H
InputDeviceVRPNButton.H
InputDeviceVRPNTracker.H
VrpnDeviceDriver.h
)

source_group("Header Files" FILES ${HEADERFILES})

add_definitions(-DUSE_VRPN)

#------------------------------------------
# Download dependencies
#------------------------------------------

		set(vrpn_checkout_Dir ${PROJECT_SOURCE_DIR}/vrpn)
		make_directory(${vrpn_checkout_Dir})
        message("   Library will be built from source in ${vrpn_checkout_Dir}.")
		include(ExternalProject)
		set(vrpn_PREFIX "${vrpn_checkout_Dir}")
		set(vrpn_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/vrpn")
		set(vrpn_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${vrpn_INSTALL_DIR} -DVRPN_BUILD_DIRECTSHOW_VIDEO_SERVER=OFF -DVRPN_BUILD_HID_GUI=OFF -DVRPN_BUILD_JAVA=OFF -DVRPN_BUILD_PYTHON=OFF -DVRPN_USE_DIRECTINPUT=OFF -DVRPN_USE_DIRECTSHOW=OFF)
		set(vrpn_DIR "${vrpn_INSTALL_DIR}")


		if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
			set(vrpn_CMAKE_ARGS ${vrpn_CMAKE_ARGS} -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD=c++11 -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY=libc++)
		elseif(MSVC)
				set(vrpn_CMAKE_ARGS ${vrpn_CMAKE_ARGS} -DVRPN_USE_HID=ON -DVRPN_HID_DEBUGGING=ON -DVRPN_USE_LOCAL_HIDAPI=ON)
		endif()

		ExternalProject_add(vrpn
				PREFIX ${vrpn_PREFIX}
				URL https://github.com/vrpn/vrpn/releases/download/v07.33/vrpn_07_33.zip
				INSTALL_DIR ${vrpn_INSTALL_DIR}
				CMAKE_ARGS ${vrpn_CMAKE_ARGS}
				UPDATE_COMMAND ""
		 )		 
		set_property(TARGET vrpn PROPERTY FOLDER "Dependencies")
		set(VRPN_INCLUDE_DIR ${vrpn_INSTALL_DIR}/include CACHE INTERNAL "Directory of VRPN header files")
		if(MSVC)
			set(VRPN_LIBRARY optimized ${vrpn_INSTALL_DIR}/lib/vrpn.lib debug ${vrpn_INSTALL_DIR}/lib/vrpnd.lib CACHE INTERNAL "VRPN lib file")
			set(All_LIB ${MinVR_LIBRARIES})
		else()
			set(VRPN_LIBRARY optimized ${vrpn_INSTALL_DIR}/lib/libvrpn.a debug ${vrpn_INSTALL_DIR}/lib/libvrpnd.a CACHE INTERNAL "VRPN lib file")
		endif()	
		add_definitions(-DUSE_VRPN)
		#set(LIBS_ALL ${LIBS_ALL} ${VRPN_LIBRARY})
		include_directories(${VRPN_INCLUDE_DIR})

#------------------------------------------
# Include Directories
#------------------------------------------
include_directories (
  .
)
# ${MinVR_INCLUDE_DIRS}

#------------------------------------------
# Specific preprocessor defines
#------------------------------------------

# Windows Section #
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	# Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set(All_LIB ${MinVR_LIBRARIES})
endif()

#------------------------------------------
# Set output directories to lib, and bin
#------------------------------------------
make_directory(${CMAKE_BINARY_DIR}/lib)
make_directory(${CMAKE_BINARY_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
foreach (CONF ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${CONF} CONF)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/bin)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/lib)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/lib)
endforeach(CONF CMAKE_CONFIGURATION_TYPES)

#------------------------------------------
# Handle library naming
#------------------------------------------

#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

#------------------------------------------
# Build Target
#------------------------------------------
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library ( ${PROJECT_NAME} SHARED ${HEADERFILES} ${SOURCEFILES} )
if(USE_BOOST)
	add_dependencies(${PROJECT_NAME} boost vrpn MVRCore)
else()
	add_dependencies(${PROJECT_NAME} vrpn MVRCore)
endif()
target_link_libraries(${PROJECT_NAME} ${VRPN_LIBRARY} ${All_LIB})

#------------------------------------------
# Install Target
#------------------------------------------

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION ${PROJECT_NAME}/lib
         ARCHIVE DESTINATION ${PROJECT_NAME}/lib
         RUNTIME DESTINATION ${PROJECT_NAME}/bin)
