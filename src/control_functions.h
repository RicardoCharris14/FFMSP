#ifndef CONTROL_FUNCTIONS_H
#define CONTROL_FUNCTIONS_H

#include <string>
#include <vector>

const std::string alphabet = "ACGT";

int d(std::string, std::string);
int checkSolution(std::vector<std::string>, std::string, const float);
std::vector<std::string> getDnaS(const std::string& filename);

#endif