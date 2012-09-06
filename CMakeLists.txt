
cmake_minimum_required (VERSION 2.8.8)
set(INCLUDES /usr/include/)
set(INCLUDES ${INCLUDES} /usr/include/ni/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(AVG_PATH $ENV{AVG_PATH})
if(NOT EXISTS "${AVG_PATH}/libavg/src/api.h")
          message(FATAL_ERROR "Please define the environment variable AVG_PATH to the directory containing the main libavg dir.")
endif()

if(WIN32)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${AVG_PATH}")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "../deps")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\gtkmm")
endif()

project (onicam)

set(PYTHON_LIBRARY "/usr/lib/libpython2.7.so")
set(PYTHON_INCLUDE_DIR "/home/richy/.virtualenvs/Archimedes/include/python2.7")
find_package(PythonLibs REQUIRED)
set(INCLUDES ${INCLUDES} ${PYTHON_INCLUDE_DIRS})
set(LIBS ${LIBS} ${PYTHON_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS python thread)
set(INCLUDES ${INCLUDES} ${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

find_package(LibXml2 REQUIRED)
set(INCLUDES ${INCLUDES} ${LIBXML2_INCLUDE_DIR})
set(LIBS ${LIBS} ${LIBXML2_LIBRARIES})

find_package(OpenNI REQUIRED)
set(INCLUDES ${INCLUDES} ${OpenNI_INCLUDE_DIR})
set(LIBS ${LIBS} ${OPENNI_LIBRARY})

set(INCLUDES ${INCLUDES} ${AVG_PATH}/libavg/src)

include_directories (${INCLUDES})

set(ONITOUCH_SRC src/DepthTouchDetector.cpp src/OniDeviceManager.cpp src/OniCamPlugin.cpp
                                src/OniDevice.cpp src/OniDeviceThread.cpp src/OniCameraNode.cpp src/OniCamera.cpp)

add_library (onicam MODULE ${ONITOUCH_SRC})
set_target_properties(onicam PROPERTIES PREFIX "")
if(APPLE)
    set(CMAKE_MODULE_LINKER_FLAGS "-bundle -flat_namespace -undefined suppress")
    target_link_libraries (onicam ${LIBS})
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries (onicam ${LIBS} ${AVG_PATH}/libavg/src/wrapper/.libs/avg.so /usr/lib/libOpenNI.so)
endif()

if(WIN32)
    set_target_properties(onicam PROPERTIES COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB;AVG_PLUGIN")
    target_link_libraries (onicam ${LIBS} ${AVG_PATH}/libavg/win/Release/avg.lib)
endif()
add_custom_command(
    TARGET onicam
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CFG_INTDIR}/onicam${CMAKE_SHARED_LIBRARY_SUFFIX} ..
    )

execute_process(COMMAND python -c "import os,libavg; print os.path.dirname(libavg.__file__)"
    OUTPUT_VARIABLE AVG_LIB_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
install(TARGETS onicam
    DESTINATION ${AVG_LIB_PATH}/plugin/
    )

set_target_properties(PROPERTIES PREFIX "")
