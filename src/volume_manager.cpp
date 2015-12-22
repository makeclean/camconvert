#include "volume_manager.hpp"
#include <stddef.h>

VolumeManager* VolumeManager::pInstance = NULL;

VolumeManager::VolumeManager() {
}

VolumeManager::~VolumeManager() {
}

VolumeManager* VolumeManager::Instance() {
  if(!pInstance)
    pInstance = new VolumeManager();
  return pInstance;
}

// add a volume to the map
void VolumeManager::AddVolume(Volume *volume) {
  volumeMap[volume->GetId()] = volume;
  volumeList.push_back(volume->GetId());
}

// remove volume from list
void VolumeManager::RemoveVolume(Volume *volume) {
  std::map<int,Volume*>::iterator it; // map iterator
  it=volumeMap.find(volume->GetId()); //f ind the volume
  volumeMap.erase(it); // remove it from the map
}

// get the list of volumes
std::list<int> VolumeManager::GetVolumeList() {
  return volumeList;
}

// remove volume from list
Volume* VolumeManager::GetVolume(int vol_id) {
  // check to make sure volume exists
  if(volumeMap.count(vol_id) == 0 ) {
    return NULL;
  } else {
    // return the appropriate volume object
    return volumeMap[vol_id];
  }
}
