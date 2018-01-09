#include "../headers/main.hpp"
#include <vector>
typedef char byte;
const std::size_t batchsize = 10;
const std::size_t image_height = 32;
const std::size_t image_width = 32;
const std::size_t color_channels = 3;
void write_file(double img_out[MAX_IM])
{
  std::ofstream outFlux("output_image.txt");

  //outFlux<<LIGNE_OUT<<endl;
  //outFlux<<COLONNE_OUT<<endl;

  for(int i=0;i< MAX_IM;i++)
    {
      outFlux<<img_out[i]<<endl;
    }

}

void write_file(double img_out[LIGNE_OUT][COLONNE_OUT], char* name)
{
    std::ofstream outFlux(name);
    for(int i=0;i<LIGNE_OUT;i++)
    {
        for(int j=0;j<COLONNE_OUT;j++)
        {
            outFlux<<img_out[i][j]<<endl;
        }
    }

}

void write_file_32(double img_out[NB_LIGNE_PLUS][NB_COLONNE_PLUS], char* name)
{
    std::ofstream outFlux(name);
    for(int i=0;i<NB_LIGNE_PLUS;i++)
    {
        for(int j=0;j<NB_COLONNE_PLUS;j++)
        {
            outFlux<<img_out[i][j]<<endl;
        }
    }

}


float accuracy(unsigned char imgIn,
	       unsigned char imgClassPredicted,int goodPredictionNum,
	       int totalImgRead){
  std::cout << "Label: " << static_cast<int>(imgIn) << "\n";
  if(imgClassPredicted == imgIn ){
    goodPredictionNum++;
  }
  return (float)(goodPredictionNum)/(float)(totalImgRead)*100;
}

unsigned char arg_max(double softmax_out[10]){
  double max_temp = softmax_out[0];
  unsigned char temp;
  for (unsigned char i = 1; i < 10; i++) {
    if(max_temp < softmax_out[i]){
      max_temp = softmax_out[i];
      temp = i;
    } 
    //cout <<  "\nMax is: " << max_temp << endl;
  }
  cout <<  "\nMax argument is: " << max_temp << endl;
  cout <<  "\nPosition predict is: " << static_cast<int>(temp) << endl;
  return temp;

}


void normalize_image_2(unsigned char buffer[3073], double img_out_red[NB_LIGNE][NB_COLONNE], double img_out_green[NB_LIGNE][NB_COLONNE], double img_out_blue[NB_LIGNE][NB_COLONNE])
{
  int img_in_red[NB_LIGNE][NB_COLONNE];
  int img_in_green[NB_LIGNE][NB_COLONNE];
  int img_in_blue[NB_LIGNE][NB_COLONNE];
  double img_in_R[NB_LIGNE_PLUS][NB_COLONNE_PLUS];
  double img_in_B[NB_LIGNE_PLUS][NB_COLONNE_PLUS];
  double img_in_G[NB_LIGNE_PLUS][NB_COLONNE_PLUS];
  double mu=0,sigma=0;
  int k=1;
  double max_img=0;

  //create a matrix of image input
  for(int ligne=0;ligne<NB_LIGNE_PLUS;ligne++)
    {
      for(int colonne=0;colonne<NB_COLONNE_PLUS;colonne++)
        {
	  img_in_R[ligne][colonne]=(int)buffer[k];
	  k++;
        }
    }
  write_file_32(img_in_R, "Red.txt");
  for(int ligne=0;ligne<NB_LIGNE_PLUS;ligne++)
    {
      for(int colonne=0;colonne<NB_COLONNE_PLUS;colonne++)
        {
	  img_in_G[ligne][colonne]=(int)buffer[k];
	  k++;
        }
    }
  for(int ligne=0;ligne<NB_LIGNE_PLUS;ligne++)
    {
      for(int colonne=0;colonne<NB_COLONNE_PLUS;colonne++)
        {
	  img_in_B[ligne][colonne]=(int)buffer[k];
	  k++;
        }
    }

  //Foramt image 24x24
  for(int ligne=4;ligne<NB_LIGNE;ligne++){
    for(int colonne=4;colonne<NB_COLONNE;colonne++){
      img_in_red[ligne][colonne]=img_in_R[ligne][colonne];
    }
  }

  for(int ligne=4;ligne<NB_LIGNE;ligne++){
    for(int colonne=4;colonne<NB_COLONNE;colonne++){
      img_in_green[ligne][colonne]=img_in_G[ligne][colonne];
    }
  }

  for(int ligne=4;ligne<NB_LIGNE;ligne++){
    for(int colonne=4;colonne<NB_COLONNE;colonne++){
      img_in_blue[ligne][colonne]=img_in_B[ligne][colonne];
    }
  }

  //calcul de la moyenne, ecart type
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      mu+=img_in_red[ligne][colonne];
    }
  }
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      mu+=img_in_green[ligne][colonne];
    }
  }
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      mu+=img_in_blue[ligne][colonne];
    }
  }
  mu=mu/(NB_COLONNE*NB_LIGNE*3);

  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      sigma+=pow((img_in_red[ligne][colonne]-mu),2);
    }
  }
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      sigma+=pow((img_in_green[ligne][colonne]-mu),2);
    }
  }
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      sigma+=pow((img_in_blue[ligne][colonne]-mu),2);
    }
  }
  sigma=sqrt(sigma/(NB_LIGNE*NB_COLONNE*3));


  //calcul image out
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      img_out_red[ligne][colonne]=(img_in_red[ligne][colonne]-mu)/max_func(sigma,1/sqrt(NB_LIGNE*NB_COLONNE));
      if(img_out_red[ligne][colonne]>1)
	img_out_red[ligne][colonne]=1;
      else if(img_out_red[ligne][colonne]<-1)
	img_out_red[ligne][colonne]=-1;

    }
  }
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      img_out_green[ligne][colonne]=(img_in_green[ligne][colonne]-mu)/max_func(sigma,1/sqrt(NB_LIGNE*NB_COLONNE));
      if (img_out_green[ligne][colonne]>1)
	img_out_green[ligne][colonne]=1;
      else if(img_out_green[ligne][colonne]<-1)
	img_out_green[ligne][colonne]=-1;

    }
  }
  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      img_out_blue[ligne][colonne]=(img_in_blue[ligne][colonne]-mu)/max_func(sigma,1/sqrt(NB_LIGNE*NB_COLONNE));
      if(img_out_blue[ligne][colonne]>1)
	img_out_blue[ligne][colonne]=1;
      else if(img_out_blue[ligne][colonne]<-1)
	img_out_blue[ligne][colonne]=-1;
    }
  }


  for(int ligne=0;ligne<NB_LIGNE;ligne++){
    for(int colonne=0;colonne<NB_COLONNE;colonne++){
      max_img=max_func(max_img,img_out_red[ligne][colonne]);
    }
  }
  return ;
}


