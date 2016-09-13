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
# include <unistd.h>

# define FD_MAX 250
# define FD_FREE 0
# define FD_SERVER 1
# define FD_UNAMED_CLIENT 2
# define FD_CLIENT 3

# define READ_MAX 512

# define SEND_SIZE 4096
# define RECEIVE_SIZE 4096

/*
 * structs
 */
typedef struct      s_cmd
{
    int             type;
    char            *first;
    char            *rest;
}                   t_cmd;

typedef struct      s_ring_buf
{
    size_t          size;
    int             flag;
    char            *start;
    char            *end;
    char            *read;
    char            *write;
}                   t_ring_buf;

typedef struct      s_member
{
    int             status;
    char            name[12];
    t_ring_buf      rcv_buf;
    t_ring_buf      snd_buf;
}                   t_member;

typedef struct      s_channel
{
    char            *name;
    int             number;
    //list of users
}                   t_channel;

typedef struct      s_server
{
    int             port;
    int             sock;
    unsigned int    fd_max;
    int             fd_select;
    fd_set          fd_read;
    fd_set          fd_write;
}                   t_server;

typedef void (*t_fpointer) (t_cmd, t_member **, int);

enum                e_buff_type{SEND, RECEIVE};
enum                e_cmd_type{NICK, MSG, QUIT};

/*
 * accept.c
 */
int         init_client(t_member *user);
int         ft_accept(t_server *serv, t_member *user[FD_MAX]);

/*
 * client.c
 */
void        get_client_name(t_cmd cmd, t_member **user, int fd);
int         find_name(t_member **user, char *name);

/*
 * close.c
 */
void        close_client(t_member *user, int id);
void        exit_server(t_server *serv, t_member **user);

/*
 * error.c
 */
void        usage(char *name);
int         r_error(char *error);

/*
 * get_commands.c
 */
void        get_commands(t_server *serv, t_member **user, int fd);

/*
 * main.c
 */
int         get_port(char *number, int *port);
int         init(t_server *serv, t_member **user, int port);

/*
 * read.c
 */
int         ft_read(t_server *serv, t_member **user, int fd);

/*
 * ring_buffer.c
 */
char        get_last_char(t_ring_buf *buf);
int         init_buffer(t_ring_buf *rbuf, int type);
char        *read_buf(t_ring_buf *buf);
int         write_buf(t_ring_buf *buf, char *str, int len);

/*
 * select_loop.c
 */
void         int_handler(int dummy);
void         ft_select(t_server *serv);
void         process_select(t_server *serv, t_member **user);
void         loop(t_server *serv, t_member **user);

/*
 * send.c
 */
void        send_all(t_server *serv, t_member **user, char *str, int fd);
void        send_msg(t_cmd cmd, t_member **user, int fd);

/*
 * strsplit.c
 */
char        **ft_strsplit(char const *s, char c);

/*
 * write.c
 */
void          ft_write(t_ring_buf *buf, int fd);

#endif
