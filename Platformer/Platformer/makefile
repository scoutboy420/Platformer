#COMPILER
CC = g++
CFLAGS = -std=c++11 -Wall

#LIBRARIES
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

#FOLDERS
BIN = bin
OBJ = $(BIN)/obj
EXE = $(BIN)/game

#TARGET
TARGET = $(EXE)/game.out

#FILES
SOURCE_FILES= main.cpp
OBJECT_FILES = $(SOURCE_FILES:%.cpp=$(OBJ)/%.o)

all: $(TARGET)

clean:
	rm -r -f $(BIN)

.PHONY: all game clean

$(TARGET): $(OBJECT_FILES)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<