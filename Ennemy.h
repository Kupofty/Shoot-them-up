#ifndef ENNEMY_H
#define ENNEMY_H


#include "InitVariables.h"

//---------------------------------------------------------------------
//ENNEMIS
void ennemi(vector<Ennemi> & liste_ennemi,int difficulte){ //modifier la frequence d'apparition sur pc LINUX
    double aleatoire=rand()%(difficulte*50); //frequence d'apparition augmente avec la difficulte (difficulte qui baisse = reduit le nombre aleatoire et augmente la probabilite de creer un ennemi et inversement)
    if(aleatoire<=1){   //condition pour creer un ennemi
        Ennemi ennemi;
        ennemi.x_ennemi=10+rand()%475;
        ennemi.y_ennemi=80 ;
        ennemi.vitesse_ennemi=0.5;
        ennemi.couleur_ennemi=rand()%10+1;
        ennemi.taille_ennemi=15;

        double forme_aleatoire=rand()%30;       //forme aleatoire
        if(forme_aleatoire<=10)
            ennemi.forme_ennemi=1; // cercle
        else if(forme_aleatoire<=20)
            ennemi.forme_ennemi=2; //carre
        else if(forme_aleatoire<=30)
            ennemi.forme_ennemi=3; //triangle

        liste_ennemi.push_back(ennemi);}} //ajoute l'ennemi a la liste

void affiche_ennemi(CImg<unsigned char> & jeu , vector<Ennemi> & liste_ennemi){
    for(Ennemi ennemi : liste_ennemi){        //parcourt la liste des ennemis pour les afficher
        if(ennemi.forme_ennemi==1)
            jeu.draw_circle(ennemi.x_ennemi,ennemi.y_ennemi,ennemi.taille_ennemi,couleur[ennemi.couleur_ennemi],1);

        if(ennemi.forme_ennemi==2)
            jeu.draw_rectangle(ennemi.x_ennemi-ennemi.taille_ennemi,ennemi.y_ennemi-ennemi.taille_ennemi,ennemi.x_ennemi+ennemi.taille_ennemi,ennemi.y_ennemi+ennemi.taille_ennemi,couleur[ennemi.couleur_ennemi],1);

        if(ennemi.forme_ennemi==3)
            jeu.draw_triangle(ennemi.x_ennemi-ennemi.taille_ennemi,ennemi.y_ennemi+ennemi.taille_ennemi,ennemi.x_ennemi,ennemi.y_ennemi+2*ennemi.taille_ennemi+10,ennemi.x_ennemi+ennemi.taille_ennemi,ennemi.y_ennemi+ennemi.taille_ennemi,couleur[ ennemi.couleur_ennemi],1);}}

void bouger_ennemi(vector<Ennemi> & liste_ennemi,int & score){
    for(int i=0;i<liste_ennemi.size();++i){     //parcourt la liste des ennemis pour modifier les coordonees pour les faire bouger
        liste_ennemi[i].y_ennemi += liste_ennemi[i].vitesse_ennemi;
        if(liste_ennemi[i].y_ennemi>650){
            liste_ennemi.erase(liste_ennemi.begin()+i);         //deplace l'ennemi et enleve 1000pts si l'ennemi atteint l'ecran du bas
            score-=1000;}}}

void collision_ennemi_joueur(vector<Ennemi>& liste_ennemi, Joueur & joueur){
    for(int i=0;i<liste_ennemi.size();++i)          //parcourt liste ennemi pour verifier les conditions de collision de chacun des ennemis avec le joueur
        if(liste_ennemi[i].y_ennemi-liste_ennemi[i].taille_ennemi-10>= joueur.y_sommet_joueur )
            if(liste_ennemi[i].x_ennemi >= joueur.x_joueur-45 and liste_ennemi[i].x_ennemi <= joueur.x_joueur +45 ){
                liste_ennemi.erase(liste_ennemi.begin()+i);     //si un ennemi touche le joueur, l'ennemi disparait et le joueur perd 1 vie
                joueur.nombre_de_vie-=1;}}

#endif // ENNEMY_H
