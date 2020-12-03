/**
 * @file  Agent that implements minimax algorithm
 */

#pragma once

#include "State.hpp"
#include "Node.hpp"
#include <climits>
#include <memory>
#include <vector>

class MinMaxAgent {
public:
    /** Initialize the agent given a state */
    MinMaxAgent(const Node&);

    /**
     * Choose an action accordin to the minimax algorithm.
     */
    int choose_action();
    
private:
    /** The token the agent plays with (X or O). */
    const Token token;

    /** Tree datastructure to run the agent's algorithm. */
    std::shared_ptr<Node> root;
    
    /**
     * Determine the minimax score of a (Node) state and store it
     * in the node.
     * @param  root The node of the state to evaluate.
     * @param  depth The current recursion depth of the algorithm.
     * @param  max_depth The maximal depth we allow for the algorithm.
     * @return  The computed minimax score of the state.
     */
    int set_value(std::shared_ptr<Node> node, int depth=0, int max_depth=INT_MAX, bool maximizing_player=true) const;
    
    /**
     * Populate the node's children vector using all possible actions.
     */
    std::vector<std::shared_ptr<Node>>& add_all_children(std::shared_ptr<Node>& node) const;
};

