/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:01:25 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 16:41:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_struct(t_shell shell)
{
	free(shell.line);
	if (shell.command)
		free(shell.command);
	if (shell.flag)
		free(shell.flag);
	if (shell.content)
		free(shell.content);
}

void	free_split(char ***split)
{
	int		i;
	char	**temp;

	i = -1;
	temp = *split;
	while (temp[++i])
		free(temp[i]);
	free(*split);
}

int	clear(t_shell shell)
{
	if (!ft_strncmp(shell.command, "clear", ft_strlen(shell.command)))
	{
		if (!is_flag_null(shell))
			return (1);
		printf("\033[2J\033[1;1H");
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
		if (!is_flag_null(shell))
			return (1);
		control = 1;
		free_struct(shell);
		rl_clear_history();
	}
	return (control);
}
