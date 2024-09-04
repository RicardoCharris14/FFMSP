#include <iostream>
#include <fstream>
#include <queue>
#include <chrono>

const std::string alphabet = "ACGT";

int d(std::string str1, std::string str2){
    int distance = 0, strSize = str1.size();
    for(int i=0; i<strSize; i++){
        if(str1[i] != str2[i]){
            distance++;
        }
    }
    return distance;
}

std::queue<std::string> getDnaS(const std::string& filename){

    std::queue<std::string> dnaChains;
    std::string chain;
    
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);
    } else{

        while(std::getline(file, chain)){
            dnaChains.push(chain);
        }
        return dnaChains;

    }
}

std::string heuristic(std::queue<std::string> chains, const int change_degree){

    std::string solution;
    std::string sub_chain;
    int chain_size = chains.front().size();
    int num_chains = chains.size();
    int index, j, sub_chain_size;
    for (int i=0 ; i<num_chains ; i++){
        index = (i*change_degree) % chain_size;
        if(index > chain_size-change_degree){

            sub_chain = chains.front().substr(index, chain_size - index);
            sub_chain_size = sub_chain.size();
            for (int i=0; i < sub_chain_size; i++){
                j = 0;
                while(sub_chain[i]!=alphabet[j]){
                    j++;
                }
                sub_chain[i] = alphabet[(j+2)%4];
            }
            solution.replace(index, chain_size - index, sub_chain);
            sub_chain = chains.front().substr(0, change_degree - (chain_size - index));
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

            sub_chain = chains.front().substr(index, change_degree);
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
        
        chains.pop();
    }

    return solution;
}

double checkSolution(std::queue<std::string> chains, std::string solution, const float t){
    int chainSize = chains.front().size();
    int numChains = chains.size();
    int threshold = t * chainSize;
    int count = 0;
    
    for(int i=0; i < numChains; i++){
        if(d(chains.front(), solution) >= threshold){
            count++;
        }
        chains.pop();
    }

    double quality = (double)count / (double)numChains; 
    return quality;
}

int main(){
    std::string filename = "../FFMS_all_instances/100-300-001.txt";
    std::queue<std::string> chains = getDnaS(filename);
    
    auto start = std::chrono::high_resolution_clock::now();
    std::string solution = heuristic(chains, 40);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double elapsedTime = elapsed.count();

    // std::cout << solution << std::endl;
    std::cout << checkSolution(chains, solution, 0.7) << " " << elapsedTime << std::endl;

    return 0;
}