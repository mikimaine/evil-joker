#include "stdwx.h"

#include "AppFrame.h"
#include "wx\stopwatch.h"
#define GRID_SIZE	32
#define LEVEL_X		20
#define LEVEL_Y		10

#define UPDATE_TIMER  100

BEGIN_EVENT_TABLE(AppFrame, wxFrame)
		EVT_MENU		(ID_NEW, AppFrame::OnNew)
		EVT_MENU		(ID_LOAD, AppFrame::OnLoad)
		EVT_MENU		(ID_ABOUT, AppFrame::OnAbout)
		EVT_MENU		(ID_EXIT, AppFrame::OnExit)

		EVT_TIMER		(ID_Timer,AppFrame::OnTimer)
END_EVENT_TABLE()

AppFrame::AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	player = NULL;
	 

	level = NULL;
	backBuffer = NULL;
	wxMenuBar *menu_Bar = new wxMenuBar;
	
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_NEW, "&New");
	menuFile->AppendSeparator();
	menuFile->Append(ID_LOAD, "&Load");
	menuFile->AppendSeparator();
	menuFile->Append(ID_ABOUT, "&About");
	menuFile->AppendSeparator();
	menuFile->Append(ID_EXIT, "E&xit");

	menu_Bar->Append(menuFile, "&File");
	SetMenuBar(menu_Bar);


	m_panel = new wxPanel(this, -1);
	m_info_panel = new wxPanel(m_panel,-1,wxDefaultPosition,wxSize(200,400),wxBORDER_STATIC);

	gamewindow = new wxWindow(m_panel, -1, wxDefaultPosition, wxSize(200, 400), wxBORDER_STATIC);

	gamewindow->Connect(-1, -1, wxEVT_PAINT, (wxObjectEventFunction) &AppFrame::OnPaint, NULL, this);
	
	gamewindow->Connect(-1, -1, wxEVT_KEY_DOWN, (wxObjectEventFunction) &AppFrame::OnKey, NULL, this);
	stPlayerLives = new wxStaticText(m_info_panel, -1, _T("Lives : "), wxDefaultPosition, wxSize(100, 15), wxST_NO_AUTORESIZE);

	stCurrentLevel = new wxStaticText(m_info_panel, -1, _T("Level : "), wxDefaultPosition, wxSize(100, 15), wxST_NO_AUTORESIZE);
	stNumEnemies = new wxStaticText(m_info_panel, -1, _T("Enemies : "), wxDefaultPosition, wxSize(100, 15), wxST_NO_AUTORESIZE);

	wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(gamewindow, 1, wxGROW | wxALL , 5);
	mainSizer->Add(m_info_panel, 0, wxGROW | wxALL | wxSTRETCH_NOT, 5);

	wxBoxSizer *subsizer = new wxBoxSizer(wxVERTICAL);
	subsizer->Add(stPlayerLives, 0, wxLEFT | wxTOP, 5);
	subsizer->Add(stCurrentLevel, 0, wxLEFT | wxTOP, 5);
	subsizer->Add(stNumEnemies, 0, wxLEFT | wxTOP, 5);

	m_panel->SetAutoLayout(TRUE);
	m_panel->SetSizer(mainSizer);


	m_info_panel->SetAutoLayout(TRUE);
	m_info_panel->SetSizer(subsizer);


	
	drawArea.createBackgroundTile(TILE_EMPTY, &wxBITMAP(EMPTYTILE));
	drawArea.createBackgroundTile(TILE_WALL, &wxBITMAP(WALLTILE));

	drawArea.createSprite(SPRITE_PLAYER, &wxBITMAP(PLAYERTILE));
	drawArea.createSprite(SPRITE_ENEMY, &wxBITMAP(ENEMYTILE));
	drawArea.createSprite(SPRITE_FIREBALL, &wxBITMAP(FIREBALLTILE));


	m_timer = new wxTimer(this, ID_Timer);
	m_timer->Start(UPDATE_TIMER);


	srand((int) wxGetLocalTime());
    stopwatch = new wxStopWatch();
    stopwatch->Start();

	gameState = STATE_NULL;
}
AppFrame::~AppFrame()
{
	gameState = STATE_NULL;

	m_timer->Stop(); 

	delete m_timer;

	if (player)
	{
		delete player;
	}
	if (level)
		delete level;
	{

	}
}
void AppFrame::OnNew(wxCommandEvent &event)
{
	m_timer->Stop();
	if (player)
	{
		delete player;
	}
	player = new Mage(level, &drawArea, 0); 
	startNewLevel(RANDOM_NEW_LEVEL);
	level->addEnemies(3,5);
	currentLevel = 1;

	gameState = STATE_GAME_IN_PROGRESS;

	m_timer->Start(UPDATE_TIMER);
	
}
void AppFrame::OnLoad(wxCommandEvent &event)
{

}
void AppFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox(_T("The EvilMokeys is Developed by Miki Maine"),_T("About Evil Mokeys"));
}
void AppFrame::OnExit(wxCommandEvent &event)
{
	Close(TRUE);
}


void AppFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(gamewindow);
	dc.SetBackground(*wxBLACK_BRUSH);
	dc.Clear();
	updateView();
	
}

void AppFrame::OnTimer(wxTimerEvent &event)
{
	if (gameState == STATE_GAME_IN_PROGRESS)
	{
		
		updateGame();
	}
}
void AppFrame::OnKey(wxKeyEvent &event)
{
	
	if (gameState == STATE_GAME_IN_PROGRESS)
	{
		level->keyPress(event.GetKeyCode() | 32);
	}
	
	updateView();
	
	

}

bool AppFrame::startNewLevel(LevelType type)
{
	if (level)
		delete level;

	if (backBuffer)
	{
		delete backBuffer;
	}

	switch (type)
	{
			case RANDOM_NEW_LEVEL:
			{
				level = new Level(&drawArea,LEVEL_X,LEVEL_Y);
			}

	}

	backBuffer =	new wxBitmap(level->getWidth() * GRID_SIZE, level->getHeight() * GRID_SIZE);
					drawArea.setWindow(backBuffer, level->getWidth(), level->getHeight());
		
		   
			level	->addPlayer(player);
			level	->draw();
			player->setLevel(level);
			player->update();

			return	true;
	
}

void AppFrame::updateGame(void)
{
	wxString info_Lives		 = "Lives : " + wxString::Format("%d", player->getLives());
	wxString info_Level		 = "Level : " + wxString::Format("%d", currentLevel);
	wxString info_NumEnemies = "Enemies : " + wxString::Format("%d", level->numEnemies());

	stPlayerLives->SetLabel(info_Lives);
	stCurrentLevel->SetLabel(info_Level);
	stNumEnemies->SetLabel(info_NumEnemies);

	if (level->numEnemies() == 0)
	{
		m_timer->Stop();
		currentLevel++;
		startNewLevel(RANDOM_NEW_LEVEL);
		int numEnemies = (currentLevel * 3);
		if (numEnemies > 15)
		{
			numEnemies = 15;
		}
		int newSpeed = pow(2, currentLevel);
		if (newSpeed > 100)
		{
			newSpeed = 100;
		}
		level->addEnemies(numEnemies,newSpeed);
		level->setPlayerStart();
		m_timer->Start(UPDATE_TIMER);

	}
	else if (level->numEnemies() > 0 && !player->isAlive())
	{
		gameState = STATE_GAME_OVER;
		m_timer->Stop();
	}
	else
	{
		level->update(wxGetLocalTime());
	}
	updateView();
}
void AppFrame::updateView(void)
{

	wxClientDC area(gamewindow);
	if (backBuffer && gameState==STATE_GAME_IN_PROGRESS)
	{
		area.DrawBitmap(*backBuffer, wxPoint(0, 0));
	}
	

}
