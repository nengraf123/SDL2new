all:
	g++ src/main.cpp -o bin/app sdl2_wayland -lSDL2
	./bin/app
