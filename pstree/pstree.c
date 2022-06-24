// print process tree with commmand argument -V -p -n
#include <stdio.h>
#include "libs/proc.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt = 0;
    const char **numDirs = getNumSubdirs(procPath);
    PsNode *root = createPsNodeWithNameId("??", "0");
    for (int i = 0; numDirs[i]; ++i)
        insert(root, createPsNodeWithId(numDirs[i]));
    while (1)
    {
        int opt = getopt(argc, argv, "Vp:n:");
        printf("%c\n", opt);
        if (opt == -1 || opt == '?')
            break;
        switch (opt)
        {
        case 'V':
        {
            perror("pstree (PSmisc) UNKNOWN"
                   "Copyright (C) 1993-2019 Werner Almesberger and Craig Small"

                   "PSmisc comes with ABSOLUTELY NO WARRANTY."
                   "This is free software, and you are welcome to redistribute it under"
                   "the terms of the GNU General Public License."
                   "For more information about these matters, see the files named COPYING.");
            break;
        }

        case 'p':
        {
            const char *pid = optarg;
            PsNode *node = searchByPid(root, pid);
            assert(node != NULL);
            printPsTree(node, 0);
            break;
        }

        case 'n':
        {
            const char *pid = optarg;
            int len = 0;
            PsNode **childs = getChilds(root, pid, &len);
            qsort(childs, len, sizeof(PsNode *), PsNodeCmp);
            for (int i = 0; i < len; ++i)
            {
                printf("%s(%s) ", childs[i]->pName, childs[i]->pid);
            }
            printf("\n");
            break;
        }
        }
    }
    return 0;
}