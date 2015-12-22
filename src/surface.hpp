#ifndef SURFACE_HPP
#define SURFACE_HPP 1

enum SURFACE_TYPE { UNKNOWN,
		    PLANE_X,
		    PLANE_Y,
		    PLANE_Z,
		    GENERAL_PLANE,
		    CYLINDER_X,
		    CYLINDER_Y,
		    CYLINDER_Z,
		    CONE_X,
		    CONE_Y,
		    CONE_Z,
		    ELLIPSOID,
		    ELLIPTICAL_CYLINDER,      
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
  void PrintFluka();

private:
  void SetCoefficients(coefficients surface_coefficients);
  void SetId(int id);
  void Identify();


private:
  coefficients surfaceCoeffs;
  int surfaceType;
  int surfaceId;
};

#endif
