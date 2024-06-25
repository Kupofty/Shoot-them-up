#ifndef INITVARIABLES_H
#define INITVARIABLES_H

#include <vector>
#include <time.h>
#include "CImg.h"
#include "Structs.h"

using namespace std;
using namespace cimg_library;

int hauteur_fenetre=650; //parametres taille fenetre
int largeur_fenetre=500;
//-------------------------------------------------
bool afficher_menu=true;
bool afficher_jeu=false;
bool afficher_commandes=false;  //conditions pour les boucles whiles / changements de page
bool afficher_credits=false;
bool afficher_reglages=false;
bool afficher_game_over=false;
bool afficher_production=true;
//-------------------------------------------------
int score=0;
int nbr_ennemi_tue=0; //pour le tir special (tuer x ennemi avant de le declencher)
vector<int> liste_high_score={0,0,0};
//-------------------------------------------------
bool tir_alternatif=false;
double temps_cooldown=4; //temps minimal entre les tirs
int tic_tir_secondaire=2000; //duree bonus tir secondaire
//-------------------------------------------------
int difficulte=4; //par defaut = facile
int nombre_vie=3;//par defaut
//-------------------------------------------------
double x; //position souris sur l'ecran
double y;
//-------------------------------------------------
int couleur_vaisseau=1; //noir par defaut

unsigned char couleur[10][3]{ //liste des couleurs disponibles
    {255,255,255},//blanc
    {0,0,0},//noir
    {255,0,0},//rouge
    {0,255,0}, // vert
    {0,0,255}, // bleu
    {0,180,255}, //bleu ciel
    {148,0,211}, // violet
    {75,0,130}, // indigo
    {255,127,0}, // orange
    {100,149,237}}; //cornflowerblue


#endif // INITVARIABLES_H
