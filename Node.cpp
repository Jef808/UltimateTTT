/**
 * @file Implementation of Node.hpp
 */

#include "Node.hpp"
#include <memory>

/**
 * Initialize a Node object from a state
 * Resulting Node::parent is an empty shared pointer.
 */
Node::Node(State _state)
    : state(_state)
    , parent(std::weak_ptr<Node>())
    , valid_actions(_state.get_valid_actions())
    , parent_action{-1}
    , value(0)
{}

/**
 * Constructs the Node and wrap it in a shared_ptr
 */
std::shared_ptr<Node> Node::construct_child(int action)
{
    Node*    child_node = new Node(state.apply_action(action));
    node_ptr child(child_node);

    child->parent        = this->get_weak_ptr();
    child->parent_action = action;
    child->value         = value;
    
    return child;
}

/**
 * Create child node then share its ownership with the parent before storing it.
 * @details  Remember how the Node* object needs to be wrapped inside a shared_ptr
 *     before its ownership can be furthermore shared with the parent!
 */
std::shared_ptr<Node>& Node::add_child(int action)
{
    node_ptr child = construct_child(action);
    
    return children.emplace_back(child->get_self_ptr());
}

