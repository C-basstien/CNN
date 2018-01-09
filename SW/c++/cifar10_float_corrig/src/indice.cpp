#include "../headers/main.hpp"
unsigned int indice(unsigned int i,unsigned int j, unsigned int k, unsigned int size [3])
{
    return (size[1]*i+j)*size[2]+k;
}
unsigned int indice(unsigned int i,unsigned int j, unsigned int k,unsigned int l,unsigned int size [4])
{
    return ((size[1]*i+j)*size[2]+k)*size[3]+l;
}
