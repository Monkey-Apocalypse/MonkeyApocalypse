#include <iostream>
#include <ncurses.h>
using namespace std;

class Character{
    protected:
        int direction; // Input da tastiera per il movimento del character
        int x;
        int y;
    public:
   		Character(int x, int y);
        int getX();
        int getY();
    	int moveCharacter();
};

