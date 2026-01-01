#include <iostream>

int* make_stack(int size){
    int A[size * size];
    A[0] = 10;
    A[1] = 20;
    return A; // a major bug since the lifetime is done
}

int* make_heap(int size){
    int* b = new int[size * size];
    b[0] = 10;
    b[1] = 20;
    return b;
}

int main() {

    // make a matrix, increase this too much and not enough space on the stack
    int size = 512;

    // int* a_ptr = make_stack(size);
    // std::cout << a_ptr[0] << " " << a_ptr[1] << std::endl;

    // lets make it on heap then
    int* b_ptr = make_heap(size);
    std::cout << b_ptr[0] << " " << b_ptr[1] << std::endl;

}