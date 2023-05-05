/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:32 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 17:09:13 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	unset(t_shell shell)
{
	int	i;
	int	tam;

	i = -1;
	if (!ft_strncmp(shell.command, "unset", ft_strlen(shell.command)))
	{
		if (!is_flag_null(shell) || !shell.content)
			return (1);
		tam = ft_strlen(shell.content);
		while (shell.envp[++i] != NULL)
		{
			if (!ft_strncmp(shell.envp[i], shell.content, tam))
				break ;
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
