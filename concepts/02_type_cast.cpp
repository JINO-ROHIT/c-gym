#include <iostream>

int main() {
    int test = 4;
    double yeap = static_cast<double>(test);

    std::cout << "test address: " << &test << ", value: " << test << '\n';
    std::cout << "yeap address: " << &yeap << ", value: " << yeap << '\n';
}