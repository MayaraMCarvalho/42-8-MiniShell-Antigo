/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/06/03 12:17:21 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	make_shell(t_shell *shell, char *line)
{
	char	**split;
	int		tam_command;

	inicialize(shell);
	split = ft_split(line, ' ');
	if (!ft_strchr(split[0], '='))
	{
		shell->command = ft_strdup(split[0]);
		tam_command = ft_strlen(shell->command);
		if (split[1])
		{
			if ((split[1][0] == '-'
				&& strcmp_mod(shell->command, "echo"))
				|| (!strcmp_mod(shell->command, "echo")
				&& !strcmp_mod(split[1], "-n")))
				shell->flag = ft_strdup(split[1]);
			else
				shell->content = ft_substr(line, tam_command + 1, ft_strlen(line));
			if (!shell->content && split[2])
			{
				if (shell->content)
					free(shell->content);
				if (shell->flag)
					shell->content = ft_substr(line, tam_command
							+ ft_strlen(shell->flag) + 2, ft_strlen(line));
				else
					shell->content = ft_substr(line, tam_command + 1,
							ft_strlen(line));
			}
		}

	}
	else
	{
		shell->command = ft_strdup(line);
		shell->content = NULL;

	}
	free_split(&split);
	free(line);
}
// muitas linhas
// ajustar para receber parametros.
