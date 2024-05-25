#include <sys/stat.h>

#include "../common/Common.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid input\n");

        exit(1);
    }

    char sres[1];
    char buf[BUFFER_SIZE + 1];
    char name1[] = "OS_IHW1_8.fifo";
    char name2[] = "OS_IHW1_8.fifo";

    mknod(name1, S_IFIFO | 0666, 0);
    mknod(name2, S_IFIFO | 0666, 0);

    int fifow = tryOpen(name1, O_WRONLY, -1);
    int readFd = tryOpen(argv[1], O_RDONLY, -1);
    int size = readMax(readFd, buf, BUFFER_SIZE);

    tryClose(readFd);
    writeAll(fifow, buf, size);
    tryClose(fifow);

    int fifor = tryOpen(name2, O_RDONLY, -1);

    readAll(fifor, sres, 1);

    int writeFd = tryOpen(argv[2], O_WRONLY | O_CREAT, 0666);

    writeAll(writeFd, sres, 1);
    tryClose(writeFd);
    tryClose(fifor);

    return 0;
}