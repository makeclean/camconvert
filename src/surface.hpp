#include <fstream>

#ifndef SURFACE_HPP
#define SURFACE_HPP 1

enum SURFACE_TYPE { UNKNOWN,
		    PLANE_X,
		    PLANE_Y,
		    PLANE_Z,
		    GENERAL_PLANE,
		    SPHERE,
		    CYLINDER_X,
		    CYLINDER_Y,
		    CYLINDER_Z,
		    CONE_X,
		    CONE_Y,
		    CONE_Z,
		    ELLIPSOID,
		    ELLIPTICAL_CYLINDER_X,
		    ELLIPTICAL_CYLINDER_Y,      
		    ELLIPTICAL_CYLINDER_Z,      
		    GENERAL_QUADRATIC};
		   
class Surface { 
public:
  struct coefficients {
    double a0;
    double a1;
    double a2;
    double a3;
    double a4;
    double a5;
    double a6;
    double a7;
    double a8;
    double a9;
    double a10;
  };

public:
  Surface();
  ~Surface();
  Surface(coefficients surface_coefficients,int id);
  void Print();
  int GetId();
  int GetSurfaceType();
  int Evaluate(double x, double y, double z);
  void PrintFluka(std::ofstream &output);

private:
  void SetCoefficients(coefficients surface_coefficients);
  void SetId(int id);
  void Identify();


private:
  coefficients surfaceCoeffs;
  /*
   * senseReverse is to deal with the fact the CAM/CAF format allows the normal of a surface to be defined
   * this is not allowed in Fluka, as each surface has a defined "sense", therefore in order to use the
   * prefined surfaces, sometimes the normal will point in the incorrect direction. 
   */
  int senseReverse;
  int surfaceType;
  int surfaceId;
};

#endif