void readFile(char const *filename){
  //std::ifstream ifs(filename, std::ios::in | std::ios::binary);

  const int number_of_images = 100;
  int channel = 3;
  int rows = 32*32;
  int rgb_data_size = rows * channel;

  vector<vector<double> > images;
  vector<double> labels;
  
  std::ifstream ifs (filename, std::ios::binary);
  for (int i = 0; i < number_of_images; i++) {

    unsigned char label_num;
    unsigned char imgc;
    vector<double> img_f;

    //read label
    ifs.read((char *) &label_num, sizeof(unsigned char));
    labels.push_back((double) label_num);

    //read data
    for (int k = 0; k < rgb_data_size; k++) {
      ifs.read((char *)&imgc, sizeof(unsigned char));
      img_f.push_back((double) imgc);
    }
    images.push_back(img_f);
  }

  ifs.close();
}


int main()
{
  cout<<"Start cifar10 program"<<endl;
  int goodPredictionNum = 0;
  const int number_of_images = 1;
  /**Weight**/
  double coeff_weight1[MAX_KER];unsigned int weight1_size[4]={3,3,3,64};//[3][64][3][3];
  double coeff_weight2[MAX_KER];unsigned int weight2_size[4]={3,3,64,32};//[64][32][3][3];
  double coeff_weight3[MAX_KER];unsigned int weight3_size[4]={3,3,32,20};//[32][20][3][3];
  /**Biases**/
  double coeff_biases1[MAX_BIAS];unsigned int size_biases1=64;//[64];
  double coeff_biases2[MAX_BIAS];unsigned int size_biases2=32;//[32];
  double coeff_biases3[MAX_BIAS];unsigned int size_biases3=20;//[20];
  double coeff_biases4[NB_BIAS_4];unsigned int size_biases4=10;//[10];
  /**Perceptron**/
  double coeff_reshape[number_of_images][180];
  cout<<"Read coefficients"<<endl;
  read_coefficient("./cifardata/CNN_coeff_3x3.txt",
		   coeff_weight1,weight1_size,
		   coeff_weight2,weight2_size,
		   coeff_weight3,weight3_size,
		   coeff_biases1,
		   coeff_biases2,
		   coeff_biases3,
		   coeff_biases4,
		   coeff_reshape);

  cout<<"Read and normalize image"<<endl;
  //  normalize_image("./cifardata/data_batch_1.bin",img_red,img_green,img_blue);

  /*----------------------------------------------------------------------------------------------------*/
  
  int channel = 3;
  int rows = 32*32;
  int rgb_data_size = rows * channel;

  vector<vector<double> > images;
  vector<double> labels;
  unsigned char buffer[number_of_images][3073]; 
  std::ifstream ifs ("./cifardata/data_batch_1.bin", std::ios::binary);
  for (int i = 0; i < number_of_images; i++) {

    unsigned char label_num;
    unsigned char imgc;
    vector<double> img_f;


    //read label
    ifs.read((char *) &label_num, sizeof(unsigned char));
    buffer[i][0] =  label_num;
    //labels.push_back((double) label_num);
    //read data
    for (int k = 0; k < rgb_data_size; k++) {
      ifs.read((char *)&imgc, sizeof(unsigned char));
      //img_f.push_back((double) imgc);
      buffer[i][k+1] = imgc; 
    }
    //images.push_back(img_f);
  }

  ifs.close();
  
  /*----------------------------------------------------------------------------------------------------*/
  unsigned char buffer_1D[3073];
  for (int i = 0; i < number_of_images; i++) {
    for(int j = 0; j < 3073; j++){
      buffer_1D[j] = buffer[i][j];
    }
    std::cout << "Lan thu " << i << "\n";
    double matrix_in[MAX_IM];
 
    double conv_out1[MAX_IM];
    double conv_out2[MAX_IM];
    double conv_out3[MAX_IM];
    double pool_out1[MAX_IM];
    double pool_out2[MAX_IM];
    double pool_out3[MAX_IM];
    double reshape_out[180];
    double matprod_out[10];
    double softmax_out[10];
    unsigned int sig_size[3]={24,24,3};

    double img_red[NB_LIGNE][NB_COLONNE];
    double img_green[NB_LIGNE][NB_COLONNE];
    double img_blue[NB_LIGNE][NB_COLONNE];

    normalize_image_2(buffer_1D,img_red,img_green,img_blue);
    // normalize_image("./cifardata/data_batch_1.bin",img_red,img_green,img_blue);
    for(int L=0;L<24;L++)
      {
	for(int C=0;C<24;C++)
	  {
	    matrix_in[L*3+C*3*24]=img_red[L][C];
	    matrix_in[1+L*3+C*3*24]=img_green[L][C];
	    matrix_in[2+L*3+C*3*24]=img_blue[L][C];
	  }
      }
    write_file(img_blue, "blue.txt");
    write_file(matrix_in);
    cout<<"Layer1"<<endl;
    /***LAYER 1***/
    convolve(matrix_in,conv_out1,coeff_weight1,coeff_biases1,sig_size,weight1_size,size_biases1);
    cout << "Convolution1 Done" << endl;
    relu(conv_out1);
    cout << "Relu1 Done" << endl;
    maxpool(conv_out1,pool_out1,sig_size,2,3);
    cout << "Maxpool1 Done" << endl;
    /***LAYER 2***/
    convolve(pool_out1,conv_out2,coeff_weight2,coeff_biases2,sig_size,weight2_size,size_biases2);
    cout << "Convolution2 Done" << endl;
    relu(conv_out2);
    cout << "Relu2 Done" << endl;
    maxpool(conv_out2,pool_out2,sig_size,2,3);
    cout << "Maxpool2 Done" << endl;

    /***LAYER 3***/
    convolve(pool_out2,conv_out3,coeff_weight3,coeff_biases3,sig_size,weight3_size,size_biases3);
    cout << "Convolution3 Done" << endl;
    relu(conv_out3);
    cout << "Relu3 Done" << endl;
    maxpool(conv_out3,pool_out3,sig_size,2,3);
    cout << "Maxpool3 Done" << endl;
    /**FULLY CONNECTED LAYER**/
    reshape(pool_out3,reshape_out);
    matrix_product(reshape_out,matprod_out,coeff_reshape,coeff_biases4);
    softmax(matprod_out,softmax_out);
    cout<<endl;
    for(int i=0;i<10;i++){cout<<i<<":"<<" "<<100*softmax_out[i]<<"% ";}
    cout<<endl;
    cout<<"End cifar10 program"<<endl;
    unsigned char predict = arg_max(softmax_out);
    std::cout << "Accurancy: " << accuracy(buffer_1D[0], predict, goodPredictionNum, i) << "\n";
  }
  return 0;
}
