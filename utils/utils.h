#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include <stdexcept>

std::string getInputPath(int argc, char** argv, 
                         const std::string& default_file);
std::ifstream openFile(const std::string& filename);

#endif