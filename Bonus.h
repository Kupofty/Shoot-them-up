#ifndef BONUS_H
#define BONUS_H


#include "InitVariables.h"


//--------------------------------------------------------------------
//BONUS
void bonus(CImgDisplay &fenetre,vector<Bonus> & liste_bonus){
    double nbr_aleatoire=rand()%10000; //taux d'apparition

    Bonus bonus;
    bonus.x_bonus=10+rand()%475;
    bonus.y_bonus=80;
    bonus.vitesse_bonus=0.5;
    bonus.taille_bonus=15;

    if(nbr_aleatoire<=1){
        bonus.type=1; //bonus vie
        liste_bonus.push_back(bonus);}
    if(nbr_aleatoire >=9996){
        bonus.type=2; //bonus tir ameliore
        liste_bonus.push_back(bonus);}}

void affiche_bonus(CImgDisplay &fenetre, CImg<unsigned char> & jeu , vector<Bonus> & liste_bonus){
    int largeur=1; //pour changer la taille du coeur
    for(Bonus bonus : liste_bonus){ //affiche les bonus de tir et de vie
        if(bonus.type==1){
            for(int i=0;i<8;++i){//pixel art du coeur
                jeu.draw_rectangle(bonus.x_bonus+i*largeur,bonus.y_bonus+largeur-i*largeur,bonus.x_bonus+i*largeur,bonus.y_bonus-i*largeur,couleur[1]);
                jeu.draw_rectangle(bonus.x_bonus-i*largeur,bonus.y_bonus+largeur-i*largeur,bonus.x_bonus-i*largeur,bonus.y_bonus-i*largeur,couleur[1]);}

            jeu.draw_rectangle(bonus.x_bonus+7*largeur,bonus.y_bonus-10*largeur,bonus.x_bonus+7*largeur,bonus.y_bonus-7*largeur,couleur[1]);
            jeu.draw_rectangle(bonus.x_bonus-7*largeur,bonus.y_bonus-10*largeur,bonus.x_bonus-7*largeur,bonus.y_bonus-7*largeur,couleur[1]);

            jeu.draw_rectangle(bonus.x_bonus-6*largeur,bonus.y_bonus-11*largeur,bonus.x_bonus-6*largeur,bonus.y_bonus-10*largeur,couleur[1]);
            jeu.draw_rectangle(bonus.x_bonus+6*largeur,bonus.y_bonus-11*largeur,bonus.x_bonus+6*largeur,bonus.y_bonus-10*largeur,couleur[1]);

            jeu.draw_rectangle(bonus.x_bonus-5*largeur,bonus.y_bonus-12*largeur,bonus.x_bonus-2*largeur,bonus.y_bonus-12*largeur,couleur[1]);
            jeu.draw_rectangle(bonus.x_bonus+5*largeur,bonus.y_bonus-12*largeur,bonus.x_bonus+2*largeur,bonus.y_bonus-12*largeur,couleur[1]);

            jeu.draw_rectangle(bonus.x_bonus-1*largeur,bonus.y_bonus-11*largeur,bonus.x_bonus-largeur,bonus.y_bonus-12*largeur,couleur[1]);
            jeu.draw_rectangle(bonus.x_bonus+1*largeur,bonus.y_bonus-11*largeur,bonus.x_bonus+largeur,bonus.y_bonus-12*largeur,couleur[1]);

            jeu.draw_rectangle(bonus.x_bonus,bonus.y_bonus-10*largeur,bonus.x_bonus,bonus.y_bonus-11*largeur,couleur[1]);}

        else if(bonus.type==2){
            jeu.draw_circle(bonus.x_bonus,bonus.y_bonus,10,couleur[1],1,~0U);
            jeu.draw_text(bonus.x_bonus-2,bonus.y_bonus-6,"?",1,couleur[0],1,15);}}}

void bouger_bonus(CImgDisplay &fenetre,vector<Bonus> & liste_bonus, int & score){
    for(int i=0;i<liste_bonus.size();++i){      //parcourt la liste des bonus et modifie la coordonee y pour les faire avancer
        liste_bonus[i].y_bonus+=liste_bonus[i].vitesse_bonus;
        if(liste_bonus[i].y_bonus>650)
            liste_bonus.erase(liste_bonus.begin()+i);}}

void collision_bonus_joueur(vector<Bonus>& liste_bonus, Joueur & joueur,bool & tir_alternatif){
    for(int i=0;i<liste_bonus.size();++i)           //parcourt la liste des bonus pour verifier les collisions bonus/joueur et appliquer les effets en cas de collision avec le bonus vie ou tir
        if(liste_bonus[i].y_bonus-liste_bonus[i].taille_bonus -15>= joueur.y_sommet_joueur )
            if(liste_bonus[i].x_bonus +liste_bonus[i].taille_bonus >= joueur.x_joueur-45 and liste_bonus[i].x_bonus - liste_bonus[i].taille_bonus <= joueur.x_joueur+45){
                if(liste_bonus[i].type==1){
                    liste_bonus.erase(liste_bonus.begin()+i);
                    if(joueur.nombre_de_vie<nombre_vie)
                        joueur.nombre_de_vie+=1;
                    else
                        score+=10000;}      //collision coeur = +1vie ou +10000pts si vie max

                else if(liste_bonus[i].type==2){
                    liste_bonus.erase(liste_bonus.begin()+i);
                    tir_alternatif=true;}}}     //collision bonus ? = arme secondaire



#endif // BONUS_H
