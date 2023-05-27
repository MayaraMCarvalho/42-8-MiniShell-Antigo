/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:32 by macarval          #+#    #+#             */
/*   Updated: 2023/05/27 17:32:01 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_unset(t_shell shell)
{
	if (!strcmp_mod(shell.command, "unset"))
	{
		apart_args(shell, ' ', exe_unset);
		return (1);
	}
	return (0);
}

void	exe_unset(t_shell shell)
{
	t_lst	*node;

	if (shell.content)
	{
		node = find_arg(shell, shell.content);
		if (is_flag_null(shell) && node != NULL && node->type != ENVP)
		{
			if (shell.env == node)
				shell.env = node->next;
			else
				node->prev->next = node->next;
			if (node->next != NULL)
				node->next->prev = node->prev;
			free(node->var);
			free(node->msg);
			free(node);
		}
	}
}
