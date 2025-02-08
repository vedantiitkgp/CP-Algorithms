
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    const char* pathname = "example.txt";
    int flags = O_RDONLY;
    mode_t mode = 0644;

    // Parameters Directly passed to the the System call
    int fd = open(pathname, flags, mode);

    //Parameters the adress of the block
    //int params[3];
    //params[0] = (int)pathname;
    //params[1] = flags;
    //params[2] = mode;

    //int fd = syscall(SYS_open,params);

    // in function call open(), we passed the parameters pathanme,flags,mode to the kernal directly

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // File operations here...

    close(fd);
    return 0;
}