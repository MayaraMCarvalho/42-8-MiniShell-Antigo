/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:35:31 by macarval          #+#    #+#             */
/*   Updated: 2023/09/25 16:29:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	verify_commands(char *token)
{
	char	*path;
	char	*temp;
	char	**split;
	int		i;

	path = getenv("PATH");
	split = ft_split(path, ':');
	i = -1;
	while (split[++i])
	{
		temp = ft_strjoin(split[i], "/");
		path = ft_strjoin(temp, token);
		free(temp);
		if (strcmp_mod(token, "com")
			&& !access(path, X_OK))
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

int	verify_list(char *token, char **list)
{
	int	i;

	i = -1;
	while (list[++i])
	{
		if (!strcmp_mod(token, list[i]))
		{
			free_array(&list);
			return (1);
		}
	}
	free_array(&list);
	return (0);
}
