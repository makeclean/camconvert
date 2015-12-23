#include <fstream>
#include <string>

class MakeCSG {
public:
  MakeCSG(std::string filename);
  ~MakeCSG();
public:
  void WriteVolumes();
  void WriteSurfaces();
private:
  std::ofstream output;
};
