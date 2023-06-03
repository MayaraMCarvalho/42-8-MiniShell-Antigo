/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:21:16 by macarval          #+#    #+#             */
/*   Updated: 2023/06/03 16:48:21 by macarval         ###   ########.fr       */
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
	if (shell.content[0] == '=' || !ft_isalpha(shell.content[0])
		|| isalnum_mod(shell.content) || (!strcmp_mod(shell.command, "unset")
			&& ft_strchr(shell.content, '=')))
	{
		printf("bash: %s: `%s': not a valid identifier\n",
			shell.command, shell.content);
		return (0);
	}
	return (1);
}

void	apart_args(t_shell shell, char c, int (*function)(t_shell))
{
	int		i;
	char	**split;
	int		control;

	i = -1;
	if (shell.content)
	{
		split = ft_split(shell.content, c);
		if (function == add_local && is_args_local(split))
		{
			free_split(&split);
			return ;
		}
		while (split[++i])
		{
			shell.content = split[i];
			control = function(shell);
			if (control == 1 && split[i + 1])
				printf(" ");
			if (control == 0 && !split[i + 1]
				&& !strcmp_mod(shell.command, "echo"))
				printf("\b");
		}
		free_split(&split);
	}
}
