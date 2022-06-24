#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stringutils.h"
#include <dirent.h>
#if defined(WIN32)
#define SEP '\\'
#else
#define SEP '/'
#endif
#define MAX_PROC_NUM 200000
#define MAX_DIG 20

const char *join(const char *p1, const char *p2)
{
    int l1 = len(p1), l2 = len(p2);
    int l = l1 + l2 + 1;
    char *joinPath = (char *)malloc(sizeof(char) * l);
    strcpy(joinPath, p1);
    int curl = l1;
    if (joinPath[curl - 1] != SEP && p2[0] != SEP)
        joinPath[curl++] = SEP;
    strcpy(joinPath + curl, p2);
    joinPath[l] = 0;
    return joinPath;
}

const char *readStatusLine(const char *path, const char *keyword)
{
    const char *statPath = join(path, "status");
    FILE *fpStat = fopen(statPath, "r");
    assert(fpStat != NULL);
    char *line = (char *)malloc(sizeof(char) * MAXLEN);
    size_t size = 0, len = MAXLEN;
    while ((size = getline(&line, &len, fpStat)) > 0)
    {
        if (strstr((const char *)line, keyword) != NULL)
        {
            fclose(fpStat);
            return line;
        }
    }
    free(line);
    fclose(fpStat);
    return NULL;
}

const char *readTask(const char *path, const char *fileName)
{
    const char *filePath = join(path, join("task", fileName));
    FILE *fp = fopen(filePath, "r");
    assert(fp != NULL);
    char *line = (char *)malloc(sizeof(char) * MAXLEN);
    size_t size = 0, len = MAXLEN;
    getline(&line, &len, fp);
    return line;
}

const char **getNumSubdirs(const char *path)
{
    char **dirs = (char **)malloc(sizeof(char *) * MAX_PROC_NUM);
    struct dirent *pDirent;
    DIR *pDir;
    pDir = opendir(path);
    int i = 0;
    while ((pDirent = readdir(pDir)) != NULL)
    {
        if (isNumber(pDirent->d_name))
            dirs[i++] = pDirent->d_name;
    }
    dirs[i] = NULL;
    return (const char **)dirs;
}