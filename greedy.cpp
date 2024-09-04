#include <iostream>
#include <fstream>
#include <queue>

const std::string alphabet = "ACGT";

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

std::string heuristic(std::queue<std::string> chains, const int chain_size, const int change_degree){

    std::string solution;
    std::string sub_chain;
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

int checkSolution(std::queue<std::string> chains, std::string solution, const int chain_size, const float t){
    
}

int main(){
    std::string filename = "../FFMS_all_instances/100-300-001.txt";
    std::queue<std::string> chains = getDnaS(filename);
    std::string solution;
    solution = heuristic(chains, 300, 40);
    std::cout << solution << std::endl;

    return 0;
}