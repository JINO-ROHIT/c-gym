// use the new keyword to allocate stuff on heap
// use it when you there isnt enough space in stack (or) when you need to manage the lifecycle of the object yourself unlike stack

#include <iostream>

int* make_in_stack() {
    int x = 10;
    return &x; 
};

void trash_stack() {
    int arr[1000];
    for (int i = 0; i < 1000; i++)
        arr[i] = i;
}

int* make_in_heap(){
    return new int(10);
}

int main(){
    {
        int b = 2;
    }
    //std::cout << b <<std::endl; // see here b becomes undefined bc out of scope

    //new returns a ptr to the address where the object is created
    int* a;
    {
        a = new int(10);
    }

    std::cout << *a << std::endl;

    delete a; // need to do manual cleanup

    int* s = make_in_stack();

    trash_stack(); // adding this to make the dangling pointer from the stack s fail

    std::cout << *s << std::endl; // this is wrong bc the stack lifetime is done

    int* h = make_in_heap();
    std::cout << *h << std::endl;

    delete h;

}