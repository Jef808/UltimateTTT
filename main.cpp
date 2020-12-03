#include "State.hpp"
#include "MinMaxAgent.hpp"
#include "Node.hpp"
#include <algorithm>
#include <iostream>


int main()
    
{
    // In this position, it is X's move and he wins in one turn by playing 2, 3 or 8.
    constexpr std::array<Token, 9> board1 {
      { Token::X    , Token::O,     Token::EMPTY ,
        Token::EMPTY, Token::X,     Token::O     ,
        Token::X    , Token::O,     Token::EMPTY }
    };    

    // Let's see how the agent evaluates this position from either side.
    State board(board1);
    
    MinMaxAgent agent = MinMaxAgent(Node(board));

    std::cout << agent.choose_action() << std::endl;
}
