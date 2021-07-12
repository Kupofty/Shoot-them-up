#include <iostream>
#include "CImg.h"
#include <vector>
#include <time.h>
using namespace std;
using namespace cimg_library;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* +++++++++++++++++++ */
/* +++ Notes/idées +++ */
/* +++++++++++++++++++ */

//--------------------------------------------------------------------------------------------------------

/* +++++++++++++++++++++++ */
/* +++ Bugs / Problèmes+++ */
/* +++++++++++++++++++++++ */

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* ++++++++++++++++++++++++++++++++++++ */
/* +++ Variables globales générales +++ */
/* ++++++++++++++++++++++++++++++++++++ */

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
int tic_tir_secondaire=2000; //durée bonus tir secondaire
//-------------------------------------------------
int difficulte=4; //par défaut = facile
int nombre_vie=3;//par défaut
//-------------------------------------------------
double x; //position souris sur l'écran
double y;
//-------------------------------------------------
int couleur_vaisseau=1; //noir par défaut

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


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* +++++++++++++++++++++++++++++++++++++ */
/* +++ Initialisation des structures +++ */
/* +++++++++++++++++++++++++++++++++++++ */

struct Joueur{
    double x_joueur;
    double y_sommet_joueur;
    int nombre_de_vie=3;}; // par défaut

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


//-----------------------------------------------------------------------------------------------------
/* ++++++++++++++++++++++++++++++++++++ */
/* +++ Initialisation des fonctions +++ */
/* ++++++++++++++++++++++++++++++++++++ */

//fonctions affichage statique
void dessine_fond_blanc(CImg<unsigned char> & jeu){
    for (int i=0; i<jeu.width(); ++i)
        for (int j=0; j<jeu.height(); ++j){     //dessine le fond blanc qui servira de support pour dessiner le reste
            jeu(i,j,1)=255;
            jeu(i,j,2)=255;
            jeu(i,j,0)=255;}}

void dessiner_ecran_jeu(CImg<unsigned char> & jeu){
    for (int i=0; i<jeu.width(); i=i+20)
        jeu.draw_line(i+100,80,i+100,650,couleur[9],1);

    for(int i=0;i<jeu.height();i=i+20)                      //dessine le quadrillage de l'écran de jeu (style feuille papier)
        jeu.draw_line(0,i+140,500,i+140,couleur[9],1);

    jeu.draw_line(100,80,100,650,couleur[2],1);}

void affiche_ecran_accueil(CImg<unsigned char> & jeu,CImgDisplay &fenetre,int x, int y){
    dessine_fond_blanc(jeu);

    //affichage des boutons  intéractifs
    jeu.draw_text(100,30,"The War Of",55,couleur[0],1,60);
    jeu.draw_text(30,80,"Geometry Shapes",55,couleur[0],1,60);

    jeu.draw_rectangle (170, 190, 310, 270, couleur[1], 1, 50);
    if(x>170 and x<310 and y>190 and y<270)
        jeu.draw_rectangle (170, 190, 310, 270, couleur[1], 1, ~0U);
    jeu.draw_text(180,200,"Jouer",55,couleur[0],4,60);

    jeu.draw_rectangle (110, 310, 380, 380, couleur[1], 1, 50);
    if(x>110 and x<380 and y>310 and y<380)
        jeu.draw_rectangle (110, 310, 380, 380, couleur[1], 1,~0U);
    jeu.draw_text(120,320,"Commandes",55,couleur[0],4,50);

    jeu.draw_rectangle (140, 420, 350, 485, couleur[1], 1, 50);
    if(x>140 and x<350 and y>420 and y<485)
        jeu.draw_rectangle (140, 420, 350, 485, couleur[1], 1,~0U);
    jeu.draw_text(160,430,"Réglages",55,couleur[0],4,50);

    jeu.draw_rectangle (160, 520, 320, 580, couleur[1], 1, 50);
    if(x>160 and x<320 and y>520 and y<580)
        jeu.draw_rectangle (160, 520, 320, 580, couleur[1], 1, ~0U);
    jeu.draw_text(170,530,"Crédits",55,couleur[0],4,50);

    jeu.draw_rectangle (420, 570, 480, 630, couleur[1], 1,50);
    if(x>420 and x<480 and y>570 and y<630)
        jeu.draw_rectangle (420, 570, 480, 630, couleur[1], 1, ~0U);
    jeu.draw_line(430,580,470,620,couleur[1]);
    jeu.draw_line(470,580,430,620,couleur[1]);}

