/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:59:02 by macarval          #+#    #+#             */
/*   Updated: 2023/09/15 19:25:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_quotes(const char *str)
{
	char	quote;
	int		i;

	i = 0;
	if ((str[i] == '\'' || str[i] == '"'))
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
				control = 1;
		}
		i++;
	}
	return (control);
}
