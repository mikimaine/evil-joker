#ifndef FIREBALL_H
#define FIREBALL_H

#include "sprite.h"

class Fireball : public Sprite
{
public:
	Fireball(Level *lev,DrawEngine *de,int s_index,float x=1,float y= 1,float xDir = 0,float yDir= 0,int i_lives = 1) ;


	void idleUpdate(void);
private:

};




#endif