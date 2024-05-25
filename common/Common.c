#include "./Common.h"

int validateString(char *str, int n, int prev)
{
  if (prev < 0)
  {
    return prev;
  }

  for (int i = 0; i < n; ++i)
  {
    char c = str[i];

    if (c == '(')
    {
      ++prev;
    }
    else if (c == ')')
    {
      --prev;

      if (prev < 0)
      {
        return prev;
      }
    }
  }

  return prev;
}

void tryPipe(int *fd)
{
  if (pipe(fd) < 0)
  {
    printf("Pipe failed\n");

    exit(1);
  }
}

int tryOpen(char *name, int mode, int acc)
{
  int res = acc != -1 ? open(name, mode, acc) : open(name, mode);

  if (res < 0)
  {
    printf("Opening file failed\n");

    exit(1);
  }

  return res;
}

void tryClose(int fd)
{
  if (close(fd) < 0)
  {
    printf("Closing failed\n");

    exit(1);
  }
}

int tryFork()
{
  int res = fork();

  if (res < 0)
  {
    printf("Forking failed\n");
  }

  return res;
}

int readMax(int fd, char *buf, int len)
{
  int res = read(fd, buf, len + 1);

  if (res > len)
  {
    printf("Rading failed\n");

    exit(1);
  }

  return res;
}

void readAll(int fd, char *buf, int len)
{
  if (read(fd, buf, len) != len)
  {
    printf("Reading failed\n");

    exit(1);
  }
}

void writeAll(int fd, char *buf, int len)
{
  if (write(fd, buf, len) != len)
  {
    printf("Writing failed\n");

    exit(1);
  }
}
