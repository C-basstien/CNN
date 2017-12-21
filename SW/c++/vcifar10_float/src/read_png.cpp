#include "../headers/main.hpp"
char*** read_png_file(char* file_name,unsigned int* output_im_size)
{
        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
        {
            printf("[read_png_file] file %s could not be opened for reading", file_name);
            abort();
        }
        fread(header, 1, 8, fp);
        if (png_sig_cmp((png_byte*)header, 0, 8))
        {
            printf("[read_png_file] File %s is not recognized as a PNG file", file_name);
            abort();
        }
        /* initialize stuff */
        png_structp  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
        {
            printf("[read_png_file] png_create_read_struct failed");
            abort();
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            printf("[read_png_file] png_create_info_struct failed");
            abort();

        }
        if (setjmp(png_jmpbuf(png_ptr)))
        {
            printf("[read_png_file] Error during init_io");
            abort();
        }
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);

        unsigned int width = png_get_image_width(png_ptr, info_ptr);
        unsigned int height = png_get_image_height(png_ptr, info_ptr);
        //unsigned int color_type = png_get_color_type(png_ptr, info_ptr);
        //unsigned int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        //unsigned int number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);
        output_im_size[0]=width;
        output_im_size[1]=height;
        output_im_size[2]=3;
        /*cout <<"width: "<<width<<", height: "<<height<<", color_type: "<<color_type<<"bit_depth: "<< bit_depth<< endl;
        cout<<number_of_passes<<endl;
        cout<<endl;*/
        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
        {
             printf("[read_png_file] Error during read_image");
             abort();

        }
        png_bytep * row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (unsigned int y=0; y<height; y++)
        {
            row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        }
        png_read_image(png_ptr, row_pointers);
        char *** buff= new char **[width]();
        for (unsigned int i = 0; i < width; i++)
        {
            buff[i] = new char*[height]();
            for (unsigned int j = 0; j < height;j++){buff[i][j] = new char[3]();}
            //cout<<"running init"<<endl;
        }
        for (unsigned int y=0; y<height; y++)
        {
            png_byte* row = row_pointers[y];
            for (unsigned int x=0; x<width; x++)
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

double *** chartodouble_arr(char*** im,unsigned int* im_size)
{
	 double *** out=alloc_matrix(im_size);
    for (unsigned int i = 0; i <im_size[0];i++)
    {
        for (unsigned int j = 0; j <im_size[1];j++)
        {
            for (unsigned int k = 0; k <im_size[2];k++)
            {
                out[i][j][k]=(double)im[i][j][k];
            }
        }
    }
	return out;
}
