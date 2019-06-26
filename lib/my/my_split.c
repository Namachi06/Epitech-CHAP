/*
** EPITECH PROJECT, 2017
** my_split
** File description:
** 	Split the string with separator
*/

#include "../../include/my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void count_elems(char *tmp, char **last_delim, const char *delim, size_t *count)
{
    while (*tmp) {
        if (delim[0] == *tmp) {
            *last_delim = tmp;
            (*count)++;
        }
        tmp++;
    }
}

void split(char *str, const char *delim, size_t count, char ***result)
{
    char *token = strtok(str, delim);
    size_t i = 0;

    while (token) {
        if (i < count) {
            (*result)[i++] = strdup(token);
            token = strtok(NULL, delim);
        }
    }
    if (i == count - 1)
        (*result)[i] = NULL;
    else
        (*result)[i] = NULL;
}

char **my_split(char *str, const char *separator)
{
    char **result = NULL;
    char *tmp = str;
    char *last_delim = NULL;
    size_t count = 0;
    char *occur = NULL;

    if ((occur = strstr(str, "\r\n")) != NULL)
        strcpy(occur, "\0");
    if (!strlen(str) || !separator || !strcmp(str, separator))
        return NULL;
    count_elems(tmp, &last_delim, separator, &count);
    count += last_delim < (str + strlen(str) - 1);
    if ((result = malloc(sizeof(char *) * ++count)) == NULL)
        return NULL;
    split(str, separator, count, &result);
    return (result);
}
