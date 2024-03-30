#include<iostream>
#include "grille.hpp"
#include "termite.hpp"

using namespace std;

Grille::Case::Case(){
	//valeurs d'une case vide
    brindille=false;
    numT=-1;
	nid=-1;
}

Grille::Grille() {
	nbBrindillesnonNeutre=0;
	nbBrindilles=0;
	//parcour du tableau 2d grille et inialiser les cases tant que cases vides
    for(int i = 0; i < tailleGrille; i++) {
        for(int j = 0; j < tailleGrille; j++) {
            grille[i][j] = Case();
        }
    }
}

int Grille::getNbBrindilles(){return nbBrindilles;}

void Grille::setNbBrindilles(int v){nbBrindilles=v;}

int Grille::getNbBrindillesnonNeutre(){return nbBrindillesnonNeutre;}

void Grille::setNbBrindillesnonNeutre(int v){nbBrindillesnonNeutre=v;}

void Grille::poseBrindille(Coord c){
	//verifie si la case est vide
	if (!estVide(c)) throw invalid_argument("poseBrindille : la case n'est pas vide");
	//pose la brindille sur cette case
	grille[c.getLig()][c.getCol()].brindille=true;
}

void Grille::enleveBrindille(Coord c){
	//verifie si il y a une brindille sur la case
	if (!contientBrindille(c)) throw invalid_argument("enleveBrindille : la case ne contient pas de brindille");
	//enleve la brindille de cette case
	grille[c.getLig()][c.getCol()].brindille=false;
}
bool Grille::contientBrindille(Coord c) const {
	return grille[c.getLig()][c.getCol()].brindille; 
}

void Grille::changeValueNid(Coord c, int v){
	grille[c.getLig()][c.getCol()].nid=v;
}

bool Grille::brindilleNeutre(Coord c) const {
	if(!contientBrindille(c)) throw invalid_argument("il n'y a pas de brindilles sur la case");
	return !appartientNid(c);
}	

bool Grille::appartientNid(Coord c)const{
	return numeroNid(c)!=-1;
}


void Grille::poseTermite(Coord c, int idT){
	//verifie si la case est vide
	if (!estVide(c)) throw invalid_argument("poseTermite : la case n'est pas vide");
	grille[c.getLig()][c.getCol()].numT=idT;
}
void Grille::enleveTermite(Coord c){
	//verifie si il'y a une termite sur la case
	if (numeroTermite(c)==-1) throw invalid_argument("enleveTermite : il n'y a pas de termite ");
	grille[c.getLig()][c.getCol()].numT=-1;
}
int Grille::numeroTermite(Coord c) const{
	return grille[c.getLig()][c.getCol()].numT;
}

int Grille::numeroNid(Coord c) const{
	return grille[c.getLig()][c.getCol()].nid;
}
	
	
bool Grille::estVide(Coord c) const{
	return !contientBrindille(c) && numeroTermite(c)<0;
}

//la surcharge de l'operateur d'affichage pour la grille
std::ostream &operator<<(std::ostream &out, Grille g){
	for (int i=0;i<tailleGrille;i++){
		for(int j=0;j<tailleGrille;j++){
			if(g.grille[i][j].brindille) out<<"B";
			else if(g.grille[i][j].numT==-2) out<<"N";
			else if(g.grille[i][j].numT!=-1) out<<"T";
			else out<<" ";
			
		}
		out<<endl;
	}
	return out;
}

void Grille::equipeGagnante()const{
	int equipe1=0;
	int equipe2=0;
	int equipe3=0;
	for(int i = 0; i < tailleGrille; i++) {
        for(int j = 0; j < tailleGrille; j++) {
            if(numeroNid(Coord{i,j})==1)equipe1++;
			else if(numeroNid(Coord{i,j})==2)equipe2++;
			else if(numeroNid(Coord{i,j})==3)equipe3++;
        }
    }
	if(equipe1>equipe2){
		if(equipe1>equipe3) cout<<"l'équipe gagnante est la 1"<<endl;
		else if(equipe1<equipe3) cout<<"l'équipe gagnante est la 3"<<endl;
		else cout<<"Les équipes 1 et 2 sont premières ex aequo"<<endl;
	}
	else if(equipe1<equipe2){
		if(equipe2>equipe3) cout<<"l'équipe gagnante est la 2"<<endl;
		else if(equipe2<equipe3) cout<<"l'équipe gagnante est la 3"<<endl;
		else cout<<"Les équipes 2 et 3 sont premières ex aequo"<<endl;
	}
	else {
		if(equipe1<equipe3)cout<<"l'équipe gagnante est la 3"<<endl;
		else if(equipe1>equipe3)cout<<"Les équipes 1 et 2 sont premières ex aequo"<<endl;
		else cout<<"Les équipes 1 2 et 3 sont toute à égalité : il n'y a donc pas de vainqueur"<<endl;
	}
}

int Grille::nbPointsEquipe(int idEquipe){
	int nbPoints=0;
	for(int i = 0; i < tailleGrille; i++) {
        for(int j = 0; j < tailleGrille; j++) {
			if(numeroNid(Coord{i,j})==idEquipe)nbPoints++;
		}
	}
	return nbPoints;
}