void affiche_ecran_credits(CImg<unsigned char> & jeu, CImgDisplay &fenetre){
    dessine_fond_blanc(jeu);

    for(int i=650; i>-580;--i){     //fait défiler les crédits
        fenetre.wait(10);
        jeu.draw_text(200,i,"Producteur",55,couleur[0],1,30 );
        jeu.draw_text(200,i+30,"Provost Mathis",55,couleur[0],1,20 );

        jeu.draw_text(200,i+70,"Scénariste",55,couleur[0],1,30 );
        jeu.draw_text(200,i+100,"Provost Mathis",55,couleur[0],1,20 );

        jeu.draw_text(180,i+140,"Programmeur",55,couleur[0],1,30 );
        jeu.draw_text(200,i+170,"Provost Mathis",55,couleur[0],1,20 );

        jeu.draw_text(170,i+210,"Game Designer",55,couleur[0],1,30 );
        jeu.draw_text(200,i+240,"Provost Mathis",55,couleur[0],1,20 );

        jeu.draw_text(160,i+280,"Directeur artistique",55,couleur[0],1,30 );
        jeu.draw_text(200,i+310,"Provost Mathis",55,couleur[0],1,20 );

        jeu.draw_text(150,i+350,"Directeur technique",55,couleur[0],1,30 );
        jeu.draw_text(200,i+380,"Provost Mathis",55,couleur[0],1,20 );

        jeu.draw_text(170,i+420,"Programmeur IA",55,couleur[0],1,30 );
        jeu.draw_text(200,i+450,"Provost Mathis",55,couleur[0],1,20 );
        fenetre.display(jeu);}}

