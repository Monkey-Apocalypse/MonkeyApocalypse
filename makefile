demo: main.o menu.o character.o enemyKamikaze.o
	g++ -o main main.o menu.o character.o enemyKamikaze.o -lncurses 
	./main
demo.o: main.cpp
	g++ -c main.cpp
menu.o: src/menu.cpp
	g++ -c src/menu.cpp
character.o: src/character.cpp
	g++ -c src/character.cpp
enemyKamikaze.o: src/enemyKamikaze.cpp
	g++ -c src/enemyKamikaze.cpp
clean:
	rm *.o main