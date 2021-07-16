#include "drawWindow.hpp"
#include "engineGame.hpp"
#include <ncurses.h>
#include <cmath>
#include <ctime>
#include <iostream>

EngineGame::EngineGame(int frameGameX, int frameGameY, int height, int width) {
  this->frameGameX = frameGameX;
  this->frameGameY = frameGameY;
  this->height = height;
  this->widht = width;
  this->shoots = NULL;
  this->quit = false;
  this->pause = true;
  this->isShoot = false;
  this->whileCount = 0;
}

void EngineGame::baseCommand() {
  initscr();
  cbreak();
  curs_set(0);
  nodelay(stdscr, TRUE);
  keypad(stdscr, true);
  curs_set(FALSE);
  noecho();
  use_default_colors();
  start_color();
}
Pbullet EngineGame::createBullet(int x, int y, int direction) {
  Pbullet bullet = new Bullet;
  bullet->x = x;
  bullet->y = y;
  bullet->speed = 1;
  bullet->direction = direction;
  bullet->next = this->shoots;
  return bullet;
}
void EngineGame::shootBullet() {
  Pbullet bullet = this->shoots;
  while (bullet != NULL) {
      bullet->x += bullet->speed;
      move(bullet->y, bullet->x);
      printw("-");
      bullet = bullet->next;
  }
}
Pbullet EngineGame::destroyBullet() {
  if (this->shoots != NULL) {
    if (this->shoots->next != NULL) {
      Pbullet bullet = this->shoots, prec = this->shoots;
      while (bullet != NULL) {
        if (!isEmpty(bullet->x + 1, bullet->y)) {
          prec->next = NULL;
          delete (bullet);
          bullet = NULL;
          return (this->shoots);
        }
        prec = bullet;
        bullet = bullet->next;
      }
    } else {
      if (!isEmpty(this->shoots->x + 1,this->shoots->y)) {
        delete (this->shoots);
        this->shoots = NULL;
        return NULL;
      }
    }
  }
  return this->shoots;
}

pEnemyList EngineGame::destroyEnemy(pEnemyList list, Enemy enemy){
  pEnemyList head = list, prev = list, tmp;
	while (list != NULL) {
		if (list->enemy.getLife() == enemy.getLife()) {
			if (list == head) {
				tmp = head ;
				head = list->next;
				delete tmp ;
				prev = head;
				list = head ;
			} else {
				tmp = prev->next ;
				prev->next = list->next;
				delete tmp ;
				list = prev->next ;
			}
		} else {
			prev = list;
			list = list->next;
		}
 }
  return head;
}


void EngineGame::checkEnemyCollision(pEnemyList enemys){
  bool isCollision = false;
  Pbullet head = this->shoots;
  while(enemys != NULL && isCollision == false){
    while(this->shoots != NULL && isCollision == false){
      if(enemys->enemy.getX() == this->shoots->x+1 && enemys->enemy.getY() == this->shoots->y){
        isCollision = true;
      }
      this->shoots = this->shoots->next;
    }
    this->shoots = head;
    if(isCollision) break;
    enemys = enemys->next;
  }
  if(isCollision){
    enemys->enemy.decreaseLife(10);
    if(enemys->enemy.getLife() <= 0) enemys = destroyEnemy(enemys, enemys->enemy);
  }
}

// controllo che la posizione x y sia uno spazio vuoto
bool EngineGame::isEmpty(int x, int y) { return mvinch(y, x) == ' '; }

void EngineGame::moveCharacter(Character &character, int direction) {
  int getLastMove;
  switch (direction) {  // CONTROLLO IL TASTO SPINTO
    case KEY_UP:
      if (isEmpty(character.getX(), character.getY() - 1) == true)
        character.directionUp();
        getLastMove = KEY_UP;
      break;
    case KEY_DOWN:
      if (isEmpty(character.getX(), character.getY() + 1) == true)
        character.directionDown();
        getLastMove = KEY_DOWN;
      break;
    case KEY_LEFT:
      if (isEmpty(character.getX() - 1, character.getY()) == true)
        character.directionLeft();
        getLastMove = KEY_LEFT;
      break;
    case KEY_RIGHT:
      if (isEmpty(character.getX() + 1, character.getY() ) == true)
        character.directionRight();
        getLastMove = KEY_RIGHT;
      break;  // ESCE DALLO SWITCH
    case 'e':
      shootCommand(character, getLastMove);
      break;
  }
}

