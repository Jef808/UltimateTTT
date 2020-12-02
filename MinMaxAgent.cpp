#include "MinMaxAgent.hpp"
#include "Node.hpp"
#include <algorithm>
#include <memory>
#include <vector>


MinMaxAgent::MinMaxAgent(const State& state)
    : root(std::make_shared<Node>(state))
    , token(state.get_next_player())
{}


int MinMaxAgent::choose_action() const
{
    std::vector<std::shared_ptr<Node>>& children = add_all_children(root);

    std::for_each(children.begin(), children.end(),
                  [&](auto& child)
                  {
                      set_value(*child);
                  });
    return std::max_element(children.begin(), children.end(),
                            [](const std::shared_ptr<Node>& child_l,
                               const std::shared_ptr<Node>& child_r)
                            {
                                return child_l->get_value() < child_r->get_value();
                            })->get()->get_parent_action();
}
    
std::vector<std::shared_ptr<Node>>& MinMaxAgent::add_all_children(Node& node) const
{
    std::for_each(node.get_valid_actions().begin(), node.get_valid_actions().end(),
        [&node](int action) {
            node.add_child(action);
        });
    return node.get_children();
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
inline int get_value_terminal(const State& state, Token agent_token)
{
    Token winner = state.get_winner();

        if (winner==Token::EMPTY) {
            return 0;
        }
        return (agent_token==winner ? 10 : -10);
}


int MinMaxAgent::set_value(Node& node, int depth, int max_depth) const
{
    // If game is over, use fixed reward function.
    if (node.get_state().is_terminal()) {
        int value = get_value_terminal(node.get_state(), token);
        node.set_value(value);
        return value;
    }
    // Otherwise, do minimax recursion.
    add_all_children(node);
    // First generate the minimax score of all children (recursion)
    std::vector<int> children_scores;
    std::transform(node.get_children().begin(),
                   node.get_children().end(),
                   std::back_inserter(children_scores),
                   [&, depth, max_depth](const Node::node_ptr& child)
                   {
                       set_value(*child, depth+1, max_depth);
                       return child->get_value();
                   });
    Token next_player = node.get_state().get_next_player();
    // If agent plays next, minimax score of current state
    // is max of children's scores.
    if (next_player == token) {
        node.set_value(*std::max_element(children_scores.begin(),
                                 children_scores.end(),
                                 [](int a, int b)
                                 {
                                     return a < b;
                                 }) - 1);
    }
    // If agent's opponent plays next, minimax score of current
    // state is min of children's scores.
    else {
        node.set_value(*std::min_element(children_scores.begin(),
                                 children_scores.end(),
                                 [](int a, int b)
                                 {
                                     return a < b;
                                 }) + 1);
    }
    // The -1 / +1 tweaks above is so that the agent prefers quick
    // games when winning, and long games when losing (letting opponent
    // make a mistake instead of giving up).
    return node.get_value();
}


