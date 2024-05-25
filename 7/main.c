#include <sys/stat.h>

#include "../common/Common.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Invalid input\n");

    exit(1);
  }

  char name1[] = "OS_IHW1_7.fifo";
  char name2[] = "OS_IHW1_7.fifo";

  mknod(name1, S_IFIFO | 0666, 0);
  mknod(name2, S_IFIFO | 0666, 0);

  int pid = tryFork();

  if (pid > 0)
  {
    char buf[BUFFER_SIZE + 1];
    char sres[1];

    int fd = tryOpen(name1, O_WRONLY, -1);

    int readFd = tryOpen(argv[1], O_RDONLY, -1);
    int size = readMax(readFd, buf, BUFFER_SIZE);

    tryClose(readFd);
    writeAll(fd, buf, size);
    tryClose(fd);

    int fifor = tryOpen(name2, O_RDONLY, -1);

    readAll(fifor, sres, 1);

    int writeFd = tryOpen(argv[2], O_WRONLY | O_CREAT, 0666);

    writeAll(writeFd, sres, 1);
    tryClose(writeFd);
    tryClose(fifor);
  }
  else
  {
    char buf[BUFFER_SIZE];
    char sres[2];

    int fifor = tryOpen(name1, O_RDONLY, -1);
    int size = read(fifor, buf, BUFFER_SIZE);
    int isValid = validateString(buf, size, 0) == 0;
    size = sprintf(sres, "%d", isValid);
    int fd = tryOpen(name2, O_WRONLY, -1);

    writeAll(fd, sres, size);
    tryClose(fifor);
    tryClose(fd);
  }

  return 0;
}
