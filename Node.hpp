/**
 * @file The Node class that serves as a wrapper of a state to run algorithms
 */

#pragma once

#include "State.hpp"
#include <memory>
#include <list>


/**
 * @Class Wrapper class around the state to handle the tree structure
 *     of most algorithms. Each note can expand its children and stores
 *     its value.
 *
 * @Note  When adding a child, we're not copying a node, we're constructing a
 *     new node form a const ref to an action!
 */
class Node : public std::enable_shared_from_this<Node> {
public:
    using state_ptr = std::shared_ptr<State>;
    using node_ptr  = std::shared_ptr<Node>;

    /** Initialize a (root) Node object from a state. */
    Node(const State& _state);

    /** Initialize a (child) Node object from a state */
    Node(const State& _state, const Node::node_ptr& _parent, int _parent_act);

    node_ptr get_node() { return shared_from_this(); }
    
    node_ptr& add_child(int action);
    
private:
    state_ptr                     state;
    std::weak_ptr<Node>           parent;
    int                           parent_action;
    mutable std::vector<int>      valid_actions;
    std::vector<node_ptr>         children;      
    int                           value;
    int                           n_visits;
    
    
            
public:
    const std::shared_ptr<State>& get_state() const { return state; }
    std::vector<int>& get_valid_actions() const { return valid_actions; }
    int get_value() const { return value; }
    std::vector<node_ptr>& get_children() { return children; }
    std::weak_ptr<Node> get_parent() { return parent.lock(); }
    int get_parent_action() const { return parent_action; }
    int get_n_visits() const { return n_visits; }
    int set_value(int _value) { return value = _value; }
};

inline bool operator<(const Node::node_ptr& lhs, const Node::node_ptr& rhs)
{
    return lhs->get_value() < rhs->get_value();
}
