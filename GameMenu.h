#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "InitVariables.h"
#include "Ennemy.h"

//---------------------------------------------------------------------
void game_over(Joueur & joueur,int& nbr_ennemi_tue, bool& tir_alternatif){
    if(joueur.nombre_de_vie==0){
        afficher_jeu=false;     //si plus de vie = game over
        afficher_game_over=true;
        nbr_ennemi_tue=0;
        tir_alternatif=false;
        joueur.nombre_de_vie=nombre_vie;}}

void modification_high_score(vector<int> & liste_high_score, int score){
    if(score>=liste_high_score[0]){ //modifie les 3 meilleurs scores enregistres
        liste_high_score[2]=liste_high_score[1];
        liste_high_score[1]=liste_high_score[0];
        liste_high_score[0]=score;}

    else if(score<liste_high_score[0] and score>=liste_high_score[1]){
        liste_high_score[2]=liste_high_score[1];
        liste_high_score[1]=score;}

    else if (score<liste_high_score[1] and score>=liste_high_score[2])
        liste_high_score[2]=score;}

void affiche_ennemi_accueil(CImgDisplay &fenetre, CImg<unsigned char> & jeu, vector<Ennemi> & Liste_accueil){
    int score_accueil;  //sert juste pour mettre dans les fonctions sans affecter le vrai score
    ennemi(Liste_accueil,6);
    bouger_ennemi(Liste_accueil,score_accueil);        //fait defiler les ennemis sur l'ecran d'accueil = decoration
    affiche_ennemi(jeu,Liste_accueil);
    fenetre.display(jeu);}



#endif // GAMEMENU_H
