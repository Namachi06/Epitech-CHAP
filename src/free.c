/*
** EPITECH PROJECT, 2019
** free.c
** File description:
** Free program
*/

#include "../include/client.h"

void free_chap(t_chap **mychap)
{
    if ((*mychap) == NULL)
        return;
    if ((*mychap)->target != NULL)
        free((*mychap)->target);
    if ((*mychap)->password != NULL)
        free((*mychap)->password);
    free(*mychap);
}