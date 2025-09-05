//
// Created by Roberto Jesus Garcia Pino on 17/08/25.
//

#include "match.h"

#include "symbol.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <utility>

Match::Match() : m_turn(false),
                 m_winner(Symbol::None),
                 m_moves(0),
                 m_gameOver(false)
{
    m_window = sf::RenderWindow(sf::VideoMode({1000, 1000}),
                                "Tic Tac Toe",
                                sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
                                sf::State::Windowed);

    constexpr sf::Vector2f position{50.f, 50.f};
    constexpr sf::Vector2f origin{0.f, 0.f};
    constexpr sf::Vector2f size{900.f, 900.f};
    m_board = DrawableTicTacToeBoard(position, origin, size);
    m_window.setFramerateLimit(60);

    if (!loadFont())
    {
        exit(1);
    }
}

bool Match::loadFont()
{
    // Try different font paths based on operating system
    std::vector<std::string> fontPaths {
        "arial.ttf",                                    // Local file
        // macOS paths
        "/System/Library/Fonts/Arial.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "/Library/Fonts/Arial.ttf",
        "C:/Windows/Fonts/arial.ttf",                  // Windows
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", // Linux
        "/usr/share/fonts/TTF/arial.ttf"               // Some Linux distributions
    };
    
    for (const auto& path : fontPaths)
    {
        if (m_font.openFromFile(path))
        {
            return true;
        }
    }
    
    std::cerr << "Warning: Could not load any font. Text will not be displayed." << std::endl;
    return false;
}

[[nodiscard]] bool Match::isBoardFull() const
{
    return m_board.isFull();
}

void Match::showGameOverText()
{
    assert(m_gameOver);
    sf::Text gameOverText(m_font);
    if (m_winner == Symbol::X)
    {
        gameOverText.setString("Player X Wins!");
        gameOverText.setFillColor(sf::Color::Red);
    }
    else if (m_winner == Symbol::O)
    {
        gameOverText.setString("Player O Wins!");
        gameOverText.setFillColor(sf::Color::Green);
    }
    else if (m_winner == Symbol::None)
    {
        gameOverText.setString("It's a Tie!");
        gameOverText.setFillColor(sf::Color::Yellow);
    }

    gameOverText.setPosition(sf::Vector2f(100.f, 950.f));
    m_window.draw(gameOverText);
}

void Match::showTurnText()
{
    assert(!m_gameOver);
    std::string currentPlayer = m_turn ? "O" : "X";
    sf::Text turnText(m_font);
    turnText.setString("Player " + currentPlayer + "'s Turn");
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(sf::Vector2f(100.f, 950.f));
    m_window.draw(turnText);
}

void Match::render()
{
    m_window.clear();
    m_board.draw(m_window);
    
    // Draw text elements
    // m_window.draw(m_turnText);
    if (!m_gameOver)
    {
        showTurnText();
    }
    else
    {
        showGameOverText();
    }
    
    m_window.display();
}

void Match::start()
{
    while (m_window.isOpen() && !m_gameOver)
    {
        // Handle events
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

        render();
    }
    
    // Keep window open to show winner
    while (m_window.isOpen())
    {
        while (const std::optional event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
            }
        }

        render();
    }
}

void Match::handleMouseClick()
{
    if (m_gameOver)
    {
        return; // Don't allow moves after game is over
    }
    
    const Symbol currPlayer = m_turn ? Symbol::O : Symbol::X;
    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
    sf::Vector2f relativePos = m_window.mapPixelToCoords(pixelPos);
    std::pair<int, int> cellIndexes = m_board.getCellAt(relativePos);
    
    if (cellIndexes != std::pair(-1, -1) && m_board.isCellEmpty(cellIndexes.first, cellIndexes.second))
    {
        m_board.markCell(cellIndexes.first, cellIndexes.second, currPlayer);
        m_moves++;
        
        // Check for winner
        if (m_board.isWinningMove(cellIndexes.first, cellIndexes.second))
        {
            m_winner = currPlayer;
            m_gameOver = true;
        }
        else if (isBoardFull())
        {
            // Tie game - m_winner stays Symbol::None
            m_winner = Symbol::None;
            m_gameOver = true;
        }
        
        m_turn = !m_turn;
    }
}
