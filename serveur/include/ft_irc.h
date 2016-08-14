#ifndef FT_IRC_H
# define FT_IRC_H

# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>

# define FD_MAX 250
# define FD_FREE 0
# define FD_SERVER 1
# define FD_CLIENT 3

/*
 * structs
 */

typedef struct      s_server
{
    int             port;
    int             sock;
    int             fd_max;
    int             fd_select;
    fd_set          fd_read;
    fd_set          fd_write;
}                   t_server;

typedef struct      s_member
{
    int             status;
}                   t_member;

/*
 * accept.c
 */
int         ft_accept(t_server *serv, t_member *user);

/*
 * error.c
 */
void        usage(char *name);
int         r_error(char *error);

/*
 * main.c
 */
int         get_port(char *number, int *port);
int         init(t_server *serv, t_member user[FD_MAX], int port);

/*
 * select_loop.c
 */
void         int_handler(int dummy);
void         ft_select(t_server *serv);
void         process_select(t_server *serv, t_member user[FD_MAX]);
void         loop(t_server *serv, t_member user[FD_MAX]);


#endif
