FILES= ./build/main.o ./build/system.o ./build/render.o
INCLUDES= -I./src
FLAGS= -g -Wall -O0

all: $(FILES)
	gcc $(FILES) -o ./bin/raycaster

./build/main.o: ./src/main.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/main.c -o ./build/main.o

./build/system.o: ./src/util/system.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/util/system.c -o ./build/system.o

./build/render.o: ./src/graphics/render.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/graphics/render.c -o ./build/render.o

clean:
	rm -rf $(FILES)
	rm -rf ./bin/raycaster