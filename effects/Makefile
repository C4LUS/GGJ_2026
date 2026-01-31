CC = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -O2
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lm

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = effects

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
