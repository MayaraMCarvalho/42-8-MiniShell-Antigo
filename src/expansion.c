/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:23:21 by macarval          #+#    #+#             */
/*   Updated: 2023/10/16 11:53:22 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	verify_expansion(char **token, t_shell *shell)
{
	int		i;
	char	*init;
	char	*content;

	i = 0;
	while (token[i])
	{
		init = ft_strchr(token[i], '/');
		if (!strcmp_mod(token[i], "~") || !strcmp_mod(token[i], "~/")
			|| (init && token[i][0] == '~'))
		{
			free(token[i]);
			token[i] = ft_strjoin(getenv("HOME"), init);
		}
		else if (ft_strchr(token[i], '$') && !verify_literal(token[i])
			&& strcmp_mod(token[i], "$_") && strcmp_mod(token[i], "$?")
			&& token[i][1])
		{
			content = join_expansion(shell, token[i]);
			free(token[i]);
			token[i] = content;
		}
		i++;
	}
}

char	*join_expansion(t_shell *shell, char *token)
{
	char	*init;
	char	*var;
	char	*content;

	init = strchr_rev(token, '$');
	var = apart_var(shell, ft_strchr(token, '$'));
	if (var)
		content = ft_strjoin(init, var);
	else
		content = ft_strdup(init);
	free(var);
	free(init);
	if (content[0] == '\0')
	{
		free(content);
		content = NULL;
	}
	return (content);
}

int	verify_literal(char *token)
{
	int		start;
	int		final;
	int		i;
	char	*res;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			start = i++;
			while (token[i] && token[i] != '\'')
				i++;
			final = i;
			res = ft_substr(token, start, final);
			if (ft_strchr(res, '$'))
			{
				free (res);
				return (1);
			}
			free (res);
		}
		i++;
	}
	return (0);
}
