#pragma once

#include "State.hpp"
#include <vector>
#include <utility>

const int N = 9;

/** Nothing much to do with the action class for this project really */

struct Action {

    int index;

    std::pair<int, int> get_2drep()
    {
        return {index % 3, index/3 };
    
    }

    operator int() const { return index; }
    
    void apply_action(State& state, const Action action) const
    {
        ( state.get_next_player()==Token::X ? state[action] = Token::X : state[action] = Token::O );
    }

       
};
