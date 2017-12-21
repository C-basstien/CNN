#include "../headers/main.hpp"
/**Files to test the convultion function***/
/**main to test function**/

/*void testconv(void);
double *** conv_im_input(double test_im[4][4][1]);
double **** conv_ker_input(double test_ker[3][3][1][1]);*/


double *** conv_im_input(double test_im[4][4][1])
{
	 double *** mat= new double **[4]();
    for (unsigned int i = 0; i <4;i++)
    {
        mat[i] = new double *[4]();
        for (unsigned int j = 0; j <4;j++)
        {
            mat[i][j] = new double[1]();
			   mat[i][j][0] = test_im[i][j][0];
        }
    }
    return mat;
}
double **** conv_ker_input(double test_ker[3][3][1][1])
{
	 double**** ker =new double ***[3]();
    for (unsigned int i = 0; i <3;i++)
    {
        ker[i] = new double**[3]();
        for (unsigned int j = 0; j <3 ;j++)
        {
            ker[i][j]= new double*[1]();
				ker[i][j][0] = new double[1]();
 				ker[i][j][0][0]= test_ker[i][j][0][0];

        }
    }
    return ker;
}
void testconv(void)
{
	/**here we define the coefficient of the "image" and "kernel" **/
	double test_im[4][4][1]={{{10},{3},{12},{2}},{{1},{6},{1},{2}},{{9},{6},{7},{12}},{{13},{6},{5},{2}}};
	double test_ker[3][3][1][1]={{{{1}},{{4}},{{3}}},{{{2}},{{6}},{{8}}},{{{20}},{{5}},{{6}}}};
	double test_biases[1]={0};


   unsigned int im_size[3]={4,4,1};
   unsigned int ker_size[4]={3,3,1,1};


	/**for compatibilty with the input types of convultion function we need to convert their types**/
	double*** im= conv_im_input(test_im);
	double**** ker=conv_ker_input(test_ker);
	cout<<"image"<<endl;
	print_matrix(im,im_size);
	cout<<endl;
	cout<<"kernel"<<endl;
	print_ker(ker,ker_size);
	/**try the same in python and check the differences result**/
	double *** res=convolve(im,ker,im_size,ker_size,test_biases);
   cout << "Convolution Done" << endl;
	print_matrix(res,im_size);
	/**we could build a script to have an automated comparaison. 
		But, for small array dimensions the manually comparison should not be too difficult...
		**/

}

