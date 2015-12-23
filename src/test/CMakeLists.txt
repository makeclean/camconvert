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
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsPlaneX COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsPlaneX)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsPlaneY COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsPlaneY)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsPlaneZ COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsPlaneZ)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsCylinderX COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsCylinderX)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsCylinderY COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsCylinderY)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsCylinderZ COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsCylinderZ)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsSphere COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsSphere)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsGQ COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsGQ)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsECX COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsECX)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsECY COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsECY)
ADD_TEST(NAME CamConvertSurfaceTest.MakeSurfaceCoeffsECZ COMMAND camconvert_unit_tests --gtest_filter=CamConvertTest.MakeSurfaceCoeffsECZ)

	
