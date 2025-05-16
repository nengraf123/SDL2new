# all:
# 	# g++ src/main.cpp -o bin/app $(pkg-config --cflags --libs sdl2)
# 	g++ src/main.cpp -o bin/app -lSDL2 -lSDL2_image -lSDL2_mixer #-lSDL2_image -lSDL2_ttf 
# 	./bin/app
all:
	g++ src/main.cpp src/tinyfiledialogs.c -o bin/app \
		-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	# g++ -std=c++17 src/main.cpp -o bin/app -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
	# g++ -std=c++17 src/main.cpp -o bin/app -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
	./bin/app
