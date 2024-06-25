#ifndef BUTTONS_H
#define BUTTONS_H

#include "InitVariables.h"

//-----------------------------------------------------------------------------------------------------------------------
//fonctions boutons
void bouton(int x1, int y1, int x2, int y2, bool& devient_faux, bool& devient_vrai,CImgDisplay &fenetre,vector<Ennemi> & Liste_accueil){
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2 )        //quand on clique sur le rectangle defini par les coordonnees x et y, on change la valeur des bool pour changer de page
    {Liste_accueil.clear();
        devient_faux=false;
        devient_vrai=true;}}

void bouton_quitter(int x1, int y1, int x2, int y2,CImgDisplay &fenetre){
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2 )
        exit(0);} //appuyer sur la croix pour fermer completement le jeu

void bouton_quitter_jeu(int x1, int y1, int x2, int y2, bool& devient_faux, bool& devient_vrai,int & score,vector<Balle> & Liste_balle, vector<Ennemi>& Liste_ennemi,vector<Bonus> Liste_bonus,CImgDisplay &fenetre,bool& tir_alternatif,int& nbr_ennemi_tue){
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2){//pour retourner au menu
        devient_faux=false;
        devient_vrai=true;
        score=0;
        Liste_ennemi.clear();       //on reinitialise tout si on quitte le jeu
        Liste_balle.clear();
        Liste_bonus.clear();
        tir_alternatif=false;
        nbr_ennemi_tue=0;}}

void bouton_quitter_game_over(int x1, int y1, int x2, int y2, bool& devient_faux, bool& devient_vrai,int & score,CImgDisplay &fenetre){
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2 )
    {devient_faux=false;
        devient_vrai=true;      //on reinitialise le score avant de quitter le jeu
        score=0;}}

void bouton_couleur_vaisseau(int x1, int y1, int x2, int y2,int& couleur_vaisseau, int valeur,CImgDisplay &fenetre){
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2)     //quand on clique sur un des boutons de l'ecran, on change la couleur du vaisseau
        couleur_vaisseau=valeur;}

void bouton_choix_nombre_vie(int x1, int y1, int x2, int y2,int & nombre_vie, int valeur, Joueur & joueur,CImgDisplay &fenetre){
    if(fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2)        //quand on clique sur le nombre de vie desiree, ca affecte la valeur au personnage
    {nombre_vie=valeur;
        joueur.nombre_de_vie=valeur;}}

void bouton_choix_difficulte(int x1, int y1, int x2, int y2,int & difficulte, int valeur, CImgDisplay &fenetre){
    if(fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2)      //changer la difficulte du jeu quand on appuie sur les boutons
        difficulte=valeur;}


#endif // BUTTONS_H
