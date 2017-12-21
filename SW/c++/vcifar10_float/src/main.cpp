#include "../headers/main.hpp"

int main()


{
	/***CONVOLUTION TEST HERE**/	

	/**For testing the convolution function in 2D with very simple ouput**/
	/**Set the value manually to check if there is a difference betwwen python result and C implementation**/
	
	//testconv();// compare with the ouput valut of testconvalgo.py, should be the same


	/****NEURAL NETWORK TEST HERE***/
   unsigned int im_size[3];
  
   /**Init input: image, kernels and fully connected matrix**/
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

	unsigned int m_size[2]={3,3};/***size of fully connected matrix**/
	double ** ker2=gen_rand_matrix(m_size);/**fully connected matrix**/
	cout << "percepton matrix generate \n" << endl;
	
	/***LAYER 1***/
	double *** conv1=convolve(im,ker1,im_size,ker1_size,biases1);
   cout << "Convolution1 Done" << endl;
   /**definition of size of convolued output for input it into relu**/
	unsigned int conv1_size[3];
	conv1_size[0]=im_size[0];/**same width as the input image**/
	conv1_size[1]=im_size[1];/**same height as the input image**/
	conv1_size[2]=ker1_size[3];/*because ouput canal size have the same size that the filter number of kernel1**/
	relu(conv1,conv1_size);
   cout << "Relu1 Done" << endl;
   double*** maxp1=maxpool(conv1,conv1_size,3,2);
   cout << "Maxpool1 Done!" << endl;
   unsigned int maxp1_size[3]={conv1_size[0]/2,conv1_size[1]/2,conv1_size[2]};/**size needed to print the output**/
   //print_matrix(maxp1,maxp1_size);


	/***LAYER 2***/
	double *** conv2=convolve(maxp1,ker2,maxp1_size,ker2_size,biases2);
	 /**definition of size of convolued output for input it into relu**/
	unsigned int conv2_size[3];
	conv2_size[0]=maxp1_size[0];/**same width as the input image**/
	conv2_size[1]=maxp1_size[1];/**same height as the input image**/
	conv2_size[2]=ker2_size[3];/*because ouput canal size have the same size that the filter number of kernel2**/
	relu(conv2,conv2_size);
   cout << "Relu2 Done" << endl;
   double*** maxp2=maxpool(conv2,conv2_size,3,2);
   cout << "Maxpool2 Done!" << endl;
   unsigned int maxp2_size[3]={conv2_size[0]/2,conv2_size[1]/2,conv2_size[2]};/**size needed to print the output**/
   //print_matrix(maxp1,maxp2_size);
	
	/***LAYER 3***/
	double *** conv3=convolve(maxp2,ker2,maxp2_size,ker2_size,biases2);
	 /**definition of size of convolued output for input it into relu**/
	unsigned int conv3_size[3];
	conv3_size[0]=maxp2_size[0];/**same width as the input image**/
	conv3_size[1]=maxp2_size[1];/**same height as the input image**/
	conv3_size[2]=ker2_size[3];/*because ouput canal size have the same size that the filter number of kernel2**/
	relu(conv3,conv3_size);
   cout << "Relu3 Done" << endl;
   double*** maxp3=maxpool(conv3,conv3_size,3,2);
   cout << "Maxpool3 Done!" << endl;
   unsigned int maxp3_size[3]={conv3_size[0]/2,conv3_size[1]/2,conv3_size[2]};/**size needed to print the output**/
   //print_matrix(maxp2,maxp2_size);
	
	/**FULLY CONNECTED LAYER**/
	double* reshape_vect=reshape(maxp2,maxp3_size);
	double* reduced_vect=matrix_product(double ** M, reshape_vect,unsigned int* sizes);

	/*double* classes_prob_vect=;
	unsigned classe_nummber=;*/



   return 0;
}
