// #include <iostream>

// void log(const char* message){
//     std::cout << message << std::endl;
// }

// int main(){
//     std::cout << "main before log fn" << std::endl;
//     log("hey");    
// }

// main takeways 
// 1. declaration diff from definition. if the definition is below the main, then cannot find the fn, in that case write a declaration on top.
// 2. say the log fn has some error, use the std:;endl to flush the output, so if it appears before the error, we can get some logs
 

#include <iostream>

void log(const char* message) {
    int* p = nullptr;
    *p = 42; // seg fault 
}

int main() {
    std::cout << "main before log fn" << std::endl;
    log("hey");
    std::cout << "main after log fn" << std::endl;
}
