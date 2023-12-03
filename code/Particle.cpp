#include "Particle.h"


bool Particle::almostEqual(double a, double b, double eps)
{
	return fabs(a - b) < eps;
}


Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
    : m_A(2, numPoints)
{
    m_ttl = TTL;

    m_numPoints = numPoints;

    m_radiansPerSec = (float)rand() / RAND_MAX * M_PI;

    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);

    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    m_vx = (float)(rand() % 402 + 100); // per instructions range between 100 and 500 worked for prof, so we can adjust here -K

    if (rand() % 2 != 0)
    {
        m_vx *= -1; // this will randomly make m_vy a negative value
    }


    // assigns m_color1 & m_color2 with Colors (can be adjusted to whatever colors we want to display)
    m_color1 = Color::White;
    m_color2 = Color(rand() % 256, rand() % 256, rand() % 256); 

    m_A = Matrix(2, numPoints);

    // generate the numPoint vertices 
    float theta = ((float)rand() / RAND_MAX) * M_PI / 2.0;
    float dTheta = 2.0 * M_PI / (numPoints - 1);

    for (int j = 0; j < numPoints; ++j)
    {
        float r = (float)(rand() % 61 + 20); // here we have random values in a range of 20 to 80 (can be adjusted)
        float dx = r * cos(theta);
        float dy = r * sin(theta);

        // here we are assigning the Cartesian coordinate of the newly generated vertex to m_A
        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;

        // now increment theta by dTheta
        theta += dTheta;
    }
}


void Particle::draw(RenderTarget& target, RenderStates states) const
{
    // here we are constructing a VertexArray called lines
    VertexArray lines(TriangleFan, m_numPoints + 1);

    	// declaring a local Vector2f called center
    Vector2f center;

    // assigns it with mapping of m_centerCoordinate from Cartesian to pixel / monitor coordinates using mapCoordsToPixel
    center = target.mapCoordsToPixel(Vector2f(m_centerCoordinate), m_cartesianPlane);

	//Gabe ->  Deleted comments saying you initialized these? Seems like a bit of overkill in comments - Karissa
    lines[0].position = center;
    lines[0].color = m_color1;

    // loop j from 1 up to and inluding m_numPoints
    for (int j = 1; j <= m_numPoints; ++j)
    {
	// Gabe -> Shouldn't we use like a temp here maybe? Kinda like pointers and temp variables? (not pointers though) - K
	// Gabe -> This seems a bit bulky? I think it'd look more readable if it wasn't so compact (like step by step in a sense) - K
	lines[j].position = target.mapCoordsToPixel(Vector2f(m_A(0, j - 1), m_A(1, j - 1)), m_cartesianPlane);

	// assigns lines[j].color with m_Color2
	lines[j].color = m_color2;
    }
    
    // as soon as the loop is done, draw the VertexArray
    target.draw(lines);
}


void Particle::update(float dt)
{
	//Gabe ->  I'd rather define them at the top so we can refer easier than having to sift or ctrl find it -K
	float dx;
	float dy;
    m_ttl -= dt;

    rotate(dt * m_radiansPerSec);
    scale(SCALE);

    dx = m_vx * dt;
    m_vy -= G * dt;
    dy = m_vy * dt;

    translate(dx, dy); 
}


/*void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = M_PI / 4.0;
    RotationMatrix r(M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
} */
