#ifndef CHARACTER
#define CHARACTER
#include "character.hpp"
#endif
class Player : public Character {
 public:
  Player(int x, int y, char character, int damage, int life, int numberLife);
};
