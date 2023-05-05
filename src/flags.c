/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:49:16 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 16:53:09 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	verify_flags(t_shell shell, char *pattern)
{
	int	i;
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
		if (!ft_strncmp(shell.command, "env", ft_strlen(shell.command))
			|| !ft_strncmp(shell.command, "clear", ft_strlen(shell.command)))
			printf("%s: invalid option -- '%c'\n", shell.command, letter);
		else
			printf("bash: %s: -%c: invalid option\n", shell.command, letter);
		return (0);
	}
	return (1);
}
