#include "../headers/main.hpp"

void matrix_product(double input[180],double output[10],double M[10][180],double biases[10])
{
    for(unsigned int i=0;i<10;i++)
    {
        for(unsigned int j=0;j<180;j++)
        {
            output[i]=output[i]+M[i][j]*input[j];
        }
        output[i]+=biases[i];
    }
}
