// the tee command, maybe correct?

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>


int main(int argc, char* argv[]){
    int opt;
    int fd;

    while( (opt = getopt(argc, argv, ":if:a")) != -1){
        if(opt == 'a'){
            fd = open("output.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        if (fd == -1) {
            perror("open");
            return 1;
        }

        for(int i = 1; i < argc; i++){
            write(fd, argv[i], strlen(argv[i]));
            std::cout << argv[i] << std::endl;
        }
        close(fd);
        return 0;
    }

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    for(int i = 1; i < argc; i++){
        write(fd, argv[i], strlen(argv[i]));
        std::cout << argv[i] << std::endl;
    }
    close(fd);
}