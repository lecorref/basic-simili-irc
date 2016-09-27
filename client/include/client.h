#ifndef CLIENT_H
# define CLIENT_H

# include <arpa/inet.h>
# include <ctype.h>
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
# include "linked_list.h"

# define BUFF 150
# define READ_MAX 1024

typedef struct  s_channel
{
    char        *name;
    t_lst_head  *msg;
}               t_channel;

typedef struct  s_client
{
    int         sock;
    int         port;
    fd_set      fd_read;
    fd_set      fd_write;
}               t_client;

typedef struct  s_str_in
{
    int         c;
    int         size;
    int         pos;
    char        str[BUFF];
}               t_str_in;

typedef struct  s_term
{
    int         in_x;
    int         in_y;
    WINDOW      *input_win;
    WINDOW      *output_win;
}               t_term;

/*
 * channel.c
 */
int         cmp_chan(void *chan, void *str);
void        right_chan(t_lst_head *chan, t_term *term);
void        left_chan(t_lst_head *chan, t_term *term);

/*
 * commands.c
 */
void        get_command(t_str_in *to_send, t_client *client, t_lst_head *chan);

/*
 * error.c
 */
int         pr_error(const char *error);

/*
 * init.c
 */
int         init_client(t_client *init, char **args);

/*
 * input.c
 */
void        get_input(t_str_in *input, t_term *term,
                        t_client *client, t_lst_head *chan);

/*
 * loop.c
 */
void        int_handler(int dummy);
void        main_loop(t_client *client, t_lst_head *chan);

/*
 * message.c
 */
int         get_message(t_term *term, t_client *client,
                            t_lst_head *chan, t_str_in input);

/*
 * ncurses.c
 */
void        init_ncurse(t_term *term);
void        print_window(WINDOW *win, t_lst_head *chan);
void        input_win(t_term *term, char *str, int pos, t_lst_head *chans);

/*
 * strjoin.c
 */
char        *ft_strjoin(char const *s1, char const *s2);

/*
 * strsplit.c
 */
char        **ft_strsplit(char const *s, char c);
void        free_tab(char **tab);

#endif
