#include <sys/stat.h>

#include "../common/Common.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Invalid input\n");

    exit(1);
  }

  char name1[] = "OS_IHW1_5.fifo";
  char name2[] = "OS_IHW1_5.fifo";

  mknod(name1, S_IFIFO | 0666, 0);

  int pid = tryFork();

  if (pid > 0)
  {
    char buf[BUFFER_SIZE + 1];

    int fd = tryOpen(name1, O_WRONLY, -1);
    int readFd = tryOpen(argv[1], O_RDONLY, -1);
    int size = readMax(readFd, buf, BUFFER_SIZE);

    writeAll(fd, buf, size);
    tryClose(fd);
    tryClose(readFd);

    return 0;
  }

  mknod(name2, S_IFIFO | 0666, 0);

  pid = tryFork();

  if (pid > 0)
  {
    char sres[2];
    char buf[BUFFER_SIZE];

    int readFd = tryOpen(name1, O_RDONLY, -1);
    int size = read(readFd, buf, BUFFER_SIZE);
    int res = validateString(buf, size, 0) == 0;
    size = sprintf(sres, "%d", res);
    int fd = tryOpen(name2, O_WRONLY, -1);

    writeAll(fd, sres, size);
    tryClose(readFd);
    tryClose(fd);

    return 0;
  }

  char buf[1];

  int fd = tryOpen(name2, O_RDONLY, -1);

  readAll(fd, buf, 1);

  int writeFd = tryOpen(argv[2], O_WRONLY | O_CREAT, 0666);

  writeAll(writeFd, buf, 1);
  tryClose(writeFd);
  tryClose(fd);
}
