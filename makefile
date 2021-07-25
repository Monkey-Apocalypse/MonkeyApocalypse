CC = g++
CFLAGS = -c -Wall
OBJECTS = main.o engineGame.o character.o drawWindow.o player.o enemy.o coordinate.o item.o
LIBRARY = -lncurses

main: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LIBRARY)
	./main

main.o: main.cpp models/engineGame.hpp models/character.hpp models/drawWindow.hpp models/player.hpp models/enemy.hpp models/coordinate.hpp models/item.hpp
	$(CC) $(CFLAGS) main.cpp

engineGame.o: models/engineGame.cpp models/engineGame.hpp
	$(CC) $(CFLAGS) models/engineGame.cpp

character.o: models/character.cpp models/character.hpp
	$(CC) $(CFLAGS) models/character.cpp

player.o: models/player.cpp models/player.hpp
	$(CC) $(CFLAGS) models/player.cpp

drawWindow.o: models/drawWindow.cpp models/drawWindow.hpp
	$(CC) $(CFLAGS) models/drawWindow.cpp

enemy.o: models/enemy.cpp models/enemy.hpp
	$(CC) $(CFLAGS) models/enemy.cpp

coordinate.o: models/coordinate.cpp models/coordinate.hpp
	$(CC) $(CFLAGS) models/coordinate.cpp

item.o: models/item.cpp models/item.hpp
	$(CC) $(CFLAGS) models/item.cpp

clean:
	rm *.o main

format:
	clang-format -i -style=google ./**/*.cpp ./**/*.hpp
