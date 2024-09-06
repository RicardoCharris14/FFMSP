#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <cstring>
#include <cstdlib>

const std::string alphabet = "ACGT";

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

std::vector<std::string> getDnaS(const std::string& filename){

    std::vector<std::string> dnaChains;
    std::string chain;
    
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);
    } else{

        while(std::getline(file, chain)){
            dnaChains.push_back(chain);
        }
        return dnaChains;

    }
}

std::string heuristic(std::vector<std::string> chains, const int change_degree){

    std::string solution;
    std::string sub_chain;
    int chain_size = chains.front().size() - 1;
    int num_chains = chains.size();
    int index, j, sub_chain_size;

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
                sub_chain[i] = alphabet[(j+2)%4];
            }
            solution.replace(index, chain_size - index, sub_chain);
            sub_chain = chains[i].substr(0, change_degree - (chain_size - index));
            sub_chain_size = sub_chain.size();
            for (int i=0; i < sub_chain_size; i++){
                j = 0;
                while(sub_chain[i]!=alphabet[j]){
                    j++;
                }
                sub_chain[i] = alphabet[(j+2)%4];
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
                sub_chain[i] = alphabet[(j+2)%4];
            }
            solution.replace((i*change_degree) % chain_size, change_degree, sub_chain);

        }
    }

    return solution;
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

std::string greedy(std::vector<std::string> chains, double t){
    int numChains = chains.size();
    int chainSize = chains.front().size() - 1;
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

    std::vector<int> diferencias;
    int threshold = t * chainSize;
    
    // Forma la solucion con las ocurrencias minimas
    for(int i = 0; i < chainSize; i++){
        int min = ocurrences[0][i];
        int index = 0;
        for(int j = 1; j < 4; j++){
            if(ocurrences[j][i] < min){
                min = ocurrences[j][i];
                index = j;
            }
        }
        solution += alphabet[index % 4];
        
        //if (checkSolution(chains, solution + alphabet[index], t) >= checkSolution(chains, solution + alphabet[(index + 2) % 4], t)){
        //    solution += alphabet[index];
        //} else {
        //    solution += alphabet[(index + 2) % 4];
        //}

        //for (int j = 0; j < numChains; j++){
        //    int dif = d(chains[j], solution);
        //    diferencias.push_back(dif);
        //    
        //    if(dif >= threshold){
        //        chains.erase(chains.cbegin() + j);
        //    }
        //    
        //    if(i >= chains.size()){
        //        break;
        //    }
        //}
    }
    return solution;
}

int main(int argc, char const *argv[]){

     // Verifica que el número de argumentos sea correcto
    if (argc != 5) {
        std::cerr << "Uso incorrecto: " << argv[0] << " -i <instancia-problema> -th <threshold>" << std::endl;
        return 1;
    }

    std::string filename;
    double threshold;
    // Iterar sobre los argumentos de la línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            filename = argv[++i]; // Captura la instancia del problema
        } else if (strcmp(argv[i], "-th") == 0 && i + 1 < argc) {
            threshold = atof(argv[++i]); // Captura el valor del threshold
        } else {
            std::cerr << "Argumento desconocido: " << argv[i] << std::endl;
            return 1;
        }
    }

    
    std::vector<std::string> chains = getDnaS(filename);

    auto start = std::chrono::high_resolution_clock::now();
    //std::string solution = heuristic(chains, 40);
    std::string solution = greedy(chains, threshold);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double elapsedTime = elapsed.count();

    std::cout << solution.length() << std::endl;
    std::cout << checkSolution(chains, solution, threshold) << " " << elapsedTime << std::endl;

    return 0;
}