#include "Engine.h"
#include <iostream> // added for cout 
#include "Particle.h"
using namespace std;

enum Theme 
{
    RAINBOW,
    WINTER,
    SPRING,
    SUMMER,
    FALL

};

// engine constructor
Engine::Engine() : m_Window(VideoMode(1920, 1080), "Particles!!", Style::Default)
{
    // loads in the background texture 
    if (!m_backgroundTexture.loadFromFile("background.png"))
    {
        cout << "Error loading background image!" << endl;
    }

    // now we're setting the texture for background sprite
    m_backgroundSprite.setTexture(m_backgroundTexture);

    // for the themes now
    if (!m_rainbowBackgroundTexture.loadFromFile("rainbow.jpg"))
    {
        cout << "Error loading rainbow theme image!" << endl;
    }

    if (!m_winterBackgroundTexture.loadFromFile("winter.jpg"))
    {
        cout << "Error loading winter theme image!" << endl;
    }

    if (!m_springBackgroundTexture.loadFromFile("sprin.jpg"))
    {
        cout << "Error loading spring theme image!" << endl;
    }

    if (!m_summerBackgroundTexture.loadFromFile("summer.jpg"))
    {
        cout << "Error loading summer theme image!" << endl;
    }

    if (!m_fallBackgroundTexture.loadFromFile("fall.png"))
    {
        cout << "Error loading fall theme image!" << endl;
    }
    

    m_backgroundSpriteTheme.setTexture(m_rainbowBackgroundTexture);
    // added this in case font doesnt load for whatever reason
    if (!m_font.loadFromFile("font.ttf")) 
    {
        cout << "Error loading font!" << endl;
    }

    // creating m_text objects here 
    m_text.setFont(m_font);
    m_text.setCharacterSize(60); 
    m_text.setFillColor(Color::White); 
    m_text.setPosition(10, 10); 
    m_text.setString("PRESS 'T' TO CHANGE THEME");
    
    m_titleText.setFont(m_font);
    m_titleText.setCharacterSize(300);
    m_titleText.setFillColor(Color(244,172,200));
    m_titleText.setOutlineColor(Color::White);
    m_titleText.setOutlineThickness(3.0f);
    m_titleText.setPosition(550, 140);
    m_titleText.setString("PARTICLES"); 

    m_startText.setFont(m_font);
    m_startText.setCharacterSize(60);
    m_startText.setFillColor(Color::White); 
    m_startText.setPosition(700, 600);
    m_startText.setString("   PRESS ANY KEY TO PLAY!\n\nCREATED BY KARISSA & GABE");

    // bool for titlescreen, true to display, false to disappear
    m_titleScreen = true;
}


void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }

        // exits title screen ONLY if user presses a key (NO CLICKY)
        if (event.type == Event::KeyPressed && m_titleScreen && !(event.key.code == Keyboard::T))
        {
            m_titleScreen = false;
            for (int i = 0; i < 5; i++)
            {
                int numPoints = rand() % (50 - 25 - 1) + 25;
                Vector2i mouseCoords = Mouse::getPosition(m_Window);
                Particle particleDisplayLoc(m_Window, numPoints, mouseCoords);
                m_particles.push_back(particleDisplayLoc);
            }
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            for (int i = 0; i < 5; i++)
            {
                int numPoints = rand() % (50 - 25 - 1) + 25;
                Vector2i mouseCoords = Mouse::getPosition(m_Window);
                Particle particleDisplayLoc(m_Window, numPoints, mouseCoords);
                m_particles.push_back(particleDisplayLoc);
            }
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::T && !m_titleScreen)
        {
            // This outputs to the Terminal
            cout << "Changing theme from " << m_currentTheme;

            m_currentTheme = (m_currentTheme + 1) % 5; // change 5 to add to the total number of themes

            cout << " to " << m_currentTheme << endl;

            // made a new swith statement for themed backgrounds
            switch (m_currentTheme)
            {
                case RAINBOW:
                    m_backgroundSpriteTheme.setTexture(m_rainbowBackgroundTexture);
                    cout << "rainbow! (default)" << endl;
                    break;
                case WINTER:
                    m_backgroundSpriteTheme.setTexture(m_winterBackgroundTexture);
                    cout << "winter!" << endl;
                    break;
                case SPRING:
                    m_backgroundSpriteTheme.setTexture(m_springBackgroundTexture);
                    cout << "spring!" << endl;
                    break;
                case SUMMER:
                    m_backgroundSpriteTheme.setTexture(m_summerBackgroundTexture);
                    cout << "summer!" << endl;
                    break;
                case FALL:
                    m_backgroundSpriteTheme.setTexture(m_fallBackgroundTexture);
                    cout << "fall!" << endl;
                    break;
            }

            for (int i = 0; i < 5; i++)
            {
		        // generating random integer -> so it is 50-25-1 = 24 and then + 25 for 25 to 48 range
                int numPoints = rand() % (50 - 25 - 1) + 25;
                Vector2i mouseCoords = Mouse::getPosition(m_Window);
                Particle particleDisplayLoc(m_Window, numPoints, mouseCoords);

                // switches the particle color based on the current theme
                switch (m_currentTheme)
                {
                    case RAINBOW:
                        particleDisplayLoc.setColor(Color(rand() % 256, rand() % 256, rand() % 256));
                        break;
                    case WINTER:
                        particleDisplayLoc.setColor(Color(186, 219, 255));
                        break;
                    case SPRING:
                        particleDisplayLoc.setColor(Color(243, rand() % 207, 180));
                        break;
                    case SUMMER:
                        particleDisplayLoc.setColor(Color(255, 200, 100));
                        break;
                    case FALL:
                        particleDisplayLoc.setColor(Color(152, 72, 43));
                        break;
                }

                m_particles.push_back(particleDisplayLoc);
            }
        }
    }
}


void Engine::update(float dtAsSeconds)
{
   if (!m_titleScreen)
   {
	   // So, his instructions say use a for loop 
	   // I googled the increment and we only need to keep a semi-colon there at end and then it will like re-eval it but won't error out 
	   for (auto i = m_particles.begin(); i != m_particles.end();)
		   {
			   if (i->getTTL() > 0.0) // TTL expired check
			   {
				   i->update(dtAsSeconds); // calling the update here per the instructions!
				   i++;
			   }
			   else
			   {
				   i = m_particles.erase(i); // If expired then we erase it from the vector here!
			   }
		   }

        //sets theme to new particles (this actually updates the particles)
        for (auto& particle : m_particles)
        {   
            switch (m_currentTheme)
            {
                case RAINBOW:
                    particle.setColor(Color(rand() % 256, rand() % 256, rand() % 256));
                    break;
                case WINTER:
                    particle.setColor(Color(186, 219, 255));
                    break;
                case SPRING:
                    particle.setColor(Color(243, rand() % 207, 180));
                    break;
                case SUMMER:
                    particle.setColor(Color(255, 200, 100));
                    break;
                case FALL:
                    particle.setColor(Color(152, 72, 43));
                    break;
            }
        }
   }
}

void Engine::draw()
{
    m_Window.clear();

    if (m_titleScreen)
    {
        m_Window.draw(m_backgroundSprite);
        m_Window.draw(m_titleText);
        m_Window.draw(m_startText);
    }


    else
    {
	// game screen active here!
        m_Window.draw(m_backgroundSpriteTheme);

        m_Window.draw(m_text);

        for (const Particle& particle : m_particles)
        {
		// drawing our flowers here
                m_Window.draw(particle);
        } 
    }
    m_Window.display();
}

// run function to run program loop
void Engine::run()
{
    Clock clock;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
    }
}
