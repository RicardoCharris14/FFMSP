#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <algorithm>
#include <chrono>
#include "greedy1.h"
#include "control_functions.h"

// Función para inicializar la población
std::vector<std::string> iniciarPoblacion(const std::vector<std::string> chains, double t, double a, int populationSize) {
    std::vector<std::string> poblacion;
    for (int i = 0; i < populationSize; i++) {
        poblacion.push_back(greedy1(chains, t, a));
    }
    return poblacion;
}

// Selección
std::string torneo(const std::vector<std::string> poblacion, const std::vector<int> fitnesses, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, poblacion.size() - 1);

    std::string best = poblacion[dis(gen)];
    int bestFitness = fitnesses[0];

    for (int i = 1; i < size; i++) {
        int index = dis(gen);
        if (fitnesses[index] > bestFitness) {
            best = poblacion[index];
            bestFitness = fitnesses[index];
        }
    }
    return best;
}

// Operadores genéticos
std::string crossover(const std::string& parent1, const std::string& parent2) {
    std::string child = parent1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, parent1.size() - 1);
    int crossoverPoint = dis(gen);

    for (int i = crossoverPoint; i < parent1.size(); i++) {
        child[i] = parent2[i];
    }
    return child;
}

void mutar(std::string& solution) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, solution.size() - 1);
    int mutationPoint = dis(gen);

    solution[mutationPoint] = alphabet[dis(gen) % 4];
}

// Algoritmo genético
std::string AlgoritmoEvolutivo(std::vector<std::string> chains, int tiempoMaximo, double threshold, double determinismo, int populationSize, bool tuning) {
    int tournamentSize = 5;
    double mutationRate = 0.1;

    std::vector<std::string> population = iniciarPoblacion(chains, threshold, determinismo, populationSize);
    std::vector<int> fitnesses(populationSize);

    auto start = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    int bestFitness = -1;
    std::string bestSolution;
    double bestTime = 0;

    while(true) {
        for (int i = 0; i < populationSize; i++) {
            fitnesses[i] = checkSolution(chains, population[i],  threshold);
        }
        
        // Se busca el mejor individuo 
        int maxIndex = std::distance(fitnesses.begin(), std::max_element(fitnesses.begin(), fitnesses.end()));
        if (fitnesses[maxIndex] > bestFitness) {
            bestFitness = fitnesses[maxIndex];
            bestSolution = population[maxIndex];
            auto now = std::chrono::steady_clock::now();
            elapsed_seconds = now - start;
            bestTime = elapsed_seconds.count();
            // Mostrar mejora de solución
            if(!tuning)
                std::cout << bestFitness << " " << bestTime << std::endl;
        }

        std::vector<std::string> newPopulation;

        for (int i = 0; i < populationSize; i++) {
            std::string parent1 = torneo(population, fitnesses, tournamentSize);
            std::string parent2 = torneo(population, fitnesses, tournamentSize);
            std::string child = crossover(parent1, parent2);

            if ((double)rand() / RAND_MAX < mutationRate) {
                mutar(child);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;
        auto now = std::chrono::steady_clock::now();        
        elapsed_seconds = now - start;
        if (elapsed_seconds.count() >= tiempoMaximo) {
            std::cout << bestFitness << " " << bestTime << std::endl;
            break;
        }
    }

    // Encontrar mejor solución final
    return bestSolution;
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

int main(int argc, char const *argv[])
{
    if (argc < 7) {
        std::cerr << "Uso incorrecto: " << argv[0] << " -i <instancia-problema> -t <t max en seg> -th <threshold>" << std::endl;
        return 1;
    }

    std::string filename;
    double threshold;
    double alpha = 1;
    int time = 10;
    int psize;
    bool tuning = false;
    // Iterar sobre los argumentos de la línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            filename = argv[++i]; // Captura la instancia del problema
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            time = atoi(argv[++i]); // Captura el valor del threshold
        } else if (strcmp(argv[i], "-th") == 0 && i + 1 < argc) {
            threshold = atof(argv[++i]); // Captura el valor de alpha
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc){
            alpha = atof(argv[++i]);
        } else if (strcmp(argv[i], "-psize") == 0 && i + 1 < argc){
            psize = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-tuning") == 0) {
            tuning = true;
        } else {
            std::cerr << "Argumento desconocido: " << argv[i] << std::endl;
            return 1;
        }
    }

    std::vector<std::string> chains = getDnaS(filename);
    std::string solution = AlgoritmoEvolutivo(chains, time, threshold, alpha, psize, tuning);
    return 0;
}
