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
  senseReverse = 0;
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
	if ( surfaceCoeffs.a1 == -1.0 )
	  senseReverse = 1;
	else
	  senseReverse = 0;
      } else if(surfaceCoeffs.a1 == 0.0 && (surfaceCoeffs.a2 == 1.0 || surfaceCoeffs.a2 == -1.0) && surfaceCoeffs.a3 == 0.0 ) {
	surfaceType = PLANE_Y;
	if ( surfaceCoeffs.a2 == -1.0 )
	  senseReverse = 1;
	else
	  senseReverse = 0;

      }  else if(surfaceCoeffs.a1 == 0.0 && surfaceCoeffs.a2 == 0.0 && (surfaceCoeffs.a3 == 1.0 || surfaceCoeffs.a3 == -1.0) ) {
	surfaceType = PLANE_Z;
	if ( surfaceCoeffs.a3 == -1.0 )
	  senseReverse = 1;
	else
	  senseReverse = 0;
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
      // unit size
      if(surfaceCoeffs.a4 == surfaceCoeffs.a5 && surfaceCoeffs.a6 == 0.0 ) {
	//	surfaceType = CYLINDER_Z;
	surfaceType = GENERAL_QUADRATIC;
      } else if (surfaceCoeffs.a4 == surfaceCoeffs.a6 && surfaceCoeffs.a5 == 0.0 ) {
	//	surfaceType = CYLINDER_Y;
	surfaceType = GENERAL_QUADRATIC;
      } else if (surfaceCoeffs.a4 == 0.0 && surfaceCoeffs.a5 == surfaceCoeffs.a6 ) {
	//	surfaceType = CYLINDER_X;
	surfaceType = GENERAL_QUADRATIC;
      } else if (surfaceCoeffs.a4 != 0.0 && surfaceCoeffs.a5 != 0.0 && surfaceCoeffs.a6 == 0.0 ) {
	surfaceType = ELLIPTICAL_CYLINDER_Z;
      } else if (surfaceCoeffs.a4 != 0.0 && surfaceCoeffs.a6 != 0.0 && surfaceCoeffs.a5 == 0.0 ) {
	surfaceType = ELLIPTICAL_CYLINDER_Y;
      } else if (surfaceCoeffs.a4 == 0.0 && surfaceCoeffs.a5 != 0.0 && surfaceCoeffs.a6 != 0.0 ) {
	surfaceType = ELLIPTICAL_CYLINDER_X;
      }	else if (surfaceCoeffs.a4 == surfaceCoeffs.a5 && surfaceCoeffs.a5 == surfaceCoeffs.a6 ) {
	surfaceType = SPHERE;
      } else {
	surfaceType = GENERAL_QUADRATIC;
      }
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

  if (senseReverse == 1) {
    if (value < 0.0 ) return  1;
    if (value == 0.0 ) return  0;
    if (value > 0.0 ) return  -1;
  } else {
    if (value < 0.0 ) return -1;
    if (value == 0.0 ) return  0;
    if (value > 0.0 ) return  1;
  }
}

// 
void Surface::PrintFluka(std::ofstream &output) {
  if(surfaceType == PLANE_X) {
    output << "YZP S" << surfaceId << "     ";
    output << surfaceCoeffs.a0 << std::endl;
  }
  if(surfaceType == PLANE_Y) {
    output << "XZP S" << surfaceId << "     ";
    output << surfaceCoeffs.a0 << std::endl;
  }
  if(surfaceType == PLANE_Z) {
    output << "XYP S" << surfaceId << "     ";
    output << surfaceCoeffs.a0 << std::endl;
  }
  if(surfaceType == GENERAL_PLANE) {
    output << "PLA S" << surfaceId << "     ";
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << " " << surfaceCoeffs.a3;
    if(surfaceCoeffs.a1 != 0.0 )
      output << " " << 1.*surfaceCoeffs.a0/surfaceCoeffs.a1;
    else
      output << " " << 0.0;
    if(surfaceCoeffs.a2 != 0.0 )
      output << " " << 1.*surfaceCoeffs.a0/surfaceCoeffs.a2;    
    else
      output << " " << 0.0;
    if(surfaceCoeffs.a3 != 0.0 ) 
      output << " " << 1.*surfaceCoeffs.a0/surfaceCoeffs.a3;
    else
      output << " " << 0.0;
     
    output << std::endl;
  }
  if(surfaceType == CYLINDER_X) {
    output << "XCC S" << surfaceId << "     ";
    output << surfaceCoeffs.a2 << " " << surfaceCoeffs.a3 << " " << surfaceCoeffs.a5 << std::endl;
  }
  if(surfaceType == CYLINDER_Y) {
    output << "YCC S" << surfaceId << "     ";
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a3 << " " << surfaceCoeffs.a4 << std::endl;
  }
  if(surfaceType == CYLINDER_Z) {
    output << "ZCC S" << surfaceId << "     ";
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << " " << surfaceCoeffs.a5 << std::endl;
  }
  if(surfaceType == SPHERE) {
    output << "SPH S" << surfaceId << "     ";
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << " " << surfaceCoeffs.a3;
    output << " " << surfaceCoeffs.a4 << std::endl;
  }
  if(surfaceType == ELLIPTICAL_CYLINDER_X) {
    output << "XEC S" << surfaceId << "     ";
    output << surfaceCoeffs.a2 << " " << surfaceCoeffs.a3 << " ";
    output << surfaceCoeffs.a5 << " " << surfaceCoeffs.a6 << std::endl;
  }
  if(surfaceType == ELLIPTICAL_CYLINDER_Y) {
    output << "YEC S" << surfaceId << "     ";
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a3 << " ";
    output << surfaceCoeffs.a4 << " " << surfaceCoeffs.a6 << std::endl;
  }
  if(surfaceType == ELLIPTICAL_CYLINDER_Y) {
    output << "ZEC S" << surfaceId << "     ";
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << " ";
    output << surfaceCoeffs.a4 << " " << surfaceCoeffs.a5 << std::endl;
  }
  if(surfaceType == GENERAL_QUADRATIC) {
    output << "QUA S" << surfaceId << "     ";
    output << surfaceCoeffs.a4 << " " << surfaceCoeffs.a5 << "  ";    
    output << surfaceCoeffs.a6 << " " << surfaceCoeffs.a7 << "  "; 
    output << surfaceCoeffs.a9 << " " << surfaceCoeffs.a8 << "  "; 
    output << surfaceCoeffs.a1 << " " << surfaceCoeffs.a2 << "  "; 
    output << surfaceCoeffs.a3 << " " << surfaceCoeffs.a0 << std::endl; 
  }
  if(surfaceType == UNKNOWN ) {
    output << surfaceId << " Surface Type not defined!!" << std::endl;
  }
}
