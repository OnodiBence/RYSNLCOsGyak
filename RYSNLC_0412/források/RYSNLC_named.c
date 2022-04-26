#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int child;

    mkfifo("Onodi Bence", S_IRUSR | S_IWUSR);
    child = fork();

    if(child > 0) {
        char s[888];
        int fd;

        fd = open("Onodi Bence", O_RDONLY);
        read(fd, s, sizeof(s));
        printf("%s", s);
        close(fd);
        unlink("Onodi Bence");

    } else if(child == 0) {
        int fd = open("Onodi Bence", O_RDONLY);
        write(fd, "OB RYSNLC\n", 12);
        close(fd);
    }
    return 0;
}
