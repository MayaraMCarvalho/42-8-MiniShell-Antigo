/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:29:27 by macarval          #+#    #+#             */
/*   Updated: 2023/09/25 18:32:03 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**tokenization(char *line)
{
	char	**token;

	token = ft_split_mod(line, ' ');
	remove_quotes(token);
	free(line);
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
		lex[i][1] = ft_strdup(id_token(token[i]));
	}
	lex[i] = NULL;
}

char	*id_token(char *token)
{
	if (!strcmp_rev(token, ".txt")
		|| !strcmp_rev(token, ".c"))
		return (FILE);
	else if (ft_strchr(token, ' ') != NULL)
		return (CONTENT);
	else if (verify_list(token,
			ft_split("echo cd pwd export unset env exit clear", ' ')))
		return (BUILTIN);
	else if (verify_commands(token))
		return (COMMAND);
	else if (token[0] == '-')
		return (FLAG);
	else if (verify_list(token, ft_split("> < >> <<", ' ')))
		return (OPERATOR);
	else if (!strcmp_mod(token, "|"))
		return (PIPE);
	else
		return (CONTENT);
}
