#include "greedy1.h"
#include "control_functions.h"
#include <random>
#include <iostream>
#include <chrono>

std::string greedy1(std::vector<std::string> chains, double t, double a = 1){
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

std::string localSearch(std::vector<std::string> chains, double t, std::string string);
std::string grasp1(std::vector<std::string> chains, double t, double a, int time) {
    std::string bestSolution = "";
    int bestResult = 0; 
    double bestResultTime;
    int count = 0;
    auto start = std::chrono::steady_clock::now();
    
    bestSolution = greedy1(chains, t);
    bestResult = checkSolution(chains, bestSolution, t);
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - start;
    bestResultTime = elapsed_seconds.count();

    while (true) {
        std::string auxSol;
        int auxRes = 0;
        auxSol = greedy1(chains, t, a);
        auxRes = checkSolution(chains, auxSol, t);
        if (auxRes > bestResult){
            bestSolution = auxSol;
            bestResult = auxRes;
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = now - start;
            bestResultTime = elapsed_seconds.count();
            std::cout << bestResult << " " << bestResultTime << std::endl;
            bestSolution = localSearch(chains, t, bestSolution);
            bestResult = checkSolution(chains, bestSolution, t);
        }
        count++;
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        if (elapsed_seconds.count() >= time) {
            std::cout << checkSolution(chains, bestSolution, t) << " " << bestResultTime << std::endl;
            std::cout << "Se revisaron " << count << " soluciones" << std::endl;
            break;
        }
    }

    return bestSolution;
}

std::string localSearch(std::vector<std::string> chains, double t, std::string string) {
    int size = string.size();
    std::string aux = string;
    std::string result = string;
    int bestResult = checkSolution(chains, result, t);

    auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - start;
    double bestResultTime = elapsed_seconds.count();

    for(int i = 0; i < size; i++){
        for(char a: alphabet){
            aux[i] = a;
            int auxSol = checkSolution(chains, aux, t);
            if(auxSol > bestResult){
                bestResult = auxSol;
                result = aux;
                
                auto now = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = now - start;
                bestResultTime = elapsed_seconds.count();
                
                std::cout << bestResult << " " << bestResultTime << std::endl;
                break;
            }
        }
    }
    return result;
}

std::string soloBusquedaLocal(std::vector<std::string> chains, double t, double a, int time) {
    
    auto start = std::chrono::steady_clock::now();
    
    std::string solution = greedy1(chains, t);
    std::string aux = solution;
    int bestResult = checkSolution(chains, solution, t);
    
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - start;
    double bestResultTime = elapsed_seconds.count();
    
    //std::cout << bestResult << " " << bestResultTime << std::endl;

    int strSize = solution.size();
    while(true){
        for(int i = 0; i < strSize; i++){
            for(char a: alphabet){
                auto now = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = now - start;
                if (elapsed_seconds.count() >= time) {
                    std::cout << checkSolution(chains, solution, t) << " " << bestResultTime << std::endl;
                    return solution;
                }
                
                aux[i] = a;
                int auxRes = checkSolution(chains, aux, t);
                if(auxRes > bestResult){
                    auto now = std::chrono::steady_clock::now();
                    std::chrono::duration<double> elapsed_seconds = now - start;
                    bestResultTime = elapsed_seconds.count();
                    
                    bestResult = auxRes;
                    solution = aux;
                    

                    //std::cout << bestResult << " " << bestResultTime << std::endl;
                    break;
                }
            }
        }
        
    }
    return solution;
}