#include "ant_algorithm.h"
#include <random>
#include "control_functions.h"

int ACO(std::vector<std::string> chains, int antsNumber){
    std::vector<std::string> antsSolutions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int solutionSize = antsSolutions[0].size();
    for (int i=0 ; i<antsNumber ; i++){
        std::string solution = "";
        for (int i=0 ; i<solutionSize ; i++){
            solution += alphabet[dis(gen)];
        }
        antsSolutions.push_back(solution);
    }


}