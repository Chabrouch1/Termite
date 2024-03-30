#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <array>
#include "coord.hpp"

const float densiteBrindille=0.05;
const int nbTermites=20;

class Grille{
	
	private:
	int nbBrindilles;
	int nbBrindillesnonNeutre;
	struct Case{
		bool brindille;    //booléen indiquant si il y a une brindille sur la case
		int numT;          // numéro du termite qui occupe la case (-1 si il n'y en a pas)
		int nid;
		//* Constructeur par défaut d'une case qui crée une case vide(aucune espèce et numT :-1)
		Case();
	};
	
	
	
	public:
	
	
	//* getter de la colonne
	array<array<Case,tailleGrille>,tailleGrille>grille; //création de la grille
	
	Grille(); //constucteur de la grille
	
	int getNbBrindilles();
	void setNbBrindilles(int v);
	int getNbBrindillesnonNeutre();
	void setNbBrindillesnonNeutre(int v);
	
	//* fonction qui change le numéro du nid d'une case de la grile
	 //* @param[in] c une coordonnee de la case
    void changeValueNid(Coord c, int v);
	
	
	 //* fonction qui pose une brindille sur une case de la grile
	 //* @param[in] c une coordonnee de la case
    void poseBrindille(Coord c);
	
	 //* fonction qui enleve une brindille sur une case de la grile
	 //* @param[in] c une coordonnee de la case
    void enleveBrindille(Coord c);

	//* fonction qui verifie si une brindille est sur une case de la grile
	//* @param[in] c une coordonnee de la case
    bool contientBrindille(Coord c) const;

	//* fonction qui pose une termite sur une case de la grile
	//* @param[in] c une coordonnee de la case
    void poseTermite(Coord c, int idT);

	//* fonction qui enleve une termite sur une case de la grile
	//* @param[in] c une coordonnee de la case
    void enleveTermite(Coord c);

	//* fonction qui revoie le numero de la termite sur une case de la grile
	//* @param[in] c une coordonnee de la case
    int numeroTermite(Coord c) const;
	
	//* fonction qui revoie le numero du nid sur une case de la grile
	//* @param[in] c une coordonnee de la case
    int numeroNid(Coord c) const;

	//* fonction qui verifie si une case est vide(ne contient ni de termite ni de brindille)
	 //* @param[in] c une coordonnee d'une case
    bool estVide(Coord c) const;

	//* fonction qui verifie si une brindille appartient à un nid ou non
	 //* @param[in] c une coordonnee d'une case
	bool brindilleNeutre(Coord c)const;
	
	//* fonction qui verifie si une case est correspond à un nid ou non
	 //* @param[in] c une coordonnee d'une case
	bool appartientNid(Coord c)const;
	
	void equipeGagnante()const;

	int nbPointsEquipe(int idEquipe);
};

//surcharge de l'operateur d'affichage pour la grille
std::ostream &operator<<(std::ostream &out, Grille g);



#endif
