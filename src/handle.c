/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/05/05 17:49:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Refazer make_shell para criar tabela de comandos

t_shell	make_shell(char *line)
{
	// Configuração de teste
	char	**split;
	t_shell	shell;
	int		tam_command;

	inicialize(&shell);
	split = ft_split(line, ' ');
	shell.command = ft_strdup(split[0]);
	tam_command = ft_strlen(shell.command);
	if (split[1])
	{
		if ((split[1][0] == '-'
			&& ft_strncmp(shell.command, "echo", tam_command)))
		if ((split[1][0] == '-'
			&& ft_strncmp(shell.command, "echo", tam_command))
			|| (!ft_strncmp(shell.command, "echo", tam_command)
			&& !ft_strncmp(split[1], "-n", ft_strlen(split[1]) + 1)))
			shell.flag = ft_strdup(split[1]);
		else
			shell.content = ft_substr(line, tam_command + 1, ft_strlen(line));
		if (!shell.content && split[2])
		{
			if (shell.content)
				free(shell.content);
			if (shell.flag)
				shell.content = ft_substr(line, tam_command
						+ ft_strlen(shell.flag) + 2, ft_strlen(line));
			else
				shell.content = ft_substr(line, tam_command + 1,
						ft_strlen(line));
		}
	}
	free(line);
	free_split(&split);
	/*

	// char	**split;
	// t_shell	shell;
	// int		size;

	// split = ft_split(line, ' ');
	// size = size_split(split);
	// shell.command = handling(split[0]);
	// if (size > 1)
	// 	shell.flag = handling(split[1]);
	// if (size > 2)
	// 	shell.content = ft_strnstr(line, split[2], ft_strlen(line));
	// free_split(split);
	// free(line);
	*/
	return (shell);
}

// char	*handling(char *split)
// {
// 	char	*res;
// 	char	*temp;

// 	res = NULL;
// 	res = split;
// 	temp = split;
// 	if (temp[0] == '"')
// 		res = ft_strtrim(split, "\"");
// 	else if (temp[0] == '\'')
// 		res = ft_strtrim(split, "'");
// 	return (res);
// }

// char	regex(const char *str)
// {
// 	int		i;
// 	char	*res;

// 	i = 0;
// 	res = (char *) malloc((ft_strlen(str) + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		res[i] = str[i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }

// int	size_split(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split[++i])
// 		i++;
// 	return (i);
// }
