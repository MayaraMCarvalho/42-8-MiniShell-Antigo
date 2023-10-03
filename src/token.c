/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:29:27 by macarval          #+#    #+#             */
/*   Updated: 2023/10/03 20:43:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	***tokenization(t_shell *shell)
{
	char	*line;
	char	***lex;
	char	**token;

	line = remove_quotes_void(shell->line);
	token = ft_split_mod(line, ' ');
	free(line);
	verify_expasion(token, shell);
	remove_quotes(token);
	//Separar pipes e redirections
	lex = lexer(token);
	if (!lex)
		return (NULL);
	free_array(&token);
	return (lex);
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
	char	*str;

	str = ft_strrchr(token, '.');
	if (!strcmp_mod(str, ".txt")
		|| !strcmp_mod(str, ".c"))
		return (FILE);
	else if (ft_strchr(token, ' ') != NULL)
		return (CONTENT);
	else if (verify_list(token,
			ft_split("echo cd pwd export unset env exit clear history", ' ')))
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
