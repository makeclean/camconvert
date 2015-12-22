#include "readfile.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

// read the file completly into a vector of strings;
ReadFile::ReadFile() {
  counter = 0;
}

// destructor
ReadFile::~ReadFile() {
}

void ReadFile::LoadFile(std::string filename) {
  // get the filestream
  std::ifstream file(filename.c_str());

  std::string line;
  // read all lines into vector of strings
  while(std::getline(file,line)) {
    lines.push_back(line);
  }
}

void ReadFile::ProcessContents() {
  // should be read title
  ReadTitle();
  counter++;
  // read all the surfaces
  int surfaceIntRead = 0;
  std::cout << "Reading surfaces ..." << std::endl;
  while(surfaceIntRead < maxSurfId ) {
    surfaceIntRead = ReadSurface();
    counter++;
  }
  // incerment the counter
  counter++;
  // read all the volumes
  std::cout << "Reading volumes ..." << std::endl;
  int volIntRead = 0;
  while(volIntRead < maxVolId ) {
    volIntRead = ReadVolume();
    counter++;
  }
  // all done
}

// find deal with fortran fixed with floats,
// turns string, like 5.0E-5-2.3E-5 into 5.0E-5 -2.3E-5
std::string ReadFile::FixedWidthSpacer(std::string line) {
  std::string new_line = line;
  // loo over the numbers we want to replace
  for ( int i = 1 ;  i <= 9 ; i++ ) {
    std::string finder = "-"+std::to_string(i)+".";
    //  std::string finder = std::to_string(i)+"-";
    std::string replacer = " "+finder; //::to_string(i)+" -";
    std::string::size_type n = 0;
    while ( ( n = new_line.find( finder, n ) ) != std::string::npos ) {
      new_line.replace( n, finder.size(), replacer );
      n += replacer.size();
    }
  }

  // loop over letters to deal with the case where we have "-1NAME"
  // loo over the numbers we want to replace
  for ( int j = 0 ; j < 2 ; j++ ) {
    for ( int i = 65 ; i <= 90 ; i++ ) {
      char letter[1] = {char(i)};
      std::string finder(std::string("-"+std::to_string(j))+std::string(letter));
      std::string replacer = " "+finder;
      std::string::size_type n = 0;
      while ( ( n = new_line.find( finder, n ) ) != std::string::npos ) {
	new_line.replace( n, finder.size(), replacer );
	n += replacer.size();
      }
    }
  }

  return new_line;
}

// Process the string remove all spaces except 
std::string ReadFile::DeSpaceify(std::string line) {
  std::string new_line = line;
  // while we find double string, replace "  " with " "
  while ( new_line.find("  ") != std::string::npos) { 
    // replace all instances of "  " with " "
    new_line.replace(new_line.find("  "),2," ");
  }
  // remove the leading space
  new_line.erase(0,new_line.find_first_not_of(" "));
  return new_line;
}

// Tokenize the string into a number of sub strings
std::vector<std::string> ReadFile::Tokenize(std::string line) {
  std::stringstream ss(line);
  std::vector<std::string> tokens;
  std::string token;
  while(std::getline(ss,token,' ')) {
    tokens.push_back(token);
  }
  return tokens;
}

// convert string to int
int ReadFile::ToInt(std::string token) {
  return std::stoi(token);
}

// convert string to double
double ReadFile::ToDouble(std::string token) {
  return std::stod(token);
}

// read the title card and advance io appropriately
void ReadFile::ReadTitle() {
  // get the title cards
  std::vector<std::string> tokens = Tokenize(DeSpaceify(lines[0]));

  // maximum vol integer id
  maxVolId = ToInt(tokens[0]);
  // maximum surface integer id
  maxSurfId = ToInt(tokens[1]);

}

// read a surface description in its entirity
int ReadFile::ReadSurface() { 
  std::vector<std::string> tokens;
  
  // tokenize the current line
  tokens = Tokenize(DeSpaceify(FixedWidthSpacer(lines[counter])));

  // make a new surface
  Surface* new_surface;

  Surface::coefficients surface_coeffs = {};

  // assume that we first read the first line of 
  int surfid = ToInt(tokens[0]); // get the surface id
  int num_entries = ToInt(tokens[1]); // get the number of parameters

  // loop over the tokens, advancing the array as nessessary
  while (true) {
    surface_coeffs.a0 = ToDouble(tokens[2]);
    surface_coeffs.a1 = ToDouble(tokens[3]);
    surface_coeffs.a2 = ToDouble(tokens[4]);
    surface_coeffs.a3 = ToDouble(tokens[5]);
    if(num_entries <= 4) break;
    counter++;
    tokens = Tokenize(DeSpaceify(FixedWidthSpacer(lines[counter])));
    surface_coeffs.a4 = ToDouble(tokens[0]);
    surface_coeffs.a5 = ToDouble(tokens[1]);
    surface_coeffs.a6 = ToDouble(tokens[2]);
    surface_coeffs.a7 = ToDouble(tokens[3]);
    // this should be 8, but the format specification is pretty weak
    if(num_entries <= 7) break;
    counter++;
    tokens = Tokenize(DeSpaceify(FixedWidthSpacer(lines[counter])));
    surface_coeffs.a8 = ToDouble(tokens[0]);
    surface_coeffs.a9 = ToDouble(tokens[1]);
    break;
  }
  // make new surface
  new_surface = new Surface(surface_coeffs,surfid);
  
  // add the new surface to the manager
  SurfaceManager::Instance()->AddSurface(new_surface);

  return surfid;
}

