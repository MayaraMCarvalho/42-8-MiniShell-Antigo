/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:56:13 by macarval          #+#    #+#             */
/*   Updated: 2023/09/15 19:47:53 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	***lexer(char	**token)
{
	char	***lex;

	lex = malloc_lexer(token_size(token));
	if (!lex)
		return (NULL);
	copy_token(lex, token);
	//identicar tokens
	return (lex);
}

char	***malloc_lexer(int size)
{
	char	***lex;
	int		i;
	int		cols;

	i = 0;
	cols = 2;
	lex = (char ***) malloc ((size + 1) * sizeof(char **));
	if (!lex)
		return (NULL);
	while (i < size)
	{
		lex[i] = (char **) malloc (cols * sizeof(char *));
		if (!lex[i])
		{
			while (--i >= 0)
				free(lex[i]);
			free(lex);
			return (NULL);
		}
		lex[i][1] = ft_strdup("Comando"); // Deletar
		i++;
	}
	return (lex);
}

void	copy_token(char ***lex, char **token)
{
	int	size;
	int	i;

	i = -1;
	size = token_size(token);
	while (++i < size)
		lex[i][0] = ft_strdup(token[i]);
	lex[i] = NULL;
}
