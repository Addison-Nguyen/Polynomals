#include "lpoly.h"
#include "node.h"
#include <cmath>
#include <cassert>
#include <string>
#include <sstream>

lpoly::lpoly()
{
    _head_ptr = nullptr;
}

lpoly::lpoly(const lpoly & p)
{
    node * tail_ptr;
    list_copy(p._head_ptr, _head_ptr, tail_ptr);
}

lpoly::lpoly(const coeff_type & c, size_type i)
{
    _head_ptr = new node(node::value_type(c, i), nullptr);
}

lpoly::~lpoly()
{
    list_clear(_head_ptr);
}

int lpoly::degree() const
{
    if (_head_ptr == nullptr)
        return -1;
    const node * p = _head_ptr;
    p = p->link();
    const node * previous = _head_ptr;
    while (p != nullptr)
    {
        p = p->link();
        previous = previous->link();
    }
    return previous->data().i;
}

lpoly::coeff_type lpoly::operator[](size_type i) const
{
    const node * p;
    for (p = _head_ptr; p != nullptr && p->data().i != i; p = p->link());
    if (p == nullptr)
        return 0;
    return p->data().c;
}

lpoly::coeff_type lpoly::operator()(const coeff_type & v) const
{
    lpoly::coeff_type ans(0);
    for (const node * p = _head_ptr; p != nullptr; p = p->link())
        ans += p->data().c * pow(v, p->data().i);
    return ans;
}

lpoly lpoly::derivative() const
{
    lpoly derivative;
    node * tail_ptr;
    for (node * p = derivative._head_ptr; p != nullptr; p = p->link())
        if (p->data().i != 0)
        {
            derivative.set(p->data().i - 1, p->data().i * p->data().c);
        }
    return derivative;
}

lpoly lpoly::integral() const
{
    lpoly integral;
    node * tail_ptr;
    for (node * p = _head_ptr; p != nullptr; p = p->link())
    {
        integral.set(p->data().i + 1, p->data().c / (p->data().i + 1));
    }
    return integral;
}

void lpoly::print() const
{
    if (_head_ptr == nullptr)
        std::cout << "zero poly" << std::endl;
    else
        for (const node * p = _head_ptr; p != nullptr; p = p->link())
            if (p->data().c >= 0)
                std::cout << " + " << p->data();
            else
                std::cout << " - " << p->data();
}

void lpoly::set(size_type i, const coeff_type & c)
{
    if (c != 0)
    {

        // std::cout<<"error1"<<std::endl;
        node * p = _head_ptr;
        while (p != nullptr)
        {
            // std::cout<<"error2"<<std::endl;
            if (p->data().i == i)
            {
                p->set_data(node::value_type(c, i));
                // std::cout<<"error3"<<std::endl;
                return;
            }
            p = p->link();
        }

        p = _head_ptr;
        if (_head_ptr == nullptr || p->data().i > i)
        {
            // std::cout<<"error4"<<std::endl;
            list_head_insert(_head_ptr, term(c, i));
        }
        else
        {
            // p goes to next pointer, q becomes previous pointer
            if (p != nullptr)
            {
                p = p->link();
                node * q = _head_ptr;
                while (p != nullptr && p->data().i < i)
                {
                    // std::cout<<"error5"<<std::endl;
                    q = q->link();
                    p = p->link();
                }
                list_insert(q, term(c, i));
            }
        }
    }
    else
    {
        lpoly real;
        node * tail_ptr;
        list_copy(_head_ptr, real._head_ptr, tail_ptr);
        node * p = _head_ptr;
        if (p != nullptr)
        {
            // std::cout<<"error6"<<std::endl;
            if (p != nullptr && p->data().i == i &&  real.degree()== i)
                list_clear(_head_ptr);
            else if (p != nullptr && p->data().i == i && real.degree() != i)
                list_head_remove(_head_ptr);
            else
            {
                // std::cout<<"error8"<<std::endl;
                // p goes to next pointer, q becomes previous pointers
                p = p->link();
                node * q = _head_ptr;
                while (p != nullptr && p->data().i != i)
                {
                    // std::cout<<"error9"<<std::endl;
                    q = q->link();
                    p = p->link();
                }
                if (p != nullptr)
                    list_remove(q);
            }
        }
    }
}

void lpoly::operator =(const lpoly & source)
{
    node * tail_ptr;
    list_clear(_head_ptr);
    list_copy(source._head_ptr, _head_ptr, tail_ptr);
}

void lpoly::operator +=(const lpoly & source)
{
    lpoly ans;
    node * tail_ptr;
    const node * p;
    for (p = source._head_ptr; p != nullptr; p = p->link())
    {
        bool b(false);
        for (const node * q = _head_ptr; q != nullptr; q = q->link())
            if (q->data().i == p->data().i)
            {
                ans.set(q->data().i, q->data().c + p->data().c);
                b = true;
            }
        if (b == false)
            ans.set(p->data().i, p->data().c);
    }

    for (const node * s = _head_ptr; s != nullptr; s = s->link())
    {
        bool c(false);
        for (const node * r = ans._head_ptr; r != nullptr; r = r->link())
            if (s->data().i == r->data().i)
            {
                c = true;
            }
        if (c == false)
            ans.set(s->data().i, s->data().c);
    }

    list_clear(_head_ptr);
    list_copy(ans._head_ptr, _head_ptr, tail_ptr);
}

