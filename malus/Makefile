CXX = g++
CXXFLAGS = -std=c++17 -Wall -Ieffects


SRCS = Main.cpp Malus.cpp \
	effects/BlurEffect.cpp \
	effects/GrayscaleEffect.cpp \
	effects/ScreenShakeEffect.cpp \
	effects/WaveDistortionEffect.cpp \
	effects/ReverseEffect.cpp \
	effects/SplitEffect.cpp
OBJS = $(SRCS:.cpp=.o)

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o main

fclean: clean
	rm -f effects/*.o main
