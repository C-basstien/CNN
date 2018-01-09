#include "../headers/main.hpp"
void relu(double inout[MAX_IM])
{
    for (unsigned int i = 0; i <MAX_IM;i++)
    {
        if(inout[i]<0){inout[i]=0;}
    }
}