void affiche_ecran_commandes(CImg<unsigned char> & jeu,CImgDisplay &fenetre,int xsouris,int ysouris){
    dessine_fond_blanc(jeu);

    //dessins formes geometriques (rectangles, fleches, instructions,etc)
    jeu.draw_arrow(85,45,25,45,couleur[1],1,30,-40,~0U);
    jeu.draw_rectangle(15,20,100,70,couleur[1],1,60);
    if(xsouris>15 and xsouris<100 and ysouris>20 and ysouris<70)
        jeu.draw_rectangle(15,20,100,70,couleur[1],1,~0U);

    jeu.draw_rectangle(175,150,325,375,couleur[1],1,~0U);
    jeu.draw_rectangle(240,170,260,210,couleur[1],1,~0U);
    jeu.draw_line(175,225,325,225,couleur[1]);
    jeu.draw_line(250,150,250,170,couleur[1]);          //dessin souris
    jeu.draw_line(250,210,250,225,couleur[1]);
    jeu.draw_spline(250,150,200,10,250,50,200,10,couleur[1]);

    jeu.draw_rectangle(350,255,430,290,couleur[1],1,~0U);
    jeu.draw_line(430,255,430,290,couleur[0]);
    jeu.draw_line(430,255,405,230,couleur[1]);      //dessin fleche droite
    jeu.draw_line(405,230,422,213,couleur[1]);
    jeu.draw_line(422,213,481,272,couleur[1]);
    jeu.draw_line(430,290,405,315,couleur[1]);
    jeu.draw_line(405,315,422,332,couleur[1]);
    jeu.draw_line(422,332,481,273,couleur[1]);

    jeu.draw_rectangle(150,255,70,290,couleur[1],1,~0U);
    jeu.draw_line(70,255,70,290,couleur[0]);
    jeu.draw_line(70,255,95,230,couleur[1]);      //dessin fleche gauche
    jeu.draw_line(95,230,78,213,couleur[1]);
    jeu.draw_line(78,213,19,272,couleur[1]);
    jeu.draw_line(70,290,95,315,couleur[1]);
    jeu.draw_line(95,315,78,332,couleur[1]);
    jeu.draw_line(78,332,19,273,couleur[1]);

    jeu.draw_line(215,190,180,120,couleur[1]);
    jeu.draw_line(180,120,110,120,couleur[1]);
    jeu.draw_line(285,190,315,120,couleur[1]);
    jeu.draw_line(315,120,385,120,couleur[1]);

    jeu.draw_text(50,110,"Tirer",1,couleur[0],1,25);
    jeu.draw_text(400,105,"Tir",1,couleur[0],1,25);
    jeu.draw_text(385,130,"spécial",1,couleur[0],1,25);
    jeu.draw_text(45,520,"+1 Vie",1,couleur[0],1,30);
    jeu.draw_text(70,560,"ou",1,couleur[0],1,25);
    jeu.draw_text(20,590,"+10 000 pts",1,couleur[0],1,25);
    jeu.draw_text(20,615,"si vie maximale",1,couleur[0],1,20);
    int x=90;
    int y=500;
    int largeur=5;
    for(int i=0;i<8;++i){
        jeu.draw_rectangle(x+i*largeur,y+largeur-i*largeur,x+i*largeur,y-i*largeur,couleur[1]);
        jeu.draw_rectangle(x-i*largeur,y+largeur-i*largeur,x-i*largeur,y-i*largeur,couleur[1]);}

    jeu.draw_rectangle(x+7*largeur,y-10*largeur,x+7*largeur,y-7*largeur,couleur[1]);
    jeu.draw_rectangle(x-7*largeur,y-10*largeur,x-7*largeur,y-7*largeur,couleur[1]);

    jeu.draw_rectangle(x-6*largeur,y-11*largeur,x-6*largeur,y-10*largeur,couleur[1]);
    jeu.draw_rectangle(x+6*largeur,y-11*largeur,x+6*largeur,y-10*largeur,couleur[1]);           //dessin coeur

    jeu.draw_rectangle(x-5*largeur,y-12*largeur,x-2*largeur,y-12*largeur,couleur[1]);
    jeu.draw_rectangle(x+5*largeur,y-12*largeur,x+2*largeur,y-12*largeur,couleur[1]);

    jeu.draw_rectangle(x-1*largeur,y-11*largeur,x-largeur,y-12*largeur,couleur[1]);
    jeu.draw_rectangle(x+1*largeur,y-11*largeur,x+largeur,y-12*largeur,couleur[1]);

    jeu.draw_rectangle(x,y-10*largeur,x,y-11*largeur,couleur[1]);

    jeu.draw_rectangle(340,425,390,475,couleur[1],1,~0U);
    jeu.draw_circle(440,475,30,couleur[1],1,~0U);
    jeu.draw_triangle(340,485,410,500,360,550,couleur[1],1,~0U);

    jeu.draw_text(270,570,"Ennemi tué=+25/50/100/250 pts",1,couleur[0],1,15);
    jeu.draw_text(315,590,"selon la difficulté",1,couleur[0],1,15);
    jeu.draw_text(290,610,"Ennemi non tué = -1000 pts",1,couleur[0],1,15);

    jeu.draw_circle(240,465,30,couleur[1],1,~0U);
    jeu.draw_text(235,450,"?",1,couleur[0],1,30);
    jeu.draw_text(200,530,"Bonus Tir",1,couleur[0],1,20);

    fenetre.display(jeu);}

