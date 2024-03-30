CXX=g++
CXXFLAGS= -Wall -std=c++11 -g -O3
EXEC_FILES= jeu
SFML_LIBS= -L C:/clibs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I C:/clibs/SFML-2.5.1/include

all: $(EXEC_FILES)
# Regle generique
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(SFML_INCLUDE)

test: coord.o grille.o termite.o test.o
	$(CXX) -o $@ $^ $(LDFLAGS)

projet: coord.o grille.o termite.o projet.o
	$(CXX) -o $@ $^ $(LDFLAGS)

jeu: coord.o grille.o termite.o jeu.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(SFML_LIBS)
	

coord.o: coord.hpp
grille.o: grille.hpp
termite.o: termite.hpp 
projet.o: coord.hpp grille.hpp termite.hpp
test.o: coord.hpp grille.hpp termite.hpp
jeu.o: coord.hpp grille.hpp termite.hpp

check: test
	./test

clean:
	rm -f *.o *.exe