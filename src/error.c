/*
** EPITECH PROJECT, 2019
** error.c
** File description:
** Print errors
*/

#include "../include/client.h"

int print_error(const char *error)
{
    fprintf(stderr, "%s: ", error);
    fprintf(stderr, "%s\n", strerror(errno));
    return (-1);
}