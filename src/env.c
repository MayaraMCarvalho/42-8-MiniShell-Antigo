/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:46 by macarval          #+#    #+#             */
/*   Updated: 2023/05/26 16:10:57 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_env(t_shell shell)
{
	if (!strcmp_mod(shell.command, "env"))
	{
		if (!is_flag_null(shell))
			return (1);
		while (shell.env != NULL)
		{
			if (shell.env->type != LOCAL && shell.env->msg)
				printf("%s=%s\n", shell.env->var, shell.env->msg);
			shell.env = shell.env->next;
		}
		return (1);
	}
	return (0);
}

t_lst	*make_list(char **envp)
{
	t_lst	*env;
	t_lst	*node;

	env = NULL;
	while (*envp)
	{
		node = NULL;
		node = insert_front(node,
				strchr_rev(*envp, '='), strchr_mod(*envp, '='), ENVP);
		insert_last(&env, node);
		envp++;
	}
	return (env);
}

t_lst	*insert_front(t_lst *new, char *var, char *msg, int type)
{
	t_lst	*node;

	node = (t_lst *) malloc (sizeof (t_lst));
	if (!node)
		return (0);
	node->var = NULL;
	node->msg = NULL;
	node->type = type;
	if (var)
		node->var = ft_strdup(var);
	if (msg)
		node->msg = ft_strdup(msg);
	node->prev = NULL;
	node->next = new;
	if (new != NULL)
		new->prev = node;
	free(var);
	return (node);
}

void	insert_last(t_lst **lst, t_lst *new)
{
	t_lst	*list;

	if (!lst)
		return ;
	if (*lst)
	{
		list = *lst;
		while (list->next != NULL)
			list = list->next;
		list->next = new;
		new->prev = list;
	}
	else
		*lst = new;
}
