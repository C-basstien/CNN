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
#include <cstdlib>
#include <cstdio>
#include <png.h>
/*#include <jpeglib.h>
#include <jerror.h>*/
///#include <opencv2/opencv.hpp>
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


// Allocate imageData->pixels to be the correct size, start decompress and all
// that jazz, like you did in your code. Skip allocating buffer though.
// ...


	

//getPGMfile
/*int *** readJpeg( char *path )
{
    FILE *file = fopen( path, "rb" );
    if ( file == NULL )
    {
        return NULL;
    }
		

    struct jpeg_decompress_struct info; //for our jpeg info
    struct jpeg_error_mgr err; //the error handler

    info.err = jpeg_std_error( &err );     
    jpeg_create_decompress( &info ); //fills info structure

    jpeg_stdio_src( &info, file );    
    jpeg_read_header( &info, true );

    jpeg_start_decompress( &info );

		const int w = info.output_width;
		const int h = info.output_height;
		const int numChannels = info.num_components; // 3 = RGB, 4 = RGBA
    unsigned long dataSize = w * h * numChannels;
		
		int *** im = new int **[w]();
    for (int i = 0; i < w;i++)
    {
        im[i] = new int*[h]();
        for (int j = 0; j < h;j++){im[i][j] = new int[numChannels]();}
    }
    // read RGB(A) scanlines one at a time into jdata[]
    unsigned char *data = new unsigned char[dataSize]();
    unsigned char* rowptr;
    while ( info.output_scanline < h )
    {
        rowptr = data + info.output_scanline * w * numChannels;
        jpeg_read_scanlines( &info, &rowptr, 1 );
    }

    jpeg_finish_decompress( &info );    

    fclose( file );

    // this code block is only if you happen to want output in CImg format, but is illustrative
   // CImg<unsigned char> *image = new CImg<unsigned char>( w, h, 1, numChannels );
    for ( int x = 0 ; x < w ; x++ )
    {
        for ( int y = 0 ; y < h ; y++ )
        {
            for ( int c = 0 ; c < numChannels ; c++ )
            {
                im[x][y][c] = data[ y * w * numChannels + x * numChannels + c ];
            }
        }
    }

    delete data ;

    return im;
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
		//getPGMfile()
    cout << "Hello World!\n" << endl;
    return 0;
}
