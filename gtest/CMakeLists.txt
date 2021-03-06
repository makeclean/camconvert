# CMAKE build script for DAGMC Tally

# CMAKE_SOURCE_DIR (without 'CURRENT') is the top-level dir containing CMakeLists.txt
SET (gtest_home    "${CMAKE_SOURCE_DIR}/gtest" )
SET (gtest_dir     "${gtest_home}/gtest-1.7.0" )
SET (GTEST_INC_DIR ${gtest_dir}/include PARENT_SCOPE)

# Where to look for includes
INCLUDE_DIRECTORIES(${gtest_dir} ${gtest_dir}/include)

## from here
# Setup for gtest libraries
SET(cxx_base_flags "-Wall -Wshadow -Wl,--no-as-needed  ")
SET(cxx_exception_flags "-fexceptions")
# Ref: https://groups.google.com/forum/#!topic/googletestframework/8S3QSezcoRA
SET(cxx_strict_flags "-Wextra -Wno-missing-field-initializers")

IF (CMAKE_USE_PTHREADS_INIT)  # The pthreads library is available.
    SET(cxx_base_flags "${cxx_base_flags} -DGTEST_HAS_PTHREAD=1")
ENDIF()
# Make the gtest libraries
SET(cxx_exception "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_exception_flags}")
SET(cxx_strict "${cxx_exception} ${cxx_strict_flags}")

########################################################################
#
# Defines the gtest & gtest_main libraries.  User tests should link
# with one of them.
FUNCTION(cxx_library_with_type name type cxx_flags)
# type can be either STATIC or SHARED to denote a static or shared library.
# ARGN refers to additional arguments after 'cxx_flags'.
      ADD_LIBRARY(${name} ${type} ${ARGN})
      SET_TARGET_PROPERTIES(${name}
	    PROPERTIES
            COMPILE_FLAGS "${cxx_flags}")
    IF (CMAKE_USE_PTHREADS_INIT)
         TARGET_LINK_LIBRARIES(${name} ${CMAKE_THREAD_LIBS_INIT})
    ENDIF()
ENDFUNCTION()

FUNCTION(cxx_static_library name cxx_flags)
	cxx_library_with_type(${name} STATIC "${cxx_flags}" ${ARGN})
ENDFUNCTION()

cxx_static_library(gtest ${cxx_strict} "${gtest_dir}/src/gtest-all.cc")
## do not change above here

SET (TARGET "gtest")
