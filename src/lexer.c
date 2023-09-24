/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:56:13 by macarval          #+#    #+#             */
/*   Updated: 2023/09/23 21:32:17 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	***lexer(char	**token)
{
	char	***lex;
	int		size;

	size = token_size(token);
	lex = malloc_lexer(size);
	if (!lex)
		return (NULL);
	copy_token(lex, token);
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
		i++;
	}
	return (lex);
}
