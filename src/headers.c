/*
** EPITECH PROJECT, 2019
** headers.c
** File description:
** Initialize headers
*/

#include "../include/client.h"

unsigned short checksum(unsigned short *ptr, int nbytes)
{
    register long sum;
    unsigned short oddbyte;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((uint8_t *)&oddbyte) = *(uint8_t *)ptr;
        sum += oddbyte;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ((unsigned short)(~sum));
}

void build_ip(t_headers **headers, t_chap **mychap, char *data, char *buffer)
{
    (*headers)->ip->version = 4;
    (*headers)->ip->ihl = 5;
    (*headers)->ip->tos = 0;
    (*headers)->ip->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) +
        strlen(data);
    (*headers)->ip->id = htonl(54321);
    (*headers)->ip->frag_off = 0;
    (*headers)->ip->ttl = 16;
    (*headers)->ip->protocol = IPPROTO_UDP;
    (*headers)->ip->check = 0;
    (*headers)->ip->saddr = (*mychap)->src_addr.sin_addr.s_addr;
    (*headers)->ip->daddr = (*mychap)->dst_addr.sin_addr.s_addr;
    (*headers)->ip->check = checksum((unsigned short *)buffer,
        (*headers)->ip->tot_len);
}

void build_udp(t_headers **headers, t_chap **mychap, char *data)
{
    (*headers)->udp->source = (*mychap)->src_addr.sin_port;
    (*headers)->udp->dest  = (*mychap)->dst_addr.sin_port;
    (*headers)->udp->len = htons(8 + strlen(data));
    (*headers)->udp->check = 0;
    (*headers)->pshdr.src_addr = (*mychap)->src_addr.sin_addr.s_addr;
    (*headers)->pshdr.dst_addr = (*mychap)->dst_addr.sin_addr.s_addr;
    (*headers)->pshdr.placeholder = 0;
    (*headers)->pshdr.protocol = IPPROTO_UDP;
    (*headers)->pshdr.length = htons(sizeof(struct udphdr) + strlen(data));
}

int init_headers(t_headers **headers, t_chap **mychap, char *data, char *buffer)
{
    char *psbuffer;
    int ps_size;

    *headers = malloc(sizeof(t_headers));
    (*headers)->ip = (struct iphdr *)buffer;
    (*headers)->udp = (struct udphdr *)(buffer + sizeof(struct iphdr));
    build_ip(headers, mychap, data, buffer);
    build_udp(headers, mychap, data);
    ps_size = sizeof(struct s_pseudohdr) + sizeof(struct udphdr) + strlen(data);
    psbuffer = malloc(ps_size);
    memcpy(psbuffer, (char *)&(*headers)->pshdr, sizeof(struct s_pseudohdr));
    memcpy(psbuffer + sizeof(struct s_pseudohdr), (*headers)->udp,
        sizeof(struct udphdr) + strlen(data));
    (*headers)->udp->check = checksum((unsigned short *)psbuffer, ps_size);
    return (0);
}