#ifndef DRAWENGINE_H
#define DRAWENGINE_H

class DrawEngine
{
public:
	DrawEngine(int xSize =30,int ySize =20);
	~DrawEngine();


	int createSprite(int index,wxBitmap *sprite);
	void deleteSprite(int index);

	void eraseSprite(int posx, int posy);
	void drawSprite(int index, int posx, int posy);

	void createBackgroundTile(int index, wxBitmap *tile);
	void setMap(char **);
	void drawBackground(void);

	void setWindow(wxBitmap *in, int width = 30, int height = 20);


protected:
	char **map ; 
	int screenWidth, screenHeight;
	wxBitmap *spriteImage[16];
	wxBitmap *tileImage[16];

	wxBitmap *winCanvas;

};



#endif