#ifndef TERMITE_H
#define TERMITE_H

#include <iostream>
#include <vector>
#include "coord.hpp"
#include "grille.hpp"


const float probaTourner = 0.1; // proba de tourner a gauche ou a droite
const int dureeSablier = 10; // duree de vie d'une termite

class Termite{

	public:

		//plus compliquer rajouter un age + un sexe pour la possibilete de reproduction pour la population
		Termite(Coord c,int idT,Direction dir); //constructeur du termite
		int getIdT();// getteur de l'indice du termite
		int getEquipe();// getteur du numéro d'équipe du termite
		Coord getCoord(); // getteur de la coordonnee de la termite
		bool getPorte(); // getteur de si la termite porte une brindille
		Direction getDirection(); // getteur de la direction de la termite 
		void setIdT(int nvlleIdt);
		void setEquipe(int nvlleEquipe);
		

		Coord devant()const;
		
		
		void tourneADroite(); // fonction qui permet a la termite de tourner a droite
		void tourneAGauche(); // fonction qui permet a la termite de tourner a gauche
		void tourneAleat(); // fonction qui permet a la termite de tourner aleatoirement
		void tourneGaucheouDroite(); // fonction qui permet au termite de tourner a gauche ou a droite aleatoirement
		bool laVoieEstLibre(const Grille &g)const;
		bool brindilleEnFace(const Grille &g)const;
		bool termiteEnFace(const Grille &g)const;
		int voisinsLibre(const Grille &g)const;
		void avance(Grille &g);
		void marcheAleat(Grille &g);// fonction qui deplace la termite


		void prendBrindille(Grille &g);// fonction qui permet la termite de porter une brindille
		void dechargeBrindille(Grille &g); // fonction qui permet la termite de poser une brindille
		void donneOdeur(Grille &g);
		void vieTermite(Grille &g); //algo de la termite



	private:
		int idT; // l'indice de la termite (unique)
		Coord pos;// cordonnee de la termite
		bool porteBrindille;// si la termite porte une brindille
		Direction d; // ou regarde la termite
		int nbDeplacement; 
		int equipe;

};

//Direction choixDirection();
//surcharge de l'operateur d'affichage pour termite
std::ostream &operator<<(std::ostream &out, Termite a);
string to_string(Termite a);
void afficheGrille(Grille g,vector<Termite> termite);
int nbJoueurEquipe(vector<Termite> *termite, int idEquipe);
#endif