void lpoly::operator -=(const lpoly & source)
{
    lpoly ans;
    node * tail_ptr;
    const node * p;
    for (p = source._head_ptr; p != nullptr; p = p->link())
    {
        bool b(false);
        for (const node * q = _head_ptr; q != nullptr; q = q->link())
            if (q->data().i == p->data().i)
            {
                ans.set(q->data().i, q->data().c - p->data().c);
                b = true;
            }
        if (b == false)
            ans.set(p->data().i, -p->data().c);
    }

    for (const node * s = _head_ptr; s != nullptr; s = s->link())
    {
        bool c(false);
        for (const node * r = ans._head_ptr; r != nullptr; r = r->link())
            if (s->data().i == r->data().i)
            {
                c = true;
            }
        if (c == false)
            ans.set(s->data().i, s->data().c);
    }

    list_clear(_head_ptr);
    list_copy(ans._head_ptr, _head_ptr, tail_ptr);
}


void lpoly::operator *=(const lpoly & source)
{
    lpoly real, filler;
    node * tail_ptr;
    for (const node * p = source._head_ptr; p != nullptr; p = p->link())
        for (const node * q = _head_ptr; q != nullptr; q = q->link())
        {
            filler.set(q->data().i + p->data().i, p->data().c * q->data().c);
            real += filler;
            list_clear(filler._head_ptr);
        }
    list_clear(_head_ptr);
    list_copy(real._head_ptr, _head_ptr, tail_ptr);
}

void lpoly::operator /=(const lpoly & source)
{
    assert(source._head_ptr != nullptr);
    lpoly real, filler, dividend;
    node * tail_ptr;
    list_copy(_head_ptr, dividend._head_ptr, tail_ptr);
    if (degree() < source.degree())
    {
        // std::cout<<"error1"<<std::endl;
        list_clear(_head_ptr);
    }
    else
    {
        while (dividend.degree() >= source.degree())
        {
            node * p(dividend._head_ptr), * q(source._head_ptr);
            p = p->link();
            q = q->link();
            // prev_p = last node of dividend, prev_q = last node of source
            node * prev_p(dividend._head_ptr), * prev_q(source._head_ptr);
            // std::cout<<"error2"<<std::endl;
            while (p != nullptr)
            {
                prev_p = prev_p->link();
                p = p->link();
            }
            while (q != nullptr)
            {
                prev_q = prev_q->link();
                q = q->link();
            }
            filler.set(prev_p->data().i - prev_q->data().i, prev_p->data().c / prev_q->data().c);
            real += filler;
            lpoly subtract = source * filler;
            // std::cout<<dividend - subtract<<std::endl;
            list_clear(filler._head_ptr);
            dividend -= subtract;
        }
        list_clear(_head_ptr);
        list_copy(real._head_ptr, _head_ptr, tail_ptr);
    }
}

void lpoly::negate()
{
    lpoly ans;
    node * tail_ptr;
    for (const node * p = _head_ptr; p != nullptr; p = p->link())
        ans.set(p->data().i, -(p->data().c));
    list_clear(_head_ptr);
    list_copy(ans._head_ptr, _head_ptr, tail_ptr);
}

std::istream & operator >> (std::istream & is, lpoly & p)
{
    std::string s;
    getline(is, s);
    std::stringstream ss(s);
    lpoly::coeff_type c;
    lpoly::size_type i;   // c is a coefficient, i is a power


    while (ss >> c >> i)
    {
        p.set(i, c);
    }

    return is;
}

std::ostream & operator << (std::ostream & os, const lpoly & p)
{
    if (p.degree() == -1)
        os << "zero poly";
    else
        for (int i = (p.degree()); i>=0; --i)
            if (p[i] != 0) {
                if (p[i] == 1) {
                    if (i == 0)
                        os << " + " << p[i];
                    else if (i == 1)
                        os << " + " << "x";
                    else
                        os << " + " << "x" << "^" << i;
                }
                else if (p[i] == -1) {
                    if (i == 0)
                        os << " - " << abs(p[i]);
                    else if (i == 1)
                        os << " - " << "x";
                    else
                        os << " - " << "x" << "^" << i;
                }
                else if (p[i] > 0) {
                    if (i == 0)
                        os << " + " << p[i];
                    else if (i == 1)
                        os << " + " << p[i] << "x";
                    else
                        os << " + " << p[i] << "x" << "^" << i;
                }
                else {
                    if (i == 0)
                        os << " - " << abs(p[i]);
                    else if (i == 1)
                        os << " - " << abs(p[i]) << "x";
                    else
                        os << " - " << abs(p[i]) << "x" << "^" << i;

                }
            }
    return os;
}

bool operator ==(const lpoly &a, const lpoly &b)
{
    if (a.degree() != b.degree())
        return false;
    else
        for (int i = 0; i <= a.degree(); ++i)
            if (a[i] != b[i])
                return false;
    return true;
}


lpoly operator +(const lpoly & a, const lpoly & b)
{
    lpoly ans(a);
    ans += b;
    return ans;
}

lpoly operator -(const lpoly & a, const lpoly & b)
{
    lpoly ans(a);
    ans -= b;
    return ans;
}

lpoly operator *(const lpoly & a, const lpoly & b)
{
    lpoly ans(a);
    ans *= b;
    return ans;
}

lpoly operator /(const lpoly & a, const lpoly & b)
{
    assert(b.degree()!=-1);
    lpoly ans(a);
    ans /= b;
    return ans;
}

lpoly operator -(const lpoly & p)
{
    lpoly ans(p);
    ans.negate();
    return ans;
}
