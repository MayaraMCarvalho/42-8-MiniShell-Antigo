/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/02/23 19:10:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	echo(t_shell shell)
{
	int	isflag;
	int	i;

	i = 0;
	isflag = 0;
	if (!ft_strncmp(shell.command, "echo", ft_strlen(shell.command)))
	{
		if (!ft_strncmp(shell.flag, "-n", ft_strlen(shell.flag)))
			isflag = 1;
		if (isflag == 1)
			printf("%s", shell.content);
		else
		{
			printf("%s %s", shell.flag, shell.content);
			printf("\n");
		}
		return (1);
	}
	return (0);
}

// char	*process_text(t_shell shell, int tam)
// {
// 	char	*temp;
// 	char	*content;

// 	temp = NULL;
// 	content = ft_substr(line, tam, ft_strlen(line));
// 	if (content[0] == '"' && content[ft_strlen(content) - 1] == '"')
// 		temp = ft_strtrim(content, "\"");
// 	else if (content[0] == '\'' && content[ft_strlen(content) - 1] == '\'')
// 		temp = ft_strtrim(content, "\'");
// 	if (temp)
// 	{
// 		free(content);
// 		content = temp;
// 	}
// 	return (content);
// }
