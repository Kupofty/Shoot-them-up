#ifndef POSITION_H
#define POSITION_H

#include "InitVariables.h"

//-----------------------------------------------------------------------------------------------------------------------
//fonctions affichage dynamique
void position_souris(double & x, double & y,CImgDisplay &fenetre){
    x=fenetre.mouse_x();    //recupere la position de la souris
    y=fenetre.mouse_y();}

void affiche_personnage(CImg<unsigned char> & jeu, Joueur joueur, int nbr_ennemi_tue){
    int y=600; //hauteur du vaisseau = fixe
    double x = joueur.x_joueur;
    jeu.draw_triangle(x-50,y+25,x,y-50,x+50,y+25,couleur[ couleur_vaisseau ],1);

    if(joueur.nombre_de_vie>=1){
        jeu.draw_rectangle(x-50,y+30,x-20,y+35,couleur[2],1);
        jeu.draw_rectangle(x-51,y+29,x-19,y+36,couleur[1],1,~0U);

        if(joueur.nombre_de_vie>=2){
            jeu.draw_rectangle(x-15,y+30,x+15,y+35,couleur[2],1);
            jeu.draw_rectangle(x-16,y+29,x+16,y+36,couleur[1],1,~0U);        //affiche le nombre de vie restant a l'ecran

            if(joueur.nombre_de_vie==3){
                jeu.draw_rectangle(x+20,y+30,x+50,y+35,couleur[2],1);
                jeu.draw_rectangle(x+19,y+29,x+51,y+36,couleur[1],1,~0U);}}}


    jeu.draw_rectangle(x-50,y+40,x+50,y+45,couleur[1],1,~0U); //barre de chargement attaque speciale
    if(nbr_ennemi_tue<100)
        jeu.draw_rectangle(x-49,y+41,x-49+nbr_ennemi_tue,y+44,couleur[2],1);
    else
        jeu.draw_rectangle(x-49,y+41,x+49,y+44,couleur[2],1);}

void position_personnage(double x, Joueur & joueur){
    if(x!=-1)       //pour pas que le perso parte a une extremite de l'ecran quand la souris sort de l'ecran
        joueur.x_joueur=x;
    joueur.y_sommet_joueur=500;}


#endif // POSITION_H
