#include "stdwx.h"


#include "drawEngine.h"
#define GRID_SIZE 32
/*
	This is the implementation of the DrawEngine  class
	we draw stafs in this class 
	whether is a characte or a fire ball even a wall 
	we use this class to draw stafs to the console
*/

 
/*
		DrawEngine(int ,int )
		this constructor sets the screen width and Height
		and remove the cursor from the console
*/
DrawEngine::DrawEngine(int xSize, int ySize)
{
	screenWidth = xSize;
	screenHeight = ySize;

	
	map = 0;
}
/*

		~DrawEngine() 
		this distructor first remove(delete) the object created after execution
		the return back the cursore after the game is over or the user press the 'q' key

*/

DrawEngine::~DrawEngine()
{
	
}


/*
		createSprite(int ,char )
		this method see our avaliable place in our spriteImage[16] index and 
		put the character passed in to the array if it is in the approprate index and return the index
		if not it will return -1

*/
int DrawEngine::createSprite(int index, wxBitmap *sprite)
{

	if (index >= 0 && index < 16)
	{
		wxImage img = sprite->ConvertToImage();
		img.SetMaskColour(255, 255, 255);
		spriteImage[index] = new wxBitmap(img);
		return index;
	}
	return -1;
}
/*
       deleteSprite(int index)
	   this method searches the spriteImage[16] array and remove the
	   specified element


*/
void DrawEngine::deleteSprite(int index)
{
	//we dont need it 
}

/*
		drawSprite(int ,int , int)
		it will take the index of the object and the x & y postion
		it will go to the x,y postion and out put the character we have put at spriteImage[index] 
*/
void DrawEngine::drawSprite(int index, int posx, int posy)
{

	wxMemoryDC dc;
	dc.SelectObject(*winCanvas);
	dc.DrawBitmap(*spriteImage[index], wxPoint(posx * GRID_SIZE, posy *GRID_SIZE),true);
	dc.SelectObject(wxNullBitmap);

}

/*
		eraseSprite(int , int )
		goto the x and y postion and replace the character with empty ' ' character

*/
void DrawEngine::eraseSprite(int posx, int posy)
{
	wxMemoryDC dc;
	dc.SelectObject(*winCanvas);
	dc.DrawBitmap(*tileImage[0], wxPoint(posx * GRID_SIZE, posy *GRID_SIZE), true);
	dc.SelectObject(wxNullBitmap);
}
void DrawEngine::setMap(char **data)
{
	map = data;
}
void DrawEngine::createBackgroundTile(int index, wxBitmap *tile)
{
	if (index >= 0 && index < 16)
	{
		wxImage img = tile->ConvertToImage();
		img.SetMaskColour(255, 255, 255);
		tileImage[index] = new wxBitmap(img);

	}
}
void DrawEngine::drawBackground(void)
{

	wxMemoryDC dc;
	dc.SelectObject(*winCanvas);
	

	if (map)
	{
		for (int y = 0; y < screenHeight; y++)
		{
			
			for (int x = 0; x < screenWidth; x++)
			{
				
				dc.DrawBitmap(*tileImage[map[x][y]], wxPoint(x * GRID_SIZE, y *GRID_SIZE), true);

			}
		}
	}
	dc.SelectObject(wxNullBitmap);
}

void DrawEngine::setWindow(wxBitmap *in, int width , int height)
{

	winCanvas = in;
	screenWidth = width;
	screenHeight = height;
}

