/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/05/27 17:23:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Passar norminette

int	c_echo(t_shell shell)
{
	t_lst	*node;

	if (!strcmp_mod(shell.command, "echo"))
	{
		if (shell.content && shell.content[0] == '$')
		{
			node = find_arg(shell, ++shell.content);
			if (node)
				printf("%s", node->msg);
		}
		else
			printf("%s", shell.content);
		if (!shell.flag || strcmp_mod(shell.flag, "-n"))
			printf("\n");
		return (1);
	}
	return (0);
}
