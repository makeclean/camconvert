#include "surface.hpp"
#include <map>
#include <list>

#ifndef SURFACE_MANAGER_HPP
#define SURFACE_MANAGER_HPP 1

class SurfaceManager {
public:
  static SurfaceManager* Instance();
  void AddSurface(Surface *surface);
  void RemoveSurface(Surface *surface);
  Surface* GetSurface(int id);
  std::list<int> GetSurfaceList();
private:
  SurfaceManager();
  ~SurfaceManager();
  std::map<int,Surface*> surfaceMap;
  std::list<int> surfaceList;
  static SurfaceManager* pInstance;
};

#endif
