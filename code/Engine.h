#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

class Engine
{
private:
	// font for engine.cpp
	Font m_font;

	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	// adding this in so text can be accessed throughout all functions
	Text m_text;
	Text m_titleText;
	Text m_startText;

	// added title screen bool flag
	bool m_titleScreen;

	// added background texture / sprite for displaying background image (sprite)
	Texture m_backgroundTexture;
	Sprite m_backgroundSprite;

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};