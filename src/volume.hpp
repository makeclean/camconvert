#include "surface.hpp"
#include <vector>
#include <string>
#include <fstream>

#ifndef VOLUME_HPP
#define VOLUME_HPP 1

class Volume {
public:
  Volume();
  ~Volume();
  // instanciate new volume
  Volume(int vol_id, double density, int material_number,
	 std::vector<Surface*> bounding_surfaces,
	 double x, double y, double z,
	 std::string name);
  void SetDensity(double density);
  void AddSurfaces(std::vector<int> surface_ids);
  int GetId();
  int Sense(Surface *surface);
  std::vector<Surface*> GetSurfaces();
  void PrintFluka(std::ofstream &output);
  void Print();
  
private:
  bool PointInVolume(double x, double y, double z);
  void ConnectSurfaces();

private:
  int volId;
  double density;
  int materialNumber;
  double x,y,z;
  std::vector<Surface*> boundingSurfaces;
  std::string name;
};

#endif
