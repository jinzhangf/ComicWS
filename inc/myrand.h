#include "mybase.h"


int random(void)
{
        int fd;
        unsigned long seed;

        fd = open("/dev/random", 0);
        if (fd < 0 || read(fd, &seed, sizeof(seed)) < 0) {
                cerr << "failed to generate random num." << endl;
                seed = time(0);
        }

        if (fd >= 0)
                close(fd);

        srand(seed);
        return rand();
}

