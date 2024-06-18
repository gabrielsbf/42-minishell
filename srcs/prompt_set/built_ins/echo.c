#include "../../../includes/minishell.h"

void    echo(char *argv[])
{
    int i;
    int trailing;
    
    // printf("in echo, arg 0 is : %s\n", argv[0]);
    trailing = 0;
    i = 1;
    if (ft_strncmp(argv[1], "-n", 3) == 0)
        i++;
    else
        trailing = 1;
    while (argv[i] != NULL)
    {
        printf("%s", argv[i]);
        if (argv[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (trailing == 1)
        printf("\n");
}
