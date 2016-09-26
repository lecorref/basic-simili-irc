#include "client.h"

char        *ft_strjoin(char const *s1, char const *s2)
{
    size_t  total_len;
    char    *join;

    if (!s1 && s2)
        return (strdup(s2));
    if (!s2 && s1)
        return (strdup(s1));
    if (!s1 && !s2)
        return (strdup(""));
    total_len = strlen(s1) + strlen(s2);
    if (!(join = malloc(sizeof(char) * total_len + 1)))
        return (strdup(""));
    join = strcpy(join, s1);
    join = strcat(join, s2);
    return (join);
}
