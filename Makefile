main.out: main.cc
	g++ -o main.out main.cc -lsdl2 -lsdl2_image -lsdl2_mixer -lsdl2_ttf -std=c++11