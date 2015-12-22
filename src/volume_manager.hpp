#include "volume.hpp"
#include <map>
#include <list>
class VolumeManager {
public:
  static VolumeManager* Instance();
  void AddVolume(Volume *volume);
  void RemoveVolume(Volume *volume);
  std::list<int> GetVolumeList();
  Volume* GetVolume(int vol_id);
private:
  VolumeManager();
  ~VolumeManager();
private:
  std::map<int,Volume*> volumeMap;
  std::list<int> volumeList;
  static VolumeManager* pInstance;
};
