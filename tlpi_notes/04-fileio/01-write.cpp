#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(){
    const char* pathname = "test.txt";
    const char* text = "hey man how are you?";

    int fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC);

    size_t buff_size = write(fd, text, strlen(text));

    close(fd);

    std::cout << buff_size << std::endl;
}