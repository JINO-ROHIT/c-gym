#include <unordered_map>
#include <string>
#include <iostream>

int main() {
    std::unordered_map<int, std::string> weights = {
        {1, "jino"},
        {2, "rohit"},
    }; 

    auto it = weights.find(2);
    std::cout << it->first << std::endl;
    std::cout << it->second << std::endl;
    std::cout << "############" << std::endl;

    // auto it_unk = weights.find(3);
    // std::cout << it_unk->first << std::endl;
    // std::cout << it_unk->second << std::endl;
    
};