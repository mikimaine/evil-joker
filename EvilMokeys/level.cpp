#include "stdwx.h"
#include "level.h"
#include "character.h"
#include "enemy.h"


#define startX 1
#define startY 1
Level::Level(DrawEngine *de, int w, int h)
{
	drawArea = de;
	width = w;
	height = h;

	player = 0;

	//create memmory for our level
	//char **  is our map 
	level = new char *[width];

	for (int i = 0; i< width; i++)
	{
		level[i] = new char[height];
	}
	//create the level 
	createLevel();
	drawArea->setMap(level);
}

Level::~Level()
{
	for (int i = 0; i < width; i++)
	{
		delete[] level[i];
	}

	delete[] level;

	for (Iter = npc.begin(); Iter != npc.end(); Iter++)
	{
		delete (*Iter);
	}
}


void Level::createLevel(void)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int random = rand() % 100;
			//int random = 0;
			if (y == 0 || y == (height-1) || x==0 || x == (width-1))
			{
				level[x][y] = TILE_WALL;
			}
			else
			{
					if (random < 90 || (x<3 && y<3))
					{
						level[x][y] = TILE_EMPTY;
					}
					else{
						level[x][y] = TILE_WALL;
					}

			}
		}


	}
}

void Level::draw(void)
{
	//we ned to draw the level
	drawArea->drawBackground();

}
void Level::addPlayer(Character *p)
{
	player = p;

}
bool Level::keyPress(char c)
{
	if (player)
	{
		if (player->keyPress(c))
		{   
			//wxMessageBox(_T("Key pressed"));
			return true;
		}
	}
	return false;
}
void Level::update(long time)
{
	// here is where we'll be able to deal with fireballs moving
	//and extra stuff that we want
	for (Iter =npc.begin();Iter != npc.end() ; Iter++)
	{
		(*Iter)->setCurrentTime(time);
		if ((*Iter)->updateSprite())
		{
			(*Iter)->idleUpdate();
		}
		(*Iter)->idleUpdate();
		if ((*Iter)->isAlive() == false)
		{
			Sprite *temp = *Iter; 
		    Iter -- ;
			delete temp;	
		
			npc.remove(temp);
			
		}
	}

}
void Level::addEnemies(int num,int speed)
{
	int i = num;
	while (i>0)
	{
		int xpos = int ((float(rand() % 100) / 100) * (width -2 ) + 1);
		int ypos = int ((float(rand() % 100) / 100) * (height - 2) + 1);
		if (level[xpos][ypos] != TILE_WALL )
		{
			Enemy *temp = new Enemy(this, drawArea, SPRITE_ENEMY, (float)xpos, float(ypos));
			temp->setSpeed(speed);
			temp->addGoal(player);
			addNPC((Sprite *)temp);
			i--;
		}
	}
}
void Level::setPlayerStart(void)
{
	player->setPostion(startX, startY);
}
void Level::addNPC(Sprite *spr)
{
	npc.push_back(spr);
}
int Level::numEnemies(void)
{
	int numE = 0;
	for (Iter = npc.begin(); Iter != npc.end(); Iter++)
	{
		if ((*Iter)->isAlive() && (*Iter)->classID == ENEMY_CLASSID)
		{
			numE += 1;
		}
	}
	return numE;
}
int Level::getHeight()
{
	return this->height;
}
int Level::getWidth()
{
	return this->width;
}