SRC = main.cpp
NAME = ramasquemoi
CC = g++

FLAGS = -Wall -Wextra -O3
LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME) $(FLAGS) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all