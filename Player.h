#pragma once
#include "GameObj.h"
#include <list>
#include "Card.h"
#include "GameObj.h"
class Player : public GameObj
{
	float m_pos[2];
	float m_color[3];
	std::list<Card*> p_card;
	int sum_points_cards = 0;

	float cash;
	int deal;
public:
	void draw() override;
	void update()override;

	Player();
	~Player();

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	void setDeal(int d);
	float getDeal() { return deal; }
	float getCash() { return cash; }
	void set_SPC(int i) {sum_points_cards = i; }
	int get_SPC() { return sum_points_cards; }
	void Dcard(Card* c);
	void dealP();
	//void setHighlight(bool h){ m_highlight = h; }
	//void setActive(bool a) { m_acive = a; }

	void winDealer();
	void eqDealer();
	void loseDealer();
	void SurrenderP();
	void drawCards();
	void deleteCards();

};