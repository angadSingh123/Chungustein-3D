#include "Map.h"

Map::Map(const char* Location){
    strcpy(this->Location, Location);
}

Map::~Map(){
    std::cout << "Destroying Grid\n";

    delete[] Grid;
}

int Map::Initialise() {

    std::fstream file(this->Location);

    std::string place;

    if (!file.is_open()) {

        std::cout << "Error could not open file." << std::endl;

        return -1;

    }

    char buffer;

    std::getline(file, place);

    this->Rows = std::strtol(place.c_str(), NULL, 10);

    if (this->Rows == 0) {file.close(); return -1;}

    std::getline(file, place);

    this->Cols = std::strtol(place.c_str(), NULL, 10);

    if (this->Cols == 0) { file.close(); return -1;}

    int i = 0;

    Grid = new char[Rows*Cols];

    while(file >> buffer){

            (this->Grid[i]) = buffer;
            i++;

    }

    file.close();

    return 0;
}

void Map::Display(){

    for (int i = 0 ; i < Rows; i++){

        for (int j = 0 ; j < Cols; j++){

            std::cout << (char)(getData(i,j));


        }

        std::cout << std::endl;

    }


}

int Map::getRows(){
    return this->Rows;
}

int Map::getCols(){
    return this->Cols;
}


