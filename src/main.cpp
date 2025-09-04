#include "drawable_cell.h"
#include "symbol.h"
#include "drawable_tic_tac_toe_board.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 1000}),
                     "Tic Tac Toe",
                            sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
                            sf::State::Windowed);
    window.setFramerateLimit(60);

    sf::Vector2f position{50.f, 50.f};
    sf::Vector2f origin{000.f, 000.f};
    sf::Vector2f size{900.f, 900.f};
    DrawableTicTacToeBoard board(position, origin, size);


    int mousePressesCount { 0 };
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // Request for closing the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f relativePos = window.mapPixelToCoords(pixelPos);
                std::cout << ++mousePressesCount << " Mouse pressed at " << relativePos.x << " " << relativePos.y << std::endl;
                if (board.contains(relativePos))
                {
                    std::cout << "Click was made inside the board" << '\n' << std::endl;
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }
}
