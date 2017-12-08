#include "../headers/main.hpp"
/**allocate generalized matrix, doesnt work right now**/
/*template <class  T>
T* alloc_matrix(T* matrix,unsigned int * dim_val_array, unsigned int  dim_size_array)
{
    matrix = new T [dim_val_array[0]]();
    if(dim_size_array>1)
    {
		for (unsigned int i = 0; i < dim_val_array[0];i++)
		{
		    matrix[i] = alloc_matrix(matrix[i],(dim_val_array+1),dim_size_array-1);
		}
	}
	return matrix;
}*/
/**temporary solution**/
double*** alloc_matrix(unsigned int * dim_array)
{
    double *** mat= new double **[dim_array[0]]();
    for (unsigned int i = 0; i <dim_array[0];i++)
    {
        mat[i] = new double *[dim_array[1]]();
        for (unsigned int j = 0; j <dim_array[1];j++)
        {
            mat[i][j] = new double[dim_array[2]]();
        }
    }
    return mat;
}
