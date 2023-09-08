/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/09/08 20:54:19 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	make_shell(t_shell *shell)
{
	char	**token;

	token = tokenization(shell);
	/* retirar */
	int i = -1;
	while (token[++i])
		printf("token[%i]: %s\n", i, token[i]);
	printf("\n");
	/**/// Fazer o parsing correto;
	if (!ft_strchr(token[0], '='))
	{
		shell->command = ft_strdup(token[0]);
		put_token(shell, token);
	}
	else
	{
		shell->command = ft_strdup(shell->line);
		shell->content = NULL;
	}
	free_array(&token);
}

void	put_token(t_shell *shell, char **token)
{
	int		tam_command;

	tam_command = ft_strlen(shell->command);
	if (token[1])
	{
		if (token[1][0] == '-'
			&& (strcmp_mod(shell->command, "echo")
			|| (!strcmp_mod(shell->command, "echo")
			&& !verify_flags(token[1] + 1, "n"))))
			shell->flag = ft_strdup(token[1]);
		else
			shell->content = ft_substr(shell->line, tam_command + 1,
					ft_strlen(shell->line));
		if (!shell->content && token[2])
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
