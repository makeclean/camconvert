#include "surface.hpp"
#include <iostream>

// empty constructor
Surface::Surface() {
  surfaceId = 0;
  surfaceType = UNKNOWN;
  surfaceCoeffs.a0=0.0;
  surfaceCoeffs.a1=0.0;
  surfaceCoeffs.a2=0.0;
  surfaceCoeffs.a3=0.0;
  surfaceCoeffs.a4=0.0;
  surfaceCoeffs.a5=0.0;
  surfaceCoeffs.a6=0.0;
  surfaceCoeffs.a7=0.0;
  surfaceCoeffs.a8=0.0;
  surfaceCoeffs.a9=0.0;
}

// destructor
Surface::~Surface() {
}

// print
void Surface::Print() {
  std::cout << "Surface ID = " << surfaceId << std::endl;
  std::cout << "Coefficients ---" << std::endl;
  std::cout << "Surface Type = " << surfaceType << std::endl;
  std::cout << "   a0 = " << surfaceCoeffs.a0 << std::endl;
  std::cout << "   a1 = " << surfaceCoeffs.a1 << std::endl;
  std::cout << "   a2 = " << surfaceCoeffs.a2 << std::endl;
  std::cout << "   a3 = " << surfaceCoeffs.a3 << std::endl;
  std::cout << "   a4 = " << surfaceCoeffs.a4 << std::endl;
  std::cout << "   a5 = " << surfaceCoeffs.a5 << std::endl;
  std::cout << "   a6 = " << surfaceCoeffs.a6 << std::endl;
  std::cout << "   a7 = " << surfaceCoeffs.a7 << std::endl;
  std::cout << "   a8 = " << surfaceCoeffs.a8 << std::endl;
  std::cout << "   a9 = " << surfaceCoeffs.a9 << std::endl;
}

// surface constructor
Surface::Surface(coefficients surface_coefficients, int id) {
  SetCoefficients(surface_coefficients);
  SetId(id);
  Identify();
}

// set the surface coefficients
void Surface::SetCoefficients(coefficients surface_coefficients) {
  surfaceCoeffs = surface_coefficients;
}

// set the surface ids
void Surface::SetId(int id) {
  surfaceId = id;
}

// set the surface ids
int Surface::GetId() {
  return surfaceId;
}

// get the surface type
int Surface::GetSurfaceType() {
  return surfaceType;
}

// identify the surface type
void Surface::Identify() {
  // determine the kind of surface we are
  // these are planes
  if(surfaceCoeffs.a4 == 0.0 && surfaceCoeffs.a5 == 0.0 && surfaceCoeffs.a6 == 0.0 ) {
    // test the rotation terms 
    if(surfaceCoeffs.a7 == 0.0 && surfaceCoeffs.a8 == 0.0 && surfaceCoeffs.a9 == 0.0 ) {
      // if no rotations then we are a plane
      if((surfaceCoeffs.a1 == 1.0 || surfaceCoeffs.a1 == -1.0 ) && surfaceCoeffs.a2 == 0.0 && surfaceCoeffs.a3 == 0.0 ) {
	surfaceType = PLANE_X;
      } else if(surfaceCoeffs.a1 == 0.0 && (surfaceCoeffs.a2 == 1.0 || surfaceCoeffs.a2 == -1.0) && surfaceCoeffs.a3 == 0.0 ) {
	surfaceType = PLANE_Y;
      }  else if(surfaceCoeffs.a1 == 0.0 && surfaceCoeffs.a2 == 0.0 && (surfaceCoeffs.a3 == 1.0 || surfaceCoeffs.a3 == -1.0) ) {
	surfaceType = PLANE_Z;
      } else { 
	surfaceType = GENERAL_PLANE;
      }
    } else {
      // this is now a plane, plus a rotation term, right now this needs to be a General Quad
      surfaceType = GENERAL_QUADRATIC;
    }
  // we know that we are not planar
  } else {
    // if no rotations then we can be cylinders with offsets 
    if(surfaceCoeffs.a7 == 0.0 && surfaceCoeffs.a8 == 0.0 && surfaceCoeffs.a9 == 0.0 ) {
      surfaceType = GENERAL_QUADRATIC;      
    } else {
      // otherwise fall back onto a general quadratic;
      surfaceType = GENERAL_QUADRATIC;
    }
  }
}

// evaluate the surface for the given point
int Surface::Evaluate(double x, double y, double z) {
  double value = 0.0;
  value += surfaceCoeffs.a0;
  value += surfaceCoeffs.a1*x + surfaceCoeffs.a4*x*x;
  value += surfaceCoeffs.a2*y + surfaceCoeffs.a5*y*y;
  value += surfaceCoeffs.a3*z + surfaceCoeffs.a6*z*z;
  value += surfaceCoeffs.a7*x*y;
  value += surfaceCoeffs.a8*y*z;
  value += surfaceCoeffs.a9*z*x;

  if (value < 0.0 ) return -1;
  if (value < 0.0 ) return  0;
  if (value > 0.0 ) return  1;
}

// 
void Surface::PrintFluka() {
  if(surfaceType == PLANE_X) {
    std::cout << "YZP S" << surfaceId << "     ";
    std::cout << surfaceCoeffs.a0 << std::endl;
  }
  if(surfaceType == PLANE_Y) {
    std::cout << "XZP S" << surfaceId << "     ";
    std::cout << surfaceCoeffs.a0 << std::endl;
  }
  if(surfaceType == PLANE_Z) {
    std::cout << "XYP S" << surfaceId << "     ";
    std::cout << surfaceCoeffs.a0 << std::endl;
  }
  if(surfaceType == GENERAL_PLANE) {
    std::cout << "PLA S" << surfaceId << "     ";
    std::cout << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << " " << surfaceCoeffs.a3;
    std::cout << " " << -1.*surfaceCoeffs.a0/surfaceCoeffs.a1;
    std::cout << " " << -1.*surfaceCoeffs.a0/surfaceCoeffs.a2;    
    std::cout << " " << -1.*surfaceCoeffs.a0/surfaceCoeffs.a3;
    std::cout << std::endl;
  }
  if(surfaceType == GENERAL_QUADRATIC) {
    std::cout << "QUA S" << surfaceId << "     ";
    /*
    std::cout << surfaceCoeffs.a0 << " " << surfaceCoeffs.a1 << "  ";
    std::cout << surfaceCoeffs.a2 << " " << surfaceCoeffs.a3 << "  ";    
    std::cout << surfaceCoeffs.a4 << " " << surfaceCoeffs.a5 << "  ";
    std::cout << surfaceCoeffs.a6 << " " << surfaceCoeffs.a7 << "  ";
    std::cout << surfaceCoeffs.a8 << " " << surfaceCoeffs.a9 << std::endl; 
    */
    std::cout << surfaceCoeffs.a4 << " " << surfaceCoeffs.a5 << "  ";    
    std::cout << surfaceCoeffs.a6 << " " << surfaceCoeffs.a7 << "  "; 
    std::cout << surfaceCoeffs.a9 << " " << surfaceCoeffs.a8 << "  "; 
    std::cout << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << "  "; 
    std::cout << surfaceCoeffs.a3 << " " << surfaceCoeffs.a0 << std::endl; 
  }
  if(surfaceType == UNKNOWN ) {
    std::cout << surfaceId << " Surface Type not defined!!" << std::endl;
  }
}
