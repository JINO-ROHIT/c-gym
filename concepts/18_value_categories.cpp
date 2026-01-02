// lvalue usually resolves to an identifier
// rvalue resoilves to a literal and needs to be used immediately.


int main()
{
    int x { 5 }; // 5 is an rvalue
    int y { x }; // x is an lvalue expression

    const int z = 10; // z is a non modifiable lvalue
    return 0;
}