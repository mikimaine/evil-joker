#ifndef APPFRAME_H
#define APPFRAME_H

#include "stdwx.h"
//#include "wx\wx.h"
#include "drawEngine.h"
#include "level.h"
#include "mage.h"
#include <math.h>
enum ID_LIST
{
	ID_NEW =400,
	ID_LOAD,
	ID_ABOUT,
	ID_EXIT,

	ID_Timer

};
enum GameState
{
	STATE_NULL = 0,
	STATE_GAME_IN_PROGRESS,
	STATE_GAME_OVER,
	STATE_PLAYER_WON
};
enum LevelType
{
	RANDOM_NEW_LEVEL = 0
};

class AppFrame : public wxFrame
{
public:
	AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
	~AppFrame();

	void OnNew(wxCommandEvent &event);
	void OnLoad(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);

	void OnPaint(wxPaintEvent &event);

	void OnTimer(wxTimerEvent &event);
	void OnKey(wxKeyEvent &event);
	
private:
	bool startNewLevel(LevelType Type);
	void updateView(void);
	void updateGame(void);
private:
	wxPanel *m_panel;

	wxPanel *m_info_panel;

	wxWindow *gamewindow;

	wxStaticText *stPlayerLives;
	wxStaticText *stCurrentLevel;
	wxStaticText *stNumEnemies;

	wxTimer *m_timer;
	wxStopWatch *stopwatch;

	//Game Variables
	Level *level;
	Mage  *player;

	DrawEngine drawArea;

	wxBitmap *backBuffer;

	int currentLevel;

	GameState gameState;
private:
	DECLARE_EVENT_TABLE();


};

#endif