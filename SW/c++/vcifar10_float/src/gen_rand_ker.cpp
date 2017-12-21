#include "../headers/main.hpp"

double**** gen_rand_ker(unsigned int* ker_size)
{
    double**** ker =new double ***[ker_size[0]]();
    for (unsigned int i = 0; i <ker_size[0];i++)
    {
        ker[i] = new double**[ker_size[1]]();
        for (unsigned int j = 0; j <ker_size[1] ;j++)
        {
            ker[i][j]= new double*[ker_size[1]]();
            for (unsigned int k = 0; k <ker_size[2] ;k++)
            {
                ker[i][j][k] = new double[ker_size[3]]();
                for (unsigned int l = 0; l <ker_size[3] ;l++)
                {
                    ker[i][j][k][l]=((rand()/(double)(RAND_MAX)));

                }
            }
        }
    }
    return ker;
}


double** gen_rand_matrix(unsigned int* m_size)
{
    double** m =new double *[m_size[0]]();
    for (unsigned int i = 0; i <m_size[0];i++)
    {
		 m[i] = new double[m_size[1]]();
		 for (unsigned int l = 0; l <m_size[1] ;l++)
		 {
		     ker[i][j]=((rand()/(double)(RAND_MAX)));

		 }
     }
    return m;
}
