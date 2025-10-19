# Replace this with the path
# if with homebrew, you get it from `brew info sfml`
SFML_PATH = /opt/homebrew/Cellar/sfml/3.0.0_1

cppFileNames := $(shell find ./script -type f -name "*.cpp")

MAIN_PATH = ./main

all: compile

compile:	
	g++ $(cppFileNames) -I$(SFML_PATH)/include -o $(MAIN_PATH) -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
	$(MAIN_PATH)
