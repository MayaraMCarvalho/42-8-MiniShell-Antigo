/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:10 by macarval          #+#    #+#             */
/*   Updated: 2023/05/20 23:13:38 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Passar norminette

int	c_export(t_shell shell)
{
	if (!strcmp_mod(shell.command, "export"))
	{
		if (!is_flag_null(shell))
			return (1);
		if (shell.content == NULL)
		{
			while (shell.env != NULL)
			{
			/*
			// Colocar em ordem alfabética,
			// printar as variáveis vazias e
			// colocar o valor da variável entre ""
			*/
				if (shell.env->type == 0)
					printf("declare -x %s=\"%s\"\n", shell.env->var, shell.env->msg);
				shell.env = shell.env->next;
			}
		}
		return (1);
	}
	return (0);
}
