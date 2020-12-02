/**
 * @file Implementation of Node.hpp
 */

#include "Node.hpp"
#include <memory>

/** Initialize a Node object from a state */
Node::Node(const State& _state)
    : state(std::make_shared<State>(_state))
    , parent(std::weak_ptr<Node>())
    , valid_actions(_state.get_valid_actions())
    , parent_action{-1}
    , value(0)
{}

/** Copy constructor to add a child */
Node::Node(const node_ptr& _parent, int action)
    : state(std::make_shared<State>(_parent->state->apply_action(action)))
    , parent(_parent)
    , valid_actions(state->get_valid_actions())
    , parent_action{action}
    , value(_parent->value)
{}

std::shared_ptr<Node>& Node::add_child(int action)
{
    children.emplace_back(std::make_shared<Node>(this->shared_from_this(), action));
    return children.back();
}

