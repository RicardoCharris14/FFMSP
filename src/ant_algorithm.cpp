#include "ant_algorithm.h"
#include <random>
#include "control_functions.h"

int ACO(std::vector<std::string> chains, int antsNumber, int time){
    const int SUMA = 4;
    std::vector<std::string> antsSolutions;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int solutionSize = antsSolutions[0].size();
    float pheromones[solutionSize][5];

    // Inicializa los valores de las feromonas
    for(int i=0 ; i<solutionSize ; i++){
        for (int j=0 ; j<4 ; j++){
            pheromones[i][j] = 100;
        }
        pheromones[i][SUMA] = 400;
    }

    
    while (true){
        // Crea soluciones en base a las feromonas
        for (int i=0 ; i<antsNumber ; i++){
            std::string solution = "";
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
            antsSolutions.push_back(solution);
        }

        //modifica las feromonas para cada opcion
        
    }
}