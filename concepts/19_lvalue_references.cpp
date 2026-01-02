#include <iostream>

using namespace std;

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    cout << x << '\n';  // print the value of x (5)
    cout << ref << '\n'; // print the value of x via ref (5)


    // int& ref = 5; disallowed, but we can have
    const int& reff = 5;
    cout << reff << '\n';

    // When a reference is initialized with an object (or function), we say it is bound to that object (or function). 
    // The process by which such a reference is bound is called reference binding. 
    // The object (or function) being referenced is sometimes called the referent.

    return 0;
}