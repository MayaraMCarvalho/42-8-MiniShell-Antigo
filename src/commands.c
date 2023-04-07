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
	else if (pwd(shell))
		return (0);
	else if (exit_shell(shell))
		exit(0);
	return (1);
}

int	echo(t_shell shell)
{
	int	isflag;

	isflag = 0;
	if (!ft_strncmp(shell.command, "echo", ft_strlen(shell.command)))
	{
		if (shell.flag && !ft_strncmp(shell.flag, "-n", ft_strlen(shell.flag)))
			isflag = 1;
		printf("%s", shell.content);
		if (isflag == 0)
			printf("\n");
		return (1);
	}
	return (0);
}

int	pwd(t_shell shell)
{
	char	*path;
	char	buf[256];

	if (!ft_strncmp(shell.command, "pwd", ft_strlen(shell.command)))
	{
		path = getcwd(buf, 256);
		printf("%s\n", path);
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
		// free(shell.command);
		// free(shell.flag);
		// free(shell.content);
		rl_clear_history();
	}
	return (control);
}
