#ifndef LPOLY_H
#define LPOLY_H

// a class to represent polynomial of arbitrary size
// p(x) = c0 + c1*x + c2*x^2 + ... + c_n*x^n

#include <iostream>
#include <cstdlib>
#include <cassert>
#include "node.h"

class lpoly
{
public:

    // CONSTANTS & TYPES
    typedef double              coeff_type;
    typedef std::size_t 	size_type;


    // CONSTRUCTORS & DESTRUCTOR

    // pre:
    // post: creates a zero polynomial
    lpoly();

    // pre:
    // post: creates a new lpoly with same value as p
    lpoly(const lpoly & p);

    // pre:
    // post: creates a new lpoly with a single term c*x^i
    lpoly(const coeff_type & c, size_type i);

    ~lpoly();

    // CONST MEMBERS

    // pre:
    // post: returns the highest power among nonzero terms of this lpoly
    // example: degree of 3^x2 - x + 1 is 2
    //          degree of the zero poly is defined to be -1
    int degree() const;

    // pre:
    // post: returns the coefficient of the term x^i of this lpoly (0 for most values of i)
    // example: p = 3x^2 + 4x + 1, then p[0] = 1, p[1] = 4, p[2] = 3, p[3] = 0
    coeff_type operator[](size_type i) const;

    // pre:
    // post: returns the value of this lpoly at x = v
    // example:  p = 3x^2 + 4x + 1, p(0) = 1, p(1) = 8
    coeff_type operator()(const coeff_type & v) const;


    // pre:
    // post: returns the derivative of this lpoly
    lpoly derivative() const;

    // pre:
    // post: returns the indefinite integral of this lpoly with zero constant term
    lpoly integral() const;

    void print() const;

    // MODIFICATION MEMBERS


    // pre:
    // post: _c[i] has been changed to c
    void set(size_type i, const coeff_type & c);


    // pre:
    // post: this lpoly is now a copy of the given lpoly source
    void operator =(const lpoly & source);


    // pre:
    // post: p has been added to/subtracted from/multiplied to this lpoly
    void operator +=(const lpoly &p);
    void operator -=(const lpoly &p);
    void operator *=(const lpoly &p);


    // pre: p != zero poly
    // post: this lpoly has been divided by p
    void operator /=(const lpoly &p);

    // pre:
    // post: all coefficients of this lpoly have been multiplied by -1
    void negate();

private:

    node *_head_ptr;

    // class invariants:
    // 1. _head_ptr is the address of the first node in a linked list of nodes
    // 2. each node represents a term c*x^i, where i is unique, and c is nonzero
    // 3. the terms are sorted in increasing value of i

};

// NONMEMBER FUNCTIONS and OVERLOADED OPERATORS

// pre:
// post: read a polynomial from input stream is into p assuming the format
//       coeff1 power1 coeff2 power2 ....
// examples:
//           3 2 -2 0 4 1  represents polynomial 3x^2 + 4x -2
//           4 2 -1 2      represents polynomial 3x^2
//           4 2 1 10 3 12 represents polynomial 4x^2 + x^10 + 3x^12
std::istream & operator >> (std::istream & is, lpoly & p);

// pre:
// post: output polynomial p to output stream os as a sum of terms having NONZERO coefficients in INCREASING powers
//       if p is the zero polynomial, output 'zero poly'
std::ostream & operator << (std::ostream & os, const lpoly & p);

// pre:
// post: returns true iff a and b represent the same polynomial
bool operator ==(const lpoly &a, const lpoly &b);


// pre:
// post: returns the sum/difference/product of two polynomials
lpoly operator +(const lpoly &, const lpoly &);
lpoly operator -(const lpoly &, const lpoly &);
lpoly operator *(const lpoly &, const lpoly &);

// pre: b != zero poly
// post: returns the quotient a/b
lpoly operator /(const lpoly & a, const lpoly & b);


// pre:
// post: returns the negative of p
lpoly operator -(const lpoly & p);


#endif // LPOLY_H

