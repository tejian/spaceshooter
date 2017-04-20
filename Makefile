main.out: main.cc
	g++ -o main.out main.cc -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -std=c++11
