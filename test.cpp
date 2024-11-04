#include "control_functions.h"
#include <random>
#include <iostream>
#include <chrono>

std::string greedy(std::vector<std::string> chains, double t, double a, double subStringGrade){
    int subStringSize = subStringGrade * chains[0].size();
    int limite = chains[0].size() / subStringSize;
    std::string solution = chains[1];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int alpha = a * 100;

    for (int i = 0; i < limite; i++) {
        int random = dis(gen);
        if (random <= alpha) {
            for(std::string chain: chains) { 
                std::string subSolution;
                subSolution = chain.substr(i * subStringSize, subStringSize);
                if(checkSolution(chains, subSolution, t) > checkSolution(chains, solution.substr(i * subStringSize, subStringSize), t)) {
                    solution.replace(i * subStringSize, subStringSize, subSolution);
                }
            }
        } else {
            std::uniform_int_distribution<> random_dis(0, 3);
            for (int j = 0; j < subStringSize; j++) {
                solution += alphabet[random_dis(gen)];
            }
        }

    }

    return solution;
}
