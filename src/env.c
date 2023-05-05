/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:46 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 17:14:30 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	env(t_shell shell)
{
	int	i;

	i = -1;
	if (!ft_strncmp(shell.command, "env", ft_strlen(shell.command)))
	{
		if (!is_flag_null(shell))
			return (1);
		while (shell.envp[++i] != NULL)
			printf("%s\n", shell.envp[i]);
		return (1);
	}
	return (0);
}
