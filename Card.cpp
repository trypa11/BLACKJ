#include "sgg/graphics.h"
#include  "define.h"
#include "Card.h"
#include <iostream>
#include <sstream>
#include <string>

void Card::draw(std::string check)
{
	graphics::Brush br;

	if (check == "")
	{
		std::ostringstream ss;
		ss << this->getPosC() + 1;
		std::string fl_str = ss.str();

		br.texture = ASSET_PATH + std::string(fl_str + "c.png");
		br.outline_opacity = 0.0f;
		graphics::drawRect(m_pos[0], m_pos[1], CARD_SIZE, CARD_SIZE, br);
	}
	else
	{
		br.texture = ASSET_PATH + std::string("0c.png");
		br.outline_opacity = 0.0f;
		graphics::drawRect(m_pos[0], m_pos[1], CARD_SIZE, CARD_SIZE, br);
	}

}

void Card::update()
{

}

Card::Card(int pos, int val)
{
	c_val = val;
	pos_c = pos;
}

Card::~Card()
{

}