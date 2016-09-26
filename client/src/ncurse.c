#include "client.h"

static WINDOW   *create_window(int x, int y, int line, int cols)
{
    WINDOW  *win;

    win = newwin(x, y, line, cols);
    wrefresh(win);
    return (win);
}

void            init_ncurse(t_term *term)
{
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(1);
    refresh();
    term->output_win = create_window(LINES - 3, 0, 0, 0);
    term->input_win = create_window(0, 0, LINES - 3, 0);
    box(term->input_win, 0 , 0);
    getyx(term->input_win, term->in_y, term->in_x);
    wrefresh(term->input_win);
}

void            print_window(WINDOW *win, t_lst_head *chan_head)
{
    t_lst_elem   *msg;

    msg = ((t_channel *)chan_head->first->content)->msg->first;
    while (msg != NULL)
    {
        wprintw(win, "%s", msg->content);
        msg = msg->next;
    }
    wrefresh(win);
}
