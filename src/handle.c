/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:20:05 by macarval          #+#    #+#             */
/*   Updated: 2023/04/07 14:56:11 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Refazer make_shell para criar tabela de comandos

t_shell	make_shell(char *line)
{
	char	**split;
	t_shell	shell;
	int		size;

	split = ft_split(line, ' ');
	size = size_split(split);
	shell.command = handling(split[0]);
	if (size > 1)
		shell.flag = handling(split[1]);
	if (size > 2)
		shell.content = ft_strnstr(line, split[2], ft_strlen(line));
	// free_split(split);
	// free(line);
	return (shell);
}

char	*handling(char *split)
{
	char	*res;
	char	*temp;

	res = NULL;
	res = split;
	temp = split;
	if (temp[0] == '"')
		res = ft_strtrim(split, "\"");
	else if (temp[0] == '\'')
		res = ft_strtrim(split, "'");
	return (res);
}

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
