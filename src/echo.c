/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/09/24 20:55:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_echo(t_shell shell)
{
	if (!strcmp_mod(shell.command, "echo"))
	{
		if (strcmp_mod(shell.content, "$_"))
			update_(shell);
		if (!strcmp_mod(shell.content, "$?"))
			printf("%i", shell.exit_code);
		else
			apart_args(shell, ' ', print_echo);
		if (!shell.flag || verify_flags(shell.flag, "-n"))
			printf("\n");
		return (1);
	}
	return (0);
}

int	print_echo(t_shell shell)
{
	printf("%s", shell.content);
	return (1);
}
