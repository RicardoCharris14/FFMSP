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

std::string grasp2(std::vector<std::string> chains, int change_degree, double t, double a, int time){
    std::string bestSolution = "";
    int bestResult = 0; 
    int count = 0;
    auto start = std::chrono::steady_clock::now();
    
    while (true) {
        std::string auxSol;
        int auxRes = 0;
        auxSol = greedy2(chains, change_degree, a);
        auxRes = checkSolution(chains, auxSol, t);
        if (auxRes > bestResult){
            bestSolution = auxSol;
            bestResult = auxRes;
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = now - start;
            std::cout << auxRes << " " << elapsed_seconds.count() << std::endl;
        }
        count++;
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - start;
        if (elapsed_seconds.count() >= time) {
            std::cout << "Se revisaron " << count << " soluciones" << std::endl;
            break;
        }
    }
}