GG = g++

all : desktop move

move :
	cp -r assets ./build

desktop : main.cpp ./src/app.cpp ./src/beeper.cpp ./src/chip8.cpp
	$(GG) main.cpp ./src/app.cpp ./src/beeper.cpp ./src/chip8.cpp -lSDL2 -o ./build/chip8 -std=c++14

rundesktop:
	./build/chip8

CC = emcc
em: main.cpp ./src/app.cpp ./src/beeper.cpp ./src/chip8.cpp
	$(CC) main.cpp ./src/app.cpp ./src/beeper.cpp ./src/chip8.cpp -O2 -s TOTAL_MEMORY=67108864 -s USE_SDL=2 --preload-file assets -o ./build/chip8.html -std=c++14 --emrun
