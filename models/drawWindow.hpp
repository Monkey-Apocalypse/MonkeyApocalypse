#include "character.hpp"
#include "coordinate.hpp"
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
  void printCommand(int *cnt);
  void printCredits();
  void credits(int direction);
  void printHowToPlay();
  void HowToPlay(int direction);
  void drawStats(int startX, int startY, int width, int heigth, long *points,
                 Character character, pEnemyList enemyList);
  int lenghtList(pEnemyList list);
  void printCharacterStats(pEnemyList list, Character character);
  void printEnemy(pEnemyList list, DrawWindow drawWindow);
  void changeRoom(Character &character, int &monsterCount, int &bonusCount, int &round,
                  pEnemyList &list, pPosition &listMountain);
  void moveEnemy(pEnemyList list, Character character, DrawWindow drawWindow,
                 long points);
  Position randomPosition(int startRange, int endRange);
  pPosition generateMountain(pPosition list);
  void printMountain(pPosition list);
  void printBonus (pPosition bonusList);

};
