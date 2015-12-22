#include "csgwriter.hpp"
#include "volume_manager.hpp"
#include "surface_manager.hpp"
#include <list>
#include <iostream>

MakeCSG::MakeCSG() {
  std::cout << "*...+....1....+....2....+....3....+....4....+....5....+....6....+....7....+...." << std::endl;
  std::cout << "DEFAULTS                                                              PRECISIO  " << std::endl;
  std::cout << "GEOBEGIN                                                              COMBNAME  " << std::endl;
  std::cout << "      0    0          " << std::endl;
}

MakeCSG::~MakeCSG() {
}

// write the volumes 
void MakeCSG::WriteVolumes() {
  // get the list of volumes
  std::list<int> volume_list = VolumeManager::Instance()->GetVolumeList();
  // loop over the volume ids
  std::list<int>::iterator it;
  for ( it = volume_list.begin()  ; it != volume_list.end() ; ++it ) {
    // get the volume
    Volume *vol = VolumeManager::Instance()->GetVolume(*it);
    vol->PrintFluka();
  }
  std::cout << "GEOEND" << std::endl;
}

// write out all the surface descriptions
void MakeCSG::WriteSurfaces() {
  // Get the list of surfaces
  std::list<int> surface_list = SurfaceManager::Instance()->GetSurfaceList();
  // loop over the list
  std::list<int> :: iterator it;
  // loop over the surface list
  for ( it = surface_list.begin() ; it != surface_list.end() ; ++it ) {
    // get the surface
    Surface *surf = SurfaceManager::Instance()->GetSurface(*it);
    surf->PrintFluka();
  }
  std::cout << "END" << std::endl;
}
