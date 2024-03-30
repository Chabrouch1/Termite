#include <stdexcept>
#include <vector>
#include <string>
#include <random>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp"

TEST_CASE("Test Operateur d'affichage d'une coordonnée"){
    ostringstream ch;
    ch<<Coord{5,6};
    CHECK(ch.str()=="(5,6)");
    ostringstream th;
    th<<Coord{5,8};
    CHECK(th.str()=="(5,8)");
}

TEST_CASE("Test Operateur d'affichage d'une direction"){
    ostringstream ch;
    ch<<Direction::nordOuest;
    CHECK(ch.str()=="nord-ouest");
    ostringstream th;
    th<<Direction::sudOuest;
    CHECK(th.str()=="sud-ouest");
	ostringstream vh;
    vh<<Direction::ouest;
    CHECK(vh.str()=="ouest");
}

// TEST_CASE("Test affichage de Direction"){
//   //tester tout les valeurs de Direction
//   for(int i=0;i<stringDirection.size();i++){
//     ostringstream ch;
//     ch<<stringDirection[i];
//     CHECK(ch.str()==stringDirectionTest[i]);
//   }
// }


// Tests d'opérateurs d'égalité

TEST_CASE("Test Operateur == de coordonnee") {

  CHECK(Coord{18,18}==Coord{18,18});
  CHECK(Coord{1,1}==Coord{1,1});
  CHECK(Coord{0,0}==Coord{0,0});
  CHECK(Coord{20,20}==Coord{20,20});
}
  
TEST_CASE("Test Operateur !=") {
  CHECK(Coord{18,18}!=Coord{0,18});
  CHECK(Coord{1,1}!=Coord{1,3});
}



TEST_CASE("Test des fonctions getLig et getCol"){
	CHECK(Coord{0,0}.getLig()==0);
	CHECK(Coord{0,0}.getCol()==0);

	CHECK(Coord{0,5}.getLig()==0);
	CHECK(Coord{0,5}.getCol()==5);

	CHECK(Coord{5,0}.getLig()==5);
	CHECK(Coord{5,0}.getCol()==0);

	CHECK(Coord{20,20}.getLig()==20);
	CHECK(Coord{20,20}.getCol()==20);

	CHECK(Coord{20,5}.getLig()==20);
	CHECK(Coord{20,5}.getCol()==5);

	CHECK(Coord{5,20}.getLig()==5);
	CHECK(Coord{5,20}.getCol()==20);

	CHECK(Coord{7,9}.getLig()==7);
	CHECK(Coord{7,9}.getCol()==9);
}

  

// Tests des fonctions de direction

TEST_CASE("Test Operateur de la fonction devantCoord"){
	CHECK(Coord{5,5}.devantCoord(Direction::nordOuest)==Coord{6,4});
	CHECK(Coord{5,5}.devantCoord(Direction::nord)==Coord{6,5});
	CHECK(Coord{5,5}.devantCoord(Direction::nordEst)==Coord{6,6});
	CHECK(Coord{5,5}.devantCoord(Direction::est)==Coord{5,6});
	CHECK(Coord{5,5}.devantCoord(Direction::sudEst)==Coord{4,6});
	CHECK(Coord{5,5}.devantCoord(Direction::sud)==Coord{4,5});
	CHECK(Coord{5,5}.devantCoord(Direction::sudOuest)==Coord{4,4});
	CHECK(Coord{5,5}.devantCoord(Direction::ouest)==Coord{5,4});

	// test de avance tourne 4 fois puis avance
	Coord c{8,8};
	Direction d=Direction::nord;
	c=c.devantCoord(d);
	for(int i=0;i<4;i++){
		d=aDroite(d);
	}
	c=c.devantCoord(d);
	CHECK(c==Coord{8,8});

	//test de cas limite
	CHECK(Coord{0,8}.devantCoord(Direction::sud)==Coord{19,8});
	CHECK(Coord{19,4}.devantCoord(Direction::nord)==Coord{0,4});
	CHECK(Coord{0,0}.devantCoord(Direction::sudOuest)==Coord{19,19});
	CHECK(Coord{0,19}.devantCoord(Direction::sudEst)==Coord{19,0});
	CHECK(Coord{19,0}.devantCoord(Direction::nordOuest)==Coord{0,19});
	CHECK(Coord{19,19}.devantCoord(Direction::nordEst)==Coord{0,0});
	CHECK(Coord{5,19}.devantCoord(Direction::est)==Coord{5,0});
	CHECK(Coord{7,0}.devantCoord(Direction::ouest)==Coord{7,19});
}


