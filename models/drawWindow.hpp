#include "character.hpp"
#ifndef ENEMY
#define ENEMY
#include "enemy.hpp"
#endif
class DrawWindow {
 public:
  DrawWindow();
  void printCharacter(int x, int y, char c);
  void drawRect(int startX, int startY, int width, int heigth,
                pEnemyList enemyList);
  void drawMenu();
  void printCommand(int* cnt);
  void printCredits();
  void credits(int direction);
  void printHowToPlay();
  void HowToPlay(int direction);
  void drawStats(int startX, int startY, int width, int heigth, long* points,
                 Character character, pEnemyList enemyList);
  int lenghtList(pEnemyList list);
  void printCharacterStats(pEnemyList list, Character character);
  void printEnemy(pEnemyList list, DrawWindow drawWindow);
  bool openRoom(pEnemyList list, int round);
  void changeRoom(Character &character, int &monsterCount, int &round, pEnemyList &list);
};
