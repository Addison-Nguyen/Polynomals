#ifndef NODE_H
#define NODE_H

#include <iomanip>
#include <iostream>

struct term
{
    std::size_t i;
    double c;

    term(double ic = 0.0, std::size_t ii = 0)
    {
        i = ii;
        c = ic;
    }
};

std::istream & operator >> (std::istream &, term &);
std::ostream & operator << (std::ostream &, const term &);


class node
{
public:

    // TYPES & CONSTANTS
    typedef term value_type;

    // CONSTRUCTORS & DESTRUCTOR

    // pre:
    // post: a node has been created with given initial values
    //       default values = value_type() and nullptr
    node(const value_type & init_data = value_type(),
         node *       init_link = nullptr);

    // CONSTANT MEMBER FUNCTIONS

    // pre:
    // post: returns data value in this node
    value_type data() const;

    // pre:
    // post: returns a CONSTANT version of the link
    //       the user can use this link to read the next node
    //       BUT NOT TO CHANGE IT
    const node * link() const;

    // MODIFICATION MEMBERS

    // pre:
    // post: returns link of this node
    //       the user can use this link to read the next node
    //       AS WELL AS TO CHANGE IT
    node * link();


    // pre:
    // post: changes the value in this node to the given new value
    void set_data(const value_type & new_value);

    // pre:
    // post: changes the link in this node to the given new link
    void set_link(node * new_link);


private:

    // class invariants:
    //  1. _data stores value of this node
    //  2. _link stores the address of the node following this node
    value_type _data;
    node *     _link;

};

// NONMEMBER LINKED-LIST TOOLKIT FUNCTIONS


// pre: head_ptr points to the first node in a linked list
// post: returns the number of nodes in this linked list
std::size_t list_length(const node * head_ptr);

// pre: head_ptr points to the first node in a linked list
// post: a new node with data value entry has been added to the FRONT of this linked list
void list_head_insert(node * & head_ptr,
                      const node::value_type & entry);

;
// pre: head_ptr points to the first node of a linked list
// post: the values in this linked list have been printed in order to the screen
void list_print(const node * head_ptr);

// pre: head_ptr points to the first node in a linked list
//      or nullptr
// post: front node has been removed; if linked list is empty, do nothing
void list_head_remove(node * & head_ptr);

// pre: head_ptr points to the front node in a linked list or nullptr
// post: all nodes in this list has been deleted and head_ptr is set to nullptr;
//       if head_ptr == nullptr do nothing;
void list_clear(node * & head_ptr);

// pre: head_ptr points to the first node in a linked list or nullptr;
// post: returns a pointer to the first node in this list whose data is target
//       if no such node exists, return nullptr
const node * list_search(const node * head_ptr, const node::value_type &target);
node * list_search(node * head_ptr, const node::value_type &target);


// pre: position > 0, head_ptr points to the first node in a linked list
// post: returns a pointer to the (position)^th node in the list
//       or nullptr if (position > length of list)
node * list_locate(node * head_ptr,
                  std::size_t position);
const node * list_locate(const node * head_ptr,
                        std::size_t position);

// pre: src_ptr points to the first node of a linked list
// post: a copy of the list is made;
//       head_ptr has the address of the first node of the copy
//       tail_ptr has the address of the last node of the copy
//       if src_ptr == nullptr, then head_ptr = tail_ptr = nullptr
void list_copy(const node * src_ptr,
               node * & head_ptr,
               node * & tail_ptr);

// pre: previous_ptr != nullptr
// post: a new node with entry value has been inserted after the node
//       whose address is in previous_ptr;
void list_insert( node * previous_ptr, const node::value_type & entry);


// pre: previous_ptr has a node following it
// post: the node following previous_ptr has been removed
void list_remove(node  * & previous_ptr);
#endif
