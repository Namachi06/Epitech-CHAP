/*
** EPITECH PROJECT, 2019
** socket.c
** File description:
** Socket
*/

#include "../include/client.h"

int set_addr(t_chap **mychap)
{
    (*mychap)->src_addr.sin_family = AF_INET;
    (*mychap)->src_addr.sin_port = htons(80);
    inet_aton("127.0.0.1", &(*mychap)->src_addr.sin_addr);
    (*mychap)->dst_addr.sin_family = AF_INET;
    (*mychap)->dst_addr.sin_port = htons((*mychap)->port);
    (*mychap)->dst_addr.sin_addr =
        *((struct in_addr *)(*mychap)->host->h_addr_list[0]);
    return (0);
}

int init_socket(t_chap **mychap)
{
    int opt = 1;

    (*mychap)->host = (struct hostent *)gethostbyname((*mychap)->target);
    if ((*mychap)->host == NULL)
        return (fprintf(stderr, "No such hostname: \'%s\'\n",
            (*mychap)->target), -1);
    if (((*mychap)->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
        return print_error("socket");
    if (set_addr(mychap))
        return (-1);
    if (setsockopt((*mychap)->sockfd, IPPROTO_IP, IP_HDRINCL, &opt,
        sizeof(opt)) == -1)
        return print_error("setsockopt");
    return (0);
}