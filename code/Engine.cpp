// Suggestions:
// Karissa do you want to organize the functions like this or match exactly to the instructions? I think this looks more sequential but lemme know what you think
// Gabe -> I think the functions look fine, we just want to make sure it's readable for the professor // this should be okay

#include "Engine.h"
#include <iostream> // added for cout 
#include "Particle.h"
#include <iterator>
using namespace std;

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
/*Poll the Windows event queue - Dne
Handle the Escape key pressed and closed events so your program can exit - Done
Handle the left mouse button pressed event
Create a loop to construct 5 particles (I used 5, you can change this if you want)
numPoints is a random number in the range [25:50] (you can experiment with this too)
Pass the position of the mouse click into the constructor*/
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
        {
            m_Window.close();
        }

        // exits title screen ONLY if user presses a key (NO CLICKY)
        if (event.type == Event::KeyPressed && m_titleScreen)
        {
            m_titleScreen = false;
            for (int i = 0; i < 5; i++)
            {
                // constructs the particles 
                int numPoints = rand() % (50 - 25 - 1) + 25;
                Vector2i mouseCoords = Mouse::getPosition(m_Window);
                Particle particleDisplayLoc(m_Window, numPoints, mouseCoords);
                m_particles.push_back(particleDisplayLoc);
            }
        }

        // Check for mouse button press to create particles
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            int numPoints = rand() % (50 - 25 - 1) + 25;
            //Vector2i mouseCoords = Mouse::getPosition(m_Window);
            Particle particleDisplayLoc(m_Window, numPoints, Mouse::getPosition(m_Window));
            m_particles.push_back(particleDisplayLoc);
        }
    }
}

// update function to update game state
void Engine::update(float dtAsSeconds)
/*The general idea here is to loop through m_particles and call update on each Particle in the vector whose ttl (time to live) has not expired
If a particle's ttl has expired, it must be erased from the vector
This is best done with an iterator-based for-loop
Don't automatically increment the iterator for each iteration
if getTTL() > 0.0
Call update on that Particle
increment the iterator
else
erase the element the iterator points to
erase returns an iterator that points to the next element after deletion, or end if it is the end of the vector
Assign the iterator to this return value
Do not increment the iterator (if you do you might increment past the end of the vector after you delete the last element)*/
{
   if (!m_titleScreen)
   {
	   // So, his instructions say use a for loop 
	   // I googled the increment and we only need to keep a semi-colon there at end and then it will like re-eval it but won't error out 
	   for (auto i = m_particles.begin(); i != m_particles.end();)
		   {
			   if (i->getTTL() > 0.0)
			   {
				   i->update(dtAsSeconds);
				   i++;
			   }
			   else
			   {
				   i = m_particles.erase(i);
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
        for (Particle parti : m_particles)
        {
                m_Window.draw(parti);
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