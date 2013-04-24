cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#Based on the Solution from Nicolas Burrus
project(Recorder)

## Add current Source Dir
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
## Add folder /include
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
###############################################################################
# Find OpenNI
#
# This sets the following variables:
# OPENNI_FOUND - True if OPENNI was found.
# OPENNI_INCLUDE_DIRS - Directories containing the OPENNI include files.
# OPENNI_LIBRARIES - Libraries needed to use OPENNI.
# OPENNI_DEFINITIONS - Compiler flags for OPENNI.

find_package(PkgConfig)
if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
  pkg_check_modules(PC_OPENNI2 openni-dev)
else()
  pkg_check_modules(PC_OPENNI2 QUIET openni-dev)
endif()

set(OPENNI_DEFINITIONS ${PC_OPENNI_CFLAGS_OTHER})

#add a hint so that it can find it without the pkg-config
find_path(OPENNI_INCLUDE_DIR OpenNI.h
          HINTS ${NESTK_ROOT_DIRS_HINTS} ${PC_OPENNI_INCLUDEDIR} ${PC_OPENNI_INCLUDE_DIRS} /usr/include
          PATHS "$ENV{PROGRAMFILES}/OpenNI/Include" "$ENV{PROGRAMW6432}/OpenNI/Include"
          PATH_SUFFIXES openni)
#add a hint so that it can find it without the pkg-config
find_library(OPENNI_LIBRARY
             NAMES OpenNI64 OpenNI2
             HINTS ${NESTK_ROOT_DIRS_HINTS} ${PC_OPENNI_LIBDIR} ${PC_OPENNI_LIBRARY_DIRS} /usr/lib
             PATHS "$ENV{PROGRAMFILES}/OpenNI/Lib${OPENNI_SUFFIX}" "$ENV{PROGRAMW6432}/OpenNI/Lib${OPENNI_SUFFIX}"
             PATH_SUFFIXES lib
)

set(OPENNI_INCLUDE_DIRS ${OPENNI_INCLUDE_DIR} ${NITE_INCLUDE_DIR})
if(APPLE)
  set(OPENNI_LIBRARIES ${OPENNI_LIBRARY} ${NITE_LIBRARY} usb)
else()
  set(OPENNI_LIBRARIES ${OPENNI_LIBRARY} ${NITE_LIBRARY})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenNI2 DEFAULT_MSG
    OPENNI_LIBRARY OPENNI_INCLUDE_DIR)

mark_as_advanced(OPENNI_LIBRARY OPENNI_INCLUDE_DIR)
if(OPENNI_FOUND)
  include_directories(${OPENNI_INCLUDE_DIRS})
  link_directories(${OPENNI_LIBRARY})
  add_definitions(${OPENNI_DEFINITIONS})
  message(STATUS "OpenNI2 found (include: ${OPENNI_INCLUDE_DIR}, lib: ${OPENNI_LIBRARY})")
endif(OPENNI_FOUND)