TEST_CASE("Test Operateur de la fonction aGauche"){
	CHECK(aGauche(Direction::nordOuest)==Direction::ouest);  //cas limite
	CHECK(aGauche(Direction::nord)==Direction::nordOuest);
	CHECK(aGauche(Direction::nordEst)==Direction::nord);
	CHECK(aGauche(Direction::est)==Direction::nordEst);
	CHECK(aGauche(Direction::sudEst)==Direction::est);
	CHECK(aGauche(Direction::sud)==Direction::sudEst);
	CHECK(aGauche(Direction::sudOuest)==Direction::sud);
	CHECK(aGauche(Direction::ouest)==Direction::sudOuest);
}

TEST_CASE("Test Operateur de la fonction aDroite"){
	CHECK(aDroite(Direction::nordOuest)==Direction::nord);
	CHECK(aDroite(Direction::nord)==Direction::nordEst);
	CHECK(aDroite(Direction::nordEst)==Direction::est);
	CHECK(aDroite(Direction::est)==Direction::sudEst);
	CHECK(aDroite(Direction::sudEst)==Direction::sud);
	CHECK(aDroite(Direction::sud)==Direction::sudOuest);
	CHECK(aDroite(Direction::sudOuest)==Direction::ouest);
	CHECK(aDroite(Direction::ouest)==Direction::nordOuest);  //cas limite
}


TEST_CASE("tests combinés aDroite et aGauche"){
  //tourner a gauche puis a droite
  for(int i=0;i<8;i++){
    CHECK(aDroite(aGauche(stringDirection[i]))==stringDirection[i]);
  }

  //tourner a droite puis a gauche
  for(int i=0;i<8;i++){
    CHECK(aGauche(aDroite(stringDirection[i]))==stringDirection[i]);
  }

  //test tourner 8 fois à aGauche
  Direction a=Direction::nord;
  for(int i=0; i<8;i++){
    a= aGauche(a);
  }
  CHECK(a==Direction::nord);
 
	//test tourner 8 fois à aDroite
  Direction b=Direction::nord;
  for(int i=0; i<8;i++){
    b= aDroite(b);
  }
  CHECK(b==Direction::nord);
}


TEST_CASE("Tests des fonctions pour brindille"){
  Grille g=Grille();
  g.poseBrindille(Coord{1,1});
  CHECK(g.contientBrindille(Coord{1,1}));
  CHECK_FALSE(g.contientBrindille(Coord{0,0}));
  g.enleveBrindille(Coord{1,1});
  CHECK_FALSE(g.contientBrindille(Coord{1,1}));

}

TEST_CASE("Test de fonction pour termites"){
  Grille g;
  g.poseTermite(Coord{1,1},1);
  CHECK(g.numeroTermite(Coord{1,1})==1);
  g.enleveTermite(Coord{1,1});
  CHECK(g.numeroTermite(Coord{1,1})==-1);
}

TEST_CASE("Test de grille vide"){
	Grille g;
	g.poseTermite(Coord{1,1},1);
	g.poseBrindille(Coord{19,19});
	CHECK_FALSE(g.estVide(Coord{19,19}));
	CHECK_FALSE(g.estVide(Coord {1,1}));
	CHECK(g.estVide(Coord {0,0}));
	CHECK(g.estVide(Coord {18,18}));
  
}

TEST_CASE("Brindille en face"){
	Grille g;
	Termite t{{5,5},0,Direction::est};
	
	g.poseTermite(t.getCoord(),t.getIdT());
	CHECK_FALSE(t.brindilleEnFace(g));
	g.poseBrindille({5,6});
	CHECK(t.brindilleEnFace(g));
	g.enleveBrindille({5,6});
	g.poseBrindille({5,4});
	CHECK_FALSE(t.brindilleEnFace(g));
}

int main(int argc, const char **argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
  return 0;
}




