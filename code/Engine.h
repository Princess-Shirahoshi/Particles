#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

class Engine
{
private:
	
	Font m_font;

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

	// for themes
	Texture m_winterBackgroundTexture;

	Texture m_springBackgroundTexture;

	Texture m_summerBackgroundTexture;

	Texture m_fallBackgroundTexture;
	
	Texture m_rainbowBackgroundTexture;
	Sprite m_backgroundSpriteTheme;

	// added so themes can be changed
	int m_currentTheme;
	Color m_currentThemeColor;

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};
