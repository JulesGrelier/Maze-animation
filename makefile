# Replace this with the path you get from `brew info sfml`
SFML_PATH = /opt/homebrew/Cellar/sfml/3.0.0_1

# Replace "src" with the name of the folder where all your cpp code is
cppFileNames := $(shell find ./script -type f -name "*.cpp")

MAIN_PATH = ./main


all: compile

compile:	
	g++ $(cppFileNames) -I$(SFML_PATH)/include -o $(MAIN_PATH) -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -std=c++17
	$(MAIN_PATH)
