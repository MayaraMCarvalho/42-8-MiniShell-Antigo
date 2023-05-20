#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc && argv)
	{}
	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	shell->envp = envp;
    minishell(shell);
}