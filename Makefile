# Папки
SRC_DIR := src
OBJ_DIR := src/file_o
BIN_DIR := bin
LIB_DIR := src/biblioteki

# Файлы
SOURCES := $(SRC_DIR)/main.cpp \
           $(SRC_DIR)/common/common.cpp \
           $(SRC_DIR)/musicPlayer/musicPlayer.cpp \
           $(SRC_DIR)/towerDefens/towerDefens.cpp \
           $(LIB_DIR)/tinyfiledialogs.c
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp,$(SOURCES))) \
          $(patsubst $(LIB_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SOURCES)))
EXECUTABLE := $(BIN_DIR)/app

# Компилятор и флаги
CC := g++
CFLAGS := -I$(LIB_DIR)/SDL2 -I$(LIB_DIR)
LDFLAGS := -L$(LIB_DIR)/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CXXFLAGS := -std=c++17 -Wall

# Цели
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Правило для .cpp файлов в корне src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Правило для .cpp файлов в src/common
$(OBJ_DIR)/common/%.o: $(SRC_DIR)/common/%.cpp | $(OBJ_DIR)/common
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Правило для .cpp файлов в src/musicPlayer
$(OBJ_DIR)/musicPlayer/%.o: $(SRC_DIR)/musicPlayer/%.cpp | $(OBJ_DIR)/musicPlayer
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Правило для .cpp файлов в src/towerDefens
$(OBJ_DIR)/towerDefens/%.o: $(SRC_DIR)/towerDefens/%.cpp | $(OBJ_DIR)/towerDefens
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Правило для .c файлов в src/biblioteki
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директорий
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/common:
	mkdir -p $(OBJ_DIR)/common

$(OBJ_DIR)/musicPlayer:
	mkdir -p $(OBJ_DIR)/musicPlayer

$(OBJ_DIR)/towerDefens:
	mkdir -p $(OBJ_DIR)/towerDefens

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/app

.PHONY: all clean
