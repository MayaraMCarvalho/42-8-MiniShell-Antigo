/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:02:28 by macarval          #+#    #+#             */
/*   Updated: 2023/02/24 14:06:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(void)
{
	t_shell	shell;

	while (1)
	{
		shell.line = readline("minishell>>$ ");
		if (shell.line[0])
		{
			add_history (shell.line);
			shell = make_shell(shell.line);
			if (is_command(shell))
				printf("bash: %s: command not found\n", shell.command);
			free(shell.line);
		}
	}
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	size_split(char **split)
{
	int	i;

	i = 0;
	while (split[++i])
		i++;
	return (i);
}

