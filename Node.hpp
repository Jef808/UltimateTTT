/**
 * @file The Node class that serves as a wrapper of a state to run algorithms
 */

#pragma once

#include "State.hpp"
#include <memory>


/**
 * @Class Wrapper class around the state to handle the tree structure
 *     of most algorithms. Each note can expand its children and stores
 *     its value.
 */
class Node : std::enable_shared_from_this<Node> {
public:
    using state_ptr = std::shared_ptr<State>;
    using node_ptr  = std::shared_ptr<Node>;

    /** Initialize a Node object from a state. */
    Node(const State& _state);

    /** Copy constructor for adding a child */
    Node(const node_ptr& _parent, int action);
    ~Node() = default;
    
private:
    state_ptr state;                     
    std::weak_ptr<Node> parent;      
    int parent_action;
    std::vector<int> valid_actions;
    std::vector<node_ptr> children;      
    int value;
    
public:
    /**
     * Add a node to the vector #children corresponding to the given action
     *
     * @param action  The action that's being applied.
     */
    node_ptr& add_child(int action);
    
    /** Standard getters for the Node class */
    const std::vector<int>& get_valid_actions() const;
    int get_value() const;
    State& get_state() const;
    std::vector<node_ptr>& get_children();
    int get_parent_action() const;
   
    /** Standard setters for the Node class */
    void set_value(int _value);

private:
    
};


/// Short methods to implement right here

inline const std::vector<int>& Node::get_valid_actions() const
{
    return valid_actions;
}
inline int Node::get_value() const
{
    return value;
}
inline State& Node::get_state() const
{
    return *state;
}
inline int Node::get_parent_action() const
{
    return parent_action;
}
inline std::vector<Node::node_ptr>& Node::get_children()
{
    return children;
}
inline void Node::set_value(int _value)
{
    value = _value;
}
