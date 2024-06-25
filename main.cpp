//Generic libraries
#include <iostream>
#include "CImg.h"

//Custom libraries
#include "InitVariables.h"
#include "DisplayFunctions.h"
#include "Buttons.h"
#include "Bonus.h"
#include "Ennemy.h"
#include "GameMenu.h"
#include "Position.h"
#include "Shooting.h"




//// Main ////
int main(){

    /*Initialisation des variables locales au main()*/
    Joueur joueur;    //on cree le joueur
    vector<Ennemi> Liste_accueil; //pour gerer les ennemis sur l'ecran d'accueil
    srand(time(nullptr)); //pour creer des chiffres aleatoires

    /* ======================================== */
    /* === Creation de la fenetre graphique === */
    /* ======================================== */
    CImg<unsigned char> jeu(largeur_fenetre,hauteur_fenetre,1,3);
    CImgDisplay fenetre(jeu,"The War Of Geometry Shapes");

    //---------------------------------------------------------------------
    while(not fenetre.is_closed()){ //pour faire tourner le jeu tant que la fenetre est ouverte

        /* =================== */
        /* === Menu du jeu === */
        /* =================== */

        if(afficher_production){ //affiche la production
            affiche_ecran_production(jeu,fenetre);
            afficher_production=false;
            afficher_menu=true;}

        while(afficher_menu){ //affiche le menu
            affiche_ecran_accueil(jeu,x,y); //affiche tous les elements visuels de l'ecran d'accueil
            position_souris(x,y,fenetre); //recupere la position de la souris sur l'ecran

            //si on clique sur un des boutons de l'ecran on bascule de l'ecran du menu a l'ecran souhaite
            bouton(170,190,310,270,afficher_menu,afficher_jeu,fenetre,Liste_accueil);
            bouton(110,310,380,380,afficher_menu,afficher_commandes,fenetre,Liste_accueil);
            bouton(110,420,400,485,afficher_menu,afficher_reglages,fenetre,Liste_accueil);
            bouton(160,520,320,580,afficher_menu,afficher_credits,fenetre,Liste_accueil);

            //pluie d'ennemi (decoratif)
            affiche_ennemi_accueil(fenetre,jeu,Liste_accueil);

            //si on clique sur la croix on ferme la fenetre
            bouton_quitter(420,570,480,630,fenetre);}

        //---------------------------------------------------------------------
        while (afficher_commandes){ //affiche la page des commandes
            position_souris(x,y,fenetre);
            affiche_ecran_commandes(jeu,fenetre,x,y);
            bouton(15,20,100,70,afficher_commandes,afficher_menu,fenetre,Liste_accueil);}

        //---------------------------------------------------------------------
        while(afficher_reglages) {// affiche la page des customisations
            position_souris(x,y,fenetre);
            affiche_ecran_reglage(jeu,fenetre,difficulte,nombre_vie,couleur_vaisseau,x,y);
            bouton(15,20,100,70,afficher_reglages,afficher_menu,fenetre,Liste_accueil);

            //----------------------------------------------------------------------
            //boutons pour choix couleur vaisseau
            bouton_couleur_vaisseau(70,180,120,230,couleur_vaisseau,2,fenetre); //rouge
            bouton_couleur_vaisseau(170,180,220,230,couleur_vaisseau,3,fenetre);//vert
            bouton_couleur_vaisseau(270,180,320,230,couleur_vaisseau,5,fenetre);//bleu
            bouton_couleur_vaisseau(370,180,420,230,couleur_vaisseau,1,fenetre); //noir

            //----------------------------------------------------------------------
            //boutons pour choix nombre vie
            bouton_choix_nombre_vie(60,305,150,360,nombre_vie,1,joueur,fenetre); //1 vie
            bouton_choix_nombre_vie(210,305,300,360,nombre_vie,2,joueur,fenetre); //2 vie
            bouton_choix_nombre_vie(360,305,450,360,nombre_vie,3,joueur,fenetre); //3 vie

            //----------------------------------------------------------------------
            //boutons pour choix difficulte
            bouton_choix_difficulte(80,460,230,510,difficulte,4,fenetre);// tres facile
            bouton_choix_difficulte(260,460,410,510,difficulte,3,fenetre);//facile
            bouton_choix_difficulte(80,535,230,585,difficulte,2,fenetre);//moyen
            bouton_choix_difficulte(260,535,410,585,difficulte,1,fenetre);}//difficile

        //---------------------------------------------------------------------
        if(afficher_credits){  //affiche la page des credits
            affiche_ecran_credits(jeu,fenetre);
            afficher_credits=false;
            afficher_menu=true;}


        //---------------------------------------------------------------------
        /* =========== */
        /* === Jeu === */
        /* ============ */
        vector<Balle> Liste_balle; //liste qui contient les balles (positions, vitesse)
        vector<Ennemi> Liste_ennemi; // liste qui va contenir les ennemis (//)
        vector<Bonus> Liste_bonus; //liste qui va contenir les bonus (//)


        while(afficher_jeu){
            fenetre.wait(10);       //taux de rafraichissement (pour eviter les impressions de ralentissement sur certains pc)
            //-------------------------------------
            position_souris(x,y,fenetre);
            bouton_quitter_jeu(15,20,100,70,afficher_jeu,afficher_menu,score,Liste_balle,Liste_ennemi,Liste_bonus,fenetre,tir_alternatif,nbr_ennemi_tue);     //bouton pour retourner au menu et tout reinitialiser
            game_over(joueur,nbr_ennemi_tue,tir_alternatif);     //fin de la partie quand on a epuise les 3 vies
            //-------------------------------------
            affiche_ecran_jeu(jeu,difficulte); //affiche ecran arriere (fond + bouton + score + difficulte)
            dessiner_ecran_jeu(jeu);            //affiche cadrillage
            //-------------------------------------
            position_personnage(x,joueur);
            affiche_personnage(jeu, joueur,nbr_ennemi_tue); //affiche le vaisseau du joueur
            //-------------------------------------
            cool_down(temps_cooldown);                              //cooldown pour pas tirer trop vite
            tir(x,y, fenetre, Liste_balle,temps_cooldown,tir_alternatif);          // gere la liste des positions des balles
            tir_secondaire(x,y,fenetre,Liste_balle,temps_cooldown,tir_alternatif,tic_tir_secondaire); //tir 3 balles par 3 balles grece au bonus
            tir_special(x,y,fenetre,Liste_balle,Liste_ennemi,nbr_ennemi_tue,score);           //detruit tout les ennemis de l'ecran (necessite 100 kills)
            affiche_tir(jeu, Liste_balle);                          // affiche les balles
            bouger_balle(Liste_balle);                              //et gere leurs deplacements
            collision_balle_ennemi(Liste_balle,Liste_ennemi,score,nbr_ennemi_tue,difficulte); //gere la collision entre les balles et les ennemis
            //-------------------------------------
            ennemi(Liste_ennemi,difficulte);            //gere la liste d'ennemis
            affiche_ennemi(jeu,Liste_ennemi);     //affiche les ennemis
            bouger_ennemi(Liste_ennemi,score);                //et gere leurs deplacements
            collision_ennemi_joueur(Liste_ennemi,joueur); //gere la collision ennemi/joueur
            //-------------------------------------
            bonus(fenetre,Liste_bonus);
            affiche_bonus(fenetre,jeu,Liste_bonus);                  // +1vie si on a pas le nbr de vie max (definie dans les parametre) sinon +500pts
            bouger_bonus(fenetre,Liste_bonus,score);                 // bonus tir = tire 3 balles par coup (temps limite)
            collision_bonus_joueur(Liste_bonus,joueur,tir_alternatif);
            //-------------------------------------
            jeu.display(fenetre);} //affiche fenetre jeu

        //------------------------------------------------------------------------------------------
        modification_high_score(liste_high_score,score); //on change la liste des high score avant d'afficher la page game_over
        //------------------------------------------------------------------------------------------

        while(afficher_game_over ){
            position_souris(x,y,fenetre);
            affiche_ecran_game_over(jeu,fenetre,score,liste_high_score,x,y);
            bouton_quitter_game_over(15,20,100,70,afficher_game_over,afficher_menu,score,fenetre); //si on clique sur la fleche de retour on retourne au menu
            bouton_quitter_game_over(200,540,310,590,afficher_game_over,afficher_jeu,score,fenetre);}}} //si on clique sur rejouer , ca relance une nouvelle partie
