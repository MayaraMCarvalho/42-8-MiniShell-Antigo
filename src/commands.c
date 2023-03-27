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
	if (exit_shell(shell))
		exit(0);
	else if (echo(shell))
		return (0);
	return (1);
}

// int	pwd(void)
// {
// 	char	*path;
// 	char	buf[256];

// 	path = getcwd(buf, 256);
// 	return (path);
// }

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
