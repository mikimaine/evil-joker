#include "stdwx.h"
#include "sprite.h"


/*
		This is the implementation of the Sprite  class
		we draw 2d image which have a position xy , a certaine number of lives
		sprite index and draw it to the screen
*/


/*
		Sprite(DrawEngine , int , float , float , int )
		this constructor will get a pointer to the address of the DrawEngine object the index
		the x and y postion and the lives of the Sprite
		and assine those to there aproprate variables
*/
Sprite::Sprite(Level *l,DrawEngine *de, int s_index, float x, float y, int i_lives)
{

	drawArea = de;

	pos.x = x;
	pos.y = y;

	spriteIndex = s_index;

	numLives = i_lives;

	facingDirection.x = 1;
	facingDirection.y = 0;

	classID = SPRITE_CLASSID;

	level = l ;
	delay = 80;
	lastTime = 0;
	bUpdateSprite = false;
}

/*
		~Sprite()
		is the distructor and will erase the created sprite at the postion
		Pos.x and Pos.y
*/
Sprite::~Sprite()
{
	//erase the dying sprite
	erase(pos.x, pos.y);
}

void Sprite::setPostion(int x=1, int y=1)
{
	erase(pos.x, pos.y);

	facingDirection.x = facingDirection.y * -100;
	pos.x = x;
	pos.y = y;

	draw(pos.x, pos.y);

}

/*
       getPostion(void)
	   this returns a vector struct of the current set postion
*/
vector Sprite::getPostion(void)
{
	return pos;

}

/*
       getX(void)
	   this returns the current X postion
*/
float Sprite::getX(void)
{
	return pos.x;
}
/*
       getY(void)
	   this returns the current Y postion
*/
float Sprite::getY(void)
{
	return pos.y;
}
/*
       addLives(int )
	   this method accepts an int  add that amount of live to the numLives
*/
void Sprite::addLives(int num)
{
	numLives += num;

}
/*
       getLives(void)
	   this returns the number of live the sprite have
*/
int Sprite::getLives(void)
{
	return numLives;
}
/*
       isALive(void)
	   this returns true if the character have more than 0 numLive else its dead
*/
bool Sprite::isAlive(void)
{
	return (numLives > 0);

}
/*
       move(float , float)
	   this method erase the curent character then add relative postion to  the current postion
	   and draw the character at the new postion 
*/
bool Sprite::move(float x, float y)
{
	int xpos = (int) (pos.x + x);
	int ypos = (int)(pos.y + y);
	if (isValidLevelMove(xpos, ypos))
	{



		//erase 
		erase(pos.x, pos.y);
		pos.x += x;
		pos.y += y;

		facingDirection.x = x;
		facingDirection.y = y;

		//drawSprite
		draw(pos.x, pos.y);
		return true;
	}
	return false;
}

/*
		draw(float ,float )
		this method accepts x and y postion and draw asprite using the DrawEngine instance Object
*/
void Sprite::draw(float x, float y)
{
	drawArea->drawSprite(spriteIndex, (int) x, (int)y);

}
/*
		erase(float ,float )
		this method accepts x and y postion and erase a sprite using the DrawEngine instance Object
*/
void Sprite::erase(float x, float y)
{
	drawArea->eraseSprite((int) x,(int) y);

}

/*
		isValidLevelMove(int ,int )
		chaecks if the character is making 
		a valid move means it is not a TILE_WALL that it tries to move 
	
*/
bool Sprite::isValidLevelMove(int xpos, int ypos)
{
	if (level->level[xpos][ypos] != TILE_WALL)
	{
		return true;
	}
	return false;
}

/*
		idelUpdate(void)
		This method this simply here for use by the child class
		it is no gone be implemented in the class 
*/

void Sprite::idleUpdate(void)
{

}


void Sprite::setLevel(Level *newLevel)
{
	level = newLevel;
}

void Sprite::update()
{

	draw(pos.x, pos.y);
}
int Sprite::getID(void)
{
	return classID;
}

void Sprite::setSpeed(int new_speed)
{
	delay = 200 - (new_speed / 100.0f ) * 200;
}
void Sprite::setCurrentTime(long time)
{ 
	if (time - lastTime > delay)
	{
		lastTime = time;
		bUpdateSprite = true;
	}
}

bool Sprite::updateSprite(void)
{
	bool out = bUpdateSprite;
	bUpdateSprite = false;
		return out;
}