#include <iostream>
#include <fstream>
#include <queue>

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


int main(){
    std::string filename = "../Problema FFMS/FFMS_all_instances/100-300-001.txt";
    std::queue chains = getDnaS(filename);
    int num_chains = chains.size();
    for(int i=0 ; i < num_chains ; i++){

        std::cout << chains.front() << std::endl;
        chains.pop();

    }

    return 0;
}