void affiche_ecran_reglage(CImg<unsigned char> & jeu, CImgDisplay &fenetre ,int difficulte, int nombre_vie, int couleur_vaisseau,int x,int y){
    dessine_fond_blanc(jeu);

    jeu.draw_arrow(85,45,25,45,couleur[1],1,30,-40,~0U);
    jeu.draw_rectangle(15,20,100,70,couleur[1],1,60);
    if(x>15 and x<100 and y>20 and y<70)
        jeu.draw_rectangle(15,20,100,70,couleur[1],1,~0U);

    //------------------------------------------------------------------------------------

    jeu.draw_text(35,110,"Choissisez une couleur pour le vaisseau !",55,couleur[0],1,25 ); //choix couleur vaisseau

    jeu.draw_rectangle (70, 180, 120, 230, couleur[2]);
    jeu.draw_rectangle (70, 180, 120, 230, couleur[1], 1, ~0U);
    if(couleur_vaisseau==2)
        jeu.draw_rectangle(70,260,120,260,couleur[1],1);
    jeu.draw_text(70,240,"Rouge",55,couleur[0],1,20 );          //affiche les choix de couleur (carrés colorés et texte)

    jeu.draw_rectangle (170, 180, 220, 230, couleur[3]);
    jeu.draw_rectangle (170, 180, 220, 230, couleur[1], 1, ~0U);
     if(couleur_vaisseau==3)
        jeu.draw_rectangle(175,260,215,260,couleur[1],1);
    jeu.draw_text(175,240,"Vert",55,couleur[0],1,20 );

    jeu.draw_rectangle (270, 180, 320, 230, couleur[5]);
    jeu.draw_rectangle (270, 180, 320, 230, couleur[1], 1, ~0U);
     if(couleur_vaisseau==5)
        jeu.draw_rectangle(277,260,312,260,couleur[1],1);
    jeu.draw_text(277,240,"Bleu",55,couleur[0],1,20 );

    jeu.draw_rectangle (370, 180, 420, 230, couleur[1]);
     if(couleur_vaisseau==1)
        jeu.draw_rectangle(380,260,410,260,couleur[1],1);
    jeu.draw_text(380,240,"Noir",55,couleur[0],1,20 );

    //------------------------------------------------------------------------------------

    jeu.draw_text(80,400,"Choix de la difficulté !",55,couleur[0],1,35 ); //choix difficulté

    jeu.draw_rectangle (80, 460, 230, 510, couleur[1], 1, 50);
    if(difficulte==4)
        jeu.draw_rectangle(80,460,230,510,couleur[1],1,~0U);
    jeu.draw_text(130,475,"Facile",55,couleur[0],1,25 );

    jeu.draw_rectangle (260, 460, 410, 510, couleur[1], 1, 50);
    if(difficulte==3)
        jeu.draw_rectangle(260,460,410,510,couleur[1],1,~0U);
    jeu.draw_text(300,475,"Moyen",55,couleur[0],1,25 );

    jeu.draw_rectangle (80, 535, 230, 585, couleur[1], 1, 50);
    if(difficulte==2)
        jeu.draw_rectangle(80,535,230,585,couleur[1],1,~0U);
    jeu.draw_text(120,550,"Difficile",55,couleur[0],1,25  );

    jeu.draw_rectangle (260, 535, 410, 585, couleur[1], 1, 50);
    if(difficulte==1)
        jeu.draw_rectangle(260,535,410,585,couleur[1],1,~0U);
    jeu.draw_text(295,550,"Hardcore",55,couleur[0],1,25 );

    //------------------------------------------------------------------------------------

    jeu.draw_rectangle (60, 305, 150, 360, couleur[1], 1, 50); //choix du nombre de vie du joueur
    if(nombre_vie==1)
        jeu.draw_rectangle(60,305,150,360,couleur[1],1,~0U);
    jeu.draw_text(80,325,"1 vie",55,couleur[0],1,20 );

     jeu.draw_rectangle (210, 305, 300, 360, couleur[1], 1, 50);
     if(nombre_vie==2)
        jeu.draw_rectangle(210,305,300,360,couleur[1],1,~0U);
    jeu.draw_text(230,325,"2 vie",55,couleur[0],1,20 );

     jeu.draw_rectangle (360, 305, 450, 360, couleur[1], 1, 50);
     if(nombre_vie==3)
        jeu.draw_rectangle(360,305,450,360,couleur[1],1,~0U);
    jeu.draw_text(380,325,"3 vie",55,couleur[0],1,20 );

    jeu.display(fenetre);}

