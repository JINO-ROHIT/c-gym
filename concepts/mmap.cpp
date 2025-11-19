#include <iostream>
#include <fstream>
#include <fcntl.h>

#include <filesystem>
#include <sys/mman.h>

int main(){
    const char* file = "concepts/files/example.txt";
    int fd = open(file, O_RDONLY);
    // std::cout << fd;
    if (fd < 0) {
        perror("open");
        return 1;
    }

    size_t size = std::filesystem::file_size(file);

    // mmap(
    // NULL,       // Let OS choose address
    // size,       // Map exactly `size` bytes
    // PROT_READ,  // Pages should be readable
    // MAP_PRIVATE,// Copy-on-write, changes not written to file
    // fd,         // File descriptor of the file to map
    // 0           // Offset from start of file
    // );

    char* data = (char*) mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(data == MAP_FAILED){
        perror("MAP");
    }

    std::cout << data;

    munmap(data, size); // unmap at the end

}