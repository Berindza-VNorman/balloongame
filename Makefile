all: compile link

compile:
	g++ -Isrc/include -c tilemap.cpp tile.cpp game.cpp main.cpp balloon.cpp MainMenu.cpp tower.cpp

link:
	g++ *.o -o game -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main




