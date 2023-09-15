/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:29:27 by macarval          #+#    #+#             */
/*   Updated: 2023/09/15 19:44:05 by macarval         ###   ########.fr       */
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

void	remove_quotes(char **token)
{
	char	quote[2];
	char	*temp;

	quote[1] = '\0';
	while (*token)
	{
		if (quotes_close(*token)
			&& (*token[0] == '\'' || *token[0] == '"'))
		{
			quote[0] = *token[0];
			temp = ft_strtrim(*token, quote);
			free(*token);
			*token = temp;
		}
		token++;
	}
}

int	token_size(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}
