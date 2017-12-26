#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>
#include "Write_file.hpp"
using namespace std;



#define LIGNE_OUT 24
#define COLONNE_OUT 24

void write_img(double img_out[LIGNE_OUT][COLONNE_OUT])
{
    std::ofstream outFlux("File_image.txt");

    //outFlux<<LIGNE_OUT<<endl;
    //outFlux<<COLONNE_OUT<<endl;

    for(int i=0;i<LIGNE_OUT;i++)
    {
        for(int j=0;j<COLONNE_OUT;j++)
        {
            outFlux<<img_out[i][j]<<endl;
        }
    }

}
