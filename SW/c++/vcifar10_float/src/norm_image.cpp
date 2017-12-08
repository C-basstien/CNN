#include "../headers/main.hpp"
double*** troncature_image(double ***im,unsigned int* im_size)
{
    unsigned int size[3]={24,24,3};
    double ***troncated_im=alloc_matrix(size);
    for(unsigned int c=0;c<3;c++)
    {

        for(unsigned int i=0;i<24;i++)
        {
            for(unsigned int j=0;j<24;j++)
            {
                unsigned int ii=(unsigned int)(i-12+im_size[0]/2);/***Attention vérifier le centrage de ces indices*/
                unsigned int jj=(unsigned int)(j-12+im_size[1]/2);
                troncated_im[i][j][c]=im[ii][jj][c];
            }

        }

    }
    return troncated_im;
}
double*** norm_image(double ***im,unsigned int* im_size)
{
    double ***normed_image=alloc_matrix(im_size);
    double mean[3];
    double var[3];
    double max=0;

    /***Calcul de la moyenne des pixels par canal*/
    for(unsigned int c=0;c<3;c++)
    {
        for(unsigned int i=0;i<im_size[0];i++)
        {
            for(unsigned int j=0;j<im_size[1];j++)
            {
                mean[c]=mean[c]+im[i][j][c];
            }
        }
         mean[c]= mean[c]/(im_size[0]*im_size[1]);
    }


    /***Calcul de la variance des pixels par canal*/
    for(unsigned int c=0;c<3;c++)
    {
        for(unsigned int i=0;i<im_size[0];i++)
        {
            for(unsigned int j=0;j<im_size[1];j++)
            {
                var[c]=var[c]+(mean[c]-im[i][j][c])*(mean[c]-im[i][j][c]);
            }
        }
        var[c]= sqrt(var[c]/(im_size[0]*im_size[1]));
    }
    for(unsigned int c=0;c<3;c++)
    {
        if(var[c]>1/sqrt(24*24)){max=var[c];}
        else{max=1/sqrt(24*24);}
        for(unsigned i=0;i<im_size[0];i++)
        {
            for( unsigned int j=0;j<im_size[1];j++)
            {
                normed_image[i][j][c]=(normed_image[i][j][c]-mean[c])/max;
            }
        }
    }
    return normed_image;
}
