#include "convolve.h"
void getDim()
void* convolve(int im[][][],int ker[][][][])
{	
	/**Get the dimmension**/

		/*IM*/
	unsigned int im_width= sizeof(im)/(sizeof(im[0]);
	unsigned int im_height= sizeof(im[0])/(sizeof(im[0][0]);
	unsigned int im_canal= sizeof(im[0][0]);
		
		/*KER*/
	unsigned int ker_width= sizeof(ker)/(sizeof(ker[0]);
	unsigned int ker_height= sizeof(ker[0])/(sizeof(ker[0][0]);
	unsigned int ker_canal= sizeof(ker[0][0])/(sizeof(ker[0][0][0]);
	unsigned int ker_filer= sizeof(ker[0][0][0]);
	
	/** **/
	
	/**Create a buffer and output vat**/
	
	buff= new int[im_width+ker_width-1][im_height+ker_height-1][ker_filer];
	out= new int[im_width][im_height][ker_filer]; 
	

	/**Filter Loop **/
	for(int filer_index=0;filer_index< ker_filer;filer_index++)
	{
		for(int canal_index=0;canal_index< im_canal;canal_index++)
		{
		
			for(int x=0;x< im_width+ker_width;x++)
			{
				for(int y=0;y< im_height+ker_height);y++)
				{
					for(int ind_ker_x=0;ind_ker_x< ker_width;ind_ker_x++))
					{
						for(int ind_ker_y=0;ind_ker_y< ker_height;ind_ker_x++)
						{
							if( i-k <0 or i-k >=im_width or j-l<0 or j-l >= im_height )
              else{buff[x][y][filter_index]=buff[ind_ker_x][ind_ker_y][filter_index]+im[x-ind_ker_x][y-ind_ker_y][canal_index]*ker[k][l][canal_index][filter_index];}
						}
					}
				}
			}
		}
	}
	for (int x=0; x< im_width;x++)
	{
		 for (int y=0;y< im_height;y++)
		{
			out[x][y]=buff[x][y];
		}
	}
	delete buff;
	return out;
}
