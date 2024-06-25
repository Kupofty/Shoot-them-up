#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include "InitVariables.h"

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

    for(int i=0;i<jeu.height();i=i+20)                      //dessine le quadrillage de l'ecran de jeu (style feuille papier)
        jeu.draw_line(0,i+140,500,i+140,couleur[9],1);

    jeu.draw_line(100,80,100,650,couleur[2],1);}

void affiche_ecran_accueil(CImg<unsigned char> & jeu,int x, int y){
    dessine_fond_blanc(jeu);

    //affichage des boutons  interactifs
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
    jeu.draw_text(160,430,"Reglages",55,couleur[0],4,50);

    jeu.draw_rectangle (160, 520, 320, 580, couleur[1], 1, 50);
    if(x>160 and x<320 and y>520 and y<580)
        jeu.draw_rectangle (160, 520, 320, 580, couleur[1], 1, ~0U);
    jeu.draw_text(170,530,"Credits",55,couleur[0],4,50);

    jeu.draw_rectangle (420, 570, 480, 630, couleur[1], 1,50);
    if(x>420 and x<480 and y>570 and y<630)
        jeu.draw_rectangle (420, 570, 480, 630, couleur[1], 1, ~0U);
    jeu.draw_line(430,580,470,620,couleur[1]);
    jeu.draw_line(470,580,430,620,couleur[1]);}

void affiche_ecran_credits(CImg<unsigned char> & jeu, CImgDisplay &fenetre){
    dessine_fond_blanc(jeu);

    for(int i=650; i>-580;--i){     //fait defiler les credits
        fenetre.wait(10);
        jeu.draw_text(200,i,"Producteur",55,couleur[0],1,30 );
        jeu.draw_text(200,i+30,"Kupofty",55,couleur[0],1,20 );

        jeu.draw_text(200,i+70,"Scenariste",55,couleur[0],1,30 );
        jeu.draw_text(200,i+100,"Kupofty",55,couleur[0],1,20 );

        jeu.draw_text(180,i+140,"Programmeur",55,couleur[0],1,30 );
        jeu.draw_text(200,i+170,"Kupofty",55,couleur[0],1,20 );

        jeu.draw_text(170,i+210,"Game Designer",55,couleur[0],1,30 );
        jeu.draw_text(200,i+240,"Kupofty",55,couleur[0],1,20 );

        jeu.draw_text(160,i+280,"Directeur artistique",55,couleur[0],1,30 );
        jeu.draw_text(200,i+310,"Kupofty",55,couleur[0],1,20 );

        jeu.draw_text(150,i+350,"Directeur technique",55,couleur[0],1,30 );
        jeu.draw_text(200,i+380,"Kupofty",55,couleur[0],1,20 );

        jeu.draw_text(170,i+420,"Programmeur IA",55,couleur[0],1,30 );
        jeu.draw_text(200,i+450,"Kupofty",55,couleur[0],1,20 );
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
    jeu.draw_text(385,130,"special",1,couleur[0],1,25);
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

    jeu.draw_text(270,570,"Ennemi tue=+25/50/100/250 pts",1,couleur[0],1,15);
    jeu.draw_text(315,590,"selon la difficulte",1,couleur[0],1,15);
    jeu.draw_text(290,610,"Ennemi non tue = -1000 pts",1,couleur[0],1,15);

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
    jeu.draw_text(70,240,"Rouge",55,couleur[0],1,20 );          //affiche les choix de couleur (carres colores et texte)

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

    jeu.draw_text(80,400,"Choix de la difficulte !",55,couleur[0],1,35 ); //choix difficulte

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
    jeu.draw_rectangle(15,20,100,65,couleur[1],1,60);           //affiche la difficulte actuelle dans l'ecran jeu
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
    fenetre.wait(3000);}  //laisse l'image quelques secondes e l'ecran


#endif // DISPLAYFUNCTIONS_H
