#include <iostream>
#include <fstream>
#include <fcntl.h>

#include <filesystem>
#include <sys/mman.h>

int main(){
    const char* file = "concepts/files/model_embed_tokens_weight.bin";
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

    // std::cout.write(data, size); ts will print binary

    //read the header
    uint8_t dtype = data[0];
    uint8_t ndims = data[1];

    std::cout << (int)dtype << '\n';
    std::cout << (int)ndims << '\n';

    //read the dims
    int32_t* dims = (int32_t*)(data + 2); // move pointer byte 2

    std::cout << "dims: ";
    for (int i = 0; i < ndims; i++) {
        std::cout << dims[i] << " ";
    }
    std::cout << "\n";

    //read the actual values
    size_t header_bytes = 10; // we know this
    float* values = (float*)(data + header_bytes);

    size_t total_values = 1;
    for (int i = 0; i < ndims; i++) {
        total_values *= dims[i];
    }

    std::cout << "Total values: " << total_values << "\n";
    std::cout << "First 10 values:\n";
    for (int i = 0; i < 10 && i < total_values; i++) {
        std::cout << values[i] << " ";
    }
    std::cout << "\n";

    munmap(data, size); // unmap at the end

}