#include "../../../includes/minishell.h"

void	throw_error(int	status)
{/*
	if (status == 1)
		ft_putendl_fd("invalid input: ERROR", 2);*/
	if (status == 2)
		ft_putendl_fd("invalid syntax or argument: ERROR", 2);
	/*if (status == 126)
		ft_putendl_fd("invalid execution: ERROR", 2); */
	if (status == 127)
		ft_putendl_fd("command not found: ERROR", 2);/*
	if (status == 128)
		ft_putendl_fd("invalid output argument: ERROR", 2);
	if (status == 255)
		ft_putendl_fd("invalid output status: ERROR", 2); */
}
/*
	NO_ERROR = 0,
	ERROR = 1,
	MISUSE = 2,
	CANT_EXEC = 126,
	NOT_FOUND = 127,
	INVALID_EXIT_ARG = 128,
	FATAL_ERROR_MINUS_N = 128,
	USED_CTRL_C = 130,
	EXIT_STATUS_OUT_RANGE = 255, */
