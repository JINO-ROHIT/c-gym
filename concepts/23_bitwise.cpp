#include <iostream>

using namespace std;

int main(){
    cout << ~1 << endl; // bitwise not - [general rule for signed integers ~x == -(x + 1)]


    //bitwise AND
    int a = 6;   // 110
    int b = 3;   // 011
    int c = a & b; // 010 = 2

    cout << c << endl;

    //bitwise OR
    int d = 6;   // 110
    int e = 3;   // 011
    int z = d | e; // 111 = 7


    //bitwise XOR - sets bits that are different
    int f = 6;   // 110
    int g = 3;   // 011
    int x = f ^ g; // 101 = 5

    //left shift - shifts bits left and fills with zero
    int y = 3;   // 0011
    //x << 2;      // 1100 = 12
    y << 1;
    cout << y << endl;

}