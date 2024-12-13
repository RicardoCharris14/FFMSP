#include <chrono>
#include <random>
#include <iostream>
#include "control_functions.h"
#include "acoElite.h"
#include "greedy1.h"

std::string ACOElite(std::vector<std::string> chains, int antsNumber, float evaporation, double determinism, int time, 
                    float threshold, bool tuning){
    const int SUMA = 4;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int solutionSize = chains[0].size();
    std::string bestSolution;
    int bestQuality = 0;
    double bestTime = 0;
    int solQuality;
    int pheromones[solutionSize][5] = {0};

    auto start = std::chrono::high_resolution_clock::now();

    // Inicializa los valores de las feromonas
    for(int i=0 ; i<solutionSize ; i++){
        for (int j=0 ; j<4 ; j++){
            pheromones[i][j] = 200;
            pheromones[i][SUMA] += pheromones[i][j];
        }
    }

    //Inicializa el grupo de soluciones mediante greedy1
    std::string solution;
    for (int i=0 ; i<antsNumber ; i++){
        solution = greedy1(chains, threshold, determinism);
        solQuality = checkSolution(chains, solution, threshold);
        if (solQuality > bestQuality){
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsedTime = now - start;
            double actualTime = elapsedTime.count();
            bestQuality = solQuality;
            bestSolution = solution;
            bestTime = actualTime;
            if (!tuning){
                std::cout << bestTime << " " << bestQuality << std::endl;
            }
            
        }
    }
    
    while (true){
        //modifica las feromonas para cada opcion
        for (int i=0 ; i<solutionSize ; i++){
            int pheromonesSum = pheromones[i][4];
            pheromones[i][4] = 0;
            for(int j=0 ; j<4 ; j++){
                //Proceso de evaporación de feromonas
                pheromones[i][j] = evaporation * pheromones[i][j];
                //Incremento de feromonas según la mejor solución
                if(bestSolution[i] == 'A' && j==0){
                    pheromones[i][j] += (1 - evaporation) * bestQuality;
                }else if(bestSolution[i] == 'C' && j==1){
                    pheromones[i][j] += (1 - evaporation) * bestQuality;
                }else if(bestSolution[i] == 'G' && j==2){
                    pheromones[i][j] += (1 - evaporation) * bestQuality;
                }else if(bestSolution[i] == 'T' && j==3){
                    pheromones[i][j] += (1 - evaporation) * bestQuality;
                }
                
                pheromones[i][4] += pheromones[i][j];
            }
        }

        // Crea soluciones en base a las feromonas
        for (int i=0 ; i<antsNumber ; i++){
            solution = "";
            for (int j=0 ; j<solutionSize ; j++){
                float selection_number = pheromones[j][SUMA] * dis(gen)/100;
                std::string letter;
                if(selection_number <= pheromones[j][0]){
                    letter = "A";
                }else if(pheromones[j][0] < selection_number <= pheromones[j][0]+pheromones[j][1]){
                    letter = "C";
                }else if(pheromones[j][0]+pheromones[j][1] < selection_number <= pheromones[j][0]+pheromones[j][1]+pheromones[j][2]){
                    letter = "G";
                }else{
                    letter = "T";
                }
                solution += letter;
            }
            //Guarda la mejor solución
            solQuality = checkSolution(chains, solution, threshold);
            if (solQuality > bestQuality){
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = now - start;
                double actualTime = elapsedTime.count();
                bestQuality = solQuality;
                bestSolution = solution;
                bestTime = actualTime;
                if (!tuning){
                    std::cout << bestTime << " " << bestQuality << std::endl;
                }
                
            }
        }

        //Verifica si el tiempo se completo y retorna la solucion final
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = now - start;
        double actualTime = elapsedTime.count();
        if (actualTime >= time){
            std::cout << bestTime << " " << bestQuality << std::endl;
            return bestSolution;
        }
    }
}