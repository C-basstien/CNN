#include "../headers/main.hpp"
/**temporary solution**/
void print_signal(double signal[MAX_IM],unsigned int sig_size[3])
{
    for (unsigned int i = 0; i <sig_size[0];i++)
    {
        for (unsigned int j = 0; j <sig_size[1];j++)
        {
            for (unsigned int k = 0; k <sig_size[2];k++)
            {
                printf("[%u][%u][%u]:%lf\n",i,j,k,signal[indice(i,j,k,sig_size)]);
            }
        }
    }
}

void print_ker(double ker[MAX_KER],unsigned int ker_size[4])
{
    for(unsigned int i = 0; i <ker_size[0];i++)
    {
        for(unsigned int j = 0; j <ker_size[1];j++)
        {
            for(unsigned int k = 0; k <ker_size[2];k++)
            {
                for(unsigned int l=0;l <ker_size[3];l++)
                {
                    printf("[%u][%u][%u][%u]:%lf\n",i,j,k,ker[indice(i,j,k,l,ker_size)]);
                }

            }
        }
    }
}

void print_vector(double* vect, unsigned int size)
{
	for (unsigned int i = 0; i <size ;i++)
	{
		 printf("[%u]:%lf\n",i,vect[i]);
	}
}



