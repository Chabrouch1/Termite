#include <iostream>
#include "termite.hpp"
#include <cstdlib>

using namespace std;

Termite::Termite(Coord a, int id, Direction dir) : idT(id), pos(a), d(dir){
	porteBrindille = false; // au debut le termite ne porte pas de brindille
	// choix de direction aleatoire
	nbDeplacement = 0;
	equipe=1;
};

int Termite::getIdT() { return idT; };
int Termite::getEquipe() { return equipe; };
Coord Termite::getCoord() { return pos; };
bool Termite::getPorte() { return porteBrindille; };
Direction Termite::getDirection() { return d; };
void Termite::setIdT(int nvlleIdt){idT=nvlleIdt;};
void Termite::setEquipe(int nvlleEquipe){equipe=nvlleEquipe;};

Coord Termite::devant() const { return pos.devantCoord(d); }

void Termite::tourneADroite() { d = aDroite(d); }

void Termite::tourneAGauche() { d = aGauche(d); }

void Termite::tourneAleat()
{
	d = stringDirection[rand() % 8];
}

void Termite::tourneGaucheouDroite()
{
	d = rand() % 2 == 0 ? aGauche(d) : aDroite(d);
}

bool Termite::laVoieEstLibre(const Grille &g) const
{
	if (termiteEnFace(g)) return false;
	else if (brindilleEnFace(g) && porteBrindille) return false;
	else if (brindilleEnFace(g) && !g.brindilleNeutre(devant())) return false;
	else return true;
}

bool Termite::brindilleEnFace(const Grille &g) const
{
	return g.contientBrindille(devant());
}

bool Termite::termiteEnFace(const Grille &g) const
{
	return g.numeroTermite(devant()) != -1;
}

int Termite::voisinsLibre(const Grille &g) const{
	int s = 0;
	for (Direction a : stringDirection)
	{
		if (g.estVide(pos.devantCoord(a)))
			s++;
	}
	return s;
}

void Termite::avance(Grille &g){
	if (g.estVide(devant())){
		g.poseTermite(devant(),idT);
		g.enleveTermite(pos);
		pos=devant();
		nbDeplacement++;
	}
}


// changer la fonction pour que le deplacement depend des fonctions aDroite et aGauche et si une autre termite bloque le chemin
void Termite::marcheAleat(Grille &g)
{
	if (laVoieEstLibre(g) &&(double(rand())/RAND_MAX)>probaTourner)
		avance(g);
	else tourneGaucheouDroite();
}

void Termite::prendBrindille(Grille &g)
{
	if (laVoieEstLibre(g) && brindilleEnFace(g) && g.brindilleNeutre(devant()) && nbDeplacement >= dureeSablier)
	{								 // verifie si la case devant la termite contient une brindille
		g.enleveBrindille(devant()); // enleve la brindille de cette case
		porteBrindille = true;		 // porte la brindille
		nbDeplacement = 0;
	}
};

void Termite::dechargeBrindille(Grille &g)
{
	if (laVoieEstLibre(g) && porteBrindille && voisinsLibre(g)>=2 && nbDeplacement>=dureeSablier)
	{							   // verfie si la case devant la termite est vide et si la termite porte une brindille
		g.poseBrindille(devant()); // met la brindille sur cette case
		porteBrindille = false;	   // pose la brindille*
		donneOdeur(g);
		int nb=g.getNbBrindillesnonNeutre()+1;
		g.setNbBrindillesnonNeutre(nb);
	}
}

void Termite::donneOdeur(Grille &g){
	g.changeValueNid(devant(),equipe);
}

std::ostream &operator<<(std::ostream &out, Termite a)
{
	out<<flecheDirection[int(a.getDirection())];
	return out;
}

string to_string(Termite a)
{
	return flecheDirection[int(a.getDirection())];
}

// algoritheme de la termite:
// dans un tour elle bouge d'une case regarde si une brindille est devant si c'est le cas il l'a prend(essaye de rentre chez lui pour la reposer) puis verifie si son age a depase 30 tour (+chance de se reproduire)


void Termite::vieTermite(Grille &g){
	if(porteBrindille){
		if(nbDeplacement>=6 && brindilleEnFace(g) && voisinsLibre(g)>=2){
			while(!laVoieEstLibre(g))tourneAleat();
			dechargeBrindille(g);
		}
		else marcheAleat(g);
	}
	else{
		if(brindilleEnFace(g) && nbDeplacement>=6 && g.brindilleNeutre(devant())) prendBrindille(g);
		
		else { 
			marcheAleat(g);
		}
	}	
}


// test
void afficheGrille(Grille g, vector<Termite> termite)
{
	cout<<" ";
	for(int i = 0; i < tailleGrille; i++)cout<<"_"; 
	cout<<endl;
	for (int i = 0; i < tailleGrille; i++)
	{
		for (int j = 0; j < tailleGrille; j++)
		{
			if(j==0) cout<<"|";
			if (g.contientBrindille({i, j}))
				cout << "*";
			else if (g.numeroTermite({i, j}) != -1)
				cout << termite[g.numeroTermite({i, j})];

			else
				cout << " ";
			if(j==tailleGrille-1) cout<<"|";
		}
		cout << endl;
	}
	cout<<" ";
	for(int i = 0; i < tailleGrille; i++)cout<<"_"; 
	cout<<endl;
}


int nbJoueurEquipe(vector<Termite> *termite, int idEquipe){
	int s=0;
	for(int i=0; i<int(termite->size()); i++){
		if(termite->at(i).getEquipe()==idEquipe){
			s++;
		}
	}
	return s;
}