void affiche_ecran_jeu(CImg<unsigned char> & jeu,int difficulte){
    dessine_fond_blanc(jeu);

    jeu.draw_arrow(85,40,25,40,couleur[1],1,30,-40,~0U);
    jeu.draw_rectangle(15,20,100,65,couleur[1],1,60);           //affiche la difficulté actuelle dans l'écran jeu
    if(x>15 and x<100 and y>20 and y<65)
        jeu.draw_rectangle(15,20,100,65,couleur[1],1,~0U);

    jeu.draw_rectangle(340,20,490,65,couleur[1],1,~0U);
    jeu.draw_text(350,30,"Score : ",55,couleur[0],1,30 );
    jeu.draw_text(440,39,to_string(score).c_str(),80,couleur[0],10);

    jeu.draw_rectangle(120,20,320,65,couleur[1],1,~0U);
    if(difficulte==4)
        jeu.draw_text(190,30,"Facile",55,couleur[0],1,30 );

    if(difficulte==3)
        jeu.draw_text(180,30,"Moyen",55,couleur[0],1,30 );

    if(difficulte==2)
        jeu.draw_text(180,30,"Difficile",55,couleur[0],1,30 );

    if(difficulte==1)
        jeu.draw_text(170,30,"Hardcore",55,couleur[0],1,30 );}

void affiche_ecran_game_over(CImg<unsigned char> & jeu, CImgDisplay &fenetre, int& score, vector<int> liste_high_score,int x,int y){
    dessine_fond_blanc(jeu);
    jeu.draw_arrow(85,40,25,40,couleur[1],1,30,-40,~0U);
    jeu.draw_rectangle(15,20,100,65,couleur[1],1,60);
    if(x>15 and x<100 and y>20 and y<65)
        jeu.draw_rectangle(15,20,100,65,couleur[1],1,~0U);  //dessine rectangle trait plein quand on passe la souris sur le bouton

    jeu.draw_text(55,70,"GAME OVER",55,couleur[0],1,80 );
    jeu.draw_text(180,170,"Score : ",55,couleur[0],1,30 );          //affiche le score de la partie
    jeu.draw_text(280,180,to_string(score).c_str(),80,couleur[0],10);

    //afficher high score
    jeu.draw_rectangle(120,250,380,500,couleur[1],1,60);
    jeu.draw_rectangle(120,250,380,310,couleur[1],1,60);
    jeu.draw_rectangle(120,310,380,350,couleur[1],1,60);
    jeu.draw_rectangle(120,310,250,500,couleur[1],1,60);

    jeu.draw_text(130,260,"HIGH SCORES",55,couleur[0],1,45 );
    jeu.draw_text(150,320,"RANK",55,couleur[0],1,25 );
    jeu.draw_text(280,320,"SCORE",55,couleur[0],1,25);

    jeu.draw_text(160,375,"1ST",55,couleur[0],1,25 );
    jeu.draw_text(160,415,"2ND",55,couleur[0],1,25 );
    jeu.draw_text(160,455,"3RD",55,couleur[0],1,25 );

    jeu.draw_text(300,380,to_string(liste_high_score[0]).c_str(),80,couleur[0],10);
    jeu.draw_text(300,420,to_string(liste_high_score[1]).c_str(),80,couleur[0],10);     //affiche la liste des meilleures scores
    jeu.draw_text(300,460,to_string(liste_high_score[2]).c_str(),80,couleur[0],10);

    jeu.draw_rectangle (200, 540, 310, 590, couleur[1], 1, 50);
    jeu.draw_text(210,550,"Rejouer",55,couleur[0],1,30 );
    if(x>200 and x<310 and y>540 and y<590)
        jeu.draw_rectangle (200, 540, 310, 590, couleur[1], 1, ~0U);

    jeu.display(fenetre);}

void affiche_ecran_production(CImg<unsigned char> & jeu, CImgDisplay &fenetre){
    dessine_fond_blanc(jeu);
    jeu.draw_text(30,300,"A PA'SEA'FIQUE PRODUCTION",50,couleur[0],1,35);       //affiche ecran "production"
    jeu.draw_rectangle(30,340,470,350,couleur[1],1);
    jeu.draw_rectangle(30,290,470,280,couleur[1],1);
    fenetre.display(jeu);
    fenetre.wait(3000);}  //laisse l'image quelques secondes à l'écran


//-----------------------------------------------------------------------------------------------------------------------
//fonctions boutons
void bouton(int x1, int y1, int x2, int y2, bool& devient_faux, bool& devient_vrai,CImgDisplay &fenetre,vector<Ennemi> & Liste_accueil){
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2 )        //quand on clique sur le rectangle defini par les coordonnées x et y, on change la valeur des bool pour changer de page
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
    if (fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2)     //quand on clique sur un des boutons de l'écran, on change la couleur du vaisseau
        couleur_vaisseau=valeur;}

