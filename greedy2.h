#ifndef GREEDY2_H
#define GREEDY2_H

#include <string>
#include <vector>

std::string greedy2(std::vector<std::string>, const int, const float);
std::string grasp2(std::vector<std::string> chains, const int change_degree, const double t, const double a, const int time);
std::pair<std::string, double> localSearch2(std::vector<std::string> chains, double t, std::string string, double time);
std::string soloBusquedaLocal2(std::vector<std::string> chains, double t, double a, int time);

#endif 