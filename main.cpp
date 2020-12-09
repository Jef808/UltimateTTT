#include "State.hpp"
#include "MinMaxAgent.hpp"
#include "Node.hpp"
#include <algorithm>
#include <iostream>


constexpr std::array<Token, 9>  EMPTY_GRID {
    { Token::EMPTY, Token::EMPTY, Token::EMPTY,
      Token::EMPTY, Token::EMPTY, Token::EMPTY,
      Token::EMPTY, Token::EMPTY, Token::EMPTY }
};

int main()
{
    State state(EMPTY_GRID);
    MinMaxAgent agent(Token::O);

    int oppR, oppC, n_valid_actions, row, col;
    while (1) {
        
        std::cin >> oppR >> oppC; std::cin.ignore();
        
        if (oppR==-1) {
            agent.set_token(Token::X);
        } else {
            state = state.apply_action(3*oppR + oppC);
        }
                
        std::cin >> n_valid_actions; std::cin.ignore();
        for (int i=0; i<n_valid_actions; ++i) {
            std::cin >> row >> col; std::cin.ignore();
        }

        int action = agent.choose_action(state);
        state = state.apply_action(action);
        
        std::cout << (int)(action/3) << ' ' << action%3 << std::endl;
    }
}
