
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "Normalize.hpp"
using namespace std;



double max_func(double a,double b)
{
    if(a<b)
        return b;
    else
        return a;
}
/*Normalize image */
void normalize_image(std::string image, double img_out_red[NB_LIGNE][NB_COLONNE], double img_out_green[NB_LIGNE][NB_COLONNE], double img_out_blue[NB_LIGNE][NB_COLONNE])
{
    FILE* img_in_bin =fopen("data_batch_1.bin","rb") ;
    int img_in_red[NB_LIGNE][NB_COLONNE];
    int img_in_green[NB_LIGNE][NB_COLONNE];
    int img_in_blue[NB_LIGNE][NB_COLONNE];
    double img_in_R[NB_LIGNE_PLUS][NB_COLONNE_PLUS];
    double img_in_B[NB_LIGNE_PLUS][NB_COLONNE_PLUS];
    double img_in_G[NB_LIGNE_PLUS][NB_COLONNE_PLUS];
    double mu=0,sigma=0;
    int k=1;
    double max_img=0;


    size_t Taille;
    unsigned char buffer[3073];

    if(img_in_bin==NULL)
    {
        printf("Error ! Can not open file!\n");
        return ;
    }
    printf("Read image in function normalize_image\n");
        Taille=fread(buffer,sizeof(unsigned char),3073,img_in_bin);
    fclose(img_in_bin);

    //create a matrix of image input
    for(int ligne=0;ligne<NB_LIGNE_PLUS;ligne++)
    {
        for(int colonne=0;colonne<NB_COLONNE_PLUS;colonne++)
        {
            img_in_R[ligne][colonne]=(int)buffer[k];
            k++;
        }
    }
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
