#include "Game.h"
#include "define.h"
#include "sgg/graphics.h"
#include <map>
#include <cstdlib>

Game* Game::m_instance = nullptr;
void Game::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("tablebj.png");
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::setFont("BJfont.ttf");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	if (m_state == STATE_INIT)
	{
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.6f, "Loading assets...", br);
		m_state = STATE_PL;
		return;
	}
	if (m_state == STATE_PL)
	{
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, "Welcome to BlackJack!", br);
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.8, 0.4f, "Choose the number of Players", br);
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.6, 0.4f, "Press 1 for 1 player or 2 for 2 players ", br);
		return;
	}
	if (m_state == STATE_DEAL_PL1)
	{
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, "Now you can deal Player 1! ", br);
		graphics::drawText(CANVAS_WIDTH / 3.3, CANVAS_HEIGHT / 1.8, 0.4f, "Press 3 for 5$, 4 for 50$, 5 for 100$", br);
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.6, 0.4f, "Press X to verify your choice", br);
		auto it = m_players.find(1);
		it->second->draw();
		if (GetNumP() == 2)
		{
			it = m_players.find(2);
			it->second->draw();
		}
		return;

	}
	if (m_state == STATE_DEAL_PL2)
	{
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, "Now you can deal Player 2! ", br);
		graphics::drawText(CANVAS_WIDTH / 3.3, CANVAS_HEIGHT / 1.8, 0.4f, "Press 3 for 5$, 4 for 50$, 5 for 100$  ", br);
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.6, 0.4f, "Press M to verify your choice", br);
		auto it = m_players.find(1);
		it->second->draw();
		if (GetNumP() == 2)
		{
			it = m_players.find(2);
			it->second->draw();
		}
		return;
	}
	if (m_state == STATE_START_TURN)
	{
		auto it = m_players.find(1);
		it->second->draw();
		if (GetNumP() == 2)
		{
			it = m_players.find(2);
			it->second->draw();
		}
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, "Press E to start the game ", br);
		return;
	}
	if (m_state == STATE_TURN_PL1)
	{

		auto it = m_players.find(1);
		it->second->draw();
		it->second->drawCards();
		if (GetNumP() == 2)
		{
			it = m_players.find(2);
			it->second->draw();
			it->second->drawCards();
		}
		for (auto c : dealer)
		{
			c->setPosX(CANVAS_HEIGHT / 1.4);
			c->setPosY(CANVAS_WIDTH / 8);
			c->draw();
		}
		std::string turn_string = "Player 1 Press S to stop. Press D to draw card. Press F to Surrender.";
		graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, 0.4f, turn_string, br);
		return;

	}
	if (m_state == STATE_TURN_PL2)
	{
		auto it = m_players.find(1);
		it->second->draw();
		it->second->drawCards();
		if (GetNumP() == 2)
		{

			it = m_players.find(2);
			it->second->draw();
			it->second->drawCards();
		}
		for (auto c : dealer)
		{
			c->setPosX(CANVAS_HEIGHT / 1.4);
			c->setPosY(CANVAS_WIDTH / 8);
			c->draw();
		}

		std::string turn_string = "Player 2 Press J to stop. Press K to draw card. Press L to Surrender.";
		graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, 0.4f, turn_string, br);

		return;
	}
	
	if (m_state == STATE_DEALER)
	{
		auto it = m_players.find(1);
		it->second->draw();
		it->second->drawCards();

		if (GetNumP() == 2)
		{
			it = m_players.find(2);
			it->second->draw();
			it->second->drawCards();
		}

		int i = 0;
		for (auto c : dealer)
		{
			c->setPosX((CANVAS_HEIGHT / 1.4) + (i * 0.8f)) ;
			c->setPosY(CANVAS_WIDTH / 8);
			c->draw();
			i++;
		}
		std::string str = "Dealer's play";
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, str, br);
	}
	if (m_state == STATE_END)
	{
		auto it = m_players.find(1);
		it->second->draw();
		it->second->drawCards();

		if (it->second->get_SPC() <= 21)
		{
			if (dealer_points < it->second->get_SPC() || dealer_points>21 )
			{
				std::string str = "Player 1 you win";
				graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, str, br);

			}
			else if (dealer_points == it->second->get_SPC())
			{
				std::string str = "Player 1 Tie";
				graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, str, br);
			}
			else
			{
				std::string str = "Player 1 you lose";
				graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, str, br);
			}
		}
		else
		{
			std::string str = "Player 1 you lose";
			graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, str, br);
		}
		if (GetNumP() == 2)
		{
			auto it = m_players.find(2);
			it->second->draw();
			it->second->drawCards();
			
			if (it->second->get_SPC() <= 21)
			{
				if (dealer_points < it->second->get_SPC() || dealer_points > 21)
				{
					std::string str = "Player 2 you win";
					graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.8, 0.4f, str, br);

				}
				else if (dealer_points == it->second->get_SPC() )
				{
					std::string str = "Player 2 Tie";
					graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.8, 0.4f, str, br);
				}
				else
				{
					std::string str = "Player 2 you lose";
					graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.8, 0.4f, str, br);
				}
			}
			else
			{
				std::string str = "Player 2 you lose";
				graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.8, 0.4f, str, br);
			}
		}


		int i = 0;
		for (auto c : dealer)
		{
			c->setPosX((CANVAS_HEIGHT / 1.4) + (i * 0.8f));
			c->setPosY(CANVAS_WIDTH / 8);
			c->draw();
			i++;
		}
		std::string str = "Press Y for new round. Press N to exit.";
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 1.6, 0.4f, str, br);
		
		return;
	}
	if (m_state == STATE_EXIT)
	{
		std::string str = "THANKS FOR PLAYING!!!";
		graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, 0.4f, str, br);
		return;
	}
}

