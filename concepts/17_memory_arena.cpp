// allocate a large block of memory upfront. whenever memory needed, move the pointer forward, at the end, free the entire arena.


#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

size_t PAGE_SIZE = sysconf(_SC_PAGE_SIZE);

struct Arena{
    char* base_ptr; // staring point
    size_t reserved_size; // reserved size
    size_t commited_size; // how much of reserved space is taken
    size_t current_offset; // bump pointer
};

Arena* createArena(size_t reserve_size){
    Arena* arena = new Arena();

    //std::cout << arena << std::endl;
    reserve_size = (reserve_size + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE; // round reserve_size up to the next multiple of PAGE_SIZE

    void* block = mmap(NULL, reserve_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(block == MAP_FAILED){
        delete arena;
        return nullptr;
    }

    arena->base_ptr = (char*)block;
    arena->reserved_size = reserve_size;
    arena->commited_size = 0;
    arena->current_offset = 0;
    return arena;
}

void* arenaAlloc(Arena* arena, size_t size){
    if(!arena || size == 0){
        return nullptr;
    }

    size_t new_offset = arena->current_offset + size;

    if(new_offset > arena->reserved_size){
        return nullptr; // cannot exceed reserved size
    };

    if(new_offset > arena->commited_size){
        size_t new_commit_target = (new_offset + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE;

        //clamp so it doesnt exceed the reserved size
        if(new_commit_target > arena->reserved_size){
            new_commit_target = arena->reserved_size;
        }

        size_t size_to_commit = new_commit_target - arena->commited_size;
        void* commit_start_addr = arena->base_ptr + arena->commited_size;

        if (mprotect(commit_start_addr, size_to_commit, PROT_READ | PROT_WRITE) != 0) {
            return nullptr;
        }

        arena->commited_size = new_commit_target;
    }

    void* memory = arena->base_ptr + arena->current_offset;
    arena->current_offset = new_offset;
    return memory;
}

void arenaReset(Arena* arena){
    arena->current_offset = 0;
}

void arenaRelease(Arena* arena) {
    munmap(arena->base_ptr, arena->reserved_size);
    delete arena;
}

void printArenaState(Arena* arena, const char* label = "") {
    std::cout << "\n--- arena state";
    if (label[0] != '\0') {
        std::cout << " (" << label << ")";
    }
    std::cout << " ---\n";
    std::cout << "base Pointer:    " << (void*)arena->base_ptr << "\n";
    std::cout << "reserved Size:   " << arena->reserved_size << " bytes (" 
              << arena->reserved_size / PAGE_SIZE << " pages)\n";
    std::cout << "commited Size:  " << arena->commited_size << " bytes (" 
              << arena->commited_size / PAGE_SIZE << " pages)\n";
    std::cout << "current offset:  " << arena->current_offset << " bytes\n";
    std::cout << "used %:          " << (arena->current_offset * 100.0 / arena->reserved_size) << "%\n";
    std::cout << "committed %:     " << (arena->commited_size * 100.0 / arena->reserved_size) << "%\n";
    std::cout << "available:       " << (arena->reserved_size - arena->current_offset) << " bytes\n";
}

void test_allocations(){
    Arena* arena = createArena(PAGE_SIZE * 4);
    printArenaState(arena, "Initial");

    void* ptr1 = arenaAlloc(arena, 100);
    std::cout << "\nallocated 100 bytes at: " << ptr1 << "\n";
    printArenaState(arena, "after 100 bytes");

    void* ptr2 = arenaAlloc(arena, 500);
    std::cout << "\nallocated 500 bytes at: " << ptr2 << "\n";
    printArenaState(arena, "after 500 bytes");

    void* ptr3 = arenaAlloc(arena, 8000);
    std::cout << "\nallocated 8000 bytes at: " << ptr3 << "\n";
    printArenaState(arena, "after 8000 bytes");

    arenaRelease(arena);
}


int main(){
    test_allocations();
}
