/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:21:16 by macarval          #+#    #+#             */
/*   Updated: 2023/09/25 17:22:09 by macarval         ###   ########.fr       */
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
	char	*content;
	t_lst	*var;

	content = shell.content;
	if (content[0] == '=' || !ft_isalpha(content[0])
		|| isalnum_mod(content) || (!strcmp_mod(shell.command, "unset")
			&& ft_strchr(content, '=')))
	{
		var = find_arg(shell, content + 1);
		if (content[0] == '$' && var)
			content = var->msg;
		printf("bash: %s: `%s': not a valid identifier\n",
			shell.command, content);
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
			free_array(&split);
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
		free_array(&split);
	}
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
		free_array(&split);
	}
	return (str);
}
