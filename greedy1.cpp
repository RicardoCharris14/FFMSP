#include "greedy1.h"
#include "control_functions.h"
#include <random>
#include <iostream>


std::string greedy1(std::vector<std::string> chains, double t, double a){
    int numChains = chains.size();
    int chainSize = chains.front().size();
    int ocurrences[4][chainSize] = {0};
    std::string solution = "";

    // LLena la matriz de ocurrencias
    for(int i = 0; i < numChains; i++){
        for(int j = 0; j < chainSize; j++){
            if(chains[i][j] == 'A'){
                ocurrences[0][j]++;
            }else if(chains[i][j] == 'C'){
                ocurrences[1][j]++;
            }else if(chains[i][j] == 'G'){
                ocurrences[2][j]++;
            }else if(chains[i][j] == 'T'){
                ocurrences[3][j]++;
            }else {
                std::cerr << "Error en la cadena" << std::endl;
                exit(1);
            }
        }
    }

    int threshold = t * chainSize;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int alpha = a * 100;

    // Forma la solucion con las ocurrencias minimas
    for(int i = 0; i < chainSize; i++){
        int min = ocurrences[0][i];
        int index = 0;
        int random = dis(gen);
        if(random <= alpha){
            for(int j = 1; j < 4; j++){
                if(ocurrences[j][i] < min){
                    min = ocurrences[j][i];
                    index = j;
                }
            }
            if (checkSolution(chains, solution + alphabet[index], t) >= checkSolution(chains, solution + alphabet[(index + 1) % 4], t)){
                solution += alphabet[index];
            } else {
                solution += alphabet[(index + 1) % 4];
            }
        }
        else {
            std::uniform_int_distribution<> random_dis(0, 3);
            solution += alphabet[random_dis(gen)];
        }
    }
    return solution;
}