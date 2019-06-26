/*
** EPITECH PROJECT, 2019
** mychap.c
** File description:
** my CHAP program
*/

#include "../include/client.h"

void send_msg(t_chap **mychap, t_headers *headers, char *buffer)
{
    if (sendto((*mychap)->sockfd, buffer, headers->ip->tot_len, 0,
        (struct sockaddr *)&((*mychap)->dst_addr),
        sizeof((*mychap)->dst_addr)) == -1)
        print_error("sendto");
}

void rcv_msg(t_chap **mychap)
{
    int n;
    socklen_t len = sizeof((*mychap)->dst_addr);
    char msg[MAX_LINE];

    n = recvfrom((*mychap)->sockfd, (char *)msg, MAX_LINE, MSG_WAITALL,
        (struct sockaddr *)&(*mychap)->dst_addr, &len);
    msg[n] = '\0';
    printf("Server: %s\n", msg);
}

int my_chap(t_chap **mychap)
{
    t_headers *headers;
    char buffer[MAX_LINE], *data;

    memset(buffer, 0, MAX_LINE);
    if (init_socket(mychap) != 0)
        return (-1);
    data = (char *)(buffer + sizeof(struct iphdr) + sizeof(struct udphdr));
    strcpy(data, "client ello");
    if (init_headers(&headers, mychap, data, buffer) != 0)
        return (-1);
    send_msg(mychap, headers, buffer);
    // rcv_msg(mychap);
    close((*mychap)->sockfd);
    return (0);
}