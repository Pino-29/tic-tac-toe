//
// Created by Roberto Jesus Garcia Pino on 17/08/25.
//

#include "match.h"

#include "symbol.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <utility>

Match::Match() : m_turn(false),
                 m_winner(Symbol::None),
                 m_moves(0)
{
    m_window = sf::RenderWindow(sf::VideoMode({1000, 1000}),
                          "Tic Tac Toe",
                          sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
                          sf::State::Windowed);

    constexpr sf::Vector2f position{0.f, 0.f};
    constexpr sf::Vector2f origin{0.f, 0.f};
    constexpr sf::Vector2f size{900.f, 900.f};
    m_board = DrawableTicTacToeBoard(position, origin, size);
    m_window.setFramerateLimit(30);
}

void Match::start()
{
    while (m_window.isOpen() && m_winner == Symbol::None)
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                return;
            }

            if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                handleMouseClick();
            }
        }

        m_window.clear();
        m_board.draw(m_window);
        m_window.display();
    }
}

void Match::handleMouseClick()
{
    const Symbol currPlayer         { m_turn % 2 == 0 ? Symbol::X : Symbol::O };
    sf::Vector2i pixelPos           { sf::Mouse::getPosition(m_window) };
    sf::Vector2f relativePos        { m_window.mapPixelToCoords(pixelPos) };
    std::pair<int, int> cellIndexes { m_board.getCellAt(relativePos) };
    
    if (cellIndexes != std::pair(-1, -1) && m_board.isCellEmpty(cellIndexes.first, cellIndexes.second))
    {
        m_board.markCell(cellIndexes.first, cellIndexes.second, currPlayer);
        m_turn = !m_turn;
        m_moves++;
    }
}
