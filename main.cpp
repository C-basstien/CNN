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
//*#include <jpeglib.h>*/
//#include <jerror.h>*/
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
char*** read_png_file(char* file_name,int* output_im_size)
{
        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
        {
            // abort_("[read_png_file] File %s could not be opened for reading", file_name);
        }

        fread(header, 1, 8, fp);
        if (png_sig_cmp((png_byte*)header, 0, 8))
        {
                //  abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
        }


        /* initialize stuff */
        png_structp  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
        {
            // abort_("[read_png_file] png_create_read_struct failed");
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            // abort_("[read_png_file] png_create_info_struct failed");

        }
        if (setjmp(png_jmpbuf(png_ptr)))
        {
            //  abort_("[read_png_file] Error during init_io");
        }

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        const int width = png_get_image_width(png_ptr, info_ptr);
        const int  height = png_get_image_height(png_ptr, info_ptr);
        const int  color_type = png_get_color_type(png_ptr, info_ptr);
        const int  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        output_im_size[0]=width;
        output_im_size[1]=height;
        output_im_size[2]=3;
        const int number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);

        cout <<"width: "<<width<<", height: "<<height<<", color_type: "<<color_type<<"bit_depth: "<< bit_depth<< endl;
        cout<<number_of_passes<<endl;
        cout<<endl;
        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
        {
            //  abort_("[read_png_file] Error during read_image");

        }

        png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (int y=0; y<height; y++)
        {
            row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        }


        png_read_image(png_ptr, row_pointers);

        char *** buff= new char **[width]();
        for (int i = 0; i < width; i++)
        {
            buff[i] = new char*[height]();
            for (int j = 0; j < height;j++){buff[i][j] = new char[3]();}
            //cout<<"running init"<<endl;
        }

        for (int y=0; y<height; y++)
        {
            png_byte* row = row_pointers[y];
            for (int x=0; x<width; x++)
            {
                /*cout<<(int)(ptr)<<'\t';}cout<<endl;*/
                png_byte* ptr = &(row[x*4]);
                //printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
                buff[x][y][0]=ptr[0];
                buff[x][y][1]=ptr[1];
                buff[x][y][2]=ptr[2];
                //cout<<"running conversion"<<endl;

            }
        }

        fclose(fp);
        return buff;
}

double*** convolve(char*** im, double**** ker,int* im_size, int* ker_size)
{
	/**Get the dimmension**/

		/*IM*/
	int im_width= im_size[0];
	int im_height= im_size[1];
	int im_canal= im_size[2];

		/*KER*/
	int ker_width= ker_size[0];
	int ker_height= ker_size[1];
	int ker_canal= ker_size[2];
	int ker_filter= ker_size[3];

	/**Create a buffer and output val**/

	double *** buff= new double **[im_width+ker_width-1]();
    for (int i = 0; i < im_width+ker_width-1;i++)
    {
        buff[i] = new double*[im_height+ker_height-1]();
        for (int j = 0; j < im_height+ker_height-1;j++){buff[i][j] = new double[ker_filter]();}
    }


	/*[const int(im_height+ker_height-1)][const int(ker_filer)];
	int * out= new int[const int(im_width)][const int(im_height)][const int(ker_filer)];*/


	/**Filter Loop**/
	for(int filter_index=0;filter_index< ker_filter;filter_index++)
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

void relu(double*** sig,int* sig_size)
{
    for (int i = 0; i <sig_size[0];i++)
    {
        for (int j = 0; j <sig_size[1] ;j++)
        {
            for (int k = 0; k <sig_size[2] ;k++)
            {
                    if(sig[i][j][k]<0){sig[i][j][k]=0;}
            }
        }
    }
}
double*** maxpool(double ***sig,int* sig_size,int stride)
{
    double *** max= new double **[sig_size[0]/stride]();
    for (int i = 0; i < sig_size[0]/stride;i++)
    {
        max[i] = new double *[sig_size[1]/stride]();
        for (int j = 0; j < sig_size[1]/stride;i++)
        {
            max[i][j] = new double[sig_size[3]]();
        }
    }

    for (int n = 0; n <sig_size[3];n++)
    {
        for (int i = 0; i <sig_size[1];i+=stride)
        {
            for (int j = 0; j <sig_size[2] ;j+=stride)
            {
                    int ii=i/(stride);
                    int jj=j/(stride);
                    for (int a = 0; a <stride ;a++)
                    {
                        for (int b = 0; b <stride ;b++)
                        {
                            if(sig[i+a][j+b][n]>max[ii][jj][n] ){max[ii][jj][n]=sig[i+a][j+b][n];}
                        }
                    }


            }
        }
    }
    return max;
}

int main()
{
    //getPGMfile()
    int im_size[3];
    int ker_size[3];
    ker_size[0]=3;
    ker_size[1]=3;
    ker_size[2]=3;
    ker_size[3]=2;
    char ***im=read_png_file("test.png",im_size );
    double **** ker= new double ***[ker_size[0]]();
    for (int i = 0; i <ker_size[0];i++)
    {
        ker[i] = new double**[ker_size[1]]();
        for (int j = 0; j <ker_size[1] ;j++)
        {
            ker[i][j]= new double*[ker_size[1]]();
            for (int k = 0; k <ker_size[2] ;k++)
            {
                ker[i][j][k] = new double[ker_size[3]]();
                for (int l = 0; l <ker_size[3] ;l++)
                {
                    ker[i][j][k][l]=((rand()/(double)(RAND_MAX)));

                }
            }
        }
    }
    for (int i = 0; i <ker_size[0];i++)
    {
        for (int j = 0; j <ker_size[1] ;j++)
        {
            for (int k = 0; k <ker_size[2] ;k++)
            {
                for (int l = 0; l <ker_size[3] ;l++)
                {
                    printf("ker:[%u][%u][%u][%u]: %lf\n",i,j,k,l,ker[i][j][k][l]);
                }
            }
        }
    }
    //
   /* const int im_width= sizeof(im)/(sizeof(im[0]));
	const int im_height= sizeof(im[0])/(sizeof(im[0][0]));
	const int im_canal= sizeof(im[0][0]);*/
	cout<<im_size[0]<<endl;
	cout<<im_size[1]<<endl;
	cout<<im_size[2]<<endl;
	cout << "Image readed sucessfully\n" << endl;
	double *** res=convolve(im,ker,im_size,ker_size);
    cout << "Convolution Done" << endl;
    int sig_size[3];sig_size[0]=im_size[0];sig_size[1]=im_size[1];sig_size[0]=ker_size[3];

    relu(res,sig_size);
    /*for (int i = 0; i <im_size[0];i++)//affiche le resutat de la convolution
    {
        for (int j = 0; j <im_size[1] ;j++)
        {
            for (int k = 0; k <ker_size[3] ;k++)
            {
                    printf("ker:[%u][%u][%u]: %lf\n",i,j,k,res[i][j][k]);
            }
        }
    }*/
    cout << "Relu Done" << endl;
    maxpool(res,sig_size,4);
    cout << "Maxpool Done!" << endl;
    return 0;
}