void bouton_choix_nombre_vie(int x1, int y1, int x2, int y2,int & nombre_vie, int valeur, Joueur & joueur,CImgDisplay &fenetre){
      if(fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2)        //quand on clique sur le nombre de vie désirée, ca affecte la valeur au personnage
            {nombre_vie=valeur;
            joueur.nombre_de_vie=valeur;}}

void bouton_choix_difficulte(int x1, int y1, int x2, int y2,int & difficulte, int valeur, CImgDisplay &fenetre){
    if(fenetre.button()&1 and x>=x1 and x<=x2 and y>=y1 and y<=y2)      //changer la difficulté du jeu quand on appuie sur les boutons
            difficulte=valeur;}

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
            jeu.draw_rectangle(x-16,y+29,x+16,y+36,couleur[1],1,~0U);        //affiche le nombre de vie restant a l'écran

            if(joueur.nombre_de_vie==3){
                jeu.draw_rectangle(x+20,y+30,x+50,y+35,couleur[2],1);
                jeu.draw_rectangle(x+19,y+29,x+51,y+36,couleur[1],1,~0U);}}}


    jeu.draw_rectangle(x-50,y+40,x+50,y+45,couleur[1],1,~0U); //barre de chargement attaque spéciale
    if(nbr_ennemi_tue<100)
        jeu.draw_rectangle(x-49,y+41,x-49+nbr_ennemi_tue,y+44,couleur[2],1);
    else
        jeu.draw_rectangle(x-49,y+41,x+49,y+44,couleur[2],1);}

void position_personnage(double x, Joueur & joueur){
    if(x!=-1)       //pour pas que le perso parte a une extremité de l'écran quand la souris sort de l'écran
        joueur.x_joueur=x;
    joueur.y_sommet_joueur=500;}

//---------------------------------------------------------------------
//TIR
void cool_down(double& temps_cooldown){
    if(temps_cooldown>0)        //réduit le cooldown pour pouvoir tirer a nouveau
            temps_cooldown-=0.1;}

