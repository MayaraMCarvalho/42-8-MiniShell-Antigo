/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:49:16 by macarval          #+#    #+#             */
/*   Updated: 2023/10/14 13:48:51 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	verify_flags(char *flag, char *pattern)
{
	int		i;
	char	letter;

	i = 0;
	letter = '\0';
	if (flag)
	{
		if (flag[0] == '-')
			i++;
		if (!flag[i])
			return ('-');
		while (flag[i] && letter == '\0')
		{
			if (!ft_strchr(pattern, flag[i]))
				letter = flag[i];
			i++;
		}
	}
	return (letter);
}

int	is_flag_null(t_shell *shell)
{
	char	letter;

	letter = verify_flags(shell->flag, NULL);
	if (letter != '\0')
	{
		if (!strcmp_mod(shell->command, "env")
			|| !strcmp_mod(shell->command, "clear"))
		{
			printf("%s: invalid option -- '%c'\n", shell->command, letter);
			shell->exit_code = 1;
		}
		else
		{
			printf("bash: %s: -%c: invalid option\n", shell->command, letter);
			shell->exit_code = 2;
		}
		return (0);
	}
	return (1);
}
