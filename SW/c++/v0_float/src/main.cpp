// Format me with:
//   clang-format -i -style=file main.cpp
//
// Compile me with:
#include "../headers/main.hpp"

int main()
{
    //getPGMfile()
    unsigned int im_size[3];
    unsigned int ker_size[4]={3,3,3,2};
    char* f_name=(char*)"test.png";
    char ***im=read_png_file(f_name,im_size );
    double **** ker=gen_rand_ker(ker_size);
	cout<<im_size[0]<<endl;
	cout<<im_size[1]<<endl;
	cout<<im_size[2]<<endl;
	cout << "Image readed sucessfully\n" << endl;
	double *** res=convolve(im,ker,im_size,ker_size);
    cout << "Convolution Done" << endl;
    unsigned int sig_size[3];sig_size[0]=im_size[0];sig_size[1]=im_size[1];sig_size[2]=ker_size[3];
    relu(res,sig_size);
    cout << "Relu Done" << endl;
    double*** maxp_r=maxpool(res,sig_size,4);
    cout << "Maxpool Done!" << endl;
    unsigned int maxpool_size[3]={sig_size[0]/4,sig_size[1]/4,sig_size[2]};
    print_matrix(maxp_r,maxpool_size);
    return 0;
}
