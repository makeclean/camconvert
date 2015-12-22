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
  surface = new Surface(coeffs,2);
  surface->Print();
  EXPECT_EQ(2,surface->GetId());
  EXPECT_EQ(GENERAL_PLANE,surface->GetSurfaceType());
}
