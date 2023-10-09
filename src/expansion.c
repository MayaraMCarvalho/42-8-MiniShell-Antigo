/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:23:21 by macarval          #+#    #+#             */
/*   Updated: 2023/10/09 12:50:49 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	verify_expasion(char **token, t_shell *shell)
{
	int		i;
	char	*init;
	char	*var;
	char	*content;

	i = 0;
	while (token[i])
	{
		if (ft_strchr(token[i], '$') &&
			!verify_literal(token[i]) && token[i][1])
		{
			init = strchr_rev(token[i], '$');
			var = apart_var(shell, ft_strchr(token[i], '$'));
			if (var)
				content = ft_strjoin(init, var);
			else
				content = ft_strdup(init);
			free(var);
			free(token[i]);
			token[i] = ft_strdup(content);
			free(content);
			free(init);
		}
		i++;
	}
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

char	*apart_var(t_shell *shell, char *token)
{
	int		i;
	char	**split;
	char	*temp;
	char	*temp2;
	char	*str;

	i = -1;
	str = NULL;
	if (token)
	{
		split = ft_split(token, '$');
		while (split[++i])
		{
			temp = get_var(split[i], shell);
			temp2 = ft_strjoin(str, temp);
			free(str);
			free(temp);
			str = ft_strdup(temp2);
			free(temp2);
		}
		if (token[ft_strlen(token) - 1] == '$')
			str = put_final_sign(str);
		free_array(&split);
	}
	return (str);
}

char	*get_var(char *token, t_shell *shell)
{
	t_lst	*node;
	char	*final;
	char	*var;
	int		i;

	i = 1;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	final = ft_substr(token, i, ft_strlen(token) - i);
	var = ft_substr(token, 0, i);
	node = find_arg(*shell, var);
	free(var);
	if (node && node->msg)
		var = ft_strjoin(node->msg, final);
	else
		var = ft_strdup(final);
	free(final);
	return (var);
}

char	*put_final_sign(char *str)
{
	char	*temp;

	temp = ft_strjoin(str, "$");
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}
