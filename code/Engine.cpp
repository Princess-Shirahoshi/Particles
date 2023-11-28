// Suggestions:
// Karissa do you want to organize the functions like this or match exactly to the instructions? I think this looks more sequential but lemme know what you think

#include "Engine.h"
#include <iostream> // added for cout 

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

    
    // added this in case font doesnt load for whatever reason
    if (!m_font.loadFromFile("font.ttf")) 
    {
        // Displays message to user if font doesn't load
        cout << "Error loading font!" << endl;
    }

    // creating m_text objects here 
    m_text.setFont(m_font);
    m_text.setCharacterSize(60); //Sets m_text size
    m_text.setFillColor(Color::White); //Sets m_text color
    m_text.setPosition(10, 10); //Positions m_text
    
    m_titleText.setFont(m_font);
    m_titleText.setCharacterSize(300);
    m_titleText.setFillColor(Color(244,172,200));
    m_titleText.setOutlineColor(Color::White);
    m_titleText.setOutlineThickness(3.0f);
    m_titleText.setPosition(550, 140);
    m_titleText.setString("Particles"); //Adds title screen

    m_startText.setFont(m_font);
    m_startText.setCharacterSize(60);
    m_startText.setFillColor(Color::White); 
    m_startText.setPosition(700, 600);
    m_startText.setString("   PRESS ANY KEY TO PLAY!\n\nCREATED BY KARISSA & GABE");

    // bool for titlescreen, true to display, false to dissapear
    m_titleScreen = true;
}

// input function to handle user input
void Engine::input()
{
    Event event;
	while (m_Window.pollEvent(event))
	{
        if (event.type == Event::Closed)
        {
		    // quit the game when the window is closed
			m_Window.close();
        }
			
        // exits title screen ONLY if user presses a key (NO CLICKY)
        if (event.type == Event::KeyPressed && m_titleScreen) 
        {
            m_titleScreen = false;
        }

        // If you press escape it exits the game
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
    }
}

// update function to update game state
void Engine::update(float dtAsSeconds)
{
   // if (!m_titleScreen)
  //  {
        // add code here

        // loops through particles to update them
       // auto it = m_particles.begin();
      //  while (it != m_particles.end())
       // {
       //     if (it->getTTL() > 0.0f)
       //     {
       //         it->update(dtAsSeconds);
       //         ++it;
       //     }
        //    else
        //    {
        //        it = m_particles.erase(it);
          //  }
       // } 
 //   }

    
}

// draw function to draw out the program

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
        // here add draw code for the engine

        // loops through particles and draws them out, i think we've already learned how to add range based for loops but let me know if you wanna do it another way
       // for (const auto& particle : m_particles)
      //  {
      //      m_Window.draw(particle);
      //  } 
    }
    
    m_Window.display();
}

// run function to run program loop
void Engine::run()
{
    // constructs the clock object to track time per frame
    Clock clock;

    // constructs a local particle to be used for unit tests
    //cout << "Starting Particle unit tests..." << endl;
    //Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    //p.unitTests();
    //cout << "Unit tests complete.  Starting engine..." << endl;

    // here's the game loop
    while (m_Window.isOpen())
    {
        // restarts the clock which returns the time elapsed since the last frame
        Time dt = clock.restart();

        // converts clock time into seconds
        float dtAsSeconds = dt.asSeconds();

        // calls input function
        input();

        // calls update function
        update(dtAsSeconds);

        // calls draw function
        draw();
    }
}

