build:
	gcc *.c -IC:\SDL2\include\SDL2 -LC:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -Wall -mwindows -o ./build/build.exe
	
debug-build:
	gcc *.c -IC:\SDL2\include\SDL2 -LC:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -Wall -o ./build/build.exe