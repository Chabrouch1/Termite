#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

#include "grille.hpp"
#include "coord.hpp"
#include "termite.hpp"

using namespace sf;

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

int dirToInt(Termite t)
{    // associe un entier correspondant a une direction
    int n = 0;
    switch (t.getDirection())
    {
    case Direction::nord:
        n = 0;
        break;
    case Direction::sud:
        n = 1;
        break;
    case Direction::est:
        n = 2;
        break;
    case Direction::ouest:
        n = 3;
        break;
    case Direction::nordEst:
        n = 5;
        break;
    case Direction::nordOuest:
        n = 4;
        break;
    case Direction::sudEst:
        n = 7;
        break;
    case Direction::sudOuest:
        n = 6;
        break;
    }

    return n;
}

Color termiteTeam(Termite *t)
{   // donne une couleur a une equipe rouge-> 3 / blue-> 1 / vert -> 2
    Color color;
    switch (t->getEquipe())
    {
    
    case 1:
        color = Color::Blue;
        break;
    case 2:
        color = Color::Green;
        break;
    case 3:
        color = Color::Red; 
        break;
    }
    return color;
}

void setTextProperties(Text &text, const string &str, int charSize, const Color &fillColor, float x, float y, Font &font)
{   
    // donne les proprietes du text a ecrire
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(charSize);
    text.setFillColor(fillColor);
    text.setPosition(x, y);
}

array<Color, 3> podiumColor(int teamR, int teamV, int teamB) {
    // renvoie l'ordre des termites gagnantes
    array<Color, 3> colors;

    if (teamR > teamV && teamR > teamB) {
        colors[0] = Color::Red;
        if (teamV > teamB) {
            colors[1] = Color::Green;
            colors[2] = Color::Blue;
        } else {
            colors[1] = Color::Blue;
            colors[2] = Color::Green;
        }
    } else if (teamV > teamR && teamV > teamB) {
        colors[0] = Color::Green;
        if (teamR > teamB) {
            colors[1] = Color::Red;
            colors[2] = Color::Blue;
        } else {
            colors[1] = Color::Blue;
            colors[2] = Color::Red;
        }
    } else {
        colors[0] = Color::Blue;
        if (teamR > teamV) {
            colors[1] = Color::Red;
            colors[2] = Color::Green;
        } else {
            colors[1] = Color::Green;
            colors[2] = Color::Red;
        }
    }

    return colors;
}

Color brinCol(Grille *g,Coord x){
    Color color(133, 87, 35);
    if(g->appartientNid(x)){
        switch (g->numeroNid(x))
        {
        
        case 1:
            color = Color::Blue;
            break;
        case 2:
            color = Color::Green;
            break;
        case 3:
            color = Color::Red; 
            break;
        }
    }
    return color;
}

