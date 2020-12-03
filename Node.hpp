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
class Node : std::enable_shared_from_this<Node> {
public:
    using state_ptr = std::shared_ptr<State>;
    using node_ptr  = std::shared_ptr<Node>;

    /** Initialize a Node object from a state. */
    explicit Node(State _state);

    /** Just use defaults for now and optimize later */
    Node(const Node&) = default;
    ~Node()           = default;
    /**
     * @Note Inheritence from enable_shared_from_this overrides the assignment operator.
    y*/
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;
    
private:
    State                         state;
    std::weak_ptr<Node>           parent;
    int                           parent_action;
    mutable std::vector<int>      valid_actions;
    mutable std::vector<node_ptr> children;      
    int                           value;

    /** private constructor to avoid stray children. */
    node_ptr construct_child(int action);
         
public:
    node_ptr get_self_ptr();
    std::weak_ptr<Node> get_weak_ptr();
    std::vector<int>& get_valid_actions() const;
    int get_value() const;
    const State& get_state() const;
    std::vector<node_ptr>& get_children();
    /** The Node that lead to this one by applying an action */
    node_ptr get_parent() const;
    /** The Action used to pass from the parent Node to this */
    int get_parent_action() const;
    int set_value(int _value);

    /**
     * Converts a valid_action into an actual children of the node.
     * @param action  The action that gets transformed into a Node.
     */
    node_ptr& add_child(int action);
};


inline std::weak_ptr<Node> Node::get_weak_ptr()
{
    return weak_from_this();
}
inline std::shared_ptr<Node> Node::get_self_ptr()
{
    return shared_from_this();
}
inline std::vector<int>& Node::get_valid_actions() const
{
    return valid_actions;
}
inline int Node::get_value() const
{
    return value;
}
inline const State& Node::get_state() const
{
    return state;
}
inline std::shared_ptr<Node> Node::get_parent() const
{
    return parent.lock();
}
inline int Node::get_parent_action() const
{
    return parent_action;
}
inline std::vector<Node::node_ptr>& Node::get_children()
{
    return children;
}
inline int Node::set_value(int _value)
{
    return value = _value;
}
