/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/03/28 00:46:14 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_command(t_shell shell)
{
	if (echo(shell))
		return (0);
	else if (cd(shell))
		return (0);
	else if (pwd(shell))
		return (0);
	else if (export(shell))
		return (0);
	else if (unset(shell))
		return (0);
	else if (env(shell))
		return (0);
	else if (exit_shell(shell))
		exit(0);
	return (1);
}

int	cd(t_shell shell)
{
	if (!ft_strncmp(shell.command, "cd", ft_strlen(shell.command)))
	{
		if (chdir(shell.content) != 0)
    		printf("bash: cd: %s: No such file or directory\n", shell.content);
		return (1);
	}
	return (0);
}

int	pwd(t_shell shell)
{
	char	buf[256];

	if (!ft_strncmp(shell.command, "pwd", ft_strlen(shell.command)))
	{
		printf("%s\n", getcwd(buf, 256));
		return (1);
	}
	return (0);
}

int	export(t_shell shell)
{
	int	i;

	i = -1;
	if (!ft_strncmp(shell.command, "export", ft_strlen(shell.command)))
	{
		if (shell.content == NULL)
		{
			while (shell.envp[++i] != NULL)
			// Colocar em ordem alfabética,
			// printar as variáveis vazia e
			// colocar o valor da variável entre ""
				printf("declare -x %s\n", shell.envp[i]);
		}
		return (1);
	}
	return (0);
}

int	unset(t_shell shell)
{
	int	i;
	int	tam;

	i = -1;
	if (!ft_strncmp(shell.command, "unset", ft_strlen(shell.command)))
		{
			tam = ft_strlen(shell.content);
			while (shell.envp[++i] != NULL)
			{
				if (!ft_strncmp(shell.envp[i], shell.content, tam))
					break;
			}
			if (shell.envp[i] && shell.envp[i][tam] == '=')
			{
				while (shell.envp[i] != NULL)
				{
					shell.envp[i] = shell.envp[i + 1];
					i++;
				}
			}
			return (1);
		}
	return (0);

}

int	env(t_shell shell)
{
	int	i;

	i = -1;
	if (!ft_strncmp(shell.command, "env", ft_strlen(shell.command)))
	{
		while (shell.envp[++i] != NULL)
			printf("%s\n", shell.envp[i]);
		return (1);
	}
	return (0);

}

int	exit_shell(t_shell shell)
{
	int		control;

	control = 0;
	if (!ft_strncmp(shell.command, "exit", ft_strlen(shell.command)))
	{
		control = 1;
		free(shell.command);
		free(shell.flag);
		free(shell.content);
		rl_clear_history();
	}
	return (control);
}
