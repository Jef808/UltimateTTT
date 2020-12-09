/**
 * @file  Agent that implements minimax algorithm
 */

#pragma once

#include "State.hpp"
#include "Node.hpp"
#include <climits>

/**
 * Discrete (win or lose) minimax with prunning.
 */ 
class MinMaxAgent {
public:
    /** Initialize the agent given a state */
    MinMaxAgent(const Token _token)
        : token(_token)
    {}
    /**
     * Choose an action by running algorithm on every child.
     */
    int choose_action(const State& state);

    /** Set the token of the agent */
    void set_token(const Token _token) { token = _token; };
        
private:
    /** The token the agent plays with (X or O). */
    Token token;

    /**
     * Determine the minimax score of a (Node) state and store it
     * in the node.
     * @param  root The node of the state to evaluate.
     * @param  depth The current recursion depth of the algorithm.
     * @param  max_depth The maximal depth we allow for the algorithm.
     * @return  The computed minimax score of the state.
     */
    int minimax(Node::node_ptr& node, int alpha=INT_MIN, int beta=INT_MAX, int depth=0, bool is_agents_turn=true);
};
