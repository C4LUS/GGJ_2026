NAME    = ramasquemoi
CC      = g++
SRC     = $(wildcard src/*.cpp)
FLAGS   = -Iinclude -std=c++17
LIBS    = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

all:
	$(CC) $(SRC) -o $(NAME) $(FLAGS) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all