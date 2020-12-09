#include "MinMaxAgent.hpp"
#include "Node.hpp"
#include <algorithm>
#include <functional>
#include <memory>


int MinMaxAgent::choose_action(const State& state)
{
    Node::node_ptr root = std::make_shared<Node>(state);

    if (root->get_valid_actions().size() == 9) {
        return 0;
    }

    minimax(root);

    auto it = std::max_element(root->get_children().begin(), root->get_children().end());

    return (*it)->get_parent_action();
}

/**
 * Compute the value of a state from the agent's viewpoint when state
 * is terminal.
 *
 * @param state  The state in question.
 * @param agent_token  The token the agent is playing with (X or O).
 *
 * @details +10 if winning for agent, -10 if losing for agent, 0 if
 *     game is a draw. Those value are pretty much first-fit material
 *     so there might be room to rethink them.
 */
int get_value_terminal(const Node::node_ptr& node, Token token)
{
    Token winner = node->get_state()->get_winner();

    if (!winner) {
        return 0;
    }
    return (token == winner ? 10 : -10);
}

/** Give a score from -10 to 10 to a node by running the minimax algorithm */
int MinMaxAgent::minimax(Node::node_ptr& node, int alpha, int beta, int depth, bool is_agents_turn)
{
    // Base case if node is terminal
    if (node->get_state()->is_terminal()) {
        return get_value_terminal(node, token);
    }

    if (is_agents_turn) {
        int value = INT_MIN;

        for (auto& action : node->get_valid_actions()) {

            value = std::max(value, minimax(node->add_child(action), alpha, beta, depth+1, false));
            alpha = std::max(alpha, value);
            
            if (alpha > beta-1) break;
        }
        
        return value - 1;
    } else {
        int value = INT_MAX;

        for (auto& action : node->get_valid_actions()) {

            value = std::min(value, minimax(node->add_child(action), alpha, beta, depth+1, true));
            beta  = std::min(beta, value);

            if (alpha > beta-1) break;
        }

        return value + 1;        
    }
}
