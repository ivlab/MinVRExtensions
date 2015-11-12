cmake_minimum_required (VERSION 2.8.2)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

project (MinVR_Oculus)

#------------------------------------------
# Define the source and header files
#------------------------------------------

set (SOURCEFILES
	OculusRiftDisplay.cpp
)

set (HEADERFILES
	OculusRiftDisplay.h
)

source_group("Header Files" FILES ${HEADERFILES})

#------------------------------------------
# Download dependencies
#------------------------------------------

set(osdk_checkout_Dir ${PROJECT_SOURCE_DIR}/osdk)
make_directory(${osdk_checkout_Dir})
message("   Library will be built from source in ${osdk_checkout_Dir}.")
include(ExternalProject)
set(osdk_PREFIX "${osdk_checkout_Dir}")
set(osdk_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/oculus")
set(osdk_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${osdk_INSTALL_DIR}")
set(osdk_DIR "${osdk_INSTALL_DIR}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(osdk_CMAKE_ARGS ${osdk_CMAKE_ARGS} -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD=c++11 -DCMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY=libc++)
endif()

ExternalProject_add(osdk
PREFIX ${osdk_PREFIX}
GIT_REPOSITORY https://github.com/ivlab/OculusSdkMin.git
GIT_TAG mesa
INSTALL_DIR ${osdk_INSTALL_DIR}
CMAKE_ARGS ${osdk_CMAKE_ARGS}
UPDATE_COMMAND ""
)

set_property(TARGET osdk PROPERTY FOLDER "Dependencies")
set(osdk_INCLUDE_DIR ${osdk_INSTALL_DIR}/include CACHE INTERNAL "Directory of osdk header files")
	if(MSVC)
		set(osdk_LIBRARY optimized ${osdk_INSTALL_DIR}/lib/edid.lib debug ${osdk_INSTALL_DIR}/lib/edidd.lib CACHE INTERNAL "edid lib file")
		set(osdk_LIBRARY ${osdk_LIBRARY} optimized ${osdk_INSTALL_DIR}/lib/OculusVR.lib debug ${osdk_INSTALL_DIR}/lib/OculusVRd.lib CACHE INTERNAL "edid lib file")
	else()
#		set(osdk_LIBRARY optimized ${osdk_INSTALL_DIR}/lib/libedid.a debug ${osdk_INSTALL_DIR}/lib/libedidd.a CACHE INTERNAL "edid lib file")
		set(osdk_LIBRARY ${osdk_INSTALL_DIR}/lib/libedid.a CACHE INTERNAL "edid lib file")
#		set(osdk_LIBRARY optimized ${osdk_INSTALL_DIR}/lib/libOculusVR.a debug ${osdk_INSTALL_DIR}/lib/libOculusVRd.a CACHE INTERNAL "osdk lib file")
		set(osdk_LIBRARY ${osdk_LIBRARY} ${osdk_INSTALL_DIR}/lib/libOculusVR.a CACHE INTERNAL "osdk lib file")
	endif()
add_definitions(-DUSE_osdk)
set(LIBS_ALL ${LIBS_ALL} ${osdk_LIBRARY})
include_directories(${osdk_INCLUDE_DIR})
ExternalProject_Get_Property(osdk source_dir)
include_directories(${source_dir}/LibOVR/Src)
message(sdk ${source_dir})
message(${osdk_INCLUDE_DIR})

#------------------------------------------
# Include Directories
#------------------------------------------
include_directories (
  .
)
#${MinVR_INCLUDE_DIRS}

if(USE_BOOST)
	add_definitions(-DUSE_BOOST)
endif()

#------------------------------------------
# Specific preprocessor defines
#------------------------------------------

# Windows Section #
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	# Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
	set(All_LIB ${MinVR_LIBRARIES})
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
add_library ( ${PROJECT_NAME} SHARED ${HEADERFILES} ${SOURCEFILES} )
if(USE_BOOST)
	add_dependencies(${PROJECT_NAME} osdk boost MVRCore)
else()
	add_dependencies(${PROJECT_NAME} osdk MVRCore)
endif()
target_link_libraries(${PROJECT_NAME} ${All_LIB} ${LIBS_ALL})

#------------------------------------------
# Install Target
#------------------------------------------

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION ${PROJECT_NAME}/lib
         ARCHIVE DESTINATION ${PROJECT_NAME}/lib
         RUNTIME DESTINATION ${PROJECT_NAME}/bin)
         
install(DIRECTORY ${PROJECT_SOURCE_DIR}/vrsetup/ DESTINATION "${PROJECT_NAME}/share/vrsetup")
