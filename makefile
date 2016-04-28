CC=g++
CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -Ilibs/include -DSFML_STATIC
LDFLAGS=-static-libgcc -static-libstdc++
LDLIBS=
ifeq ($(OS),Windows_NT)
	LDFLAGS+=-Llibs/lib/windows
	LDLIBS+=-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfreetype -ljpeg -lwinmm -lgdi32 -lopengl32
else
	LDFLAGS+=
	LDLIBS+=-lsfml-graphics -lsfml-window -lsfml-system
endif

vpath %.o obj
vpath %.cpp src

src_game=Main.cpp Map.cpp Tank.cpp Block.cpp BrickBlock.cpp WaterBlock.cpp Polygon.cpp Utils.cpp Core.cpp World.cpp Renderer.cpp Time.cpp Bullet.cpp

obj_game=$(addprefix obj/,$(src_game:.cpp=.o))

all: game

game: $(obj_game)
	$(CC) $(LDFLAGS) $(obj_game) $(LDLIBS) -o tanks_multiplayer

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	@$(RM) -r obj
	@$(RM) tanks_multiplayer

