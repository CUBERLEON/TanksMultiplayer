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

src_sys=Utils.cpp Time.cpp Polygon.cpp
src_main=Main.cpp Map.cpp Tank.cpp Block.cpp BrickBlock.cpp WaterBlock.cpp Core.cpp World.cpp Renderer.cpp Bullet.cpp

obj_sys=$(addprefix obj/sys/,$(src_sys:.cpp=.o))
obj_main=$(addprefix obj/,$(src_main:.cpp=.o))

all: game

game: $(obj_main) $(obj_sys)
	$(CC) $(LDFLAGS) $(obj_main) $(obj_sys) $(LDLIBS) -o tanks_multiplayer

obj/%.o: src/%.cpp
	@mkdir -p obj/sys
	@mkdir -p obj
	$(CXX) -c $(CXXFLAGS) $^ -o $@

clean:
	@$(RM) -r obj
	@$(RM) tanks_multiplayer

