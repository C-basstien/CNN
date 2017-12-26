#ifndef NORMALIZE_HPP
#define NORMALIZE_HPP

#define NB_LIGNE_PLUS 32
#define NB_COLONNE_PLUS 32
#define NB_LIGNE 24
#define NB_COLONNE 24

double max_func(double a,double b);
void normalize_image(std::string image, double img_out_red[NB_LIGNE][NB_COLONNE], double img_out_green[NB_LIGNE][NB_COLONNE], double img_out_blue[NB_LIGNE][NB_COLONNE]);

#endif 
