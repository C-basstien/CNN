#include "../headers/main.hpp"

/***
ROLE:
	Function that convolve an image (im) with a kernel
	The mode of convultion is 'same'. Please refers to testconvalgo.py
	to understand what the differents modes does.
***/

/***
INPUT :
		3D array (im), 4D array (ker)
		im_size: indic the size of the dimensions of the image 
		ker_size: indic the size of the dimensions of the kernel
		bias: 1D array  which store the bias value to add up to the convultion result
***/

/***
OUTPUT
	3D array, result of the convultion and the addition of the biases
***/
double*** convolve(double*** im, double**** ker,unsigned int* im_size, unsigned int* ker_size, double * bias)
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

	/**Indice array to do a trick to select correctly the data
		corresponding to 
		conv_same2=conv_full2[kersize//2:imsize+kersize//2,kersize//2:imsize+kersize//2]
		in python
		because same, full, valid modes of convultion are the same algorithm valid and same just select submatrix in 			the full convolution result**/
	unsigned int width_start= ker_size[0]/2;unsigned int width_end=im_size[0]+ker_size[0]/2;
	unsigned int height_start= ker_size[1]/2;unsigned int height_end=im_size[1]+ker_size[1]/2;
	printf("kerw=%u kerh=%u ws=%u wh=%u\n",ker_width,ker_height,width_start,height_start);
	unsigned int xbuff,ybuff;
	/**because the computation for cifar10 convolution is "same" mode**/    
	unsigned int buff_size[3]= {im_width,im_height,ker_filter};
	/**check if the canals sof kernel and image have the same size.**/
   if(ker_canal!=im_canal){printf("error ker and input have different canal size");abort();}
	double *** buff=alloc_matrix(buff_size);
	/**Filter Loop**/
	for(unsigned int filter_index=0;filter_index< ker_filter;filter_index++)
	{
		for(unsigned int canal_index=0;canal_index< im_canal;canal_index++)//Fill the canal of the ouput matrix
		{
			for(unsigned int x=width_start;x< width_end;x++)//Fill the line of the ouput matrix
			{
				for(unsigned int y=height_start;y< height_end;y++)//Fill the column of the ouput matrix
				{
					for(unsigned int ker_x=0;ker_x< ker_width;ker_x++)
					{//convolution horizontal index sweeping
						xbuff=x-width_start;
						for(unsigned int ker_y=0;ker_y< ker_height;ker_y++)
						{//convolution vertical index sweeping
							ybuff=y-height_start;
							//Index value out of the image border are paded to 0
							//printf("xbuff=%u ybuff=%u x=%u y=%u ker_x=%u ker_y=%u\n",xbuff,ybuff,x,y,ker_x,ker_y);
							//printf("xim=%u yim=%u x=%u y=%u ker_x=%u ker_y=%u\n",x-ker_x,ker_y-y,x,y,ker_x,ker_y);
							if( x-ker_x<0 || x-ker_x >=im_width || y-ker_y<0 || y-ker_y >= im_height ){}
                     else
							{
								buff[xbuff][ybuff][filter_index]=buff[xbuff][ybuff][filter_index]+im[x-ker_x][y-ker_y][canal_index]*ker[ker_x][ker_y][canal_index][filter_index];
							}
						}
					}
					buff[xbuff][ybuff][filter_index]=buff[xbuff][ybuff][filter_index]+bias[filter_index];
				}
			}
		}

	}
	return buff;
}

