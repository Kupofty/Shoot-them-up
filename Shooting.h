#ifndef SHOOTING_H
#define SHOOTING_H

#include "InitVariables.h"

//---------------------------------------------------------------------
//TIR
void cool_down(double& temps_cooldown){
    if(temps_cooldown>0)        //reduit le cooldown pour pouvoir tirer a nouveau
        temps_cooldown-=0.1;}

void tir(int x,int y,CImgDisplay &fenetre, vector<Balle> & liste_balle, double & temps_cooldown,bool tir_alternatif){
    if (fenetre.button()&1 and y>=65 and temps_cooldown<=0){        //si clic gauche et cooldown ok : on peut tirer
        if(!tir_alternatif){
            Balle balle;
            balle.vitesse_balle=2;
            balle.x_balle=x;
            balle.y_balle=545;
            balle.taille_balle=5;
            liste_balle.push_back(balle); //cree une balle dans une liste si on tire
            temps_cooldown=4;}}}

void tir_secondaire(int x,int y,CImgDisplay &fenetre, vector<Balle> & liste_balle, double & temps_cooldown,bool & tir_alternatif,int & tic_tir_secondaire){
    if (fenetre.button()&1 and y>=65 and temps_cooldown<=0){
        if(tir_alternatif){
            for(int i=-15;i<=15;i+=15){     //tir alternatif grace au bonus : 3 balles a la fois
                Balle balle;
                balle.vitesse_balle=2;
                balle.x_balle=x+i;
                balle.y_balle=545;
                balle.taille_balle=5;
                liste_balle.push_back(balle);}
            temps_cooldown=4;}}

    tic_tir_secondaire-=1;
    if(tic_tir_secondaire<=0){
        tir_alternatif=false;       //fin du bonus avec un certain temps
        tic_tir_secondaire=2000;}}

void tir_special(int x,int y,CImgDisplay &fenetre, vector<Balle> & liste_balle, vector<Ennemi> & liste_ennemi, int & nbr_ennemi_tue, int & score){
    if(fenetre.button()&2 and nbr_ennemi_tue>=100) {    //tir special si clic droit et barre d'attaque speciale chargee a fond

        nbr_ennemi_tue=0;   //on reinitialise la barre d'attaque speciale
        score+= 100*liste_ennemi.size(); //on gagne 100 pts * nombre d'ennemi tue sur l'ecran
        liste_ennemi.clear();}}//tue tous les ennemis

void affiche_tir(CImg<unsigned char> & jeu , vector<Balle> & liste_balle){
    for(Balle balle : liste_balle)
        jeu.draw_circle(balle.x_balle,balle.y_balle,balle.taille_balle,couleur[couleur_vaisseau],1);}

void bouger_balle(vector<Balle> & liste_balle){
    for(int i=0;i<liste_balle.size();++i){
        liste_balle[i].y_balle -= liste_balle[i].vitesse_balle;  //diminue la position y pour faire monter la balle
        if(liste_balle[i].y_balle<75)
            liste_balle.erase(liste_balle.begin()+i);}} //efface element de la liste si la balle sort de l'ecran

void collision_balle_ennemi(vector<Balle> & liste_balle,vector<Ennemi>& liste_ennemi, int & score, int & nbr_ennemi_tue, int difficulte){
    for(int i=0;i<liste_balle.size();++i)       //on parcourt la liste pour venir verifier les conditions de collision de chacune des balles avec chacun des ennemis
        for(int j=0;j<liste_ennemi.size();++j)
            if(liste_balle[i].y_balle-liste_balle[i].taille_balle<=liste_ennemi[j].y_ennemi+liste_ennemi[j].taille_ennemi)
                if(liste_balle[i].x_balle >= liste_ennemi[j].x_ennemi-liste_ennemi[j].taille_ennemi and liste_balle[i].x_balle <= liste_ennemi[j].x_ennemi+liste_ennemi[j].taille_ennemi ){
                    liste_balle.erase(liste_balle.begin()+i);       //si la balle touche un ennemi, la balle et l'ennemi disparaissent
                    liste_ennemi.erase(liste_ennemi.begin()+j);
                    nbr_ennemi_tue+=1;
                    if(difficulte==4)
                        score+=25;
                    else if(difficulte==3)
                        score+=50;
                    else if(difficulte==2)          //selon la difficulte on gagne plus ou moins de points
                        score+=100;
                    else if(difficulte==1)
                        score+=250;}}

#endif // SHOOTING_H