void EngineGame::shootCommand(Character &character, int direction){
  if (whileCount / 2 > 1) {
    this->shoots = createBullet(character.getX(), character.getY(),direction);
    whileCount = 0;
  }
}


void EngineGame::choiceGame(DrawWindow drawWindow, int *direction,
                            int *selection) {
  int cnt = 0;
  while (*direction != 32) {
    drawWindow.drawMenu();
    drawWindow.printCommand(&cnt);
    *direction = getch();
    if (*direction == 32) *selection = cnt;
    if (*direction == KEY_UP) cnt--;
    if (*direction == KEY_DOWN) cnt++;
    if (cnt > 3) cnt = 0;
    if (cnt < 0) cnt = 3;
  }
  clear();
}

pEnemyList EngineGame::generateEnemy(int *count, int x, int y, char character, int damage, int life, pEnemyList list) {
  while(*count > 0){
    pEnemyList head = new EnemyList;
    Enemy enemy(x,y,character,damage,life);
    head->enemy = enemy;
    head->next = list;
    *count-=1;
    return head;
  }
  return list;
}

void EngineGame::printEnemy(pEnemyList list, DrawWindow drawWindow){
  pEnemyList tmp = list;
  while(list != NULL){
    drawWindow.printCharacter(list->enemy.getX(),list->enemy.getY(),list->enemy.getCharacter());
    list = list->next;
  }
  list = tmp;
}

void EngineGame::engine(Character character, DrawWindow drawWindow) {
  int direction, selection;
  baseCommand();
  choiceGame(drawWindow, &direction, &selection);
  while (pause) {
    switch (selection) {
      case 0:
        pause = false;
        runGame(character, drawWindow, direction);
        selection = 4;
        break;
      case 1:
        drawWindow.HowToPlay(direction);
        selection = 4;
        break;
      case 2:
        drawWindow.credits(direction);
        selection = 4;
        break;
      case 3:
        refresh();
        std::cout << "Thanks for playing ;) ";
        exit(1);
        break;
      case 4:
        clear();
        engine(character, drawWindow);
        break;
    }
  }
  endwin();
}

Position EngineGame::randomPosition(int startRange, int endRange){
  Position pos;
  pos.x = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
  pos.y = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
  while(!isEmpty(pos.x,pos.y)){
    pos.x = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
    pos.y = startRange + ( std::rand() % ( endRange - startRange + 1 ) );
  }
  return pos;
}

void EngineGame::runGame(Character character, DrawWindow drawWindow,int direction) {
  long points = 0;
  int monsterCount = 1;
  pEnemyList enemyList = new EnemyList;
  while (!pause) {
    direction = getch();
    moveCharacter(character, direction);
    clear();
    drawWindow.printCharacter(character.getX(), character.getY(), character.getCharacter());
    drawWindow.drawRect(this->frameGameX, this->frameGameY, this->widht,this->height);
    drawWindow.drawStats(this->frameGameX, this->frameGameY, this->widht,this->height, &points);
    enemyList = generateEnemy(&monsterCount,randomPosition(23,70).x,randomPosition(8,19).y,'A',10,40,enemyList);
    printEnemy(enemyList,drawWindow);  // x = 23 | y = 8 HL | end | x = 70 | y = 19 | RD
    shootBullet();
    checkEnemyCollision(enemyList);
    mvprintw(23, 22, "%d",enemyList->enemy.getLife());
    refresh();
    this->whileCount += 1;
    points +=1;
    this->shoots = destroyBullet();
    timeout(50);
    if (direction == 27) pause = true;
  }
}
