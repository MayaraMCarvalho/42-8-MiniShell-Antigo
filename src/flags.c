/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:49:16 by macarval          #+#    #+#             */
/*   Updated: 2023/05/20 23:13:06 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	verify_flags(t_shell shell, char *pattern)
{
	int		i;
	char	letter;

	i = 0;
	letter = '\0';
	if (shell.flag != NULL)
	{
		while (shell.flag[++i] && letter == '\0')
		{
			if (!ft_strchr(pattern, shell.flag[i]))
				letter = shell.flag[i];
		}
	}
	return (letter);
}

int	is_flag_null(t_shell shell)
{
	char	letter;

	letter = verify_flags(shell, NULL);
	if (letter != '\0')
	{
		if (!strcmp_mod(shell.command, "env")
			|| !strcmp_mod(shell.command, "clear"))
			printf("%s: invalid option -- '%c'\n", shell.command, letter);
		else
			printf("bash: %s: -%c: invalid option\n", shell.command, letter);
		return (0);
	}
	return (1);
}