void Game::update()
{
	if (m_state == STATE_INIT)
	{
		return;
	}
	if (m_state == STATE_PL)
	{
		init();
		return;
	}
	if (m_state == STATE_DEAL_PL1)
	{
		s = 0;
		t = 0;
		auto it = m_players.find(1);
		deal(it->second);
		it->second->set_SPC(0);
		if (graphics::getKeyState(graphics::SCANCODE_X))
		{
			if (GetNumP() == 1)
			{
				m_state = STATE_START_TURN;
			}
			else if (GetNumP() == 2)
			{
				m_state = STATE_DEAL_PL2;
			}
		}
		return;
	}
	if (m_state == STATE_DEAL_PL2)
	{
		auto it = m_players.find(2);
		deal(it->second);
		it->second->set_SPC(0);
		if (graphics::getKeyState(graphics::SCANCODE_M))
		{
			m_state = STATE_START_TURN;
		}
		return;
	}

	if (m_state == STATE_START_TURN)
	{
		int r ;
		this->createCardDeck();
		do
		{
			if (s>=1) break;
			r = rand() % 52;
			if (carddeck[r] == 0)
			{
				continue;																 
			}
			Card* c = new Card(r, carddeck[r]);								//draw card for dealer
			dealer.push_front(c);
			dealer_points += carddeck[r];
			carddeck[r] = 0;
		} while (carddeck[r] != 0);

		auto it = m_players.find(1);
		do
		{
			r = rand() % 52;
			if (s >= 2) break;
			if (carddeck[r] == 0)
			{
				continue;
			}
			Card* cp = new Card(r, carddeck[r]);								//draw 2cards for P1																					
			it->second->Dcard(cp);												//cp = card player1
			carddeck[r] = 0;
		} while (carddeck[r] != 0);


		
		 if (GetNumP() == 2)
		{
			auto it = m_players.find(2);
			do
			{
				r = rand() % 52;
				if (carddeck[r] == 0)
				{
					continue;
				}
				if (s >= 2) break;
				Card* cp = new Card(r, carddeck[r]);		//cp = card player1
				it->second->Dcard(cp);
				carddeck[r] = 0;
			} while (carddeck[r] != 0);
			
		}
		 s++;

		if (graphics::getKeyState(graphics::SCANCODE_E))
		{
			m_state = STATE_TURN_PL1;
			return;
		}
	}
	//State for player1
	if (m_state == STATE_TURN_PL1)
	{
		auto it = m_players.find(1);
		if (it->second->get_SPC() > 21)
		{
			if (GetNumP() == 2)
			{
				m_state = STATE_TURN_PL2;
				return;
			}
			else
			{
				m_state = STATE_DEALER;
				return;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_S))
		{
			if (GetNumP() == 2)
			{
				m_state = STATE_TURN_PL2;
				return;
			}
			else
			{
				m_state = STATE_DEALER;
				return;
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_D))
		{
			sleep(250);
			auto it = m_players.find(1);

			int r;
			do
			{
				r = rand() % 52;
				if (carddeck[r] == 0)
				{
					continue;
				}
				Card* cp = new Card(r, carddeck[r]);		//cp = card player1
				it->second->Dcard(cp);
				carddeck[r] = 0;

			} while (carddeck[r] != 0);

			return;

		}

		if (graphics::getKeyState(graphics::SCANCODE_F))
		{
			auto it = m_players.find(1);
			it->second->SurrenderP();
			if (GetNumP() == 2)
			{
				m_state = STATE_TURN_PL2;
				return;
			}
			else
			{
				m_state = STATE_DEALER;
			}
			return;
		}

	}
	if (m_state == STATE_TURN_PL2)
	{
		auto it = m_players.find(2);
		if (it->second->get_SPC() > 21)
		{
			m_state = STATE_DEALER;
			return;
		}
		if (graphics::getKeyState(graphics::SCANCODE_J))
		{
				m_state = STATE_DEALER;
				return;
		}
		if (graphics::getKeyState(graphics::SCANCODE_K))
		{

			sleep(250);																							//PLAYER2 PLAY TURN 
			auto it = m_players.find(2); 

			int r;
			do
			{
				r = rand() % 52;
				if (carddeck[r] == 0)
				{
					continue;
				}
				Card* cp = new Card(r, carddeck[r]);		//cp = card player1
				it->second->Dcard(cp);
				carddeck[r] = 0;

			} while (carddeck[r] != 0);

			return ;

		}
		if (graphics::getKeyState(graphics::SCANCODE_L))
		{
			it->second->SurrenderP();
			m_state = STATE_DEALER;
			return;

		}

	}

	if (m_state == STATE_DEALER)
	{
		int	r;
		while (dealer_points <= 17)
		{
			do
			{
				r = rand() % 52;
				if (carddeck[r] == 0)
				{
					continue;																					//DEAL PLAY TURN
				}
				Card* c = new Card(r, carddeck[r]);
				dealer.push_front(c);
				dealer_points += carddeck[r];
				carddeck[r] = 0;
				sleep(500);
			} while (carddeck[r] != 0);
		}

		m_state = STATE_END;
		return;
		
	}
	if (m_state == STATE_END)
	{
		if (t < 1)
		{
			auto it = m_players.find(1);
			if (it->second->get_SPC() <= 21)
			{
				if (dealer_points < (it->second->get_SPC()) || dealer_points > 21)
				{
					it->second->winDealer();
				}
				else if (dealer_points == it->second->get_SPC())
				{
					it->second->eqDealer();
				}
				else
				{
					it->second->loseDealer();
				}
			}
			else
			{
				it->second->loseDealer();
			}
			if (GetNumP() == 2)
			{
				it = m_players.find(2);
				if (it->second->get_SPC() <= 21)
				{
					if (dealer_points < it->second->get_SPC() || dealer_points > 21)
					{
						it->second->winDealer();																								
					}
					else if (dealer_points == it->second->get_SPC() )
					{
						it->second->eqDealer();
					}
					else
					{
						it->second->loseDealer();
					}
				}
				else
				{
					it->second->loseDealer();
				}
				
			}
			
			t++;
		}

		//New turn or exit game
		if (graphics::getKeyState(graphics::SCANCODE_Y))
		{
			
			auto it = m_players.find(1);
			it->second->deleteCards();
			if( GetNumP()==2)
			{
				it = m_players.find(2);
				it->second->deleteCards();
			}
			for (auto c : dealer)
			{
				delete c;																		//NEW TURN OR END GAME
			}
			dealer.clear();
			dealer_points = 0;
			
			m_state = STATE_DEAL_PL1;
			return;
		}
		if (graphics::getKeyState(graphics::SCANCODE_N))
		{
			m_state = STATE_EXIT;
			return;
		}
	}

	if (m_state == STATE_EXIT)
	{
		graphics::stopMusic();
		return;
	}
	
	
}

