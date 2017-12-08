#include "../headers/main.hpp"
/**print generalized matrix, doesnt work right now**/
/*template <typename  T>
void print_matrix(T  matrix,unsigned int * dim_val_array, unsigned int  dim_size_array)
{
    if(dim_size_array>1)
    {
		for (unsigned int i= 0; i < *dim_val_array;i++)
		{
		   print_matrix(matrix[i],(dim_val_array+1),dim_size_array-1);
		}
	}
	else if(dim_size_array ==1)
	{
		for (unsigned int i = 0; i < *dim_val_array;i++)
		{
            cout<<(matrix[i])<<" ";
		}
	}
	else{}
}*/
/**temporary solution**/
void print_matrix(double*** mat,unsigned int * dim_array)
{
    for (unsigned int i = 0; i <dim_array[0];i++)
    {
        for (unsigned int j = 0; j <dim_array[1];j++)
        {
            for (unsigned int k = 0; k <dim_array[2];k++)
            {
                printf("[%u][%u][%u]:%lf\n",i,j,k,mat[i][j][k]);
            }
        }
    }
}

void print_ker(double**** ker,unsigned int * dim_array)
{
    for (unsigned int i = 0; i <dim_array[0];i++)
    {
        print_matrix(ker[i],dim_array+1);
    }
}

