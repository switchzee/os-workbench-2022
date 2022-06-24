#include <assert.h>
#include <unistd.h>
#include "../../utils/fileutils.h"
#include "../../utils/ioutils.h"
#define MAXLEN 100
#define ROOT_NAME "??"
const char *procPath = "/proc";

// get parent pid of the current pid.
const char *getPPid(const char *pid)
{
    assert(isNumber(pid));
    if (strcmp(pid, "0") == 0)
        return "0";
    // make path to this pid file.
    const char *ppath = join(procPath, pid);

    // read its PPid line then extrace PPid.
    const char *line = readStatusLine(ppath, "PPid");
    int len = 0;
    const char **words = split(line, '\t', &len);

    assert(len == 2);
    return words[1];
}

const char *getPidName(const char *pid)
{
    assert(isNumber(pid));
    if (strcmp(pid, "0") == 0)
        return ROOT_NAME;
    const char *line = readStatusLine(join(procPath, pid), "Name");
    int len = 0;
    const char **words = split(line, '\t', &len);

    assert(len == 2);
    return words[1];
}

// print Ps tree, return the blank str
int printPsTreeEnd(const char *pid)
{
    if (strcmp(pid, "0") == 0)
        return 0;

    // print its child.
    int spaceCnt = printPsTreeEnd(getPPid(pid));

    // print it.
    printSpace(spaceCnt);
    printf("|\n");
    printSpace(spaceCnt);
    printf("+---%s\n", getPidName(pid));

    return spaceCnt + 4;
}