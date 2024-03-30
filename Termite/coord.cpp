#include <iostream>
#include "coord.hpp"

using namespace std;


Coord::Coord(int lig, int col){
	//verfie si on sort de la grille
    if (lig>tailleGrille || col>tailleGrille || lig<0 || col<0) throw out_of_range("sortie de la grille");
	//cree la coordonnee
    ligne=lig;
    colonne=col;
};
bool Coord::operator<(const Coord& other) const {
        if (ligne == other.ligne) {
            return colonne < other.colonne;
        }
        return ligne < other.ligne;
    }


int Coord::getLig(){return ligne;}

int Coord::getCol(){return colonne;}

std::ostream &operator<<(std::ostream &out, Coord c){
    out<<"("<<c.getLig()<<","<<c.getCol()<<")";
    return out;
}

bool operator==(Coord a, Coord b){return b.getLig()==a.getLig() && a.getCol() ==b.getCol();}

bool operator!=(Coord a, Coord b){return !(a==b);}


std::ostream &operator<<(std::ostream &out, Direction d){
    switch (d){ //associe a chaque 
    case Direction::nordOuest:out<<"nord-ouest";break;
    case Direction::nord:out<<"nord";break;
    case Direction::nordEst:out<<"nord-est";break;
    case Direction::est:out<<"est";break;
    case Direction::sudEst:out<<"sud-est";break;
    case Direction::sud:out<<"sud";break;
    case Direction::sudOuest:out<<"sud-ouest";break;
    case Direction::ouest:out<<"ouest";break;
    }
	return out;
}

Coord Coord::devantCoord(Direction b)const{
    int x=ligne;
    int y=colonne;
    switch (b){
    case Direction::nordOuest:
			x=(x+1)%tailleGrille;
			y=(y-1+tailleGrille)%tailleGrille;
			break;
    case Direction::nord:
			x=(x+1)%tailleGrille;
			break;
    case Direction::nordEst:
			x=(x+1)%tailleGrille;
			y=(y+1)%tailleGrille;
			break;
    case Direction::est:
			y=(y+1)%tailleGrille;
			break;
    case Direction::sudEst:
			x=(x-1+tailleGrille)%tailleGrille;
			y=(y+1)%tailleGrille;
			break;
    case Direction::sud:
			x=(x-1+tailleGrille)%tailleGrille;
			break;
	case Direction::sudOuest:
			x=(x-1+tailleGrille)%tailleGrille;
			y=(y-1+tailleGrille)%tailleGrille;
			break;
	case Direction::ouest:
			y=(y-1+tailleGrille)%tailleGrille;
			break;
    }
	return Coord{x,y};
}

Direction aDroite(Direction a){
	return stringDirection[(int(a)+1)%8];
}
Direction aGauche(Direction a){
    return stringDirection[(int(a)+7)%8];
}

