/*
** EPITECH PROJECT, 2019
** args_handler.c
** File description:
** Handle long arguments
*/

#include "../include/client.h"

void print_usage(void)
{
    fprintf(stderr, "USAGE: ./client"
        "\n\t-t (or --target) followed by the target "
        "of the remote authenticating entity.\n"
        "\t-p (or --port) followed by the port.\n"
        "\t-P (or --password) followed by the password that "
        "allows you to authenticate to the entity\n");
}

int check_args(int c, t_chap **mychap, int *is_args_ok)
{
    switch (c) {
        case 't':
            (*mychap)->target = strdup(optarg);
            (*is_args_ok)++;
            break;
        case 'p':
            (*mychap)->port = atoi(optarg);
            (*is_args_ok)++;
            break;
        case 'P':
            (*mychap)->password = strdup(optarg);
            (*is_args_ok)++;
            break;
        default:
            print_usage();
            return (-1);
    }
    return (0);
}

int handle_args(int argc, char *argv[], t_chap **mychap)
{
    int c;
    opterr = 0;
    int opt_indx = 0;
    int is_args_ok = 0;
    struct option long_opt[] = {
        { "target", required_argument, NULL, 't' },
        { "port", required_argument, NULL, 'p' },
        { "password", required_argument, NULL, 'P' },
        { 0, 0, 0, 0 }
    };

    do {
        c = getopt_long(argc, argv, "t:p:P:", long_opt, &opt_indx);
        if (check_args(c, mychap, &is_args_ok) != 0)
            return (-1);
    } while (c != -1 && is_args_ok != 3);
    if ((*mychap)->port == 0)
        return (fprintf(stderr, "Invalid port\n"), -1);
    return (0);
}