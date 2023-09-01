/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/09/01 20:44:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	make_shell(t_shell *shell)
{
	char	**split;

	split = ft_split(shell->line, ' ');
	if (!ft_strchr(split[0], '='))
	{
		shell->command = ft_strdup(split[0]);
		put_split(shell, split);
	}
	else
	{
		shell->command = ft_strdup(shell->line);
		shell->content = NULL;
	}
	free_split(&split);
}

void	put_split(t_shell *shell, char **split)
{
	int		tam_command;

	tam_command = ft_strlen(shell->command);
	if (split[1])
	{
		if (split[1][0] == '-'
			&& (strcmp_mod(shell->command, "echo")
			|| (!strcmp_mod(shell->command, "echo")
			&& !verify_flags(split[1] + 1, "n"))))
			shell->flag = ft_strdup(split[1]);
		else
			shell->content = ft_substr(shell->line, tam_command + 1,
					ft_strlen(shell->line));
		if (!shell->content && split[2])
		{
			if (shell->content)
				free(shell->content);
			if (shell->flag)
				shell->content = ft_substr(shell->line, tam_command
						+ ft_strlen(shell->flag) + 2, ft_strlen(shell->line));
			else
				shell->content = ft_substr(shell->line, tam_command + 1,
						ft_strlen(shell->line));
		}
	}
}
