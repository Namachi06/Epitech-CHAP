/*
** EPITECH PROJECT, 2019
** client.h
** File description:
** Client header
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <linux/ip.h>
#include <linux/udp.h>

#define MAX_LINE 4096

struct s_pseudohdr
{
    u_int32_t src_addr;
    u_int32_t dst_addr;
    u_int8_t protocol;
    u_int8_t placeholder;
    uint16_t length;
};

typedef struct s_headers
{
    struct iphdr *ip;
    struct udphdr *udp;
    struct s_pseudohdr pshdr;
} t_headers;

typedef struct s_chap
{
    char *target;
    int port;
    char *password;
    int sockfd;
    struct hostent *host;
    struct sockaddr_in src_addr;
    struct sockaddr_in dst_addr;
} t_chap;

// args_handler.c
int handle_args(int argc, char *argv[], t_chap **mychap);

// mychap.c
int my_chap(t_chap **mychap);

// headers.c
int init_headers(t_headers **headers, t_chap **mychap, char *data,
    char *buffer);

// socket.c
int init_socket(t_chap **mychap);

// free.c
void free_chap(t_chap **mychap);

// error.c
int print_error(const char *error);

#endif /* !CLIENT_H_ */
