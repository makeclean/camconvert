#include "volume.hpp"
#include <iostream>

// empty constructor
Volume::Volume(){
}

// destructor
Volume::~Volume(){
}

// instanciate new volume
Volume::Volume(int vol_id, double density, int material_number,
	       std::vector<Surface*> bounding_surfaces,
	       double x, double y, double z,
	       std::string name) {
  volId = vol_id;
  this->density = density;
  materialNumber = material_number;
  // this needs converting to surface pointers instead
  boundingSurfaces = bounding_surfaces;
  this->x = x;
  this->y = y;
  this->z = z;
  this->name = name;
}

// set the Id associated with the volume
int Volume::GetId() {
  return volId;
}

// set the density assigned to the volume
void Volume::SetDensity(double density) {
  this->density = density;
}

// add surfaces to the list of bounding surfaces
void Volume::AddSurfaces(std::vector<int> bounding_surfaces) {
}

// loop over the vector of surfaces and add them as pointers to the
// actual surfaces
void Volume::ConnectSurfaces() {
}

// determine if the point is insdide the volume
bool Volume::PointInVolume(double x, double y, double z) {
}

// evaluate the sense of the surface, of the volume relative to 
// the reference point
int Volume::Sense(Surface *surface) {
  return surface->Evaluate(x,y,z);
}

// get the surfaces that bound the volume
std::vector<Surface*> Volume::GetSurfaces() {
  return boundingSurfaces;
}

// print a simple text based description of the volume
void Volume::Print() {
}

// print the fluka description of the volume
void Volume::PrintFluka(std::ofstream &output) {
  output << name << "     5 "; 
  std::vector<Surface*> surfaces = GetSurfaces();
  Surface *surface;
  for ( int i = 0 ; i < surfaces.size() ; i++ ) {
    int eval = Sense(surfaces[i]);
    if( eval == 1 ) output << "-S"<<surfaces[i]->GetId() << " ";
    if( eval == -1 ) output << "+S"<<surfaces[i]->GetId() << " ";
  }
  output << std::endl;
}
