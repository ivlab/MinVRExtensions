cmake_minimum_required (VERSION 2.8.2)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

project (MinVR_TUIO)

#------------------------------------------
# Define the source and header files
#------------------------------------------

set (SOURCEFILES
TUIOPlugin.cpp
InputDeviceTUIOClient.cpp
TuioDeviceDriver.cpp
)

set (HEADERFILES
InputDeviceTUIOClient.H
TuioDeviceDriver.h
)

add_definitions(-DUSE_TUIO)

source_group("Header Files" FILES ${HEADERFILES})

#------------------------------------------
# Download dependencies
#------------------------------------------

	set(tuio_checkout_Dir ${PROJECT_SOURCE_DIR}/tuio)
	make_directory(${tuio_checkout_Dir})
    message("   Library will be built from source in ${tuio_checkout_Dir}.")
	include(ExternalProject)
	set(tuio_PREFIX "${tuio_checkout_Dir}")
	set(tuio_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}")
	set(tuio_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${tuio_INSTALL_DIR}")
	set(tuio_DIR "${tuio_INSTALL_DIR}")
	set(tuio_PATCH ${CMAKE_COMMAND} -E copy ${tuio_checkout_Dir}/CMakeLists.txt <SOURCE_DIR>/CMakeLists.txt && ${CMAKE_COMMAND} -E copy ${tuio_checkout_Dir}/TuioServer.cpp <SOURCE_DIR>/TUIO/TuioServer.cpp)

	if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(tuio_CMAKE_ARGS ${tuio_CMAKE_ARGS} -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD=c++11 -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY=libc++)
	endif()

	ExternalProject_add(TUIO
			PREFIX ${tuio_PREFIX}
			URL http://prdownloads.sourceforge.net/reactivision/TUIO_CPP-1.4.zip
			INSTALL_DIR ${tuio_INSTALL_DIR}
			CMAKE_ARGS ${tuio_CMAKE_ARGS}
			PATCH_COMMAND ${tuio_PATCH}
			UPDATE_COMMAND ""
	 )		 
	set_property(TARGET TUIO PROPERTY FOLDER "Dependencies")
	set(TUIO_INCLUDE_DIR ${tuio_INSTALL_DIR}/include CACHE INTERNAL "Directory of TUIO header files")
	if(MSVC)
		set(TUIO_LIBRARY ${tuio_INSTALL_DIR}/lib/TUIO.dll CACHE INTERNAL "TUIO lib file")
	else()
		set(TUIO_LIBRARY ${tuio_INSTALL_DIR}/lib/libTUIO.so CACHE INTERNAL "TUIO lib file")
	endif()
	set(LIBS_ALL ${LIBS_ALL} ${TUIO_LIBRARY})
	include_directories(${TUIO_INCLUDE_DIR})

#------------------------------------------
# Include Directories
#------------------------------------------
include_directories (
  .
)
#${MinVR_INCLUDE_DIRS}

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
add_library ( ${PROJECT_NAME} SHARED ${HEADERFILES} ${SOURCEFILES} )
if(USE_BOOST)
	add_dependencies(${PROJECT_NAME} boost MVRCore)
else()
	add_dependencies(${PROJECT_NAME} MVRCore)
endif()


#------------------------------------------
# Install Target
#------------------------------------------

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION ${PROJECT_NAME}/lib
         ARCHIVE DESTINATION ${PROJECT_NAME}/lib
         RUNTIME DESTINATION ${PROJECT_NAME}/bin)
