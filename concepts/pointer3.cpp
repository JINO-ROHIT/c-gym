#include <iostream>
#include <string>

struct A {
    char c;   // 1 byte
    int x;    // 4 bytes
    char y;   // 1 byte
};


int main(){
    const char* text = "timmy"; // ptr to t
    std::string candidate(text, 2);
    std::cout << text << std::endl;
    std::cout << candidate << std::endl;

    std::cout << *text << std::endl; //*text is the character stored at that pointer

    while(*text){
        std::cout << *text << std::endl;
        text++;
    };

    int value = 10;
    int* tokens = &value;
    std::cout << tokens << std::endl;
    std::cout << *tokens << std::endl;


    std::cout << sizeof(A) << std::endl;
}