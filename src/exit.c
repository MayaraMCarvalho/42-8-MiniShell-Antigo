/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:13:37 by macarval          #+#    #+#             */
/*   Updated: 2023/10/13 14:56:21 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_clear(t_shell *shell)
{
	if (!strcmp_mod(shell->command, "clear"))
	{
		update_(*shell);
		if (!is_flag_null(shell))
			return (1);
		printf(CLEAR_SCREEN);
		return (1);
	}
	return (0);
}

int	c_exit(t_shell *shell)
{
	int		control;

	control = 0;
	if (!strcmp_mod(shell->command, "exit"))
	{
		if (!is_flag_null(shell))
			return (1);
		control = 1;
		free_list(shell->env);
		free_shell(*shell);
		rl_clear_history();
	}
	return (control);
}
