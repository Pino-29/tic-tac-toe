#include "drawable_cell.h"
#include "symbols.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
                     "Tic Tac Toe",
                            sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
                            sf::State::Windowed);
    window.setFramerateLimit(60);

    sf::Vector2f position{100.f, 100.f};
    sf::Vector2f origin{0.f, 0.f};
    sf::Vector2f size{100.f, 100.f};
    DrawableCell cell(position,
                      origin,
                      size,
                      Symbol::O);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // Request for closing the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        cell.draw(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cell.setSymbol(Symbol::X);
    }
}
