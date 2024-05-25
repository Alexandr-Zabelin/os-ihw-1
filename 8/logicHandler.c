#include <sys/stat.h>

#include "../common/Common.h"

int main()
{
    char sres[2];
    char buf[BUFFER_SIZE];
    char name1[] = "OS_IHW1_8.fifo";
    char name2[] = "OS_IHW1_8.fifo";

    int fifor = tryOpen(name1, O_RDONLY, -1);

    int size = read(fifor, buf, BUFFER_SIZE);
    int isValid = validateString(buf, size, 0) == 0;
    size = sprintf(sres, "%d", isValid);

    int fifow = tryOpen(name2, O_WRONLY, -1);

    writeAll(fifow, sres, size);
    tryClose(fifor);
    tryClose(fifow);

    return 0;
}
