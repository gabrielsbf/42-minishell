#include "../../includes/minishell.h"

void    cd_home()
{
    char    *home;

    home = getenv("HOME");
    chdir(home);
}

char    *get_prev_dir(char *cwd)
{
    int i;

    i = 0;
    while (cwd[i] != '\0')
        i++;
    while (cwd[i] != '/' && i != 0)
    {
        cwd[i] = '\0';
        i--;
    }
    printf("%c\n", cwd[i]);
    return (cwd);
}

void    prev_path()
{
    char    *prev;
    char    cwd[4097];

    getcwd(cwd, sizeof(cwd));
    prev = get_prev_dir(cwd);
    chdir(prev);
}

void    cd_manager(char *argument)
{
    if (ft_strncmp(argument, "", 1) == 0)
        cd_home();
    else if (ft_strncmp(argument, "..", 2) == 0)
        prev_path();
}
