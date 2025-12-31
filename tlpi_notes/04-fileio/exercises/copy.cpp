#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main() {
    int src_fd = open("output.txt", O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        return 1;
    }

    int dst_fd = open("final.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("open dest");
        close(src_fd);
        return 1;
    }

    char buffer[4096];
    int bytes_read;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        int bytes_written = 0;
        while (bytes_written < bytes_read) {
            int n = write(
                dst_fd,
                buffer + bytes_written,
                bytes_read - bytes_written
            );
            if (n == -1) {
                perror("write");
                close(src_fd);
                close(dst_fd);
                return 1;
            }
            bytes_written += n;
        }
    }

    close(src_fd);
    close(dst_fd);
    return 0;
}
