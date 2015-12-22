#include "surface_manager.hpp"
#include "surface.hpp"
#include "volume_manager.hpp"
#include "volume.hpp"

#include <string>
#include <vector>

#ifndef READFILE_HPP
#define READFILE_HPP 1

class ReadFile {
public:
  ReadFile();
  ~ReadFile();
  void ProcessContents();
  void LoadFile(std::string filename);
private:
  std::vector<std::string> Tokenize(std::string line);
  std::string DeSpaceify(std::string line);
  std::string FixedWidthSpacer(std::string line);
  int ToInt(std::string token);
  double ToDouble(std::string token);
  void ReadTitle();
  int ReadSurface();
  int ReadVolume();
  // read the first part of a volume statement
  std::vector<std::string> ReadVolumeLine(std::string line);
  std::vector<std::string> ReadVolumeContinueLine(std::string line);
  // read the first part of the surface line statement
  std::vector<std::string> ReadSurfaceLine(std::string line);
  std::vector<std::string> ReadSurfaceContinueLine(std::string line);

private:
  int counter;
  std::vector<std::string> lines;
  int maxVolId;
  int maxSurfId;
};

#endif
