#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

class Level;
class Character;

class Enemy : public Sprite
{
public:
	Enemy(Level *l,DrawEngine *de,int s_index,float x=1,float y = 1 ,int i_lives = 1) ;

	~Enemy();

	void addGoal(Character *g);
	bool move(float x, float y);
	void idleUpdate(void);
private:

protected:
	void simulateAI(void);
	Character *goal;

};


#endif