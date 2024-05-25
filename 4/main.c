#include "../common/Common.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Invalid input\n");

    exit(1);
  }

  // 1 process

  int pd1[2];
  tryPipe(pd1);

  int pid = tryFork();

  if (pid > 0)
  {
    tryClose(pd1[0]);

    char buf[BUFFER_SIZE + 1];
    int readFd = tryOpen(argv[1], O_RDONLY, -1);
    int size = readMax(readFd, buf, BUFFER_SIZE);

    writeAll(pd1[1], buf, size);
    tryClose(pd1[1]);
    tryClose(readFd);

    return 0;
  }

  tryClose(pd1[1]);

  // -----------------------
  // 2 process

  int pd2[2];
  tryPipe(pd2);

  pid = tryFork();

  if (pid > 0)
  {
    tryClose(pd2[0]);

    char buf[BUFFER_SIZE];
    char sres[2];

    int size = read(pd1[0], buf, BUFFER_SIZE);
    int isValid = validateString(buf, size, 0) == 0;
    size = sprintf(sres, "%d", isValid);

    writeAll(pd2[1], sres, size);
    tryClose(pd2[1]);

    return 0;
  }

  // -----------------------
  // 3 process

  tryClose(pd2[1]);

  char buf[1];

  readAll(pd2[0], buf, 1);
  tryClose(pd2[0]);

  int writeFd = tryOpen(argv[2], O_WRONLY | O_CREAT, 0666);

  writeAll(writeFd, buf, 1);
  tryClose(writeFd);

  return 0;
}
