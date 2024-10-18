#ifndef GREEDY1_H
#define GREEDY1_H

#include <string>
#include <vector>

std::string greedy1(std::vector<std::string> chains, double t, double a);
std::string grasp1(std::vector<std::string> chains, double t, double a, int time);
std::string localSearch(std::vector<std::string> chains, double t, double a, int time);
std::string soloBusquedaLocal(std::vector<std::string> chains, double t, double a, int time);

#endif