// A copy constructor is a constructor that is used to initialize an object with an existing object of the same type
// if you dont create one, the compiler makes one for you

// TO-DO need to read up more on this

#include <iostream>

// class Fraction
// {
// private:
//     int m_numerator{ 0 };
//     int m_denominator{ 1 };

// public:
//     // Default constructor
//     Fraction(int numerator=0, int denominator=1)
//         : m_numerator{numerator}, m_denominator{denominator}
//     {
//     }

//     void print() const
//     {
//         std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
//     }
// };

// int main()
// {
//     Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
//     Fraction fCopy { f }; // What constructor is used here? this is the copy constructor

//     f.print();
//     fCopy.print();

//     return 0;
// }


// lets add our own copy constructor


class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    Fraction(Fraction const &fraction) : m_numerator{fraction.m_numerator}, m_denominator{fraction.m_denominator}{
        std::cout << "Copy constructor called\n";
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here? this is the copy constructor

    f.print();
    fCopy.print();

    return 0;
}