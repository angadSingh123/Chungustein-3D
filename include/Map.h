#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>

#define MAX_LENGTH 10

class Map
{
    public:

        Map(const char* location);
        virtual ~Map();
        void Display();
        void Print();
        int Initialise();
        int getRows();
        int getCols();
        int getGridLength();
        int getGridWidth();
        inline char getData(int x, int y) {return Grid[x*Cols + y];}


    private:

        int Rows;
        int Cols;
        char* Grid;
        char Location[MAX_LENGTH];
};

#endif // MAP_H
