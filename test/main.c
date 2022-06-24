#include "../utils/ioutils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int osBits()
{
    return (int)(sizeof(char *) * 8);
}

int main(int argc, char *argv[])
{
    printf("os is %d bits\n", osBits());
    int opt;
    while ((opt = getopt(argc, argv, "Vp:")) != -1)
    {
        switch (opt)
        {
        case 'V':
            break;
        case 'p':
        {
            printf("%s\n", optarg);
        }
        break;
        }
    }
}
