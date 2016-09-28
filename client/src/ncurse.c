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
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(1);
    refresh();
    term->output_win = create_window(LINES - 3, 0, 0, 0);
    scrollok(term->output_win, TRUE);
    term->input_win = create_window(0, 0, LINES - 3, 0);
    scrollok(term->input_win, TRUE);
    box(term->input_win, 0, 0);
    getyx(term->input_win, term->in_y, term->in_x);
    input_win(term, "", 0, NULL);
}

void            print_window(WINDOW *win, t_lst_head *chan_head)
{
    t_lst_elem   *msg;

    msg = ((t_channel *)chan_head->first->content)->msg->first;
    wmove(win, 0, 0);
    while (msg != NULL)
    {
        waddstr(win, msg->content);
        waddch(win, '\n');
        msg = msg->next;
    }
    wrefresh(win);
}

void            input_win(t_term *term, char *str, int pos, t_lst_head *chans)
{
    t_lst_elem      *tmp;
    int             len;

    if (!chans)
        mvwprintw(term->input_win, 0, 0, "channel_name");
    else
    {
        tmp = chans->first;
        len = 0;
        while (tmp != NULL && len < COLS)
        {
            mvwprintw(term->input_win, 0, len, " %s ",
                    ((t_channel *)tmp->content)->name);
            len += 4 + strlen(((t_channel *)tmp->content)->name);
            tmp = tmp->next;
        }
    }
    mvwprintw(term->input_win, 1, 0, "$> %s", str);
    wmove(term->input_win, term->in_y + 1, term->in_x + pos + 3);
    wrefresh(term->input_win);
}
