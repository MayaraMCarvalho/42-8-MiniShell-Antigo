/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:14:03 by macarval          #+#    #+#             */
/*   Updated: 2023/05/20 23:14:14 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// Passar norminette

int	c_echo(t_shell shell)
{
	int	isflag;

	isflag = 0;
	if (!strcmp_mod(shell.command, "echo"))
	{
		// Alterar para imprimir variavel de ambiente
			if (shell.env)
			{}
		//
		if (shell.flag && !strcmp_mod(shell.flag, "-n"))
			isflag = 1;
		if (shell.content)
		{
			if (!strcmp_mod(shell.content, "$?"))
				printf("%s", shell.content);//mudar
			else
				printf("%s", shell.content);
		}
		if (isflag == 0)
			printf("\n");
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
