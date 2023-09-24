/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:59:02 by macarval          #+#    #+#             */
/*   Updated: 2023/09/23 21:49:42 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_quotes(const char *str)
{
	char	quote;
	int		i;

	i = 0;
	if (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
			i++;
	}
	return (i);
}

int	quotes_close(const char *str)
{
	int		control;
	char	quote;
	int		i;

	i = 0;
	control = -1;
	while (str[i] && control != 0)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			control = 0;
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				control++;
		}
		i++;
	}
	return (control);
}

void	remove_quotes(char **token)
{
	char	*temp;
	int		tam;
	int		pair_quotes;

	pair_quotes = 2;
	while (*token)
	{
		tam = quotes_close((*token));
		if (tam > 0)
		{
			tam = ft_strlen(*token) - (pair_quotes * tam);
			temp = (char *) malloc ((tam + 1) * sizeof(char));
			if (!temp)
				return ;
			clear_quotes(token, temp);
		}
		token++;
	}
}

void	clear_quotes(char **token, char *temp)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while ((*token) && (*token)[i])
	{
		if ((*token)[i] && ((*token)[i] == '\'' || (*token)[i] == '"'))
		{
			quote = (*token)[i];
			i++;
			while ((*token)[i] && (*token)[i] != quote)
				temp[j++] = (*token)[i++];
		}
		else
			temp[j++] = (*token)[i];
		i++;
	}
	temp[j] = '\0';
	free(*token);
	*token = temp;
}