int main()
{
    // longeur et largeur de la fenetre
    const int WIDHT = 1400;
    const int HEIGHT = 800;
    const int INFOPANNELWIDHT = 260; // longeur de la partie des informations

    // longuer et largeur d'une cellule
    const float cellWidht = (WIDHT - INFOPANNELWIDHT) / tailleGrille;
    const float cellHeight = HEIGHT / tailleGrille;

    // chargement des images
    // creation des variables pour les images

    Texture brindilleImg;
    Sprite spriteB;
    Texture backGroundImg;
    Sprite spriteBack;
    Texture menuBack;
    Sprite menuBackSprite;
    Texture termiteLogo;
    Sprite termiteLogoSprite;
    Texture podium;
    Sprite podiumSprite;
    Texture termiteWin1;
    Sprite termiteWin1Sprite;
    Texture termiteWin2;
    Sprite termiteWin2Sprite;
    Texture termiteLose;
    Sprite termiteLoseSprite;
    Texture coupe;
    Sprite coupeSprite;
    Image icon;
    

    array<String, 8> dir = {"Nord", "Sud", "Est", "Ouest", "NordOuest", "NordEst", "SudOuest", "SudEst"};

    array<Texture, 8> termiteDirectionTextures;
    array<Texture, 8> termiteBrindilleDirectionTextures;

    array<Sprite, 8> termiteDirectionSprites;
    array<Sprite, 8> termiteBrindilleDirectionSprites;

    // differentes directions de la termite
    for (int i = 0; i < 8; i++)
    {

        if (!termiteDirectionTextures[i].loadFromFile("assets/termite/termite" + dir[i] + ".png") || 
        !termiteBrindilleDirectionTextures[i].loadFromFile("assets/TermiteBrindille/termitePorteBrindille" + dir[i] + ".png")) // Si le chargement du fichier a échoué
        {
            std::cerr << "Erreur durant le chargement de l'image" << endl; // affiche l'erreur
            return EXIT_FAILURE;                                           // On ferme le programme
        }
        else // Si le chargement de l'image a réussi
        {
            termiteDirectionSprites[i].setTexture(termiteDirectionTextures[i]);
            termiteBrindilleDirectionSprites[i].setTexture(termiteBrindilleDirectionTextures[i]);
        }

        termiteDirectionSprites[i].setScale((cellWidht+20) / termiteDirectionSprites[i].getLocalBounds().width,
                                            (cellHeight+20) / termiteDirectionSprites[i].getLocalBounds().height);

        termiteBrindilleDirectionSprites[i].setScale((cellWidht+20) / termiteBrindilleDirectionSprites[i].getLocalBounds().width,
                                                     (cellHeight+20) / termiteBrindilleDirectionSprites[i].getLocalBounds().height);
    }

    // background et la brindille
    if (!brindilleImg.loadFromFile("assets/brindilleImg.png") || !backGroundImg.loadFromFile("assets/grassBackground.jpg") || 
    !icon.loadFromFile("assets/terIcon.png") || !menuBack.loadFromFile("assets/backGround.jpg") || !termiteLogo.loadFromFile("assets/cartoonTermite.png") ||
    !podium.loadFromFile("assets/podium.png") || !termiteWin1.loadFromFile("assets/termite/termite1.png") || 
    !termiteWin2.loadFromFile("assets/termite/termite2.png") || !termiteLose.loadFromFile("assets/termite/termite3.png") ||
    !coupe.loadFromFile("assets/coupe.png") ) // Si le chargement du fichier a échoué
    {
        std::cerr << "Erreur durant le chargement de l'image" << endl; // affiche l'erreur
        return EXIT_FAILURE;                                           // On ferme le programme
    }
    else // Si le chargement de l'image a réussi
    {

        spriteB.setTexture(brindilleImg);     // image de la brindille
        spriteBack.setTexture(backGroundImg); // le fond du jeu
        menuBackSprite.setTexture(menuBack);
        termiteLogoSprite.setTexture(termiteLogo);
        podiumSprite.setTexture(podium);
        termiteWin1Sprite.setTexture(termiteWin1);
        termiteWin2Sprite.setTexture(termiteWin2);
        termiteLoseSprite.setTexture(termiteLose);
        coupeSprite.setTexture(coupe);
    }
    
    // mettre les images a l'echelle

    spriteB.setScale((cellWidht-20) / spriteB.getLocalBounds().width,
                     (cellWidht-20) / spriteB.getLocalBounds().width);

    spriteBack.setScale((WIDHT - INFOPANNELWIDHT) / spriteBack.getLocalBounds().width,
                        HEIGHT / spriteBack.getLocalBounds().height);
    menuBackSprite.setScale(WIDHT  / menuBackSprite.getLocalBounds().width,
                        HEIGHT / menuBackSprite.getLocalBounds().height);

    podiumSprite.setScale(WIDHT  / podiumSprite.getLocalBounds().width,
                        HEIGHT / podiumSprite.getLocalBounds().height);
    
    termiteWin1Sprite.setScale((WIDHT/3)  / termiteWin1Sprite.getLocalBounds().width,
                        (HEIGHT/2) / termiteWin1Sprite.getLocalBounds().height);
    termiteWin2Sprite.setScale((WIDHT/3)  / termiteWin2Sprite.getLocalBounds().width,
                        (HEIGHT/2) / termiteWin2Sprite.getLocalBounds().height);
    termiteLoseSprite.setScale((WIDHT/3) / termiteLoseSprite.getLocalBounds().width,
                        (HEIGHT/2) / termiteLoseSprite.getLocalBounds().height);
    
    coupeSprite.setScale((WIDHT/4) / coupeSprite.getLocalBounds().width,
                        (HEIGHT/4) / coupeSprite.getLocalBounds().height);
    
    termiteWin1Sprite.setPosition(420,100);
    termiteWin2Sprite.setPosition(100,200);
    termiteLoseSprite.setPosition((WIDHT/2)+20,200);
    coupeSprite.setPosition(600,50);
    coupeSprite.rotate(10);

    vector<Termite> termites;

    Grille g = creaGrilleAlea(&termites);

    map<Coord, Sprite> BrindilleSprites;

    for (int i = 0; i < tailleGrille; i++)
    {
        for (int j = 0; j < tailleGrille; j++)
        {
            BrindilleSprites[{i, j}] = spriteB;
        }
    }


    vector<Sprite> termiteSprites(termites.size(), spriteB);
    vector<Sprite> termitePorteSprites(termites.size(), spriteB);
    
    float x,y=0;

    Font openSansBold;
    Font openSansLight;
    if (!openSansBold.loadFromFile("fonts/OpenSansBold.ttf") || !openSansLight.loadFromFile("fonts/openSansLight.ttf"))
    {
        std::cerr << "Erreur durant le chargement de la police" << endl; // affiche l'erreur
        return EXIT_FAILURE;                                             // On ferme le programme
    }

    Text equipeRouge;
    Text equipeVerte;
    Text equipeBlue;
    Text nbBrindilleRestant;
    Text nbBrin;
    Text TermiteSimulation;
    Text nbPRouge,nbPBlue,nbPVert;
    int nbB = g.getNbBrindilles() - g.getNbBrindillesnonNeutre();
    int nbPR=0;
    int nbPB=0;
    int nbPV=0;

    setTextProperties(equipeRouge, "Equipe Rouge : ", 24, Color::White, WIDHT - INFOPANNELWIDHT + 20, 20, openSansBold);
    setTextProperties(equipeVerte, "Equipe Verte : ", 24, Color::White, WIDHT - INFOPANNELWIDHT + 20, 220, openSansBold);
    setTextProperties(equipeBlue, "Equipe Blue : ", 24, Color::White, WIDHT - INFOPANNELWIDHT + 20, 420, openSansBold);

    setTextProperties(nbBrindilleRestant, "nombre de brindilles neutres restant : ", 12, Color::White, WIDHT - INFOPANNELWIDHT + 20, 620, openSansBold);
    setTextProperties(nbBrin, to_string(nbB), 42, Color::White, WIDHT - INFOPANNELWIDHT + 70, 690, openSansBold);

    setTextProperties(TermiteSimulation, "Termite Simulation", 60, Color::White, WIDHT/3, 100, openSansBold);

    setTextProperties(nbPRouge, to_string(nbPR), 42, Color::White,  WIDHT - INFOPANNELWIDHT + 70, 70, openSansBold);
    setTextProperties(nbPVert, to_string(nbPB), 42, Color::White,  WIDHT - INFOPANNELWIDHT + 70, 270, openSansBold);
    setTextProperties(nbPBlue, to_string(nbPR), 42, Color::White,  WIDHT - INFOPANNELWIDHT + 70, 470, openSansBold);


    SoundBuffer buffer;
    if (!buffer.loadFromFile("sound/Sea_Shanty_2.ogg"))
        std::cerr << "erreur de changerment de fichier de music" << endl;

    Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(50);
    sound.play();
    sound.setLoop(true);
    // boucle principale du jeu

    RenderWindow mainMenu(VideoMode(WIDHT, HEIGHT), "Main Menu");
    mainMenu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    
    
    // Create star button
    Text starButton("Start", openSansBold, 50);
    starButton.setPosition(mainMenu.getSize().x / 2 - starButton.getGlobalBounds().width / 2,
                           mainMenu.getSize().y / 2 - starButton.getGlobalBounds().height / 2);




    // boucle principale du menu
    while (mainMenu.isOpen())
    {
         // gere les evenements
        Event event;
        while (mainMenu.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                mainMenu.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    // si on a appuier sur le bouton start
                    if (starButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        mainMenu.close(); // ferme la fenetre du menu et on ouvre le jeu
                        RenderWindow window(VideoMode(WIDHT, HEIGHT), "Simulations des Termites");
                        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
                        window.setFramerateLimit(60);
                        while (window.isOpen()) // boucle principale du jeu
                        {

                            Event event; // appuis d'un bouton
                            while (window.pollEvent(event))
                            {
                                // ferme la fenetre si on appuis sur le bouton de la fermeture
                                if (event.type == Event::Closed)
                                    window.close();
                            }

                            // affichage
                            window.clear();
                            window.draw(spriteBack);

                            for (int i = 0; i < tailleGrille; i++)
                            {

                                for (int j = 0; j < tailleGrille; j++)
                                {

                                    // calcule des coordoner de la case de la grille dans la fenetre
                                    x=i*cellWidht;
                                    y=j*cellHeight;
                                    if (g.contientBrindille({i, j}))
                                    { // si la case contient une brindille on affiche une brindille
                                        // calcul des coordonee de la brindille dans la grille
                                        
                                        BrindilleSprites[{i, j}].setPosition(x, y);
                                        BrindilleSprites[{i, j}].setColor(brinCol(&g,{i,j}));
                                        window.draw(BrindilleSprites[{i, j}]);
                                    }
                                    else if (g.numeroTermite({i, j}) != -1)
                                    { // si c'est une termite
                                        // calcul des coordonee de la termite dans la grille
                                        
                                        Termite t = termites[g.numeroTermite({i, j})];

                                        if (t.getPorte())
                                        { // si elle porte une brindille affichage de l'image de la termite avec la brindille
                                            termitePorteSprites[g.numeroTermite({i, j})] = termiteBrindilleDirectionSprites[dirToInt(t)];
                                            termitePorteSprites[g.numeroTermite({i, j})].setColor(termiteTeam(&t));
                                            termitePorteSprites[g.numeroTermite({i, j})].setPosition(x, y);
                                            window.draw(termitePorteSprites[g.numeroTermite({i, j})]);
                                        }
                                        else
                                        {
                                            // sinon affichage de l'image de termite
                                            termiteSprites[g.numeroTermite({i, j})] = termiteDirectionSprites[dirToInt(t)]; // rotation de la termite en fonction de sa direction
                                            termiteSprites[g.numeroTermite({i, j})].setColor(termiteTeam(&t));
                                            termiteSprites[g.numeroTermite({i, j})].setPosition(x, y);
                                            window.draw(termiteSprites[g.numeroTermite({i, j})]);
                                        }
                                    }
                                }
                            }
                            if (nbB>0) //arrete l'arriere plan si le jeu est fini
                            {
                                for (int i = 0; i < int(termites.size()); i++)
                                {
                                    termites[i].vieTermite(g);
                                }
                                afficheGrille(g, termites);
                                cout<<"nombre points de l'Equipe 1 : "<<g.nbPointsEquipe(1)<<endl;
                                cout<<"nombre points de l'Equipe 2 : "<<g.nbPointsEquipe(2)<<endl;
                                cout<<"nombre points de l'Equipe 3 : "<<g.nbPointsEquipe(3)<<endl;
                            }
                            
                            
                            if (nbB==0) //affiche le podium pour la termite gagnate
                            {   
                                
                                
                                    window.draw(podiumSprite);
                                    termiteWin1Sprite.setColor(podiumColor(nbPR,nbPV,nbPB)[0]);
                                    window.draw(termiteWin1Sprite);
                                    termiteWin2Sprite.setColor(podiumColor(nbPR,nbPV,nbPB)[1]);
                                    window.draw(termiteWin2Sprite);
                                    termiteLoseSprite.setColor(podiumColor(nbPR,nbPV,nbPB)[2]);
                                    window.draw(termiteLoseSprite);
                                    window.draw(coupeSprite);
                                
                                
                            }
                            
                            // affichage du jeu
                            
                            sleep(milliseconds(125)); // le programme prend une pause de 150 millisecondes pour que l'utilisateur peut reamrquer l'evolution des termites
                            window.draw(equipeRouge);
                            window.draw(equipeVerte);
                            window.draw(equipeBlue);
                            window.draw(nbBrindilleRestant);
                            nbPB=g.nbPointsEquipe(1);
                            nbPR=g.nbPointsEquipe(3);
                            nbPV=g.nbPointsEquipe(2);
                            nbPRouge.setString(to_string(nbPR));
                            nbPVert.setString(to_string(nbPV));
                            nbPBlue.setString(to_string(nbPB));
                            nbB = g.getNbBrindilles() - g.getNbBrindillesnonNeutre();
                            nbBrin.setString(to_string(nbB));
                            window.draw(nbPRouge);
                            window.draw(nbPVert);
                            window.draw(nbPBlue);
                            window.draw(nbBrin);
                            window.display();
                        }
                    }
                }
            }
        }

        // affichage du  menu
        mainMenu.clear();
        mainMenu.draw(menuBackSprite);
        mainMenu.draw(TermiteSimulation);
        mainMenu.draw(termiteLogoSprite);
        mainMenu.draw(starButton);
        mainMenu.display();
    }

    return 0;
}
