/**
 * @file State.hpp  Interface for regular 3x3 Tic-Tac-Toe.
*/

#pragma once

#include <array>
#include <vector>
#include <ostream>
#include <memory>
#include <list>


/** The possible values for a Cell in a Tic-Tac-Toe grid. */
enum class Token {
    EMPTY = 0,
    X,
    O
};

inline std::ostream& operator<<(std::ostream& _out, Token t);


/**
 * @class Implements the 3x3 grid of a Tic-Tac-Toe board.
 * 
 * @details Objects are only modifiable through the State::apply_action method.
 */
class State {
public:
    using grid_t = std::array<Token, 9>;
    using line_t = std::array<int, 3>;

    /** Default constructor initializes cells to the EMPTY token */
    State()
        : grid{Token::EMPTY}
    {}

    /** Initialize a State from a given 3x3 grid */
    explicit State(grid_t _grid)
        : grid(_grid)
    {}

    State(const State&) = default;
    State(State&&)      = default;
    ~State()            = default;

    State& operator = (const State&) = default;
    State& operator=(State&&) = default;

private:
    /** The grid holding the cells of the game */
    grid_t grid;

public:
    
    /**
     * Checks if the game is won according to ::WIN_COMBIN.
     * @return Token::X (resp Token::O) if X wins (resp if O wins)
     *     or Token::EMPTY if there is no winner.
     */
    Token get_winner() const;

    /** Check if game is a draw. */
    bool is_draw() const;

    /** Check if the current game is over */
    bool is_terminal() const;
    
    /**
     * Generate all possible moves from this position.
     * @return vector containing indices of each empty cell.
     */
    std::vector<int> get_valid_actions() const;

    /**
     * Play a move on the board.
     * @param  ndx  The index (from 0 to 8) of the chosen cell.
     * @param  t  The token (Token::X or Token::O) of the player
     *     making the move.
     * @return  A copy of the state with the move played.
    */
    State apply_action(int ndx) const;

    /** Check who is the player to play next. */
    Token get_next_player() const;
    
    Token operator[](int ndx) const;
    Token& operator[](int ndx); 
};


inline Token State::operator[](int ndx) const { return grid[ndx]; }
inline Token& State::operator[](int ndx) { return grid[ndx]; }

/** Renders the board for help while debugging. */
inline std::ostream& operator<<(std::ostream& _out, const State& board)
{
    for (int i=0; i<3; ++i) {
        _out << "| ";
        for (int j=0; j<3; ++j) {
            _out << board[i * 3 + j] << ' ';
        }
        _out << " |\n";
    }
    return _out;
}

/** More debugging features. */
inline std::ostream& operator<<(std::ostream& _out, Token t)
{
    switch (t) {
    case Token::EMPTY:
        return _out << ' ';
    case Token::X:
        return _out << "X";
    case Token::O:
        return _out << "O";
    }
}
