#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;

const double GRAVITY = (9.81);
const double TIME_INTVERAL = 0.1;

void drawScene(sf::RenderWindow &window)
{

    window.clear();

    sf::RectangleShape ground(sf::Vector2f(900.f, 30.f));
    ground.setPosition(0, 500.f);
    ground.setFillColor(sf::Color::Green);
    window.draw(ground);

    sf::RectangleShape pole(sf::Vector2f(50.f, 300.f));
    pole.setPosition(700, 200);
    pole.setFillColor(sf::Color::White);
    window.draw(pole);

    sf::RectangleShape basket_hinge(sf::Vector2f(5.0f, 30.f));
    basket_hinge.setPosition(695, 220);
    basket_hinge.setFillColor(sf::Color::Red);
    window.draw(basket_hinge);

    sf::RectangleShape basket_mouth(sf::Vector2f(75.0f, 10.0f));
    basket_mouth.setPosition(620, 230);
    basket_mouth.setFillColor(sf::Color::White);
    window.draw(basket_mouth);

    /*
     *   Net is created using the instance of VertexArray class
     *   consisting of an array of 4 vertexs which are fixed at
     *   certain points.
     */

    sf::VertexArray net(sf::LineStrip, 4);
    net[0].position = sf::Vector2f(625, 240);
    net[1].position = sf::Vector2f(640, 290);
    net[2].position = sf::Vector2f(680, 290);
    net[3].position = sf::Vector2f(695, 240);
    for (int i = 0; i <= 3; i++)
        net[i].color = sf::Color::White;
    net[2].color = sf::Color::White;
    window.draw(net);
}

int main()
{
    int xPosition, yPosition;
    double xVelocity, yVelocity;

    sf::RenderWindow window(sf::VideoMode(800, 600), "CasketBoll Scene");
    int x;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Draw the initial scene
        drawScene(window);

        // Create BasketBall Object
        sf::CircleShape boll(15);
        boll.setFillColor(sf::Color::Yellow);
        boll.setPosition(100, 470);
        window.draw(boll);

        // Prompt the user for launch velocity and angle
        int lvel, langle;
        std::cout << "Enter launch angle : ";
        std::cin >> langle;
        std::cout << std::endl;
        std::cout << "Enter launch velocity : ";
        std::cin >> lvel;
        std::cout << std::endl;

        // Calculating radian angle
        double langle_radian = (langle * M_PI) / 180.0;

        // Defining Initial position and velocity of basketboll
        xPosition = 100;
        yPosition = 470;
        xVelocity = lvel * cos(langle_radian);
        yVelocity = lvel * sin(langle_radian);

        // Animation loop
        while (yPosition <= 500)
        {
            window.clear();
            // Update positions of basketball
            xPosition += round(xVelocity * TIME_INTVERAL);
            yPosition -= round(yVelocity * TIME_INTVERAL + ((0.5 * GRAVITY) * (TIME_INTVERAL * TIME_INTVERAL)));
            yVelocity += round(GRAVITY * TIME_INTVERAL);
            std::cout << xPosition << " : " << yPosition << std::endl;

            boll.setPosition(xPosition, yPosition);
            drawScene(window);
            window.draw(boll);
            window.display();
            sf::sleep(sf::milliseconds(100));
        }

        window.display();
    }
    return 0;
}