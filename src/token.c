/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:29:27 by macarval          #+#    #+#             */
/*   Updated: 2023/09/23 20:50:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**tokenization(t_shell *shell)
{
	char	**token;

	token = ft_split_mod(shell->line, ' ');
	remove_quotes(token);
	return (token);
}

int	token_size(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

void	copy_token(char ***lex, char **token)
{
	int	size;
	int	i;

	i = -1;
	size = token_size(token);
	while (++i < size)
	{
		lex[i][0] = ft_strdup(token[i]);
		lex[i][1] =  ft_strdup(id_token(token[i]));
	}
	lex[i] = NULL;
}

char	*id_token(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (ft_strchr(token, ' ') != NULL)
		return (CONTENT);
	else if (ft_strnstr("echo cd pwd export unset env exit clear",
			token, len))
		return (BUILTIN);
	else if (verify_commands(token))
		return (COMMAND);
	else if (token[0] == '-')
		return (FLAG);
	else if (ft_strnstr("> < >> <<", token, len))
		return (OPERATOR);
	else if (!strcmp_mod(token, "|"))
		return (PIPE);
	else if (!strcmp_rev(token, ".txt")
		|| !strcmp_rev(token, ".c"))
		return (FILE);
	else
		return (CONTENT);
}

int	verify_commands(char *token)
{
	char	*path;
	char	*temp;
	char	**split;

	path = getenv("PATH");
	split = ft_split(path, ':');
	int i = -1;
	while (split[++i])
	{
		temp = ft_strjoin(split[i], "/");
		path = ft_strjoin(temp, token);
		free(temp);
		if (!access(path, X_OK))
		{
			free_array(&split);
			free(path);
			return (1);
		}
		free(path);
	}
	free_array(&split);
	return (0);
}
