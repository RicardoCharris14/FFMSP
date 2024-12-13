#ifndef ANT_ALGORITHM_H
#define ANT_ALGORITHM_H
#include <vector>
#include <string>


std::string ACOElite(std::vector<std::string> chains, int antsNumber, float evaporation, double determinism, int time, float threshold, bool tuning = false);

#endif