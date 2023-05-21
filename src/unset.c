/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:32 by macarval          #+#    #+#             */
/*   Updated: 2023/05/20 23:02:33 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_unset(t_shell shell)
{
	t_lst	*node;

	if (!strcmp_mod(shell.command, "unset"))
	{
		if (shell.content)
		{
			node = find_var(shell);
			if (is_flag_null(shell) && node != NULL)
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
		return (1);
	}
	return (0);
}

t_lst	*find_var(t_shell shell)
{
	t_lst	*temp;

	temp = shell.env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, shell.content))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	remove_var(t_lst *env)
{
	printf("var: %s, msg: %s\n", env->var, env->msg);
}
