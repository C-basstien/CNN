#include "../headers/main.hpp"

int main()


{
	/***CONVOLUTION TEST HERE**/	

	/**For testing the convolution function in 2D with very simple ouput**/
	/**Set the value manually to check if there is a difference betwwen python result and C implementation**/
	
	//testconv();// compare with the ouput valut of testconvalgo.py, should be the same


	/****NEURAL NETWORK TEST HERE**/
   unsigned int im_size[3];
  

   char* f_name=(char*)"test.png";/**your file name**/
   char ***imchar=read_png_file(f_name,im_size );/**convert png into a 3D double array **/	
	double*** im=chartodouble_arr(imchar,im_size);

	cout << "Image readed \n" << endl; 
 /*cout<<im_size[0]<<endl;
	cout<<im_size[1]<<endl;
	cout<<im_size[2]<<endl;*/ //check image sizes
	
	/***kernel dimensions definition {width,height,canal,filter_number}**/
   unsigned int ker1_size[4]={3,3,3,2};/***size of kernel1**/
   double **** ker1=gen_rand_ker(ker1_size);/**kernel 1**/
	cout << "kernel1 generate \n" << endl; 

	unsigned int ker2_size[4]={3,3,3,2};/***size of kernel1**/
	double **** ker2=gen_rand_ker(ker2_size);/**kernel 2**/
	cout << "kernel2 generate \n" << endl;

	double biases1[2]={0,0};/**biases must have size of filter_number **/
	cout << "biases1 generate \n" << endl;
	double biases2[2]={0,0};/**biases must have size of filter_number **/
	cout << "biases2 generate \n" << endl;
	
	double *** res=convolve(im,ker1,im_size,ker1_size,biases1);
   cout << "Convolution Done" << endl;
   /**definition of size of convolued output for input it into relu**/
	unsigned int conv1_size[3];
	conv1_size[0]=im_size[0];/**same width as the input image**/
	conv1_size[1]=im_size[1];/**same height as the input image**/
	conv1_size[2]=ker1_size[3];/*because ouput canal size have the same size that the filter number of kernel1**/
	relu(res,conv1_size);
   cout << "Relu Done" << endl;
   double*** maxp_r=maxpool(res,conv1_size,3,2);
   cout << "Maxpool Done!" << endl;
   unsigned int maxpool_size[3]={conv1_size[0]/4,conv1_size[1]/4,conv1_size[2]};/**size needed to print the output**/
   print_matrix(maxp_r,maxpool_size);
   return 0;
}
