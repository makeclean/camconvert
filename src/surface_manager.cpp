#include "surface_manager.hpp"
#include <stddef.h>

SurfaceManager* SurfaceManager::pInstance = NULL;

SurfaceManager::SurfaceManager() {
}

SurfaceManager::~SurfaceManager() {
}

SurfaceManager* SurfaceManager::Instance() {
  if(!pInstance)
    pInstance = new SurfaceManager();
  return pInstance;
}

// add a surface to the map
void SurfaceManager::AddSurface(Surface *surface) {
  surfaceMap[surface->GetId()] = surface;
  surfaceList.push_back(surface->GetId());
}

// remove surface from list
void SurfaceManager::RemoveSurface(Surface *surface) {
  std::map<int,Surface*>::iterator it; // map iterator
  it=surfaceMap.find(surface->GetId()); //f ind the surface
  surfaceMap.erase(it); // remove it from the map
}

std::list<int> SurfaceManager::GetSurfaceList() {
  return surfaceList;
}

// get the surface
Surface* SurfaceManager::GetSurface(int id) {
  Surface* new_surface;
  if(surfaceMap.count(id) == 0 ) {
    return NULL;
  } else {
    return surfaceMap[id];
  }   
}
