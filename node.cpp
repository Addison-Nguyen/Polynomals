#include "node.h"
#include <cassert>

bool operator ==(const term &a, const term &b)
{
    return (a.i == b.i);
}

std::ostream & operator << (std::ostream & os, const term & t)
{
    os << std::showpos << t.c << "x^" << std::noshowpos << t.i;
    return os;
}

std::istream & operator >> (std::istream & is, term & t)
{
    is >> t.c >> t.i;
    return is;
}


node::node(const value_type & init_data,
           node * init_link)
{
    _data = init_data;
    _link = init_link;
}

void node::set_data(const value_type & new_data)
{
    _data = new_data;
}

void node::set_link(node * new_link)
{
    _link = new_link;
}

node::value_type node::data() const
{
    return _data;
}

const node * node::link() const
{
    return _link;
}

node * node::link()
{
    return _link;
}

std::size_t list_length(const node * head_ptr)
{
    std::size_t ans(0);
    for (const node * p = head_ptr; p != nullptr; p = p->link())
        ++ans;

    return ans;
}

void list_head_insert(node * & head_ptr,
                      const node::value_type & entry)
{
    head_ptr = new node(entry, head_ptr);
}

void list_print(const node * head_ptr)
{
    for (const node *p = head_ptr; p != nullptr; p = p->link())
        std::cout << p->data() << " ";
    std::cout << std::endl;
}

void list_head_remove(node * & head_ptr)
{
    if (head_ptr == nullptr)
        return;

    node * temp = head_ptr;
    head_ptr = head_ptr->link();
    delete temp;
}

void list_clear(node * & head_ptr)
{
    while (head_ptr != nullptr)
    {
        node * temp = head_ptr;
        head_ptr = head_ptr->link();
        delete temp;
    }
}


const node * list_search(const node * head_ptr,
                        const node::value_type & target)
{
    const node * p;


    for (p = head_ptr; p != nullptr; p = p->link())
        if (p->data() == target)
            return p;

    return nullptr;

}

node * list_search(node * head_ptr,
                  const node::value_type & target)
{
    node * p;


    for (p = head_ptr; p != nullptr; p = p->link())
        if (p->data() == target)
            return p;

    return nullptr;
}

node * list_locate(node * head_ptr,
                  std::size_t position
                  )

{
    std::size_t count(1);
    node * p;

    for (p = head_ptr;
         p != nullptr && count < position;
         p = p->link())
        ++count;

    return p;
}

const node * list_locate(const node * head_ptr,
                        std::size_t position
                        )

{
    std::size_t count(1);
    const node * p;

    for (p = head_ptr;
         p != nullptr && count < position;
         p = p->link())
        ++count;

    return p;
}

void list_insert(node * previous_ptr,
                 const node::value_type & entry)
{
    assert(previous_ptr != nullptr);
    node * new_ptr = new node(entry, previous_ptr->link());
    previous_ptr->set_link(new_ptr);

}

void list_copy(const node * src_ptr,
               node * & head_ptr,
               node * & tail_ptr)
{
    head_ptr = tail_ptr = nullptr;
    if (src_ptr == nullptr)
        return;
    list_head_insert(head_ptr, src_ptr->data());
    tail_ptr = head_ptr;

    for (const node * p = src_ptr->link();
         p != nullptr;
         p = p->link())
    {
        list_insert(tail_ptr, p->data());
        tail_ptr = tail_ptr->link();
    }

}

void list_remove(node * & previous_ptr)
{
    assert(previous_ptr->link() != nullptr);

    node * save = previous_ptr->link();
    previous_ptr->set_link(save->link());

    delete save;
}

