/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 17:14:24 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_command(t_shell shell)
{
	if (echo(shell))
		return (0);
	else if (cd(shell))
		return (0);
	else if (pwd(shell))
		return (0);
	else if (export(shell))
		return (0);
	else if (unset(shell))
		return (0);
	else if (env(shell))
		return (0);
	else if (ls(shell))
		return (0);
	else if (clear(shell))
		return (0);
	else if (exit_shell(shell))
		exit(0);
	return (1);
}
