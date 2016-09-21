#ifndef CLIENT_H
# define CLIENT_H

# include <arpa/inet.h>
# include <ncurses.h>
# include <netdb.h>
# include <netinet/in.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>

typedef struct  s_client
{
    int         sock;
    int         port;
    fd_set      fd_read;
}               t_client;

/*
 * error.c
 */
int         pr_error(const char *error);

/*
 * init.c
 */
int         init_client(t_client *init, char **args);

/*
 * loop.c
 */
void        int_handler(int dummy);
void        main_loop(t_client *client);

#endif
