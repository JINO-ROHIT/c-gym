#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd;
    int buff_size = 2;
    int read_size = 1;
    char lol[buff_size + 1]; // add 1 for null terminator for print

    fd = open("test.txt", O_RDONLY);
    std::cout << fd << std::endl;

    while(read_size > 0){
        read_size = read(fd, lol, buff_size);
        lol[read_size] = '\0';
        std::cout << lol << std::endl;
    }

    close(fd);
}