# test source
SET (camconvert_test_src ${CMAKE_CURRENT_SOURCE_DIR}/test_CamConvert.cpp)

# set libraries needed to link to test cases
SET(LIBS
    gtest
    camfuncs
    pthread)

# set the include dirs
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/src )
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/gtest/gtest-1.7.0/include)

# add the test executable
ADD_EXECUTABLE(camconvert_unit_tests 
  camconvert_test_driver.cpp
  ${camconvert_test_src})

# libraries
TARGET_LINK_LIBRARIES(camconvert_unit_tests ${LIBS})

# run the test
ADD_TEST(NAME CamConvertSurfaceTest.Setup COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.SetUp)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurface COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurface)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceID COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceID)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffs COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffs)

	
