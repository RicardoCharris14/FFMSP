#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "greedy2.h"
#include "control_functions.h"


std::string greedy2(std::vector<std::string> chains, const int change_degree, const float determinism = 1){

    std::string solution;
    std::string sub_chain;
    int chain_size = chains.front().size() ;
    int num_chains = chains.size();
    int index, j, sub_chain_size;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 100);

    for (int i=0 ; i<num_chains ; i++){
        index = (i*change_degree) % chain_size;
        if(index > chain_size-change_degree){

            sub_chain = chains[i].substr(index, chain_size - index);
            sub_chain_size = sub_chain.size();
            for (int i=0; i < sub_chain_size; i++){
                j = 0;
                while(sub_chain[i]!=alphabet[j]){
                    j++;
                    if(j == 4){
                        break;
                    }
                }

                // Elije un caracter aleatorio según el grado de determinismo
                if (distribution(gen) > 100*determinism){
                    sub_chain[i] = alphabet[distribution(gen)%4];
                }else{
                    sub_chain[i] = alphabet[(j+2)%4];
                }
                
            }
            solution.replace(index, chain_size - index, sub_chain);
            sub_chain = chains[i].substr(0, change_degree - (chain_size - index));
            sub_chain_size = sub_chain.size();
            for (int i=0; i < sub_chain_size; i++){
                j = 0;
                while(sub_chain[i]!=alphabet[j]){
                    j++;
                }

                // Elije un caracter aleatorio según el grado de determinismo
                if (distribution(gen) > 100*determinism){
                    sub_chain[i] = alphabet[distribution(gen)%4];
                }else{
                    sub_chain[i] = alphabet[(j+2)%4];
                }
                
            }
            solution.replace(0, change_degree - (chain_size - index), sub_chain);

        }else{

            sub_chain = chains[i].substr(index, change_degree);
            sub_chain_size = sub_chain.size();
            for (int i=0; i < sub_chain_size; i++){
                j = 0;
                while(sub_chain[i]!=alphabet[j]){
                    j++;
                }
                
                // Elije un caracter aleatorio según el grado de determinismo
                if (distribution(gen) > 100*determinism){
                    sub_chain[i] = alphabet[distribution(gen)%4];
                }else{
                    sub_chain[i] = alphabet[(j+2)%4];
                }
                
            }
            solution.replace((i*change_degree) % chain_size, change_degree, sub_chain);

        }
    }

    return solution;
}

std::string grasp2(std::vector<std::string> chains, int time, double t, double a) {
    std::pair<std::string, double> solutionTime;
    std::string bestSolution = "";
    std::string posibleSolution;
    int bestResult = 0, posibleResult; 
    double bestResultTime, posibleTime;
    int count = 0;
    auto start = std::chrono::steady_clock::now();
    
    // Calcula solucion con greedy1 determinista
    bestSolution = greedy2(chains, t);
    bestResult = checkSolution(chains, bestSolution, t);

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - start;
    bestResultTime = elapsed_seconds.count();
    std::cout << bestResult << " " << bestResultTime << std::endl;

    // Hace busqueda local sobre la solucion determinista encontrada con greedy1
    solutionTime = localSearch2(chains, t, bestSolution, bestResultTime);
    posibleSolution = solutionTime.first;
    posibleResult = checkSolution(chains, posibleSolution, t);

    posibleTime = solutionTime.second;

    while (true) {
        std::string auxSol;
        int auxRes = 0;
        auxSol = greedy2(chains, t, a);
        auxRes = checkSolution(chains, auxSol, t);
        if (auxRes > bestResult){

            bestSolution = auxSol;
            bestResult = auxRes;

            now = std::chrono::steady_clock::now();
            elapsed_seconds = now - start;
            bestResultTime = elapsed_seconds.count();
            std::cout << bestResult << " " << bestResultTime << std::endl;

            solutionTime = localSearch2(chains, t, bestSolution, bestResultTime);
            auxSol = solutionTime.first;
            auxRes = checkSolution(chains, auxSol, t);

            if(auxRes > posibleResult){

                posibleTime = solutionTime.second;

                posibleSolution = auxSol;
                posibleResult = auxRes;
            }
        }
        count++;
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        if (elapsed_seconds.count() >= time) {
            if(posibleResult > bestResult){
                bestResult = posibleResult;
                bestSolution = posibleSolution;
                bestResultTime = posibleTime;
            }
            std::cout << bestResult << " " << bestResultTime << std::endl;
            break;
        }
    }

    return bestSolution;
}

std::pair<std::string, double> localSearch2(std::vector<std::string> chains, double t, std::string string, double time) {
    auto start = std::chrono::steady_clock::now();
    std::pair<std::string, double> retorno;
    double solTime;
    int size = string.size();
    std::string auxSol;
    std::string bestSolution = string;
    int bestResult = checkSolution(chains, bestSolution, t);

    for(int i = 0; i < size; i++){
        auxSol = bestSolution;
        for(char a: alphabet){
            auxSol[i] = a;
            int auxRes = checkSolution(chains, auxSol, t);
            if(auxRes > bestResult){

                auto now = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds = now - start;
                solTime = elapsed_seconds.count() + time;
                bestResult = auxRes;
                bestSolution = auxSol;
                std::cout << bestResult << " " << solTime << std::endl;
                break;
            }
        }
    }

    retorno.first = bestSolution;
    retorno.second = solTime;
    return retorno;
}

std::string soloBusquedaLocal2(std::vector<std::string> chains, double t, double a, int time) {
    
    auto start = std::chrono::steady_clock::now();
    
    std::string solution = greedy2(chains, t);
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