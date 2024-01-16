#pragma once
#include <string>

class Card {
	int pos_c;
	int c_val;
protected:

	float m_color[3];
	float m_pos[2];
public:
	void update();
	void draw(std::string check = "");

	int getPosC() { return pos_c; }
	int getCVal() { return c_val; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	Card(int pos, int val);
	~Card();

};