void tir(int x,int y,CImgDisplay &fenetre, vector<Balle> & liste_balle, double & temps_cooldown,bool tir_alternatif){
    if (fenetre.button()&1 and y>=65 and temps_cooldown<=0){        //si clic gauche et cooldown ok : on peut tirer
        if(!tir_alternatif){
            Balle balle;
            balle.vitesse_balle=2;
            balle.x_balle=x;
            balle.y_balle=545;
            balle.taille_balle=5;
            liste_balle.push_back(balle); //crée une balle dans une liste si on tire
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
    if(fenetre.button()&2 and nbr_ennemi_tue>=100) {    //tir special si clic droit et barre d'attaque spéciale chargée a fond

        nbr_ennemi_tue=0;   //on reinitialise la barre d'attaque spéciale
        score+= 100*liste_ennemi.size(); //on gagne 100 pts * nombre d'ennemi tué sur l'écran
        liste_ennemi.clear();}}//tue tous les ennemis

void affiche_tir(CImg<unsigned char> & jeu , vector<Balle> & liste_balle){
    for(Balle balle : liste_balle)
        jeu.draw_circle(balle.x_balle,balle.y_balle,balle.taille_balle,couleur[couleur_vaisseau],1);}

void bouger_balle(vector<Balle> & liste_balle){
    for(int i=0;i<liste_balle.size();++i){
        liste_balle[i].y_balle -= liste_balle[i].vitesse_balle;  //diminue la position y pour faire monter la balle
        if(liste_balle[i].y_balle<75)
            liste_balle.erase(liste_balle.begin()+i);}} //efface element de la liste si la balle sort de l'écran

void collision_balle_ennemi(vector<Balle> & liste_balle,vector<Ennemi>& liste_ennemi, int & score, int & nbr_ennemi_tue, int difficulte){
    for(int i=0;i<liste_balle.size();++i)       //on parcourt la liste pour venir vérifier les conditions de collision de chacune des balles avec chacun des ennemis
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
                    else if(difficulte==2)          //selon la difficulté on gagne plus ou moins de points
                        score+=100;
                    else if(difficulte==1)
                        score+=250;}}

//---------------------------------------------------------------------
//ENNEMIS
void ennemi(vector<Ennemi> & liste_ennemi,int difficulte){ //modifier la fréquence d'apparition sur pc LINUX
    double aleatoire=rand()%(difficulte*50); //frequence d'apparition augmente avec la difficulté (difficulté qui baisse = réduit le nombre aléatoire et augmente la probabilité de creer un ennemi et inversement)
    if(aleatoire<=1){   //condition pour créer un ennemi
        Ennemi ennemi;
        ennemi.x_ennemi=10+rand()%475;
        ennemi.y_ennemi=80 ;
        ennemi.vitesse_ennemi=0.5;
        ennemi.couleur_ennemi=rand()%10+1;
        ennemi.taille_ennemi=15;

        double forme_aleatoire=rand()%30;       //forme aléatoire
        if(forme_aleatoire<=10)
            ennemi.forme_ennemi=1; // cercle
        else if(forme_aleatoire<=20)
            ennemi.forme_ennemi=2; //carré
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
    for(int i=0;i<liste_ennemi.size();++i){     //parcourt la liste des ennemis pour modifier les coordonées pour les faire bouger
        liste_ennemi[i].y_ennemi += liste_ennemi[i].vitesse_ennemi;
        if(liste_ennemi[i].y_ennemi>650){
            liste_ennemi.erase(liste_ennemi.begin()+i);         //déplace l'ennemi et enleve 1000pts si l'ennemi atteint l'écran du bas
            score-=1000;}}}

void collision_ennemi_joueur(vector<Ennemi>& liste_ennemi, Joueur & joueur){
    for(int i=0;i<liste_ennemi.size();++i)          //parcourt liste ennemi pour vérifier les conditions de collision de chacun des ennemis avec le joueur
        if(liste_ennemi[i].y_ennemi-liste_ennemi[i].taille_ennemi-10>= joueur.y_sommet_joueur )
            if(liste_ennemi[i].x_ennemi >= joueur.x_joueur-45 and liste_ennemi[i].x_ennemi <= joueur.x_joueur +45 ){
                liste_ennemi.erase(liste_ennemi.begin()+i);     //si un ennemi touche le joueur, l'ennemi disparait et le joueur perd 1 vie
                joueur.nombre_de_vie-=1;}}

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
        bonus.type=2; //bonus tir amélioré
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
    for(int i=0;i<liste_bonus.size();++i){      //parcourt la liste des bonus et modifie la coordonée y pour les faire avancer
        liste_bonus[i].y_bonus+=liste_bonus[i].vitesse_bonus;
        if(liste_bonus[i].y_bonus>650)
            liste_bonus.erase(liste_bonus.begin()+i);}}

void collision_bonus_joueur(vector<Bonus>& liste_bonus, Joueur & joueur,bool & tir_alternatif){
    for(int i=0;i<liste_bonus.size();++i)           //parcourt la liste des bonus pour vérifier les collisions bonus/joueur et appliquer les effets en cas de collision avec le bonus vie ou tir
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

//---------------------------------------------------------------------
void game_over(Joueur & joueur,int& nbr_ennemi_tue, bool& tir_alternatif){
    if(joueur.nombre_de_vie==0){
        afficher_jeu=false;     //si plus de vie = game over
        afficher_game_over=true;
        nbr_ennemi_tue=0;
        tir_alternatif=false;
        joueur.nombre_de_vie=nombre_vie;}}

void modification_high_score(vector<int> & liste_high_score, int score){
    if(score>=liste_high_score[0]){ //modifie les 3 meilleurs scores enregistrés
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
    bouger_ennemi(Liste_accueil,score_accueil);        //fait défiler les ennemis sur l'écran d'accueil = décoration
    affiche_ennemi(jeu,Liste_accueil);
    fenetre.display(jeu);}



//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* +++++++++++++++++++++++++++ */
/* +++ Fonction principale +++ */
/* +++++++++++++++++++++++++++ */
int main(){

/*Initialisation des variables locales au main()*/
Joueur joueur;    //on crée le joueur
vector<Ennemi> Liste_accueil; //pour gerer les ennemis sur l'écran d'accueil
srand(time(nullptr)); //pour créer des chiffres aléatoires

/* ======================================== */
/* === Création de la fenêtre graphique === */
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
        affiche_ecran_accueil(jeu,fenetre,x,y); //affiche tous les éléments visuels de l'écran d'accueil
        position_souris(x,y,fenetre); //recupere la position de la souris sur l'écran

        //si on clique sur un des boutons de l'écran on bascule de l'écran du menu a l'écran souhaité
        bouton(170,190,310,270,afficher_menu,afficher_jeu,fenetre,Liste_accueil);
        bouton(110,310,380,380,afficher_menu,afficher_commandes,fenetre,Liste_accueil);
        bouton(110,420,400,485,afficher_menu,afficher_reglages,fenetre,Liste_accueil);
        bouton(160,520,320,580,afficher_menu,afficher_credits,fenetre,Liste_accueil);

        //pluie d'ennemi (décoratif)
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
        //boutons pour choix difficulté
        bouton_choix_difficulte(80,460,230,510,difficulte,4,fenetre);// très facile
        bouton_choix_difficulte(260,460,410,510,difficulte,3,fenetre);//facile
        bouton_choix_difficulte(80,535,230,585,difficulte,2,fenetre);//moyen
        bouton_choix_difficulte(260,535,410,585,difficulte,1,fenetre);}//difficile

//---------------------------------------------------------------------
    if(afficher_credits){  //affiche la page des crédits
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
        fenetre.wait(10);       //taux de rafraichissement (pour éviter les impressions de ralentissement sur certains pc)
        //-------------------------------------
        position_souris(x,y,fenetre);
        bouton_quitter_jeu(15,20,100,70,afficher_jeu,afficher_menu,score,Liste_balle,Liste_ennemi,Liste_bonus,fenetre,tir_alternatif,nbr_ennemi_tue);     //bouton pour retourner au menu et tout réinitialiser
        game_over(joueur,nbr_ennemi_tue,tir_alternatif);     //fin de la partie quand on a épuisé les 3 vies
        //-------------------------------------
        affiche_ecran_jeu(jeu,difficulte); //affiche écran arriere (fond + bouton + score + difficulté)
        dessiner_ecran_jeu(jeu);            //affiche cadrillage
        //-------------------------------------
        position_personnage(x,joueur);
        affiche_personnage(jeu, joueur,nbr_ennemi_tue); //affiche le vaisseau du joueur
        //-------------------------------------
        cool_down(temps_cooldown);                              //cooldown pour pas tirer trop vite
        tir(x,y, fenetre, Liste_balle,temps_cooldown,tir_alternatif);          // gère la liste des positions des balles
        tir_secondaire(x,y,fenetre,Liste_balle,temps_cooldown,tir_alternatif,tic_tir_secondaire); //tir 3 balles par 3 balles grâce au bonus
        tir_special(x,y,fenetre,Liste_balle,Liste_ennemi,nbr_ennemi_tue,score);           //détruit tout les ennemis de l'écran (necessite 100 kills)
        affiche_tir(jeu, Liste_balle);                          // affiche les balles
        bouger_balle(Liste_balle);                              //et gère leurs déplacements
        collision_balle_ennemi(Liste_balle,Liste_ennemi,score,nbr_ennemi_tue,difficulte); //gère la collision entre les balles et les ennemis
        //-------------------------------------
        ennemi(Liste_ennemi,difficulte);            //gere la liste d'ennemis
        affiche_ennemi(jeu,Liste_ennemi);     //affiche les ennemis
        bouger_ennemi(Liste_ennemi,score);                //et gere leurs déplacements
        collision_ennemi_joueur(Liste_ennemi,joueur); //gère la collision ennemi/joueur
        //-------------------------------------
        bonus(fenetre,Liste_bonus);
        affiche_bonus(fenetre,jeu,Liste_bonus);                  // +1vie si on a pas le nbr de vie max (définie dans les parametre) sinon +500pts
        bouger_bonus(fenetre,Liste_bonus,score);                 // bonus tir = tire 3 balles par coup (temps limité)
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
