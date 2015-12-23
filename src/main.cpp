#include <iostream>
#include "readfile.hpp"
#include "csgwriter.hpp"

int main(int argc, char* argv[]) {
  // class to handle file reading and problem setup
  ReadFile *file = new ReadFile();
  std::cout << "Loading file..." << std::endl;
  // load the data
  file->LoadFile("cam.dat");
  // process the data
  file->ProcessContents();
  
  // make class to handle making and writing the output
  MakeCSG *csg = new MakeCSG("output.inp");
  csg->WriteSurfaces();
  csg->WriteVolumes();
  
  return 0;
}
