#include "stdwx.h"
#include"character.h"
/*
		This is the implementation of the Character  class and extendes the Sprite Class
		this is a sprite that is contrlled by the player
*/

/*
		Character(DrawEngine , int , float , float , int , char up_key , char down_key , char left_key , char right_key ) : Sprite(de,s_index,x,y,i_lives)
		this constructor accepts the address of the Drawengine object ,index,x,y and live and pass that
		straight to the super class Sprite and also accepts the up,down,left and right key and assign 
		them to there aproprate variables 

*/
Character::Character(Level *l,DrawEngine *de, int s_index, float x , float y , int i_lives ,
	char up_key , char down_key , char left_key , char right_key )
	: Sprite(l,de,s_index,x,y,i_lives)
{
	upKey = up_key;
	downKey = down_key;
	leftKey = left_key;
	rightKey = right_key;

	classID = CHARACTER_CLASSID;

}

/*
		keyPress(char )
		this method will accept the key pressed by the player 
		and dessieds what key was pressed and return the key pressed

*/
bool Character::keyPress(char c)
{
	if (c == upKey)
	{
		return move(0, -1);
	}
	else if (c == downKey)
	{
		return move(0, 1);
	}
	else if (c == leftKey)
	{
		return move(-1, 0);
	}
	else if (c == rightKey)
	{
		return move(1, 0);
	}

	return false;
}
void Character::addLives(int num)
{
	Sprite::addLives(num);
	if (Sprite::isAlive())
	{
		pos.x = 1;
		pos.y = 1;
		move(0, 0);
	}
}