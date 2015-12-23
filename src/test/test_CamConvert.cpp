// FluDAG/src/test/test_FlukaFuncs.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <cassert>

#include "surface.hpp"

//---------------------------------------------------------------------------//
// TEST FIXTURES
//---------------------------------------------------------------------------//
class CamConvertTest : public ::testing::Test
{
  protected:
    // initalize variables for each test
    virtual void SetUp()
    {
    }
  protected:
};

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(CamConvertTest, SetUp)
{
}

//---------------------------------------------------------------------------//
// FIXTURE-BASED TESTS:
//---------------------------------------------------------------------------//
TEST_F(CamConvertTest, MakeSurface)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  surface = new Surface();
  EXPECT_EQ(0, surface->GetId());
}

// test if the id is set correctly
TEST_F(CamConvertTest, MakeSurfaceID)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  surface = new Surface(coeffs,1);
  EXPECT_EQ(1,surface->GetId());
}

// test if the id the surface type is set correctly
TEST_F(CamConvertTest, MakeSurfaceCoeffs)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a0 = 10.;
  coeffs.a1 = 1.0;
  coeffs.a2 = 1.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(GENERAL_PLANE,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly
TEST_F(CamConvertTest, MakeSurfaceCoeffsPlaneX)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a0 = 10.;
  coeffs.a1 = 1.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(PLANE_X,surface->GetSurfaceType());
  EXPECT_LT(0,surface->Evaluate(0,0,0));
  EXPECT_EQ(0,surface->Evaluate(-10,0,0));
  EXPECT_GT(0,surface->Evaluate(-15,0,0));  
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsPlaneY)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a0 = 10.;
  coeffs.a2 = 1.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(PLANE_Y,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsPlaneZ)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a0 = 10.;
  coeffs.a3 = 1.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(PLANE_Z,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsCylinderX)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a4 = 1.0;
  coeffs.a5 = 1.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(CYLINDER_Z,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsSphere)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a4 = 1.0;
  coeffs.a5 = 1.0;
  coeffs.a6 = 1.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(SPHERE,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsGQ)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a4 = 1.0;
  coeffs.a5 = 1.0;
  coeffs.a6 = 2.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(GENERAL_QUADRATIC,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsECX)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a5 = 1.0;
  coeffs.a6 = 2.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(ELLIPTICAL_CYLINDER_X,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsECY)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a4 = 1.0;
  coeffs.a6 = 2.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(ELLIPTICAL_CYLINDER_Y,surface->GetSurfaceType());
}

// test if the id the surface type is set correctly 
TEST_F(CamConvertTest, MakeSurfaceCoeffsECZ)
{
  Surface *surface;
  Surface::coefficients coeffs = {0};
  coeffs.a4 = 1.0;
  coeffs.a5 = 2.0;
  surface = new Surface(coeffs,2);
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(ELLIPTICAL_CYLINDER_Z,surface->GetSurfaceType());
}
