//
// Created by Roberto Jesus Garcia Pino on 17/08/25.
//

#ifndef TICTACTOE_TICTACMATH_H
#define TICTACTOE_TICTACMATH_H

#include "drawable_tic_tac_toe_board.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Match
{
public:
    Match();
    void start();

private:
    bool m_turn;
    sf::RenderWindow m_window;
    DrawableTicTacToeBoard m_board;
    Symbol m_winner;
    int m_moves;
    bool m_gameOver;
    sf::Font m_font;

    void handleMouseClick();
    // void showWinner();
    // void updateTurnText();
    void render();
    bool loadFont();
    [[nodiscard]] bool isBoardFull() const;
    void showGameOverText();
    void showTurnText();
};

#endif //TICTACTOE_TICTACMATH_H