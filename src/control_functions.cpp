#include "control_functions.h"
#include <iostream>
#include <fstream>
#include <algorithm>

int d(std::string str1, std::string str2){
    int distance = 0;
    int strSize = str1.size() > str2.size() ? str2.size() : str1.size();
    for(int i=0; i<strSize; i++){
        if(str1[i] != str2[i]){
            distance++;
        }
    }
    return distance;
}

int checkSolution(std::vector<std::string> chains, std::string solution, const float t){
    int chainSize = chains.front().size();
    int numChains = chains.size();
    int threshold = t * chainSize;
    int count = 0;
    
    for(int i=0; i < numChains; i++){
        if(d(chains[i], solution) >= threshold){
            count++;
        }
    }

    //double quality = (double)count / (double)numChains; 
    //return quality;
    return count;
}

std::vector<std::string> getDnaS(const std::string& filename) {
    std::vector<std::string> dnaChains;
    std::string chain;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);
    }

    while (std::getline(file, chain)) {
        // Eliminar saltos de línea y otros espacios en blanco
        chain.erase(std::remove_if(chain.begin(), chain.end(), ::isspace), chain.end());
        if (!chain.empty()) {
            dnaChains.push_back(chain);
        }
    }

    return dnaChains;
}