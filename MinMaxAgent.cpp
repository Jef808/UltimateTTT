#include "MinMaxAgent.hpp"
#include "Node.hpp"
#include <algorithm>
#include <memory>
#include <vector>
#include <functional>


MinMaxAgent::MinMaxAgent(const Node& _root)
    : root(std::make_shared<Node>(_root))
    , token(_root.get_state().get_next_player())
{}


int MinMaxAgent::choose_action()
{
    std::vector<std::shared_ptr<Node>>& children = add_all_children(root);

    std::for_each(children.begin(), children.end(),
                  [&](std::shared_ptr<Node>& child)
                  {
                      set_value(child);
                  });
    return std::max_element(children.begin(), children.end(),
                            [](const std::shared_ptr<Node>& child_l,
                               const std::shared_ptr<Node>& child_r)
                            {
                                return child_l->get_value() < child_r->get_value();
                            })->get()->get_parent_action();
}
    
std::vector<std::shared_ptr<Node>>& MinMaxAgent::add_all_children(std::shared_ptr<Node>& node) const
{
    std::for_each(node->get_valid_actions().begin(), node->get_valid_actions().end(),
        [&node](int action) {
            node->add_child(action);
        });
    return node->get_children();
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
inline int set_value_terminal(std::shared_ptr<Node>& node, Token agent_token)
{
    Token winner = node->get_state().get_winner();

        if (winner==Token::EMPTY) {
            return node->set_value(0);
        }
        return (agent_token==winner ? node->set_value(10) : node->set_value(-10));
}


int MinMaxAgent::set_value(std::shared_ptr<Node> node, int depth, int max_depth, bool maximizing_player) const
{
    add_all_children(node);
    
    if (node->get_state().is_terminal()) {
        return set_value_terminal(node, token);
    }

    std::for_each(node->get_children().begin(), node->get_children().end(),
                  [&](Node::node_ptr& child)
                  {
                      set_value(child, depth+1, max_depth, !maximizing_player);                      
                  });
        
    // If it's our agent's turn
    if (maximizing_player) {
        return std::max_element(node->get_children().begin(),
                                node->get_children().end(),
                                [&](Node::node_ptr& child1, Node::node_ptr& child2)
                                {
                                    return set_value(child1, depth+1, max_depth, !maximizing_player) < set_value(child2, depth+1, max_depth, !maximizing_player);
                                })->get()->get_value()-1;
    } else {
        return std::min_element(node->get_children().begin(),
                                node->get_children().end(),
                                [&](Node::node_ptr& child1, Node::node_ptr& child2)
                                {
                                    return set_value(child1, depth+1, max_depth, !maximizing_player) < set_value(child2, depth+1, max_depth, !maximizing_player);
                                })->get()->get_value()+1;
    }
}


