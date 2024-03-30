// -*- coding: utf-8 -*-
#include <stdexcept>
#include <vector>
#include <string>
#include <random>
#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"
#include <unistd.h>

using namespace std;

Grille creaGrilleAlea(vector<Termite> *termites) {
    Grille g;
	
	int nbNid=1;
	while(nbNid<4){
        Coord c((rand()/tailleGrille)%tailleGrille,(rand()/tailleGrille)%tailleGrille);
		if(g.appartientNid(c))break;
		else {
			g.changeValueNid(c,nbNid);
			nbNid++;
		}
    }
    int nbT =0;
	int nbB=0;
	int id=0;
    for (int i=0;i<tailleGrille;i++){
        for (int j=0; j<tailleGrille; j++){
            if (g.appartientNid({i,j})){
                continue;
            }
            else {
                switch ((rand()/tailleGrille)%9) {
                    case 0:
                        if (double(rand())/RAND_MAX > densiteBrindille){
                            g.poseBrindille({i,j});
							nbB++;
							g.setNbBrindilles(nbB);
                        }
                        break;
                    case 1:
                        if (nbT<nbTermites){
                            termites->push_back({{i,j},id,stringDirection[rand()%8]});
                            nbT++;
							id++;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
	if (termites->size()%3==1) termites->pop_back();
	else if(termites->size()%3==2){
		termites->pop_back();
		termites->pop_back();
	}
    int tier=termites->size()/3;
    
    for (int i=0; i<int(termites->size()); i++){
		if(i<tier)g.poseTermite(termites->at(i).getCoord(),termites->at(i).getIdT());
        else if (i<tier*2){
			termites->at(i).setEquipe(2);
			g.poseTermite(termites->at(i).getCoord(),termites->at(i).getIdT());
		}
        else {
			termites->at(i).setEquipe(3);
			g.poseTermite(termites->at(i).getCoord(),termites->at(i).getIdT());
		}
	}
    return g;
}


int main(){
    int timer=400000;
	srand(time(0)); 
	vector<Termite>termites;
    Grille g=creaGrilleAlea(&termites);
	afficheGrille(g,termites);
    string n="";
    // int nbPasse=10;
	int nbPasse;
	cout<<" Combien veux tu d'itération entre chaque affichage ?"<<endl;
	cin>>nbPasse;
    while (n!="." && g.getNbBrindilles()!=g.getNbBrindillesnonNeutre()){
        for (int j = 0; j < nbPasse; j++){
            for(int i=0;i<int(termites.size());i++){
                termites[i].vieTermite(g);
				if (g.getNbBrindilles()==g.getNbBrindillesnonNeutre())break;
            }
            system("clear");
            afficheGrille(g,termites);
            usleep(timer);
            
			if (g.getNbBrindilles()==g.getNbBrindillesnonNeutre())break;
        }
        system("clear");
        afficheGrille(g,termites);
        cout<<"nombre points de l'Equipe 1 : "<<g.nbPointsEquipe(1)<<endl;
        cout<<"nombre points de l'Equipe 2 : "<<g.nbPointsEquipe(2)<<endl;
        cout<<"nombre points de l'Equipe 3 : "<<g.nbPointsEquipe(3)<<endl;
		if (g.getNbBrindilles()==g.getNbBrindillesnonNeutre())break;
		cout<<"si tu veux multiplier le nombre d'itération par 2 appuie sur * si tu veux le diviser par 2 appuie sur / si tu veux arrêter le programme appuie sur ."<<endl;
        cin>>n;
        if (n=="*")nbPasse*=2;
		else if (n=="/")nbPasse/=2;
        else if (n=="4")timer-=200000; 
        else if (n=="5")timer+=200000;
    }
	g.equipeGagnante();
    return 0;
}