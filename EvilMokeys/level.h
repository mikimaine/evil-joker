#ifndef LEVEL_H
#define LEVEL_H

#include "drawEngine.h"
#include <list>

using std::list;
#include <stdlib.h>

enum 
{
	SPRITE_PLAYER,
	SPRITE_ENEMY,
	SPRITE_FIREBALL
};
enum 
{
	TILE_EMPTY,
	TILE_WALL
};
class Sprite;
class Character;
class Level
{
public:
	Level(DrawEngine *de,int width =30 , int height = 20);
	~Level();
	
	void addPlayer(Character *p);
	void update(long time);
	void draw(void);
	bool keyPress(char c);
	
	void addEnemies(int num,int speed= 5);
	void addNPC(Sprite *spr);
	void setPlayerStart(void);
	int  numEnemies(void);
	int  getHeight(void);
	int  getWidth(void);
	friend class Sprite;

private:
	int width;
	int height;
	char **level;
	
	 
	Character *player;
	DrawEngine *drawArea;

protected:
	void createLevel(void);

public :
	list <Sprite *> npc;
	list <Sprite *>::iterator Iter;

};



#endif