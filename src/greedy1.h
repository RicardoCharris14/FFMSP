#ifndef GREEDY1_H
#define GREEDY1_H

#include <string>
#include <vector>
#include <utility>

std::string greedy1(std::vector<std::string> chains, double t, double a = 1);
std::string grasp1(std::vector<std::string> chains, int time, double t, double a = 1);
std::pair<std::string, double> localSearch(std::vector<std::string> chains, double t, std::string solution, double time = 0);
std::string soloBusquedaLocal(std::vector<std::string> chains, double t, double a, int time);

#endif