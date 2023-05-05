/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:10 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 16:51:06 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	export(t_shell shell)
{
	int	i;

	i = -1;
	if (!ft_strncmp(shell.command, "export", ft_strlen(shell.command)))
	{
		if (!is_flag_null(shell))
			return (1);
		if (shell.content == NULL)
		{
			while (shell.envp[++i] != NULL)
			/*
			// Colocar em ordem alfabética,
			// printar as variáveis vazias e
			// colocar o valor da variável entre ""
			*/
				printf("declare -x %s\n", shell.envp[i]);
		}
		return (1);
	}
	return (0);
}
