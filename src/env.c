/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:36:46 by macarval          #+#    #+#             */
/*   Updated: 2023/06/03 17:24:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	c_env(t_shell shell)
{
	if (!strcmp_mod(shell.command, "env"))
	{
		update_(shell);
		if (!is_flag_null(shell))
			return (1);
		if (shell.content != NULL)
		{
			printf("%s: ‘%s’: No such file or directory\n",
				shell.command, shell.content);
			return (1);
		}
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
	char	*var;

	env = NULL;
	while (*envp)
	{
		var = strchr_rev(*envp, '=');
		node = NULL;
		node = insert_front(node, var, strchr_mod(*envp, '='), ENVP);
		free(var);
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

t_lst	*duplicate_env(t_lst *env)
{
	t_lst	*lst;
	t_lst	*node;

	lst = NULL;
	while (env != NULL)
	{
		node = NULL;
		node = insert_front(node, env->var, env->msg, env->type);
		insert_last(&lst, node);
		env = env->next;
	}
	return (lst);
}
