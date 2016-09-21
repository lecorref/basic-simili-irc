#include "client.h"

int         main(int ac, char **av)
{
    t_client    init;

    bzero(&init, sizeof(t_client));
    if (ac > 3)
        ;//print usage and return
    if (ac > 1)
    {
        if (init_client(&init, av + 1))
            return (1);
    }
    main_loop(&init);
}
