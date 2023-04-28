FILES= ./build/main.o ./build/system.o ./build/render.o ./build/getch.o ./build/shapes.o ./build/helper.o
INCLUDES= -I./src
LINK_FLAGS = -lm
FLAGS= -Wall -O0

all: $(FILES)
	gcc $(FILES) $(INCLUDES) $(LINK_FLAGS) -o ./bin/raycaster

./build/main.o: ./src/main.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/main.c -o ./build/main.o

./build/system.o: ./src/util/system.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/util/system.c -o ./build/system.o

./build/render.o: ./src/graphics/render.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/graphics/render.c -o ./build/render.o

./build/shapes.o: ./src/graphics/shapes.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/graphics/shapes.c -o ./build/shapes.o

./build/getch.o: ./src/util/getch.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/util/getch.c -o ./build/getch.o

./build/helper.o: ./src/util/helper.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/util/helper.c -o ./build/helper.o

clean:
	rm -rf $(FILES)
	rm -rf ./bin/raycaster