#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <filesystem>
#include <sys/mman.h>

int main(){
    const char* file = "concepts/files/example.txt";
    int fd = open(file, O_RDONLY);

    size_t size = std::filesystem::file_size(file);
    char* data_ptr = (char*) mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

    std::cout << data_ptr[1];
}