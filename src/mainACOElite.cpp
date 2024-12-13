#include <iostream>
#include <cstring>
#include "acoElite.h"
#include "control_functions.h"

int main(int argc, char* argv[]){
    if(argc < 13){
        std::cerr << "Uso incorrecto: " << argv[0] << " -i <ruta instancia> -t <tiempo> -th <threshold> -ant <cantidad de hormigas> -e <factor de evaporacion ]0,1[> -a <determinismo>" << std::endl;
        exit(1);
    }

    std::vector<std::string> chains;
    std::string filename;
    int antsNumber = 20;
    float evaporation = 0.1;
    int time = 10;
    float threshold = 0.75;
    bool tuning = false;
    double determinism = 0.9;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            filename = argv[++i]; 
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            time = atoi(argv[++i]); 
        } else if (strcmp(argv[i], "-th") == 0 && i + 1 < argc) {
            threshold = atof(argv[++i]); 
        } else if (strcmp(argv[i], "-ant") == 0 && i + 1 < argc){
            antsNumber = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc){
            determinism = atof(argv[++i]);
        } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc){
            evaporation = atof(argv[++i]);
        } else if(strcmp(argv[i], "-tuning") == 0 && i + 1 < argc){
            if(strcmp(argv[i+1], "1") == 0){
                tuning = true;
            }
        } else {
            std::cerr << "Argumento desconocido: " << argv[i] << std::endl;
            exit(1);
        }
    }

    chains = getDnaS(filename);
    std::string bestQuality = ACOElite(chains, antsNumber, evaporation, determinism, time, threshold, tuning);
    return 0;
}