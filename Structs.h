#ifndef STRUCTS_H
#define STRUCTS_H

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* +++++++++++++++++++++++++++++++++++++ */
/* +++ Initialisation des structures +++ */
/* +++++++++++++++++++++++++++++++++++++ */

struct Joueur{
        double x_joueur;
        double y_sommet_joueur;
        int nombre_de_vie=3;}; // par defaut

struct Balle{
        double x_balle;
        double y_balle;
        double vitesse_balle;
        int taille_balle;};

struct Ennemi{
        double x_ennemi;
        double y_ennemi;
        double vitesse_ennemi;
        int couleur_ennemi;
        int taille_ennemi;
        int forme_ennemi;};

struct Bonus{
        double x_bonus;
        double y_bonus;
        double vitesse_bonus;
        int taille_bonus;
        int type;}; //bonus vie ou arme



#endif // STRUCTS_H
