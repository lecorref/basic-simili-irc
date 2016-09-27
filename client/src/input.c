#include "client.h"

static void add_char(t_str_in *input, char c)
{
    int     pos;

    pos = input->pos;
    if (input->size < BUFF - 1)
    {
        memmove(input->str + pos + 1, input->str + pos, input->size - pos);
        input->str[input->pos++] = c;
        input->size++;
    }
    else
        beep();
}

static void move_cursor(t_str_in *input, int dir)
{
    if ((input->pos * dir) < (dir == 1 ? input->size : 0))
        input->pos += dir;
    else
        beep();
}

static void backspace(t_str_in *input)
{
    int     pos;

    pos = input->pos;
    if (pos > 0)
    {
        memmove(input->str + pos - 1, input->str + pos, input->size - pos);
        input->pos--;
        input->size--;
    }
    else
        beep();
}

static void delete(t_str_in *input)
{
    int     pos;

    pos = input->pos;
    if (pos < input->size)
    {
        memmove(input->str + pos, input->str + pos + 1, input->size - pos - 1);
        input->size--;
    }
    else
        beep();
}

void        get_input(t_str_in *input, t_term *term,
                        t_client *client, t_lst_head *chan)
{
    if (input->c == KEY_ENTER || input->c == '\n' || input->c == '\r')
    {
        get_command(input, client, chan);
        wclear(term->input_win);
        box(term->input_win, 0 , 0);
    }
    else if (isprint(input->c))
        add_char(input, input->c);
    else if (input->c == KEY_LEFT)
        move_cursor(input, -1);
    else if (input->c == KEY_RIGHT)
        move_cursor(input, 1);
    else if (input->c == KEY_BACKSPACE)
        backspace(input);
    else if (input->c == KEY_DC)
        delete(input);
    else if (input->c == KEY_PPAGE)
        right_chan(chan, term);
    else if (input->c == KEY_NPAGE)
        left_chan(chan, term);
    else
        beep();
    input->str[input->size] = ' ';
}
