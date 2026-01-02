#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <signal.h>

static size_t PAGE_SIZE;

void wait(const char* msg) {
    std::cout << "\n=== " << msg << " ===\n";
    std::cout << "ENTER to continue...\n";
    std::cin.get();
}


int main() {
    PAGE_SIZE = sysconf(_SC_PAGE_SIZE);

    std::cout << "Page size: " << PAGE_SIZE << " bytes\n";

    // pure virtual address reservation
    wait("experiment 1: mmap(PROT_NONE) reserve address space only");

    size_t reserve_size = 16 * PAGE_SIZE;
    void* region = mmap(
        nullptr,
        reserve_size,
        PROT_NONE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    std::cout << "reserved virtual memory at: " << region << "\n";
    std::cout << "touching it will segfault.\n";

    // Uncomment to crash
    //((char*)region)[0] = 1;

    // experiment 2: commit pages via mprotect
    wait("experiment 2: mprotect make pages readable/writable");

    mprotect(region, 2 * PAGE_SIZE, PROT_READ | PROT_WRITE);
    std::cout << "first 2 pages are now accessible.\n";

    char* p = (char*)region;
    p[0] = 42;
    p[2 * PAGE_SIZE - 1] = 43;

    //this should error out
    //p[2 * PAGE_SIZE] = 44;  

    std::cout << "wrote to first 2 pages.\n";

    // experiment 3 demand paging (physical memory allocation)
    wait("experiment 3: touching pages allocates physical memory");

    for (size_t i = 0; i < 2 * PAGE_SIZE; i += PAGE_SIZE) {
        p[i] = 1;
        std::cout << "touched page at offset " << i << "\n";
    }

    // experiment 4: file backed mmap
    wait("experiment 4: file backed mmap");

    int fd = open("mmap_test.txt", O_CREAT | O_RDWR, 0644);
    const char* text = "Hello from mmap!\n";
    write(fd, text, strlen(text));
    lseek(fd, 0, SEEK_SET);

    void* file_map = mmap(
        nullptr,
        PAGE_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE,
        fd,
        0
    );

    std::cout << "mapped file at: " << file_map << "\n";
    std::cout << "file contents: " << (char*)file_map << "\n";

    ((char*)file_map)[0] = 'h'; // a private copy but never the actual file is overwritten
    std::cout << "modified mapping (copy on write).\n";

    close(fd);

    // experiment 5: MAP_SHARED
    wait("experiment 5: MAP_SHARED (write back to file)");

    fd = open("mmap_test.txt", O_RDWR);
    void* shared_map = mmap(
        nullptr,
        PAGE_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    ((char*)shared_map)[0] = 'B';
    msync(shared_map, PAGE_SIZE, MS_SYNC);

    std::cout << "write back done. check file now.\n";
    close(fd);


    wait("6: munmap");

    munmap(region, reserve_size);
    std::cout << "mapping unmapped.\n";

    // uncomment to crash
    // p[0] = 1;
    return 0;
}
