// Format me with:
//   clang-format -i -style=file main.cpp
//
// Compile me with:
//   g++ -o main.exe main.cpp
// or with:
//   g++ -Wall  -o main.exe main.cpp
//
// Run the compiled program (exe):
//   ./main.exe
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
/*void* new_multidimensional_matrix(const int dim_size_array[] )
{
    sizeof(im)
    void * out
    dim_size_array[0]
    for(int i=0; i<dim_size_array[0] ;i++)
    {
        if(sizeof(dim_size_array)>1){new_multidimensional_matrix(dim_size_array+1)}
    }

}*/

void* convolve(int*** im, int**** ker)
{
	/**Get the dimmension**/

		/*IM*/
	const int im_width= sizeof(im)/(sizeof(im[0]));
	const int im_height= sizeof(im[0])/(sizeof(im[0][0]));
	const int im_canal= sizeof(im[0][0]);

		/*KER*/
	const int ker_width= sizeof(ker)/(sizeof(ker[0]));
	const int ker_height= sizeof(ker[0])/(sizeof(ker[0][0]));
	const int ker_canal= sizeof(ker[0][0])/(sizeof(ker[0][0][0]));
	const int ker_filer= sizeof(ker[0][0][0]);

	/**Create a buffer and output vat**/

	int *** buff= new int **[im_width+ker_width-1]();
    for (int i = 0; i < im_width+ker_width-1;i++)
    {
        buff[i] = new int*[im_height+ker_height-1]();
        for (int j = 0; j < im_height+ker_height-1;j++){buff[i][j] = new int[ker_filer]();}
    }


	/*[const int(im_height+ker_height-1)][const int(ker_filer)];
	int * out= new int[const int(im_width)][const int(im_height)][const int(ker_filer)];*/


	/**Filter Loop**/
	for(int filter_index=0;filter_index< ker_filer;filter_index++)
	{
		for(int canal_index=0;canal_index< im_canal;canal_index++)
		{

			for(int x=0;x< im_width+ker_width;x++)
			{
				for(int y=0;y< im_height+ker_height;y++)
				{
					for(int ind_ker_x=0;ind_ker_x< ker_width;ind_ker_x++)
					{
						for(int ind_ker_y=0;ind_ker_y< ker_height;ind_ker_y++)
						{
							if( x-ind_ker_x<0 || x-ind_ker_x >=im_width || y-ind_ker_y<0 || y-ind_ker_y >= im_height ){}
                            else{buff[x][y][filter_index]=buff[x][y][filter_index]+im[x-ind_ker_x][y-ind_ker_y][canal_index]*ker[ind_ker_x][ind_ker_y][canal_index][filter_index];}
						}
					}
				}
			}
		}
	}
	/*for (int x=0; x< im_width;x++)
	{
		 for (int y=0;y< im_height;y++)
		{
			out[x][y]=buff[x][y];
		}
	}*/
	//delete buff;
	return buff;
}

int main()
{
    cout << "Hello World!\n" << endl;
    return 0;
}
