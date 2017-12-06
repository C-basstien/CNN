#include "../headers/main.hpp"
double*** convolve(char*** im, double**** ker,unsigned int* im_size, unsigned int* ker_size)
{
	/**Get the dimmension**/

		/*IM*/
	unsigned int im_width= im_size[0];
	unsigned int im_height= im_size[1];
	unsigned int im_canal= im_size[2];

		/*KER*/
	unsigned int ker_width= ker_size[0];
	unsigned int ker_height= ker_size[1];
	unsigned int ker_canal= ker_size[2];
	unsigned int ker_filter= ker_size[3];

    unsigned int buff_size[3]= {im_width+ker_width-1,im_height+ker_height-1,ker_filter};
    if(ker_canal!=im_canal){printf("error ker and input have different canal size");abort();}
	double *** buff=alloc_matrix(buff_size);
	/**Filter Loop**/
	for(unsigned int filter_index=0;filter_index< ker_filter;filter_index++)
	{
		for(unsigned int canal_index=0;canal_index< im_canal;canal_index++)
		{
			for(unsigned int x=0;x< im_width+ker_width;x++)
			{
				for(unsigned int y=0;y< im_height+ker_height;y++)
				{
					for(unsigned int ind_ker_x=0;ind_ker_x< ker_width;ind_ker_x++)
					{
						for(unsigned int ind_ker_y=0;ind_ker_y< ker_height;ind_ker_y++)
						{
							if( x-ind_ker_x<0 || x-ind_ker_x >=im_width || y-ind_ker_y<0 || y-ind_ker_y >= im_height ){}
                            else{buff[x][y][filter_index]=buff[x][y][filter_index]+im[x-ind_ker_x][y-ind_ker_y][canal_index]*ker[ind_ker_x][ind_ker_y][canal_index][filter_index];}
						}
					}
				}
			}
		}
	}
	return buff;
}
