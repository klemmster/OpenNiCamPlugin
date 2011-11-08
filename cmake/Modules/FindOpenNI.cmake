# - Try to find Cairo
# Once done, this will define
#
#  CAIRO_FOUND - system has Cairo
#  Cairo_INCLUDE_DIRS - the Cairo include directories
#  Cairo_LIBRARIES - link these to use Cairo

include(LibFindMacros)

# Dependencies
libfind_package(OpenNI)

# Include dir
find_path(OpenNI_INCLUDE_DIR
  NAMES XnCppWrapper.h
  PATHS ${/usr/include/ni/}
  PATH_SUFFIXES openni
)

# Finally the library itself
find_library(OpenNI_LIBRARY
  NAMES OpenNI
  PATHS ${/usr/lib/}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(OpenNI_PROCESS_INCLUDES OpenNI_INCLUDE_DIR)
set(OpenNI_PROCESS_LIBS OpenNI_LIBRARY)
libfind_process(OpenNI)
