#ifndef COORD_H
#define COORD_H

#include <iostream>
#include<array>
using namespace std;

//taille de la grille
const int tailleGrille=20;
//les direction
enum Direction{nordOuest,nord,nordEst,est,sudEst,sud,sudOuest,ouest};
//liste des directions
const array<Direction, 8> stringDirection={Direction::nordOuest,Direction::nord, Direction::nordEst,Direction::est,
										   Direction::sudEst,Direction::sud,Direction::sudOuest,Direction::ouest};

const array<string, 8> flecheDirection={"↙","↓","↘","→","↗","↑","↖","←"};


class Coord{
    public:
         //* Constructeur à partir de deux entiers
		 //* @param[in] lig un numéro de ligne
		//* @param[in] col un numéro de colonnes
        Coord(int lig, int col);
		//* getter de la ligne 
        int getLig();
		//* getter de la colonne
		int getCol();
		//* fonction devantCoord rencvoie la coordonne devant un coordonnee donne et une direction
		//* @param[in] d une direction
        Coord devantCoord(Direction d)const;
		bool operator<(const Coord& other) const;
	private:
        int ligne;
        int colonne;
};

// surcharge de l'operateur d'affichage pour les coordonnee
std::ostream &operator<<(std::ostream &out, Coord c);
// surcharge de l'operateur d'egalite pour les coordonnee
bool operator==(Coord a, Coord b);
// surcharge de l'operateur d'inegalite pour les coordonnee
bool operator!=(Coord a, Coord b);
// surcharge de l'operateur d'affichage pour les directions
std::ostream &operator<<(std::ostream &out, Direction d);
//* fonction aGauche rencvoie la direction a gauche de la direction en entree
//* @param[in] a une direction
Direction aGauche(Direction a);
//* fonction aDroite rencvoie la direction a droite de la direction en entree
//* @param[in] a une direction
Direction aDroite(Direction a);


#endif

