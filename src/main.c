/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main programm
*/

#include "../include/client.h"

int init_chap_struct(t_chap **mychap)
{
    if ((*mychap = malloc(sizeof(t_chap))) == NULL)
        return (-1);
    (*mychap)->password = NULL;
    (*mychap)->target = NULL;
    (*mychap)->port = 0;
    (*mychap)->sockfd = 0;
    return (0);
}

int main(int argc, char *argv[])
{
    t_chap *mychap;

    if (init_chap_struct(&mychap) != 0)
        return (84);
    if (handle_args(argc, argv, &mychap) != 0) {
        free_chap(&mychap);
        return (84);
    }
    if (my_chap(&mychap) != 0)
        return (84);
    free_chap(&mychap);
    return (0);
}
