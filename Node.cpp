/**
 * @file Implementation of Node.hpp
 */

#include "Node.hpp"
#include <memory>

/**
 * Initialize a Node object from a state
 * Resulting Node::parent is an empty shared pointer.
 */
Node::Node(State& _state)
    : state(_state)
    , parent(std::weak_ptr<Node>())
    , _ptr(std::shared_ptr<Node>())
    , valid_actions(_state.get_valid_actions())
    , parent_action{-1}
    , value(0)
{
    _ptr = shared_from_this();
}

/**
 * @details Use the user-defined @link Node::Node(const node_ptr& _parent, int action)
 *     constructor@endlink that makes sure the constructed child is not sole
 *     owner of its parent.
 */
std::shared_ptr<Node>& Node::add_child(int action)
{
    node_ptr child       = std::make_shared<Node>(state.apply_action(action));
    child->parent_action = action;
    child->parent        = get_self_ptr();
    child->valid_actions = child->state.get_valid_actions();
    child->value         = value;
    child->_ptr = child;
    
    return children.emplace_back(child);
}

