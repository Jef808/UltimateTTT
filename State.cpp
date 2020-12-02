/**
 * @file State.cpp  Source file for the 3x3 Tic-Tac-toe board.
 */

#include "State.hpp"
#include <algorithm>
#include <iterator>
#include <array>


/** The lines giving a win when filled up. */
constexpr std::array<std::array<int, 3>, 8> WIN_COMBIN {
    {   { 0, 1, 2 },
        { 3, 4, 5 },
        { 6, 7, 8 },
        { 0, 3, 6 },
        { 1, 4, 7 },
        { 2, 5, 8 },
        { 0, 4, 8 },
        { 2, 4, 6 } }
};

/** An empty 3x3 board. */
constexpr std::array<Token, 9>  EMPTY_GRID {
    { Token::EMPTY, Token::EMPTY, Token::EMPTY,
      Token::EMPTY, Token::EMPTY, Token::EMPTY,
      Token::EMPTY, Token::EMPTY, Token::EMPTY }
};

/** State is terminal if it's drawn or there's a winner */
bool State::is_terminal() const
{
    return is_draw() || get_winner() != Token::EMPTY;
}


/**
 * Utility function to check value of a line in the State::grid.
 * 
 * @param line The indices of the desired cells in the object's #grid.
 * @param valplue What to compare the cells against.
 * 
 * @return `true` if all cells of the line in the object's #grid
 * are equal to \p value, `false` otherwise.
 */
bool compare(const State& state, const State::line_t& line, Token value)
{
    for (int n : line) {
        if (state[n] != value) {
            return false;
        }
    }
    return true;
}

std::vector<int> State::get_valid_actions() const
{
    std::vector<int> ret;

    for (int i = 0; i < 9; ++i) {
        if (grid[i] == Token::EMPTY) {
            ret.push_back(i);
        }
    }
    return ret;
}

/**
 * @details
 *     Determine if it is X (resp O)'s turn to play by checking
 *     if the number of empty cells remaining is odd (resp even).
 */ 
Token State::get_next_player() const
{
    int n_turns_left  = std::count_if(grid.begin(), grid.end(),
        [](const Token t) {
            return t == Token::EMPTY;
        });
    return (n_turns_left & 1 ? Token::X : Token::O);
}

/**
 * @details  For efficiency purposes, there are no checks done
 *     when applying an action. The token is computed with the
 *     #get_next_player member function.
 */
State State::apply_action(int ndx) const {
    std::array<Token, 9> grid_r = grid;
    grid_r[ndx] = get_next_player();

    return State(grid_r);
}

/** Checks if game is drawn */
bool State::is_draw() const
{
    bool full = (std::none_of(grid.begin(), grid.end(),
        [](Token t) {
            return t == Token::EMPTY;
        }));
    return full && get_winner()==Token::EMPTY;
}

/**
 * @details  Check all lines of the object's #grid according
 *     to #WIN_COMBIN.
 */
Token State::get_winner() const
{
    for (line_t line : WIN_COMBIN) {
        if (compare(*this, line, Token::X)) {
            return Token::X;
        }
        if (compare(*this, line, Token::O)) {
            return Token::O;
        }
    }
    return Token::EMPTY;
}