// reads a fortran formatted string volume 
std::vector<std::string> ReadFile::ReadVolumeLine(std::string line) {
  std::vector<std::string> split_lines;
  // we are all done reading volumes
  if(line.length() == 0 ) return split_lines;

  std::string vol_id = line.substr(0,4);
  split_lines.push_back(vol_id);
  std::string mat_num = line.substr(7,3);
  split_lines.push_back(mat_num);
  std::string density = line.substr(10,9);
  split_lines.push_back(density);
  std::string x = line.substr(18,9);  
  split_lines.push_back(x);
  std::string y = line.substr(27,9);
  split_lines.push_back(y);
  std::string z = line.substr(36,9);
  split_lines.push_back(z);
  std::string s1 = line.substr(48,4);
  split_lines.push_back(s1);
  std::string s2 = line.substr(52,4);
  split_lines.push_back(s2);
  std::string s3 = line.substr(56,4);
  split_lines.push_back(s3);
  std::string s4 = line.substr(60,4);
  split_lines.push_back(s4);
  std::string s5 = line.substr(64,4);
  split_lines.push_back(s5);
  std::string s6 = line.substr(68,4);
  split_lines.push_back(s6);
  std::string name = line.substr(72,8);
  split_lines.push_back(name);

  return split_lines;
}

// for reading a continue line of a volume, in the format 18I4
std::vector<std::string> ReadFile::ReadVolumeContinueLine(std::string line) {
  std::vector<std::string> split_lines;
  std::string element;
  // these are all just surface numbers
  if(line.size() == 80 ) {
    for ( int i = 0 ; i < 18 ; i++ ) {
      // 0, 4, 8, 12, 16
      try {
	element = line.substr(i*4,4);
      } catch (std::out_of_range& exception) {
	element = "    ";
      }
      if(element != "    ")  // dont push back blanks
	split_lines.push_back(element);
    }
  } else {
    std::cout << "Line does not conform to format" << std::endl;
    std::cout << line << std::endl;
    std::cout << "Trying to fit a continue statement" << std::endl;
    // try to fit it intto 
    for ( int i = 0 ; i < line.length()/4 ; i++ ) {
      element = line.substr(i*4,4);
      if(element != "    ")  // dont push back blanks
	split_lines.push_back(element);
    }
  }
  
  return split_lines;
}

// read a volume description in its entireity
int ReadFile::ReadVolume() { 
  std::vector<std::string> tokens;
  // tokenize the current line
  tokens = ReadVolumeLine(lines[counter]);
  //  tokens = Tokenize(DeSpaceify(FixedWidthSpacer(lines[counter])));

  // we could be all done with reading volumes
  if(tokens.size() == 0) return maxVolId;

  // volume id
  int volume_id = ToInt(tokens[0]);
  int material_number = ToInt(tokens[1]);
  double density = ToDouble(tokens[2]);
  double x = ToDouble(tokens[3]);
  double y = ToDouble(tokens[4]);
  double z = ToDouble(tokens[5]);

  std::vector<int> surface_numbers;
  // loop over the surface numbers and push them back
  for ( int i = 6 ; i < 11 ; i++ ) {
    if(ToInt(tokens[i]) > 0 )
      surface_numbers.push_back(ToInt(tokens[i]));
    else
      break;
  }

   // add the cell name
  std::string cell_name = tokens[12]; 

  // indicates a continue line
  if(ToInt(tokens[11]) == -1) {
    counter++;
    // advance the counter
    tokens = ReadVolumeContinueLine(lines[counter]);
    for ( int i = 0 ; i < tokens.size()-1 ; i++ ) {
      if(ToInt(tokens[i]) > 0 ) {
	surface_numbers.push_back(ToInt(tokens[i]));
      } else {
	break;
      }     
    }
  } else { // its a valid surface number
    surface_numbers.push_back(ToInt(tokens[11]));
  }

  // it may be the case there there are more surfaces to read on another line
  
  
  // the next line might have more surfaces to add 
  Volume *new_volume;

  std::vector<Surface*> surfaces;
  Surface *surface;
  // loop over the surfaces needed, make sure they exist then append
  for ( int i = 0 ; i < surface_numbers.size() ; i++ ) {
    // dont add surfaces with id = 0
    if(surface_numbers[i] == 0 ) continue;
    surface = SurfaceManager::Instance()->GetSurface(surface_numbers[i]);
    if(surface == NULL) {
      std::cout << "Surface " << surface_numbers[i] << " does not exist in the problem" << std::endl;
      std::cout << "FATAL ERROR" << std::endl;
    } else {
      surfaces.push_back(surface);
    }
  }

  // construct a new volume
  new_volume = new Volume(volume_id, density, material_number, surfaces, x,y,z, cell_name);

  // add the new surface to the manager
  VolumeManager::Instance()->AddVolume(new_volume);

  
  return volume_id;
}
