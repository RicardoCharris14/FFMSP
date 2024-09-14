#include "control_functions.h"
#include <iostream>

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