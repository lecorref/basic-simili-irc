#include "client.h"

static WINDOW   *create_window(int x, int y, int line, int cols)
{
    WINDOW  *win;

    win = newwin(x, y, line, cols);
    box(win, 0 , 0);
    wrefresh(win);
    return (win);
}

void            init_ncurse(t_term *term)
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(1);
    refresh();
    term->output_win = create_window(LINES - 3, 0, 0, 0);
    term->input_win = create_window(0, 0, LINES - 3, 0);
    getyx(term->input_win, term->in_y, term->in_x);
}
