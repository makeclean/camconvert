######################################################################
#
# CMakeLists.txt for GCR Source
#
######################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT( camconvert )

MESSAGE ( STATUS "Building CamConvert" )

ADD_SUBDIRECTORY(test)
ADD_DEFINITIONS("-std=c++11")

# set the source files
SET(CAMCON_SRC  "main.cpp")
LIST(APPEND CAMCON_SRC "readfile.cpp")
LIST(APPEND CAMCON_SRC "csgwriter.cpp")

# set the library
SET(CAMCON_LIB "surface.cpp")
LIST(APPEND CAMCON_LIB "volume.cpp")
LIST(APPEND CAMCON_LIB "surface_manager.cpp")
LIST(APPEND CAMCON_LIB "volume_manager.cpp")

# set the includes
INCLUDE_DIRECTORIES( ${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR})

# function libraries
ADD_LIBRARY(camfuncs STATIC ${CAMCON_LIB})

# add executable
ADD_EXECUTABLE(camconvert ${CAMCON_SRC})

#
TARGET_LINK_LIBRARIES(camconvert camfuncs)

# Put the library in Lib
INSTALL ( TARGETS camconvert
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  PUBLIC_HEADER DESTINATION "include" )


