// align your data structures to improve performance
// maybe start with big types first
// char can be aligned to 1 byte
// short can be aligned to 2 bytes
// int can be aligned to 4 bytes
// float can be aligned to 4 bytes
// double can be aligned to 8 bytes
// long long can be aligned to 8 bytes
// pointers can be aligned to 4 or 8 bytes depending on architecture

#include <iostream>

struct lol{
    char a;        // 1 byte
    // 3 bytes padding here for alignment
    int b;         // 4 bytes
    double c;      // 8 bytes
};

//instead of 1 + 4 + 8 = 13, we get 16 bc int can be in multiples of 4 only, so pos 1, 2, 3 is padded.

struct lol2{
    double c;
    int b;
    char a;
};
// unfortunately this also has padding, not a good example but you get it lol.

int main(){
    std::cout << sizeof(lol) << std::endl; // should print 16
    std::cout << sizeof(lol2) << std::endl; // should print 13
}