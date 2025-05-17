CC := g++
CFLAGS := -Isrc/biblioteki/SDL2 -Isrc/biblioteki -std=c++17 -Wall
TINY_CFLAGS := $(CFLAGS) -Wno-format-overflow
LDFLAGS := -Lsrc/biblioteki/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJDIR := src/file_o
BINDIR := bin
SRCS := src/main.cpp src/common/common.cpp src/mainMenu/mainMenu.cpp src/musicPlayer/musicPlayer.cpp src/settings/settings.cpp src/towerDefens/towerDefens.cpp
TINY_SRC := src/biblioteki/tinyfiledialogs.c
OBJS := $(SRCS:%.cpp=$(OBJDIR)/%.o) $(OBJDIR)/src/biblioteki/tinyfiledialogs.o
TARGET := $(BINDIR)/app

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/src/biblioteki/tinyfiledialogs.o: $(TINY_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(TINY_CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
