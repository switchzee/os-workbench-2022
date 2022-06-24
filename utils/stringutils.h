#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXLEN 100
int len(const char *p1)
{
    int l = 0;
    for (; p1[l] && l < MAXLEN; l++)
        ;
    return l == MAXLEN ? 0 : l;
}

int count(const char *str, const char sep)
{
    int cnt = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == sep)
            cnt++;
    }
    return cnt;
}

int isNumber(const char *str)
{
    for (; *str; str++)
        if (isdigit(*str) == 0)
            return 0;
    return 1;
}

int getNumber(const char *str)
{
    int num = 0;
    for (; *str; str++)
        if (isdigit(*str))
        {
            for (; *str && isdigit(*str); str++)
            {
                num *= 10;
                num += *str - '0';
            }
            return num;
        }
    return -1;
}

const char **split(const char *line, const char sep, int *len)
{
    *len = count(line, sep) + 1;
    int cnt = 0, i = 0, j = 0;
    char **words = (char **)malloc(sizeof(char *) * (*len));
    for (i = 0; line[i] && line[i] != '\n'; ++i)
    {
        if (line[i] == sep)
        {
            words[j] = (char *)malloc(sizeof(char) * (cnt + 1));
            memcpy(words[j], line + (i - cnt), sizeof(char) * cnt);
            words[j++][cnt] = 0;
            cnt = 0;
        }
        else
            cnt++;
    }
    if (cnt > 0)
    {
        words[j] = (char *)malloc(sizeof(char) * (cnt + 1));
        memcpy(words[j], line + (i - cnt), sizeof(char) * cnt);
        words[j++][cnt] = 0;
    }
    return (const char **)words;
}