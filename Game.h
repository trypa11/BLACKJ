#pragma once
#include <list>
#include<map>
#include "Player.h"

class Game
{
public:
	enum game_state_t{STATE_INIT, STATE_PL, STATE_DEAL_PL1, STATE_DEAL_PL2, STATE_MGAME, STATE_START_TURN, STATE_TURN_PL1, STATE_TURN_PL2, STATE_DCARD_PL, STATE_DEALER, STATE_END,  STATE_EXIT};
protected:
	static Game * m_instance;
	int num_p ;				
	std::map < int, Player* > m_players;
	std::map<int, Player*>::iterator it;
	std::list<Card*> dealer;
	int dealer_points = 0;
	Player* p1;
	Player* p2;
	game_state_t m_state = STATE_INIT;				      													
	Game() {}
	int carddeck[52];
	int s;
	int t ;

public:

	void draw();
	void update();
	void init();
	void deal(Player *p);
	void SetNumP(int i) { num_p = i; }
	int GetNumP() { return num_p; }
	~Game();


	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Game * getInstance();
	
	//void processEvents();
	//void addEvent(Event * evt);

	void createCardDeck();
};