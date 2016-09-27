#include "client.h"

int         usage(void)
{
    printf("./client [machine [port]]\n");
    return (1);
}

int         main(int ac, char **av)
{
    t_client    init;
    t_lst_head  chan;

    bzero(&chan, sizeof(chan));
    bzero(&init, sizeof(t_client));
    if (ac > 3)
        return (usage());
    if (ac > 1)
    {
        if (init_client(&init, av + 1))
            return (pr_error("Cannot etablish connection with the server"));
    }
    main_loop(&init, &chan);
}
