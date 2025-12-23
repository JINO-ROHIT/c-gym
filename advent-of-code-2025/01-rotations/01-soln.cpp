#include <fstream>
#include <iostream>
#include <string>

// remember the range is between 0 to 99, 100th become 0

// imagine 99 + 2 = 1 ( 0 + 1)
// imagine 99 + 20 = 19 ( 0 + 19)
// imagine 80 + 20 = 0

// imagine (95, R(60)) = 55
int handle_right(int curr_pos, int turn){

    int lol = curr_pos + turn;
    if(lol <= 99){
        return lol;
    }
    else{
        return (lol - 100) % 100;
    }
}

// (50, L68) --> -18 = 82
int handle_left(int curr_pos, int turn){
    int lol = curr_pos - turn;
    if(lol >= 0){
        return lol;
    }
    else{
        return (100 + lol) % 100;
    }
}

int main(){
    std::ifstream ifs;
    std::string line;

    int curr_pos = 50;

    int count = 0;
    ifs.open("input.txt");
    while(std::getline(ifs, line)){

        if(line.find("R") != std::string::npos){
            //std::cout << line << std::endl;
            //std::cout << line.substr(1, line.length()) << std::endl;
            curr_pos = handle_right(curr_pos, std::stoi(line.substr(1, line.length())));
        }
        else{
            curr_pos = handle_left(curr_pos, std::stoi(line.substr(1, line.length())));
        };

        if (curr_pos == 0){
            count += 1;
        }

        //std::cout << line << std::endl;
        //std::cout << curr_pos << std::endl;
    }

    std::cout << count << std::endl;
    ifs.close();

}