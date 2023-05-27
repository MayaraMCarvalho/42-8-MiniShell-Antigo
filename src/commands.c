/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:26 by macarval          #+#    #+#             */
/*   Updated: 2023/05/27 17:31:29 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_command(t_shell shell)
{
	if (c_echo(shell)) //
		return (0);
	else if (c_cd(shell))
		return (0);
	else if (c_pwd(shell))
		return (0);
	else if (c_export(shell)) //
		return (0);
	else if (c_unset(shell)) //
		return (0);
	else if (c_env(shell))
		return (0);
	else if (c_clear(shell))
		return (0);
	else if (c_exit(shell))
		exit(0);
	// else if (c_local(shell))
	// 	return(0);
	return (1);
}

// int	c_local(t_shell shell)
// {
// 	return (0);
// }
