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
		inout_size: indic the size of the dimensions of the image
		ker_size: indic the size of the dimensions of the kernel
		bias: 1D array  which store the bias value to add up to the convultion result
***/

/***
OUTPUT
	3D array, result of the convultion and the addition of the biases
***/
void convolve(double input[MAX_IM],double output[MAX_IM],double ker[MAX_KER],double bias[MAX_BIAS],unsigned int inout_size[3], unsigned int ker_size[4],unsigned int bias_size)
{
	/**Get the dimmension**/

		/*IM*/
	unsigned int im_width= inout_size[0];
	unsigned int im_height= inout_size[1];
	unsigned int im_canal= inout_size[2];

		/*KER*/
	unsigned int ker_width= ker_size[0];
	unsigned int ker_height= ker_size[1];
	unsigned int ker_canal= ker_size[2];
	unsigned int ker_filter= ker_size[3];

	/**Indice array to do a trick to select correctly the data
		corresponding to
		conv_same2=conv_full2[kersize//2:imsize+kersize//2,kersize//2:imsize+kersize//2]
		in python
		because same, full, valid modes of convultion are the same algorithm valid and same just select submatrix in the full convolution result**/
	unsigned int width_start= ker_size[0]/2;
	unsigned int height_start= ker_size[1]/2;
	unsigned int xin,yin;
	/**because the computation for cifar10 convolution is "same" mode**/
	unsigned int out_size[3]= {im_width,im_height,ker_filter};
	/**check if the canals sof kernel and image have the same size.**/
    if(ker_canal!=im_canal){printf("error ker and input have different canal size");abort();}
    if(bias_size!=ker_filter){printf("error bias and output have different size");abort();}
	/**Filter Loop**/
	for(unsigned int filter_index=0;filter_index< ker_filter;filter_index++)
	{
		for(unsigned int canal_index=0;canal_index< im_canal;canal_index++)//Fill the canal of the ouput matrix
		{
			for(unsigned int x=0;x< im_width;x++)//Fill the line of the ouput matrix
			{
				for(unsigned int y=0;y< im_height;y++)//Fill the column of the ouput matrix
				{
					for(unsigned int ker_x=0;ker_x< ker_width;ker_x++)
					{//convolution horizontal index sweeping
						xin=x-width_start;
						for(unsigned int ker_y=0;ker_y< ker_height;ker_y++)
						{//convolution vertical index sweeping
							yin=y-height_start;
							//Index value out of the image border are paded to 0
							//printf("xout=%u yout=%u x=%u y=%u ker_x=%u ker_y=%u\n",xout,yout,x,y,ker_x,ker_y);
							//printf("xim=%u yim=%u x=%u y=%u ker_x=%u ker_y=%u\n",x-ker_x,ker_y-y,x,y,ker_x,ker_y);
							if( xin+ker_x<0 || xin+ker_x >=im_width || yin+ker_y<0 || yin+ker_y >= im_height ){}
                            else
							{
								output[indice(x,y,filter_index,out_size)]+=input[indice(xin+ker_x,yin+ker_y,canal_index,inout_size)]*ker[indice(ker_x,ker_y,canal_index,filter_index,ker_size)];
							}
						}
					}
					output[indice(x,y,filter_index,out_size)]+=bias[filter_index];
				}
			}
		}
	}
	inout_size[2]=ker_filter;
}

