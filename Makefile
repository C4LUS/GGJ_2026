NAME        = ramask_moi
CXX         = g++
CXXFLAGS    = -std=c++17 -Wall -Wextra -g -I. -Iinclude
LDFLAGS     = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS        = $(wildcard *.cpp) $(wildcard src/*.cpp)
OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
