#include "player.hpp"
Player::Player(int x, int y, char character, int damage, int life, int numberLife)
    : Character::Character(x, y, character, damage, life, numberLife) {
  this->x = x;
  this->y = y;
  this->character = character;
  this->damage = damage;
  this->life = life;
  this->numberLife = numberLife;
}
