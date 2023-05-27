/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:21:16 by macarval          #+#    #+#             */
/*   Updated: 2023/05/27 17:31:38 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_lst	*find_arg(t_shell shell, char *var)
{
	t_lst	*temp;

	temp = shell.env;
	while (temp != NULL)
	{
		if (!strcmp_mod(temp->var, var))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	is_args(t_shell shell)
{
	if (shell.content[0] == '=' || ft_isdigit(shell.content[0]))
	{
		printf("bash: %s: `%s': not a valid identifier\n",
			shell.command, shell.content);
		return (0);
	}
	return (1);
}

void	apart_args(t_shell shell, char c, void (*function)(t_shell))
{
	int		i;
	char	**split;

	i = -1;
	split = ft_split(shell.content, c);
	while (split[++i])
	{
		shell.content = split[i];
		function(shell);
	}
	free_split(&split);
}
