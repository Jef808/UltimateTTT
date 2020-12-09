/**
 * @file Implementation of Node.hpp
 *
 * @Comments  The point of inheriting from enable_shared_from_this<Node> can be seen
 *     for example in the implementation of the Node::child_ctor. At the end of the
 *     definition, there are two references managing the child's data so the child
 *     could go on exploring the tree, eventually getting lost, but without even
 *     storing it inside of the parent's node yet, we still could access it.
 *
 *     This will be useful for prunning entire branches, storing best-to-dates
 *     on the fly without stopping simulations etc...
 *
 *     Main thing I feel after working with this is being able to pass smart
 *     pointers using move semantics as if they're unique_ptrs but I don't loose
 *     them if the function is void or something!
 */

#include "Node.hpp"
#include <memory>

/**
 * Initialize a Node object from a state
 * Store an empty weak_ptr for the parent.
 */
Node::Node(const State& _state)
    : parent(std::weak_ptr<Node>())
    , parent_action{-1}
    , valid_actions(_state.get_valid_actions())
    , value(0)
    , n_visits(0)
{
    state = std::make_shared<State>(_state);
}

Node::Node(const State& _state, const Node::node_ptr& _parent, int _parent_act)
    : parent(std::weak_ptr<Node>(_parent))
    , parent_action(_parent_act)
    , valid_actions(_state.get_valid_actions())
    , value(_parent->get_value())
    , n_visits(0)
{
    state = std::make_shared<State>(_state);
}

Node::node_ptr& Node::add_child(int action)
{
    return children.emplace_back(std::make_shared<Node>(state->apply_action(action), this->get_node(), action));
}
