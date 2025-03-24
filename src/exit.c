#include "../include/minishell.h"

int g_exit_code = 0;

void	set_exit_code(int code)
{
	g_exit_code = code;
}

int	get_exit_code(void)
{
	return g_exit_code;
}
