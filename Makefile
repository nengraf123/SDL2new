# all:
# 	# g++ src/main.cpp -o bin/app $(pkg-config --cflags --libs sdl2)
# 	g++ src/main.cpp -o bin/app -lSDL2 -lSDL2_image -lSDL2_mixer #-lSDL2_image -lSDL2_ttf 
# 	./bin/app
# g++ -std=c++17 src/main.cpp -o bin/app -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf 
# g++ -std=c++17 src/main.cpp -o bin/app -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf 
# g++ src/main.cpp src/tinyfiledialogs.c -o bin/app \
# 	-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
#
#
#
# all:
# 	g++ src/main.cpp src/tinyfiledialogs.c -o bin/app -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
# 	./bin/app

# Компилятор
CC = g++

# Флаги компиляции
CFLAGS = -Wall -g

# Флаги для SDL2 библиотек
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Директории
SRC_DIR = src
BIN_DIR = bin
COMMON_DIR = $(SRC_DIR)/common
MUSICPLAYER_DIR = $(SRC_DIR)/musicPlayer
TOWERDEFENS_DIR = $(SRC_DIR)/towerDefens

# Исходные файлы
SOURCES = $(SRC_DIR)/main.cpp \
          $(COMMON_DIR)/common.cpp \
          $(MUSICPLAYER_DIR)/musicPlayer.cpp \
          $(TOWERDEFENS_DIR)/towerDefens.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Имя исполняемого файла
EXEC = $(BIN_DIR)/app

# Правило по умолчанию
all: $(EXEC)

# Создание исполняемого файла
$(EXEC): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(SDL_LDFLAGS)

# Компиляция исходных файлов
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

$(COMMON_DIR)/%.o: $(COMMON_DIR)/%.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

$(MUSICPLAYER_DIR)/%.o: $(MUSICPLAYER_DIR)/%.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

$(TOWERDEFENS_DIR)/%.o: $(TOWERDEFENS_DIR)/%.cpp
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(EXEC)

# Полная очистка
distclean: clean
	rm -rf $(BIN_DIR)

.PHONY: all clean distclean
