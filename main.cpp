#include <iostream>
#include "lpoly.h"

using namespace std;


int main()
{
    const int SIZE(5);
    lpoly p[SIZE];
    lpoly zero, one;
    one.set(0, 1);

    cout << "INPUT:" << endl;
    cout << endl;

    cout << "Please enter 3 2 -2 0 4 1: ";
    cin >> p[0];
    cout << "p[0] = " << p[0] << endl;

    cout << "Please enter 4 2 -1 2: ";
    cin >> p[1];
    cout << "p[1] = " << p[1] << endl;

    cout << "Please enter 4 2 1 10 3 12: ";
    cin >> p[2];
    cout << "p[2] = " << p[2] << endl;

    cout << "Please enter 0 0: ";
    cin >> p[3];
    cout << "p[3] = " << p[3] << endl;

    cout << "Please enter -1 0 2 100: ";
    cin >> p[4];
    cout << "p[4] = " << p[4] << endl;


    cout << endl;
    cout << "CONSTANT POLYS: " << endl;
    cout << endl;

    cout << "zero = " << zero << endl;
    cout << "one = " << one << endl;


    cout << endl;
    cout << "COPY CONSTRUCTOR & ASSIGNMENT: " << endl;
    lpoly pcopy(p[2]);
    cout << p[2] << " == " << pcopy << " ? " << (p[2] == pcopy) << endl;
    pcopy = p[0];
    cout << pcopy << " == " << p[0] << " ? " << (pcopy == p[0]) << endl;


    cout << endl;
    cout << "DEGREE:" << endl;
    lpoly pdegree;
    pdegree.set(0, 1);
    pdegree.set(1, -1);
    pdegree.set(4, 3);
    cout << pdegree << " has degree " << pdegree.degree() << endl;
    for (auto e: p)
        cout << e << " has degree " << e.degree() << endl;


    cout << endl;
    cout << "COEFFICIENTS: " << endl;;
    cout << pdegree << " has coefficients: ";
    for (int i = 0; i <= pdegree.degree(); ++i)
        cout << pdegree[i] << " ";
    cout << endl;
    cout << "The coefficient of x^1000000 in " << p[0] << " is " << p[0][1000000] << endl;

    cout << "Original p[4] = " << p[4] << endl;
    p[4].set(200, -3);
    cout << "After setting the coefficient of X^200 to -3, p[4] = " << p[4] << endl;


    cout << endl;
    cout << "EVALUATION: " << endl;
    for (int i = 0; i < SIZE; ++i)
        cout << p[i] << "(" << i << ") = "  << p[i](i) << endl;


    cout << endl;
    cout << "DERIVATIVE & INTEGRAL: " << endl;
    for (int i = 0; i < SIZE; ++i)
    {
        cout << "derivative of " << p[i] << " = " << p[i].derivative() << endl;
        cout << "integral of " << p[i] << " = " <<  p[i].integral() << endl;
    }


    cout << endl;
    cout << "ADDITION::" << endl;
    cout << p[0] << " + " << p[1] << " = " << p[0] + p[1] << endl;
    cout << p[2] << " + " << p[3] << " = " << p[2] + p[3] << endl;
    cout << p[4] << " + " << zero << " = " << p[4] + zero<< endl;
    cout << zero << " + " << p[4] << " = " << zero + p[4] << endl;
    cout << p[4] << " + " <<  one << " = " << p[4] + one << endl;
    cout << one << " + " << p[4] << " = " << one + p[4] << endl;

    lpoly pnegative(p[2]);
    pnegative.negate();
    cout << p[2] << " - " << p[2] << " = " << p[2] + pnegative << endl;

    cout << endl;
    cout << "SUBTRACTION:" << endl;
    cout << p[0] << " - " << p[1] << " = " << p[0] - p[1] << endl;
    cout << p[1] << " - " << p[0] << " = " << p[1] - p[0] << endl;
    cout << p[0] << " + " << zero << " = " << p[0] + zero << endl;
    cout << zero << " + " <<  p[0] << " = " << zero + p[0] << endl;
    cout << p[0] << " + " <<  one << " = " << p[0] + one << endl;
    cout << one << " + " << p[0] << " = " << one + p[0] << endl;

    cout << endl;
    cout << "MULTIPLICATION:" << endl;
    cout << p[0] << " * " << p[1] << " = " << p[0] * p[1] << endl;
    cout << p[1] << " * " << p[0] << " = " << p[1] * p[0] << endl;
    cout << p[2] << " * " << zero << " = " << p[2] * zero << endl;
    cout << zero << " * " << p[2] << " = " << zero * p[2] << endl;
    cout << p[2] << " * " << one << " = " << p[2] * one<< endl;
    cout << one << " * " << p[2] << " = " << one * p[2] << endl;

    cout << endl;
    cout << "EQUALITY: " << endl;
    lpoly copy(p[0]);
    cout << p[0] << " == " << copy << " ? " << (p[0] == copy) << endl;
    cout << p[1] << " == " << copy << "? " << (p[1] == copy) << endl;
    cout << zero << " == " << zero << " ? " << (zero == zero) << endl;
    cout << zero << " == " <<  one << " ? " << (zero == one) << endl;
    cout << one << " == " << zero << " ? " << (one == zero) << endl;


    cout << endl;
    cout << "DIVISION:" << endl;
    cout << p[0] << " / " << p[1] << " = " << p[0] / p[1] << endl;
    cout << p[1] << " / " << p[0] << " = " << p[1] / p[0] << endl;
    cout << p[2] << " / " << one << " = " << p[2] / one<< endl;
    cout << one << " / " << p[2] << " = " << one / p[2] << endl;
    lpoly dividend =  lpoly(1, 3) - lpoly(1, 0);
    lpoly divisor = lpoly(1, 1) + lpoly(-1, 0);
    cout << dividend << " / " << divisor << " = " << dividend / divisor << endl;



    return 0;
}
