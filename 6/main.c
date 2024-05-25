#include <sys/stat.h>

#include "../common/Common.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Invalid input\n");

    exit(1);
  }

  int fd1[2];
  int fd2[2];

  tryPipe(fd1);
  tryPipe(fd2);

  int pid = tryFork();

  if (pid > 0)
  {
    char buf[BUFFER_SIZE + 1];
    char sres[1];

    tryClose(fd1[0]);
    tryClose(fd2[1]);

    int readFd = tryOpen(argv[1], O_RDONLY, -1);
    int size = readMax(readFd, buf, BUFFER_SIZE);

    tryClose(readFd);
    writeAll(fd1[1], buf, size);
    tryClose(fd1[1]);
    readAll(fd2[0], sres, 1);

    int writeFd = tryOpen(argv[2], O_WRONLY | O_CREAT, 0666);

    writeAll(writeFd, sres, 1);
    tryClose(writeFd);
    tryClose(fd2[0]);
  }
  else
  {
    char buf[BUFFER_SIZE];
    char sres[2];

    tryClose(fd1[1]);
    tryClose(fd2[0]);

    int size = read(fd1[0], buf, BUFFER_SIZE);

    tryClose(fd1[0]);

    int isValid = validateString(buf, size, 0) == 0;
    size = sprintf(sres, "%d", isValid);

    writeAll(fd2[1], sres, size);
    tryClose(fd2[1]);
  }

  return 0;
}