void Game::init()
{


	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		SetNumP(1);
		Player* p1 = new Player();
		p1->setPosX(CANVAS_WIDTH * (0.5f) / 3.0f);
		p1->setPosY(CANVAS_HEIGHT / 1.4f);
		m_players.insert(std::pair<int, Player*>(1, p1));
		m_state = STATE_DEAL_PL1;

			
	}
	else if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		SetNumP(2);
		Player* p1 = new Player();
		p1->setPosX(CANVAS_WIDTH * (0.5f) / 3.0f);
		p1->setPosY(CANVAS_HEIGHT / 1.4f);
		m_players.insert(std::pair<int, Player*>(1, p1));
		Player* p2 = new Player();
		p2->setPosX(CANVAS_WIDTH * (2.3f) / 3.0f);
		p2->setPosY(CANVAS_HEIGHT / 1.4f);
		m_players.insert(std::pair<int, Player*>(2, p2));
		m_state = STATE_DEAL_PL1;
	}
		
	graphics::preloadBitmaps(ASSET_PATH);
	graphics::playMusic( std::string(ASSET_PATH) + "musicbackground.wav", 1.0f);
}


void Game::createCardDeck()
{
	int j = 1;
	int points = 1;
	for (int i = 0; i < 52; i++) {
		if (points != 10)
		{
			if (j <= 4)
			{												//create a new cardeck
				carddeck[i] = points;
				j++;
			}
			else
			{
				points++;
				carddeck[i] = points;
				j = 2;
			}
		}
		else
		{
			carddeck[i] = 10;
		}

	}
}

//Sets the amount of money the player wants to deal
void Game::deal(Player *p)
{
	int d;
	if (graphics::getKeyState(graphics::SCANCODE_3))
	{
		d = 5;
		p->setDeal(d);
		return;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_4))
	{															//deal player choices
		d = 50;
		p->setDeal(d);
		return;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_5))
	{
		d = 100;
		p->setDeal(d);
		return;
	}

}

Game* Game::getInstance()
{
	if (!m_instance)
	{
		m_instance = new Game();
	}
	return m_instance;

}

Game:: ~Game()
{
	for (int i=1;i<=2;i++)
	{
		m_players.erase(i);
	}
	for (auto c : dealer)
	{
		delete c;
	}
	dealer.clear();
	delete[] carddeck;
}