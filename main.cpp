#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <cstring>
#include <cstdlib>
#include <random>
#include <algorithm>  
#include <cctype>    
#include "control_functions.h"
#include "greedy1.h"
#include "greedy2.h"

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

int main(int argc, char const *argv[]){

     // Verifica que el número de argumentos sea correcto
    if (argc < 5) {
        std::cerr << "Uso incorrecto: " << argv[0] << " -i <instancia-problema> -th <threshold>" << std::endl;
        return 1;
    }

    std::string filename;
    double threshold;
    double alpha = 1;
    int time = 10;
    // Iterar sobre los argumentos de la línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            filename = argv[++i]; // Captura la instancia del problema
        } else if (strcmp(argv[i], "-th") == 0 && i + 1 < argc) {
            threshold = atof(argv[++i]); // Captura el valor del threshold
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            alpha = atof(argv[++i]); // Captura el valor de alpha
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc){
            time = atof(argv[++i]);
        } else {
            std::cerr << "Argumento desconocido: " << argv[i] << std::endl;
            return 1;
        }
    }

    std::vector<std::string> chains = getDnaS(filename);

    auto start = std::chrono::high_resolution_clock::now();
    std::string solution = grasp(chains, threshold, alpha, time);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double elapsedTime = elapsed.count();

    //std::cout << solution.length() << std::endl;
    //std::cout << checkSolution(chains, solution, threshold) << " " << elapsedTime << std::endl;

    return 0;
}