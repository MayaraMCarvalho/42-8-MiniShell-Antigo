/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/09/08 20:32:00 by macarval         ###   ########.fr       */
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
	char	*find;
	char	*temp;

	if (shell.content && shell.content[0] == '$')
		return (print_var(shell));
	else
	{
		find = ft_strchr(shell.content, '$');
		if (find == NULL)
			printf("%s", shell.content);
		else
		{
			temp = strchr_rev(shell.content, '$');
			printf("%s", temp);
			free(temp);
			if (!strcmp_mod(find, "$"))
				printf("$");
			else
			{
				shell.content = find;
				print_var(shell);
			}
		}
		return (1);
	}
}

int	print_var(t_shell shell)
{
	t_lst	*node;

	node = find_arg(shell, ++shell.content);
	if (node && node->msg)
	{
		printf("%s", node->msg);
		return (1);
	}
	return (0);
}
