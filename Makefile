all:
	g++ src/main.cpp -o bin/app -lSDL2 #-lSDL2_image -lSDL2_ttf 
	./bin/app
