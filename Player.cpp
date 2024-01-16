#include "Player.h"
#include "sgg/graphics.h"
#include  "define.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

void Player::draw() 
{
	graphics::Brush br;

	std::stringstream sstream1;
	sstream1 << this->getCash();
	std::string player_cash = sstream1.str() + "$";

	std::stringstream sstream2;
	sstream2 << this->getDeal();
	std::string player_deal = sstream2.str() + "$";


	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.texture = ASSET_PATH + std::string("m.png");
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
	graphics::setFont("BJfont.ttf");
	graphics::drawText(m_pos[0] + 0.2f, m_pos[1] - 0.4f, 0.5f, player_cash, br);
	graphics::drawText(m_pos[0] + 0.9f, m_pos[1] - 0.1f, 0.5f, player_deal, br);

}

void Player::update()
{
}

Player::Player()
{
	SETCOLOR(m_color, RAND0TO1(), RAND0TO1(), RAND0TO1());
	float mx = m_color[0];
	if (mx < m_color[1]) mx = m_color[1];
	if (m_color[2] > mx) mx = m_color[2];
	m_color[0] /= mx;
	m_color[1] /= mx;
	m_color[2] /= mx;
	this->deal = 0;
	this->cash = 1000;
}

Player::~Player()
{
	for (auto c : p_card)
	{
		delete c;
	}
	p_card.clear();
}



void Player::setDeal(int d)
{
	this->deal = d;
}


void Player::Dcard(Card* c)
{
	sum_points_cards += c->getCVal();
	p_card.push_front(c);
}

void Player::dealP()
{
	if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		this->setDeal(5);
		return;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		this->setDeal(50);
		return;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_3))
	{
		this->setDeal(100);
		return;
	}
}

void Player::winDealer()
{
	cash += deal;
	deal = 0;
	return;
}

void Player::loseDealer()
{
	cash = cash - deal;
	deal = 0;
	return;
}

void Player::eqDealer()
{
	deal = 0;
	return ;
}

void Player::SurrenderP()
{
	deal = deal / 2;
	cash -= deal;
	deal = 0;
	return;
}

void Player::drawCards()
{
	int i = 1;
	for (Card* c : p_card)
	{
		float x = m_pos[0] + (i * 0.8f)-1.0f;
		float y = m_pos[1] + 1.0f;
		c->setPosX(x);
		c->setPosY(y);
		c->draw();

		i++;
	}
}

void Player::deleteCards()
{
	for (auto c : p_card)
	{
		delete c;
	}
	p_card.clear();
	return;
}
